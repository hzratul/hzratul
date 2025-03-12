#include <iostream>
#include <string>
#include <ncurses.h>
#include <fstream>

std::string execute(const char*);
int find_percentage(int current, int last, int previous);
 


int gen_movie_source(int upto, int frameGapms) {
    // Open a file in write mode
    std::ofstream file("./ASCII_Movie_Files/Source/movie.cpp", std::ios::out);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file!" << std::endl;
        return 1;
    }


//// Write the Main part of Source File
    int percent = -1; // need at the end of the loop
    for(int i = 1; i <= upto;i++)
    {
        //Execute the command
        std::string cmd = "jp2a ./ASCII_Movie_Files/Image_Frames/" + std::to_string(i) + ".jpg";
        std::string output = execute(cmd.c_str());
/// Modify the output from jp2a
    // Backslashing NewLine Character
        std::string::size_type pos = 0;
        while ((pos = output.find('\n', pos)) != std::string::npos)
        {
            output.replace(pos, 1, "\\n"); pos += 2;
        }
    //Backslashing double quote
        pos = 0;
        while ((pos = output.find('\"', pos)) != std::string::npos) 
        {
            output.replace(pos, 1, "\\\""); pos += 2;
        }
    // Backslashing single quote
        pos = 0;
        while ((pos = output.find('\'', pos)) != std::string::npos) 
        {
            output.replace(pos, 1, "\\\'"); pos += 2;
        }

        file<<"mvprintw(0,0, \""<<output<<"\");"<<std::endl;
        file<<"refresh();\nnapms("<<std::to_string(frameGapms)<<");\n\n";
        

        //making progess bar
        int a = find_percentage(i, upto, percent);
        if (a != percent){
            percent = a;
            std::cout<< '\r' << percent <<" % Completed"<< std::flush;
        }
    }
    std::cout<<'\n';

    // Close the file
    file.close();
    return 0;
}


int find_percentage(int current, int last, int previous) {
    double percent = static_cast<double>(current) / last * 100; // Corrected to use floating-point division
    if (percent != previous)
        return static_cast<int>(percent); // Convert double to int for returning
    else
        return -1;
}

