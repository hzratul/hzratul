#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

// Global variables
std::mutex mtx;
std::condition_variable cv;
std::atomic<bool> firstThreadFinished(false);
bool terminateThreads(false);

// Function for the first thread
void firstThreadFunction() {
    // Do some work
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    // Set the flag to indicate completion
    firstThreadFinished = true;
    
    // Notify other threads
    cv.notify_all();
}

// Function for the second thread
void secondThreadFunction() {
    while (!terminateThreads) {
        // Do some work
        std::cout << "Second thread working..." << std::endl;
        
        // Check if the first thread has finished
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, []{ return firstThreadFinished.load() || terminateThreads; });
        }
        
        // If first thread has finished, terminate
        if (firstThreadFinished) {
            std::cout << "Second thread: First thread has finished its job. Terminating..." << std::endl;
            return;
        }
    }
}

// Function for the third thread
void thirdThreadFunction() {
    while (!terminateThreads) {
        // Do some work
        std::cout << "Third thread working..." << std::endl;
        
        // Check if the first thread has finished
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, []{ return firstThreadFinished.load() || terminateThreads; });
        }
        
        // If first thread has finished, terminate
        if (firstThreadFinished) {
            std::cout << "Third thread: First thread has finished its job. Terminating..." << std::endl;
            return;
        }
    }
}

int main() {
    // Create threads
    std::thread t1(firstThreadFunction);
    std::thread t2(secondThreadFunction);
    std::thread t3(thirdThreadFunction);
    
    // Join threads
    t1.join();
    
    // Set terminate flag to true
    {
        std::lock_guard<std::mutex> lock(mtx);
        terminateThreads = true;
    }
    
    // Notify other threads to terminate
    cv.notify_all();
    
    t2.join();
    t3.join();
    
    return 0;
}

