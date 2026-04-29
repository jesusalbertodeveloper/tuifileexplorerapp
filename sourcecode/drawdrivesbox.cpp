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
#include <drawfilesbox.h>
#include <drawscrollbarfordrivesbox.h>
#include <cleanscrollbarfordrivesbox.h>
#include <getmounteddrives.h>
bool drawingoffilesboxdone = false;
bool testdrivesvectoralreadydone = false;
int driveslistingscount = 0;
int possiblescrolldownsindrivesbox = 0;
bool alreadyran = false;
int drawdrivesbox(int scrollup = 0,int driveslistingscount = 0,int scrolldown = 0){
//std::cout << "function ran";
if (testdrivesvectoralreadydone == false){ //elementos de prueba
//driveslistings.push_back("1");
//driveslistings.push_back("2");
//driveslistings.push_back("3");
//driveslistings.push_back("4");
//driveslistings.push_back("5");
//driveslistings.push_back("6");
//driveslistings.push_back("7");
//driveslistings.push_back("8");
//driveslistings.push_back("9");
//listings.push_back("10");
//listings.push_back("11");
//listings.push_back("12");
//listings.push_back("13");
//listings.push_back("14");
//listings.push_back("15");
//listings.push_back("16");
//listings.push_back("17");
//listings.push_back("18");
//listings.push_back("19");
//listings.push_back("20");
//listings.push_back("21");
//listings.push_back("22");
//listings.push_back("23");
//listings.push_back("24");
//listings.push_back("25");
//listings.push_back("26");
//listings.push_back("27");
//listings.push_back("28");
//listings.push_back("29");
//listings.push_back("30");
//listings.push_back("31");
//listings.push_back("32");
//listings.push_back("33");
//listings.push_back("34");
//listings.push_back("35");
//listings.push_back("36");
//listings.push_back("37");
//listings.push_back("38");
//listings.push_back("39");
//listings.push_back("40");
testdrivesvectoralreadydone = true; //elementosdeprueba
}
possiblescrolldownsindrivesbox = rows / 2 - 4;
possiblescrolldownsindrivesbox = static_cast<int>(driveslistings.size()) / possiblescrolldownsindrivesbox;
//printacharacterinanyterminallocation(3,10,"x");
//putchar('\n');
//for (int i = 0;i > 20;i++) {
//std::string str = std::to_string(i);
//listings.push_back(str); }
if (scrollup == 0 && scrolldown == 0) {
for (int progressrow = 3;progressrow != rows / 2 - 1;progressrow++) {
//std::cout << "progressrow:" << progressrow;
movecursortoanyterminallocation(progressrow,2);
if (progressrow == 3 && xcoordinate == 1 && scrollup == 0) {
setBackgroundColor(3);
driveslistingscount = 0; }
if (progressrow == 3 && xcoordinate == 1 && drawingoffilesboxdone == true) {
setBackgroundColor(3);
std::cout << driveslistings[driveslistingscount].label << "-" << driveslistingscount << std::endl;
setBackgroundColor(4);
driveslistingscount = 0;
progressrow =rows / 2 - 1;
break; }
if (driveslistingscount >= driveslistings.size()) {
progressrow == rows / 2 - 1;
break;
}
std::cout << driveslistings[driveslistingscount].label << "-" << driveslistingscount << std::endl;
setBackgroundColor(4);
if (driveslistingscount < driveslistings.size()) {
driveslistingscount++;
}
else {
driveslistingscount--;
}
}
drawingoffilesboxdone = true;
}
else if (scrollup == 1) {
std::cout << "1234";
std::cout << "listingssize:" << driveslistings.size();
putchar('\n');
system("clear");
for (int progressrow = 3;progressrow != rows / 2 - 1;progressrow++) {
//std::cout << "progressrow:" << progressrow;
movecursortoanyterminallocation(progressrow,2);
if (progressrow == 3 && xcoordinate == 1) {
setBackgroundColor(3); }
if (driveslistingscount >= driveslistings.size()) {
progressrow == rows / 2 - 1;
break;
}
std::cout << driveslistings[driveslistingscount].label << "-" << driveslistings.size() << std::endl;
setBackgroundColor(4);
driveslistingscount++;
}
}
else if (scrolldown == 1) {
//std::cout << "12345678";
//putchar('\n');
//std::cout << "count before =" << driveslistingscount;
//driveslistingscount = driveslistingscount - rows / 2 - 2;
//std::cout << "count after =" << driveslistingscount;
//system("clear");
for (int progressrow = 3;progressrow != rows / 2 - 1;progressrow++) {
//std::cout << "progressrow:" << progressrow;
movecursortoanyterminallocation(progressrow,2);
if (progressrow == 3 && xcoordinate == 1) {
setBackgroundColor(3); }
if (driveslistingscount >= driveslistings.size()) {
progressrow == rows / 2 - 1;
break;
}
std::cout << driveslistings[driveslistingscount].label << "-" << driveslistingscount << std::endl;
setBackgroundColor(4);
driveslistingscount++;
//putchar('\n');
}
//std::cout << std::endl;
}
//driveslistingscount = 39;
for (int drivesrow = rows / 2 - 1;drivesrow != 1;drivesrow--) {
printacharacterinanyterminallocation(drivesrow,columns /2 - 15,"│");
}
for (int drivesrow = rows / 2 - 1;drivesrow != 1;drivesrow--) {
printacharacterinanyterminallocation(drivesrow,columns /2 - 15,"│");
}
for (int drivesrow = rows / 2 - 1;drivesrow != 1;drivesrow--) {
printacharacterinanyterminallocation(drivesrow,1,"│");
}
printacharacterinanyterminallocation(rows / 2 - 1,columns /2 - 15,"┘");
for (int drivescolumn = columns / 2 - 16;drivescolumn != 0;drivescolumn--) {
printacharacterinanyterminallocation(rows / 2 - 1,drivescolumn,"─");
}
for (int drivescolumn = columns / 2 - 16;drivescolumn != 0;drivescolumn--) {
printacharacterinanyterminallocation(2,drivescolumn,"─");
}
printacharacterinanyterminallocation(rows / 2 - 1,1,"└");
printacharacterinanyterminallocation(2,1,"┌");
printacharacterinanyterminallocation(2,columns / 2 - 15,"┐");
movecursortoanyterminallocation(2,10);
std::cout << "Drives";
putchar('\n');
cleanscrollbarfordrivesbox();
drawscrollbarfordrivesbox();
}
