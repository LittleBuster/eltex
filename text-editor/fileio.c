#include "fileio.h"

#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


static char filename[255];


int OpenFile(WINDOW *text_window)
{
	WINDOW *wnd = NULL;
	WINDOW *subwnd = NULL;
	unsigned ch = 0;
	unsigned length = 0;
	int fd = 0;
	unsigned cur_x = 0;
	unsigned cur_y = 0;
	int err = 0;

	wnd = newwin(10, 30, 6, 15);
	subwnd = derwin(wnd, 8, 28, 1, 1);
	keypad(subwnd, 1);
	box(wnd, 0, 0);

	wrefresh(wnd);
	wrefresh(subwnd);

	mvwprintw(subwnd, 0, 0, "Filename:");
	wmove(subwnd, 1, 0);

	for (;;) {
		ch = wgetch(subwnd);
		if (ch  == '\n') {
			break;
		} else if (isalpha(ch)) {
			waddch(subwnd, ch);
			filename[length++] = ch;
		} else if (ch == KEY_BACKSPACE) {
			--length;
			mvwdelch(subwnd, 1, length);
		}
	}
	filename[length] = '\0';
	if ((fd = open(filename, O_RDWR, 0666)) == -1) {
		mvwprintw(subwnd, 0, 0, "Fail opening file!");
		mvwprintw(subwnd, 1, 0, "Press any key...");
		curs_set(0);
		err = 1;
		filename[255] = '\0';
	} else {
		char data[30000];
		int bytes_read;

		wclear(text_window);
		while ((bytes_read = read(fd, data, 30000)) > 0) {
			mvwprintw(text_window, cur_y, cur_x, "%s", data);
			cur_x = (cur_x + bytes_read) % 16;
			cur_y = (cur_y + bytes_read) / 16;
		}
		if (bytes_read == -1) { 
			err = 1;
		}
		close(fd);
	}

	if (err) {
		wgetch(subwnd);
	}
	delwin(subwnd);
	delwin(wnd);
	return -err;
}

int SaveFile(WINDOW *text_window, int max_y)
{
	WINDOW *save_window,
		   *save_subwindow;
	char line[255];
	char file_name[255];
	unsigned int ch;
	int current_line = 0;
	int fd = 0;
	int length = 0;
	int error_found = 0;
	int current_x, current_y;

	getyx(text_window, current_y, current_x);

	save_window = newwin(10, 30, 6, 15);
	save_subwindow = derwin(save_window, 8, 28, 1, 1);
	keypad(save_subwindow, 1);
	box(save_window, 0, 0);

	wrefresh(save_window);
	wrefresh(save_subwindow);

	mvwprintw(save_subwindow, 0, 0, "Write filename:");
	wmove(save_subwindow, 1, 0);
	while (1) {
		ch = wgetch(save_subwindow);
		if (ch == '\n') {
			break;
		} else if (isalpha(ch)) {
			waddch(save_subwindow, ch);
			file_name[length++] = ch;
		} else if (ch == KEY_BACKSPACE) {
			--length;
			mvwdelch(save_subwindow, 1, length);
		} else if (ch == 27) {
			error_found = 0;
			goto save_exit;
		}
	}
	file_name[length] = '\0';
	if ((fd = open(file_name, O_CREAT | O_EXCL | O_WRONLY, 0666)) == -1) {
		if ((fd = open(file_name, O_WRONLY, 0666)) == -1) {
			mvwprintw(save_subwindow, 0, 0, "Can't open the file!");
			mvwprintw(save_subwindow, 1, 0, "Press any key to continue");
			curs_set(0);
			error_found = 1;
			file_name[0] = '\0';
		}
	}
	if (!error_found) {
		for (current_line = 0; current_line < max_y; ++current_line) {
			mvwinnstr(text_window, current_line, 0, line, 79);
			if (write(fd, line, 79) == -1) { 
				mvwprintw(save_subwindow, 0, 0, "Can't write into the file!");
				mvwprintw(save_subwindow, 1, 0, "Press any key to continue");
				curs_set(0);
				error_found = 1;
			}
		}
		close(fd);
	}
	wmove(text_window, current_y, current_x);
	if (error_found) {
		wgetch(save_subwindow);
		curs_set(1);
	}
save_exit:
	delwin(save_subwindow);
	delwin(save_window);
	return -error_found; 
}