// ADT for Bit-strings
// COMP1521 17s2 Week02 Lab Exercise
// Written by John Shepherd, July 2017
// Modified by ...

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Bits.h"

// assumes that an unsigned int is 32 bits
#define BITS_PER_WORD 32

// A bit-string is an array of unsigned ints (each a 32-bit Word)
// The number of bits (hence Words) is determined at creation time
// Words are indexed from right-to-left
// words[0] contains the most significant bits
// words[nwords-1] contains the least significant bits
// Within each Word, bits are indexed right-to-left
// Bit position 0 in the Word is the least significant bit
// Bit position 31 in the Word is the most significant bit

typedef unsigned int Word;

struct BitsRep {
   int nwords;   // # of Words
   Word *words;  // array of Words
};

// make a new empty Bits with space for at least nbits
// rounds up to nearest multiple of BITS_PER_WORD
Bits makeBits(int nbits)
{
   Bits new;
   new = malloc(sizeof(struct BitsRep));
   assert(new != NULL);
   int  nwords;
   if (nbits%BITS_PER_WORD == 0)
      nwords = nbits/BITS_PER_WORD;
   else
      nwords = 1+nbits/BITS_PER_WORD;
   new->nwords = nwords;
   // calloc sets to all 0's
   new->words = calloc(nwords, sizeof(Word));
   assert(new->words != NULL);
   return new;
}

// release space used by Bits
void  freeBits(Bits b)
{
   assert(b != NULL && b->words != NULL);
   free(b->words);
   free(b);
}

// form bit-wise AND of two Bits a,b
// store result in res Bits
void andBits(Bits a, Bits b, Bits res)
{
   // TODO
	int i;
	for(i=0;i<a->nwords;i++)
	{
		res->words[i] = a->words[i] & b->words[i];
	}
}

// form bit-wise OR of two Bits a,b
// store result in res Bits
void orBits(Bits a, Bits b, Bits res)
{
   // TODO
	int i;
	for(i=0;i<a->nwords;i++)
	{
		res->words[i] = a->words[i] | b->words[i];
	}
}

// form bit-wise negation of Bits a,b
// store result in res Bits
void invertBits(Bits a, Bits res)
{
	int i;
	for(i=0;i<a->nwords;i++)
	{
		res->words[i] = ~a->words[i];
	}
	//printf("%u   ",res->words[0]);
   // TODO
}

// left shift Bits
void leftShiftBits(Bits b, int shift, Bits res)
{
	*res->words = *b->words << shift;
   // challenge problem
}

// right shift Bits
void rightShiftBits(Bits b, int shift, Bits res)
{
	*res->words = *b->words >> shift;
   // challenge problem
}

// copy value from one Bits object to another
void setBitsFromBits(Bits from, Bits to)
{
	to->words=from->words;
	to->nwords=from->nwords;
   // TODO
}

// assign a bit-string (sequence of 0's and 1's) to Bits
// if the bit-string is longer than the size of Bits, truncate higher-order bits
void setBitsFromString(Bits b, char *bitseq)
{
	int i=0;
	int c;
	int j;
	int z = 0;
	Word a = 0;
	for(j=b->nwords-1;j>=0;j--)
	{	
		if(j!=b->nwords-1)
		{
			c = i-32;
			i=0;
		}
		a = 0;
		z=0;
		while((bitseq[i] == '1' || bitseq[i] == '0'))
		{
			if(z > 0)
			{
				a = a << 1;
			}
			if(bitseq[i] == '1')
			{
				a += 1;
			}
			else if(bitseq[i] != '1')
			{
			}
			if(i == c)
			{
				break;
			}
			i++;
			z++;
		}
		//a = a >> 1;
		b->words[j] = a;
	}
   // TODO
}

// display a Bits value as sequence of 0's and 1's
void showBits(Bits b)
{
	unsigned int num[b->nwords][32];
	int i;
	int j;
	Word res;
	for(j = 0;j<b->nwords;j++)
	{
		res = b->words[j];
		//printf("words[%d] = %d\n",j,b->words[j]);
		for(i=31;i>=0;i--)
		{
			//printf("  %d",res);
			num[j][i] = res & 1;
			res = (res-1) >> 1;
			
		}
		

	   // TODO
	}
	for(j=0;j<b->nwords;j++)
	{
		for(i=0;i<32;i++)
		{
			printf("%d",num[j][i]);
		}
	}



}
