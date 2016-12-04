// Calculator addition plugin
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#ifndef ADD_LIB_H_
#define ADD_LIB_H_


struct lib_info {
	char description[255];
	char func_name[255];
};

struct lib_info *get_lib_info(void);

int add(int a, int b);


#endif