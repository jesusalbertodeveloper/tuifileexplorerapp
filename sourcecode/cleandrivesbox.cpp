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
int cleandrivesbox() {
for (int progressrow = 3;progressrow != rows / 2 - 1;progressrow++) {
for (int progresscolumn = columns / 2 - 16;progresscolumn != 1;progresscolumn--) {
setBackgroundColor(4);
printacharacterinanyterminallocation(progressrow,progresscolumn," ");
}
}
setBackgroundColor(4);
putchar('\n');
}
