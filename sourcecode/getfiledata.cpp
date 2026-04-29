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
struct fileinfo {
        std::string filename;
        std::string filedateandtime;
        };
bool finishloop = false;
std::string getFileModificationTime(const std::string& filePath) {
    struct stat fileStat;
    // Get file status
    if (stat(filePath.c_str(), &fileStat) != 0) {
    //std::cout << "filePath:" << filePath;
    //putchar('\n');
        perror("stat");
        return "";
    }
    // Get the modification time
    std::time_t modTime = fileStat.st_mtime;
    // Convert to local time
    std::tm* localTime = std::localtime(&modTime);
    // Format the time into a string
    std::ostringstream oss;
    oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
std::string path;
    std::vector<fileinfo> filenamelistings;
    vector<int> filenumbers;
    int readfilenames(string origin = "notspecified") {
    const char* pathforchdir = path.c_str();
    chdir(pathforchdir);
    DIR *dir;
    struct dirent *ent;
    opendirectory:
    if (origin != "codeforrefresh") {
    while (finishloop == false) {
    system("clear");
  //  std::cout << "Enter path" << std::endl;
path = "/";
//std::cin >> path;
const char* pathinchar = path.c_str();
chdir(pathinchar);
if ((dir = opendir(path.c_str())) != NULL) {
    finishloop = true; }
}
//cin.ignore(numeric_limits<streamsize>::max(),'\n');
        while ((ent = readdir(dir)) != NULL) {
            //if (ent->d_name[0] != '.') { // Skip hidden files
            std::string dot = ".";
            std::string twodots = "..";
            if (ent->d_name != dot && ent->d_name != twodots) {
            fileanddircount++;
            fileinfo file;
            file.filename = ent->d_name;
            file.filedateandtime = getFileModificationTime(path + ent->d_name);
            filenamelistings.push_back(file);
            //}
            }
        }
        closedir(dir);
        std::cout << "\033[2J";
        }
        else if (origin == "codeforrefresh") {
        //std::cout << path;
        if (path != "/") {
        fileinfo levelup;
        levelup.filename = "..";
        filenamelistings.push_back(levelup);
        }
        //else {
        //goto opendirectory;
        //}
        if ((dir = opendir(path.c_str())) != NULL) {
        //std::cout << std::endl << "NewPath:" << path << std::endl;
        while ((ent = readdir(dir)) != NULL) {
            //if (ent->d_name[0] != '.') { // Skip hidden files
            std::string dot = ".";
            std::string twodots = "..";
            if (ent->d_name != dot && ent->d_name != twodots) {
            //fileanddircount++;
            fileinfo file;
            file.filename = ent->d_name;
            file.filedateandtime = getFileModificationTime(ent->d_name);
            //if (file.filename != "." && file.filename != "..") {
            filenamelistings.push_back(file);
            //}
            //}
            }
        }
        }
        closedir(dir);
        }
        //std::cout << "File and directory count:" << fileanddircount << std::endl;
        }
