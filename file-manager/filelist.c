// File Manager
//
// Copyright (C) 2017 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#include "filelist.h"
#include <stdlib.h>


static struct FileList *FileListLast(struct FileList *restrict file_list)
{
    if (file_list)
        while (file_list->next)
            file_list = file_list->next;
    return file_list;
}


struct FileList *FileListAdd(struct FileList *file_list, struct File *new_file)
{
    struct FileList *new_list;
    struct FileList *last;

    new_list = (struct FileList *)malloc(sizeof(new_list));
    new_list->file = new_file;
    new_list->next = NULL;

    if (file_list) {
        last = FileListLast(file_list);
        last->next = new_list;
        return file_list;
    }
    return new_list;
}

struct File *FileListGet(struct FileList *file_list)
{
    return file_list->file;
}

struct FileList *FileListNext(struct FileList *file_list)
{
    return file_list->next;
}

void FileListFree(struct FileList *file_list)
{
    struct FileList *tmp;

    if (!file_list)
        return;

    while (file_list) {
        tmp = file_list;
        file_list = file_list->next;
        if (tmp->file != NULL)
            free(tmp->file);
        free(tmp);
    }
}