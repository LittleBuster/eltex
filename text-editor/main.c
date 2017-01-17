#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <curses.h>

#include "cui.h"
#include "fileio.h"


int main(void)
{
	struct MainWindow mainwnd;
	struct MenuWindow menuwnd;

	unsigned symbol;
	unsigned cur_y = 0;
	unsigned cur_x = 0;
	int last_y = 1;

	initscr();
	cbreak();
	noecho();
	curs_set(1);
	keypad(stdscr, 1);
	refresh();

	MainInitSize(&mainwnd, 80, 15);
	ShowMainWindow(&mainwnd);

	MenuInitSize(&menuwnd, 80, 3, 15);
	ShowMenu(&menuwnd, "[F2]Open [F5]Save [F12]Quit");
	refresh();
	wmove(mainwnd.subwnd, 0, 0);

	for (;;) {
		symbol = wgetch(mainwnd.subwnd);
		if (isalpha(symbol)) {
			AddSym(mainwnd.subwnd, symbol); 
			if (cur_x == 0)
				last_y++;
		} else {
			switch (symbol) {
				case KEY_F(2):
					if (OpenFile(mainwnd.subwnd) != -1)
						wmove(mainwnd.subwnd, 0, 0);
						redrawwin(mainwnd.subwnd);
						wmove(mainwnd.subwnd, 0, 0);
						curs_set(1);
						break;

				case KEY_F(5):
					if (SaveFile(mainwnd.subwnd, last_y) != -1) {
						redrawwin(mainwnd.subwnd);
					}
					break;
        
        		case KEY_F(12):
        			puts("Goodbye!");
        			MainFree(&mainwnd);
    				MenuFree(&menuwnd);
    				endwin();
    				exit(0);
        			break;

        		case KEY_BACKSPACE:
        			DelSym(mainwnd.subwnd);
        			break;

        		case '\n':
        			cur_y++;
        			last_y++;
        			cur_x = 0;

        		default:
        			waddch(mainwnd.subwnd, symbol);
        	}
        }
    }
    return 0;
}
