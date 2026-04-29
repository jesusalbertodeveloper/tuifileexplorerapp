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
#include <getmounteddrives.h>
int drawscrollbarfordrivesbox() {
if (driveslistings.size() > rows / 2 - 4) {
int possiblerows = rows / 2 - 4;
int currentrow = 0;
//printacharacterinanyterminallocation(3,columns / 2 - 16,"█");
//putchar('\n');
double value = scrolldownsindrivesbox;
//std::cout << "Enter value";
//cin >> value;
double limit = possiblescrolldownsindrivesbox;
int percentage = (value / limit) * 100;
int startrow = 3;
if (percentage == 0) {
printacharacterinanyterminallocation(0 + 3,columns / 2 - 16,"█");
printacharacterinanyterminallocation(0 + 4,columns / 2 - 16,"█");
printacharacterinanyterminallocation(0 + 5,columns / 2 - 16,"█");
}
if (percentage >= 1 && percentage <= 30) {
//int position = 1 + (40 * (10 - 1) / 100);
//std::cout << "P:" << position << std::endl;
printacharacterinanyterminallocation(0 + 4,columns / 2 - 16,"█");
printacharacterinanyterminallocation(0 + 5,columns / 2 - 16,"█");
printacharacterinanyterminallocation(0 + 6,columns / 2 - 16,"█");
}
if (percentage >= 40 && percentage <= 50) {
printacharacterinanyterminallocation(0 + 5,columns / 2 - 16,"█");
printacharacterinanyterminallocation(0 + 6,columns / 2 - 16,"█");
printacharacterinanyterminallocation(0 + 7,columns / 2 - 16,"█");
}
if (percentage >= 60 && percentage <= 70) {
printacharacterinanyterminallocation(0 + 7,columns / 2 - 16,"█");
printacharacterinanyterminallocation(0 + 8,columns / 2 - 16,"█");
printacharacterinanyterminallocation(0 + 9,columns / 2 - 16,"█");
}
if (percentage >= 80 && percentage <= 100) {
int amountofrowstoprintin = possiblerows * 0.40;
printacharacterinanyterminallocation(possiblerows + 2,columns / 2 - 16,"█");
printacharacterinanyterminallocation(possiblerows + 1,columns / 2 - 16,"█");
printacharacterinanyterminallocation(possiblerows,columns / 2 - 16,"█");
}
putchar('\n');
}
}
/*
int drawscrollbarfordrivesbox() {
    int possiblerows = rows / 2 - 4; // Total possible rows for the scrollbar
    double value;
    std::cout << "Enter value: ";
    std::cin >> value;
    double limit = 10; // Set the limit for the value
    int percentage = static_cast<int>((value / limit) * 100); // Calculate percentage


    // Calculate the position of the scrollbar based on the percentage

    int position = (percentage * possiblerows) / 100; // Calculate position based on percentage


    // Print the scrollbar character at the calculated position

    for (int row = 0; row < possiblerows; ++row) {

        if (row == position) {

            printacharacterinanyterminallocation(row, columns / 2 - 16, "█"); // Print scrollbar character

        } else {

            printacharacterinanyterminallocation(row, columns / 2 - 16, " "); // Print empty space

        }

    }


    putchar('\n');

    return 0; // Return 0 to indicate success

}
*/
/*
int drawscrollbarfordrivesbox() {
    int possiblerows = rows / 2 - 4; // Total possible rows for the scrollbar
    double value;
    std::cout << "Enter value: ";
    std::cin >> value;
    double limit = 10; // Set the limit for the value
    int percentage = static_cast<int>((value / limit) * 100); // Calculate percentage
    // Ensure percentage is within bounds
    if (percentage < 0) percentage = 0;
    if (percentage > 100) percentage = 100;
    // Calculate the position of the scrollbar based on the percentage
    int position = (percentage * (possiblerows - 3)) / 100; // Calculate position for 3-row scrollbar
    // Print the scrollbar character at the calculated position
    for (int row = 0; row < possiblerows; ++row) {
        if (row >= position && row < position + 3) {
            printacharacterinanyterminallocation(row, columns / 2 - 16, "█"); // Print scrollbar character
        } else {
            printacharacterinanyterminallocation(row, columns / 2 - 16, " "); // Print empty space
        }
    }
    putchar('\n');
    return 0; // Return 0 to indicate success
}
*/

