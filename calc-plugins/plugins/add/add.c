// Calculator addition plugin
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

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