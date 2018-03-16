131.o: 131.asm
	nasm -f elf32 131.asm -o 131.o
131: 131.o 131.asm
	ld -m elf_i386 411.o -o 131
run: 131
	./131
