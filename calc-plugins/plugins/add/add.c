#include "add.h"

static struct lib_info info = {
	.description = "Addition of numbers.",
	.func_name = "add"
};

struct lib_info *get_lib_info(void)
{
	return &info;
}

int add(int a, int b)
{
	return a+b;
}