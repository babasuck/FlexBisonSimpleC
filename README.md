# FlexBisonSimpleC
Flex+Bison+AST
Builded with win ver Bison, Flex aka win-bison, win-flex
win-bison -d -o parser.c parser.y
win-flex -o lexer.c lexer.l
gcc -o compiler.exe lexer.c parser.c ast.c -lfl
./compiler.exe ./src.c
