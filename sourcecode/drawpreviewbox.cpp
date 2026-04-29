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
#include <cstdint>
#include <filesystem>
#define FIONREAD	0x541B
#include <main.h>
#include <displayfiles.h>
#include <filenamehighlight.h>
#include <keypressdetection.h>
#include <getfiledata.h>
#include <drawfilesbox.h>
#include <cleanpreviewbox.h>
#pragma pack(push, 1) // Ensure no padding in structures
// Structure for the Central Directory File Header
struct CentralDirectoryFileHeader {
    uint32_t signature; // 0x02014b50
    uint16_t versionMadeBy;
    uint16_t versionNeeded;
    uint16_t generalPurposeBitFlag;
    uint16_t compressionMethod;
    uint16_t lastModFileTime;
    uint16_t lastModFileDate;
    uint32_t crc32;
    uint32_t compressedSize;
    uint32_t uncompressedSize;
    uint16_t fileNameLength;
    uint16_t extraFieldLength;
    uint16_t fileCommentLength;
    uint16_t diskNumberStart;
    uint16_t internalFileAttributes;
    uint32_t externalFileAttributes;
    uint32_t relativeOffsetOfLocalHeader;
    // Followed by fileName, extraField, and fileComment
};

#pragma pack(pop)

const uint32_t CENTRAL_DIRECTORY_SIGNATURE = 0x02014b50;

void readZipFile(const std::string& zipFilePath) {
    std::ifstream zipFile(zipFilePath, std::ios::binary);
    if (!zipFile) {
        std::cerr << "Error opening zip file for read: " << zipFilePath << std::endl;
        return;
    }

    // Move to the end of the file to find the central directory
    zipFile.seekg(-22, std::ios::end); // Go to the end of the file minus the size of the End of Central Directory record
    uint32_t endOfCentralDirSignature;
    zipFile.read(reinterpret_cast<char*>(&endOfCentralDirSignature), sizeof(endOfCentralDirSignature));

    if (endOfCentralDirSignature != 0x06054b50) {
        std::cerr << "Not a valid ZIP file." << std::endl;
        return;
    }

    // Read the Central Directory
    zipFile.seekg(-22, std::ios::end); // Go back to the start of the End of Central Directory record
    zipFile.seekg(16, std::ios::cur); // Skip to the start of the Central Directory offset
    uint32_t centralDirectoryOffset;
    zipFile.read(reinterpret_cast<char*>(&centralDirectoryOffset), sizeof(centralDirectoryOffset));

    // Move to the Central Directory
    zipFile.seekg(centralDirectoryOffset, std::ios::beg);

    // Read Central Directory entries
    while (true) {
        CentralDirectoryFileHeader header;
        zipFile.read(reinterpret_cast<char*>(&header), sizeof(header));

        if (header.signature != CENTRAL_DIRECTORY_SIGNATURE) {
            break; // No more entries
        }

        // Read the file name
        std::vector<char> fileName(header.fileNameLength);
        zipFile.read(fileName.data(), header.fileNameLength);
        std::string fileNameStr(fileName.data(), header.fileNameLength);

        // Print the file name
        std::cout << "File: " << fileNameStr << std::endl;

        // Skip extra field and file comment
        zipFile.seekg(header.extraFieldLength + header.fileCommentLength, std::ios::cur);
    }

    zipFile.close();
}
int possiblerowsinpreviewbox = rows / 2 - 2;
int writecontentsinpreviewbox();
bool isZipFile(const std::string& filePath) {
if (!std::filesystem::is_fifo(filenamelistings[filenamelistingscount].filename) && !std::filesystem::is_directory(filenamelistings[filenamelistingscount].filename)) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
    //movecursortoanyterminallocation(21,2);
    //std::cerr << "Error opening zip file: " << filePath;
        return false;
    }

    // Read the first 4 bytes
    uint32_t signature;
    file.read(reinterpret_cast<char*>(&signature), sizeof(signature));

    // Check for the ZIP file signature (0x04034b50)
    if (signature == 0x04034b50) {
        return true; // It's a ZIP file
    }

    // Optionally, you can check for other signatures
    // Reset the file pointer to check for the Central Directory signature
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(&signature), sizeof(signature));
    if (signature == 0x02014b50) {
        return true; // It's a ZIP file (Central Directory)
    }

    // Reset the file pointer to check for the End of Central Directory signature
    file.seekg(-22, std::ios::end); // Move to the end of the file minus the size of the End of Central Directory record
    file.read(reinterpret_cast<char*>(&signature), sizeof(signature));
    if (signature == 0x06054b50) {
        return true; // It's a ZIP file (End of Central Directory)
    }

    return false; // Not a ZIP file
}
else {
return false;
}
}
std::string isTextFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary); // Open file in binary mode
    if (!file.is_open()) {
       // std::cerr << "Error opening text file: " << filename << std::endl;
        return "openerror"; // File could not be opened
    }

    char ch;
    while (file.get(ch)) { // Read character by character
        // Check if the character is printable or a newline/carriage return
        if (!std::isprint(static_cast<unsigned char>(ch)) && ch != '\n' && ch != '\r') {
            return "nontext"; // Found a non-text character
        }
    }

    return "text"; // All characters are printable or valid line endings
}

