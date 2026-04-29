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
FORM *form2;
FIELD *fields2[1];
//static WINDOW *win_body, *win_form;
//char *buffer = "null";
/*
 * This is useful because ncurses fill fields blanks with spaces.
 */
static char* trim_whitespaces(char *str)
{
	char *end;

	// trim leading space
	while(isspace(*str))
		str++;

	if(*str == 0) // all spaces?
		return str;

	// trim trailing space
	end = str + strnlen(str, 128) - 1;

	while(end > str && isspace(*end))
		end--;

	// write new null terminator
	*(end+1) = '\0';

	return str;
}

static void driver(int ch)
{
	int i;
	if (ch == KEY_F(3)) {
			  char *buffer = field_buffer(fields2[1], 0);
    std::string input_string(buffer);
    //input_string = input_string.c_str();// Copy to std::string
            // Print the input string to the screen
            //mvaddch(5, 1, "You entered: %s", input_string.c_str());
            refresh();
            exit(0);
            //endwin();
            if (input_string.c_str() == "test1") {
            exit(0);}
            if (input_string == "test") {
            //mvaddch(6,1,"test");
            refresh();
            exit(0);
            }
            //putchar('\n');
            //exit(0);
            }
            if (ch == KEY_F(4)) {
            char *buffer = field_buffer(fields2[1], 0);
    std::string input_string(buffer);
    //input_string = input_string.c_str();// Copy to std::string
            // Print the input string to the screen
//            mvaddch(5, 1, "You entered: %s", input_string.c_str());
            refresh();
			  endwin();
			  std::cout << input_string;
			  if (input_string == "test1") {
            std::cout << "test1234" << std::endl;
            exit(0);
            }
			  char chara = getchar();
			  if (chara == 'j') {
			  initscr();
			  }
            //putchar('\n');
            //exit(0);
            }


	switch (ch) {
		case KEY_F(2):
			// Or the current field buffer won't be sync with what is displayed
			form_driver(form2, REQ_NEXT_FIELD);
			form_driver(form2, REQ_PREV_FIELD);
			move(LINES-3, 2);

			for (i = 0; fields2[i]; i++) {
				printw("%s", trim_whitespaces(field_buffer(fields2[i], 0)));

				if (field_opts(fields2[i]) & O_ACTIVE)
					printw("\"\t");
				else
					printw(": \"");
			}

			refresh();
			pos_form_cursor(form2);
			break;
		case KEY_DOWN:
			form_driver(form2, REQ_NEXT_FIELD);
			form_driver(form2, REQ_END_LINE);
			break;
		case KEY_UP:
			form_driver(form2, REQ_PREV_FIELD);
			form_driver(form2, REQ_END_LINE);
			break;

		case KEY_LEFT:
			form_driver(form2, REQ_PREV_CHAR);
			break;

		case KEY_RIGHT:
			form_driver(form2, REQ_NEXT_CHAR);
			break;

		// Delete the char before cursor
		case KEY_BACKSPACE:
		case 127:
			form_driver(form2, REQ_DEL_PREV);
			break;

		// Delete the char under the cursor
		case KEY_DC:
			form_driver(form2, REQ_DEL_CHAR);
			break;

		default:
		char chara = getchar();
			form_driver(form2, chara);
			break;
	}

	refresh();
}
int shownewnamedialogforcopyandmove() {
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
	fields2[0] = new_field(1, 50, 11, 20, 0, 0);
	//fields[1] = new_field(1, 40, 0, 15, 0, 0);
	fields2[1] = NULL;
	//fields[2] = new_field(1, 10, 2, 0, 0, 0);
	//fields[3] = new_field(1, 40, 2, 15, 0, 0);
	//fields[4] = NULL;
	//assert(fields[0] != NULL && fields[1] != NULL);
	assert(fields2[0] != NULL);
	set_field_buffer(fields2[0], 0, "label1");
	set_field_buffer(fields2[1], 0, "val1");
	start_color();
	init_pair(3, COLOR_WHITE, COLOR_GREEN);
	set_field_back(fields2[0], COLOR_PAIR(3));
	refresh();
	//set_field_buffer(fields[2], 0, "label2");
//	set_field_buffer(fields[3], 0, "val2");
	//set_field_opts(fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
	set_field_opts(fields2[0], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
//	set_field_opts(fields[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
	//set_field_opts(fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
	set_field_back(fields2[0], A_UNDERLINE);
	//set_field_back(fields[3], A_UNDERLINE);
	form2 = new_form(fields2);
	assert(form2 != NULL);
//	set_form_win(form, win_form);
	//set_form_sub(form, derwin(win_form, 18, 76, 1, 1));
	post_form(form2);
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
mvaddch(6,35,'N');
mvaddch(6,36,'e');
mvaddch(6,37,'w');
mvaddch(6,38,' ');
mvaddch(6,39,'n');
mvaddch(6,40,'a');
mvaddch(6,41,'m');
mvaddch(6,42,'e');
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
/*
printacharacterinanyterminallocation(6,10,"┌");
printacharacterinanyterminallocation(7,10,"│");
printacharacterinanyterminallocation(8,10,"│");
printacharacterinanyterminallocation(9,10,"│");
printacharacterinanyterminallocation(10,10,"│");
printacharacterinanyterminallocation(11,10,"│");
printacharacterinanyterminallocation(12,10,"│");
printacharacterinanyterminallocation(13,10,"│");
printacharacterinanyterminallocation(14,10,"│");
printacharacterinanyterminallocation(15,10,"│");
printacharacterinanyterminallocation(6,11,"─");
printacharacterinanyterminallocation(6,12,"─");
printacharacterinanyterminallocation(6,13,"─");
printacharacterinanyterminallocation(6,14,"─");
printacharacterinanyterminallocation(6,15,"─");
printacharacterinanyterminallocation(6,16,"─");
printacharacterinanyterminallocation(6,17,"─");
printacharacterinanyterminallocation(6,18,"─");
printacharacterinanyterminallocation(6,19,"─");
printacharacterinanyterminallocation(6,20,"─");
printacharacterinanyterminallocation(6,21,"─");
printacharacterinanyterminallocation(6,22,"─");
printacharacterinanyterminallocation(6,23,"─");
printacharacterinanyterminallocation(6,24,"─");
printacharacterinanyterminallocation(6,25,"─");
printacharacterinanyterminallocation(6,26,"─");
printacharacterinanyterminallocation(6,27,"─");
printacharacterinanyterminallocation(6,28,"─");
//printacharacterinanyterminallocation(6,28," ");
printacharacterinanyterminallocation(6,29,"─");
printacharacterinanyterminallocation(6,30,"─");
printacharacterinanyterminallocation(6,31,"─");
printacharacterinanyterminallocation(6,32,"─");
printacharacterinanyterminallocation(6,33,"─");
printacharacterinanyterminallocation(6,34,"─");
printacharacterinanyterminallocation(6,35,"N");
printacharacterinanyterminallocation(6,36,"e");
printacharacterinanyterminallocation(6,37,"w");
printacharacterinanyterminallocation(6,38," ");
printacharacterinanyterminallocation(6,39,"f");
printacharacterinanyterminallocation(6,40,"o");
printacharacterinanyterminallocation(6,41,"l");
printacharacterinanyterminallocation(6,42,"d");
printacharacterinanyterminallocation(6,43,"e");
printacharacterinanyterminallocation(6,44,"r");
printacharacterinanyterminallocation(6,45,"─");
printacharacterinanyterminallocation(6,46,"─");
printacharacterinanyterminallocation(6,47,"─");
printacharacterinanyterminallocation(6,48,"─");
//printacharacterinanyterminallocation(6,47,"?");
for (int colummn = 49;colummn < 70;colummn++) {
printacharacterinanyterminallocation(6,colummn,"─");
}
printacharacterinanyterminallocation(6,70,"┐");
printacharacterinanyterminallocation(7,70,"│");
printacharacterinanyterminallocation(8,70,"│");
printacharacterinanyterminallocation(9,70,"│");
printacharacterinanyterminallocation(10,70,"│");
printacharacterinanyterminallocation(11,70,"│");
printacharacterinanyterminallocation(12,70,"│");
printacharacterinanyterminallocation(13,70,"│");
printacharacterinanyterminallocation(14,70,"│");
printacharacterinanyterminallocation(15,70,"│");
printacharacterinanyterminallocation(16,10,"└");
printacharacterinanyterminallocation(16,70,"┘");
for (int colummn = 49;colummn < 70;colummn++) {
printacharacterinanyterminallocation(6,colummn,"─");
}
for (int colummn = 11;colummn < 70;colummn++) {
printacharacterinanyterminallocation(16,colummn,"─");
}
printacharacterinanyterminallocation(11,15,"N");
printacharacterinanyterminallocation(11,16,"a");
printacharacterinanyterminallocation(11,17,"m");
printacharacterinanyterminallocation(11,18,"e");
printacharacterinanyterminallocation(11,19,":");
printacharacterinanyterminallocation(15,30,"C");
printacharacterinanyterminallocation(15,31,"a");
printacharacterinanyterminallocation(15,32,"n");
printacharacterinanyterminallocation(15,33,"c");
printacharacterinanyterminallocation(15,34,"e");
printacharacterinanyterminallocation(15,35,"l");
printacharacterinanyterminallocation(15,39,"O");
printacharacterinanyterminallocation(15,40,"K");
putchar('\n');
*/
