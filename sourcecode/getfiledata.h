#ifndef GETFILEDATA_H_INCLUDED
#define GETFILEDATA_H_INCLUDED

std::string getFileModificationTime(const std::string& filePath);
int readfilenames(string origin = "notspecified");
extern std::string path;
struct fileinfo {
        std::string filename;
        std::string filedateandtime;
        };
extern std::vector<fileinfo> filenamelistings; // Declare the vector

#endif // GETFILEDATA_H_INCLUDED
