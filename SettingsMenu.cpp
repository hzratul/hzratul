#include <ncurses.h>
#include <string>

 #define COLOR_WHITE_1 11
 #define COLOR_WHITE_2 12
 #define COLOR_BLACK_1 13
 #define COLOR_BLACK_2 14


short int percent(short int, short int);

int main(){
    // Settings Variables
    short int height = 12;
    short int width = 36;
    short int x = 8;
    short int y = 4;
    // color variablesshort int fg_red = 900;
    short int fg_R = 900;
    short int fg_G = 900;
    short int fg_B = 900;
    short int bg_R = 100;
    short int bg_G = 100;
    short int bg_B = 100;

    initscr();
    cbreak();
    noecho();

start:
    // STDSCR variables
    short int main_h = 14;
    short int main_w = 54;
    short int main_x = (getmaxx(stdscr)-main_w)/2;
    short int main_y = (getmaxy(stdscr)-main_h)/2;

    short int opt_w = 22;
    short int opt_h = 1;
    short int opt_h_gap = 2;
    short int opt_x = main_x + 5;
    short int opt_1y = main_y + 3;
    short int opt_2y = opt_1y + opt_h_gap*1;
    short int opt_3y = opt_1y + opt_h_gap*2;
    short int opt_4y = opt_1y + opt_h_gap*3;

    short int button_h;
    short int button_w;
    short int button_x;
    short int button_y;

    // Menu texts variables
    std::string settings_title {"Settings"};
    std::string settings1_text {" Editor Dimention"};
    std::string settings2_text {" Editor Co-ordinates"};
    std::string settings3_text {" Foreground Color"};
    std::string settings4_text {" Background Color"};
    std::string button_text    {" Save & Quit "};
    std::string copyright_text {"©Hzratul"};



    // Color Section
    start_color();
    init_color(11,984,984,984);
    init_color(12,900,900,900);
    init_color(13,200,200,200);
    init_color(14,300,300,300);


    // Solid Pairs
    init_pair(1, COLOR_BLUE, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_WHITE_1);
    init_pair(3, COLOR_WHITE_2, COLOR_WHITE_2);
    // Split Pairs
    init_pair(21, COLOR_BLACK, COLOR_WHITE_2);
    init_pair(22, COLOR_WHITE_2, COLOR_BLACK_1);
    // RGB pairs
    init_pair(31, COLOR_RED, COLOR_RED);
    init_pair(32, COLOR_GREEN, COLOR_GREEN);
    init_pair(33, COLOR_BLUE, COLOR_BLUE);



    // Create Windows
    WINDOW * win_main = newwin(main_h, main_w, main_y, main_x);
    WINDOW * win_header = newwin(1, main_w, main_y, main_x);
    WINDOW * win_opt1 = newwin(1, opt_w, opt_1y, opt_x);
    WINDOW * win_opt2 = newwin(1, opt_w, opt_2y, opt_x);
    WINDOW * win_opt3 = newwin(1, opt_w, opt_3y, opt_x);
    WINDOW * win_opt4 = newwin(1, opt_w, opt_4y, opt_x);
    // Values for Opt 1 & 2
    WINDOW * win_opt1_set_x = newwin(1, 5, opt_1y, opt_x + 30);
    WINDOW * win_opt1_set_y = newwin(1, 5, opt_1y, opt_x + 39);
    WINDOW * win_opt2_set_x = newwin(1, 5, opt_2y, opt_x + 30);
    WINDOW * win_opt2_set_y = newwin(1, 5, opt_2y, opt_x + 39);
    // FG RGB values
    WINDOW * win_opt3_set_R = newwin(1, 3, opt_3y, opt_x + 29);
    WINDOW * win_opt3_set_G = newwin(1, 3, opt_3y, opt_x + 35);
    WINDOW * win_opt3_set_B = newwin(1, 3, opt_3y, opt_x + 41);
    // BG RGB values
    WINDOW * win_opt4_set_R = newwin(1, 3, opt_4y, opt_x + 29);
    WINDOW * win_opt4_set_G = newwin(1, 3, opt_4y, opt_x + 35);
    WINDOW * win_opt4_set_B = newwin(1, 3, opt_4y, opt_x + 41);

    WINDOW * win_button = newwin(1, 14, opt_4y + 3, main_x + main_w/2 - 7);



    // Cursor Properties of win
    curs_set(0);



    // Aplly color to win
    wbkgd(stdscr, COLOR_PAIR(1));
    wbkgd(win_main, COLOR_PAIR(2));

    wbkgd(win_opt1, COLOR_PAIR(21));
    wbkgd(win_opt2, COLOR_PAIR(21));
    wbkgd(win_opt3, COLOR_PAIR(21));
    wbkgd(win_opt4, COLOR_PAIR(21));

    wbkgd(win_opt1_set_x, COLOR_PAIR(21));
    wbkgd(win_opt1_set_y, COLOR_PAIR(21));
    wbkgd(win_opt2_set_x, COLOR_PAIR(21));
    wbkgd(win_opt2_set_y, COLOR_PAIR(21));

    wbkgd(win_opt3_set_R, COLOR_PAIR(21));
    wbkgd(win_opt3_set_G, COLOR_PAIR(21));
    wbkgd(win_opt3_set_B, COLOR_PAIR(21));

    wbkgd(win_opt4_set_R, COLOR_PAIR(21));
    wbkgd(win_opt4_set_G, COLOR_PAIR(21));
    wbkgd(win_opt4_set_B, COLOR_PAIR(21));

    wbkgd(win_button, COLOR_PAIR(22));



    // Write to settings panel
    mvwprintw(win_header, 0, (main_w - settings_title.length())/2, "%s", settings_title.c_str());
    wprintw(win_opt1, "%s", settings1_text.c_str());
    wprintw(win_opt2, "%s", settings2_text.c_str());
    wprintw(win_opt3, "%s", settings4_text.c_str());
    wprintw(win_opt4, "%s", settings4_text.c_str());
    wprintw(win_button, "%s", button_text.c_str());

    // Writing X Y>> Indicator text
    mvwprintw(win_main, 3, 32, "H>");
    mvwprintw(win_main, 3, 41, "W>");
    mvwprintw(win_main, 5, 32, "X>");
    mvwprintw(win_main, 5, 41, "Y>");

    //Writing RGB>>> indicator text
    attron(COLOR_PAIR(31));
    mvwprintw(win_main, 7, 32, "R ");
    mvwprintw(win_main, 9, 32, "R ");
    attroff(COLOR_PAIR(31));
    attron(COLOR_PAIR(32));
    mvwprintw(win_main, 7, 38, "G ");
    mvwprintw(win_main, 9, 38, "G ");
    attroff(COLOR_PAIR(32));
    attron(COLOR_PAIR(33));
    mvwprintw(win_main, 7, 44, "B ");
    mvwprintw(win_main, 9, 44, "B ");
    attroff(COLOR_PAIR(33));


    // Updating values
    wprintw(win_opt1_set_x, "%d", width);
    wprintw(win_opt1_set_y, "%d", height);
    wprintw(win_opt2_set_x, "%d", x);
    wprintw(win_opt2_set_y, "%d", y);

    wprintw(win_opt3_set_R, "%d", fg_R);
    wprintw(win_opt3_set_G, "%d", fg_G);
    wprintw(win_opt3_set_B, "%d", fg_B);
    wprintw(win_opt4_set_R, "%d", fg_R);
    wprintw(win_opt4_set_G, "%d", fg_G);
    wprintw(win_opt4_set_B, "%d", fg_B);



    // After all is done set cursor location
    curs_set(1);
    wmove(win_main, 1,0);
    echo();
    // Refreshh all win

    refresh();

    wrefresh(win_main);
    wrefresh(win_header);

    wrefresh(win_opt1);
    wrefresh(win_opt2);
    wrefresh(win_opt3);
    wrefresh(win_opt4);

    wrefresh(win_opt1_set_x);
    wrefresh(win_opt1_set_y);

    wrefresh(win_opt2_set_x);
    wrefresh(win_opt2_set_y);

    wrefresh(win_opt3_set_R);
    wrefresh(win_opt3_set_G);
    wrefresh(win_opt3_set_B);

    wrefresh(win_opt4_set_R);
    wrefresh(win_opt4_set_G);
    wrefresh(win_opt4_set_B);

    wrefresh(win_button);


    short int a = getmaxx(stdscr);
    short int b = getmaxy(stdscr);
    while(1)
    {
        short int tempX = getmaxx(stdscr);
        short int tempY = getmaxy(stdscr);
        if(tempX != a || tempY != b)
        {
           a = tempX;
           b = tempY;
           goto start;
        }
    }
    endwin();
    return 0;
}


short int percent(short int value, short int percent) {
    float x = ((float)value / 100) * percent;
    return (short)x;
}
