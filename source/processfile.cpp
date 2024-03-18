#include <fstream>
#include <iostream>

int process_movie_src()
{
    std::ofstream file ("./ASCII_Movie_Files/Source/main.cpp");

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open the file for writing." << std::endl;
        return 1;
    }
    
    file<<"#include <ncurses.h>\n";
    file<<"#include <thread>\n";
    file<<"#include <cstdio>\n";
    file<<"#include <string>\n";
    file<<"#include <iostream>\n";

    file<<"void playAudio(){";
    FILE* pipe = popen("mpv -quiet output_audio.mp3 2>&1", "r");
    if (!pipe) {
        printw("Error: Failed to open pipe to command.\n");
        refresh();
    } else {
        char buffer[128];
        // Read command output line by line and display it in the ncurses window
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            printw("%s", buffer);
            refresh();
        }
        pclose(pipe);
    }
    file<<"";
    file<<"";
    file<<"";
    file<<"";
    file<<"";
    file<<"";
    file<<"";
    file<<"";
    file<<"";
    file<<"";
    file<<"";
    file<<"";
    file<<"";
    file<<"";
    file<<"";
    file<<"";
    file<<"";
    file<<"";
    file<<"";

    return 0;
}
