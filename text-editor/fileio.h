#ifndef FILE_IO_H_
#define FILE_IO_H_

#include <curses.h>


int OpenFile(WINDOW *text_window);

int SaveFile(WINDOW *text_window, int max_y);


#endif