#ifndef KEYPRESSDETECTION_H_INCLUDED
#define KEYPRESSDETECTION_H_INCLUDED

int keypressdetection();
extern int scrollupsindrivesbox;
extern int scrolldownsindrivesbox;
extern int scrolldownsinfilesbox;
extern int xcoordinate;
extern int ycoordinate;
extern bool menubarmode;
extern bool copyfileoverwritedialogmode;
extern bool copydirectoryoverwritedialogmode;
extern bool movefileoverwritedialogmode;
extern bool movedirectoryoverwritedialogmode;
extern bool newfolderdialogmode;
extern bool deletefiledialogmode;
extern bool deletedirectorydialogmode;
extern int xcoordinateformenubar;
extern int countformovingdowninfilesbox;
extern int coordinateforinputfieldinnewfolderdialog;
extern string filepath;
extern string fileorfolderpathforcheckofexistenceindestination;
extern int coordinateforcopyexistingfiledialog;

#endif // KEYPRESSDETECTION_H_INCLUDED
