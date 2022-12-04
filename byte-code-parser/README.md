# byte-code-parser

Some progress with implementation of AVM2.0 bytecode parser.

```actionscript
TypeUtils.createList(ConstantType);
TypeUtils.createList(InstructionType);
TypeUtils.createList(BlockType);
TypeUtils.createList(TraitType);

TypeUtils.createMaps(AbcMethodVerifier);
TypeUtils.createMaps(OperatorUtils);

new Parser(
    SourceUtils.readSource(
        File.applicationDirectory
            .resolvePath('config.json')
            .nativePath
    )
);
```
