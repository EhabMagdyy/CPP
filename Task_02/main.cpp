#include <iostream>
#include <vector>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <utility>
#include <initializer_list>

class FileActions{
private:
    int* fd;                       
    int*& fdRef_;                  
    std::vector<std::pair<std::string, int>> actions_;

public:
    // Constructor
    FileActions(std::string& path) : fd(new int(open(path.c_str(), O_RDWR))), fdRef_(fd){
        if(*fd < 0){
            perror("Failed to open file");
        }
        else{
            std::cout << "Opened file: " << path << "\n";
        }
    }
    // Copy constructor
    FileActions(const FileActions& other) : fd(other.fd), fdRef_(fd), actions_(other.actions_) {
        std::cout << "Copy constructor -> Sharing the same file descriptor pointer\n";
    }
    // Add actions
    void registerActions(std::initializer_list<std::pair<std::string,int>> list){
        for(auto& a : list){
            actions_.push_back(a);
        }
    }
    // Execute all actions
    void executeActions(){
        for(const auto& action : actions_){
            const std::string& name = action.first;
            int value = action.second;

            if (name == "write") {
                std::string input;
                std::cout << "Enter " << value << " characters to write: ";
                std::getline(std::cin, input);

                if (input.size() < 5) {
                    std::cerr << "[ERROR] You must enter at least 5 characters!\n";
                    continue;
                }

                ssize_t result = write(*fd, input.c_str(), value);

                if (result < 0)
                    perror("write failed");
                else
                    std::cout << "[WRITE] wrote: " << input << "\n";
            }
            else if (name == "read") {

                // Move file pointer to beginning
                lseek(*fd, 0, SEEK_SET);

                char buffer[256] = {0};
                ssize_t result = read(*fd, buffer, value);

                if(result < 0){
                    perror("read failed");
                }
                else{
                    std::cout << "[READ] read " << result
                            << " characters: \"" << std::string(buffer, result) << "\"\n";
                }
            }
            else if(name == "close"){
                if(*fd >= 0){
                    close(*fd);
                    delete fd;
                    *fd = -1;
                }
                std::cout << "[CLOSED] Closed File\n"; 
            }
            else{
                std::cout << "[UNKNOWN ACTION] " << name << "\n";
            }
        }
    }

    // Destructor
    ~FileActions(){
        if(*fd >= 0){
            close(*fd);
            delete fd;
        }
        std::cout << "Destroyed fd\n";
    }
};

void copyConstructorDemo(FileActions copyFileActions){
    copyFileActions.registerActions({
       {"write", 5},
       {"read", 10},
       {"close", 0}
    });

    copyFileActions.executeActions();
}

int main(){
    std::string path = "file.txt";
    FileActions fileActions(path);

    fileActions.registerActions({
       {"write", 5},
       {"read", 5}
    });

    fileActions.executeActions();

    copyConstructorDemo(fileActions);

    return 0;
}
