#include <iostream>
#include <stdio.h>
#include <vector>
#include <dirent.h>
#include <cstring>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string>
#include <termios.h>
#include <linux/sockios.h>
#include <linux/input.h>
#include <linux/inotify.h>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <filesystem>
#include <csignal>
#define FIONREAD	0x541B
#include <main.h>
#include <displayfiles.h>
#include <filenamehighlight.h>
#include <drawdrivesbox.h>
#include <drawfilesbox.h>
#include <drawpreviewbox.h>
#include <cleandrivesbox.h>
//#include <cleanfilesbox.h>
#include <menubar.h>
#include <drawscrollbarfordrivesbox.h>
#include <cleanscrollbarfordrivesbox.h>
#include <drawscrollbarforfilesbox.h>
#include <cleanscrollbarforfilesbox.h>
#include <getmounteddrives.h>
#include <getfiledata.h>
#include <cleanfilesbox.h>
#include <cleanpreviewbox.h>
#include <ncurses.h>
#include <form.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
FORM *form1;
FIELD *fields1[1];
int showrenamedialog() {
std::cout << "\033[?25h";
setBackgroundColor(2);
//putchar('\n');
int ch;
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	//win_body = newwin(24, 80, 0, 0);
	//assert(win_body != NULL);
	//box(win_body, 0, 0);
	//win_form = derwin(win_body, 20, 78, 3, 1);
	//assert(win_form != NULL);
	//box(win_form, 0, 0);
	//mvwprintw(win_body, 1, 2, "Press F1 to quit and F2 to print fields content");
	fields1[0] = new_field(1, 50, 11, 20, 0, 0);
	//fields[1] = new_field(1, 40, 0, 15, 0, 0);
	fields1[1] = NULL;
	//fields[2] = new_field(1, 10, 2, 0, 0, 0);
	//fields[3] = new_field(1, 40, 2, 15, 0, 0);
	//fields[4] = NULL;
	//assert(fields[0] != NULL && fields[1] != NULL);
	assert(fields1[0] != NULL);
	const char * currentname = filenamelistings[filenamelistingscount].filename.c_str();
	set_field_buffer(fields1[0], 0,currentname);
	set_field_buffer(fields1[1], 0, "val1");
	start_color();
	init_pair(3, COLOR_WHITE, COLOR_GREEN);
	set_field_back(fields1[0], COLOR_PAIR(3));
	refresh();
	//set_field_buffer(fields[2], 0, "label2");
//	set_field_buffer(fields[3], 0, "val2");
	//set_field_opts(fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
	set_field_opts(fields1[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
//	set_field_opts(fields[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
	//set_field_opts(fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
	set_field_back(fields1[0], A_UNDERLINE);
	//set_field_back(fields[3], A_UNDERLINE);
	form1 = new_form(fields1);
	assert(form1 != NULL);
//	set_form_win(form, win_form);
	//set_form_sub(form, derwin(win_form, 18, 76, 1, 1));
	post_form(form1);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE); // White text on blue background
	init_pair(2, COLOR_WHITE, COLOR_GREEN);
    // Clear the screen
    // Use the first color pair
    attron(COLOR_PAIR(2));
	mvaddch(6,10,ACS_ULCORNER);
mvaddch(7,10,ACS_VLINE);
mvaddch(8,10,ACS_VLINE);
mvaddch(9,10,ACS_VLINE);
mvaddch(10,10,ACS_VLINE);
mvaddch(11,10,ACS_VLINE);
mvaddch(12,10,ACS_VLINE);
mvaddch(13,10,ACS_VLINE);
mvaddch(14,10,ACS_VLINE);
mvaddch(15,10,ACS_VLINE);
mvaddch(6,11,ACS_HLINE);
mvaddch(6,12,ACS_HLINE);
mvaddch(6,13,ACS_HLINE);
mvaddch(6,14,ACS_HLINE);
mvaddch(6,15,ACS_HLINE);
mvaddch(6,16,ACS_HLINE);
mvaddch(6,17,ACS_HLINE);
mvaddch(6,18,ACS_HLINE);
mvaddch(6,19,ACS_HLINE);
mvaddch(6,20,ACS_HLINE);
mvaddch(6,21,ACS_HLINE);
mvaddch(6,22,ACS_HLINE);
mvaddch(6,23,ACS_HLINE);
mvaddch(6,24,ACS_HLINE);
mvaddch(6,25,ACS_HLINE);
mvaddch(6,26,ACS_HLINE);
mvaddch(6,27,ACS_HLINE);
mvaddch(6,28,ACS_HLINE);
//mvaddch(6,28," ");
mvaddch(6,29,ACS_HLINE);
mvaddch(6,30,ACS_HLINE);
mvaddch(6,31,ACS_HLINE);
mvaddch(6,32,ACS_HLINE);
mvaddch(6,33,ACS_HLINE);
mvaddch(6,34,ACS_HLINE);
mvaddch(6,35,'R');
mvaddch(6,36,'e');
mvaddch(6,37,'n');
mvaddch(6,38,'a');
mvaddch(6,39,'m');
mvaddch(6,40,'e');
mvaddch(6,41,ACS_HLINE);
mvaddch(6,42,ACS_HLINE);
mvaddch(6,43,ACS_HLINE);
mvaddch(6,44,ACS_HLINE);
mvaddch(6,45,ACS_HLINE);
mvaddch(6,46,ACS_HLINE);
mvaddch(6,47,ACS_HLINE);
mvaddch(6,48,ACS_HLINE);
//mvaddch(6,47,"?");
for (int colummn = 49;colummn < 70;colummn++) {
mvaddch(6,colummn,ACS_HLINE);
}
mvaddch(6,70,ACS_URCORNER);
mvaddch(7,70,ACS_VLINE);
mvaddch(8,70,ACS_VLINE);
mvaddch(9,70,ACS_VLINE);
mvaddch(10,70,ACS_VLINE);
mvaddch(11,70,ACS_VLINE);
mvaddch(12,70,ACS_VLINE);
mvaddch(13,70,ACS_VLINE);
mvaddch(14,70,ACS_VLINE);
mvaddch(15,70,ACS_VLINE);
mvaddch(16,10,ACS_LLCORNER);
mvaddch(16,70,ACS_LRCORNER);
for (int colummn = 49;colummn < 70;colummn++) {
mvaddch(6,colummn,ACS_HLINE);
}
for (int colummn = 11;colummn < 70;colummn++) {
mvaddch(16,colummn,ACS_HLINE);
}
mvaddch(11,15,'N');
mvaddch(11,16,'a');
mvaddch(11,17,'m');
mvaddch(11,18,'e');
mvaddch(11,19,':');
mvaddch(15,30,'C');
mvaddch(15,31,'a');
mvaddch(15,32,'n');
mvaddch(15,33,'c');
mvaddch(15,34,'e');
mvaddch(15,35,'l');
mvaddch(15,39,'O');
mvaddch(15,40,'K');
//mvaddch(19,10,'g');
attron(COLOR_PAIR(2));
for (int colummn = 11;colummn < 70;colummn++) {
mvaddch(9,colummn,' ');
}
for (int colummn = 11;colummn < 70;colummn++) {
mvaddch(8,colummn,' ');
}
for (int colummn = 11;colummn < 70;colummn++) {
mvaddch(7,colummn,' ');
}
for (int colummn = 11;colummn < 70;colummn++) {
mvaddch(10,colummn,' ');
}
for (int colummn = 11;colummn < 70;colummn++) {
//mvaddch(11,colummn,' ');
}
for (int colummn = 11;colummn < 70;colummn++) {
mvaddch(12,colummn,' ');
}
for (int colummn = 11;colummn < 70;colummn++) {
mvaddch(13,colummn,' ');
}
for (int colummn = 11;colummn < 70;colummn++) {
mvaddch(14,colummn,' ');
}
for (int colummn = 11;colummn < 30;colummn++) {
mvaddch(15,colummn,' ');
}
for (int colummn = 36;colummn < 39;colummn++) {
mvaddch(15,colummn,' ');
}
for (int colummn = 41;colummn < 70;colummn++) {
mvaddch(15,colummn,' ');
}
mvaddch(11,11,' ');
mvaddch(11,12,' ');
mvaddch(11,13,' ');
mvaddch(11,14,' ');
	refresh();
	//wrefresh(win_body);
	//wrefresh(win_form);
	//while ((ch = getch()) != KEY_F(1))
		//driver(ch);
	//unpost_form(form);
	//free_form(form);
	//free_field(fields[0]);
	//free_field(fields[1]);
	//endwin();
//std::cout << "test";
//mvprintw(5, 1, "You entered: %s", input_string.c_str());
}
