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
#define FIONREAD	0x541B
#include <main.h>
#include <displayfiles.h>
#include <filenamehighlight.h>
#include <keypressdetection.h>
#include <drawpreviewbox.h>
#include <drawdrivesbox.h>
#include <drawscrollbarforfilesbox.h>
#include <getfiledata.h>
#include <cleanfilesbox.h>
bool testfilesvectoralreadydone = false;
bool drawingofilesboxdone = false;
//vector<std::string> filenamelistings;
int filenamelistingscount = 0;
int possiblescrolldownsinfilesbox = 0;
int drawfilesbox(int scrollup = 0,int filenamelistingscount = 0,int scrolldown = 0,int refresh = 0){
drawscrollbarforfilesbox();
if (testfilesvectoralreadydone == false) {
//filenamelistings.push_back("test12345678");
//filenamelistings.push_back("jesus");
//filenamelistings.push_back("test2345");
//filenamelistings.push_back("test7890");
//filenamelistings.push_back("test5678");
//filenamelistings.push_back("test2345");
//filenamelistings.push_back("test5678");
//filenamelistings.push_back("test3458");
//filenamelistings.push_back("test4567");
//filenamelistings.push_back("test1234");
testfilesvectoralreadydone = true;
}
//std::cout << "The first " << "5" << " characters are: "
//              << filenamelistings[filenamelistingscount].filename.substr(0, 5).append(5 - filenamelistings[filenamelistingscount].filename.substr(0, 5).length(), ' ') << " "
//              << "test" <<std::endl;
possiblescrolldownsinfilesbox = rows / 2 - 4;
possiblescrolldownsinfilesbox = static_cast<int>(filenamelistings.size()) / possiblescrolldownsinfilesbox;
//std::cout << "nonexistentlisting:" << filenamelistings[90];
if (scrollup == 0 && scrolldown == 0 && refresh == 0) {
for (int progressrow = 3;progressrow != rows / 2 - 1;progressrow++) {
//std::cout << "progressrow:" << progressrow;
movecursortoanyterminallocation(progressrow,columns / 2 - 12);
if (progressrow == 3 && xcoordinate == 2 && scrollup == 0) {
setBackgroundColor(3);
filenamelistingscount = 0; }
if (progressrow == 3 && xcoordinate == 2 && scrollup == 0 && drawingofilesboxdone == true) {
setBackgroundColor(3);
filenamelistingscount = 0;
std::cout << filenamelistings[filenamelistingscount].filename << "-" << filenamelistingscount << std::endl;
setBackgroundColor(4);
progressrow == rows / 2 - 1;
break; }
if (filenamelistingscount >= filenamelistings.size()) {
progressrow == rows / 2 - 1;
break;
}
//std::cout << filenamelistings[filenamelistingscount].filename << "-" << filenamelistingscount << std::endl;
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) {
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
movecursortoanyterminallocation(progressrow,columns - 20);
std::cout << filenamelistings[filenamelistingscount].filedateandtime << std::endl;
              }
              else {
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
              movecursortoanyterminallocation(progressrow,columns - 20);
std::cout << filenamelistings[filenamelistingscount].filedateandtime << std::endl;}
if (filenamelistingscount < filenamelistings.size()) {
filenamelistingscount++;
}
else {
filenamelistingscount--;
}
}
drawingofilesboxdone = true;
//filenamelistingscount = 7;
}
else if (scrollup == 1) {
cleanfilesbox();
//std::cout << "1234";
//std::cout << "listingssize:" << filenamelistings.size();
//putchar('\n');
//system("clear");
//drawdrivesbox();
for (int progressrow = 3;progressrow != rows / 2 - 1;progressrow++) {
//std::cout << "progressrow:" << progressrow;
movecursortoanyterminallocation(progressrow,columns / 2 - 12);
if (progressrow == 3 && xcoordinate == 2) {
setBackgroundColor(3);
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) {
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
movecursortoanyterminallocation(progressrow,columns - 20);
std::cout << filenamelistings[filenamelistingscount].filedateandtime << std::endl;
              }
              else {
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
              movecursortoanyterminallocation(progressrow,columns - 20);
std::cout << filenamelistings[filenamelistingscount].filedateandtime << std::endl;} }
if (filenamelistingscount >= filenamelistings.size()) {
progressrow == rows / 2 - 1;
break;
}
setBackgroundColor(4);
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) {
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
movecursortoanyterminallocation(progressrow,columns - 20);
std::cout << filenamelistings[filenamelistingscount].filedateandtime << std::endl;
              }
              else {
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
              movecursortoanyterminallocation(progressrow,columns - 20);
std::cout << filenamelistings[filenamelistingscount].filedateandtime << std::endl;}
filenamelistingscount++;
}
}
else if (scrolldown == 1) {
//std::cout << "12345678";
//putchar('\n');
//std::cout << "count before =" << filenamelistingscount;
//filenamelistingscount = filenamelistingscount - rows / 2 - 2;
//std::cout << "count after =" << filenamelistingscount;
//system("clear");
for (int progressrow = 3;progressrow != rows / 2 - 1;progressrow++) {
//std::cout << "progressrow:" << progressrow;
movecursortoanyterminallocation(progressrow,columns / 2 - 12);
if (progressrow == 3 && xcoordinate == 2) {
setBackgroundColor(3);
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) {
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
movecursortoanyterminallocation(progressrow,columns - 20);
std::cout << filenamelistings[filenamelistingscount].filedateandtime << std::endl;
              }
              else {
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
              movecursortoanyterminallocation(progressrow,columns - 20);
std::cout << filenamelistings[filenamelistingscount].filedateandtime << std::endl;}}
if (filenamelistingscount >= filenamelistings.size()) {
progressrow == rows / 2 - 1;
break;
}
setBackgroundColor(4);
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) {
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
movecursortoanyterminallocation(progressrow,columns - 20);
std::cout << filenamelistings[filenamelistingscount].filedateandtime << std::endl;
              }
              else {
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
              movecursortoanyterminallocation(progressrow,columns - 20);
std::cout << filenamelistings[filenamelistingscount].filedateandtime << std::endl;}
filenamelistingscount++;
//filenamelistingscount++;
}
}
else if (scrolldown == 1) {
//std::cout << "12345678";
//putchar('\n');
//std::cout << "count before =" << filenamelistingscount;
//filenamelistingscount = filenamelistingscount - rows / 2 - 2;
//std::cout << "count after =" << filenamelistingscount;
//system("clear");
for (int progressrow = 3;progressrow != rows / 2 - 1;progressrow++) {
//std::cout << "progressrow:" << progressrow;
movecursortoanyterminallocation(progressrow,columns / 2 - 12);
if (progressrow == 3 && xcoordinate == 2) {
setBackgroundColor(3);
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) {
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
movecursortoanyterminallocation(progressrow,columns - 20);
std::cout << filenamelistings[filenamelistingscount].filedateandtime << std::endl;
              }
              else {
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
              movecursortoanyterminallocation(progressrow,columns - 20);
std::cout << filenamelistings[filenamelistingscount].filedateandtime << std::endl;} }
if (filenamelistingscount >= filenamelistings.size()) {
progressrow == rows / 2 - 1;
break;
}
setBackgroundColor(4);
setBackgroundColor(4);
filenamelistingscount++;
}
}
else if (refresh == 1) {
for (int progressrow = 3;progressrow != rows / 2 - 1;progressrow++) {
//std::cout << "progressrow:" << progressrow;
movecursortoanyterminallocation(progressrow,columns / 2 - 12);
if (progressrow == 3 && xcoordinate == 2) {
setBackgroundColor(3); }
if (filenamelistingscount >= filenamelistings.size()) {
progressrow == rows / 2 - 1;
break;
}
setBackgroundColor(4);
if (filenamelistings[filenamelistingscount].filename.size() > columns / 2 - 16) {
std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).append(columns / 2 - 19 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 19).length(), ' ') << "...";
movecursortoanyterminallocation(progressrow,columns - 20);
std::cout << filenamelistings[filenamelistingscount].filedateandtime << std::endl;
              }
              else {
              std::cout  << filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).append(columns / 2 - 16 - filenamelistings[filenamelistingscount].filename.substr(0, columns / 2 - 16).length(), ' ');
              movecursortoanyterminallocation(progressrow,columns - 20);
