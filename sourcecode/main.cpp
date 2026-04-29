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
#include <sys/stat.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#define FIONREAD	0x541B
#include <main.h>
#include <keypressdetection.h>
#include <limits>
#include <displayfiles.h>
#include <menubar.h>
#include <drawpreviewbox.h>
#include <drawdrivesbox.h>
#include <drawfilesbox.h>>
#include <cleandrivesbox.h>
#include <cleanpreviewbox.h>
#include <drawscrollbarfordrivesbox.h>
#include <cleanscrollbarfordrivesbox.h>
#include <getmounteddrives.h>
#include <getfiledata.h>
#include <cleanfilesbox.h>
#include <shownewdirectorydialog.h>
//development reset at 17-01-2025
using namespace std;
bool filemenu = true;
bool filenamescreen = false;
//bool notpromptforpath = false;
//bool finishloop = false;
int rows;
int columns;
int selectionxbackup;
int selectionybackup;
int fileanddircount = 0;
int scrollupsindrivesbox = 0;
int f1 = 1;
        int f2 = 2;
        int f3 = 3;
        int f4 = 4;
        int f5 = 5;
        int coordinatex;
        int coordinatey;
//        struct fileinfo {
//        std::string filename;
//        std::string filedateandtime;
//        };
 int selectionx = 0;
 int selectiony = 0;
 void handle_sigint() {

    std::cout << "Ctrl-C detected! Exiting gracefully..." << std::endl;

    // Perform cleanup if necessary

    exit(0);

}
  void setCursorPosition(int x, int y) {
     std::cout << "\033[" << y << ";" << x << "H"; // Move cursor to (x, y)
  }
  void setBackgroundColor(int color) {
    std::cout << "\033[" << (40 + color) << "m"; // Set background color (40-47)
   }
    void resetColors() {
     std::cout << "\033[0m"; // Reset all attributes
 }
 int movecursortoanyterminallocation(int termcoordxint,int termcoordyint) { //Funcion para mover el cursor de la terminal a una ubicacion especifica
    char* termcosordxchar, ansiescapecodetomovetheterminalcursor[81]; //Requiere 2 argumentos:la coordenada x y la coordenada y
 std::string str = std::to_string(termcoordxint); //Funcion para mover el cursor de la terminal a una ubicacion especifica
 const char* termcoordxchar = str.c_str(); //Funcion para mover el cursor de la terminal a una ubicacion especifica
 sprintf(ansiescapecodetomovetheterminalcursor,"\033[%s;%dH",termcoordxchar,termcoordyint); //Funcion para mover el cursor de la terminal a una ubicacion especifica
 cout << ansiescapecodetomovetheterminalcursor; //Funcion para mover el cursor de la terminal a una ubicacion especifica//
 return 0; }
 int printacharacterinanyterminallocation(int termcoordxint,int termcoordyint,string character) {
    char* termcosordxchar, ansiescapecodetomovetheterminalcursor[81];
   std::string str = std::to_string(termcoordxint);
   const char* termcoordxchar = str.c_str();
   //cout << "char" << termcoordxchar;;
  sprintf(ansiescapecodetomovetheterminalcursor,"\033[%s;%dH",termcoordxchar,termcoordyint);
  cout << ansiescapecodetomovetheterminalcursor;
  cout << character;
  return 0; }
int main(void)
{
std::cout << "\033[?1049h";
system("export TERM=xterm-256color");
setBackgroundColor(4);
system("stty -icanon -echo");
coordinatex = 0;
coordinatey = 0;
struct winsize w;
ioctl(STDOUT_FILENO, TIOCGWINSZ,&w);
rows = w.ws_row;
columns = w.ws_col;
//some code
//for (int progressrow = rows;progressrow != 0;progressrow--) {
//for (int progresscolummn = columns;progresscolummn != 0;progresscolummn--) {
//setBackgroundColor(4);
//printacharacterinanyterminallocation(progressrow,progresscolummn,"█"); }
//}/dev/nvme0n1p3
//putchar('\n');
//end of some code
/*
for (progressrow = 0;progressrow < rows;progressrow++) {
for (progresscolummn = 0;progresscolummn <= columns;progresscolummn++) {
std::cout << "\033[" << "32" << "m";
printacharacterinanyterminallocation(progressrow,progresscolummn,"█");
cout << std::endl;
}
}
for (int temp;progresscolummn <= columns;progresscolummn++) {
std::cout << "\033[" << "32" << "m";
printacharacterinanyterminallocation(rows,progresscolummn,"█");
std::cout << progresscolummn;
//cout << std::endl;
}
system("sleep 20");
std::cout << "Rows:" << rows << std::endl;
std::cout << "Columns:" << columns << std::endl;
*/
//std::cout << "Rows:" << rows << std::endl;
//std::cout << "Columns:" << columns << std::endl;
//system("sh");
//shownewdirectorydialog();
//system("sleep 5");
getMountedVolumes();
//system("sleep 5");
setBackgroundColor(4);
//drawpreviewbox();
//drawdrivesbox();
//drawfilesbox();
menubar();
//drawscrollbarfordrivesbox();
//cleandrivesbox();
//cleanpreviewbox();
//drawfilesbox();
//cleanfilesbox();
//system("sleep 20");
setBackgroundColor(4);
//getMountedVolumes();
readfilenames();
//std::cout << files[0].filename;
//std::cout << files[0].filedateandtime;
//putchar('\n');
//system("sleep 20");
drawpreviewbox();
//system("sleep 20");
drawdrivesbox();
drawfilesbox();
menubar();
setBackgroundColor(4);
//drawBox();
std::cout << "\033[?25l";
movecursortoanyterminallocation(3,3);
keypressdetection();
return 0;
}
