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
#include <ncurses.h>
#include <form.h>
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
#include <showcopyfileanddirectorydialogs.h>
#include <showdeletefileanddirectorydialogs.h>
#include <showmovefileanddirectorydialogs.h>
#include <shownewdirectorydialog.h>
#include <showrenamedialog.h>
#include <newnameforcopyandmove.h>
int ycoordinate = 1;
int xcoordinate = 1;
int countformovingdownindrivesbox = 0; //Variable para contar las veces que se mueve el usuario hacia abajo en la caja de unidades
int countformovingdowninfilesbox = 0;
int scrolldownsindrivesbox = 0;
int scrolldownsinfilesbox = 0;
int xcoordinateformenubar = 1;
int copyorcut = 0; //0 is unset,1 is copy and 2 is cut
int fileordirectorycopyorcut = 0; //0 is unset,1 is file and 2 is directory
string filepath = "notset";
bool menubarmode = false;
bool menubarwithexitonlyoptionmode = false;
bool copyfileoverwritedialogmode = false;
bool copydirectoryoverwritedialogmode = false;
bool movefileoverwritedialogmode = false;
bool movedirectoryoverwritedialogmode = false;
bool newfolderdialogmode = false;
bool deletefiledialogmode = false;
bool deletedirectorydialogmode = false;
bool firsttimeofnewfolderdialog = false;
bool newfolderdialogmodencursesmode = false;
bool renamedialogmode = false;
bool renamedialogmodencursesmode = false;
bool newnamedialogmode = false;
bool newnamedialogmodencursesmode = false;
bool nogobackadirafteruseofnano = false;
bool writeinblankspace = true;
int xcoordinatefordeletefiledialog = 1;
int xcoordinatefordeletedirectorydialog = 1;
int xcoordinatefornewfolderdialog = 1;
int ycoordinatefornewfolderdialog = 1;
int coordinateforinputfieldinnewfolderdialog = 5;
int coordinateforcopyexistingfiledialog = 0;
int ycoordinatefornewnamedialog = 1;
int ycoordinateforcopydirectoryoverwritedialog = 0;
std::string namefieldstring = "notset";
std::string fileorfolderpathforcheckofexistenceindestination = "notset";
extern std::string isTextFile(const std::string& filename);
//&& copyfileoverwritedialogmode == false && copydirectoryoverwritedialogmode == false && movefileoverwritedialogmode == false && movedirectoryoverwritedialogmode == false && deletefiledialog == false && deletedirectorydialog == false && newfolderdialog == false
void signal_handler(int signal) {
if (menubarmode == false && copyfileoverwritedialogmode == false && copydirectoryoverwritedialogmode == false && movefileoverwritedialogmode == false && movedirectoryoverwritedialogmode == false && deletefiledialogmode == false && deletedirectorydialogmode == false && newfolderdialogmode == false) {
    copyorcut = 1;
fileorfolderpathforcheckofexistenceindestination = path;
if (!std::filesystem::is_directory(filenamelistings[filenamelistingscount].filename)) {
copyorcut = 1;
fileordirectorycopyorcut = 1;
if (path == "/" ) {
filepath = path + filenamelistings[filenamelistingscount].filename; }
else if (path != "/" ) {
filepath = path + "/" + filenamelistings[filenamelistingscount].filename; }
//std::cout << "filepath:" << filepath << std::endl;
}
else if (std::filesystem::is_directory(filenamelistings[filenamelistingscount].filename)) {
copyorcut = 1;
fileordirectorycopyorcut = 2;
if (path == "/" ) {
filepath = path + filenamelistings[filenamelistingscount].filename; }
else if (path != "/" ) {
filepath = path + "/" + filenamelistings[filenamelistingscount].filename; }
//std::cout << "filepath:" << filepath << std::endl;
}
}
}
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
int keypressdetection() {
struct sigaction action;
    std::memset(&action, 0, sizeof(action)); // Clear the struct

    action.sa_handler = signal_handler; // Set the signal handler
    sigemptyset(&action.sa_mask); // Initialize the signal mask to empty
    action.sa_flags = 0; // No special flags

    // Register the signal handler for SIGINT
    sigaction(SIGINT, &action, nullptr);
    //sigaction(SIGQUIT, &action, nullptr);
vector<char> characters;
system("stty -icanon -echo");
//tuidraw();
putchar('\n');
while (true) {
/*
if (selectionx == 3 & filemenu == true) {
setBackgroundColor(3);
printacharacterinanyterminallocation(3,3,"o");
printacharacterinanyterminallocation(3,4,"n");
printacharacterinanyterminallocation(3,5,"e");
resetColors();
}
if (selectionx == 4 & filemenu == true) {
printacharacterinanyterminallocation(3,3,"o");
printacharacterinanyterminallocation(3,4,"n");
printacharacterinanyterminallocation(3,5,"e");
setBackgroundColor(3);
}
*/
int byteswaiting;
//system("stty -icanon -echo");
//system("stty sane");
if (newfolderdialogmodencursesmode == false && renamedialogmodencursesmode == false && newnamedialogmodencursesmode == false) {
ioctl(0, FIONREAD, &byteswaiting);
}
else if (newfolderdialogmodencursesmode == true) {
int ch = getch();
//std::cout << ch;
if (ch == KEY_DOWN) {
			form_driver(form, REQ_PREV_FIELD);
			form_driver(form, REQ_END_LINE);
			def_prog_mode();
			endwin();
			newfolderdialogmodencursesmode = false;
			std::cout << "\033[?25l";
			setBackgroundColor(2);
			printacharacterinanyterminallocation(7,11,"┌");
printacharacterinanyterminallocation(8,11,"│");
printacharacterinanyterminallocation(9,11,"│");
printacharacterinanyterminallocation(10,11,"│");
printacharacterinanyterminallocation(11,11,"│");
printacharacterinanyterminallocation(12,11,"│");
printacharacterinanyterminallocation(13,11,"│");
printacharacterinanyterminallocation(14,11,"│");
printacharacterinanyterminallocation(15,11,"│");
printacharacterinanyterminallocation(16,11,"│");
printacharacterinanyterminallocation(7,12,"─");
printacharacterinanyterminallocation(7,13,"─");
printacharacterinanyterminallocation(7,14,"─");
printacharacterinanyterminallocation(7,15,"─");
printacharacterinanyterminallocation(7,16,"─");
printacharacterinanyterminallocation(7,17,"─");
printacharacterinanyterminallocation(7,18,"─");
printacharacterinanyterminallocation(7,19,"─");
printacharacterinanyterminallocation(7,20,"─");
printacharacterinanyterminallocation(7,21,"─");
printacharacterinanyterminallocation(7,22,"─");
printacharacterinanyterminallocation(7,23,"─");
printacharacterinanyterminallocation(7,24,"─");
printacharacterinanyterminallocation(7,25,"─");
printacharacterinanyterminallocation(7,26,"─");
printacharacterinanyterminallocation(7,27,"─");
printacharacterinanyterminallocation(7,28,"─");
printacharacterinanyterminallocation(7,29,"─");
//printacharacterinanyterminallocation(6,28," ");
printacharacterinanyterminallocation(7,30,"─");
printacharacterinanyterminallocation(7,31,"─");
printacharacterinanyterminallocation(7,32,"─");
printacharacterinanyterminallocation(7,33,"─");
printacharacterinanyterminallocation(7,34,"─");
printacharacterinanyterminallocation(7,35,"─");
printacharacterinanyterminallocation(7,36,"N");
printacharacterinanyterminallocation(7,37,"e");
printacharacterinanyterminallocation(7,38,"w");
printacharacterinanyterminallocation(7,39," ");
printacharacterinanyterminallocation(7,40,"f");
printacharacterinanyterminallocation(7,41,"o");
printacharacterinanyterminallocation(7,42,"l");
printacharacterinanyterminallocation(7,43,"d");
printacharacterinanyterminallocation(7,44,"e");
printacharacterinanyterminallocation(7,45,"r");
printacharacterinanyterminallocation(7,46,"─");
printacharacterinanyterminallocation(7,47,"─");
printacharacterinanyterminallocation(7,48,"─");
//printacharacterinanyterminallocation(7,49,"─");
//printacharacterinanyterminallocation(6,47,"?");
for (int colummn = 49;colummn < 71;colummn++) {
printacharacterinanyterminallocation(7,colummn,"─");
}
printacharacterinanyterminallocation(7,71,"┐");
printacharacterinanyterminallocation(8,71,"│");
printacharacterinanyterminallocation(9,71,"│");
printacharacterinanyterminallocation(10,71,"│");
printacharacterinanyterminallocation(11,71,"│");
printacharacterinanyterminallocation(12,71,"│");
printacharacterinanyterminallocation(13,71,"│");
printacharacterinanyterminallocation(14,71,"│");
printacharacterinanyterminallocation(15,71,"│");
printacharacterinanyterminallocation(16,71,"│");
printacharacterinanyterminallocation(17,71,"└");
printacharacterinanyterminallocation(17,71,"┘");
for (int colummn = 49;colummn < 71;colummn++) {
//printacharacterinanyterminallocation(6,colummn,"─");
}
for (int colummn = 11;colummn < 71;colummn++) {
printacharacterinanyterminallocation(17,colummn,"─");
}
printacharacterinanyterminallocation(12,12," ");
printacharacterinanyterminallocation(12,13," ");
printacharacterinanyterminallocation(12,14," ");
printacharacterinanyterminallocation(12,15," ");
printacharacterinanyterminallocation(12,16,"N");
printacharacterinanyterminallocation(12,17,"a");
printacharacterinanyterminallocation(12,18,"m");
printacharacterinanyterminallocation(12,19,"e");
printacharacterinanyterminallocation(12,20,":");
printacharacterinanyterminallocation(16,31,"C");
printacharacterinanyterminallocation(16,32,"a");
printacharacterinanyterminallocation(16,33,"n");
printacharacterinanyterminallocation(16,34,"c");
printacharacterinanyterminallocation(16,35,"e");
printacharacterinanyterminallocation(16,36,"l");
printacharacterinanyterminallocation(16,37," ");
printacharacterinanyterminallocation(16,38," ");
printacharacterinanyterminallocation(16,39," ");
printacharacterinanyterminallocation(16,40,"O");
printacharacterinanyterminallocation(16,41,"K");
printacharacterinanyterminallocation(17,11,"└");
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(8,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(9,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(10,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(11,colummn," ");
}
for (int colummn = 11;colummn < 70;colummn++) {
//printacharacterinanyterminallocation(11,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(13,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(14,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(15,colummn," ");
}
for (int colummn = 11;colummn < 31;colummn++) {
printacharacterinanyterminallocation(16,colummn," ");
}
for (int colummn = 36;colummn < 39;colummn++) {
//printacharacterinanyterminallocation(1,colummn," ");
}
for (int colummn = 42;colummn < 71;colummn++) {
printacharacterinanyterminallocation(16,colummn," ");
}
movecursortoanyterminallocation(12,21);
char *buffer = field_buffer(fields[0], 0);
trim_whitespaces(buffer);
std::string input_string(buffer);
//std::cout << "\033[4" << std::endl;
//std::cout << input_string.substr(0, 62) << std::endl;
//std::cout << "\033[24m";
resetColors();
std::string truncated_string = input_string.substr(0, 50);
    // Print the underlined truncated string
    std::cout << "\033[4m" << truncated_string << "\033[24m" << std::endl; // Underline the text
//getchar();
ycoordinatefornewfolderdialog = 1;
setBackgroundColor(3);
printacharacterinanyterminallocation(16,31,"C");
printacharacterinanyterminallocation(16,32,"a");
printacharacterinanyterminallocation(16,33,"n");
printacharacterinanyterminallocation(16,34,"c");
printacharacterinanyterminallocation(16,35,"e");
printacharacterinanyterminallocation(16,36,"l");
setBackgroundColor(2);
printacharacterinanyterminallocation(16,37," ");
printacharacterinanyterminallocation(16,38," ");
printacharacterinanyterminallocation(16,39," ");
printacharacterinanyterminallocation(16,40,"O");
printacharacterinanyterminallocation(16,41,"K");
printacharacterinanyterminallocation(16,11,"│");
putchar('\n');
ioctl(0,FIONREAD,&byteswaiting);
			}
			else if (ch == KEY_UP) {
			}
			else if (ch == KEY_DOWN) {
			initscr();
			newfolderdialogmodencursesmode = true;
			}
			else if (ch == KEY_LEFT) {
			form_driver(form, REQ_PREV_CHAR);
			}
			else if (ch == KEY_RIGHT) {
			form_driver(form, REQ_NEXT_CHAR);
			}
			else if (ch == KEY_BACKSPACE) {
			form_driver(form, REQ_DEL_PREV);
			}
			else if (ch == KEY_DC) {
			form_driver(form, REQ_DEL_CHAR);
			}
			else if (ch == KEY_F(5)) {
			form_driver(form, REQ_PREV_FIELD);
			form_driver(form, REQ_END_LINE);
			//form_driver(form, REQ_PREV_FIELD);
			//form_driver(form, REQ_END_LINE);
			char *buffer = field_buffer(fields[0], 0);
			//std::cout << buffer;
			//endwin();
			}
			else {
form_driver(form,ch);
}
}
else if (newnamedialogmodencursesmode == true) {
int ch = getch();
//std::cout << ch;
if (ch == KEY_DOWN) {
			form_driver(form2, REQ_PREV_FIELD);
			form_driver(form2, REQ_END_LINE);
			def_prog_mode();
			endwin();
			newnamedialogmodencursesmode = false;
			std::cout << "\033[?25l";
			setBackgroundColor(2);
			printacharacterinanyterminallocation(7,11,"┌");
printacharacterinanyterminallocation(8,11,"│");
printacharacterinanyterminallocation(9,11,"│");
printacharacterinanyterminallocation(10,11,"│");
printacharacterinanyterminallocation(11,11,"│");
printacharacterinanyterminallocation(12,11,"│");
printacharacterinanyterminallocation(13,11,"│");
printacharacterinanyterminallocation(14,11,"│");
printacharacterinanyterminallocation(15,11,"│");
printacharacterinanyterminallocation(16,11,"│");
printacharacterinanyterminallocation(7,12,"─");
printacharacterinanyterminallocation(7,13,"─");
printacharacterinanyterminallocation(7,14,"─");
printacharacterinanyterminallocation(7,15,"─");
printacharacterinanyterminallocation(7,16,"─");
printacharacterinanyterminallocation(7,17,"─");
printacharacterinanyterminallocation(7,18,"─");
printacharacterinanyterminallocation(7,19,"─");
printacharacterinanyterminallocation(7,20,"─");
printacharacterinanyterminallocation(7,21,"─");
printacharacterinanyterminallocation(7,22,"─");
printacharacterinanyterminallocation(7,23,"─");
printacharacterinanyterminallocation(7,24,"─");
printacharacterinanyterminallocation(7,25,"─");
printacharacterinanyterminallocation(7,26,"─");
printacharacterinanyterminallocation(7,27,"─");
printacharacterinanyterminallocation(7,28,"─");
printacharacterinanyterminallocation(7,29,"─");
//printacharacterinanyterminallocation(6,28," ");
printacharacterinanyterminallocation(7,30,"─");
printacharacterinanyterminallocation(7,31,"─");
printacharacterinanyterminallocation(7,32,"─");
printacharacterinanyterminallocation(7,33,"─");
printacharacterinanyterminallocation(7,34,"─");
printacharacterinanyterminallocation(7,35,"─");
printacharacterinanyterminallocation(7,36,"N");
printacharacterinanyterminallocation(7,37,"e");
printacharacterinanyterminallocation(7,38,"w");
printacharacterinanyterminallocation(7,39," ");
printacharacterinanyterminallocation(7,40,"n");
printacharacterinanyterminallocation(7,41,"a");
printacharacterinanyterminallocation(7,42,"m");
printacharacterinanyterminallocation(7,43,"e");
printacharacterinanyterminallocation(7,44,"─");
printacharacterinanyterminallocation(7,45,"─");
printacharacterinanyterminallocation(7,46,"─");
printacharacterinanyterminallocation(7,47,"─");
printacharacterinanyterminallocation(7,48,"─");
//printacharacterinanyterminallocation(7,49,"─");
//printacharacterinanyterminallocation(6,47,"?");
for (int colummn = 49;colummn < 71;colummn++) {
printacharacterinanyterminallocation(7,colummn,"─");
}
printacharacterinanyterminallocation(7,71,"┐");
printacharacterinanyterminallocation(8,71,"│");
printacharacterinanyterminallocation(9,71,"│");
printacharacterinanyterminallocation(10,71,"│");
printacharacterinanyterminallocation(11,71,"│");
printacharacterinanyterminallocation(12,71,"│");
printacharacterinanyterminallocation(13,71,"│");
printacharacterinanyterminallocation(14,71,"│");
printacharacterinanyterminallocation(15,71,"│");
printacharacterinanyterminallocation(16,71,"│");
printacharacterinanyterminallocation(17,71,"└");
printacharacterinanyterminallocation(17,71,"┘");
for (int colummn = 49;colummn < 71;colummn++) {
//printacharacterinanyterminallocation(6,colummn,"─");
}
for (int colummn = 11;colummn < 71;colummn++) {
printacharacterinanyterminallocation(17,colummn,"─");
}
printacharacterinanyterminallocation(12,12," ");
printacharacterinanyterminallocation(12,13," ");
printacharacterinanyterminallocation(12,14," ");
printacharacterinanyterminallocation(12,15," ");
printacharacterinanyterminallocation(12,16,"N");
printacharacterinanyterminallocation(12,17,"a");
printacharacterinanyterminallocation(12,18,"m");
printacharacterinanyterminallocation(12,19,"e");
printacharacterinanyterminallocation(12,20,":");
printacharacterinanyterminallocation(16,31,"C");
printacharacterinanyterminallocation(16,32,"a");
printacharacterinanyterminallocation(16,33,"n");
printacharacterinanyterminallocation(16,34,"c");
printacharacterinanyterminallocation(16,35,"e");
printacharacterinanyterminallocation(16,36,"l");
printacharacterinanyterminallocation(16,37," ");
printacharacterinanyterminallocation(16,38," ");
printacharacterinanyterminallocation(16,39," ");
printacharacterinanyterminallocation(16,40,"O");
printacharacterinanyterminallocation(16,41,"K");
printacharacterinanyterminallocation(17,11,"└");
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(8,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(9,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(10,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(11,colummn," ");
}
for (int colummn = 11;colummn < 70;colummn++) {
//printacharacterinanyterminallocation(11,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(13,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(14,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(15,colummn," ");
}
for (int colummn = 11;colummn < 31;colummn++) {
printacharacterinanyterminallocation(16,colummn," ");
}
for (int colummn = 36;colummn < 39;colummn++) {
//printacharacterinanyterminallocation(1,colummn," ");
}
for (int colummn = 42;colummn < 71;colummn++) {
printacharacterinanyterminallocation(16,colummn," ");
}
movecursortoanyterminallocation(12,21);
char *buffer = field_buffer(fields2[0], 0);
trim_whitespaces(buffer);
std::string input_string(buffer);
//std::cout << "\033[4" << std::endl;
//std::cout << input_string.substr(0, 62) << std::endl;
//std::cout << "\033[24m";
resetColors();
std::string truncated_string = input_string.substr(0, 50);
    // Print the underlined truncated string
    std::cout << "\033[4m" << truncated_string << "\033[24m" << std::endl; // Underline the text
//getchar();
ycoordinatefornewfolderdialog = 1;
setBackgroundColor(3);
printacharacterinanyterminallocation(16,31,"C");
printacharacterinanyterminallocation(16,32,"a");
printacharacterinanyterminallocation(16,33,"n");
printacharacterinanyterminallocation(16,34,"c");
printacharacterinanyterminallocation(16,35,"e");
printacharacterinanyterminallocation(16,36,"l");
setBackgroundColor(2);
printacharacterinanyterminallocation(16,37," ");
printacharacterinanyterminallocation(16,38," ");
printacharacterinanyterminallocation(16,39," ");
printacharacterinanyterminallocation(16,40,"O");
printacharacterinanyterminallocation(16,41,"K");
printacharacterinanyterminallocation(16,11,"│");
putchar('\n');
//ioctl(0,FIONREAD,&byteswaiting);
			}
			else if (ch == KEY_UP) {
			}
			else if (ch == KEY_DOWN) {
			initscr();
			newfolderdialogmodencursesmode = true;
			}
			else if (ch == KEY_LEFT) {
			form_driver(form2, REQ_PREV_CHAR);
			}
			else if (ch == KEY_RIGHT) {
			form_driver(form2, REQ_NEXT_CHAR);
			}
			else if (ch == KEY_BACKSPACE) {
			form_driver(form2, REQ_DEL_PREV);
			}
			else if (ch == KEY_DC) {
			form_driver(form2, REQ_DEL_CHAR);
			}
			else if (ch == KEY_F(5)) {
			form_driver(form2, REQ_PREV_FIELD);
			form_driver(form2, REQ_END_LINE);
			//form_driver(form, REQ_PREV_FIELD);
			//form_driver(form, REQ_END_LINE);
			char *buffer = field_buffer(fields2[0], 0);
			//std::cout << buffer;
			//endwin();
			}
			else {
form_driver(form2,ch);
}
}
else if (renamedialogmodencursesmode == true) {
int ch = getch();
//std::cout << ch;
if (ch == KEY_DOWN) {
			form_driver(form1, REQ_PREV_FIELD);
			form_driver(form1, REQ_END_LINE);
			def_prog_mode();
			endwin();
			renamedialogmodencursesmode = false;
			std::cout << "\033[?25l";
			setBackgroundColor(2);
			printacharacterinanyterminallocation(7,11,"┌");
printacharacterinanyterminallocation(8,11,"│");
printacharacterinanyterminallocation(9,11,"│");
printacharacterinanyterminallocation(10,11,"│");
printacharacterinanyterminallocation(11,11,"│");
printacharacterinanyterminallocation(12,11,"│");
printacharacterinanyterminallocation(13,11,"│");
printacharacterinanyterminallocation(14,11,"│");
printacharacterinanyterminallocation(15,11,"│");
printacharacterinanyterminallocation(16,11,"│");
printacharacterinanyterminallocation(7,12,"─");
printacharacterinanyterminallocation(7,13,"─");
printacharacterinanyterminallocation(7,14,"─");
printacharacterinanyterminallocation(7,15,"─");
printacharacterinanyterminallocation(7,16,"─");
printacharacterinanyterminallocation(7,17,"─");
printacharacterinanyterminallocation(7,18,"─");
printacharacterinanyterminallocation(7,19,"─");
printacharacterinanyterminallocation(7,20,"─");
printacharacterinanyterminallocation(7,21,"─");
printacharacterinanyterminallocation(7,22,"─");
printacharacterinanyterminallocation(7,23,"─");
printacharacterinanyterminallocation(7,24,"─");
printacharacterinanyterminallocation(7,25,"─");
printacharacterinanyterminallocation(7,26,"─");
printacharacterinanyterminallocation(7,27,"─");
printacharacterinanyterminallocation(7,28,"─");
printacharacterinanyterminallocation(7,29,"─");
//printacharacterinanyterminallocation(6,28," ");
printacharacterinanyterminallocation(7,30,"─");
printacharacterinanyterminallocation(7,31,"─");
printacharacterinanyterminallocation(7,32,"─");
printacharacterinanyterminallocation(7,33,"─");
printacharacterinanyterminallocation(7,34,"─");
printacharacterinanyterminallocation(7,35,"─");
printacharacterinanyterminallocation(7,36,"R");
printacharacterinanyterminallocation(7,37,"e");
printacharacterinanyterminallocation(7,38,"n");
printacharacterinanyterminallocation(7,39,"a");
printacharacterinanyterminallocation(7,40,"m");
printacharacterinanyterminallocation(7,41,"e");
printacharacterinanyterminallocation(7,42,"─");
printacharacterinanyterminallocation(7,43,"─");
printacharacterinanyterminallocation(7,44,"─");
printacharacterinanyterminallocation(7,45,"─");
printacharacterinanyterminallocation(7,46,"─");
printacharacterinanyterminallocation(7,47,"─");
printacharacterinanyterminallocation(7,48,"─");
//printacharacterinanyterminallocation(7,49,"─");
//printacharacterinanyterminallocation(6,47,"?");
for (int colummn = 49;colummn < 71;colummn++) {
printacharacterinanyterminallocation(7,colummn,"─");
}
printacharacterinanyterminallocation(7,71,"┐");
printacharacterinanyterminallocation(8,71,"│");
printacharacterinanyterminallocation(9,71,"│");
printacharacterinanyterminallocation(10,71,"│");
printacharacterinanyterminallocation(11,71,"│");
printacharacterinanyterminallocation(12,71,"│");
printacharacterinanyterminallocation(13,71,"│");
printacharacterinanyterminallocation(14,71,"│");
printacharacterinanyterminallocation(15,71,"│");
printacharacterinanyterminallocation(16,71,"│");
printacharacterinanyterminallocation(17,71,"└");
printacharacterinanyterminallocation(17,71,"┘");
for (int colummn = 49;colummn < 71;colummn++) {
//printacharacterinanyterminallocation(6,colummn,"─");
}
for (int colummn = 11;colummn < 71;colummn++) {
printacharacterinanyterminallocation(17,colummn,"─");
}
printacharacterinanyterminallocation(12,12," ");
printacharacterinanyterminallocation(12,13," ");
printacharacterinanyterminallocation(12,14," ");
printacharacterinanyterminallocation(12,15," ");
printacharacterinanyterminallocation(12,16,"N");
printacharacterinanyterminallocation(12,17,"a");
printacharacterinanyterminallocation(12,18,"m");
printacharacterinanyterminallocation(12,19,"e");
printacharacterinanyterminallocation(12,20,":");
printacharacterinanyterminallocation(16,31,"C");
printacharacterinanyterminallocation(16,32,"a");
printacharacterinanyterminallocation(16,33,"n");
printacharacterinanyterminallocation(16,34,"c");
printacharacterinanyterminallocation(16,35,"e");
printacharacterinanyterminallocation(16,36,"l");
printacharacterinanyterminallocation(16,37," ");
printacharacterinanyterminallocation(16,38," ");
printacharacterinanyterminallocation(16,39," ");
printacharacterinanyterminallocation(16,40,"O");
printacharacterinanyterminallocation(16,41,"K");
printacharacterinanyterminallocation(17,11,"└");
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(8,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(9,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(10,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(11,colummn," ");
}
for (int colummn = 11;colummn < 70;colummn++) {
//printacharacterinanyterminallocation(11,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(13,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(14,colummn," ");
}
for (int colummn = 12;colummn < 71;colummn++) {
printacharacterinanyterminallocation(15,colummn," ");
}
for (int colummn = 11;colummn < 31;colummn++) {
printacharacterinanyterminallocation(16,colummn," ");
}
for (int colummn = 36;colummn < 39;colummn++) {
//printacharacterinanyterminallocation(1,colummn," ");
}
for (int colummn = 42;colummn < 71;colummn++) {
printacharacterinanyterminallocation(16,colummn," ");
}
movecursortoanyterminallocation(12,21);
char *buffer = field_buffer(fields1[0], 0);
trim_whitespaces(buffer);
std::string input_string(buffer);
//std::cout << "\033[4" << std::endl;
//std::cout << input_string.substr(0, 62) << std::endl;
//std::cout << "\033[24m";
resetColors();
std::string truncated_string = input_string.substr(0, 50);
    // Print the underlined truncated string
    std::cout << "\033[4m" << truncated_string << "\033[24m" << std::endl; // Underline the text
//getchar();
ycoordinatefornewfolderdialog = 1;
setBackgroundColor(3);
printacharacterinanyterminallocation(16,31,"C");
printacharacterinanyterminallocation(16,32,"a");
printacharacterinanyterminallocation(16,33,"n");
printacharacterinanyterminallocation(16,34,"c");
printacharacterinanyterminallocation(16,35,"e");
printacharacterinanyterminallocation(16,36,"l");
setBackgroundColor(2);
printacharacterinanyterminallocation(16,37," ");
printacharacterinanyterminallocation(16,38," ");
printacharacterinanyterminallocation(16,39," ");
printacharacterinanyterminallocation(16,40,"O");
printacharacterinanyterminallocation(16,41,"K");
printacharacterinanyterminallocation(16,11,"│");
putchar('\n');
ioctl(0,FIONREAD,&byteswaiting);
			}
			else if (ch == KEY_UP) {
			}
			else if (ch == KEY_DOWN) {
			initscr();
			renamedialogmodencursesmode = true;
			}
			else if (ch == KEY_LEFT) {
			form_driver(form1, REQ_PREV_CHAR);
			}
			else if (ch == KEY_RIGHT) {
			form_driver(form1, REQ_NEXT_CHAR);
			}
			else if (ch == KEY_BACKSPACE) {
			form_driver(form1, REQ_DEL_PREV);
			}
			else if (ch == KEY_DC) {
			form_driver(form1, REQ_DEL_CHAR);
			}
			else if (ch == KEY_F(5)) {
			form_driver(form1, REQ_PREV_FIELD);
			form_driver(form1, REQ_END_LINE);
			//form_driver(form, REQ_PREV_FIELD);
			//form_driver(form, REQ_END_LINE);
			char *buffer = field_buffer(fields[0], 0);
			//std::cout << buffer;
			//endwin();
			}
			else {
form_driver(form1,ch);
}
}
if (byteswaiting != 0) {
//std::cout << "byteswaiting:" << byteswaiting << std::endl;
//std::cout << "\033[4munderlined\033[24m";
}
if (byteswaiting == 1 && newfolderdialogmodencursesmode == false && renamedialogmodencursesmode == false && newnamedialogmodencursesmode == false) {
//char chinncursesformat = getch();
char ch = getchar();
ungetc(ch, stdin);
int chint = getchar();
//if (newfolderdialogmode == true && chint != 127 && ch != 'a' && ch != 'd' && ch != 'b') {
//printacharacterinanyterminallocation(2,4,"X");
//ungetc(ch,stdin);
//form_driver(form, getch());
//ch = getch();
//form_driver(form,chinncursesformat);
//}
std::ofstream archivo;
archivo.open("/home/jesus/Documents/codigo.txt");
archivo << ch;
//archivo << chint;
archivo.close();
//std::cout << "chint:" << chint;
//std::cout << "characteraschar:" << ch << std::endl;
if (ch == 'q') {
resetColors();
std::cout << "\033[2J";
std::cout << "\033[?1049l";
struct termios tty;
tcgetattr(STDIN_FILENO, &tty);
tty.c_lflag |= (ICANON | ECHO);
tcsetattr(STDIN_FILENO, TCSANOW, &tty);
std::cout << "\033[?25h";
return 0;
}
if (ch == 'b') {
movecursortoanyterminallocation(12,12);
std::cout << "namestring:" << namefieldstring << std::endl;
std::cout << "coordinateforinputfieldinnewfolderdialog:" << coordinateforinputfieldinnewfolderdialog << std::endl;
std::cout << "ycoordinatefornewfolderdialog:" << ycoordinatefornewfolderdialog << std::endl;
std::cout << "namefieldstringsize:" << namefieldstring.size() << std::endl;
}
if (ch == 'l') {
std::cout << "\033[?25l";
}
if (ch == 'h') {
std::cout << "\033[?25h";
movecursortoanyterminallocation(11,1);
//putchar('\n');
}
if (ch == 'n') {
//newfolderdialogmode = true;
//newfolderdialogmodencursesmode = true;
//shownewdirectorydialog();
//copyfileoverwritedialogmode = true;
//showcopyfileoverwritedialog();
//system("/bin/bash");
std::cout << "path:" << path << std::endl;
getchar();}
if (chint == 22) {
if (menubarmode == false && copyfileoverwritedialogmode == false && copydirectoryoverwritedialogmode == false && movefileoverwritedialogmode == false && movedirectoryoverwritedialogmode == false && deletefiledialogmode == false && deletedirectorydialogmode == false && newfolderdialogmode == false) {
std::cout << "Ctrl+V" << std::endl;
if (copyorcut == 1 && fileordirectorycopyorcut == 1) {
const auto copyOptions = filesystem::copy_options::recursive;
//std::filesystem::copy(filepath,path,copyOptions);
std::size_t found = filepath.find_last_of("/");
  //std::cout << " path: " << str.substr(0,found) << '\n';
  bool fileexists = false;
  for (int vectoritem = filenamelistings.size();vectoritem != 0,vectoritem--;) {
  if (filenamelistings[vectoritem].filename == filepath.substr(found+1)) {
  fileexists = true;
  }
  }
  if (fileexists == true) {
  //std::cout << "Folder already exists.Do you want to merge and overwrite?" << std::endl;
  //std::cout << "Y merges and overwrites,M just merges without overwrite and N cancels the operation altogether" << std::endl;
  //char answer = getchar();
  //if (answer == 'Y') {
  //const auto copyOptions = std::filesystem::copy_options::recursive |
  //std::filesystem::copy_options::overwrite_existing;
//std::filesystem::copy(filepath,path,copyOptions);
  //}
  //if (answer == 'M') {
  //const auto copyOptions = std::filesystem::copy_options::recursive |
  //std::filesystem::copy_options::skip_existing;
//std::filesystem::copy(filepath,path,copyOptions);
  //}
  //if (answer == 'N') {
  //std::cout << "The operation has been canceled";
  //}
  copyfileoverwritedialogmode = true;
  showcopyfileoverwritedialog();
}
else if (fileexists == false) {
const auto copyOptions = std::filesystem::copy_options::recursive |
  std::filesystem::copy_options::overwrite_existing;
std::filesystem::copy(filepath,path,copyOptions);
 }
}
else if (copyorcut == 1 && fileordirectorycopyorcut == 2) {
const auto copyOptions = filesystem::copy_options::recursive;
//std::filesystem::copy(filepath,path,copyOptions);
std::size_t found = filepath.find_last_of("/");
  //std::cout << " path: " << str.substr(0,found) << '\n';
  bool folderexists = false;
  for (int vectoritem = filenamelistings.size();vectoritem != 0,vectoritem--;) {
  if (filenamelistings[vectoritem].filename == filepath.substr(found+1)) {
  folderexists = true;
  }
  }
  if (folderexists == true) {
  //std::cout << "Folder already exists.Do you want to merge and overwrite?" << std::endl;
  //std::cout << "Y merges and overwrites,M just merges without overwrite and N cancels the operation altogether" << std::endl;
  //char answer = getchar();
  //if (answer == 'Y') {
  //const auto copyOptions = std::filesystem::copy_options::recursive |
  //std::filesystem::copy_options::overwrite_existing;
//std::filesystem::copy(filepath,path,copyOptions);
  //}
  //if (answer == 'M') {
  //const auto copyOptions = std::filesystem::copy_options::recursive |
  //std::filesystem::copy_options::skip_existing;
//std::filesystem::copy(filepath,path,copyOptions);
  //}
  //if (answer == 'N') {
  //std::cout << "The operation has been canceled";
  //}
  copydirectoryoverwritedialogmode = true;
  showcopydirectoryoverwritedialog();
}
else if (folderexists == false) {
const auto copyOptions = std::filesystem::copy_options::recursive |
  std::filesystem::copy_options::overwrite_existing;
std::filesystem::copy(filepath,path,copyOptions);
 }
}
else if (copyorcut == 2 && fileordirectorycopyorcut == 1) {
const auto copyOptions = filesystem::copy_options::recursive;
//std::filesystem::copy(filepath,path,copyOptions);
std::size_t found = filepath.find_last_of("/");
  //std::cout << " path: " << str.substr(0,found) << '\n';
  bool fileexists = false;
  for (int vectoritem = filenamelistings.size();vectoritem != 0,vectoritem--;) {
  if (filenamelistings[vectoritem].filename == filepath.substr(found+1)) {
  fileexists = true;
  }
  }
  if (fileexists == true) {
  //std::cout << "Folder already exists.Do you want to merge and overwrite?" << std::endl;
  //std::cout << "Y merges and overwrites,M just merges without overwrite and N cancels the operation altogether" << std::endl;
  //char answer = getchar();
  //if (answer == 'Y') {
  //const auto copyOptions = std::filesystem::copy_options::recursive |
  //std::filesystem::copy_options::overwrite_existing;
//std::filesystem::copy(filepath,path,copyOptions);
  //}
  //if (answer == 'M') {
  //const auto copyOptions = std::filesystem::copy_options::recursive |
  //std::filesystem::copy_options::skip_existing;
//std::filesystem::copy(filepath,path,copyOptions);
  //}
  //if (answer == 'N') {
  //std::cout << "The operation has been canceled";
  //}
  copydirectoryoverwritedialogmode = true;
  showcopydirectoryoverwritedialog();
}
else if (fileexists == false) {
const auto copyOptions = std::filesystem::copy_options::recursive |
  std::filesystem::copy_options::overwrite_existing;
std::filesystem::copy(filepath,path,copyOptions);
 }
}
else if (copyorcut == 2 && fileordirectorycopyorcut == 2) {
const auto copyOptions = filesystem::copy_options::recursive;
//std::filesystem::copy(filepath,path,copyOptions);
std::size_t found = filepath.find_last_of("/");
  //std::cout << " path: " << str.substr(0,found) << '\n';
  bool folderexists = false;
  for (int vectoritem = filenamelistings.size();vectoritem != 0,vectoritem--;) {
  if (filenamelistings[vectoritem].filename == filepath.substr(found+1)) {
  folderexists = true;
  }
  }
  if (folderexists == true) {
  //std::cout << "Folder already exists.Do you want to merge and overwrite?" << std::endl;
  //std::cout << "Y merges and overwrites,M just merges without overwrite and N cancels the operation altogether" << std::endl;
  //char answer = getchar();
  //if (answer == 'Y') {
  //const auto copyOptions = std::filesystem::copy_options::recursive |
  //std::filesystem::copy_options::overwrite_existing;
//std::filesystem::copy(filepath,path,copyOptions);
  //}
  //if (answer == 'M') {
  //const auto copyOptions = std::filesystem::copy_options::recursive |
  //std::filesystem::copy_options::skip_existing;
//std::filesystem::copy(filepath,path,copyOptions);
  //}
  //if (answer == 'N') {
  //std::cout << "The operation has been canceled";
  //}
  copydirectoryoverwritedialogmode = true;
  showcopydirectoryoverwritedialog();
}
else if (folderexists == false) {
const auto copyOptions = std::filesystem::copy_options::recursive |
  std::filesystem::copy_options::overwrite_existing;
std::filesystem::copy(filepath,path,copyOptions);
 }
}
}
}
if (chint == 27) {
if (menubarmode == true) {
menubarmode = false;
setBackgroundColor(4);
printacharacterinanyterminallocation(2,1," ");
printacharacterinanyterminallocation(3,1," ");
printacharacterinanyterminallocation(4,1," ");
printacharacterinanyterminallocation(5,1," ");
printacharacterinanyterminallocation(6,1," ");
printacharacterinanyterminallocation(7,1," ");
printacharacterinanyterminallocation(8,1," ");
printacharacterinanyterminallocation(9,1," ");
printacharacterinanyterminallocation(10,1," ");
printacharacterinanyterminallocation(10,2," ");
printacharacterinanyterminallocation(10,3," ");
printacharacterinanyterminallocation(10,4," ");
printacharacterinanyterminallocation(10,5," ");
printacharacterinanyterminallocation(10,6," ");
printacharacterinanyterminallocation(10,7," ");
printacharacterinanyterminallocation(10,8," ");
printacharacterinanyterminallocation(10,9," ");
printacharacterinanyterminallocation(10,10," ");
printacharacterinanyterminallocation(10,11," ");
printacharacterinanyterminallocation(10,12," ");
printacharacterinanyterminallocation(10,13," ");
printacharacterinanyterminallocation(10,14," ");
printacharacterinanyterminallocation(10,15," ");
printacharacterinanyterminallocation(10,16," ");
printacharacterinanyterminallocation(10,17," ");
printacharacterinanyterminallocation(10,18," ");
printacharacterinanyterminallocation(10,19," ");
printacharacterinanyterminallocation(10,20," ");
printacharacterinanyterminallocation(10,21," ");
printacharacterinanyterminallocation(10,22," ");
printacharacterinanyterminallocation(10,23," ");
printacharacterinanyterminallocation(10,24," ");
printacharacterinanyterminallocation(10,25," ");
printacharacterinanyterminallocation(3,25," ");
printacharacterinanyterminallocation(4,25," ");
printacharacterinanyterminallocation(5,25," ");
printacharacterinanyterminallocation(6,25," ");
printacharacterinanyterminallocation(7,25," ");
printacharacterinanyterminallocation(8,25," ");
printacharacterinanyterminallocation(9,25," ");
printacharacterinanyterminallocation(2,25," ");
printacharacterinanyterminallocation(2,24," ");
printacharacterinanyterminallocation(2,23," ");
printacharacterinanyterminallocation(2,22," ");
printacharacterinanyterminallocation(2,21," ");
printacharacterinanyterminallocation(2,20," ");
printacharacterinanyterminallocation(2,19," ");
printacharacterinanyterminallocation(2,18," ");
printacharacterinanyterminallocation(2,17," ");
printacharacterinanyterminallocation(2,16," ");
printacharacterinanyterminallocation(2,15," ");
printacharacterinanyterminallocation(2,14," ");
printacharacterinanyterminallocation(2,13," ");
printacharacterinanyterminallocation(2,12," ");
printacharacterinanyterminallocation(2,11," ");
printacharacterinanyterminallocation(2,10," ");
printacharacterinanyterminallocation(2,9," ");
printacharacterinanyterminallocation(2,8," ");
printacharacterinanyterminallocation(2,7," ");
printacharacterinanyterminallocation(2,6," ");
printacharacterinanyterminallocation(2,5," ");
printacharacterinanyterminallocation(2,4," ");
printacharacterinanyterminallocation(2,3," ");
printacharacterinanyterminallocation(2,2," ");
printacharacterinanyterminallocation(3,2," ");
printacharacterinanyterminallocation(3,3," ");
printacharacterinanyterminallocation(3,4," ");
printacharacterinanyterminallocation(3,5," ");
printacharacterinanyterminallocation(3,6," ");
printacharacterinanyterminallocation(3,7," ");
printacharacterinanyterminallocation(3,8," ");
printacharacterinanyterminallocation(3,9," ");
printacharacterinanyterminallocation(3,10," ");
printacharacterinanyterminallocation(3,11," ");
printacharacterinanyterminallocation(3,12," ");
printacharacterinanyterminallocation(3,13," ");
printacharacterinanyterminallocation(3,14," ");
printacharacterinanyterminallocation(3,15," ");
printacharacterinanyterminallocation(3,16," ");
printacharacterinanyterminallocation(3,17," ");
printacharacterinanyterminallocation(3,18," ");
printacharacterinanyterminallocation(3,19," ");
printacharacterinanyterminallocation(3,20," ");
printacharacterinanyterminallocation(3,21," ");
printacharacterinanyterminallocation(3,22," ");
printacharacterinanyterminallocation(3,23," ");
printacharacterinanyterminallocation(3,24," ");
printacharacterinanyterminallocation(4,2," ");
printacharacterinanyterminallocation(4,3," ");
printacharacterinanyterminallocation(4,4," ");
printacharacterinanyterminallocation(4,5," ");
printacharacterinanyterminallocation(4,6," ");
printacharacterinanyterminallocation(4,7," ");
printacharacterinanyterminallocation(4,8," ");
printacharacterinanyterminallocation(4,9," ");
printacharacterinanyterminallocation(4,10," ");
printacharacterinanyterminallocation(4,11," ");
printacharacterinanyterminallocation(4,12," ");
printacharacterinanyterminallocation(4,13," ");
printacharacterinanyterminallocation(4,14," ");
printacharacterinanyterminallocation(4,15," ");
printacharacterinanyterminallocation(4,16," ");
printacharacterinanyterminallocation(4,17," ");
printacharacterinanyterminallocation(4,18," ");
printacharacterinanyterminallocation(4,19," ");
printacharacterinanyterminallocation(4,20," ");
printacharacterinanyterminallocation(4,21," ");
printacharacterinanyterminallocation(4,22," ");
printacharacterinanyterminallocation(4,23," ");
printacharacterinanyterminallocation(4,24," ");
printacharacterinanyterminallocation(5,2," ");
printacharacterinanyterminallocation(5,3," ");
printacharacterinanyterminallocation(5,4," ");
printacharacterinanyterminallocation(5,5," ");
printacharacterinanyterminallocation(5,6," ");
printacharacterinanyterminallocation(5,7," ");
printacharacterinanyterminallocation(5,8," ");
printacharacterinanyterminallocation(5,9," ");
printacharacterinanyterminallocation(5,10," ");
printacharacterinanyterminallocation(5,11," ");
printacharacterinanyterminallocation(5,12," ");
printacharacterinanyterminallocation(5,13," ");
printacharacterinanyterminallocation(5,14," ");
printacharacterinanyterminallocation(5,15," ");
printacharacterinanyterminallocation(5,16," ");
printacharacterinanyterminallocation(5,17," ");
printacharacterinanyterminallocation(5,18," ");
printacharacterinanyterminallocation(5,19," ");
printacharacterinanyterminallocation(5,20," ");
printacharacterinanyterminallocation(5,21," ");
printacharacterinanyterminallocation(5,22," ");
printacharacterinanyterminallocation(5,23," ");
printacharacterinanyterminallocation(5,24," ");
printacharacterinanyterminallocation(6,2," ");
printacharacterinanyterminallocation(6,3," ");
printacharacterinanyterminallocation(6,4," ");
printacharacterinanyterminallocation(6,5," ");
printacharacterinanyterminallocation(6,6," ");
printacharacterinanyterminallocation(6,7," ");
printacharacterinanyterminallocation(6,8," ");
printacharacterinanyterminallocation(6,9," ");
printacharacterinanyterminallocation(6,10," ");
printacharacterinanyterminallocation(6,11," ");
printacharacterinanyterminallocation(6,12," ");
printacharacterinanyterminallocation(6,13," ");
printacharacterinanyterminallocation(6,14," ");
printacharacterinanyterminallocation(6,15," ");
printacharacterinanyterminallocation(6,16," ");
printacharacterinanyterminallocation(6,17," ");
printacharacterinanyterminallocation(6,18," ");
printacharacterinanyterminallocation(6,19," ");
printacharacterinanyterminallocation(6,20," ");
printacharacterinanyterminallocation(6,21," ");
printacharacterinanyterminallocation(6,22," ");
printacharacterinanyterminallocation(6,23," ");
printacharacterinanyterminallocation(6,24," ");
printacharacterinanyterminallocation(7,2," ");
printacharacterinanyterminallocation(7,3," ");
printacharacterinanyterminallocation(7,4," ");
printacharacterinanyterminallocation(7,5," ");
printacharacterinanyterminallocation(7,6," ");
printacharacterinanyterminallocation(7,7," ");
printacharacterinanyterminallocation(7,8," ");
printacharacterinanyterminallocation(7,9," ");
printacharacterinanyterminallocation(7,10," ");
printacharacterinanyterminallocation(7,11," ");
printacharacterinanyterminallocation(7,12," ");
printacharacterinanyterminallocation(7,13," ");
printacharacterinanyterminallocation(7,14," ");
printacharacterinanyterminallocation(7,15," ");
printacharacterinanyterminallocation(7,16," ");
printacharacterinanyterminallocation(7,17," ");
printacharacterinanyterminallocation(7,18," ");
printacharacterinanyterminallocation(7,19," ");
printacharacterinanyterminallocation(7,20," ");
printacharacterinanyterminallocation(7,21," ");
printacharacterinanyterminallocation(7,22," ");
printacharacterinanyterminallocation(7,23," ");
printacharacterinanyterminallocation(7,24," ");
printacharacterinanyterminallocation(8,2," ");
printacharacterinanyterminallocation(8,3," ");
printacharacterinanyterminallocation(8,4," ");
printacharacterinanyterminallocation(8,5," ");
printacharacterinanyterminallocation(8,6," ");
printacharacterinanyterminallocation(8,7," ");
printacharacterinanyterminallocation(8,8," ");
printacharacterinanyterminallocation(8,9," ");
printacharacterinanyterminallocation(8,10," ");
printacharacterinanyterminallocation(8,11," ");
printacharacterinanyterminallocation(8,12," ");
printacharacterinanyterminallocation(8,13," ");
printacharacterinanyterminallocation(8,14," ");
printacharacterinanyterminallocation(8,15," ");
printacharacterinanyterminallocation(8,16," ");
printacharacterinanyterminallocation(8,17," ");
printacharacterinanyterminallocation(8,18," ");
printacharacterinanyterminallocation(8,19," ");
printacharacterinanyterminallocation(8,20," ");
printacharacterinanyterminallocation(8,21," ");
printacharacterinanyterminallocation(8,22," ");
printacharacterinanyterminallocation(8,23," ");
printacharacterinanyterminallocation(8,24," ");
printacharacterinanyterminallocation(9,2," ");
printacharacterinanyterminallocation(9,3," ");
printacharacterinanyterminallocation(9,4," ");
printacharacterinanyterminallocation(9,5," ");
printacharacterinanyterminallocation(9,6," ");
printacharacterinanyterminallocation(9,7," ");
printacharacterinanyterminallocation(9,8," ");
printacharacterinanyterminallocation(9,9," ");
printacharacterinanyterminallocation(9,10," ");
printacharacterinanyterminallocation(9,11," ");
printacharacterinanyterminallocation(9,12," ");
printacharacterinanyterminallocation(9,13," ");
printacharacterinanyterminallocation(9,14," ");
printacharacterinanyterminallocation(9,15," ");
printacharacterinanyterminallocation(9,16," ");
printacharacterinanyterminallocation(9,17," ");
printacharacterinanyterminallocation(9,18," ");
printacharacterinanyterminallocation(9,19," ");
printacharacterinanyterminallocation(9,20," ");
printacharacterinanyterminallocation(9,21," ");
printacharacterinanyterminallocation(9,22," ");
printacharacterinanyterminallocation(9,23," ");
printacharacterinanyterminallocation(9,24," ");
putchar('\n');
drawingoffilesboxdone = false;
int backup = driveslistingscount;
driveslistingscount = backup;
drawdrivesbox();
driveslistingscount = backup;
drawingoffilesboxdone = true;
xcoordinateformenubar = 0;
menubar();
}
else if (copyfileoverwritedialogmode == true) {
}
else if (copydirectoryoverwritedialogmode == true) {
}
else if (movefileoverwritedialogmode == true) {
}
else if (movedirectoryoverwritedialogmode == true) {
}
else if (deletefiledialogmode == true) {
deletefiledialogmode = false;
xcoordinatefordeletefiledialog = 1;
int ycoordinatebackup = ycoordinate;
ycoordinate = ycoordinatebackup;
setBackgroundColor(4);
movecursortoanyterminallocation(6,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(7,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(8,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(9,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(10,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(11,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(12,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(13,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(14,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(15,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(16,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(17,11);
std::cout << "                                                           ";
cleandrivesbox();
cleanfilesbox();
cleanpreviewbox();
drawdrivesbox();
drawfilesbox(0,0,0,1);
drawpreviewbox();
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) { //not done
movecursortoanyterminallocation(ycoordinate,columns - 52);
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
              }
              else {
              setBackgroundColor(3);
              movecursortoanyterminallocation(ycoordinate,columns - 52);
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
}
//filenamelistingscount++;
setBackgroundColor(4);
//std::cout << "down";
putchar('\n');
}
else if (deletedirectorydialogmode == true) {
deletedirectorydialogmode = false;
xcoordinatefordeletedirectorydialog = 1;
int ycoordinatebackup = ycoordinate;
ycoordinate = ycoordinatebackup;
setBackgroundColor(4);
movecursortoanyterminallocation(6,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(7,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(8,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(9,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(10,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(11,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(12,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(13,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(14,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(15,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(16,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(17,11);
std::cout << "                                                           ";
cleandrivesbox();
cleanfilesbox();
cleanpreviewbox();
drawdrivesbox();
drawfilesbox(0,0,0,1);
drawpreviewbox();
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) { //not done
movecursortoanyterminallocation(ycoordinate,columns - 52);
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
              }
              else {
              setBackgroundColor(3);
              movecursortoanyterminallocation(ycoordinate,columns - 52);
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
}
//filenamelistingscount++;
setBackgroundColor(4);
//std::cout << "down";
putchar('\n');
}
else if (newfolderdialogmode == true) {
}
else if (menubarwithexitonlyoptionmode == true) {
menubarwithexitonlyoptionmode = false;
//closemenubar();
}
}
if (chint == 48) {
std::size_t found = filepath.find_last_of("/");
  //std::cout << " path: " << str.substr(0,found) << '\n';
  std::cout << " file: " << filepath.substr(found+1) << '\n';
  if (filepath.substr(found+1) == "test.rep") {
  std::cout << "test12345678" << std::endl;
  }
}
if (chint == 50) {
drawfilesbox(0,0,0,1);
}
if (ch == 'w') {
std::cout << "filenamelistingscount:" << filenamelistingscount;
std::cout << "scrolldownsinfilesbox:" << scrolldownsinfilesbox;
std::cout << "possiblescrolldownsinfilesbox:" << possiblescrolldownsinfilesbox;
drawscrollbarforfilesbox();
putchar('\n');
}
if (chint == 10) {
if (menubarmode == false && copyfileoverwritedialogmode == false && copydirectoryoverwritedialogmode == false && movefileoverwritedialogmode == false && movedirectoryoverwritedialogmode == false && deletefiledialogmode == false && deletedirectorydialogmode == false && newfolderdialogmode == false && renamedialogmode == false && newnamedialogmode == false) {
setBackgroundColor(4);
if (xcoordinate == 1) {
if (menubarwithexitonlyoptionmode == false) {
//std::cout << "You selected:" << driveslistings[driveslistingscount].label << "-" << driveslistingscount << "-" << possiblescrolldownsindrivesbox << std::endl;
path = driveslistings[driveslistingscount].mountPoint;
filenamelistings.clear();
fileanddircount = 0;
drawingoffilesboxdone = false;
filenamelistingscount = 0;
ycoordinate = 2;
countformovingdowninfilesbox = 0;
readfilenames("codeforrefresh");
//std::cout << "filenamelistingssize:" << filenamelistings.size();
//std::cout << fileanddircount;
//system("clear");
//menubar();
cleanfilesbox();
//cleandrivesbox();
cleanpreviewbox();
//drawdrivesbox();
drawpreviewbox();
drawfilesbox(0,0,0,1);
drawpreviewbox();
const char* pathinchar = path.c_str();
chdir(pathinchar); }
else if (menubarwithexitonlyoptionmode == true) {
resetColors();
std::cout << "\033[2J";
std::cout << "\033[?1049l";
struct termios tty;
tcgetattr(STDIN_FILENO, &tty);
tty.c_lflag |= (ICANON | ECHO);
tcsetattr(STDIN_FILENO, TCSANOW, &tty);
std::cout << "\033[?25h";
return 0;
}
}
if (xcoordinate == 2) {
if (filenamelistings[filenamelistingscount].filename != "..") {
//std::cout << "You selected:" << filenamelistings[filenamelistingscount].filename << "-" << filenamelistingscount << "-" << possiblescrolldownsindrivesbox << std::endl;
const char* file = filenamelistings[filenamelistingscount].filename.c_str();
if (isTextFile(filenamelistings[filenamelistingscount].filename) == "text" && !std::filesystem::is_directory(filenamelistings[filenamelistingscount].filename)) {
nogobackadirafteruseofnano = true;
std::string command = "nano " + filenamelistings[filenamelistingscount].filename;
const char* commandinconstchar = command.c_str();
system(commandinconstchar);
setBackgroundColor(4);
for (int progressrow = rows / 2 - 1;progressrow != 1;progressrow--) {
printacharacterinanyterminallocation(progressrow,columns /2 - 14," ");
}
for (int progresscolummn = columns;progresscolummn != 0;progresscolummn--) {
printacharacterinanyterminallocation(rows,progresscolummn," ");
}
movecursortoanyterminallocation(1,1);
cleandrivesbox();
cleanfilesbox();
cleanpreviewbox();
filenamelistingscount = 0;
countformovingdowninfilesbox = 0;
scrolldownsinfilesbox = 0;
drawingoffilesboxdone = false;
ycoordinate = 3;
drawdrivesbox();
drawfilesbox(0,0,0,1);
drawpreviewbox();
menubar();
putchar('\n');
}
}
//std::cout << "path:" << path << "/" << filenamelistings[filenamelistingscount].filename;
//putchar('\n');
//system("sleep 5");
if (std::filesystem::is_directory(filenamelistings[filenamelistingscount].filename) && filenamelistings[filenamelistingscount].filename != "..") {
//std::cout << filenamelistings[filenamelistingscount].filename << " is a directory." << std::endl;
if (path == "/") {
//std::cout << "test";
path = "/" + filenamelistings[filenamelistingscount].filename;
}
else {
path = path + "/" + filenamelistings[filenamelistingscount].filename;}
const char* pathinchar = path.c_str();
chdir(pathinchar);
//std::cout << "path" << path;
filenamelistings.clear();
fileanddircount = 0;
drawingoffilesboxdone = false;
filenamelistingscount = 0;
ycoordinate = 2;
countformovingdowninfilesbox = 0;
readfilenames("codeforrefresh");
//std::cout << "filenamelistingssize:" << filenamelistings.size();
//std::cout << fileanddircount;
//system("clear");
//menubar();
cleanfilesbox();
//cleandrivesbox();
cleanpreviewbox();
//drawdrivesbox(); //UI corruption 1
drawpreviewbox();
movecursortoanyterminallocation(2,2);
drawfilesbox(0,0,0,1); //UI corruption 2
drawscrollbarforfilesbox();
drawpreviewbox();
}
else if (filenamelistings[filenamelistingscount].filename == ".." && nogobackadirafteruseofnano == false) {
int index = path.find_last_of('/');
int numSlashes = 0;
for (char c : path) {
if (c == '/') {
numSlashes++;
}
}
std::cout << numSlashes;
if (numSlashes == 1) {
path = "/";
}
else {
path.erase(index); }
//movecursortoanyterminallocation(22,1);
//std::cout << "ModifiedPath:" << path;
//putchar('\n');
//system("sleep 5");
//system("clear");
filenamelistings.clear();
fileanddircount = 0;
readfilenames("codeforrefresh");
cleanfilesbox();
drawfilesbox(0,0,0,1);
}
nogobackadirafteruseofnano = false;
}
}
else if (menubarmode == true && xcoordinate == 2) {
if (xcoordinateformenubar == 1) {
std::cout << "Cut option selected" << std::endl;
copyorcut = 2;
if (path == "/" ) {
filepath = path + filenamelistings[filenamelistingscount].filename; }
else if (path != "/" ) {
filepath = path + "/" + filenamelistings[filenamelistingscount].filename; }
std::cout << "filepath:" << filepath << std::endl;
}
else if (xcoordinateformenubar == 2) {
//std::cout << "Copy option selected" << std::endl;
fileorfolderpathforcheckofexistenceindestination = path;
if (!std::filesystem::is_directory(filenamelistings[filenamelistingscount].filename)) {
copyorcut = 1;
fileordirectorycopyorcut = 1;
if (path == "/" ) {
filepath = path + filenamelistings[filenamelistingscount].filename; }
else if (path != "/" ) {
filepath = path + "/" + filenamelistings[filenamelistingscount].filename; }
//std::cout << "filepath:" << filepath << std::endl;
}
else if (std::filesystem::is_directory(filenamelistings[filenamelistingscount].filename)) {
copyorcut = 1;
fileordirectorycopyorcut = 2;
if (path == "/" ) {
filepath = path + filenamelistings[filenamelistingscount].filename; }
else if (path != "/" ) {
filepath = path + "/" + filenamelistings[filenamelistingscount].filename; }
//std::cout << "filepath:" << filepath << std::endl;
}
menubarmode = false;
setBackgroundColor(4);
printacharacterinanyterminallocation(2,1," ");
printacharacterinanyterminallocation(3,1," ");
printacharacterinanyterminallocation(4,1," ");
printacharacterinanyterminallocation(5,1," ");
printacharacterinanyterminallocation(6,1," ");
printacharacterinanyterminallocation(7,1," ");
printacharacterinanyterminallocation(8,1," ");
printacharacterinanyterminallocation(9,1," ");
printacharacterinanyterminallocation(10,1," ");
printacharacterinanyterminallocation(10,2," ");
printacharacterinanyterminallocation(10,3," ");
printacharacterinanyterminallocation(10,4," ");
printacharacterinanyterminallocation(10,5," ");
printacharacterinanyterminallocation(10,6," ");
printacharacterinanyterminallocation(10,7," ");
printacharacterinanyterminallocation(10,8," ");
printacharacterinanyterminallocation(10,9," ");
printacharacterinanyterminallocation(10,10," ");
printacharacterinanyterminallocation(10,11," ");
printacharacterinanyterminallocation(10,12," ");
printacharacterinanyterminallocation(10,13," ");
printacharacterinanyterminallocation(10,14," ");
printacharacterinanyterminallocation(10,15," ");
printacharacterinanyterminallocation(10,16," ");
printacharacterinanyterminallocation(10,17," ");
printacharacterinanyterminallocation(10,18," ");
printacharacterinanyterminallocation(10,19," ");
printacharacterinanyterminallocation(10,20," ");
printacharacterinanyterminallocation(10,21," ");
printacharacterinanyterminallocation(10,22," ");
printacharacterinanyterminallocation(10,23," ");
printacharacterinanyterminallocation(10,24," ");
printacharacterinanyterminallocation(10,25," ");
printacharacterinanyterminallocation(3,25," ");
printacharacterinanyterminallocation(4,25," ");
printacharacterinanyterminallocation(5,25," ");
printacharacterinanyterminallocation(6,25," ");
printacharacterinanyterminallocation(7,25," ");
printacharacterinanyterminallocation(8,25," ");
printacharacterinanyterminallocation(9,25," ");
printacharacterinanyterminallocation(2,25," ");
printacharacterinanyterminallocation(2,24," ");
printacharacterinanyterminallocation(2,23," ");
printacharacterinanyterminallocation(2,22," ");
printacharacterinanyterminallocation(2,21," ");
printacharacterinanyterminallocation(2,20," ");
printacharacterinanyterminallocation(2,19," ");
printacharacterinanyterminallocation(2,18," ");
printacharacterinanyterminallocation(2,17," ");
printacharacterinanyterminallocation(2,16," ");
printacharacterinanyterminallocation(2,15," ");
printacharacterinanyterminallocation(2,14," ");
printacharacterinanyterminallocation(2,13," ");
printacharacterinanyterminallocation(2,12," ");
printacharacterinanyterminallocation(2,11," ");
printacharacterinanyterminallocation(2,10," ");
printacharacterinanyterminallocation(2,9," ");
printacharacterinanyterminallocation(2,8," ");
printacharacterinanyterminallocation(2,7," ");
printacharacterinanyterminallocation(2,6," ");
printacharacterinanyterminallocation(2,5," ");
printacharacterinanyterminallocation(2,4," ");
printacharacterinanyterminallocation(2,3," ");
printacharacterinanyterminallocation(2,2," ");
printacharacterinanyterminallocation(3,2," ");
printacharacterinanyterminallocation(3,3," ");
printacharacterinanyterminallocation(3,4," ");
printacharacterinanyterminallocation(3,5," ");
printacharacterinanyterminallocation(3,6," ");
printacharacterinanyterminallocation(3,7," ");
printacharacterinanyterminallocation(3,8," ");
printacharacterinanyterminallocation(3,9," ");
printacharacterinanyterminallocation(3,10," ");
printacharacterinanyterminallocation(3,11," ");
printacharacterinanyterminallocation(3,12," ");
printacharacterinanyterminallocation(3,13," ");
printacharacterinanyterminallocation(3,14," ");
printacharacterinanyterminallocation(3,15," ");
printacharacterinanyterminallocation(3,16," ");
printacharacterinanyterminallocation(3,17," ");
printacharacterinanyterminallocation(3,18," ");
printacharacterinanyterminallocation(3,19," ");
printacharacterinanyterminallocation(3,20," ");
printacharacterinanyterminallocation(3,21," ");
printacharacterinanyterminallocation(3,22," ");
printacharacterinanyterminallocation(3,23," ");
printacharacterinanyterminallocation(3,24," ");
printacharacterinanyterminallocation(4,2," ");
printacharacterinanyterminallocation(4,3," ");
printacharacterinanyterminallocation(4,4," ");
printacharacterinanyterminallocation(4,5," ");
printacharacterinanyterminallocation(4,6," ");
printacharacterinanyterminallocation(4,7," ");
printacharacterinanyterminallocation(4,8," ");
printacharacterinanyterminallocation(4,9," ");
printacharacterinanyterminallocation(4,10," ");
printacharacterinanyterminallocation(4,11," ");
printacharacterinanyterminallocation(4,12," ");
printacharacterinanyterminallocation(4,13," ");
printacharacterinanyterminallocation(4,14," ");
printacharacterinanyterminallocation(4,15," ");
printacharacterinanyterminallocation(4,16," ");
printacharacterinanyterminallocation(4,17," ");
printacharacterinanyterminallocation(4,18," ");
printacharacterinanyterminallocation(4,19," ");
printacharacterinanyterminallocation(4,20," ");
printacharacterinanyterminallocation(4,21," ");
printacharacterinanyterminallocation(4,22," ");
printacharacterinanyterminallocation(4,23," ");
printacharacterinanyterminallocation(4,24," ");
printacharacterinanyterminallocation(5,2," ");
printacharacterinanyterminallocation(5,3," ");
printacharacterinanyterminallocation(5,4," ");
printacharacterinanyterminallocation(5,5," ");
printacharacterinanyterminallocation(5,6," ");
printacharacterinanyterminallocation(5,7," ");
printacharacterinanyterminallocation(5,8," ");
printacharacterinanyterminallocation(5,9," ");
printacharacterinanyterminallocation(5,10," ");
printacharacterinanyterminallocation(5,11," ");
printacharacterinanyterminallocation(5,12," ");
printacharacterinanyterminallocation(5,13," ");
printacharacterinanyterminallocation(5,14," ");
printacharacterinanyterminallocation(5,15," ");
printacharacterinanyterminallocation(5,16," ");
printacharacterinanyterminallocation(5,17," ");
printacharacterinanyterminallocation(5,18," ");
printacharacterinanyterminallocation(5,19," ");
printacharacterinanyterminallocation(5,20," ");
printacharacterinanyterminallocation(5,21," ");
printacharacterinanyterminallocation(5,22," ");
printacharacterinanyterminallocation(5,23," ");
printacharacterinanyterminallocation(5,24," ");
printacharacterinanyterminallocation(6,2," ");
printacharacterinanyterminallocation(6,3," ");
printacharacterinanyterminallocation(6,4," ");
printacharacterinanyterminallocation(6,5," ");
printacharacterinanyterminallocation(6,6," ");
printacharacterinanyterminallocation(6,7," ");
printacharacterinanyterminallocation(6,8," ");
printacharacterinanyterminallocation(6,9," ");
printacharacterinanyterminallocation(6,10," ");
printacharacterinanyterminallocation(6,11," ");
printacharacterinanyterminallocation(6,12," ");
printacharacterinanyterminallocation(6,13," ");
printacharacterinanyterminallocation(6,14," ");
printacharacterinanyterminallocation(6,15," ");
printacharacterinanyterminallocation(6,16," ");
printacharacterinanyterminallocation(6,17," ");
printacharacterinanyterminallocation(6,18," ");
printacharacterinanyterminallocation(6,19," ");
printacharacterinanyterminallocation(6,20," ");
printacharacterinanyterminallocation(6,21," ");
printacharacterinanyterminallocation(6,22," ");
printacharacterinanyterminallocation(6,23," ");
printacharacterinanyterminallocation(6,24," ");
printacharacterinanyterminallocation(7,2," ");
printacharacterinanyterminallocation(7,3," ");
printacharacterinanyterminallocation(7,4," ");
printacharacterinanyterminallocation(7,5," ");
printacharacterinanyterminallocation(7,6," ");
printacharacterinanyterminallocation(7,7," ");
printacharacterinanyterminallocation(7,8," ");
printacharacterinanyterminallocation(7,9," ");
printacharacterinanyterminallocation(7,10," ");
printacharacterinanyterminallocation(7,11," ");
printacharacterinanyterminallocation(7,12," ");
printacharacterinanyterminallocation(7,13," ");
printacharacterinanyterminallocation(7,14," ");
printacharacterinanyterminallocation(7,15," ");
printacharacterinanyterminallocation(7,16," ");
printacharacterinanyterminallocation(7,17," ");
printacharacterinanyterminallocation(7,18," ");
printacharacterinanyterminallocation(7,19," ");
printacharacterinanyterminallocation(7,20," ");
printacharacterinanyterminallocation(7,21," ");
printacharacterinanyterminallocation(7,22," ");
printacharacterinanyterminallocation(7,23," ");
printacharacterinanyterminallocation(7,24," ");
printacharacterinanyterminallocation(8,2," ");
printacharacterinanyterminallocation(8,3," ");
printacharacterinanyterminallocation(8,4," ");
printacharacterinanyterminallocation(8,5," ");
printacharacterinanyterminallocation(8,6," ");
printacharacterinanyterminallocation(8,7," ");
printacharacterinanyterminallocation(8,8," ");
printacharacterinanyterminallocation(8,9," ");
printacharacterinanyterminallocation(8,10," ");
printacharacterinanyterminallocation(8,11," ");
printacharacterinanyterminallocation(8,12," ");
printacharacterinanyterminallocation(8,13," ");
printacharacterinanyterminallocation(8,14," ");
printacharacterinanyterminallocation(8,15," ");
printacharacterinanyterminallocation(8,16," ");
printacharacterinanyterminallocation(8,17," ");
printacharacterinanyterminallocation(8,18," ");
printacharacterinanyterminallocation(8,19," ");
printacharacterinanyterminallocation(8,20," ");
printacharacterinanyterminallocation(8,21," ");
printacharacterinanyterminallocation(8,22," ");
printacharacterinanyterminallocation(8,23," ");
printacharacterinanyterminallocation(8,24," ");
printacharacterinanyterminallocation(9,2," ");
printacharacterinanyterminallocation(9,3," ");
printacharacterinanyterminallocation(9,4," ");
printacharacterinanyterminallocation(9,5," ");
printacharacterinanyterminallocation(9,6," ");
printacharacterinanyterminallocation(9,7," ");
printacharacterinanyterminallocation(9,8," ");
printacharacterinanyterminallocation(9,9," ");
printacharacterinanyterminallocation(9,10," ");
printacharacterinanyterminallocation(9,11," ");
printacharacterinanyterminallocation(9,12," ");
printacharacterinanyterminallocation(9,13," ");
printacharacterinanyterminallocation(9,14," ");
printacharacterinanyterminallocation(9,15," ");
printacharacterinanyterminallocation(9,16," ");
printacharacterinanyterminallocation(9,17," ");
printacharacterinanyterminallocation(9,18," ");
printacharacterinanyterminallocation(9,19," ");
printacharacterinanyterminallocation(9,20," ");
printacharacterinanyterminallocation(9,21," ");
printacharacterinanyterminallocation(9,22," ");
printacharacterinanyterminallocation(9,23," ");
printacharacterinanyterminallocation(9,24," ");
putchar('\n');
drawingoffilesboxdone = false;
int backup = driveslistingscount;
driveslistingscount = backup;
drawdrivesbox();
driveslistingscount = backup;
drawingoffilesboxdone = true;
xcoordinateformenubar = 0;
menubar();
}
else if (xcoordinateformenubar == 3) {
std::cout << "Paste option selected" << std::endl;
bool fileexists = false;
bool folderexists = false;
if (copyorcut == 1 && fileordirectorycopyorcut == 1) {
std::size_t found = filepath.find_last_of("/");
  //std::cout << " path: " << str.substr(0,found) << '\n';
  for (int vectoritem = filenamelistings.size();vectoritem != 0,vectoritem--;) {
  if (filenamelistings[vectoritem].filename == filepath.substr(found+1)) {
  fileexists = true;
  }
  }
  if (fileexists == true) {
  copyfileoverwritedialogmode = true;
  showcopyfileoverwritedialog();
  }
else if (fileexists == false) {
//const auto copyOptions = filesystem::copy_options::recursive |
  //filesystem::copy_options::overwrite_existing;
  //std::cout << "path:" << path << std::endl;
  //std::filesystem::create_directory(filepath.substr(found+1));
  //std::string destinationpath = path + "/" + filepath.substr(found+1);
  //std::cout << "path:" << destinationpath << std::endl;
std::filesystem::copy(filepath,path);
 }
}
else if (copyorcut == 1 && fileordirectorycopyorcut == 2) {
//const auto copyOptions = filesystem::copy_options::recursive;
//std::filesystem::copy(filepath,path,copyOptions);
std::size_t found = filepath.find_last_of("/");
  //std::cout << " path: " << str.substr(0,found) << '\n';
  for (int vectoritem = filenamelistings.size();vectoritem != 0,vectoritem--;) {
  if (filenamelistings[vectoritem].filename == filepath.substr(found+1)) {
  folderexists = true;
  }
  }
  if (folderexists == true) {
  copydirectoryoverwritedialogmode = true;
  showcopydirectoryoverwritedialog();
  }
else if (folderexists == false) {
//const auto copyOptions = filesystem::copy_options::recursive |
  //filesystem::copy_options::overwrite_existing;
  const auto copyOptions = std::filesystem::copy_options::recursive;
  std::cout << "path:" << path << std::endl;
  std::filesystem::create_directory(filepath.substr(found+1));
  std::string destinationpath = path + "/" + filepath.substr(found+1);
  std::cout << "path:" << destinationpath << std::endl;
std::filesystem::copy(filepath,destinationpath,copyOptions);
 }
menubarmode = false;
//folderexists = false;
menubar();
cleandrivesbox();
drawdrivesbox();
if (fileexists == true) {
copyfileoverwritedialogmode = true;
showcopyfileoverwritedialog();
}
else if (folderexists == true) {
copydirectoryoverwritedialogmode = true;
showcopydirectoryoverwritedialog();
}
filenamelistingscount = 0;
fileanddircount = 0;
countformovingdowninfilesbox = 0;
scrolldownsinfilesbox = 0;
drawingoffilesboxdone = false;
ycoordinate = 2;
filenamelistings.clear();
readfilenames("codeforrefresh");
drawscrollbarfordrivesbox();
drawscrollbarforfilesbox();
}
}
else if (xcoordinateformenubar == 4) {
//std::cout << "Rename option selected" << std::endl;
renamedialogmode = true;
renamedialogmodencursesmode = true;
menubarmode = false;
showrenamedialog();
//ioctl(0, FIONREAD, &byteswaiting);
//ioctl(0, FIONREAD, &byteswaiting);
//ioctl(0, FIONREAD, &byteswaiting);
//ioctl(0, FIONREAD, &byteswaiting);
}
else if (xcoordinateformenubar == 5) {
movecursortoanyterminallocation(9,1);
std::cout << "Delete option selected" << std::endl;
//closemenubar();
if (!std::filesystem::is_directory(filenamelistings[filenamelistingscount].filename)) {
deletefiledialogmode = true;
showdeletefiledialog();
}
else if (std::filesystem::is_directory(filenamelistings[filenamelistingscount].filename)) {
deletedirectorydialogmode = true;
showdeletedirectorydialog();
}
//menubar();
}
else if (xcoordinateformenubar == 6) {
//std::cout << "New folder option selected" << std::endl;
menubarmode = false;
newfolderdialogmode = true;
newfolderdialogmodencursesmode = true;
shownewdirectorydialog();
}
else if (xcoordinateformenubar == 7) {
resetColors();
std::cout << "\033[2J";
std::cout << "\033[?1049l";
struct termios tty;
tcgetattr(STDIN_FILENO, &tty);
tty.c_lflag |= (ICANON | ECHO);
tcsetattr(STDIN_FILENO, TCSANOW, &tty);
std::cout << "\033[?25h";
return 0;
//std::cout << "Exit option selected" << std::endl;
}
}
else if (copyfileoverwritedialogmode == true) {
if (coordinateforcopyexistingfiledialog == 0) {
copyfileoverwritedialogmode = false;
//std::cout << "Cancel button selected!" << std::endl;
int ycoordinatebackup = ycoordinate;
ycoordinate = 3;
setBackgroundColor(4);
movecursortoanyterminallocation(6,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(7,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(8,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(9,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(10,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(11,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(12,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(13,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(14,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(15,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(16,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(17,11);
std::cout << "                                                           ";
cleandrivesbox();
cleanfilesbox();
cleanpreviewbox();
drawdrivesbox();
drawfilesbox(0,filenamelistingscount,0,1);
drawpreviewbox();
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) { //not done
movecursortoanyterminallocation(ycoordinate,columns - 52);
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
              }
              else {
              setBackgroundColor(3);
              movecursortoanyterminallocation(ycoordinate,columns - 52);
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
}
//filenamelistingscount++;
setBackgroundColor(4);
//std::cout << "down";
putchar('\n');
}
else if (coordinateforcopyexistingfiledialog == 1) {
std::cout << "New name button selected!" << std::endl;
coordinateforcopyexistingfiledialog = 0;
int ycoordinatebackup = ycoordinate;
ycoordinate = 3;
setBackgroundColor(4);
movecursortoanyterminallocation(6,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(7,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(8,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(9,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(10,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(11,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(12,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(13,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(14,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(15,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(16,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(17,11);
std::cout << "                                                           ";
cleandrivesbox();
cleanfilesbox();
cleanpreviewbox();
drawdrivesbox();
drawfilesbox(0,filenamelistingscount,0,1);
drawpreviewbox();
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) { //not done
movecursortoanyterminallocation(ycoordinate,columns - 52);
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
              }
              else {
              setBackgroundColor(3);
              movecursortoanyterminallocation(ycoordinate,columns - 52);
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
}
//filenamelistingscount++;
setBackgroundColor(4);
//std::cout << "down";
putchar('\n');
//getchar();
ioctl(0,FIONREAD,&byteswaiting);
copyfileoverwritedialogmode = false;
newnamedialogmode = true;
newnamedialogmodencursesmode = true;
shownewnamedialogforcopyandmove();
}
else if (coordinateforcopyexistingfiledialog == 2) {
//std::cout << "Overwrite button selected!" << std::endl;
copyfileoverwritedialogmode = false;
coordinateforcopyexistingfiledialog = 0;
 const auto copyOptions = std::filesystem::copy_options::overwrite_existing;
try {
std::filesystem::copy(filepath,path,copyOptions);
}
catch (...) {
std::cout << "An error occurred while overwriting the file!.Check that you have permission to overwrite the file and that the filesystem isn't read-only" << std::endl;
std::cout << "Normal operation will continue after 10 seconds" << std::endl;
usleep(10000000);
}
int ycoordinatebackup = ycoordinate;
ycoordinate = 3;
setBackgroundColor(4);
movecursortoanyterminallocation(6,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(7,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(8,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(9,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(10,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(11,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(12,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(13,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(14,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(15,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(16,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(17,11);
std::cout << "                                                           ";
cleandrivesbox();
cleanfilesbox();
cleanpreviewbox();
drawdrivesbox();
drawfilesbox(0,filenamelistingscount,0,1);
drawpreviewbox();
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) { //not done
movecursortoanyterminallocation(ycoordinate,columns - 52);
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
              }
              else {
              setBackgroundColor(3);
              movecursortoanyterminallocation(ycoordinate,columns - 52);
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
}
//filenamelistingscount++;
setBackgroundColor(4);
//std::cout << "down";
putchar('\n');
}
}
else if (copydirectoryoverwritedialogmode == true) {
if (ycoordinateforcopydirectoryoverwritedialog == 0) {
copydirectoryoverwritedialogmode = false;
int ycoordinatebackup = ycoordinate;
ycoordinate = 2;
setBackgroundColor(4);
movecursortoanyterminallocation(6,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(7,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(8,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(9,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(10,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(11,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(12,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(13,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(14,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(15,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(16,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(17,11);
std::cout << "                                                           ";
cleandrivesbox();
cleanfilesbox();
cleanpreviewbox();
drawdrivesbox();
drawfilesbox(0,filenamelistingscount,0,1);
drawpreviewbox();
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) { //not done
movecursortoanyterminallocation(ycoordinate,columns - 52);
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
              }
              else {
              setBackgroundColor(3);
              movecursortoanyterminallocation(ycoordinate,columns - 52);
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
}
//filenamelistingscount++;
setBackgroundColor(4);
//std::cout << "down";
putchar('\n');
}
else if (ycoordinateforcopydirectoryoverwritedialog == 1) {
copydirectoryoverwritedialogmode = false;
newnamedialogmode = true;
newnamedialogmodencursesmode = true;
shownewnamedialogforcopyandmove();
}
else if (ycoordinateforcopydirectoryoverwritedialog == 2) {
const auto copyOptions = filesystem::copy_options::recursive | filesystem::copy_options::overwrite_existing;
try {
std::filesystem::copy(filepath,path,copyOptions);
}
catch (...) {
std::cout << "An error occurred while copying!.Check that you have permission to copy and that the filesystem isn't read-only" << std::endl;
std::cout << "Normal operation will continue after 10 seconds" << std::endl;
usleep(10000000);
}
}
else if (ycoordinateforcopydirectoryoverwritedialog == 3) {
const auto copyOptions = filesystem::copy_options::recursive | filesystem::copy_options::skip_existing;
try {
std::filesystem::copy(filepath,path,copyOptions);
}
catch (...) {
std::cout << "An error occurred while copying!.Check that you have permission to copy and that the filesystem isn't read-only" << std::endl;
std::cout << "Normal operation will continue after 10 seconds" << std::endl;
usleep(10000000);
}
}
else if (ycoordinateforcopydirectoryoverwritedialog == 4) {
bool donttrycopying = false;
const auto copyOptions = filesystem::copy_options::recursive;
std::size_t found = filepath.find_last_of("/");
try {
std::filesystem::remove_all(filepath.substr(found+1));
}
catch (...) {
donttrycopying = true;
std::cout << "An error occurred while copying!.Check that you have permission to copy and that the filesystem isn't read-only" << std::endl;
std::cout << "Normal operation will continue after 10 seconds" << std::endl;
usleep(10000000);
}
if (donttrycopying == false) {
try {
std::filesystem::copy(filepath,path,copyOptions);
}
catch (...) {
std::cout << "An error occurred while copying!.Check that you have permission to copy and that the filesystem isn't read-only" << std::endl;
std::cout << "Normal operation will continue after 10 seconds" << std::endl;
usleep(10000000);
}
}
}
else if (ycoordinateforcopydirectoryoverwritedialog == 4) {
bool donttrycopying = false;
const auto copyOptions = filesystem::copy_options::recursive;
std::size_t found = filepath.find_last_of("/");
try {
std::filesystem::remove_all(filepath.substr(found+1));
}
catch (...) {
donttrycopying = true;
std::cout << "An error occurred while copying!.Check that you have permission to copy and that the filesystem isn't read-only" << std::endl;
std::cout << "Normal operation will continue after 10 seconds" << std::endl;
usleep(10000000);
}
if (donttrycopying == false) {
try {
std::filesystem::copy(filepath,path,copyOptions);
}
catch (...) {
std::cout << "An error occurred while copying!.Check that you have permission to copy and that the filesystem isn't read-only" << std::endl;
std::cout << "Normal operation will continue after 10 seconds" << std::endl;
usleep(10000000);
}
}
}
}
else if (movefileoverwritedialogmode == true) {
}
else if (movedirectoryoverwritedialogmode == true) {
}
else if (deletefiledialogmode == true) {
if (xcoordinatefordeletefiledialog == 1) {
deletefiledialogmode = false;
std::cout << "No option selected" << std::endl;
int ycoordinatebackup = ycoordinate;
ycoordinate = 2;
setBackgroundColor(4);
movecursortoanyterminallocation(6,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(7,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(8,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(9,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(10,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(11,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(12,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(13,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(14,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(15,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(16,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(17,11);
std::cout << "                                                           ";
cleandrivesbox();
cleanfilesbox();
cleanpreviewbox();
drawdrivesbox();
drawfilesbox(0,filenamelistingscount,0,1);
drawpreviewbox();
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) { //not done
movecursortoanyterminallocation(ycoordinate,columns - 52);
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
              }
              else {
              setBackgroundColor(3);
              movecursortoanyterminallocation(ycoordinate,columns - 52);
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
}
//filenamelistingscount++;
setBackgroundColor(4);
//std::cout << "down";
putchar('\n');
}
else if (xcoordinatefordeletefiledialog == 2) {
//std::cout << "Yes option selected" << std::endl;
deletefiledialogmode = false;
xcoordinatefordeletefiledialog = 1;
try {
std::filesystem::remove(filenamelistings[filenamelistingscount].filename); }
catch (...) {
std::cout << "An error occurred while deleting the file!.Check that you have permission to delete the file and that the filesystem isn't read-only" << std::endl;
std::cout << "Normal operation will continue after 10 seconds" << std::endl;
usleep(10000000);
}
filenamelistingscount = 0;
fileanddircount = 0;
countformovingdowninfilesbox = 0;
scrolldownsinfilesbox = 0;
drawingoffilesboxdone = false;
ycoordinate = 2;
filenamelistings.clear();
readfilenames("codeforrefresh");
setBackgroundColor(4);
movecursortoanyterminallocation(6,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(7,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(8,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(9,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(10,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(11,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(12,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(13,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(14,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(15,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(16,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(17,11);
std::cout << "                                                           ";
cleandrivesbox();
cleanfilesbox();
cleanpreviewbox();
drawdrivesbox();
drawfilesbox(0,0,0,1);
drawpreviewbox();
//filenamelistingscount++;
setBackgroundColor(4);
//std::cout << "down";
putchar('\n');
}
}
else if (deletedirectorydialogmode == true) {
if (xcoordinatefordeletedirectorydialog == 1) {
deletedirectorydialogmode = false;
std::cout << "No option selected" << std::endl;
//int ycoordinatebackup = ycoordinate;
//ycoordinate = ycoordinatebackup;
//int filenamelistingscountbackup = filenamelistingscount;
setBackgroundColor(4);
movecursortoanyterminallocation(6,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(7,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(8,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(9,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(10,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(11,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(12,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(13,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(14,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(15,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(16,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(17,11);
std::cout << "                                                           ";
cleandrivesbox();
//cleanfilesbox();
cleanpreviewbox();
drawdrivesbox();
//filenamelistingscount = filenamelistingscountbackup;
//ycoordinate = ycoordinatebackup;
ycoordinate = 3;
filenamelistingscount = 0;
countformovingdowninfilesbox = 0;
cleanfilesbox();
drawfilesbox(0,0,0,1);
drawpreviewbox();
//filenamelistingscount = filenamelistingscountbackup;
//ycoordinate = ycoordinatebackup;
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) { //not done
movecursortoanyterminallocation(ycoordinate,columns - 52);
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
              }
              else {
              setBackgroundColor(3);
              movecursortoanyterminallocation(ycoordinate,columns - 52);
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
}
//filenamelistingscount = filenamelistingscountbackup;
//ycoordinate = ycoordinatebackup;
//filenamelistingscount = filenamelistingscountbackup;
//ycoordinate = ycoordinatebackup;
//filenamelistingscount++;
setBackgroundColor(4);
//std::cout << "down";
putchar('\n');
}
else if (xcoordinatefordeletedirectorydialog == 2) {
//std::cout << "Yes option selected" << std::endl;
deletedirectorydialogmode = false;
xcoordinatefordeletedirectorydialog = 1;
try {
std::filesystem::remove_all(filenamelistings[filenamelistingscount].filename); }
catch (...) {
std::cout << "An error occurred while deleting the folder!.Check that you have permission to delete the folder and that the filesystem isn't read-only" << std::endl;
std::cout << "Normal operation will continue after 10 seconds" << std::endl;
usleep(10000000);
}
filenamelistingscount = 0;
fileanddircount = 0;
countformovingdowninfilesbox = 0;
scrolldownsinfilesbox = 0;
drawingoffilesboxdone = false;
ycoordinate = 2;
filenamelistings.clear();
readfilenames("codeforrefresh");
setBackgroundColor(4);
movecursortoanyterminallocation(6,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(7,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(8,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(9,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(10,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(11,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(12,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(13,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(14,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(15,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(16,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(17,11);
std::cout << "                                                           ";
cleandrivesbox();
cleanfilesbox();
cleanpreviewbox();
drawdrivesbox();
drawfilesbox(0,0,0,1);
drawpreviewbox();
//filenamelistingscount++;
setBackgroundColor(4);
//std::cout << "down";
putchar('\n');
}
}
else if (newfolderdialogmode == true) {
if (ycoordinatefornewfolderdialog == 1) {
std::cout << "Cancel button selected!" << std::endl;
setBackgroundColor(4);
std::cout << "\033[2J" << std::endl;
drawingoffilesboxdone = false;
filenamelistingscount = 0;
ycoordinate = 2;
countformovingdowninfilesbox = 0;
menubar();
cleandrivesbox();
drawdrivesbox();
cleanscrollbarfordrivesbox();
drawscrollbarfordrivesbox();
drawfilesbox(0,0,0,1);
cleanscrollbarforfilesbox();
drawscrollbarforfilesbox();
drawpreviewbox();
newfolderdialogmode = false;
//clear from cursor to beginning of line
//std::cout << "\033[K";
}
if (ycoordinatefornewfolderdialog == 2) {
//std::cout << "OK button selected!" << std::endl;
char *buffer = field_buffer(fields[0], 0);
std::string input_string(buffer);
//std::cout << input_string << std::endl;
try {
std::filesystem::create_directory(input_string);}
catch (...) {
std::cout << "An error has occurred while creating the directory!.Please make sure that you have permission to create a directory in your current location and that its filesystem isn't read-only" << std::endl;
std::cout << "Normal operation will continue after 10 seconds" << std::endl;
usleep(10000000);
}
setBackgroundColor(4);
std::cout << "\033[2J" << std::endl;
filenamelistings.clear();
fileanddircount = 0;
drawingoffilesboxdone = false;
filenamelistingscount = 0;
ycoordinate = 2;
countformovingdowninfilesbox = 0;
readfilenames("codeforrefresh");
drawpreviewbox();
drawfilesbox(0,0,0,1);
drawpreviewbox();
menubar();
newfolderdialogmode = false;
}
}
else if (newnamedialogmode == true) {
if (ycoordinatefornewnamedialog == 1) {
std::cout << "Cancel button selected!" << std::endl;
setBackgroundColor(4);
std::cout << "\033[2J" << std::endl;
drawingoffilesboxdone = false;
filenamelistingscount = 0;
ycoordinate = 2;
countformovingdowninfilesbox = 0;
menubar();
cleandrivesbox();
drawdrivesbox();
cleanscrollbarfordrivesbox();
drawscrollbarfordrivesbox();
drawfilesbox(0,0,0,1);
cleanscrollbarforfilesbox();
drawscrollbarforfilesbox();
drawpreviewbox();
newnamedialogmode = false;
//clear from cursor to beginning of line
//std::cout << "\033[K";
}
if (ycoordinatefornewnamedialog == 2) {
//ycoordinatefornewnamedialog = 1;
std::cout << "OK button selected!" << std::endl;
//getchar();
char *buffer = field_buffer(fields2[0], 0);
std::string input_string(buffer);
//std::cout << input_string << std::endl;
if (copyorcut == 1) {
try {
std::filesystem::copy(filepath,input_string);}
catch (...) {
std::cout << "An error has occurred while copying the file!.Please make sure that you have permission to copy and that the filesystem isn't read-only" << std::endl;
std::cout << "Normal operation will continue after 10 seconds" << std::endl;
usleep(10000000);
}
}
else if (copyorcut == 2) {
try {
std::filesystem::rename(filepath,input_string);}
catch (...) {
std::cout << "An error has occurred while moving the file!.Please make sure that you have permission to move and that the filesystem isn't read-only" << std::endl;
std::cout << "Normal operation will continue after 10 seconds" << std::endl;
usleep(10000000);
}
}
setBackgroundColor(4);
std::cout << "\033[2J" << std::endl;
filenamelistings.clear();
fileanddircount = 0;
drawingoffilesboxdone = false;
filenamelistingscount = 0;
ycoordinate = 2;
countformovingdowninfilesbox = 0;
readfilenames("codeforrefresh");
drawpreviewbox();
drawfilesbox(0,0,0,1);
drawpreviewbox();
menubar();
newnamedialogmode = false;
//std::cout << "ycoordinatefornewnamedialog:" << ycoordinatefornewnamedialog << std::endl;
}
}
else if (renamedialogmode == true) {
if (ycoordinatefornewfolderdialog == 1) {
std::cout << "Cancel button selected!" << std::endl;
setBackgroundColor(4);
std::cout << "\033[2J" << std::endl;
drawingoffilesboxdone = false;
filenamelistingscount = 0;
ycoordinate = 2;
countformovingdowninfilesbox = 0;
menubar();
cleandrivesbox();
drawdrivesbox();
cleanscrollbarfordrivesbox();
drawscrollbarfordrivesbox();
drawfilesbox(0,0,0,1);
cleanscrollbarforfilesbox();
drawscrollbarforfilesbox();
drawpreviewbox();
renamedialogmode = false;
//clear from cursor to beginning of line
//std::cout << "\033[K";
}
if (ycoordinatefornewfolderdialog == 2) {
//std::cout << "OK button selected!" << std::endl;
char *buffer = field_buffer(fields1[0], 0);
std::string input_string(buffer);
//std::cout << input_string << std::endl;
try {
std::filesystem::rename(filenamelistings[filenamelistingscount].filename,input_string);}
catch (...) {
std::cout << "An error has occurred while renaming the file/directory!.Please make sure that you have permission to rename the file/directory and that its filesystem isn't read-only" << std::endl;
std::cout << "Normal operation will continue after 10 seconds" << std::endl;
usleep(10000000);
}
setBackgroundColor(4);
std::cout << "\033[2J" << std::endl;
filenamelistings.clear();
fileanddircount = 0;
drawingoffilesboxdone = false;
filenamelistingscount = 0;
ycoordinate = 2;
countformovingdowninfilesbox = 0;
readfilenames("codeforrefresh");
drawpreviewbox();
drawfilesbox(0,0,0,1);
drawpreviewbox();
menubar();
renamedialogmode = false;
}
}
}
}
else if (byteswaiting == 3) {
char ch1 = getchar();
char ch2 = getchar();
char ch3 = getchar();
std::ofstream archivo;
archivo.open("codigo.txt");
archivo << ch1;
archivo << ch2;
archivo << ch3;
archivo.close();
//std::cout << ch1 << ch2 << ch3 << endl;
if (ch1 == '' && ch2 == '[' && ch3 == 'A') { //arriba
//movecursortoanyterminallocation(progressrow,columns / 2 - 12);
if (menubarmode == false && copyfileoverwritedialogmode == false && copydirectoryoverwritedialogmode == false && movefileoverwritedialogmode == false && movedirectoryoverwritedialogmode == false && deletefiledialogmode == false && deletedirectorydialogmode == false && newfolderdialogmode == false && renamedialogmode == false && newnamedialogmode == false) {
if (xcoordinate == 1) {
if (countformovingdownindrivesbox != 0) {
if (ycoordinate == 1) {
ycoordinate = 3;
driveslistingscount = 0;}
movecursortoanyterminallocation(ycoordinate,2);
std::cout << driveslistings[driveslistingscount].label << "-" << driveslistingscount << std::endl;
ycoordinate--;
driveslistingscount--;
setBackgroundColor(3);
movecursortoanyterminallocation(ycoordinate,2);
std::cout << driveslistings[driveslistingscount].label << "-" << driveslistingscount << std::endl;
setBackgroundColor(4);
countformovingdownindrivesbox--;
//std::cout << "down";
//putchar('\n');
}
else if (driveslistingscount != 0 && driveslistings.size() > rows / 2 - 4) {
if (scrolldownsindrivesbox != 0) {
scrolldownsindrivesbox--; }
std::cout << "up";
cleandrivesbox();
//std::cin.ignore();
//std::cin.ignore();
//std::cin.ignore();
int substraction = rows / 2 - 4;
driveslistingscount = driveslistingscount - substraction;
drawdrivesbox(0,driveslistingscount,1);
//drawscrollbarfordrivesbox();
drawfilesbox();
drawpreviewbox();
menubar();
}
//std::cout << "up";
//putchar('\n');
}
if (xcoordinate == 2) {
if (countformovingdowninfilesbox != 0) { //not done
if (ycoordinate == 1) {
ycoordinate = 3;
filenamelistingscount = 0;}
movecursortoanyterminallocation(ycoordinate,columns / 2 - 12);
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) {
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
movecursortoanyterminallocation(ycoordinate,columns - 20);
std::cout << "\033[" << (40 + 4) << "m" << filenamelistings[filenamelistingscount].filedateandtime << std::endl;
              }
              else {
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
              movecursortoanyterminallocation(ycoordinate,columns - 20);
std::cout << "\033[" << (40 + 4) << "m" << filenamelistings[filenamelistingscount].filedateandtime << std::endl;}
//filenamelistingscount++;
ycoordinate--;
filenamelistingscount--;
setBackgroundColor(3);
movecursortoanyterminallocation(ycoordinate,columns / 2 - 12);
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) {
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
movecursortoanyterminallocation(ycoordinate,columns - 20);
std::cout << "\033[" << (40 + 4) << "m" << filenamelistings[filenamelistingscount].filedateandtime << std::endl;
              }
              else {
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
              movecursortoanyterminallocation(ycoordinate,columns - 20);
std::cout << "\033[" << (40 + 4) << "m" << filenamelistings[filenamelistingscount].filedateandtime << std::endl;}
//filenamelistingscount--;
setBackgroundColor(4);
countformovingdowninfilesbox--;
//std::cout << "down";
//putchar('\n');
}
else if (filenamelistingscount != 0 && filenamelistings.size() > rows / 2 - 4) { //not done
if (scrolldownsinfilesbox != 0) {
scrolldownsinfilesbox--; }
std::cout << "up";
//cleandrivesbox();
//std::cin.ignore();
//std::cin.ignore();
//std::cin.ignore();
int substraction = rows / 2 - 4;
filenamelistingscount = filenamelistingscount - substraction;
cleandrivesbox();
driveslistingscount = 0;
drawdrivesbox(0,driveslistingscount,1);
//drawdrivesbox();
cleanscrollbarforfilesbox();
drawscrollbarforfilesbox();
drawfilesbox(1,filenamelistingscount,0);
drawpreviewbox();
menubar();
}
}
writecontentsinpreviewbox();
}
else if (menubarmode == true) {
if (xcoordinateformenubar != 1) {
xcoordinateformenubar--;
menubar();
}
}
else if (copyfileoverwritedialogmode == true) {
}
else if (copydirectoryoverwritedialogmode == true) {
}
else if (movefileoverwritedialogmode == true) {
}
else if (movedirectoryoverwritedialogmode == true) {
}
else if (deletefiledialogmode == true) {
}
else if (deletedirectorydialogmode == true) {
std::cout << "up" << std::endl;
}
else if (newfolderdialogmode == true) {
//std::cout << "\033[?25h";
movecursortoanyterminallocation(1,1);
//initscr();
//noecho();
	//cbreak();
	//keypad(stdscr, TRUE);
	//movecursortoanyterminallocation(15,5);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	//std::cout << "byteswaiting:" << byteswaiting << std::endl;
	//getchar();
	//getchar();
	//getchar();
	//getchar();
	//std::cin.ignore();
	//std::cin.ignore();
	//std::cin.ignore();
	//std::cin.ignore();
	reset_prog_mode();
	curs_set(1);
	refresh();
newfolderdialogmodencursesmode = true;
}
else if (renamedialogmode == true) {
//std::cout << "\033[?25h";
movecursortoanyterminallocation(1,1);
//initscr();
//noecho();
	//cbreak();
	//keypad(stdscr, TRUE);
	//movecursortoanyterminallocation(15,5);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	//std::cout << "byteswaiting:" << byteswaiting << std::endl;
	//getchar();
	//getchar();
	//getchar();
	//getchar();
	//std::cin.ignore();
	//std::cin.ignore();
	//std::cin.ignore();
	//std::cin.ignore();
	reset_prog_mode();
	curs_set(1);
	refresh();
renamedialogmodencursesmode = true;
}
else if (newnamedialogmode == true) {
//std::cout << "\033[?25h";
movecursortoanyterminallocation(1,1);
//initscr();
//noecho();
	//cbreak();
	//keypad(stdscr, TRUE);
	//movecursortoanyterminallocation(15,5);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	ioctl(0, FIONREAD, &byteswaiting);
	//std::cout << "byteswaiting:" << byteswaiting << std::endl;
	//getchar();
	//getchar();
	//getchar();
	//getchar();
	//std::cin.ignore();
	//std::cin.ignore();
	//std::cin.ignore();
	//std::cin.ignore();
	reset_prog_mode();
	curs_set(1);
	refresh();
newnamedialogmodencursesmode = true;
}
}
if (ch1 == '' && ch2 == '[' && ch3 == 'B') { //down
if (menubarmode == false && copyfileoverwritedialogmode == false && copydirectoryoverwritedialogmode == false && movefileoverwritedialogmode == false && movedirectoryoverwritedialogmode == false && deletefiledialogmode == false && deletedirectorydialogmode == false && newfolderdialogmode == false && renamedialogmode == false && newnamedialogmode == false) {
if (xcoordinate == 1) {
//driveslistingscount-ycoordinate-countformovingdownindrivesbox
//8-2-0
//9-2-1
//8-1-0
if (countformovingdownindrivesbox < rows / 2 - 4 && ycoordinate != rows / 2 - 2 + 1 && driveslistingscount != static_cast<int>(driveslistings.size() - 1)) {
if (ycoordinate == 1 && driveslistingscount < rows / 2 - 4) {
ycoordinate = 3;
driveslistingscount = 0; }
if (ycoordinate == 1 && driveslistingscount >= rows / 2 - 4) {
setBackgroundColor(4);
ycoordinate = 3; }
if (ycoordinate == 2) {
ycoordinate = 3;
setBackgroundColor(4);
}
if (ycoordinate != 2) {
movecursortoanyterminallocation(ycoordinate,2);
setBackgroundColor(4);
std::cout << driveslistings[driveslistingscount].label << "-" << driveslistingscount << std::endl;
ycoordinate++;
driveslistingscount++;
setBackgroundColor(3);
movecursortoanyterminallocation(ycoordinate,2);
std::cout << driveslistings[driveslistingscount].label << "-" << driveslistingscount << std::endl;
setBackgroundColor(4);
countformovingdownindrivesbox++;
//std::cout << "down";
//putchar('\n');
}
}
if (countformovingdownindrivesbox >= rows / 2 - 4) {
if (scrolldownsindrivesbox < possiblescrolldownsindrivesbox) {
scrolldownsindrivesbox++; }
countformovingdownindrivesbox = 0;
//std::cout << "test";
ycoordinate = 2;
//std::cin.ignore();
//std::cin.ignore();
//std::cin.ignore();
//system("clear");
if (driveslistings.size() > rows / 2 - 4) {
if (ycoordinate != rows / 2 - 2 + 1) {
cleandrivesbox();
if (countformovingdownindrivesbox != 0) {
driveslistingscount = driveslistingscount - countformovingdownindrivesbox;
}
drawdrivesbox(1,driveslistingscount);
//drawscrollbarfordrivesbox();
drawfilesbox();
drawpreviewbox();
menubar();
}
//putchar('\n');
}
}
}
if (xcoordinate == 2) {
//driveslistingscount-ycoordinate-countformovingdownindrivesbox
//8-2-0
//9-2-1
//8-1-0
if (countformovingdowninfilesbox < rows / 2 - 4 && ycoordinate != rows / 2 - 2 + 1 && filenamelistingscount != static_cast<int>(filenamelistings.size() - 1)) { //done
if (ycoordinate == 1 && filenamelistingscount < rows / 2 - 4) { //skipped
ycoordinate = 3;
filenamelistingscount = 0; }
if (ycoordinate == 1 && filenamelistingscount >= rows / 2 - 4) { //skipped
setBackgroundColor(4);
ycoordinate = 3; }
if (ycoordinate == 2) { //skipped
ycoordinate = 3;
setBackgroundColor(4);
}
if (ycoordinate != 2) { //done
movecursortoanyterminallocation(ycoordinate,columns / 2 - 12);
//std::cout << "ycoordinate:" << ycoordinate << std::endl;
setBackgroundColor(4);
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) { //done
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
movecursortoanyterminallocation(ycoordinate,columns - 20);
std::cout << "\033[" << (40 + 4) << "m" << filenamelistings[filenamelistingscount].filedateandtime << std::endl;
              }
              else {
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
              movecursortoanyterminallocation(ycoordinate,columns - 20);
std::cout << "\033[" << (40 + 4) << "m" << filenamelistings[filenamelistingscount].filedateandtime << std::endl;}
filenamelistingscount++;
ycoordinate++;
//filenamelistingscount++;
setBackgroundColor(3);
movecursortoanyterminallocation(ycoordinate,columns / 2 - 12);
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) { //not done
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
movecursortoanyterminallocation(ycoordinate,columns - 20);
std::cout << "\033[" << (40 + 4) << "m" << filenamelistings[filenamelistingscount].filedateandtime << std::endl;
              }
              else {
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
              movecursortoanyterminallocation(ycoordinate,columns - 20);
std::cout << "\033[" << (40 + 4) << "m" << filenamelistings[filenamelistingscount].filedateandtime << std::endl;}
//filenamelistingscount++;
setBackgroundColor(4);
countformovingdowninfilesbox++;
//std::cout << "down";
//putchar('\n');
}
}
if (countformovingdowninfilesbox >= rows / 2 - 4) {
if (scrolldownsinfilesbox < possiblescrolldownsinfilesbox) {
scrolldownsinfilesbox++; }
countformovingdowninfilesbox = 0;
//std::cout << "test";
ycoordinate = 2;
//std::cin.ignore();
//std::cin.ignore();
//std::cin.ignore();
//system("clear");
if (filenamelistings.size() > rows / 2 - 4) {
if (ycoordinate != rows / 2 - 2 + 1) {
cleandrivesbox();
if (countformovingdowninfilesbox != 0) {
filenamelistingscount = filenamelistingscount - countformovingdowninfilesbox;
}
xcoordinate = 2;
drawfilesbox(1,filenamelistingscount);
cleanscrollbarforfilesbox();
drawscrollbarforfilesbox();
drawdrivesbox();
drawpreviewbox();
menubar();
}
//putchar('\n');
}
}
}
writecontentsinpreviewbox();
}
else if (menubarmode == true) {
if (xcoordinateformenubar != 7) {
xcoordinateformenubar++;
menubar();
}
}
else if (copyfileoverwritedialogmode == true) {
}
else if (copydirectoryoverwritedialogmode == true) {
}
else if (movefileoverwritedialogmode == true) {
}
else if (movedirectoryoverwritedialogmode == true) {
}
else if (deletefiledialogmode == true) {
}
else if (deletedirectorydialogmode == true) {
std::cout << "down" << std::endl;
}
else if (newfolderdialogmode == true) {
}
else if (renamedialogmode == true) {
}
}
//std::cout << "down" << std::endl;
if (ch1 == '' && ch2 == '[' && ch3 == 'D') {
if (menubarmode == false && copyfileoverwritedialogmode == false && copydirectoryoverwritedialogmode == false && movefileoverwritedialogmode == false && movedirectoryoverwritedialogmode == false && deletefiledialogmode == false && deletedirectorydialogmode == false && newfolderdialogmode == false && renamedialogmode == false && newnamedialogmode == false) {
if (xcoordinate != 1) {
xcoordinate--;
ycoordinate = 1;
driveslistingscount = 0;
countformovingdownindrivesbox == 0;
filenamelistingscount = 0;
drawdrivesbox();
drawfilesbox();
drawingoffilesboxdone = false;
}
//return 0;
//std::cout << "left";
//putchar('\n');
}
else if (copyfileoverwritedialogmode == true) {
if (coordinateforcopyexistingfiledialog != 2) {
coordinateforcopyexistingfiledialog++;
}
if (coordinateforcopyexistingfiledialog == 2) {
setBackgroundColor(3);
printacharacterinanyterminallocation(18,15,"O");
printacharacterinanyterminallocation(18,16,"v");
printacharacterinanyterminallocation(18,17,"e");
printacharacterinanyterminallocation(18,18,"r");
printacharacterinanyterminallocation(18,19,"w");
printacharacterinanyterminallocation(18,20,"r");
printacharacterinanyterminallocation(18,21,"i");
printacharacterinanyterminallocation(18,22,"t");
printacharacterinanyterminallocation(18,23,"e");
setBackgroundColor(1);
printacharacterinanyterminallocation(18,24," ");
printacharacterinanyterminallocation(18,25," ");
printacharacterinanyterminallocation(18,26," ");
printacharacterinanyterminallocation(18,27," ");
printacharacterinanyterminallocation(18,28,"N");
printacharacterinanyterminallocation(18,29,"e");
printacharacterinanyterminallocation(18,30,"w");
printacharacterinanyterminallocation(18,31," ");
printacharacterinanyterminallocation(18,32,"n");
printacharacterinanyterminallocation(18,33,"a");
printacharacterinanyterminallocation(18,34,"m");
printacharacterinanyterminallocation(18,35,"e");
printacharacterinanyterminallocation(18,36," ");
printacharacterinanyterminallocation(18,37," ");
printacharacterinanyterminallocation(18,38," ");
printacharacterinanyterminallocation(18,39," ");
printacharacterinanyterminallocation(18,40,"C");
printacharacterinanyterminallocation(18,41,"a");
printacharacterinanyterminallocation(18,42,"n");
printacharacterinanyterminallocation(18,43,"c");
printacharacterinanyterminallocation(18,44,"e");
printacharacterinanyterminallocation(18,45,"l");
}
else if (coordinateforcopyexistingfiledialog == 1) {
printacharacterinanyterminallocation(18,15,"O");
printacharacterinanyterminallocation(18,16,"v");
printacharacterinanyterminallocation(18,17,"e");
printacharacterinanyterminallocation(18,18,"r");
printacharacterinanyterminallocation(18,19,"w");
printacharacterinanyterminallocation(18,20,"r");
printacharacterinanyterminallocation(18,21,"i");
printacharacterinanyterminallocation(18,22,"t");
printacharacterinanyterminallocation(18,23,"e");
printacharacterinanyterminallocation(18,24," ");
printacharacterinanyterminallocation(18,25," ");
printacharacterinanyterminallocation(18,26," ");
printacharacterinanyterminallocation(18,27," ");
setBackgroundColor(3);
printacharacterinanyterminallocation(18,28,"N");
printacharacterinanyterminallocation(18,29,"e");
printacharacterinanyterminallocation(18,30,"w");
printacharacterinanyterminallocation(18,31," ");
printacharacterinanyterminallocation(18,32,"n");
printacharacterinanyterminallocation(18,33,"a");
printacharacterinanyterminallocation(18,34,"m");
printacharacterinanyterminallocation(18,35,"e");
setBackgroundColor(1);
printacharacterinanyterminallocation(18,36," ");
printacharacterinanyterminallocation(18,37," ");
printacharacterinanyterminallocation(18,38," ");
printacharacterinanyterminallocation(18,39," ");
printacharacterinanyterminallocation(18,40,"C");
printacharacterinanyterminallocation(18,41,"a");
printacharacterinanyterminallocation(18,42,"n");
printacharacterinanyterminallocation(18,43,"c");
printacharacterinanyterminallocation(18,44,"e");
printacharacterinanyterminallocation(18,45,"l");
}
else if (coordinateforcopyexistingfiledialog == 0) {
printacharacterinanyterminallocation(18,15,"O");
printacharacterinanyterminallocation(18,16,"v");
printacharacterinanyterminallocation(18,17,"e");
printacharacterinanyterminallocation(18,18,"r");
printacharacterinanyterminallocation(18,19,"w");
printacharacterinanyterminallocation(18,20,"r");
printacharacterinanyterminallocation(18,21,"i");
printacharacterinanyterminallocation(18,22,"t");
printacharacterinanyterminallocation(18,23,"e");
printacharacterinanyterminallocation(18,24," ");
printacharacterinanyterminallocation(18,25," ");
printacharacterinanyterminallocation(18,26," ");
printacharacterinanyterminallocation(18,27," ");
printacharacterinanyterminallocation(18,28,"N");
printacharacterinanyterminallocation(18,29,"e");
printacharacterinanyterminallocation(18,30,"w");
printacharacterinanyterminallocation(18,31," ");
printacharacterinanyterminallocation(18,32,"n");
printacharacterinanyterminallocation(18,33,"a");
printacharacterinanyterminallocation(18,34,"m");
printacharacterinanyterminallocation(18,35,"e");
printacharacterinanyterminallocation(18,36," ");
printacharacterinanyterminallocation(18,37," ");
printacharacterinanyterminallocation(18,38," ");
printacharacterinanyterminallocation(18,39," ");
setBackgroundColor(3);
printacharacterinanyterminallocation(18,40,"C");
printacharacterinanyterminallocation(18,41,"a");
printacharacterinanyterminallocation(18,42,"n");
printacharacterinanyterminallocation(18,43,"c");
printacharacterinanyterminallocation(18,44,"e");
printacharacterinanyterminallocation(18,45,"l");
setBackgroundColor(1);
}
putchar('\n');
}
else if (copydirectoryoverwritedialogmode == true) {
if (ycoordinateforcopydirectoryoverwritedialog < 5) {
ycoordinateforcopydirectoryoverwritedialog++;
}
if (ycoordinateforcopydirectoryoverwritedialog == 0) {
printacharacterinanyterminallocation(18,15,"O");
printacharacterinanyterminallocation(18,16,"v");
printacharacterinanyterminallocation(18,17,"e");
printacharacterinanyterminallocation(18,18,"r");
printacharacterinanyterminallocation(18,19,"w");
printacharacterinanyterminallocation(18,20,"r");
printacharacterinanyterminallocation(18,21,"i");
printacharacterinanyterminallocation(18,22,"t");
printacharacterinanyterminallocation(18,23,"e");
printacharacterinanyterminallocation(18,24," ");
printacharacterinanyterminallocation(18,25," ");
printacharacterinanyterminallocation(18,26," ");
printacharacterinanyterminallocation(18,27," ");
printacharacterinanyterminallocation(18,28,"M");
printacharacterinanyterminallocation(18,29,"e");
printacharacterinanyterminallocation(18,30,"r");
printacharacterinanyterminallocation(18,31,"g");
printacharacterinanyterminallocation(18,32,"e");
printacharacterinanyterminallocation(18,33," ");
printacharacterinanyterminallocation(18,34," ");
printacharacterinanyterminallocation(18,35," ");
printacharacterinanyterminallocation(18,36," ");
printacharacterinanyterminallocation(18,37,"M");
printacharacterinanyterminallocation(18,38,"e");
printacharacterinanyterminallocation(18,39,"r");
printacharacterinanyterminallocation(18,40,"g");
printacharacterinanyterminallocation(18,41,"e");
printacharacterinanyterminallocation(18,42,"(");
printacharacterinanyterminallocation(18,43,"o");
printacharacterinanyterminallocation(18,44,"v");
printacharacterinanyterminallocation(18,45,"e");
printacharacterinanyterminallocation(18,46,"r");
printacharacterinanyterminallocation(18,47,"w");
printacharacterinanyterminallocation(18,48,"r");
printacharacterinanyterminallocation(18,49,"i");
printacharacterinanyterminallocation(18,50,"t");
printacharacterinanyterminallocation(18,51,"e");
printacharacterinanyterminallocation(18,52,")");
printacharacterinanyterminallocation(18,53,"N");
printacharacterinanyterminallocation(18,54,"e");
printacharacterinanyterminallocation(18,55,"w");
printacharacterinanyterminallocation(18,56," ");
printacharacterinanyterminallocation(18,57,"n");
printacharacterinanyterminallocation(18,58,"a");
printacharacterinanyterminallocation(18,59,"m");
printacharacterinanyterminallocation(18,60,"e");
setBackgroundColor(3);
printacharacterinanyterminallocation(18,62,"C");
printacharacterinanyterminallocation(18,63,"a");
printacharacterinanyterminallocation(18,64,"n");
printacharacterinanyterminallocation(18,65,"c");
printacharacterinanyterminallocation(18,66,"e");
printacharacterinanyterminallocation(18,67,"l");
setBackgroundColor(1);
}
else if (ycoordinateforcopydirectoryoverwritedialog == 1) {
printacharacterinanyterminallocation(18,15,"O");
printacharacterinanyterminallocation(18,16,"v");
printacharacterinanyterminallocation(18,17,"e");
printacharacterinanyterminallocation(18,18,"r");
printacharacterinanyterminallocation(18,19,"w");
printacharacterinanyterminallocation(18,20,"r");
printacharacterinanyterminallocation(18,21,"i");
printacharacterinanyterminallocation(18,22,"t");
printacharacterinanyterminallocation(18,23,"e");
printacharacterinanyterminallocation(18,24," ");
printacharacterinanyterminallocation(18,25," ");
printacharacterinanyterminallocation(18,26," ");
printacharacterinanyterminallocation(18,27," ");
printacharacterinanyterminallocation(18,28,"M");
printacharacterinanyterminallocation(18,29,"e");
printacharacterinanyterminallocation(18,30,"r");
printacharacterinanyterminallocation(18,31,"g");
printacharacterinanyterminallocation(18,32,"e");
printacharacterinanyterminallocation(18,33," ");
printacharacterinanyterminallocation(18,34," ");
printacharacterinanyterminallocation(18,35," ");
printacharacterinanyterminallocation(18,36," ");
printacharacterinanyterminallocation(18,37,"M");
printacharacterinanyterminallocation(18,38,"e");
printacharacterinanyterminallocation(18,39,"r");
printacharacterinanyterminallocation(18,40,"g");
printacharacterinanyterminallocation(18,41,"e");
printacharacterinanyterminallocation(18,42,"(");
printacharacterinanyterminallocation(18,43,"o");
printacharacterinanyterminallocation(18,44,"v");
printacharacterinanyterminallocation(18,45,"e");
printacharacterinanyterminallocation(18,46,"r");
printacharacterinanyterminallocation(18,47,"w");
printacharacterinanyterminallocation(18,48,"r");
printacharacterinanyterminallocation(18,49,"i");
printacharacterinanyterminallocation(18,50,"t");
printacharacterinanyterminallocation(18,51,"e");
printacharacterinanyterminallocation(18,52,")");
setBackgroundColor(3);
printacharacterinanyterminallocation(18,53,"N");
printacharacterinanyterminallocation(18,54,"e");
printacharacterinanyterminallocation(18,55,"w");
printacharacterinanyterminallocation(18,56," ");
printacharacterinanyterminallocation(18,57,"n");
printacharacterinanyterminallocation(18,58,"a");
printacharacterinanyterminallocation(18,59,"m");
printacharacterinanyterminallocation(18,60,"e");
setBackgroundColor(1);
printacharacterinanyterminallocation(18,62,"C");
printacharacterinanyterminallocation(18,63,"a");
printacharacterinanyterminallocation(18,64,"n");
printacharacterinanyterminallocation(18,65,"c");
printacharacterinanyterminallocation(18,66,"e");
printacharacterinanyterminallocation(18,67,"l");
}
else if (ycoordinateforcopydirectoryoverwritedialog == 2) {
printacharacterinanyterminallocation(18,15,"O");
printacharacterinanyterminallocation(18,16,"v");
printacharacterinanyterminallocation(18,17,"e");
printacharacterinanyterminallocation(18,18,"r");
printacharacterinanyterminallocation(18,19,"w");
printacharacterinanyterminallocation(18,20,"r");
printacharacterinanyterminallocation(18,21,"i");
printacharacterinanyterminallocation(18,22,"t");
printacharacterinanyterminallocation(18,23,"e");
printacharacterinanyterminallocation(18,24," ");
printacharacterinanyterminallocation(18,25," ");
printacharacterinanyterminallocation(18,26," ");
printacharacterinanyterminallocation(18,27," ");
printacharacterinanyterminallocation(18,28,"M");
printacharacterinanyterminallocation(18,29,"e");
printacharacterinanyterminallocation(18,30,"r");
printacharacterinanyterminallocation(18,31,"g");
printacharacterinanyterminallocation(18,32,"e");
printacharacterinanyterminallocation(18,33," ");
printacharacterinanyterminallocation(18,34," ");
printacharacterinanyterminallocation(18,35," ");
printacharacterinanyterminallocation(18,36," ");
setBackgroundColor(3);
printacharacterinanyterminallocation(18,37,"M");
printacharacterinanyterminallocation(18,38,"e");
printacharacterinanyterminallocation(18,39,"r");
printacharacterinanyterminallocation(18,40,"g");
printacharacterinanyterminallocation(18,41,"e");
printacharacterinanyterminallocation(18,42,"(");
printacharacterinanyterminallocation(18,43,"o");
printacharacterinanyterminallocation(18,44,"v");
printacharacterinanyterminallocation(18,45,"e");
printacharacterinanyterminallocation(18,46,"r");
printacharacterinanyterminallocation(18,47,"w");
printacharacterinanyterminallocation(18,48,"r");
printacharacterinanyterminallocation(18,49,"i");
printacharacterinanyterminallocation(18,50,"t");
printacharacterinanyterminallocation(18,51,"e");
printacharacterinanyterminallocation(18,52,")");
setBackgroundColor(1);
printacharacterinanyterminallocation(18,53,"N");
printacharacterinanyterminallocation(18,54,"e");
printacharacterinanyterminallocation(18,55,"w");
printacharacterinanyterminallocation(18,56," ");
printacharacterinanyterminallocation(18,57,"n");
printacharacterinanyterminallocation(18,58,"a");
printacharacterinanyterminallocation(18,59,"m");
printacharacterinanyterminallocation(18,60,"e");
printacharacterinanyterminallocation(18,62,"C");
printacharacterinanyterminallocation(18,63,"a");
printacharacterinanyterminallocation(18,64,"n");
printacharacterinanyterminallocation(18,65,"c");
printacharacterinanyterminallocation(18,66,"e");
printacharacterinanyterminallocation(18,67,"l");
}
else if (ycoordinateforcopydirectoryoverwritedialog == 3) {
printacharacterinanyterminallocation(18,15,"O");
printacharacterinanyterminallocation(18,16,"v");
printacharacterinanyterminallocation(18,17,"e");
printacharacterinanyterminallocation(18,18,"r");
printacharacterinanyterminallocation(18,19,"w");
printacharacterinanyterminallocation(18,20,"r");
printacharacterinanyterminallocation(18,21,"i");
printacharacterinanyterminallocation(18,22,"t");
printacharacterinanyterminallocation(18,23,"e");
printacharacterinanyterminallocation(18,24," ");
printacharacterinanyterminallocation(18,25," ");
printacharacterinanyterminallocation(18,26," ");
printacharacterinanyterminallocation(18,27," ");
setBackgroundColor(3);
printacharacterinanyterminallocation(18,28,"M");
printacharacterinanyterminallocation(18,29,"e");
printacharacterinanyterminallocation(18,30,"r");
printacharacterinanyterminallocation(18,31,"g");
printacharacterinanyterminallocation(18,32,"e");
setBackgroundColor(1);
printacharacterinanyterminallocation(18,33," ");
printacharacterinanyterminallocation(18,34," ");
printacharacterinanyterminallocation(18,35," ");
printacharacterinanyterminallocation(18,36," ");
printacharacterinanyterminallocation(18,37,"M");
printacharacterinanyterminallocation(18,38,"e");
printacharacterinanyterminallocation(18,39,"r");
printacharacterinanyterminallocation(18,40,"g");
printacharacterinanyterminallocation(18,41,"e");
printacharacterinanyterminallocation(18,42,"(");
printacharacterinanyterminallocation(18,43,"o");
printacharacterinanyterminallocation(18,44,"v");
printacharacterinanyterminallocation(18,45,"e");
printacharacterinanyterminallocation(18,46,"r");
printacharacterinanyterminallocation(18,47,"w");
printacharacterinanyterminallocation(18,48,"r");
printacharacterinanyterminallocation(18,49,"i");
printacharacterinanyterminallocation(18,50,"t");
printacharacterinanyterminallocation(18,51,"e");
printacharacterinanyterminallocation(18,52,")");
printacharacterinanyterminallocation(18,53,"N");
printacharacterinanyterminallocation(18,54,"e");
printacharacterinanyterminallocation(18,55,"w");
printacharacterinanyterminallocation(18,56," ");
printacharacterinanyterminallocation(18,57,"n");
printacharacterinanyterminallocation(18,58,"a");
printacharacterinanyterminallocation(18,59,"m");
printacharacterinanyterminallocation(18,60,"e");
printacharacterinanyterminallocation(18,62,"C");
printacharacterinanyterminallocation(18,63,"a");
printacharacterinanyterminallocation(18,64,"n");
printacharacterinanyterminallocation(18,65,"c");
printacharacterinanyterminallocation(18,66,"e");
printacharacterinanyterminallocation(18,67,"l");
}
else if (ycoordinateforcopydirectoryoverwritedialog == 4) {
setBackgroundColor(3);
printacharacterinanyterminallocation(18,15,"O");
printacharacterinanyterminallocation(18,16,"v");
printacharacterinanyterminallocation(18,17,"e");
printacharacterinanyterminallocation(18,18,"r");
printacharacterinanyterminallocation(18,19,"w");
printacharacterinanyterminallocation(18,20,"r");
printacharacterinanyterminallocation(18,21,"i");
printacharacterinanyterminallocation(18,22,"t");
printacharacterinanyterminallocation(18,23,"e");
setBackgroundColor(1);
printacharacterinanyterminallocation(18,24," ");
printacharacterinanyterminallocation(18,25," ");
printacharacterinanyterminallocation(18,26," ");
printacharacterinanyterminallocation(18,27," ");
printacharacterinanyterminallocation(18,28,"M");
printacharacterinanyterminallocation(18,29,"e");
printacharacterinanyterminallocation(18,30,"r");
printacharacterinanyterminallocation(18,31,"g");
printacharacterinanyterminallocation(18,32,"e");
printacharacterinanyterminallocation(18,33," ");
printacharacterinanyterminallocation(18,34," ");
printacharacterinanyterminallocation(18,35," ");
printacharacterinanyterminallocation(18,36," ");
printacharacterinanyterminallocation(18,37,"M");
printacharacterinanyterminallocation(18,38,"e");
printacharacterinanyterminallocation(18,39,"r");
printacharacterinanyterminallocation(18,40,"g");
printacharacterinanyterminallocation(18,41,"e");
printacharacterinanyterminallocation(18,42,"(");
printacharacterinanyterminallocation(18,43,"o");
printacharacterinanyterminallocation(18,44,"v");
printacharacterinanyterminallocation(18,45,"e");
printacharacterinanyterminallocation(18,46,"r");
printacharacterinanyterminallocation(18,47,"w");
printacharacterinanyterminallocation(18,48,"r");
printacharacterinanyterminallocation(18,49,"i");
printacharacterinanyterminallocation(18,50,"t");
printacharacterinanyterminallocation(18,51,"e");
printacharacterinanyterminallocation(18,52,")");
printacharacterinanyterminallocation(18,53,"N");
printacharacterinanyterminallocation(18,54,"e");
printacharacterinanyterminallocation(18,55,"w");
printacharacterinanyterminallocation(18,56," ");
printacharacterinanyterminallocation(18,57,"n");
printacharacterinanyterminallocation(18,58,"a");
printacharacterinanyterminallocation(18,59,"m");
printacharacterinanyterminallocation(18,60,"e");
printacharacterinanyterminallocation(18,62,"C");
printacharacterinanyterminallocation(18,63,"a");
printacharacterinanyterminallocation(18,64,"n");
printacharacterinanyterminallocation(18,65,"c");
printacharacterinanyterminallocation(18,66,"e");
printacharacterinanyterminallocation(18,67,"l");
}
}
else if (movefileoverwritedialogmode == true) {
}
else if (movedirectoryoverwritedialogmode == true) {
}
else if (deletefiledialogmode == true) {
if (xcoordinatefordeletefiledialog != 2) {
xcoordinatefordeletefiledialog++;
}
if (xcoordinatefordeletefiledialog == 1) {
printacharacterinanyterminallocation(18,30,"Y");
printacharacterinanyterminallocation(18,31,"e");
printacharacterinanyterminallocation(18,32,"s");
printacharacterinanyterminallocation(18,33," ");
printacharacterinanyterminallocation(18,34," ");
printacharacterinanyterminallocation(18,35," ");
printacharacterinanyterminallocation(18,36," ");
setBackgroundColor(3);
printacharacterinanyterminallocation(18,37,"N");
printacharacterinanyterminallocation(18,38,"o");
setBackgroundColor(1);
}
else if (xcoordinatefordeletefiledialog == 2) {
setBackgroundColor(3);
printacharacterinanyterminallocation(18,30,"Y");
printacharacterinanyterminallocation(18,31,"e");
printacharacterinanyterminallocation(18,32,"s");
setBackgroundColor(1);
printacharacterinanyterminallocation(18,33," ");
printacharacterinanyterminallocation(18,34," ");
printacharacterinanyterminallocation(18,35," ");
printacharacterinanyterminallocation(18,36," ");
printacharacterinanyterminallocation(18,37,"N");
printacharacterinanyterminallocation(18,38,"o");
}
putchar('\n');
}
else if (deletedirectorydialogmode == true) {
//std::cout << "left" << std::endl;
if (xcoordinatefordeletedirectorydialog != 2) {
xcoordinatefordeletedirectorydialog++;
}
if (xcoordinatefordeletedirectorydialog == 1) {
printacharacterinanyterminallocation(15,30,"Y");
printacharacterinanyterminallocation(15,31,"e");
printacharacterinanyterminallocation(15,32,"s");
printacharacterinanyterminallocation(15,33," ");
printacharacterinanyterminallocation(15,34," ");
printacharacterinanyterminallocation(15,35," ");
printacharacterinanyterminallocation(15,36," ");
setBackgroundColor(3);
printacharacterinanyterminallocation(15,37,"N");
printacharacterinanyterminallocation(15,38,"o");
setBackgroundColor(1);
}
else if (xcoordinatefordeletedirectorydialog == 2) {
setBackgroundColor(3);
printacharacterinanyterminallocation(15,30,"Y");
printacharacterinanyterminallocation(15,31,"e");
printacharacterinanyterminallocation(15,32,"s");
setBackgroundColor(1);
printacharacterinanyterminallocation(15,33," ");
printacharacterinanyterminallocation(15,34," ");
printacharacterinanyterminallocation(15,35," ");
printacharacterinanyterminallocation(15,36," ");
printacharacterinanyterminallocation(15,37,"N");
printacharacterinanyterminallocation(15,38,"o");
}
putchar('\n');
}
else if (newfolderdialogmode == true) {
setBackgroundColor(3);
printacharacterinanyterminallocation(16,31,"C");
printacharacterinanyterminallocation(16,32,"a");
printacharacterinanyterminallocation(16,33,"n");
printacharacterinanyterminallocation(16,34,"c");
printacharacterinanyterminallocation(16,35,"e");
printacharacterinanyterminallocation(16,36,"l");
setBackgroundColor(2);
printacharacterinanyterminallocation(16,37," ");
printacharacterinanyterminallocation(16,38," ");
printacharacterinanyterminallocation(16,39," ");
printacharacterinanyterminallocation(16,40,"O");
printacharacterinanyterminallocation(16,41,"K");
ycoordinatefornewfolderdialog = 1;
putchar('\n');
}
else if (newnamedialogmode == true) {
setBackgroundColor(3);
printacharacterinanyterminallocation(16,31,"C");
printacharacterinanyterminallocation(16,32,"a");
printacharacterinanyterminallocation(16,33,"n");
printacharacterinanyterminallocation(16,34,"c");
printacharacterinanyterminallocation(16,35,"e");
printacharacterinanyterminallocation(16,36,"l");
setBackgroundColor(2);
printacharacterinanyterminallocation(16,37," ");
printacharacterinanyterminallocation(16,38," ");
printacharacterinanyterminallocation(16,39," ");
printacharacterinanyterminallocation(16,40,"O");
printacharacterinanyterminallocation(16,41,"K");
ycoordinatefornewnamedialog = 1;
putchar('\n');
}
else if (renamedialogmode == true) {
setBackgroundColor(3);
printacharacterinanyterminallocation(16,31,"C");
printacharacterinanyterminallocation(16,32,"a");
printacharacterinanyterminallocation(16,33,"n");
printacharacterinanyterminallocation(16,34,"c");
printacharacterinanyterminallocation(16,35,"e");
printacharacterinanyterminallocation(16,36,"l");
setBackgroundColor(2);
printacharacterinanyterminallocation(16,37," ");
printacharacterinanyterminallocation(16,38," ");
printacharacterinanyterminallocation(16,39," ");
printacharacterinanyterminallocation(16,40,"O");
printacharacterinanyterminallocation(16,41,"K");
ycoordinatefornewfolderdialog = 1;
putchar('\n');
}
}
if (ch1 == '' && ch2 == '[' && ch3 == 'C') {
if (menubarmode == false && copyfileoverwritedialogmode == false && copydirectoryoverwritedialogmode == false && movefileoverwritedialogmode == false && movedirectoryoverwritedialogmode == false && deletefiledialogmode == false && deletedirectorydialogmode == false && newfolderdialogmode == false && renamedialogmode == false && newnamedialogmode == false) {
//std::cout << driveslistingscount << "-" << ycoordinate << "-" << countformovingdownindrivesbox;
//cleandrivesbox();
//std::cout << "right";
//putchar('\n');
if (xcoordinate != 2) {
xcoordinate++;
//xcoordinate = 3;
ycoordinate = 3;
driveslistingscount = 0;
countformovingdownindrivesbox = 0;
filenamelistingscount = 0;
drawdrivesbox();
drawfilesbox();
drawingoffilesboxdone = false;
}
}
else if (copyfileoverwritedialogmode == true) {
if (coordinateforcopyexistingfiledialog != 0) {
coordinateforcopyexistingfiledialog--;
}
if (coordinateforcopyexistingfiledialog == 2) {
setBackgroundColor(3);
printacharacterinanyterminallocation(18,15,"O");
printacharacterinanyterminallocation(18,16,"v");
printacharacterinanyterminallocation(18,17,"e");
printacharacterinanyterminallocation(18,18,"r");
printacharacterinanyterminallocation(18,19,"w");
printacharacterinanyterminallocation(18,20,"r");
printacharacterinanyterminallocation(18,21,"i");
printacharacterinanyterminallocation(18,22,"t");
printacharacterinanyterminallocation(18,23,"e");
setBackgroundColor(1);
printacharacterinanyterminallocation(18,24," ");
printacharacterinanyterminallocation(18,25," ");
printacharacterinanyterminallocation(18,26," ");
printacharacterinanyterminallocation(18,27," ");
printacharacterinanyterminallocation(18,28,"N");
printacharacterinanyterminallocation(18,29,"e");
printacharacterinanyterminallocation(18,30,"w");
printacharacterinanyterminallocation(18,31," ");
printacharacterinanyterminallocation(18,32,"n");
printacharacterinanyterminallocation(18,33,"a");
printacharacterinanyterminallocation(18,34,"m");
printacharacterinanyterminallocation(18,35,"e");
printacharacterinanyterminallocation(18,36," ");
printacharacterinanyterminallocation(18,37," ");
printacharacterinanyterminallocation(18,38," ");
printacharacterinanyterminallocation(18,39," ");
printacharacterinanyterminallocation(18,40,"C");
printacharacterinanyterminallocation(18,41,"a");
printacharacterinanyterminallocation(18,42,"n");
printacharacterinanyterminallocation(18,43,"c");
printacharacterinanyterminallocation(18,44,"e");
printacharacterinanyterminallocation(18,45,"l");
}
else if (coordinateforcopyexistingfiledialog == 1) {
printacharacterinanyterminallocation(18,15,"O");
printacharacterinanyterminallocation(18,16,"v");
printacharacterinanyterminallocation(18,17,"e");
printacharacterinanyterminallocation(18,18,"r");
printacharacterinanyterminallocation(18,19,"w");
printacharacterinanyterminallocation(18,20,"r");
printacharacterinanyterminallocation(18,21,"i");
printacharacterinanyterminallocation(18,22,"t");
printacharacterinanyterminallocation(18,23,"e");
printacharacterinanyterminallocation(18,24," ");
printacharacterinanyterminallocation(18,25," ");
printacharacterinanyterminallocation(18,26," ");
printacharacterinanyterminallocation(18,27," ");
setBackgroundColor(3);
printacharacterinanyterminallocation(18,28,"N");
printacharacterinanyterminallocation(18,29,"e");
printacharacterinanyterminallocation(18,30,"w");
printacharacterinanyterminallocation(18,31," ");
printacharacterinanyterminallocation(18,32,"n");
printacharacterinanyterminallocation(18,33,"a");
printacharacterinanyterminallocation(18,34,"m");
printacharacterinanyterminallocation(18,35,"e");
setBackgroundColor(1);
printacharacterinanyterminallocation(18,36," ");
printacharacterinanyterminallocation(18,37," ");
printacharacterinanyterminallocation(18,38," ");
printacharacterinanyterminallocation(18,39," ");
printacharacterinanyterminallocation(18,40,"C");
printacharacterinanyterminallocation(18,41,"a");
printacharacterinanyterminallocation(18,42,"n");
printacharacterinanyterminallocation(18,43,"c");
printacharacterinanyterminallocation(18,44,"e");
printacharacterinanyterminallocation(18,45,"l");
}
else if (coordinateforcopyexistingfiledialog == 0) {
printacharacterinanyterminallocation(18,15,"O");
printacharacterinanyterminallocation(18,16,"v");
printacharacterinanyterminallocation(18,17,"e");
printacharacterinanyterminallocation(18,18,"r");
printacharacterinanyterminallocation(18,19,"w");
printacharacterinanyterminallocation(18,20,"r");
printacharacterinanyterminallocation(18,21,"i");
printacharacterinanyterminallocation(18,22,"t");
printacharacterinanyterminallocation(18,23,"e");
printacharacterinanyterminallocation(18,24," ");
printacharacterinanyterminallocation(18,25," ");
printacharacterinanyterminallocation(18,26," ");
printacharacterinanyterminallocation(18,27," ");
printacharacterinanyterminallocation(18,28,"N");
printacharacterinanyterminallocation(18,29,"e");
printacharacterinanyterminallocation(18,30,"w");
printacharacterinanyterminallocation(18,31," ");
printacharacterinanyterminallocation(18,32,"n");
printacharacterinanyterminallocation(18,33,"a");
printacharacterinanyterminallocation(18,34,"m");
printacharacterinanyterminallocation(18,35,"e");
printacharacterinanyterminallocation(18,36," ");
printacharacterinanyterminallocation(18,37," ");
printacharacterinanyterminallocation(18,38," ");
printacharacterinanyterminallocation(18,39," ");
setBackgroundColor(3);
printacharacterinanyterminallocation(18,40,"C");
printacharacterinanyterminallocation(18,41,"a");
printacharacterinanyterminallocation(18,42,"n");
printacharacterinanyterminallocation(18,43,"c");
printacharacterinanyterminallocation(18,44,"e");
printacharacterinanyterminallocation(18,45,"l");
setBackgroundColor(1);
}
putchar('\n');
}
else if (copydirectoryoverwritedialogmode == true) {
if (ycoordinateforcopydirectoryoverwritedialog != 0) {
ycoordinateforcopydirectoryoverwritedialog--;
}
if (ycoordinateforcopydirectoryoverwritedialog == 0) {
printacharacterinanyterminallocation(18,15,"O");
printacharacterinanyterminallocation(18,16,"v");
printacharacterinanyterminallocation(18,17,"e");
printacharacterinanyterminallocation(18,18,"r");
printacharacterinanyterminallocation(18,19,"w");
printacharacterinanyterminallocation(18,20,"r");
printacharacterinanyterminallocation(18,21,"i");
printacharacterinanyterminallocation(18,22,"t");
printacharacterinanyterminallocation(18,23,"e");
printacharacterinanyterminallocation(18,24," ");
printacharacterinanyterminallocation(18,25," ");
printacharacterinanyterminallocation(18,26," ");
printacharacterinanyterminallocation(18,27," ");
printacharacterinanyterminallocation(18,28,"M");
printacharacterinanyterminallocation(18,29,"e");
printacharacterinanyterminallocation(18,30,"r");
printacharacterinanyterminallocation(18,31,"g");
printacharacterinanyterminallocation(18,32,"e");
printacharacterinanyterminallocation(18,33," ");
printacharacterinanyterminallocation(18,34," ");
printacharacterinanyterminallocation(18,35," ");
printacharacterinanyterminallocation(18,36," ");
printacharacterinanyterminallocation(18,37,"M");
printacharacterinanyterminallocation(18,38,"e");
printacharacterinanyterminallocation(18,39,"r");
printacharacterinanyterminallocation(18,40,"g");
printacharacterinanyterminallocation(18,41,"e");
printacharacterinanyterminallocation(18,42,"(");
printacharacterinanyterminallocation(18,43,"o");
printacharacterinanyterminallocation(18,44,"v");
printacharacterinanyterminallocation(18,45,"e");
printacharacterinanyterminallocation(18,46,"r");
printacharacterinanyterminallocation(18,47,"w");
printacharacterinanyterminallocation(18,48,"r");
printacharacterinanyterminallocation(18,49,"i");
printacharacterinanyterminallocation(18,50,"t");
printacharacterinanyterminallocation(18,51,"e");
printacharacterinanyterminallocation(18,52,")");
printacharacterinanyterminallocation(18,53,"N");
printacharacterinanyterminallocation(18,54,"e");
printacharacterinanyterminallocation(18,55,"w");
printacharacterinanyterminallocation(18,56," ");
printacharacterinanyterminallocation(18,57,"n");
printacharacterinanyterminallocation(18,58,"a");
printacharacterinanyterminallocation(18,59,"m");
printacharacterinanyterminallocation(18,60,"e");
setBackgroundColor(3);
printacharacterinanyterminallocation(18,62,"C");
printacharacterinanyterminallocation(18,63,"a");
printacharacterinanyterminallocation(18,64,"n");
printacharacterinanyterminallocation(18,65,"c");
printacharacterinanyterminallocation(18,66,"e");
printacharacterinanyterminallocation(18,67,"l");
setBackgroundColor(1);
}
else if (ycoordinateforcopydirectoryoverwritedialog == 1) {
printacharacterinanyterminallocation(18,15,"O");
printacharacterinanyterminallocation(18,16,"v");
printacharacterinanyterminallocation(18,17,"e");
printacharacterinanyterminallocation(18,18,"r");
printacharacterinanyterminallocation(18,19,"w");
printacharacterinanyterminallocation(18,20,"r");
printacharacterinanyterminallocation(18,21,"i");
printacharacterinanyterminallocation(18,22,"t");
printacharacterinanyterminallocation(18,23,"e");
printacharacterinanyterminallocation(18,24," ");
printacharacterinanyterminallocation(18,25," ");
printacharacterinanyterminallocation(18,26," ");
printacharacterinanyterminallocation(18,27," ");
printacharacterinanyterminallocation(18,28,"M");
printacharacterinanyterminallocation(18,29,"e");
printacharacterinanyterminallocation(18,30,"r");
printacharacterinanyterminallocation(18,31,"g");
printacharacterinanyterminallocation(18,32,"e");
printacharacterinanyterminallocation(18,33," ");
printacharacterinanyterminallocation(18,34," ");
printacharacterinanyterminallocation(18,35," ");
printacharacterinanyterminallocation(18,36," ");
printacharacterinanyterminallocation(18,37,"M");
printacharacterinanyterminallocation(18,38,"e");
printacharacterinanyterminallocation(18,39,"r");
printacharacterinanyterminallocation(18,40,"g");
printacharacterinanyterminallocation(18,41,"e");
printacharacterinanyterminallocation(18,42,"(");
printacharacterinanyterminallocation(18,43,"o");
printacharacterinanyterminallocation(18,44,"v");
printacharacterinanyterminallocation(18,45,"e");
printacharacterinanyterminallocation(18,46,"r");
printacharacterinanyterminallocation(18,47,"w");
printacharacterinanyterminallocation(18,48,"r");
printacharacterinanyterminallocation(18,49,"i");
printacharacterinanyterminallocation(18,50,"t");
printacharacterinanyterminallocation(18,51,"e");
printacharacterinanyterminallocation(18,52,")");
setBackgroundColor(3);
printacharacterinanyterminallocation(18,53,"N");
printacharacterinanyterminallocation(18,54,"e");
printacharacterinanyterminallocation(18,55,"w");
printacharacterinanyterminallocation(18,56," ");
printacharacterinanyterminallocation(18,57,"n");
printacharacterinanyterminallocation(18,58,"a");
printacharacterinanyterminallocation(18,59,"m");
printacharacterinanyterminallocation(18,60,"e");
setBackgroundColor(1);
printacharacterinanyterminallocation(18,62,"C");
printacharacterinanyterminallocation(18,63,"a");
printacharacterinanyterminallocation(18,64,"n");
printacharacterinanyterminallocation(18,65,"c");
printacharacterinanyterminallocation(18,66,"e");
printacharacterinanyterminallocation(18,67,"l");
}
else if (ycoordinateforcopydirectoryoverwritedialog == 2) {
printacharacterinanyterminallocation(18,15,"O");
printacharacterinanyterminallocation(18,16,"v");
printacharacterinanyterminallocation(18,17,"e");
printacharacterinanyterminallocation(18,18,"r");
printacharacterinanyterminallocation(18,19,"w");
printacharacterinanyterminallocation(18,20,"r");
printacharacterinanyterminallocation(18,21,"i");
printacharacterinanyterminallocation(18,22,"t");
printacharacterinanyterminallocation(18,23,"e");
printacharacterinanyterminallocation(18,24," ");
printacharacterinanyterminallocation(18,25," ");
printacharacterinanyterminallocation(18,26," ");
printacharacterinanyterminallocation(18,27," ");
printacharacterinanyterminallocation(18,28,"M");
printacharacterinanyterminallocation(18,29,"e");
printacharacterinanyterminallocation(18,30,"r");
printacharacterinanyterminallocation(18,31,"g");
printacharacterinanyterminallocation(18,32,"e");
printacharacterinanyterminallocation(18,33," ");
printacharacterinanyterminallocation(18,34," ");
printacharacterinanyterminallocation(18,35," ");
printacharacterinanyterminallocation(18,36," ");
setBackgroundColor(3);
printacharacterinanyterminallocation(18,37,"M");
printacharacterinanyterminallocation(18,38,"e");
printacharacterinanyterminallocation(18,39,"r");
printacharacterinanyterminallocation(18,40,"g");
printacharacterinanyterminallocation(18,41,"e");
printacharacterinanyterminallocation(18,42,"(");
printacharacterinanyterminallocation(18,43,"o");
printacharacterinanyterminallocation(18,44,"v");
printacharacterinanyterminallocation(18,45,"e");
printacharacterinanyterminallocation(18,46,"r");
printacharacterinanyterminallocation(18,47,"w");
printacharacterinanyterminallocation(18,48,"r");
printacharacterinanyterminallocation(18,49,"i");
printacharacterinanyterminallocation(18,50,"t");
printacharacterinanyterminallocation(18,51,"e");
printacharacterinanyterminallocation(18,52,")");
setBackgroundColor(1);
printacharacterinanyterminallocation(18,53,"N");
printacharacterinanyterminallocation(18,54,"e");
printacharacterinanyterminallocation(18,55,"w");
printacharacterinanyterminallocation(18,56," ");
printacharacterinanyterminallocation(18,57,"n");
printacharacterinanyterminallocation(18,58,"a");
printacharacterinanyterminallocation(18,59,"m");
printacharacterinanyterminallocation(18,60,"e");
printacharacterinanyterminallocation(18,62,"C");
printacharacterinanyterminallocation(18,63,"a");
printacharacterinanyterminallocation(18,64,"n");
printacharacterinanyterminallocation(18,65,"c");
printacharacterinanyterminallocation(18,66,"e");
printacharacterinanyterminallocation(18,67,"l");
}
else if (ycoordinateforcopydirectoryoverwritedialog == 3) {
printacharacterinanyterminallocation(18,15,"O");
printacharacterinanyterminallocation(18,16,"v");
printacharacterinanyterminallocation(18,17,"e");
printacharacterinanyterminallocation(18,18,"r");
printacharacterinanyterminallocation(18,19,"w");
printacharacterinanyterminallocation(18,20,"r");
printacharacterinanyterminallocation(18,21,"i");
printacharacterinanyterminallocation(18,22,"t");
printacharacterinanyterminallocation(18,23,"e");
printacharacterinanyterminallocation(18,24," ");
printacharacterinanyterminallocation(18,25," ");
printacharacterinanyterminallocation(18,26," ");
printacharacterinanyterminallocation(18,27," ");
setBackgroundColor(3);
printacharacterinanyterminallocation(18,28,"M");
printacharacterinanyterminallocation(18,29,"e");
printacharacterinanyterminallocation(18,30,"r");
printacharacterinanyterminallocation(18,31,"g");
printacharacterinanyterminallocation(18,32,"e");
setBackgroundColor(1);
printacharacterinanyterminallocation(18,33," ");
printacharacterinanyterminallocation(18,34," ");
printacharacterinanyterminallocation(18,35," ");
printacharacterinanyterminallocation(18,36," ");
printacharacterinanyterminallocation(18,37,"M");
printacharacterinanyterminallocation(18,38,"e");
printacharacterinanyterminallocation(18,39,"r");
printacharacterinanyterminallocation(18,40,"g");
printacharacterinanyterminallocation(18,41,"e");
printacharacterinanyterminallocation(18,42,"(");
printacharacterinanyterminallocation(18,43,"o");
printacharacterinanyterminallocation(18,44,"v");
printacharacterinanyterminallocation(18,45,"e");
printacharacterinanyterminallocation(18,46,"r");
printacharacterinanyterminallocation(18,47,"w");
printacharacterinanyterminallocation(18,48,"r");
printacharacterinanyterminallocation(18,49,"i");
printacharacterinanyterminallocation(18,50,"t");
printacharacterinanyterminallocation(18,51,"e");
printacharacterinanyterminallocation(18,52,")");
printacharacterinanyterminallocation(18,53,"N");
printacharacterinanyterminallocation(18,54,"e");
printacharacterinanyterminallocation(18,55,"w");
printacharacterinanyterminallocation(18,56," ");
printacharacterinanyterminallocation(18,57,"n");
printacharacterinanyterminallocation(18,58,"a");
printacharacterinanyterminallocation(18,59,"m");
printacharacterinanyterminallocation(18,60,"e");
printacharacterinanyterminallocation(18,62,"C");
printacharacterinanyterminallocation(18,63,"a");
printacharacterinanyterminallocation(18,64,"n");
printacharacterinanyterminallocation(18,65,"c");
printacharacterinanyterminallocation(18,66,"e");
printacharacterinanyterminallocation(18,67,"l");
}
else if (ycoordinateforcopydirectoryoverwritedialog == 4) {
setBackgroundColor(3);
printacharacterinanyterminallocation(18,15,"O");
printacharacterinanyterminallocation(18,16,"v");
printacharacterinanyterminallocation(18,17,"e");
printacharacterinanyterminallocation(18,18,"r");
printacharacterinanyterminallocation(18,19,"w");
printacharacterinanyterminallocation(18,20,"r");
printacharacterinanyterminallocation(18,21,"i");
printacharacterinanyterminallocation(18,22,"t");
printacharacterinanyterminallocation(18,23,"e");
setBackgroundColor(1);
printacharacterinanyterminallocation(18,24," ");
printacharacterinanyterminallocation(18,25," ");
printacharacterinanyterminallocation(18,26," ");
printacharacterinanyterminallocation(18,27," ");
printacharacterinanyterminallocation(18,28,"M");
printacharacterinanyterminallocation(18,29,"e");
printacharacterinanyterminallocation(18,30,"r");
printacharacterinanyterminallocation(18,31,"g");
printacharacterinanyterminallocation(18,32,"e");
printacharacterinanyterminallocation(18,33," ");
printacharacterinanyterminallocation(18,34," ");
printacharacterinanyterminallocation(18,35," ");
printacharacterinanyterminallocation(18,36," ");
printacharacterinanyterminallocation(18,37,"M");
printacharacterinanyterminallocation(18,38,"e");
printacharacterinanyterminallocation(18,39,"r");
printacharacterinanyterminallocation(18,40,"g");
printacharacterinanyterminallocation(18,41,"e");
printacharacterinanyterminallocation(18,42,"(");
printacharacterinanyterminallocation(18,43,"o");
printacharacterinanyterminallocation(18,44,"v");
printacharacterinanyterminallocation(18,45,"e");
printacharacterinanyterminallocation(18,46,"r");
printacharacterinanyterminallocation(18,47,"w");
printacharacterinanyterminallocation(18,48,"r");
printacharacterinanyterminallocation(18,49,"i");
printacharacterinanyterminallocation(18,50,"t");
printacharacterinanyterminallocation(18,51,"e");
printacharacterinanyterminallocation(18,52,")");
printacharacterinanyterminallocation(18,53,"N");
printacharacterinanyterminallocation(18,54,"e");
printacharacterinanyterminallocation(18,55,"w");
printacharacterinanyterminallocation(18,56," ");
printacharacterinanyterminallocation(18,57,"n");
printacharacterinanyterminallocation(18,58,"a");
printacharacterinanyterminallocation(18,59,"m");
printacharacterinanyterminallocation(18,60,"e");
printacharacterinanyterminallocation(18,62,"C");
printacharacterinanyterminallocation(18,63,"a");
printacharacterinanyterminallocation(18,64,"n");
printacharacterinanyterminallocation(18,65,"c");
printacharacterinanyterminallocation(18,66,"e");
printacharacterinanyterminallocation(18,67,"l");
}
}
else if (movefileoverwritedialogmode == true) {
}
else if (movedirectoryoverwritedialogmode == true) {
}
else if (deletefiledialogmode == true) {
if (xcoordinatefordeletefiledialog != 1) {
xcoordinatefordeletefiledialog--;
}
if (xcoordinatefordeletefiledialog == 1) {
printacharacterinanyterminallocation(18,30,"Y");
printacharacterinanyterminallocation(18,31,"e");
printacharacterinanyterminallocation(18,32,"s");
printacharacterinanyterminallocation(18,33," ");
printacharacterinanyterminallocation(18,34," ");
printacharacterinanyterminallocation(18,35," ");
printacharacterinanyterminallocation(18,36," ");
setBackgroundColor(3);
printacharacterinanyterminallocation(18,37,"N");
printacharacterinanyterminallocation(18,38,"o");
setBackgroundColor(1);
}
else if (xcoordinatefordeletefiledialog == 2) {
setBackgroundColor(3);
printacharacterinanyterminallocation(18,30,"Y");
printacharacterinanyterminallocation(18,31,"e");
printacharacterinanyterminallocation(18,32,"s");
setBackgroundColor(1);
printacharacterinanyterminallocation(18,33," ");
printacharacterinanyterminallocation(18,34," ");
printacharacterinanyterminallocation(18,35," ");
printacharacterinanyterminallocation(18,36," ");
printacharacterinanyterminallocation(18,37,"N");
printacharacterinanyterminallocation(18,38,"o");
}
putchar('\n');
}
else if (deletedirectorydialogmode == true) {
//std::cout << "right" << std::endl;
if (xcoordinatefordeletedirectorydialog != 1) {
xcoordinatefordeletedirectorydialog--;
}
if (xcoordinatefordeletedirectorydialog == 1) {
printacharacterinanyterminallocation(15,30,"Y");
printacharacterinanyterminallocation(15,31,"e");
printacharacterinanyterminallocation(15,32,"s");
printacharacterinanyterminallocation(15,33," ");
printacharacterinanyterminallocation(15,34," ");
printacharacterinanyterminallocation(15,35," ");
printacharacterinanyterminallocation(15,36," ");
setBackgroundColor(3);
printacharacterinanyterminallocation(15,37,"N");
printacharacterinanyterminallocation(15,38,"o");
setBackgroundColor(1);
}
else if (xcoordinatefordeletedirectorydialog == 2) {
setBackgroundColor(3);
printacharacterinanyterminallocation(15,30,"Y");
printacharacterinanyterminallocation(15,31,"e");
printacharacterinanyterminallocation(15,32,"s");
setBackgroundColor(1);
printacharacterinanyterminallocation(15,33," ");
printacharacterinanyterminallocation(15,34," ");
printacharacterinanyterminallocation(15,35," ");
printacharacterinanyterminallocation(15,36," ");
printacharacterinanyterminallocation(15,37,"N");
printacharacterinanyterminallocation(15,38,"o");
}
putchar('\n');
}
else if (newfolderdialogmode == true) {
printacharacterinanyterminallocation(16,31,"C");
printacharacterinanyterminallocation(16,32,"a");
printacharacterinanyterminallocation(16,33,"n");
printacharacterinanyterminallocation(16,34,"c");
printacharacterinanyterminallocation(16,35,"e");
printacharacterinanyterminallocation(16,36,"l");
printacharacterinanyterminallocation(16,37," ");
printacharacterinanyterminallocation(16,38," ");
printacharacterinanyterminallocation(16,39," ");
setBackgroundColor(3);
printacharacterinanyterminallocation(16,40,"O");
printacharacterinanyterminallocation(16,41,"K");
setBackgroundColor(2);
ycoordinatefornewfolderdialog = 2;
putchar('\n');
}
else if (newnamedialogmode == true) {
printacharacterinanyterminallocation(16,31,"C");
printacharacterinanyterminallocation(16,32,"a");
printacharacterinanyterminallocation(16,33,"n");
printacharacterinanyterminallocation(16,34,"c");
printacharacterinanyterminallocation(16,35,"e");
printacharacterinanyterminallocation(16,36,"l");
printacharacterinanyterminallocation(16,37," ");
printacharacterinanyterminallocation(16,38," ");
printacharacterinanyterminallocation(16,39," ");
setBackgroundColor(3);
printacharacterinanyterminallocation(16,40,"O");
printacharacterinanyterminallocation(16,41,"K");
setBackgroundColor(2);
ycoordinatefornewnamedialog = 2;
putchar('\n');
}
else if (renamedialogmode == true) {
printacharacterinanyterminallocation(16,31,"C");
printacharacterinanyterminallocation(16,32,"a");
printacharacterinanyterminallocation(16,33,"n");
printacharacterinanyterminallocation(16,34,"c");
printacharacterinanyterminallocation(16,35,"e");
printacharacterinanyterminallocation(16,36,"l");
printacharacterinanyterminallocation(16,37," ");
printacharacterinanyterminallocation(16,38," ");
printacharacterinanyterminallocation(16,39," ");
setBackgroundColor(3);
printacharacterinanyterminallocation(16,40,"O");
printacharacterinanyterminallocation(16,41,"K");
setBackgroundColor(2);
ycoordinatefornewfolderdialog = 2;
putchar('\n');
}
else if (menubarmode == true) {
drawdrivesbox();
setBackgroundColor(3);
printacharacterinanyterminallocation(1,6,"A");
printacharacterinanyterminallocation(1,7,"b");
printacharacterinanyterminallocation(1,8,"o");
printacharacterinanyterminallocation(1,9,"u");
printacharacterinanyterminallocation(1,10,"t");
setBackgroundColor(2);
}
}
}
else if (byteswaiting == 4) {
//std::cout << "byteswaiting:" << byteswaiting << std::endl;
char ch1 = getchar();
char ch2 = getchar();
char ch3 = getchar();
char ch4 = getchar();
std::ofstream archivo;
archivo.open("/home/jesus/Desktop/codigo.txt");
archivo << ch1;
archivo << ch2;
archivo << ch3;
archivo << ch4;
archivo.close();
if (ch1 == '' && ch2 == '[' && ch3 == '5' && ch4 == '~') {
//std::cout << "test1234" << std::endl;
if (xcoordinate == 1 && menubarmode == false) {
if (driveslistings.size() > rows / 2 - 4) {
if (scrolldownsindrivesbox != 0) {
scrolldownsindrivesbox--;
}
if (driveslistingscount != 0) {
setBackgroundColor(4);
if (countformovingdownindrivesbox != 0) {
driveslistingscount = driveslistingscount - countformovingdownindrivesbox;
ycoordinate = 3;
countformovingdownindrivesbox = 0;
}
int substraction = rows / 2 - 4;
driveslistingscount = driveslistingscount - substraction;
drawdrivesbox(0,driveslistingscount,1);
drawfilesbox();
drawpreviewbox();
menubar();
//std::cout << "scroll up";
}
}
}
else if (xcoordinate == 2 && menubarmode == false) {
if (filenamelistings.size() > rows / 2 - 4) {
if (scrolldownsinfilesbox != 0) {
scrolldownsinfilesbox--;
}
if (filenamelistingscount != 0) {
setBackgroundColor(4);
cleandrivesbox();
if (countformovingdowninfilesbox != 0) {
filenamelistingscount = filenamelistingscount - countformovingdowninfilesbox;
ycoordinate = 3;
countformovingdowninfilesbox = 0;
}
int substraction = rows / 2 - 4;
filenamelistingscount = filenamelistingscount - substraction;
if (filenamelistingscount <= -1) {
filenamelistingscount = 0;
}
cleanfilesbox();
drawfilesbox(0,filenamelistingscount,1);
if (filenamelistingscount <= -1) {
filenamelistingscount = 0;
}
cleanscrollbarforfilesbox();
drawscrollbarforfilesbox();
drawpreviewbox();
menubar();
//std::cout << "scroll up";
}
}
}
}
if (ch1 == '' && ch2 == '[' && ch3 == '6' && ch4 == '~') {
if (xcoordinate == 1 && menubarmode == false) {
if (driveslistings.size() > rows / 2 - 4) {
if (scrolldownsindrivesbox != 0) {
scrolldownsindrivesbox++;
}
if (driveslistingscount != 0) {
setBackgroundColor(4);
if (countformovingdownindrivesbox != 0) {
driveslistingscount = driveslistingscount + countformovingdownindrivesbox;
ycoordinate = 3;
countformovingdownindrivesbox = 0;
}
int addition = rows / 2 - 4;
driveslistingscount = driveslistingscount + addition;
drawdrivesbox(0,driveslistingscount,1);
drawfilesbox();
drawpreviewbox();
menubar();
//std::cout << "scroll up";
}
}
}
else if (xcoordinate == 2 && menubarmode == false) {
//if (filenamelistings.size() > rows / 2 - 4) {
//if (scrolldownsinfilesbox != 0) {
//scrolldownsinfilesbox++;
//}
//if (filenamelistingscount != 0) {
//setBackgroundColor(4);
//cleandrivesbox();
//if (countformovingdowninfilesbox != 0) {
//filenamelistingscount = filenamelistingscount + countformovingdowninfilesbox;
//ycoordinate = 3;
//countformovingdowninfilesbox = 0;
//}
int addition = rows / 2 - 4;
filenamelistingscount = filenamelistingscount + addition;
if (filenamelistingscount > filenamelistings.size()) {
filenamelistingscount = filenamelistings.size() - addition;
}
cleanfilesbox();
drawfilesbox(1,filenamelistingscount,0);
if (filenamelistingscount > filenamelistings.size()) {
filenamelistingscount = filenamelistings.size() - addition;
}
cleanscrollbarforfilesbox();
drawscrollbarforfilesbox();
drawpreviewbox();
menubar();
//std::cout << "scroll up";
}
}
if (ch1 == '' && ch2 == '[' && ch3 == '3' && ch4 == '~') {
if (xcoordinate == 2) {
movecursortoanyterminallocation(13,1);
std::cout << "Delete key pressed!" << std::endl;
if (!std::filesystem::is_directory(filenamelistings[filenamelistingscount].filename)) {
deletefiledialogmode = true;
showdeletefiledialog();
}
else if (std::filesystem::is_directory(filenamelistings[filenamelistingscount].filename)) {
deletedirectorydialogmode = true;
showdeletedirectorydialog();
}
}
}
}
else if (byteswaiting == 5) {
//std::cout << "byteswaiting:" << byteswaiting << std::endl;
char ch1 = getchar();
char ch2 = getchar();
char ch3 = getchar();
char ch4 = getchar();
char ch5 = getchar();
std::ofstream archivo;
archivo.open("/home/jesus/Documents/codigo.txt");
archivo << ch1;
archivo << ch2;
archivo << ch3;
archivo << ch4;
archivo << ch5;
archivo.close();
if (ch1 == '' && ch2 == '[' && ch3 == '2' && ch4 == '1' && ch5 == '~' || ch1 == '' && ch2 == '[' && ch3 == '2' && ch4 == '0' && ch5 == '~') {
std::cout << "F10 or F9 key pressed" << std::endl;
if (menubarmode == false && xcoordinate == 2 && copyfileoverwritedialogmode == false && copydirectoryoverwritedialogmode == false && movefileoverwritedialogmode == false && movedirectoryoverwritedialogmode == false && deletefiledialogmode == false && deletedirectorydialogmode == false && newfolderdialogmode == false) {
menubarmode = true;
setBackgroundColor(2);
printacharacterinanyterminallocation(2,1,"┌");
printacharacterinanyterminallocation(3,1,"│");
printacharacterinanyterminallocation(4,1,"│");
printacharacterinanyterminallocation(5,1,"│");
printacharacterinanyterminallocation(6,1,"│");
printacharacterinanyterminallocation(7,1,"│");
printacharacterinanyterminallocation(8,1,"│");
printacharacterinanyterminallocation(9,1,"│");
printacharacterinanyterminallocation(10,1,"└");
printacharacterinanyterminallocation(10,2,"─");
printacharacterinanyterminallocation(10,3,"─");
printacharacterinanyterminallocation(10,4,"─");
printacharacterinanyterminallocation(10,5,"─");
printacharacterinanyterminallocation(10,6,"─");
printacharacterinanyterminallocation(10,7,"─");
printacharacterinanyterminallocation(10,8,"─");
printacharacterinanyterminallocation(10,9,"─");
printacharacterinanyterminallocation(10,10,"─");
printacharacterinanyterminallocation(10,11,"─");
printacharacterinanyterminallocation(10,12,"─");
printacharacterinanyterminallocation(10,13,"─");
printacharacterinanyterminallocation(10,14,"─");
printacharacterinanyterminallocation(10,15,"─");
printacharacterinanyterminallocation(10,16,"─");
printacharacterinanyterminallocation(10,17,"─");
printacharacterinanyterminallocation(10,18,"─");
printacharacterinanyterminallocation(10,19,"─");
printacharacterinanyterminallocation(10,20,"─");
printacharacterinanyterminallocation(10,21,"─");
printacharacterinanyterminallocation(10,22,"─");
printacharacterinanyterminallocation(10,23,"─");
printacharacterinanyterminallocation(10,24,"─");
printacharacterinanyterminallocation(10,25,"┘");
printacharacterinanyterminallocation(3,25,"│");
printacharacterinanyterminallocation(4,25,"│");
printacharacterinanyterminallocation(5,25,"│");
printacharacterinanyterminallocation(6,25,"│");
printacharacterinanyterminallocation(7,25,"│");
printacharacterinanyterminallocation(8,25,"│");
printacharacterinanyterminallocation(9,25,"│");
printacharacterinanyterminallocation(2,25,"┐");
printacharacterinanyterminallocation(2,24,"─");
printacharacterinanyterminallocation(2,23,"─");
printacharacterinanyterminallocation(2,22,"─");
printacharacterinanyterminallocation(2,21,"─");
printacharacterinanyterminallocation(2,20,"─");
printacharacterinanyterminallocation(2,19,"─");
printacharacterinanyterminallocation(2,18,"─");
printacharacterinanyterminallocation(2,17,"─");
printacharacterinanyterminallocation(2,16,"─");
printacharacterinanyterminallocation(2,15,"─");
printacharacterinanyterminallocation(2,14,"─");
printacharacterinanyterminallocation(2,13,"─");
printacharacterinanyterminallocation(2,12,"─");
printacharacterinanyterminallocation(2,11,"─");
printacharacterinanyterminallocation(2,10,"─");
printacharacterinanyterminallocation(2,9,"─");
printacharacterinanyterminallocation(2,8,"─");
printacharacterinanyterminallocation(2,7,"─");
printacharacterinanyterminallocation(2,6,"─");
printacharacterinanyterminallocation(2,5,"─");
printacharacterinanyterminallocation(2,4,"─");
printacharacterinanyterminallocation(2,3,"─");
printacharacterinanyterminallocation(2,2,"─");
setBackgroundColor(3);
printacharacterinanyterminallocation(3,2,"C");
printacharacterinanyterminallocation(3,3,"u");
printacharacterinanyterminallocation(3,4,"t");
printacharacterinanyterminallocation(3,5," ");
printacharacterinanyterminallocation(3,6," ");
printacharacterinanyterminallocation(3,7," ");
printacharacterinanyterminallocation(3,8," ");
printacharacterinanyterminallocation(3,9," ");
printacharacterinanyterminallocation(3,10," ");
printacharacterinanyterminallocation(3,11," ");
printacharacterinanyterminallocation(3,12," ");
printacharacterinanyterminallocation(3,13," ");
printacharacterinanyterminallocation(3,14," ");
printacharacterinanyterminallocation(3,15," ");
printacharacterinanyterminallocation(3,16," ");
printacharacterinanyterminallocation(3,17," ");
printacharacterinanyterminallocation(3,18," ");
printacharacterinanyterminallocation(3,19," ");
printacharacterinanyterminallocation(3,20," ");
printacharacterinanyterminallocation(3,21," ");
printacharacterinanyterminallocation(3,22," ");
printacharacterinanyterminallocation(3,23," ");
printacharacterinanyterminallocation(3,24," ");
setBackgroundColor(2);
printacharacterinanyterminallocation(4,2,"C");
printacharacterinanyterminallocation(4,3,"o");
printacharacterinanyterminallocation(4,4,"p");
printacharacterinanyterminallocation(4,5,"y");
printacharacterinanyterminallocation(4,6," ");
printacharacterinanyterminallocation(4,7," ");
printacharacterinanyterminallocation(4,8," ");
printacharacterinanyterminallocation(4,9," ");
printacharacterinanyterminallocation(4,10," ");
printacharacterinanyterminallocation(4,11," ");
printacharacterinanyterminallocation(4,12," ");
printacharacterinanyterminallocation(4,13," ");
printacharacterinanyterminallocation(4,14," ");
printacharacterinanyterminallocation(4,15," ");
printacharacterinanyterminallocation(4,16," ");
printacharacterinanyterminallocation(4,17," ");
printacharacterinanyterminallocation(4,18," ");
printacharacterinanyterminallocation(4,19," ");
printacharacterinanyterminallocation(4,20," ");
printacharacterinanyterminallocation(4,21," ");
printacharacterinanyterminallocation(4,22," ");
printacharacterinanyterminallocation(4,23," ");
printacharacterinanyterminallocation(4,24," ");
printacharacterinanyterminallocation(5,2,"P");
printacharacterinanyterminallocation(5,3,"a");
printacharacterinanyterminallocation(5,4,"s");
printacharacterinanyterminallocation(5,5,"t");
printacharacterinanyterminallocation(5,6,"e");
printacharacterinanyterminallocation(5,7," ");
printacharacterinanyterminallocation(5,8," ");
printacharacterinanyterminallocation(5,9," ");
printacharacterinanyterminallocation(5,10," ");
printacharacterinanyterminallocation(5,11," ");
printacharacterinanyterminallocation(5,12," ");
printacharacterinanyterminallocation(5,13," ");
printacharacterinanyterminallocation(5,14," ");
printacharacterinanyterminallocation(5,15," ");
printacharacterinanyterminallocation(5,16," ");
printacharacterinanyterminallocation(5,17," ");
printacharacterinanyterminallocation(5,18," ");
printacharacterinanyterminallocation(5,19," ");
printacharacterinanyterminallocation(5,20," ");
printacharacterinanyterminallocation(5,21," ");
printacharacterinanyterminallocation(5,22," ");
printacharacterinanyterminallocation(5,23," ");
printacharacterinanyterminallocation(5,24," ");
printacharacterinanyterminallocation(6,2,"R");
printacharacterinanyterminallocation(6,3,"e");
printacharacterinanyterminallocation(6,4,"n");
printacharacterinanyterminallocation(6,5,"a");
printacharacterinanyterminallocation(6,6,"m");
printacharacterinanyterminallocation(6,7,"e");
printacharacterinanyterminallocation(6,8," ");
printacharacterinanyterminallocation(6,9," ");
printacharacterinanyterminallocation(6,10," ");
printacharacterinanyterminallocation(6,11," ");
printacharacterinanyterminallocation(6,12," ");
printacharacterinanyterminallocation(6,13," ");
printacharacterinanyterminallocation(6,14," ");
printacharacterinanyterminallocation(6,15," ");
printacharacterinanyterminallocation(6,16," ");
printacharacterinanyterminallocation(6,17," ");
printacharacterinanyterminallocation(6,18," ");
printacharacterinanyterminallocation(6,19," ");
printacharacterinanyterminallocation(6,20," ");
printacharacterinanyterminallocation(6,21," ");
printacharacterinanyterminallocation(6,22," ");
printacharacterinanyterminallocation(6,23," ");
printacharacterinanyterminallocation(6,24," ");
printacharacterinanyterminallocation(7,2,"D");
printacharacterinanyterminallocation(7,3,"e");
printacharacterinanyterminallocation(7,4,"l");
printacharacterinanyterminallocation(7,5,"e");
printacharacterinanyterminallocation(7,6,"t");
printacharacterinanyterminallocation(7,7,"e");
printacharacterinanyterminallocation(7,8," ");
printacharacterinanyterminallocation(7,9," ");
printacharacterinanyterminallocation(7,10," ");
printacharacterinanyterminallocation(7,11," ");
printacharacterinanyterminallocation(7,12," ");
printacharacterinanyterminallocation(7,13," ");
printacharacterinanyterminallocation(7,14," ");
printacharacterinanyterminallocation(7,15," ");
printacharacterinanyterminallocation(7,16," ");
printacharacterinanyterminallocation(7,17," ");
printacharacterinanyterminallocation(7,18," ");
printacharacterinanyterminallocation(7,19," ");
printacharacterinanyterminallocation(7,20," ");
printacharacterinanyterminallocation(7,21," ");
printacharacterinanyterminallocation(7,22," ");
printacharacterinanyterminallocation(7,23," ");
printacharacterinanyterminallocation(7,24," ");
printacharacterinanyterminallocation(8,2,"N");
printacharacterinanyterminallocation(8,3,"e");
printacharacterinanyterminallocation(8,4,"w");
printacharacterinanyterminallocation(8,5," ");
printacharacterinanyterminallocation(8,6,"f");
printacharacterinanyterminallocation(8,7,"o");
printacharacterinanyterminallocation(8,8,"l");
printacharacterinanyterminallocation(8,9,"d");
printacharacterinanyterminallocation(8,10,"e");
printacharacterinanyterminallocation(8,11,"r");
printacharacterinanyterminallocation(8,12," ");
printacharacterinanyterminallocation(8,13," ");
printacharacterinanyterminallocation(8,14," ");
printacharacterinanyterminallocation(8,15," ");
printacharacterinanyterminallocation(8,16," ");
printacharacterinanyterminallocation(8,17," ");
printacharacterinanyterminallocation(8,18," ");
printacharacterinanyterminallocation(8,19," ");
printacharacterinanyterminallocation(8,20," ");
printacharacterinanyterminallocation(8,21," ");
printacharacterinanyterminallocation(8,22," ");
printacharacterinanyterminallocation(8,23," ");
printacharacterinanyterminallocation(8,24," ");
printacharacterinanyterminallocation(9,2,"E");
printacharacterinanyterminallocation(9,3,"x");
printacharacterinanyterminallocation(9,4,"i");
printacharacterinanyterminallocation(9,5,"t");
printacharacterinanyterminallocation(9,6," ");
printacharacterinanyterminallocation(9,7," ");
printacharacterinanyterminallocation(9,8," ");
printacharacterinanyterminallocation(9,9," ");
printacharacterinanyterminallocation(9,10," ");
printacharacterinanyterminallocation(9,11," ");
printacharacterinanyterminallocation(9,12," ");
printacharacterinanyterminallocation(9,13," ");
printacharacterinanyterminallocation(9,14," ");
printacharacterinanyterminallocation(9,15," ");
printacharacterinanyterminallocation(9,16," ");
printacharacterinanyterminallocation(9,17," ");
printacharacterinanyterminallocation(9,18," ");
printacharacterinanyterminallocation(9,19," ");
printacharacterinanyterminallocation(9,20," ");
printacharacterinanyterminallocation(9,21," ");
printacharacterinanyterminallocation(9,22," ");
printacharacterinanyterminallocation(9,23," ");
printacharacterinanyterminallocation(9,24," ");
putchar('\n');
menubar();
}
else if (menubarmode == true) {
menubarmode = false;
setBackgroundColor(4);
printacharacterinanyterminallocation(2,1," ");
printacharacterinanyterminallocation(3,1," ");
printacharacterinanyterminallocation(4,1," ");
printacharacterinanyterminallocation(5,1," ");
printacharacterinanyterminallocation(6,1," ");
printacharacterinanyterminallocation(7,1," ");
printacharacterinanyterminallocation(8,1," ");
printacharacterinanyterminallocation(9,1," ");
printacharacterinanyterminallocation(10,1," ");
printacharacterinanyterminallocation(10,2," ");
printacharacterinanyterminallocation(10,3," ");
printacharacterinanyterminallocation(10,4," ");
printacharacterinanyterminallocation(10,5," ");
printacharacterinanyterminallocation(10,6," ");
printacharacterinanyterminallocation(10,7," ");
printacharacterinanyterminallocation(10,8," ");
printacharacterinanyterminallocation(10,9," ");
printacharacterinanyterminallocation(10,10," ");
printacharacterinanyterminallocation(10,11," ");
printacharacterinanyterminallocation(10,12," ");
printacharacterinanyterminallocation(10,13," ");
printacharacterinanyterminallocation(10,14," ");
printacharacterinanyterminallocation(10,15," ");
printacharacterinanyterminallocation(10,16," ");
printacharacterinanyterminallocation(10,17," ");
printacharacterinanyterminallocation(10,18," ");
printacharacterinanyterminallocation(10,19," ");
printacharacterinanyterminallocation(10,20," ");
printacharacterinanyterminallocation(10,21," ");
printacharacterinanyterminallocation(10,22," ");
printacharacterinanyterminallocation(10,23," ");
printacharacterinanyterminallocation(10,24," ");
printacharacterinanyterminallocation(10,25," ");
printacharacterinanyterminallocation(3,25," ");
printacharacterinanyterminallocation(4,25," ");
printacharacterinanyterminallocation(5,25," ");
printacharacterinanyterminallocation(6,25," ");
printacharacterinanyterminallocation(7,25," ");
printacharacterinanyterminallocation(8,25," ");
printacharacterinanyterminallocation(9,25," ");
printacharacterinanyterminallocation(2,25," ");
printacharacterinanyterminallocation(2,24," ");
printacharacterinanyterminallocation(2,23," ");
printacharacterinanyterminallocation(2,22," ");
printacharacterinanyterminallocation(2,21," ");
printacharacterinanyterminallocation(2,20," ");
printacharacterinanyterminallocation(2,19," ");
printacharacterinanyterminallocation(2,18," ");
printacharacterinanyterminallocation(2,17," ");
printacharacterinanyterminallocation(2,16," ");
printacharacterinanyterminallocation(2,15," ");
printacharacterinanyterminallocation(2,14," ");
printacharacterinanyterminallocation(2,13," ");
printacharacterinanyterminallocation(2,12," ");
printacharacterinanyterminallocation(2,11," ");
printacharacterinanyterminallocation(2,10," ");
printacharacterinanyterminallocation(2,9," ");
printacharacterinanyterminallocation(2,8," ");
printacharacterinanyterminallocation(2,7," ");
printacharacterinanyterminallocation(2,6," ");
printacharacterinanyterminallocation(2,5," ");
printacharacterinanyterminallocation(2,4," ");
printacharacterinanyterminallocation(2,3," ");
printacharacterinanyterminallocation(2,2," ");
printacharacterinanyterminallocation(3,2," ");
printacharacterinanyterminallocation(3,3," ");
printacharacterinanyterminallocation(3,4," ");
printacharacterinanyterminallocation(3,5," ");
printacharacterinanyterminallocation(3,6," ");
printacharacterinanyterminallocation(3,7," ");
printacharacterinanyterminallocation(3,8," ");
printacharacterinanyterminallocation(3,9," ");
printacharacterinanyterminallocation(3,10," ");
printacharacterinanyterminallocation(3,11," ");
printacharacterinanyterminallocation(3,12," ");
printacharacterinanyterminallocation(3,13," ");
printacharacterinanyterminallocation(3,14," ");
printacharacterinanyterminallocation(3,15," ");
printacharacterinanyterminallocation(3,16," ");
printacharacterinanyterminallocation(3,17," ");
printacharacterinanyterminallocation(3,18," ");
printacharacterinanyterminallocation(3,19," ");
printacharacterinanyterminallocation(3,20," ");
printacharacterinanyterminallocation(3,21," ");
printacharacterinanyterminallocation(3,22," ");
printacharacterinanyterminallocation(3,23," ");
printacharacterinanyterminallocation(3,24," ");
printacharacterinanyterminallocation(4,2," ");
printacharacterinanyterminallocation(4,3," ");
printacharacterinanyterminallocation(4,4," ");
printacharacterinanyterminallocation(4,5," ");
printacharacterinanyterminallocation(4,6," ");
printacharacterinanyterminallocation(4,7," ");
printacharacterinanyterminallocation(4,8," ");
printacharacterinanyterminallocation(4,9," ");
printacharacterinanyterminallocation(4,10," ");
printacharacterinanyterminallocation(4,11," ");
printacharacterinanyterminallocation(4,12," ");
printacharacterinanyterminallocation(4,13," ");
printacharacterinanyterminallocation(4,14," ");
printacharacterinanyterminallocation(4,15," ");
printacharacterinanyterminallocation(4,16," ");
printacharacterinanyterminallocation(4,17," ");
printacharacterinanyterminallocation(4,18," ");
printacharacterinanyterminallocation(4,19," ");
printacharacterinanyterminallocation(4,20," ");
printacharacterinanyterminallocation(4,21," ");
printacharacterinanyterminallocation(4,22," ");
printacharacterinanyterminallocation(4,23," ");
printacharacterinanyterminallocation(4,24," ");
printacharacterinanyterminallocation(5,2," ");
printacharacterinanyterminallocation(5,3," ");
printacharacterinanyterminallocation(5,4," ");
printacharacterinanyterminallocation(5,5," ");
printacharacterinanyterminallocation(5,6," ");
printacharacterinanyterminallocation(5,7," ");
printacharacterinanyterminallocation(5,8," ");
printacharacterinanyterminallocation(5,9," ");
printacharacterinanyterminallocation(5,10," ");
printacharacterinanyterminallocation(5,11," ");
printacharacterinanyterminallocation(5,12," ");
printacharacterinanyterminallocation(5,13," ");
printacharacterinanyterminallocation(5,14," ");
printacharacterinanyterminallocation(5,15," ");
printacharacterinanyterminallocation(5,16," ");
printacharacterinanyterminallocation(5,17," ");
printacharacterinanyterminallocation(5,18," ");
printacharacterinanyterminallocation(5,19," ");
printacharacterinanyterminallocation(5,20," ");
printacharacterinanyterminallocation(5,21," ");
printacharacterinanyterminallocation(5,22," ");
printacharacterinanyterminallocation(5,23," ");
printacharacterinanyterminallocation(5,24," ");
printacharacterinanyterminallocation(6,2," ");
printacharacterinanyterminallocation(6,3," ");
printacharacterinanyterminallocation(6,4," ");
printacharacterinanyterminallocation(6,5," ");
printacharacterinanyterminallocation(6,6," ");
printacharacterinanyterminallocation(6,7," ");
printacharacterinanyterminallocation(6,8," ");
printacharacterinanyterminallocation(6,9," ");
printacharacterinanyterminallocation(6,10," ");
printacharacterinanyterminallocation(6,11," ");
printacharacterinanyterminallocation(6,12," ");
printacharacterinanyterminallocation(6,13," ");
printacharacterinanyterminallocation(6,14," ");
printacharacterinanyterminallocation(6,15," ");
printacharacterinanyterminallocation(6,16," ");
printacharacterinanyterminallocation(6,17," ");
printacharacterinanyterminallocation(6,18," ");
printacharacterinanyterminallocation(6,19," ");
printacharacterinanyterminallocation(6,20," ");
printacharacterinanyterminallocation(6,21," ");
printacharacterinanyterminallocation(6,22," ");
printacharacterinanyterminallocation(6,23," ");
printacharacterinanyterminallocation(6,24," ");
printacharacterinanyterminallocation(7,2," ");
printacharacterinanyterminallocation(7,3," ");
printacharacterinanyterminallocation(7,4," ");
printacharacterinanyterminallocation(7,5," ");
printacharacterinanyterminallocation(7,6," ");
printacharacterinanyterminallocation(7,7," ");
printacharacterinanyterminallocation(7,8," ");
printacharacterinanyterminallocation(7,9," ");
printacharacterinanyterminallocation(7,10," ");
printacharacterinanyterminallocation(7,11," ");
printacharacterinanyterminallocation(7,12," ");
printacharacterinanyterminallocation(7,13," ");
printacharacterinanyterminallocation(7,14," ");
printacharacterinanyterminallocation(7,15," ");
printacharacterinanyterminallocation(7,16," ");
printacharacterinanyterminallocation(7,17," ");
printacharacterinanyterminallocation(7,18," ");
printacharacterinanyterminallocation(7,19," ");
printacharacterinanyterminallocation(7,20," ");
printacharacterinanyterminallocation(7,21," ");
printacharacterinanyterminallocation(7,22," ");
printacharacterinanyterminallocation(7,23," ");
printacharacterinanyterminallocation(7,24," ");
printacharacterinanyterminallocation(8,2," ");
printacharacterinanyterminallocation(8,3," ");
printacharacterinanyterminallocation(8,4," ");
printacharacterinanyterminallocation(8,5," ");
printacharacterinanyterminallocation(8,6," ");
printacharacterinanyterminallocation(8,7," ");
printacharacterinanyterminallocation(8,8," ");
printacharacterinanyterminallocation(8,9," ");
printacharacterinanyterminallocation(8,10," ");
printacharacterinanyterminallocation(8,11," ");
printacharacterinanyterminallocation(8,12," ");
printacharacterinanyterminallocation(8,13," ");
printacharacterinanyterminallocation(8,14," ");
printacharacterinanyterminallocation(8,15," ");
printacharacterinanyterminallocation(8,16," ");
printacharacterinanyterminallocation(8,17," ");
printacharacterinanyterminallocation(8,18," ");
printacharacterinanyterminallocation(8,19," ");
printacharacterinanyterminallocation(8,20," ");
printacharacterinanyterminallocation(8,21," ");
printacharacterinanyterminallocation(8,22," ");
printacharacterinanyterminallocation(8,23," ");
printacharacterinanyterminallocation(8,24," ");
printacharacterinanyterminallocation(9,2," ");
printacharacterinanyterminallocation(9,3," ");
printacharacterinanyterminallocation(9,4," ");
printacharacterinanyterminallocation(9,5," ");
printacharacterinanyterminallocation(9,6," ");
printacharacterinanyterminallocation(9,7," ");
printacharacterinanyterminallocation(9,8," ");
printacharacterinanyterminallocation(9,9," ");
printacharacterinanyterminallocation(9,10," ");
printacharacterinanyterminallocation(9,11," ");
printacharacterinanyterminallocation(9,12," ");
printacharacterinanyterminallocation(9,13," ");
printacharacterinanyterminallocation(9,14," ");
printacharacterinanyterminallocation(9,15," ");
printacharacterinanyterminallocation(9,16," ");
printacharacterinanyterminallocation(9,17," ");
printacharacterinanyterminallocation(9,18," ");
printacharacterinanyterminallocation(9,19," ");
printacharacterinanyterminallocation(9,20," ");
printacharacterinanyterminallocation(9,21," ");
printacharacterinanyterminallocation(9,22," ");
printacharacterinanyterminallocation(9,23," ");
printacharacterinanyterminallocation(9,24," ");
putchar('\n');
drawingoffilesboxdone = false;
int backup = driveslistingscount;
driveslistingscount = backup;
drawdrivesbox();
driveslistingscount = backup;
drawingoffilesboxdone = true;
xcoordinateformenubar = 0;
menubar();
}
else if (xcoordinate == 1 && menubarwithexitonlyoptionmode == false) {
menubarwithexitonlyoptionmode = true;
setBackgroundColor(2);
printacharacterinanyterminallocation(2,1,"┌");
printacharacterinanyterminallocation(3,1,"│");
printacharacterinanyterminallocation(4,1,"│");
//printacharacterinanyterminallocation(5,1,"│");
//printacharacterinanyterminallocation(6,1,"│");
//printacharacterinanyterminallocation(7,1,"│");
//printacharacterinanyterminallocation(8,1,"│");
//printacharacterinanyterminallocation(9,1,"│");
printacharacterinanyterminallocation(4,1,"└");
printacharacterinanyterminallocation(4,2,"─");
printacharacterinanyterminallocation(4,3,"─");
printacharacterinanyterminallocation(4,4,"─");
printacharacterinanyterminallocation(4,5,"─");
printacharacterinanyterminallocation(4,6,"─");
printacharacterinanyterminallocation(4,7,"─");
printacharacterinanyterminallocation(4,8,"─");
printacharacterinanyterminallocation(4,9,"─");
printacharacterinanyterminallocation(4,10,"─");
printacharacterinanyterminallocation(4,11,"─");
printacharacterinanyterminallocation(4,12,"─");
printacharacterinanyterminallocation(4,13,"─");
printacharacterinanyterminallocation(4,14,"─");
printacharacterinanyterminallocation(4,15,"─");
printacharacterinanyterminallocation(4,16,"─");
printacharacterinanyterminallocation(4,17,"─");
printacharacterinanyterminallocation(4,18,"─");
printacharacterinanyterminallocation(4,19,"─");
printacharacterinanyterminallocation(4,20,"─");
printacharacterinanyterminallocation(4,21,"─");
printacharacterinanyterminallocation(4,22,"─");
printacharacterinanyterminallocation(4,23,"─");
printacharacterinanyterminallocation(4,24,"─");
printacharacterinanyterminallocation(3,25,"│");
printacharacterinanyterminallocation(4,25,"┘");
//printacharacterinanyterminallocation(4,25,"│");
//printacharacterinanyterminallocation(4,25,"│");
//printacharacterinanyterminallocation(5,25,"│");
//printacharacterinanyterminallocation(6,25,"│");
//printacharacterinanyterminallocation(7,25,"│");
//printacharacterinanyterminallocation(8,25,"│");
//printacharacterinanyterminallocation(9,25,"│");
printacharacterinanyterminallocation(2,25,"┐");
printacharacterinanyterminallocation(2,24,"─");
printacharacterinanyterminallocation(2,23,"─");
printacharacterinanyterminallocation(2,22,"─");
printacharacterinanyterminallocation(2,21,"─");
printacharacterinanyterminallocation(2,20,"─");
printacharacterinanyterminallocation(2,19,"─");
printacharacterinanyterminallocation(2,18,"─");
printacharacterinanyterminallocation(2,17,"─");
printacharacterinanyterminallocation(2,16,"─");
printacharacterinanyterminallocation(2,15,"─");
printacharacterinanyterminallocation(2,14,"─");
printacharacterinanyterminallocation(2,13,"─");
printacharacterinanyterminallocation(2,12,"─");
printacharacterinanyterminallocation(2,11,"─");
printacharacterinanyterminallocation(2,10,"─");
printacharacterinanyterminallocation(2,9,"─");
printacharacterinanyterminallocation(2,8,"─");
printacharacterinanyterminallocation(2,7,"─");
printacharacterinanyterminallocation(2,6,"─");
printacharacterinanyterminallocation(2,5,"─");
printacharacterinanyterminallocation(2,4,"─");
printacharacterinanyterminallocation(2,3,"─");
printacharacterinanyterminallocation(2,2,"─");
setBackgroundColor(3);
printacharacterinanyterminallocation(1,1,"F");
printacharacterinanyterminallocation(1,2,"i");
printacharacterinanyterminallocation(1,3,"l");
printacharacterinanyterminallocation(1,4,"e");
printacharacterinanyterminallocation(3,2,"E");
printacharacterinanyterminallocation(3,3,"x");
printacharacterinanyterminallocation(3,4,"i");
printacharacterinanyterminallocation(3,5,"t");
printacharacterinanyterminallocation(3,6," ");
printacharacterinanyterminallocation(3,7," ");
printacharacterinanyterminallocation(3,8," ");
printacharacterinanyterminallocation(3,9," ");
printacharacterinanyterminallocation(3,10," ");
printacharacterinanyterminallocation(3,11," ");
printacharacterinanyterminallocation(3,12," ");
printacharacterinanyterminallocation(3,13," ");
printacharacterinanyterminallocation(3,14," ");
printacharacterinanyterminallocation(3,15," ");
printacharacterinanyterminallocation(3,16," ");
printacharacterinanyterminallocation(3,17," ");
printacharacterinanyterminallocation(3,18," ");
printacharacterinanyterminallocation(3,19," ");
printacharacterinanyterminallocation(3,20," ");
printacharacterinanyterminallocation(3,21," ");
printacharacterinanyterminallocation(3,22," ");
printacharacterinanyterminallocation(3,23," ");
printacharacterinanyterminallocation(3,24," ");
//printacharacterinanyterminallocation(3,25,"│");
setBackgroundColor(2);
putchar('\n');
//menubar();
}
else if (menubarwithexitonlyoptionmode == true) {
menubarwithexitonlyoptionmode = false;
//closemenubar();
}
//std::string teststring = "test12345678";
//setBackgroundColor(3);
//std::cout << "The first " << "5" << " characters are: " << teststring.substr(0, 5) << std::endl;
//std::cout << "The first " << "5" << " characters are: "
//              << teststring.substr(0, 5).append(5 - teststring.substr(0, 5).length(), ' ') << " "
//              << "test" <<std::endl;
//setBackgroundColor(4);
}
//drawscrollbarfordrivesbox();
}
else if (byteswaiting != 3 && byteswaiting != 4 && byteswaiting != 0 && byteswaiting != 1) {
std::cout << "Bytes number not handled" << "bytes" << byteswaiting << std::endl;
//cout << byteswaiting;
int progresscharnum = 0;
for (progresscharnum = 0;progresscharnum <= byteswaiting;progresscharnum++) {
std::cin.ignore();
}
}
}
}