std::cout << filenamelistings[filenamelistingscount].filedateandtime << std::endl;}
filenamelistingscount++;
//filenamelistingscount++;
}
}
for (int filesrow = rows / 2 - 2;filesrow != 1;filesrow--) {
printacharacterinanyterminallocation(filesrow,columns /2 - 13,"│");
}
printacharacterinanyterminallocation(2,columns / 2 - 13,"┌");
putchar('\n');
for (int filesrow = rows / 2 - 2;filesrow != 1;filesrow--) {
printacharacterinanyterminallocation(filesrow,columns,"│");
}
printacharacterinanyterminallocation(rows / 2 - 1,columns,"┘");
printacharacterinanyterminallocation(rows / 2 - 1,columns / 2 -13,"└");
printacharacterinanyterminallocation(2,columns,"┐");
for (int filescolumn = columns - 3;filescolumn != columns / 2 - 13;filescolumn--) {
printacharacterinanyterminallocation(2,filescolumn,"─");
}
for (int filescolumn = columns - 1;filescolumn != columns / 2 - 13;filescolumn--) {
printacharacterinanyterminallocation(rows / 2 - 1,filescolumn,"─");
}
printacharacterinanyterminallocation(2,columns - 1,"─");
printacharacterinanyterminallocation(2,columns - 2,"─");
putchar('\n');
movecursortoanyterminallocation(2,columns - 30);
std::cout << "Files";
putchar('\n');
}
