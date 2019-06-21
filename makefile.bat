flex lex.l
bison -d ffff.y
gcc lex.yy.c ffff.tab.c -lfl -ly -o prosamet 
prosamet test.txt