int drawpreviewbox() {
isZipFile(path);
//system("clear");
printacharacterinanyterminallocation(rows / 2,columns,"─");
printacharacterinanyterminallocation(rows / 2,1,"┌");
printacharacterinanyterminallocation(rows / 2,columns,"┐");
printacharacterinanyterminallocation(rows - 1,1,"└");
for (int previewrow = rows - 1;previewrow != rows / 2;previewrow--){
printacharacterinanyterminallocation(previewrow,1,"│");
putchar('\n');
}
movecursortoanyterminallocation(1,1);
for (int previewrow = rows - 1;previewrow != rows / 2;previewrow--){
printacharacterinanyterminallocation(previewrow,columns,"│");
//system("sleep 1");
putchar('\n');
}
for (int previewcolummn = columns - 1;previewcolummn > 1;previewcolummn--) {
printacharacterinanyterminallocation(rows / 2,previewcolummn,"─");
putchar('\n');
}
for (int previewcolummn = columns - 1;previewcolummn > 1;previewcolummn--) {
printacharacterinanyterminallocation(rows - 1,previewcolummn,"─");
putchar('\n');
}
printacharacterinanyterminallocation(rows - 1,1,"└");
printacharacterinanyterminallocation(rows - 1,columns,"┘");
printacharacterinanyterminallocation(rows - 1,columns - 1,"─");
printacharacterinanyterminallocation(rows - 1,columns - 2,"─");
printacharacterinanyterminallocation(rows - 1,columns - 3,"─");
printacharacterinanyterminallocation(rows - 1,columns - 4,"─");
movecursortoanyterminallocation(rows / 2,columns - 57);
std::cout << "Preview(only for text and zip files)";
printacharacterinanyterminallocation(rows / 2 + 1,columns - 1,"-");
int possiblerows;
//std::cout <<
putchar('\n');
//writecontentsinpreviewbox();
}
int writecontentsinpreviewbox() {
cleanpreviewbox();
int row = rows / 2 + 1;
possiblerowsinpreviewbox = rows / 2 - 2;
//std::cout << possiblerowsinpreviewbox << std::endl;
std::string textfilecheckresponse = "noresponse";
if (!std::filesystem::is_fifo(filenamelistings[filenamelistingscount].filename) && !std::filesystem::is_directory(filenamelistings[filenamelistingscount].filename)) {
textfilecheckresponse = isTextFile(filenamelistings[filenamelistingscount].filename); //issue with 0666 file in my machine
}
//std::cout << "test1234" << std::endl;
if (!std::filesystem::is_directory(filenamelistings[filenamelistingscount].filename) && textfilecheckresponse == "text") {
//std::cout << "test1234" << std::endl;
std::ifstream file(filenamelistings[filenamelistingscount].filename);
std::string line;
std::getline(file, line);
for (int numberoftimes = 0;numberoftimes < possiblerowsinpreviewbox;numberoftimes++) {
movecursortoanyterminallocation(row,2);
if (line.size() > columns - 2) {
std::cout << line.substr(0, columns - 5) << "..." << std::endl;
}
else if (line.size() <= columns - 2) {
std::cout << line.substr(0, columns - 2) << std::endl;
}
row++;
std::getline(file, line);
//putchar('\n');
}
}
else if (isZipFile(filenamelistings[filenamelistingscount].filename) && !std::filesystem::is_directory(filenamelistings[filenamelistingscount].filename)) {
std::ifstream zipFile(filenamelistings[filenamelistingscount].filename, std::ios::binary);
    if (!zipFile) {
        std::cerr << "Error opening zip file for show: " << filenamelistings[filenamelistingscount].filename << std::endl;
    }

    // Move to the end of the file to find the central directory
    zipFile.seekg(-22, std::ios::end); // Go to the end of the file minus the size of the End of Central Directory record
    uint32_t endOfCentralDirSignature;
    zipFile.read(reinterpret_cast<char*>(&endOfCentralDirSignature), sizeof(endOfCentralDirSignature));

    if (endOfCentralDirSignature != 0x06054b50) {
        std::cerr << "Not a valid ZIP file." << std::endl;
    }

    // Read the Central Directory
    zipFile.seekg(-22, std::ios::end); // Go back to the start of the End of Central Directory record
    zipFile.seekg(16, std::ios::cur); // Skip to the start of the Central Directory offset
    uint32_t centralDirectoryOffset;
    zipFile.read(reinterpret_cast<char*>(&centralDirectoryOffset), sizeof(centralDirectoryOffset));

    // Move to the Central Directory
    zipFile.seekg(centralDirectoryOffset, std::ios::beg);

    // Read Central Directory entries
  for (int numberoftimes = 0;numberoftimes < possiblerowsinpreviewbox;numberoftimes++) {
CentralDirectoryFileHeader header;
        zipFile.read(reinterpret_cast<char*>(&header), sizeof(header));
        if (header.signature != CENTRAL_DIRECTORY_SIGNATURE) {
            break; // No more entries
        }
        // Read the file name
        std::vector<char> fileName(header.fileNameLength);
        zipFile.read(fileName.data(), header.fileNameLength);
        std::string fileNameStr(fileName.data(), header.fileNameLength);
        // Print the file name
        movecursortoanyterminallocation(row,2);
        std::cout << fileNameStr << std::endl;
        // Skip extra field and file comment
        zipFile.seekg(header.extraFieldLength + header.fileCommentLength, std::ios::cur);
row++;
//putchar('\n');
}
    zipFile.close();
}
}

