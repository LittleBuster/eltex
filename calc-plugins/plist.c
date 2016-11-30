// Calculator with plugins
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#include "plist.h"
#include <stdlib.h>


static struct plugins_list *plugins_list_last(struct plugins_list *restrict plist)
{
    if (plist)
        while (plist->next)
            plist = plist->next;
    return plist;
}


struct plugins_list *plugins_list_append(struct plugins_list *plist, struct plugin *plugin)
{
    struct plugins_list *new_list;
    struct plugins_list *last;

    new_list = (struct plugins_list *)malloc(sizeof(new_list));
    new_list->plugin = plugin;
    new_list->next = NULL;

    if (plist) {
        last = plugins_list_last(plist);
        last->next = new_list;
        return plist;
    }
    return new_list;
}

struct plugin *plugins_list_get_meteo(struct plugins_list *plist)
{
    return plist->plugin;
}

struct plugins_list *plugins_list_next(struct plugins_list *plist)
{
    return plist->next;
}

void plugins_list_free_all(struct plugins_list *plist)
{
    struct plugins_list *tmp;

    if (!plist)
        return;

    while (plist) {
        tmp = plist;
        plist = plist->next;
        if (tmp->plugin != NULL)
            free(tmp->plugin);
        free(tmp);
    }
}