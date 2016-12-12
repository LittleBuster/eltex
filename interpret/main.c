// Interpret numbers and structs
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#include <stdio.h>
#include <stdint.h>
#include <string.h>


struct Bits {
	unsigned a:1;
	unsigned b:1;
	unsigned c:1;
	unsigned d:1;
	unsigned e:1;
	unsigned f:1;
	unsigned g:1;
	unsigned h:1;
};

void PrintBits(int num)
{
	struct Bits *bits = (struct Bits *)(&num);
	printf("Num: %u Bits: %u%u%u%u%u%u%u%u\n", num, bits->h, bits->g, bits->f, bits->e, bits->d, bits->c, bits->b, bits->a);
}

struct Block {
	char a;
	int b;
} __attribute__((packed));


void InitBlocks(char *str_out, const struct Block *block)
{
	for (size_t i = 0; i < 15; i += 5) {
		memcpy(str_out, (char *)block, 5);
		str_out += i;
	}
}

void PrintBlocks(const char *str)
{
	char *p_str = (char *)str;
	size_t block_num = 0;

	for (size_t i = 0; i < 15; i += 5) {
		struct Block *block = (struct Block *)p_str;

		printf("Block[%lu] a=%c b=%i\n", block_num, block->a, block->b);

		p_str += i;
		block_num++;
	}
}

int main(void)
{
	int num = 200;
	char str[15];
	struct Block block1 = {'1', 0};
	struct Block block2 = {'1', 550};

	puts("Number to bits:");
	PrintBits(num);

	puts("Example 1:");
	InitBlocks(str, &block1);
	PrintBlocks(str);

	puts("Example 2:");
	InitBlocks(str, &block2);
	PrintBlocks(str);
	return 0;
}
