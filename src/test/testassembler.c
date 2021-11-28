/*
-----------------------------------------------------------------------------------------
 testassembler tests inline assembler code. 
 
 To compile:

     gcc testassembler.c -o testassembler.exe
	 
 To translate in assembler:
 
     testassembler -S testassembler.c 
	 
 To compile the translated file:
 
     gcc testassembler.s -o testassembler2.exe

+------------------------------+------------------------------------+
|       Intel Code             |      AT&T Code                     |
+------------------------------+------------------------------------+
| add     eax,[ebx]	           |  addl    %ebx,%eax                 |   
+------------------------------+------------------------------------+
 
-----------------------------------------------------------------------------------------
*/

#include <stdio.h>
void main()
{
int a = 2, b = 18;
asm(
"addl  %%ebx,%%eax":"=a"(a):"a"(a), "b"(b)
);
printf("2 + 18 = %d\n", a );
return;
}