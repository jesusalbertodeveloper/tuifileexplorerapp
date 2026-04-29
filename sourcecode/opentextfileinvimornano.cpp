#include <iostream>
#include <cstdlib> // For system()
#include <string>

void openInVim(const std::string& filename) {
    std::string command = "vim " + filename; // Create the command string
    system(command.c_str()); // Execute the command
}

void openInNano(const std::string& filename) {
    std::string command = "nano " + filename; // Create the command string
    system(command.c_str()); // Execute the command
}

int main() {
    std::string filename;
    char choice;

    std::cout << "Enter the filename to open: ";
    std::getline(std::cin, filename); // Get the filename from user input

    std::cout << "Open in (v)im or (n)ano? ";
    std::cin >> choice;

    if (choice == 'v' || choice == 'V') {
        openInVim(filename); // Open the file in vim
    } else if (choice == 'n' || choice == 'N') {
        openInNano(filename); // Open the file in nano
    } else {
        std::cout << "Invalid choice. Please enter 'v' for vim or 'n' for nano." << std::endl;
    }

    return 0;
}
