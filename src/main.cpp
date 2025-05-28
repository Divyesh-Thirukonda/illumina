#include "Engine.h"
#include <iostream>
#include <filesystem>
#include <limits>

int main() {
    std::cout << "=== Welcome to Illumina Editor ===\n"
              << "1. Create New Project\n"
              << "2. Exit\n"
              << "Select an option: ";

    int choice = 0;
    std::cin >> choice;
    if (!std::cin || choice != 1) {
        std::cout << "Goodbye!\n";
        return 0;
    }

    // flush newline before getline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string projectName;
    std::cout << "Enter new project name: ";
    std::getline(std::cin, projectName);

    std::cout << "Enter root directory (leave empty for current): ";
    std::string dirInput;
    std::getline(std::cin, dirInput);

    std::filesystem::path root = dirInput.empty()
                                    ? std::filesystem::current_path()
                                    : std::filesystem::path(dirInput);

    Engine engine;
    if (!engine.CreateProject(projectName, root)) {
        return -1;
    }

    std::cout << "Launch editor now? (y/n): ";
    char launch = 'n';
    std::cin >> launch;
    if (launch == 'y' || launch == 'Y') {
        if (!engine.Init()) {
            return -1;
        }
        engine.Run();
        engine.Shutdown();
    }

    return 0;
}
