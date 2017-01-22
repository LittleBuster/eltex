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

    	if (f_cur->d_type == DT_DIR)
    		file->type = TYPE_DIR;
    	else
    		file->type = TYPE_FILE;

    	fd = open(f_cur->d_name, O_RDONLY, 0);
    	fstat(fd, &st);
    	file->size = st.st_size;
    	close(fd);

    	file_list = FileListAdd(file_list, file);
    }
    closedir(dir);
    return file_list;
}

const char *GetCurPath(unsigned panel)
{
	if (panel == LEFT_PANEL)
		return left.cur_path;
	else
		return right.cur_path;
}

unsigned GetMax(unsigned panel)
{
	if (panel == LEFT_PANEL)
		return FileListCount(left.files);
	else
		return FileListCount(right.files);
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
			if (file->type == TYPE_DIR)
				sprintf(out, "[%s (%lu B) (DIR)]", file->name, file->size);
			else
				sprintf(out, "[%s (%lu B) (FILE)]", file->name, file->size);
			mvwprintw(left.wnd, count, 2, out);
		} else {
			if (file->type == TYPE_DIR)
				sprintf(out, "%s (%lu B) (DIR)", file->name, file->size);
			else
				sprintf(out, "%s (%lu B) (FILE)", file->name, file->size);
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
			if (file->type == TYPE_DIR)
				sprintf(out, "[%s (%lu B) (DIR)]", file->name, file->size);
			else
				sprintf(out, "[%s (%lu B) (FILE)]", file->name, file->size);
			mvwprintw(right.wnd, count, 2, out);
		} else {
			if (file->type == TYPE_DIR)
				sprintf(out, "%s (%lu B) (DIR)", file->name, file->size);
			else
				sprintf(out, "%s (%lu B) (FILE)", file->name, file->size);
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

bool RightChangeExec()
{
	struct FileList *files = NULL;
	unsigned count = 1;

	for (files = right.files; files != NULL; files = FileListNext(files)) {
		struct File *file = FileListGet(files);

		if ((count-1) == right.cur_file) {
			if (file->type == TYPE_DIR) {
				char path[255];

				if (!strcmp(file->name, "..")) {
					chdir("..");
					getcwd(path, 255);
					strcpy(right.cur_path, path);
					strcat(right.cur_path, "/");
					right.files = GetFiles(right.cur_path);

					return true;
				} else {
					strcat(right.cur_path, file->name);
					strcat(right.cur_path, "/");
					chdir(right.cur_path);
					right.files = GetFiles(right.cur_path);

					return false;
				}
			} else {
				//chdir(right.cur_path);
				AppExec(file->name);
			}
			break;
		}
		count++;
	}
	return false;
}

bool LeftChangeExec()
{
	struct FileList *files = NULL;
	unsigned count = 1;

	for (files = left.files; files != NULL; files = FileListNext(files)) {
		struct File *file = FileListGet(files);

		if ((count-1) == left.cur_file) {
			if (file->type == TYPE_DIR) {
				char path[255];

				if (!strcmp(file->name, "..")) {
					chdir("..");
					getcwd(path, 255);
					strcpy(left.cur_path, path);
					strcat(left.cur_path, "/");
					left.files = GetFiles(left.cur_path);
					return true;
				} else {
					strcat(left.cur_path, file->name);
					strcat(left.cur_path, "/");
					chdir(left.cur_path);
					left.files = GetFiles(left.cur_path);
					return false;
				}
			} else {
			//	chdir(left.cur_path);
				AppExec(file->name);
			}
			break;
		}
		count++;
	}
	return false;
}

void AppExec(const char *filename)
{
	char *ext;
	char file[255];
	char cmd[255];

	strcpy(file, filename);
	strtok(file, ".");
	ext = strtok(NULL, ".");

	if (ext == NULL) {
		sprintf(cmd, "./%s", filename);
		system(cmd);
		return;
	}
	if (ext[0] == 'p' && ext[1] == 'n' && ext[2] == 'g') {
		sprintf(cmd, "shotwell %s", filename);
		system(cmd);
	}
	if (ext[0] == 'j' && ext[1] == 'p' && ext[2] == 'g') {
		sprintf(cmd, "shotwell %s", filename);
		system(cmd);
	}
	if (ext[0] == 'j' && ext[1] == 'p' && ext[2] == 'e' && ext[3] == 'g') {
		sprintf(cmd, "shotwell %s", filename);
		system(cmd);
	}
	if (ext[0] == 't' && ext[1] == 'x' && ext[2] == 't') {
		sprintf(cmd, "gedit %s", filename);
		system(cmd);
	}
	if (ext[0] == 'c' && ext[1] == 'f' && ext[2] == 'g') {
		sprintf(cmd, "gedit %s", filename);
		system(cmd);
	}
	if (ext[0] == 'l' && ext[1] == 'o' && ext[2] == 'g') {
		sprintf(cmd, "gedit %s", filename);
		system(cmd);
	}
}