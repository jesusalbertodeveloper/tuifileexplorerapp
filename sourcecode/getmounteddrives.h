#ifndef GETMOUNTEDDRIVES_H_INCLUDED
#define GETMOUNTEDDRIVES_H_INCLUDED
struct MountedVolume {
    std::string mountPoint;
    std::string devicePath;
    std::string label;
};
std::string getDevicePath(const std::string& mountPoint);
std::string getVolumeLabel(const std::string& device);
std::vector<MountedVolume> getMountedVolumes();
extern std::vector<MountedVolume> driveslistings;

#endif // GETMOUNTEDDRIVES_H_INCLUDED
