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


static struct {
	WINDOW *wnd;
	struct FileList *files;
	char cur_path[255];
	unsigned cur_file;
} left = {
	.wnd = NULL,
	.files = NULL,
	.cur_file = 0
};

static struct {
	WINDOW *wnd;
	struct FileList *files;
	char cur_path[255];
	unsigned cur_file;
} right = {
	.wnd = NULL,
	.files = NULL,
	.cur_file = 0,
};


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
    	if (f_cur->d_name[0] == '.' && f_cur->d_name[1] != '.')
    		continue;

    	struct File *file = (struct File *)malloc(sizeof(file));
    	strcpy(file->name, f_cur->d_name);
    	file_list = FileListAdd(file_list, file);
    }
    closedir(dir);
    return file_list;
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

	wclear(left.wnd);
	box(left.wnd, 0, 0);

	for (files = left.files; files != NULL; files = FileListNext(files)) {
		struct File *file = FileListGet(files);

		if ((count-1) == left.cur_file) {
			char out[100];

			strcpy(out, "[");
			strcat(out, file->name);
			strcat(out, "]");

			mvwprintw(left.wnd, count, 2, out);

		} else {
			mvwprintw(left.wnd, count, 2, file->name);
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

	wclear(right.wnd);
	box(right.wnd, 0, 0);

	for (files = right.files; files != NULL; files = FileListNext(files)) {
		struct File *file = FileListGet(files);

		if ((count-1) == right.cur_file) {
			char out[100];

			strcpy(out, "[");
			strcat(out, file->name);
			strcat(out, "]");

			mvwprintw(right.wnd, count, 2, out);
		} else {
			mvwprintw(right.wnd, count, 2, file->name);
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