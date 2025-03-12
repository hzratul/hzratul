#include <iostream>
#include <string>
#include "execute.cpp"
#include "term_col.cpp"
#include "countFiles.cpp"
#include "genCpp2.cpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <video_file_path>" << std::endl;
        return 1;
    }
// Make folder for all files that will be created
    std::string command = "mkdir './ASCII_Movie_Files'";
    execute(command.c_str());
    std::cout << "'./ASCII_Movie_Files' directory created." << std::endl;
    
// Make folder for storing images inside movie folder
    command = "mkdir './ASCII_Movie_Files/Image_Frames'";
    execute(command.c_str());
    std::cout << "'./ASCII_Movie_Files/Image_Frames' directory created." << std::endl;

// Generate Images by ffmpeg
    std::string videoFilePath = argv[1];
    command = "ffmpeg -i " + videoFilePath + " -vf \"fps=24,scale=" + std::to_string(term_col()*3) + ":-1\" './ASCII_Movie_Files/Image_Frames/%d.jpg'";
    execute(command.c_str());

// Make a folder for storing movie.cpp files (-> movie.out)
    command = "mkdir ./ASCII_Movie_Files/Source";
    execute(command.c_str());
    std::cout<<"'./ASCCI_Movie_Files/Source' directory created\n";

// Finding total number of image generated
    int totalImages {countFiles("./ASCII_Movie_Files/Image_Frames")};

// Generate movie.cpp file
adjust:
    std::cout<<"Adjust Your Terminal Width and Height, resolution will take effect accordingly. When done >>type 2894 and press enter: ";
    int check;
    std::cin>>check;
    if(check != 2894) 
        goto adjust;

    std::cout<<"Generating movie source file..."<<std::endl;
    if(gen_movie_source(totalImages, 41) == 0) 
        std::cout<<"\nSuccesfully created movie.cpp file in ./ASCII_Movie_Files/Source directory.\n";
    else 
        std::cout<<"Error: ./ASCII_Movie_Files/Source/movie.cpp file generation failed.\nAborted.\n";
    return 0;
}

