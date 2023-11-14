# FlexBisonSimpleC
Flex+Bison+AST+LLVM
Builded with win ver Bison, Flex aka win-bison, win-flex + LLVM-C 
## Сборка
win-bison -d -o parser.c parser.y
win-flex -o lexer.c lexer.l
gcc -o compiler.exe lexer.c parser.c ast.c -lfl
./compiler.exe ./src.c 
(Удачи собрать через gcc или clang т.к. нужно подключать очень много библиотек или создать makefile)

Лучше собирать в Visual Studio 2022
Список необходимых библиотек можно посмотреть утилитой llvm-config:
llvm-config --cflags --ldflags --system-libs --libs all

## Output (LLVM IR) with src.c

```
; ModuleID = 'test_module'
source_filename = "test_module"

@a = global i32 0
@b = global double 0
@c = global i1 false

define void @main() {
entry:
  store i32 8, ptr @a, align 4
  store double 3.140000e+00, ptr @b, align 8
  store i1 true, ptr @c, align 1
  store ptr add (ptr @a, i32 10), ptr @a, align 8
  %divtmp = sdiv ptr @b, double 2.000000e+00
  store ptr %divtmp, ptr @b, align 8
}
```
