#!/usr/bin/env bash

#------------------------------------------------------

compose_start=`date +%s`

#------------------------------------------------------

files=1;

echo "Merging JavaScript external files to single file ..."
cat ../ref/*.js > flash.js

echo "Compiling C++ source files to LLVM bytecode ..."
find ../src -name "*.cpp" | while read file; do
    if [[ ${file} != *"generic"* ]]; then
        clang++ -O3 --std=c++17 --target=wasm32 --compile --include-directory=../src -emit-llvm -fno-rtti -fno-exceptions -ffreestanding -fvisibility=hidden -o flash_${files}.bc ${file}
        echo "Compiling C++ source file $file [$files] ..."
        (( files++ ))
    fi
done

echo "Linking LLVM bytecode to single file ..."
bc_files=('flash_*.bc')
llvm-link -o flash.bc ${bc_files[@]}
rm ${bc_files[@]}

echo "Translating LLVM bytecode to LLVM text format ..."
llc -march=wasm32 -filetype=asm -asm-verbose=false -O3 -thread-model=single -o flash.sc flash.bc
rm flash.bc

echo "Translating from LLVM text format to WebAssembly text format ..."
s2wasm --ignore-unknown --global-base=0 --allocate-stack=4096 --trap-mode=js -o flash.wast flash.sc
rm flash.sc

echo "Fixing several WebAssembly text format exports ..."
sed -i 's/(memory $0 /(memory (export "memory") /g' flash.wast
sed -i 's/(table /(table (export "table") /g' flash.wast
sed -i '/(export "memory" /d' flash.wast
sed -i '/(export "_ZdaPv" /d' flash.wast
sed -i '/(export "_ZdlPv" /d' flash.wast
sed -i '/(export "_Znaj" /d' flash.wast
sed -i '/(export "_Znwj" /d' flash.wast

echo "Translating from WebAssembly text format to bytecode ..."
wat2wasm -o flash.wasm flash.wast
rm flash.wast

#------------------------------------------------------

dispose_time=`date +%s`
summary_time=$((dispose_time - compose_start))

#------------------------------------------------------

echo "Compilation time: $summary_time seconds"
