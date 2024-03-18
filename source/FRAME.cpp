#include <iostream>
#include <ncurses.h>
#include <string>
#include <thread>
#include <cstdlib>
#include <mutex>
#include <condition_variable>

// Global variables
std::mutex mtx;
std::condition_variable cv;
std::atomic<bool> firstThreadFinished(false);
bool terminateThreads(false);


void playVideo();
void playAudio(std::string path);
void refresh_scr();


int main(int argc, char * argv[]){
    if(argc>2){
        std::cerr<<"Arg usage: "<<argv[0]<<" <audio_file_path>\n";
    }

    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);

    int choice;
    mvprintw(getmaxy(stdscr)/2,getmaxx(stdscr)/2-15, "Press Enter to start playing...");
    getch();

    std::thread video(playVideo);
    std::thread refresher(refresh_scr);
    if(argc == 2){
        std::thread audio(playAudio, argv[0]);
        audio.join();
    }
    video.join();
    refresher.join();


    clear();
    refresh();
    mvprintw(getmaxy(stdscr)/2,getmaxx(stdscr)/2-11, "Press Any key to exit");

    getch();
    endwin();
    return 0;
        
}



void playVideo()
{
    #include "movie.cpp"    
    // Set the flag to indicate completion
    firstThreadFinished = true;

    // Notify other threads
    cv.notify_all();
}

void playAudio(std::string path){
    std::string cmd = "mpv -quiet " + path + " 2>&1";
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        printw("Error: Failed to open pipe to command.\n");
        refresh();
    } else {
        char buffer[128];
        // Read command output line by line and display it in the ncurses window
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            printw("%s", buffer);
            refresh();
    // Check if the first thread has finished
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, []{ return firstThreadFinished.load() || terminateThreads; });
        }
	// If first thread has finished, terminate
	   if (firstThreadFinished) {
		break;
		return;
	   }
        }
        pclose(pipe);
    }

}

void refresh_scr()
{
    int col = getmaxx(stdscr), row=getmaxy(stdscr);
    while(1){
        int a = getmaxx(stdscr), b=getmaxy(stdscr);
        if(col != a|| row != b){
            col = a;
            row = b;
            clear();
            refresh();
        }
        napms(100);
    // Check if the first thread has finished
        {
            std::unique_lock<std::mutex> lock(mtx);                                cv.wait(lock, []{ return firstThreadFinished.load() || terminateThreads; });                                                              }
	
        if (firstThreadFinished) {
		break;
		return;
	}
    }
}
