// File Manager
//
// Copyright (C) 2017 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#ifndef FILES_H_
#define FILES_H_

#include <curses.h>
#include <stdbool.h>

#include "filelist.h"

#define MAX_FILES 15


enum Panels {
	LEFT_PANEL,
	RIGHT_PANEL
};

struct Panel {
	WINDOW *wnd;
	struct FileList *files;
	char cur_path[255];
	unsigned cur_file;
};


const char *GetCurPath(unsigned panel);

unsigned GetMax(unsigned panel);

void SetCurPanel(unsigned panel);

void SetFilesWindows(WINDOW *left_wnd, WINDOW *right_wnd);

void LeftSetCurrent(unsigned num);

void LeftFilesReadDir(const char *path);

void LeftFilesShow();

void RightSetCurrent(unsigned num);

void RightFilesReadDir(const char *path);

void RightFilesShow();

bool LeftChangeExec();

bool RightChangeExec();

void AppExec(const char *filename);


#endif