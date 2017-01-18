// File Manager
//
// Copyright (C) 2017 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#ifndef FILE_LIST_H_
#define FILE_LIST_H_

#include <stdio.h>


struct File {
	unsigned long size;
	char name[100];
};

struct FileList {
    struct File *file;
    struct FileList *next;
};


struct FileList *FileListAdd(struct FileList *file_list, struct File *new_file);

struct FileList *FileListNext(struct FileList *file_list);

struct File *FileListGet(struct FileList *file_list);

void FileListFree(struct FileList *file_list);


#endif