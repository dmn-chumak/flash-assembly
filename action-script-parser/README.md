# action-script-parser

Almost finished implementation of ActionScript 3.0 language lexer/parser.

```actionscript
var sourceFile:String = "ActionScript 3.0 source code here";

var cursor:Cursor = new Cursor();
var lexer:Lexer = new Lexer(cursor);
var parser:Parser = new Parser(lexer);

trace(parser.process());
```
