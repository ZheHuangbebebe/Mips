// where_are_the_bits.c ... determine bit-field order
// COMP1521 Lab 03 Exercise
// Written by ...

#include <stdio.h>
#include <stdlib.h>

struct _bit_fields {
   unsigned int a : 4,
                b : 8,
                c : 20;
};

int main(void)
{
   struct _bit_fields x;

	unsigned int val = 0;

	int i;
	x.a = 1;	
	x.c = 0;
	x.b = 0;
	printf("%u\n",x);
/*
	val = x.a;
	for(i=0;i<32;i++)
	{
		printf("%d",val&1U);
		if(i!=31)
		val = val >> 1;
	}
	printf("\n");
*/
   return 0;
}
