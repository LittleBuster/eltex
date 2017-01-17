#include "cui.h"


static WINDOW *ShowWindow(unsigned height, unsigned width, unsigned y, unsigned x)
{
	WINDOW *wnd = NULL;

	wnd = newwin(height, width, y, x);
	box(wnd, 0, 0);
	wrefresh(wnd);

	return wnd;
}

void MainInitSize(struct MainWindow *mw, unsigned width, unsigned height)
{
	mw->width = width;
	mw->height = height;
}

void ShowMainWindow(struct MainWindow *mw)
{
	mw->mainwnd = newwin(mw->height, mw->width, 0, 0);
	mw->subwnd = subwin(mw->mainwnd, mw->height - 2, mw->width - 2, 1, 1);

	keypad(mw->subwnd, 1);
	scrollok(mw->subwnd, 1);
	idlok(mw->subwnd, 1);

	box(mw->mainwnd, 0, 0);
	wrefresh(mw->mainwnd);
}

void MainFree(struct MainWindow *mw)
{
	delwin(mw->mainwnd);
	delwin(mw->subwnd);
}

void MenuInitSize(struct MenuWindow *mw, unsigned width, unsigned height, unsigned main_height)
{
	mw->width = width;
	mw->height = height;
	mw->main_height = main_height;
}

void ShowMenu(struct MenuWindow *mw, const char *text)
{
	mw->menuwnd = ShowWindow(mw->height, mw->width, mw->main_height, 0);
	mvwprintw(mw->menuwnd, 1, 1, text);
	wrefresh(mw->menuwnd);
}

void MenuFree(struct MenuWindow *mw)
{
	delwin(mw->menuwnd);
}

void AddSym(WINDOW *wnd, char sym)
{
	char line[255];
	unsigned x;
	unsigned y;

	winnstr(wnd, line, 255);
	waddch(wnd, sym);
	getyx(wnd, y, x); 
	wprintw(wnd, "%s", line);
	wmove(wnd, y, x);
}

void DelSym(WINDOW *wnd)
{
	unsigned x;
	unsigned y;

	getyx(wnd, y, x);
	if (x != 0)
		mvwdelch(wnd, y, x - 1);
	else if (y != 0) {
		mvwdelch(wnd, y - 1, 254); 
	}
}