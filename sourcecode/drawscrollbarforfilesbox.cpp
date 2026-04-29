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
#include <menubar.h>
#include <drawdrivesbox.h>
#include <drawfilesbox.h>
#include <getfiledata.h>
int drawscrollbarforfilesbox() {
if (filenamelistings.size() > rows / 2 - 4) {
int possiblerows = rows / 2 - 4;
int currentrow = 0;
//printacharacterinanyterminallocation(3,columns - 1,"█");
//putchar('\n');
double value = scrolldownsinfilesbox;
//std::cout << "Enter value";
//cin >> value;
double limit = possiblescrolldownsinfilesbox;
int percentage = (value / limit) * 100;
//std::cout << "percentage:" << percentage << std::endl;
int startrow = 3;
if (percentage == 0) {
printacharacterinanyterminallocation(0 + 3,columns - 1,"█");
printacharacterinanyterminallocation(0 + 4,columns - 1,"█");
printacharacterinanyterminallocation(0 + 5,columns - 1,"█");
}
if (percentage >= 1 && percentage <= 15) {
//int position = 1 + (40 * (10 - 1) / 100);
//std::cout << "P:" << position << std::endl;
printacharacterinanyterminallocation(0 + 4,columns - 1,"█");
printacharacterinanyterminallocation(0 + 5,columns - 1,"█");
printacharacterinanyterminallocation(0 + 6,columns - 1,"█");
}
if (percentage >= 15 && percentage <= 50) {
printacharacterinanyterminallocation(0 + 5,columns - 1,"█");
printacharacterinanyterminallocation(0 + 6,columns - 1,"█");
printacharacterinanyterminallocation(0 + 7,columns - 1,"█");
}
if (percentage >= 50 && percentage <= 75) {
printacharacterinanyterminallocation(0 + 7,columns - 1,"█");
printacharacterinanyterminallocation(0 + 8,columns - 1,"█");
printacharacterinanyterminallocation(0 + 9,columns - 1,"█");
}
if (percentage >= 75 && percentage <= 100) {
int amountofrowstoprintin = possiblerows * 0.40;
printacharacterinanyterminallocation(possiblerows + 2,columns - 1,"█");
printacharacterinanyterminallocation(possiblerows + 1,columns - 1,"█");
printacharacterinanyterminallocation(possiblerows,columns - 1,"█");
}
putchar('\n');
}
}
