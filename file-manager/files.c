// File Manager
//
// Copyright (C) 2017 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#include "files.h"

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <dlfcn.h>


static struct Panel left = {
	.wnd = NULL,
	.files = NULL,
	.cur_file = 0
};

static struct Panel right = {
	.wnd = NULL,
	.files = NULL,
	.cur_file = 0,
};

unsigned cur_panel = LEFT_PANEL;


static struct FileList *GetFiles(const char *path)
{
	struct FileList *file_list = NULL;
	DIR *dir;
	struct dirent *f_cur;

    if ((dir = opendir(path)) == NULL) {
    	puts("Fail reading files folder.");
        return NULL;
    }

    while ((f_cur = readdir(dir)) != NULL) {
    	struct File *file;
    	struct stat st;
    	int fd;

    	if (f_cur->d_name[0] == '.' && f_cur->d_name[1] != '.')
    		continue;

    	file = (struct File *)malloc(sizeof(file));
    	strcpy(file->name, f_cur->d_name);

    	fd = open(f_cur->d_name, O_RDONLY, 0);
    	fstat(fd, &st);
    	file->size = st.st_size;
    	close(fd);

    	file_list = FileListAdd(file_list, file);
    }
    closedir(dir);
    return file_list;
}

void SetCurPanel(unsigned panel)
{
	cur_panel = panel;
}

void SetFilesWindows(WINDOW *left_wnd, WINDOW *right_wnd)
{
	left.wnd = left_wnd;
	right.wnd = right_wnd;
}

void LeftFilesReadDir(const char *path)
{
	if (left.files != NULL)
		FileListFree(left.files);

	left.files = GetFiles(path);
	strcpy(left.cur_path, path);
}

void LeftFilesShow()
{
	struct FileList *files = NULL;
	unsigned count = 1;
	char out[40];

	wclear(left.wnd);
	box(left.wnd, 0, 0);

	for (files = left.files; files != NULL; files = FileListNext(files)) {
		struct File *file = FileListGet(files);

		if ((count-1) == left.cur_file && cur_panel == LEFT_PANEL) {
			sprintf(out, "[%s (%lu B)]", file->name, file->size);
			mvwprintw(left.wnd, count, 2, out);

		} else {
			sprintf(out, "%s (%lu B)", file->name, file->size);
			mvwprintw(left.wnd, count, 2, out);
		}
		count++;

		if (count == MAX_FILES)
			break;
	}
	wrefresh(left.wnd);
}

void LeftSetCurrent(unsigned num)
{
	left.cur_file = num;
}

void RightFilesReadDir(const char *path)
{
	if (right.files != NULL)
		FileListFree(right.files);

	right.files = GetFiles(path);
	strncpy(right.cur_path, path, 255);
}

void RightFilesShow()
{
	struct FileList *files = NULL;
	unsigned count = 1;
	char out[40];

	wclear(right.wnd);
	box(right.wnd, 0, 0);

	for (files = right.files; files != NULL; files = FileListNext(files)) {
		struct File *file = FileListGet(files);

		if ((count-1) == right.cur_file && cur_panel == RIGHT_PANEL) {
			sprintf(out, "[%s (%lu B)]", file->name, file->size);
			mvwprintw(right.wnd, count, 2, out);

		} else {
			sprintf(out, "%s (%lu B)", file->name, file->size);
			mvwprintw(right.wnd, count, 2, out);
		}
		count++;

		if (count == MAX_FILES)
			break;
	}
	wrefresh(right.wnd);
}

void RightSetCurrent(unsigned num)
{
	right.cur_file = num;
}