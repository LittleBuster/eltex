// Calculator multiplication test
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "../mul.h"


void exit_test(bool result)
{
	puts("----------------------------------");
	if (result)
		puts("Test complete. [OK]");
	else
		puts("Test not completed. [FAIL]");
}

int main(void)
{
	int ret_val;
	struct lib_info *info = NULL;

	puts("\nStarting multiplication test");
	puts("----------------------------------");

	// Test lib info
	info = get_lib_info();
	if (info == NULL) {		
		puts("[ERROR] Loading lib info.");
		exit_test(false);
		assert(info != NULL);
	}
	puts("[PASSED] Loading lib info.");

	// Test description
	ret_val = strcmp(info->description, "Multiplication of numbers.");
	if (ret_val != 0) {
		puts("[ERROR] Loading library description.");
		exit_test(false);
		assert(ret_val == 0);
	}
	puts("[PASSED] Loading library description.");

	// Test func name
	ret_val = strcmp(info->func_name, "mul");
	if (ret_val != 0) {
		puts("[ERROR] Loading library function name.");
		exit_test(false);
		assert(ret_val == 0);
	}
	puts("[PASSED] Loading library function name.");

	ret_val = mul(10, 3);
	if (ret_val != 30) {
		puts("[ERROR] Test multiplication function.");
		exit_test(false);
		assert(ret_val == 30);
	}
	puts("[PASSED] Test multiplication function.");

	exit_test(true);
	return 0;
}