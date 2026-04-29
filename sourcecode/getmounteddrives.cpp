#include <iostream>
#include <vector>
#include <string>
#include <sys/statvfs.h>
#include <dirent.h>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <mntent.h>
#include <stdio.h>
/*
int mountcount = 0;
struct MountedVolume {
    std::string mountPoint;
    std::string devicePath;
    std::string label;
};

std::vector<MountedVolume> driveslistings;
std::string getDevicePath(const std::string& mountPoint) {
    std::ifstream mountsFile("/proc/mounts");
    std::string line;
    // Check if the file is open
    if (!mountsFile.is_open()) {
        std::cerr << "Error opening /proc/mounts" << std::endl;
        return "";
    }
    // Read each line from /proc/mounts
    while (std::getline(mountsFile, line)) {
        // Split the line into tokens
        std::istringstream iss(line);
        std::string device, mount, fstype, options;
        // Read the device, mount point, filesystem type, and options
        if (iss >> device >> mount >> fstype >> options) {
            // Check if the mount point matches
            if (mount == mountPoint) {
                return device; // Return the device path
            }
        }
    }
    // If the mount point was not found
    std::cerr << "Mount point not found: " << mountPoint << std::endl;
    //volumes.erase(volumes.begin() + mountcount - 1);
    return "nopath";
}
std::string getVolumeLabel(const std::string& device) {
    std::string command = "blkid -s LABEL -o value " + device;
    char buffer[128];
    std::string result = "";

    // Open the command for reading
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "popen() failed!" << std::endl;
        return result;
    }

    // Read the output a line at a time - output it.
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
        //std::cout << result;
    }

    // Close the pipe
    pclose(pipe);

    // Remove newline character from the result
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }

    return result;
}

std::vector<MountedVolume> getMountedVolumes() {
    DIR* dir = opendir("/mnt"); // Check the /mnt directory for mounted volumes
    struct dirent* entry;
    MountedVolume volume;
     volume.mountPoint = "/";
    volume.label = "Root directory";
    driveslistings.push_back(volume);
    mountcount++;

    if (dir == nullptr) {
        std::cerr << "Failed to open /mnt directory." << std::endl;
        return driveslistings;
    }

    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
        mountcount++;
            std::string mountPoint = "/mnt/" + std::string(entry->d_name);
            //std::string label = ""; // Get the volume label

            volume.mountPoint = mountPoint;
            volume.devicePath = getDevicePath(mountPoint);
            volume.label = getVolumeLabel(volume.devicePath);
            if (volume.devicePath != "nopath") {
            driveslistings.push_back(volume);
            mountcount++;
            }
        }
    }

    closedir(dir);
    DIR* dir1 = opendir("/media"); // Check the /mnt directory for mounted volumes
    struct dirent* entry1;

    if (dir == nullptr) {
        std::cerr << "Failed to open /mnt directory." << std::endl;
        return driveslistings;
    }

    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            std::string mountPoint = "/mnt/" + std::string(entry->d_name);
            //std::string label = ""; // Get the volume label
mountcount++;
            MountedVolume volume;
            volume.mountPoint = mountPoint;
            volume.devicePath = getDevicePath(mountPoint);
            volume.label = getVolumeLabel(volume.devicePath);
            if (volume.devicePath != "nopath") {
            driveslistings.push_back(volume);
            mountcount++;
            }
        }
    }

    closedir(dir1);
    return driveslistings;
}
/*
int main() {
    std::vector<MountedVolume> volumes = getMountedVolumes();

    std::cout << "Mounted Volumes:\n";
    for (const auto& volume : volumes) {
        std::cout << "Mount Point: " << volume.mountPoint
                  << ", Label: " << (volume.label.empty() ? "No Label" : volume.label) << std::endl;
    }
std::cout << "Volumes:" << volumes.size();
std::cout << "Volume 1:" << volumes[0].mountPoint;
//std::cout << "Volume 2:" << volumes[1].mountPoint;
//std::cout << "Volume 3:" << volumes[2].mountPoint;
//std::cout << "Volume 4:" << volumes[3].mountPoint;
    return 0;
}
*/
int mountcount = 0;
struct MountedVolume {
    std::string mountPoint;
    std::string devicePath;
    std::string label;
};
std::vector<MountedVolume> driveslistings;
std::string getDevicePath(const std::string& mountPoint) {
    std::ifstream mountsFile("/proc/mounts");
    std::string line;
    // Check if the file is open
    if (!mountsFile.is_open()) {
        std::cerr << "Error opening /proc/mounts" << std::endl;
        return "";
    }
    // Read each line from /proc/mounts
    while (std::getline(mountsFile, line)) {
        // Split the line into tokens
        std::istringstream iss(line);
        std::string device, mount, fstype, options;
        // Read the device, mount point, filesystem type, and options
        if (iss >> device >> mount >> fstype >> options) {
            // Check if the mount point matches
            if (mount == mountPoint) {
                return device; // Return the device path
            }
        }
    }
    // If the mount point was not found
    std::cerr << "Mount point not found: " << mountPoint << std::endl;
    //volumes.erase(volumes.begin() + mountcount - 1);
    return "nopath";
}
std::string getVolumeLabel(const std::string& device) {
    std::string command = "blkid -s LABEL -o value " + device;
    char buffer[128];
    std::string result = "";

    // Open the command for reading
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "popen() failed!" << std::endl;
        return result;
    }

    // Read the output a line at a time - output it.
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
        //std::cout << result;
    }

    // Close the pipe
    pclose(pipe);

    // Remove newline character from the result
    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }

    return result;
}
//std::vector<MountedVolume> driveslistings;
bool is_valid_volume(const char* fstype) {
    // List of valid filesystem types
    const char* valid_fstypes[] = {"ext4", "xfs", "btrfs", "vfat", "ntfs", "ext3", "ext2","fuseblk","exfat","fat32","fat16","fat",nullptr};

    for (int i = 0; valid_fstypes[i] != nullptr; ++i) {
        if (strcmp(fstype, valid_fstypes[i]) == 0) {
            return true;
        }
    }
    return false;
}
std::vector<MountedVolume> getMountedVolumes() {
    FILE *mounts = setmntent("/proc/mounts", "r");
   if (mounts == nullptr) {
       std::cerr << "Error opening /proc/mounts" << std::endl;
        exit(0);
    }

    struct mntent *mnt;
    struct MountedVolume volume;
    volume.mountPoint = "/";
    volume.label = "Root directory";
    driveslistings.push_back(volume);
    mountcount++;
    while ((mnt = getmntent(mounts)) != nullptr) {
        if (is_valid_volume(mnt->mnt_type)) {
        volume.mountPoint = mnt->mnt_dir;
            volume.devicePath = getDevicePath(volume.mountPoint);
            volume.label = getVolumeLabel(volume.devicePath);
            if (volume.devicePath != "nopath" && volume.mountPoint != "/" && volume.mountPoint != "/boot/efi") {
            driveslistings.push_back(volume);
            mountcount++;
            }
            std::cout << "Device: " << volume.devicePath << std::endl;
            std::cout << "Mount Point: " << volume.mountPoint << std::endl;
            //std::cout << "File System Type: " << mnt->mnt_type << std::endl;
            std::cout << "Label: " << volume.label << std::endl;
            std::cout << "-----------------------------------" << std::endl;
       //char test = getchar();
       //system("sleep 5");
        }
    }

    endmntent(mounts);
    std::cout << "size:" << driveslistings.size() << std::endl;
    //char test = getchar();
//    return 0;
return driveslistings;
        }
//    closedir(dir1);
    //return driveslistings;
