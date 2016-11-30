// Calculator with plugins
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#ifndef PLUGINS_LIST_H_
#define PLUGINS_LIST_H_

#include <stdio.h>


struct plugin {
	char description[255];
	int (*func)(int, int);
};

struct plugins_list {
    struct plugin *plugin;
    struct plugins_list *next;
};


struct plugins_list *plugins_list_append(struct plugins_list *plist, struct plugin *new_plugin);

struct plugins_list *plugins_list_next(struct plugins_list *plist);

struct plugin *plugins_list_get_plugin(struct plugins_list *plist);

void plugins_list_free_all(struct plugins_list *plist);


#endif