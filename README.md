# Flash Assembly

Nothing special, just a failed project of porting Flash (ActionScript 3.0) applications to the WebAssembly platform.

This repository contains an unfinished implementation of the ActionScript 3.0 language (and AVM2.0 bytecode) transpiler to C++. In 2017-18 years, when it was clear that Flash technology support planned to refuse in browsers, I had an idea to port Flash application to WebAssembly. It was a part of learning and diving into programming languages lexer/parser, and due to lack of time was abandoned.

- **action-script-parser** contains almost finished implementation of ActionScript 3.0 language lexer/parser;

- **byte-code-parser** contains some progress for AVM2.0 bytecode parser;

- **flash-runtime-engine** contains C++ classes with a very simple implementation of native Flash APIs.

You will need FlashSDK, LLVM, WebAssembly tools, and some other tools to build these sources. And most likely some of the latest WebAssembly tools are not compatible with this code. There are no instructions/guides on how to run this code, and most likely never will be.

Flash ♥
