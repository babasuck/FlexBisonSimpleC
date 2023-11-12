# FlexBisonSimpleC
Flex+Bison+AST
Builded with win ver Bison, Flex aka win-bison, win-flex
win-bison -d -o parser.c parser.y
win-flex -o lexer.c lexer.l
gcc -o compiler.exe lexer.c parser.c ast.c -lfl
./compiler.exe ./src.c
Output with src.c:
Declaration of int: a
Declaration of double: b
Declaration of bool: c
Integer: 5
Assignment to a
Integer: 5
Double: 3.140000
Assignment to b
Double: 3.140000
Assignment to c
Identifier: a
Integer: 10
Binary Op: +
Identifier: a
Integer: 10
testAssignment to a
Binary Op: +
Identifier: a
Integer: 10
Identifier: b
Double: 2.000000
Identifier: b
Double: 2.000000
Assignment to b
Binary Op: /
Parsing successful.
