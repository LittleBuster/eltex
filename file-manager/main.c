#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <curses.h>
#include "files.h"

enum Panel {
	LEFT_PANEL,
	RIGHT_PANEL
};


int main(void)
{
	unsigned sym;
	unsigned cur_panel = LEFT_PANEL;
	unsigned cur_left = 0;
	unsigned cur_right = 0;
	WINDOW *mainwnd;
	WINDOW *btnwnd;
	WINDOW *leftwnd;
	WINDOW *rightwnd;

	initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    //Init windows
    mainwnd = newwin(16, 79, 0, 0);
	wrefresh(mainwnd);

	btnwnd = newwin(3, 79, 16, 0);
	box(btnwnd, 0, 0);
	wrefresh(btnwnd);

	mvwprintw(btnwnd, 1, 1, "[F2] Open [F2] Save [F12] Exit");
	wrefresh(btnwnd);

	//Working panels
	leftwnd = derwin(mainwnd, 16, 39, 0, 0);
	box(leftwnd, 0, 0);
	wrefresh(leftwnd);

	rightwnd = derwin(mainwnd, 16, 39, 0, 40);
	box(rightwnd, 0, 0);
	wrefresh(rightwnd);

	// Reading default dirs
	SetFilesWindows(leftwnd, rightwnd);
	LeftFilesReadDir("/home/serg/");
	RightFilesReadDir("/");
	LeftFilesShow();
	RightFilesShow();

	for (;;) {
		sym = wgetch(mainwnd);

		switch(sym) {
			case '\t': {
				if (cur_panel == LEFT_PANEL)
					cur_panel = RIGHT_PANEL;
				else
					cur_panel = LEFT_PANEL;
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
	delwin(mainwnd);
	delwin(leftwnd);
	delwin(rightwnd);
	delwin(btnwnd);
	endwin();
		
    return 0;
}
