#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include <fstream>
#include <condition_variable>

// It does NOT own memory, just points to existing characters, No copying, no allocation, Super fast, Read-only
constexpr std::string_view FILE_PATH = "/sys/class/leds/input3::capslock/brightness";

std::mutex mtx;
std::condition_variable cv;
bool isCapsPressed = false;

void checker(){
    static bool prevCapsState = false;

    while(true){
        std::ifstream file(FILE_PATH.data());
        if (!file){
            return;
        }
    
        std::string buffer;
        file >> buffer;
        bool currCapsState = (buffer == "1");
    
        if(currCapsState && !prevCapsState){
            std::lock_guard<std::mutex> lock(mtx);
            isCapsPressed = currCapsState;
        }
        
        cv.notify_one();    // Notify the listener thread that the state has changed
        prevCapsState = currCapsState;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void listener(){
    std::unique_lock<std::mutex> lock(mtx); // lock_guard is not used here because we need to unlock and wait on the condition variable
    while(true){
        cv.wait(lock, []{ return isCapsPressed; }); // Waits until isCapsPressed becomes true
        std::cout << "Caps Lock is pressed!" << std::endl;
        isCapsPressed = false;
    }
}

int main(){
    std::thread t1(checker);
    std::thread t2(listener);

    t1.join();
    t2.join();

    return 0;
}