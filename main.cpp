#include <iostream>
#include <string>
#include <memory>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>  // Include cstring for strcmp
#include "./src/app/processes/ProcessManagement.hpp"
#include "./src/app/processes/Task.hpp"
#include "./src/app/filehandling/IO.hpp"  // Include the IO header

void processDirectory(const std::string& directory, const std::string& action, ProcessManagement& processManagement) {
    DIR* dir = opendir(directory.c_str());
    if (dir == nullptr) {
        std::cerr << "Unable to open directory: " << directory << std::endl;
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        std::string path = directory + "/" + entry->d_name;

        struct stat info;
        if (stat(path.c_str(), &info) != 0) {
            std::cerr << "Error getting stats for file: " << path << std::endl;
            continue;
        }

        if (S_ISDIR(info.st_mode)) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                processDirectory(path, action, processManagement);
            }
        } else if (S_ISREG(info.st_mode)) {
            IO io(path);
            std::fstream f_stream = std::move(io.getFileStream());

            if (f_stream.is_open()) {
                Action taskAction = (action == "encrypt") ? Action::ENCRYPT : Action::DECRYPT;
                auto task = std::make_unique<Task>(std::move(f_stream), taskAction, path);
                processManagement.submitToQueue(std::move(task));
            } else {
                std::cerr << "Unable to open file: " << path << std::endl;
            }
        }
    }

    closedir(dir);
}

int main(int argc, char* argv[]) {
    std::string directory;
    std::string action;

    std::cout << "Enter the directory path: ";
    std::getline(std::cin, directory);

    std::cout << "Enter the action (encrypt/decrypt): ";
    std::getline(std::cin, action);

    ProcessManagement processManagement;
    processDirectory(directory, action, processManagement);
    processManagement.executeTasks();

    return 0;
}
