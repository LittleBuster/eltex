// File Manager
//
// Copyright (C) 2017 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#include <stdio.h>

#include <curses.h>

#include "files.h"


WINDOW *mainwnd = NULL;
WINDOW *btnwnd = NULL;
WINDOW *leftwnd = NULL;
WINDOW *rightwnd = NULL;
WINDOW *pwnd = NULL;
WINDOW *pwnd2 = NULL;


int main(void)
{
	unsigned sym;
	unsigned cur_panel = LEFT_PANEL;
	unsigned cur_left = 0;
	unsigned cur_right = 0;

	initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    //Init windows
    mainwnd = newwin(20, 79, 0, 0);
	wrefresh(mainwnd);

	//Working panels
	leftwnd = derwin(mainwnd, 16, 39, 3, 0);
	box(leftwnd, 0, 0);
	wrefresh(leftwnd);

	rightwnd = derwin(mainwnd, 16, 39, 3, 40);
	box(rightwnd, 0, 0);
	wrefresh(rightwnd);

	//Paths
	pwnd = derwin(mainwnd, 3, 39, 0, 0);
	box(pwnd, 0, 0);
	wrefresh(pwnd);

	pwnd2 = derwin(mainwnd, 3, 39, 0, 40);
	box(pwnd2, 0, 0);
	wrefresh(pwnd2);

	//Btn
	btnwnd = newwin(3, 79, 19, 0);
	box(btnwnd, 0, 0);
	wrefresh(btnwnd);

	mvwprintw(btnwnd, 1, 1, "[F4] Edit [F12] Exit");
	wrefresh(btnwnd);

	// Reading default dirs
	SetFilesWindows(leftwnd, rightwnd);
	LeftFilesReadDir("/home/serg/");
	RightFilesReadDir("/");

	mvwprintw(pwnd, 1, 1, "Path: /home/serg/");
	mvwprintw(pwnd2, 1, 1, "Path: /");
	wrefresh(pwnd);
	wrefresh(pwnd2);

	LeftFilesShow();
	RightFilesShow();

	for (;;) {
		sym = wgetch(mainwnd);

		switch(sym) {
			case '\t': {
				if (cur_panel == LEFT_PANEL) {
					cur_panel = RIGHT_PANEL;
				}
				else {
					cur_panel = LEFT_PANEL;
				}
				SetCurPanel(cur_panel);
				LeftFilesShow();
				RightFilesShow();
				break;
			}

			//F12
			case 52: {
				goto EXIT;
				break;
			}

			//UP
			case 65: {
				if (cur_panel == LEFT_PANEL) {
					if (cur_left != 0) {
						cur_left--;
						LeftSetCurrent(cur_left);
						LeftFilesShow();
					}
				}
				if (cur_panel == RIGHT_PANEL) {
					if (cur_right != 0) {
						cur_right--;
						RightSetCurrent(cur_right);
						RightFilesShow();
					}
				}
				break;
			}			

			//DOWN
			case 66: {
				if (cur_panel == LEFT_PANEL) {
					if (cur_left < MAX_FILES-2) {
						cur_left++;
						LeftSetCurrent(cur_left);
						LeftFilesShow();
					}
				}
				if (cur_panel == RIGHT_PANEL) {
					if (cur_right < MAX_FILES-2) {
						cur_right++;
						RightSetCurrent(cur_right);
						RightFilesShow();
					}
				}
				break;
			}
		}		
	}

EXIT:
	delwin(mainwnd);
	delwin(leftwnd);
	delwin(rightwnd);
	delwin(pwnd);
	delwin(pwnd2);
	delwin(btnwnd);
	endwin();
		
    return 0;
}