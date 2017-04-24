/* stack4-stdin.c
*
* specially crafted to feed your brain by gera */

#include <stdio.h>

void stack4();

int main() {
	stack4();
	return 0;
}
	
void stack4() {
	char buf[80];
	int cookie;
	printf("buf: %08x cookie: %08x\n", &buf, &cookie);
	gets(buf);
	printf("Cookie: %08x\n",cookie);
	if (cookie == 0x000d0a00)
		printf("you win!\n");
}