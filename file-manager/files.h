#ifndef FILES_H_
#define FILES_H_

#include <curses.h>
#include "filelist.h"

#define MAX_FILES 15


void SetFilesWindows(WINDOW *left_wnd, WINDOW *right_wnd);

void LeftSetCurrent(unsigned num);

void LeftFilesReadDir(const char *path);

void LeftFilesShow();

void RightSetCurrent(unsigned num);

void RightFilesReadDir(const char *path);

void RightFilesShow();


#endif