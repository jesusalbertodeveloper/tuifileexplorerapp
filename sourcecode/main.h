#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
using namespace std;
// Function declarations
int drawBox();
int movecursortoanyterminallocation(int x, int y);
int printacharacterinanyterminallocation(int termcoordxint,int termcoordyint,string character);
int tuidraw();
void resetColors();
void setBackgroundColor(int color);
int closeBox();
int drawSubMenu();
int closeSubMenu();
int selectionfunction();
int scrollup();
int scrolldown();
int clearfilenamesfrombox();
int displayfiles();
// Add other function declarations as needed

// Variable declarations

// Declare the variable
// Declare other variables as needed
extern bool filenamescreen;
extern int selectionxbackup;
extern int selectionybackup;
extern int fileanddircount;
extern int rows;
extern int columns;
extern int coordinatex;
extern int coordinatey;
// Declare the vector
extern std::vector<int> filenumbers;
extern int selectionx;
extern int selectiony;
extern int scrollupsindrivesbox;
#endif // MAIN_H_INCLUDED
