//
// Console user interface
//

#ifndef CUI_H_
#define CUI_H_

#include <curses.h>


struct MainWindow {
	WINDOW *mainwnd;
	WINDOW *subwnd;
	unsigned width;
	unsigned height;
};


void MainInitSize(struct MainWindow *mw, unsigned width, unsigned height);

void ShowMainWindow(struct MainWindow *mw);

void MainFree(struct MainWindow *mw);


struct MenuWindow {
	WINDOW *menuwnd;
	unsigned width;
	unsigned height;
	unsigned main_height;
};


void MenuInitSize(struct MenuWindow *mw, unsigned width, unsigned height, unsigned main_height);

void ShowMenu(struct MenuWindow *mw, const char *text);

void MenuFree(struct MenuWindow *mw);


void AddSym(WINDOW *wnd, char sym);

void DelSym(WINDOW *wnd);


#endif