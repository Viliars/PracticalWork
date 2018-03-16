paral: paral.c
	gcc -ansi -pedantic -Wall paral.c -o paral
prog1:
	gcc prog1.c -o prog1
prog2:
	gcc prog2.c -o prog2
run: paral prog1 prog2
	./paral prog1 arg11 arg12 prog2 arg21 arg22
