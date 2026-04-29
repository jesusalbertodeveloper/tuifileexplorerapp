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
int cleanpreviewbox() {
for (int progressrow = rows / 2 + 1;progressrow != rows - 1;progressrow++) {
for (int progresscolumn = columns - 1;progresscolumn != 1;progresscolumn--) {
setBackgroundColor(4);
printacharacterinanyterminallocation(progressrow,progresscolumn," ");
movecursortoanyterminallocation(rows - 2,1);
}
}
//int possiblerowsinpreviewbox = rows / 2 - 2;
//std::cout << "possible rows:" << possiblerowsinpreviewbox;
setBackgroundColor(4);
putchar('\n');
}
