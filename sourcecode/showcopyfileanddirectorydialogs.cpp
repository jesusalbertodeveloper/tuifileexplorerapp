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
#include <keypressdetection.h>
int showcopyfileoverwritedialog() {
if (fileorfolderpathforcheckofexistenceindestination != path) {
//std::cout << fileorfolderpathforcheckofexistenceindestination << std::endl;
//std::cout << path << std::endl;
//getchar();
/*
if (fileorfolderpathforcheckofexistenceindestination != path) {
  std::cout << "File already exists.Do you want to give the new file a new name or overwrite the existing one?" << std::endl;
  std::cout << "Y overwrites,R gives the new file a new name and N cancels the operation altogether" << std::endl;
  char answer = getchar();
  //toupper(answer);
  if (answer == 'Y' || answer == 'y') {
  const auto copyOptions = std::filesystem::copy_options::overwrite_existing;
std::filesystem::copy(filepath,path,copyOptions);
  }
  //if (answer == 'M' || answer == 'm') {
  //const auto copyOptions = std::filesystem::copy_options::recursive |
  //std::filesystem::copy_options::skip_existing;
//std::filesystem::copy(filepath,path,copyOptions);
  //}
   if (toupper(answer) == 'R') {
  //const auto copyOptions = std::filesystem::copy_options::recursive |
  //std::filesystem::copy_options::skip_existing;
  bool newfilenamingcompleted = false;
  string newfilename = "notset";
  while (newfilenamingcompleted == false){
  std::cout << "New name?If you want to overwrite the existing file instead type O" << std::endl;
  std::cin >> newfilename;
  std::size_t found = filepath.find_last_of("/");
  if (newfilename == filepath.substr(found+1)) {
  std::cout << "Filename is the same as the previous one!.If you want to overwrite simply type O" << std::endl;
  getchar();
  }
  else if (newfilename == "O") {
  const auto copyOptions = std::filesystem::copy_options::overwrite_existing;
std::filesystem::copy(filepath,path,copyOptions);
newfilenamingcompleted = true;
break;
  }
  else {
    }
    std::string newpath = path + "/" + newfilename;
//    newpath.push_back("/" + newfilename);
std::filesystem::copy(filepath,newpath);
newfilenamingcompleted = true;
break;
  }
  }
  if (toupper(answer) == 'N') {
  std::cout << "The operation has been canceled" << std::endl;
  }
}
else if (fileorfolderpathforcheckofexistenceindestination == path) {
  std::cout << "File already exists.Do you want to give the new file a new name?.You can't overwrite the file since you are pasting to the same directory in where the file was copied from" << std::endl;
  std::cout << "R gives the new file a new name and N cancels the operation altogether" << std::endl;
  char answer = getchar();
  //toupper(answer);
   if (toupper(answer) == 'R') {
  //const auto copyOptions = std::filesystem::copy_options::recursive |
  //std::filesystem::copy_options::skip_existing;
  bool newfilenamingcompleted = false;
  string newfilename = "notset";
  while (newfilenamingcompleted == false){
  std::cout << "New name?If you want to overwrite the existing file instead type O" << std::endl;
  std::cin >> newfilename;
  std::size_t found = filepath.find_last_of("/");
  if (newfilename == filepath.substr(found+1)) {
  std::cout << "Filename is the same as the previous one!.Try again with a different name" << std::endl;
  getchar();
  }
  else {
    std::string newpath = path + "/" + newfilename;
//    newpath.push_back("/" + newfilename);
std::filesystem::copy(filepath,newpath);
newfilenamingcompleted = true;
break;
  }
  }
  if (toupper(answer) == 'N') {
  std::cout << "The operation has been canceled" << std::endl;
  }
}
}
}
*/
setBackgroundColor(1);
printacharacterinanyterminallocation(6,10,"┌");
printacharacterinanyterminallocation(7,10,"│");
printacharacterinanyterminallocation(8,10,"│");
printacharacterinanyterminallocation(9,10,"│");
printacharacterinanyterminallocation(10,10,"│");
printacharacterinanyterminallocation(11,10,"│");
printacharacterinanyterminallocation(12,10,"│");
printacharacterinanyterminallocation(13,10,"│");
printacharacterinanyterminallocation(14,10,"│");
printacharacterinanyterminallocation(15,10,"│");
printacharacterinanyterminallocation(16,10,"│");
printacharacterinanyterminallocation(17,10,"│");
printacharacterinanyterminallocation(18,10,"│");
printacharacterinanyterminallocation(19,10,"└");
printacharacterinanyterminallocation(6,11,"─");
printacharacterinanyterminallocation(6,12,"─");
printacharacterinanyterminallocation(6,13,"─");
printacharacterinanyterminallocation(6,14,"─");
printacharacterinanyterminallocation(6,15,"─");
printacharacterinanyterminallocation(6,16,"─");
printacharacterinanyterminallocation(6,17,"─");
printacharacterinanyterminallocation(6,18,"─");
printacharacterinanyterminallocation(6,19,"─");
printacharacterinanyterminallocation(6,20,"─");
printacharacterinanyterminallocation(6,21,"─");
printacharacterinanyterminallocation(6,22,"─");
printacharacterinanyterminallocation(6,23,"─");
printacharacterinanyterminallocation(6,24,"─");
printacharacterinanyterminallocation(6,25,"─");
printacharacterinanyterminallocation(6,26,"─");
printacharacterinanyterminallocation(6,27,"─");
printacharacterinanyterminallocation(6,28,"─");
//printacharacterinanyterminallocation(6,28," ");
printacharacterinanyterminallocation(6,29,"─");
printacharacterinanyterminallocation(6,30,"─");
printacharacterinanyterminallocation(6,31,"─");
printacharacterinanyterminallocation(6,32,"─");
printacharacterinanyterminallocation(6,33,"─");
printacharacterinanyterminallocation(6,34,"─");
printacharacterinanyterminallocation(6,35,"O");
printacharacterinanyterminallocation(6,36,"v");
printacharacterinanyterminallocation(6,37,"e");
printacharacterinanyterminallocation(6,38,"r");
printacharacterinanyterminallocation(6,39,"w");
printacharacterinanyterminallocation(6,40,"r");
printacharacterinanyterminallocation(6,41,"i");
printacharacterinanyterminallocation(6,42,"t");
printacharacterinanyterminallocation(6,43,"e");
printacharacterinanyterminallocation(6,44,"?");
printacharacterinanyterminallocation(6,45,"─");
printacharacterinanyterminallocation(6,46,"─");
//printacharacterinanyterminallocation(6,47,"?");
for (int colummn = 47;colummn < 70;colummn++) {
printacharacterinanyterminallocation(6,colummn,"─");
}
printacharacterinanyterminallocation(6,70,"┐");
printacharacterinanyterminallocation(7,70,"│");
printacharacterinanyterminallocation(8,70,"│");
printacharacterinanyterminallocation(9,70,"│");
printacharacterinanyterminallocation(10,70,"│");
printacharacterinanyterminallocation(11,70,"│");
printacharacterinanyterminallocation(12,70,"│");
printacharacterinanyterminallocation(13,70,"│");
printacharacterinanyterminallocation(14,70,"│");
printacharacterinanyterminallocation(15,70,"│");
printacharacterinanyterminallocation(16,70,"│");
printacharacterinanyterminallocation(17,70,"│");
printacharacterinanyterminallocation(18,70,"│");
printacharacterinanyterminallocation(19,70,"┘");
printacharacterinanyterminallocation(19,10,"└");
std::cout << "The first " << "5" << " characters are: " << filenamelistings[filenamelistingscount].filename.substr(0, 5) << std::endl;
for (int colummn = 11;colummn < 70;colummn++) {
printacharacterinanyterminallocation(19,colummn,"─");
}
movecursortoanyterminallocation(7,11);
if (filenamelistings[filenamelistingscount].filename.size() == 10) {
std::cout << "Do you want to overwrite the file " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
//printacharacterinanyterminallocation(7,63," ");
//printacharacterinanyterminallocation(7,64," ");
//printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 9) {
std::cout << "Do you want to overwrite the file " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 8) {
std::cout << "Do you want to overwrite the file " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?" << "";
printacharacterinanyterminallocation(7,54," ");
printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 7) {
std::cout << "Do you want to overwrite the file " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
printacharacterinanyterminallocation(7,53," ");
printacharacterinanyterminallocation(7,54," ");
printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 6) {
std::cout << "Do you want to overwrite the file " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
printacharacterinanyterminallocation(7,52," ");
printacharacterinanyterminallocation(7,53," ");
printacharacterinanyterminallocation(7,54," ");
printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 5) {
std::cout << "Do you want to overwrite the file " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
printacharacterinanyterminallocation(7,51," ");
printacharacterinanyterminallocation(7,52," ");
printacharacterinanyterminallocation(7,53," ");
printacharacterinanyterminallocation(7,54," ");
printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 4) {
std::cout << "Do you want to overwrite the file " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
printacharacterinanyterminallocation(7,50," ");
printacharacterinanyterminallocation(7,51," ");
printacharacterinanyterminallocation(7,52," ");
printacharacterinanyterminallocation(7,53," ");
printacharacterinanyterminallocation(7,54," ");
printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 3) {
std::cout << "Do you want to overwrite the file " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
printacharacterinanyterminallocation(7,49," ");
printacharacterinanyterminallocation(7,50," ");
printacharacterinanyterminallocation(7,51," ");
printacharacterinanyterminallocation(7,52," ");
printacharacterinanyterminallocation(7,53," ");
printacharacterinanyterminallocation(7,54," ");
printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 2) {
std::cout << "Do you want to overwrite the file " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
printacharacterinanyterminallocation(7,48," ");
printacharacterinanyterminallocation(7,49," ");
printacharacterinanyterminallocation(7,50," ");
printacharacterinanyterminallocation(7,51," ");
printacharacterinanyterminallocation(7,52," ");
printacharacterinanyterminallocation(7,53," ");
printacharacterinanyterminallocation(7,54," ");
printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 1) {
std::cout << "Do you want to overwrite the file " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
printacharacterinanyterminallocation(7,47," ");
printacharacterinanyterminallocation(7,48," ");
printacharacterinanyterminallocation(7,49," ");
printacharacterinanyterminallocation(7,50," ");
printacharacterinanyterminallocation(7,51," ");
printacharacterinanyterminallocation(7,52," ");
printacharacterinanyterminallocation(7,53," ");
printacharacterinanyterminallocation(7,54," ");
printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else {
std::cout << "Do you want to overwrite the file " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "..." << "?" << "    ";
}
movecursortoanyterminallocation(8,11);
std::cout << "You can overwrite the file or you can give it a new    ";
printacharacterinanyterminallocation(8,66," ");
printacharacterinanyterminallocation(8,67," ");
printacharacterinanyterminallocation(8,68," ");
printacharacterinanyterminallocation(8,69," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,61," ");
//printacharacterinanyterminallocation(7,60," ");
//printacharacterinanyterminallocation(7,59," ");
//printacharacterinanyterminallocation(7,58," ");
//printacharacterinanyterminallocation(7,57," ");
//printacharacterinanyterminallocation(7,56," ");
//printacharacterinanyterminallocation(7,55," ");
//printacharacterinanyterminallocation(7,54," ");
movecursortoanyterminallocation(9,11);
std::cout << "name.Keep in mind that overwritten files cannot be         ";
movecursortoanyterminallocation(10,11);
std::cout << "recovered not even with data recovery software so make sure";
movecursortoanyterminallocation(11,11);
std::cout << "that you really want to overwrite this file.You can also   ";
movecursortoanyterminallocation(12,11);
std::cout << "give the file a new name instead of overwriting the        ";
movecursortoanyterminallocation(13,11);
std::cout << "existing file.The Overwrite option overwrites the existing ";
movecursortoanyterminallocation(14,11);
std::cout << "file while the new name option gives the new file a new    ";
movecursortoanyterminallocation(15,11);
std::cout << "name                                                       ";
movecursortoanyterminallocation(16,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(17,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(18,11);
std::cout << "                   ";
movecursortoanyterminallocation(18,11);
std::cout << "                   ";
movecursortoanyterminallocation(18,37);
std::cout << "                                 ";
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
printacharacterinanyterminallocation(18,46," ");
printacharacterinanyterminallocation(18,47," ");
printacharacterinanyterminallocation(18,48," ");
printacharacterinanyterminallocation(18,49," ");
printacharacterinanyterminallocation(18,50," ");
printacharacterinanyterminallocation(18,51," ");
printacharacterinanyterminallocation(18,52," ");
printacharacterinanyterminallocation(18,53," ");
printacharacterinanyterminallocation(18,54," ");
printacharacterinanyterminallocation(18,55," ");
printacharacterinanyterminallocation(18,56," ");
printacharacterinanyterminallocation(18,57," ");
printacharacterinanyterminallocation(18,58," ");
printacharacterinanyterminallocation(18,59," ");
printacharacterinanyterminallocation(18,60," ");
printacharacterinanyterminallocation(18,62," ");
printacharacterinanyterminallocation(18,63," ");
printacharacterinanyterminallocation(18,64," ");
printacharacterinanyterminallocation(18,65," ");
printacharacterinanyterminallocation(18,66," ");
printacharacterinanyterminallocation(18,67," ");
//std::cout << "The first " << "5" << " characters are: " << filenamelistings[filenamelistingscount].filename.substr(0, 5) << std::endl;
putchar('\n');
//printacharacterinanyterminallocation(6,70,"┌");
}
else {
movecursortoanyterminallocation(rows - 9,1);
std::cout << "Cant copy file to itself!.Do you want to copy the file under a new name?(Y/N)" << std::endl;
char answer = getchar();
if (toupper(answer) == 'Y') {
std::cout << "New name?.Type c to cancel" << std::endl;
std::string newname;
std::cin >> newname;
if (newname != "cancel") {
 std::size_t found = filepath.find_last_of("/");
  if (newname == filepath.substr(found+1)) {
  std::cout << "The file name is the same as the previous one!.No copying made" << std::endl;
  getchar();
  }
  else {
try {
std::filesystem::copy(filepath,newname);
}
catch (...) {
std::cout << "An error occured during copying!.Make sure that you have permission to copy and that the filesystem isnt read-only" << std::endl;
std::cout << "Normal operation will continue after 10 seconds" << std::endl;
usleep(10000000);
}
}
}
else {
std::cout << "Operation cancelled!" << std::endl;
}
}
}
}
int showcopydirectoryoverwritedialog() {
/*
if (fileorfolderpathforcheckofexistenceindestination != path) {
  std::cout << "Folder already exists.Do you want to merge and overwrite?" << std::endl;
  std::cout << "Y merges and overwrites,M just merges without overwrite and N cancels the operation altogether" << std::endl;
  char answer = getchar();
  //toupper(answer);
  if (answer == 'Y' || answer == 'y') {
  const auto copyOptions = std::filesystem::copy_options::recursive |
  std::filesystem::copy_options::overwrite_existing;
std::filesystem::copy(filepath,path,copyOptions);
  }
  if (answer == 'M' || answer == 'm') {
  const auto copyOptions = std::filesystem::copy_options::recursive |
  std::filesystem::copy_options::skip_existing;
std::filesystem::copy(filepath,path,copyOptions);
  }
     if (toupper(answer) == 'R') {
  //const auto copyOptions = std::filesystem::copy_options::recursive |
  //std::filesystem::copy_options::skip_existing;
  bool newfoldernamingcompleted = false;
  string newfoldername = "notset";
  while (newfoldernamingcompleted == false){
  std::cout << "New name?If you want to overwrite the existing folder instead type O" << std::endl;
  std::cin >> newfoldername;
  std::size_t found = filepath.find_last_of("/");
  if (newfoldername == filepath.substr(found+1)) {
  std::cout << "The folder name is the same as the previous one!.If you want to overwrite simply type O" << std::endl;
  getchar();
  }
  else if (newfoldername == "O") {
  const auto copyOptions = std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive;
std::filesystem::copy(filepath,path,copyOptions);
newfoldernamingcompleted = true;
break;
  }
  else {
    const auto copyOptions = std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive;
    std::string newpath = path + "/" + newfoldername;
//    newpath.push_back("/" + newfilename);
std::filesystem::copy(filepath,newpath,copyOptions);
newfoldernamingcompleted = true;
break;
  }
  }
  if (toupper(answer) == 'N') {
  std::cout << "The operation has been canceled" << std::endl;
  }
}
}
else if (fileorfolderpathforcheckofexistenceindestination == path) {
  std::cout << "Folder already exists.Do you want to give the new folder a new name?.You can't neither merge nor overwrite files since the folder is being pasted to the same location where the folder was copied from" << std::endl;
  std::cout << "R gives the folder a new name and N cancels the operation altogether" << std::endl;
  char answer = getchar();
  //toupper(answer);
     if (toupper(answer) == 'R') {
  //const auto copyOptions = std::filesystem::copy_options::recursive |
  //std::filesystem::copy_options::skip_existing;
  bool newfoldernamingcompleted = false;
  string newfoldername = "notset";
  while (newfoldernamingcompleted == false){
  std::cout << "New name?" << std::endl;
  std::cin >> newfoldername;
  std::size_t found = filepath.find_last_of("/");
  if (newfoldername == filepath.substr(found+1)) {
  std::cout << "The folder name is the same as the previous one!.Try again with a different name!" << std::endl;
  getchar();
  }
  else {
    const auto copyOptions = std::filesystem::copy_options::overwrite_existing | std::filesystem::copy_options::recursive;
    std::string newpath = path + "/" + newfoldername;
//    newpath.push_back("/" + newfilename);
std::filesystem::copy(filepath,newpath,copyOptions);
newfoldernamingcompleted = true;
break;
  }
  }
  if (toupper(answer) == 'N') {
  std::cout << "The operation has been canceled" << std::endl;
  }
}
}
*/
/*
setBackgroundColor(1);
printacharacterinanyterminallocation(6,10,"┌");
printacharacterinanyterminallocation(7,10,"│");
printacharacterinanyterminallocation(8,10,"│");
printacharacterinanyterminallocation(9,10,"│");
printacharacterinanyterminallocation(10,10,"│");
printacharacterinanyterminallocation(11,10,"│");
printacharacterinanyterminallocation(12,10,"│");
printacharacterinanyterminallocation(13,10,"│");
printacharacterinanyterminallocation(14,10,"│");
printacharacterinanyterminallocation(15,10,"│");
printacharacterinanyterminallocation(16,10,"│");
printacharacterinanyterminallocation(17,10,"│");
printacharacterinanyterminallocation(18,10,"│");
printacharacterinanyterminallocation(19,10,"└");
printacharacterinanyterminallocation(6,11,"─");
printacharacterinanyterminallocation(6,12,"─");
printacharacterinanyterminallocation(6,13,"─");
printacharacterinanyterminallocation(6,14,"─");
printacharacterinanyterminallocation(6,15,"─");
printacharacterinanyterminallocation(6,16,"─");
printacharacterinanyterminallocation(6,17,"─");
printacharacterinanyterminallocation(6,18,"─");
printacharacterinanyterminallocation(6,19,"─");
printacharacterinanyterminallocation(6,20,"─");
printacharacterinanyterminallocation(6,21,"─");
printacharacterinanyterminallocation(6,22,"─");
printacharacterinanyterminallocation(6,23,"─");
printacharacterinanyterminallocation(6,24,"─");
printacharacterinanyterminallocation(6,25,"─");
printacharacterinanyterminallocation(6,26,"─");
printacharacterinanyterminallocation(6,27,"─");
printacharacterinanyterminallocation(6,28,"─");
//printacharacterinanyterminallocation(6,28," ");
printacharacterinanyterminallocation(6,29,"─");
printacharacterinanyterminallocation(6,30,"─");
printacharacterinanyterminallocation(6,31,"─");
printacharacterinanyterminallocation(6,32,"─");
printacharacterinanyterminallocation(6,33,"─");
printacharacterinanyterminallocation(6,34,"─");
printacharacterinanyterminallocation(6,35,"O");
printacharacterinanyterminallocation(6,36,"v");
printacharacterinanyterminallocation(6,37,"e");
printacharacterinanyterminallocation(6,38,"r");
printacharacterinanyterminallocation(6,39,"w");
printacharacterinanyterminallocation(6,40,"r");
printacharacterinanyterminallocation(6,41,"i");
printacharacterinanyterminallocation(6,42,"t");
printacharacterinanyterminallocation(6,43,"e");
printacharacterinanyterminallocation(6,44,"?");
printacharacterinanyterminallocation(6,45,"─");
printacharacterinanyterminallocation(6,46,"─");
//printacharacterinanyterminallocation(6,47,"?");
for (int colummn = 47;colummn < 70;colummn++) {
printacharacterinanyterminallocation(6,colummn,"─");
}
printacharacterinanyterminallocation(6,70,"┐");
printacharacterinanyterminallocation(7,70,"│");
printacharacterinanyterminallocation(8,70,"│");
printacharacterinanyterminallocation(9,70,"│");
printacharacterinanyterminallocation(10,70,"│");
printacharacterinanyterminallocation(11,70,"│");
printacharacterinanyterminallocation(12,70,"│");
printacharacterinanyterminallocation(13,70,"│");
printacharacterinanyterminallocation(14,70,"│");
printacharacterinanyterminallocation(15,70,"│");
printacharacterinanyterminallocation(16,70,"│");
printacharacterinanyterminallocation(17,70,"│");
printacharacterinanyterminallocation(18,70,"│");
printacharacterinanyterminallocation(19,70,"┘");
printacharacterinanyterminallocation(19,10,"└");
std::cout << "The first " << "5" << " characters are: " << filenamelistings[filenamelistingscount].filename.substr(0, 5) << std::endl;
for (int colummn = 11;colummn < 70;colummn++) {
printacharacterinanyterminallocation(19,colummn,"─");
}
movecursortoanyterminallocation(7,11);
if (filenamelistings[filenamelistingscount].filename.size() == 10) {
std::cout << "Do you want to overwrite the folder " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
//printacharacterinanyterminallocation(7,63," ");
//printacharacterinanyterminallocation(7,64," ");
//printacharacterinanyterminallocation(7,65," ");
//printacharacterinanyterminallocation(7,56," ");
//printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 9) {
std::cout << "Do you want to overwrite the folder " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
//printacharacterinanyterminallocation(7,55," ");
//printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 8) {
std::cout << "Do you want to overwrite the folder " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?" << "";
//printacharacterinanyterminallocation(7,54," ");
//printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 7) {
std::cout << "Do you want to overwrite the folder " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
//printacharacterinanyterminallocation(7,53," ");
//printacharacterinanyterminallocation(7,54," ");
printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 6) {
std::cout << "Do you want to overwrite the folder " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
//printacharacterinanyterminallocation(7,52," ");
//printacharacterinanyterminallocation(7,53," ");
printacharacterinanyterminallocation(7,54," ");
printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 5) {
std::cout << "Do you want to overwrite the folder " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
//printacharacterinanyterminallocation(7,51," ");
//printacharacterinanyterminallocation(7,52," ");
printacharacterinanyterminallocation(7,53," ");
printacharacterinanyterminallocation(7,54," ");
printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 4) {
std::cout << "Do you want to overwrite the folder " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
//printacharacterinanyterminallocation(7,50," ");
//printacharacterinanyterminallocation(7,51," ");
printacharacterinanyterminallocation(7,52," ");
printacharacterinanyterminallocation(7,53," ");
printacharacterinanyterminallocation(7,54," ");
printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 3) {
std::cout << "Do you want to overwrite the folder " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
//printacharacterinanyterminallocation(7,49," ");
//printacharacterinanyterminallocation(7,50," ");
printacharacterinanyterminallocation(7,51," ");
printacharacterinanyterminallocation(7,52," ");
printacharacterinanyterminallocation(7,53," ");
printacharacterinanyterminallocation(7,54," ");
printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 2) {
std::cout << "Do you want to overwrite the folder " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
//printacharacterinanyterminallocation(7,48," ");
//printacharacterinanyterminallocation(7,49," ");
printacharacterinanyterminallocation(7,50," ");
printacharacterinanyterminallocation(7,51," ");
printacharacterinanyterminallocation(7,52," ");
printacharacterinanyterminallocation(7,53," ");
printacharacterinanyterminallocation(7,54," ");
printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else if (filenamelistings[filenamelistingscount].filename.size() == 1) {
std::cout << "Do you want to overwrite the folder " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "?";
//printacharacterinanyterminallocation(7,47," ");
//printacharacterinanyterminallocation(7,48," ");
printacharacterinanyterminallocation(7,49," ");
printacharacterinanyterminallocation(7,50," ");
printacharacterinanyterminallocation(7,51," ");
printacharacterinanyterminallocation(7,52," ");
printacharacterinanyterminallocation(7,53," ");
printacharacterinanyterminallocation(7,54," ");
printacharacterinanyterminallocation(7,55," ");
printacharacterinanyterminallocation(7,56," ");
printacharacterinanyterminallocation(7,57," ");
printacharacterinanyterminallocation(7,58," ");
printacharacterinanyterminallocation(7,59," ");
printacharacterinanyterminallocation(7,60," ");
printacharacterinanyterminallocation(7,61," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
}
else {
std::cout << "Do you want to overwrite the folder " << filenamelistings[filenamelistingscount].filename.substr(0, 10) << "..." << "?" << "    ";
}
movecursortoanyterminallocation(8,11);
//55
std::cout << "You can overwrite the folder or you can merge without  ";
printacharacterinanyterminallocation(8,66," ");
printacharacterinanyterminallocation(8,67," ");
printacharacterinanyterminallocation(8,68," ");
printacharacterinanyterminallocation(8,69," ");
printacharacterinanyterminallocation(7,66," ");
printacharacterinanyterminallocation(7,67," ");
printacharacterinanyterminallocation(7,68," ");
printacharacterinanyterminallocation(7,69," ");
printacharacterinanyterminallocation(7,65," ");
printacharacterinanyterminallocation(7,64," ");
printacharacterinanyterminallocation(7,63," ");
printacharacterinanyterminallocation(7,62," ");
printacharacterinanyterminallocation(7,61," ");
//printacharacterinanyterminallocation(7,60," ");
//printacharacterinanyterminallocation(7,59," ");
//printacharacterinanyterminallocation(7,58," ");
//printacharacterinanyterminallocation(7,57," ");
//printacharacterinanyterminallocation(7,56," ");
//printacharacterinanyterminallocation(7,55," ");
//printacharacterinanyterminallocation(7,54," ");
movecursortoanyterminallocation(9,11);
std::cout << "overwriting anything.You can also give the folder a new    ";
movecursortoanyterminallocation(10,11);
std::cout << "name.You can also cancel the operation.Keep in mind that   ";
movecursortoanyterminallocation(11,11);
std::cout << "overwritten files cannot be recovered not even with data   ";
movecursortoanyterminallocation(12,11);
std::cout << "recovery software so make sure that you really want to over";
movecursortoanyterminallocation(13,11);
std::cout << "write files.The Overwrite option deletes the folder and re ";
movecursortoanyterminallocation(14,11);
std::cout << "places it with the new one.The Merge option merges without ";
movecursortoanyterminallocation(15,11);
std::cout << "overwriting while the Merge(overwrite) option merges both  ";
movecursortoanyterminallocation(16,11);
std::cout << "folders without overwriting existing files                 ";
movecursortoanyterminallocation(17,11);
std::cout << "                                                           ";
movecursortoanyterminallocation(18,11);
std::cout << "                   ";
movecursortoanyterminallocation(18,11);
std::cout << "                   ";
movecursortoanyterminallocation(18,37);
std::cout << "                                 ";
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
//std::cout << "The first " << "5" << " characters are: " << filenamelistings[filenamelistingscount].filename.substr(0, 5) << std::endl;
putchar('\n');
*/
movecursortoanyterminallocation(rows - 7,1);
setBackgroundColor(1);
std::cout << "The copying of existing folders has not yet been implemented!" << std::endl;
std::cout << "To copy an existing folder please either:" << std::endl;
std::cout << "-Rename the folder you are copying" << std::endl;
std::cout << "-Rename the destination folder" << std::endl;
std::cout << "-or delete the destination folder" << std::endl;
std::cout << "Normal operation will continue(without the copying of the file after 10 seconds" << std::endl;
setBackgroundColor(4);
usleep(10000000);
}

