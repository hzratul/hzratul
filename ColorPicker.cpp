// 11 - 226  →  ncolors color
// 227 - resultant cokor
// 1 - 216 - (pair no) 216 color cube boxes
// 217 - (pair no) color picker tag
// 218 - (pair no) red slider
// 219 - (pair no) red slider
// 220 - (pair no) red slider
// 221 - (pair no) for winFill


#include <ncurses.h>
#include <cstdint>
#include <cmath>

void init_color_ncubes(WINDOW * winColorCubes);
void increase_colorValue(short int* baseColorValue, short int upperLimit);
void decrease_colorValue(short int* baseColorValue);
void dim_slider_window(WINDOW * win);
void highlight_slider_window(WINDOW * win);
void fill8_vl(WINDOW * win, int8_t height);
void modify_slider(WINDOW * win, short int* baseColorValue, short int upperLimit, short int pairNumber);
void fill_window(WINDOW * win,short int r,short int g,short int b, int8_t winFillH);


int main()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    start_color();
    keypad(stdscr, TRUE);

    // Variable for Windows Height & Width
    int8_t winMainH = 19;
    int8_t winMainW = 50;
    int8_t gap = 2;
    int8_t winColorCubesH = 8;
    int8_t winColorCubesW = 81;
    int8_t winFillH = 11;
    int8_t winSliderH = 10;
    int8_t winSliderW = 5;
    int8_t winDataH = 5;
    int8_t winDataW = winMainW - 4;

    // Variabkes for Windows X Y ordinates on stdscr
    int8_t winMainY = (getmaxy(stdscr)-winMainH - winColorCubesH - gap)/2;
    int8_t winMainX = (getmaxx(stdscr)-winMainW)/2;
    int8_t winColorCubesY = winMainY + gap + winMainH;
    int8_t winColorCubesX = (getmaxx(stdscr)-winColorCubesW)/2;
    int8_t winFillY = winMainY + 2;
    int8_t winFillX = winMainX + winMainW/2 - 1;
    int8_t winSliderY = winFillY;
    int8_t winSliderX = winMainX + 5;
    int8_t winDataY = winFillY + winFillH;
    int8_t winDataX = winMainX +2;

    // Create Windows
    WINDOW * winMain = newwin(winMainH, winMainW, winMainY, winMainX);
    WINDOW * winColorCubes = newwin(winColorCubesH, winColorCubesW, winColorCubesY, winColorCubesX);
    WINDOW * winFill = newwin(winFillH, winFillH*2, winFillY, winFillX);
    WINDOW * winSliderR = newwin(winSliderH, winSliderW, winSliderY, winSliderX);
    WINDOW * winSliderG = newwin(winSliderH, winSliderW, winSliderY, winSliderX+winSliderW);
    WINDOW * winSliderB = newwin(winSliderH, winSliderW, winSliderY, winSliderX + 2*winSliderW);
    WINDOW * winData = newwin(winDataH, winDataW, winDataY, winDataX);


    // Draw BOXes for each windiw
    box(winColorCubes, 0,0);
    box(winMain, 0,0);
    box(winFill,0,0);
    box(winData, 0, 0);


    // Give Labels to different windows
    init_pair(217, COLOR_BLACK, COLOR_CYAN); // 217 here
    attron(COLOR_PAIR(217));
    attroff(COLOR_PAIR(217));
    mvwprintw(winMain,1, 31, "Resultant");
    mvwprintw(winMain,1,7, "R" );
    mvwprintw(winMain,1,12, "G" );
    mvwprintw(winMain,1,17, "B" );


    // Refresh Windows
    refresh();
    wrefresh(winMain);
    wrefresh(winColorCubes);
    wrefresh(winFill);
    wrefresh(winSliderR);
    wrefresh(winSliderG);
    wrefresh(winSliderB);
    wrefresh(winData);


    // Forma thw color cube window
    init_color_ncubes(winColorCubes);

    // Make Color pairs for RGB sliders
    init_pair(218, 191, COLOR_BLACK); // red on black
    init_pair(219, 35, COLOR_BLACK); // green on black
    init_pair(220, 6, COLOR_BLACK); // blue on black
//**********************************************//
    // ***Main ENGINE***
    int colorLoop {1073741824};
    int8_t baseColor {1};
    short int pairNumber {218};
    int8_t a = colorLoop % 3;
    bool rgbValueRegular = true;

    short int upperLimit {255};
    short int rValue {upperLimit};
    short int gValue {upperLimit};
    short int bValue {upperLimit};

    short int * baseColorValue = &rValue;

    int ch;
    while(1)
    {
        fill_window(winFill,rValue,gValue, bValue,winFillH);
        mvprintw(1,4,"%d", rValue);
        mvprintw(2,4,"%d", gValue);
        mvprintw(3,4,"%d", bValue);
        mvprintw(4,4,"baseColor %d", baseColor);
        mvprintw(5,4,"pairNumber %d", pairNumber);
        mvprintw(6,4,"colorLoop%d", colorLoop);

        refresh();

        // highlight and modify slider
        switch(baseColor)
        {
            case 1:
                dim_slider_window(winSliderG);
                dim_slider_window(winSliderB);
                wrefresh(winSliderG);
                wrefresh(winSliderB);

                wclear(winSliderR);
                highlight_slider_window(winSliderR);
                pairNumber = 218;
                modify_slider(winSliderR, baseColorValue, upperLimit, pairNumber);
                wrefresh(winSliderR);
                break;
            case 2:
                dim_slider_window(winSliderR);
                dim_slider_window(winSliderB);
                wrefresh(winSliderR);
                wrefresh(winSliderB);

                wclear(winSliderG);
                highlight_slider_window(winSliderG);
                pairNumber = 219;
                modify_slider(winSliderG, baseColorValue, upperLimit, pairNumber);
                wrefresh(winSliderG);
                break;
            case 0:
                dim_slider_window(winSliderR);
                dim_slider_window(winSliderG);
                wrefresh(winSliderR);
                wrefresh(winSliderG);

                wclear(winSliderB);
                highlight_slider_window(winSliderB);
                pairNumber = 220;
                modify_slider(winSliderB, baseColorValue, upperLimit, pairNumber);
                wrefresh(winSliderB);
                break;
        }
        ch = getch();
        // analyse user input and change variabke values to take effect
        switch(ch)
        {
            case KEY_UP:
                increase_colorValue(baseColorValue, upperLimit);
                break;
            case KEY_DOWN:
                decrease_colorValue(baseColorValue);
                break;
            case KEY_RIGHT:
                colorLoop++;
                a = colorLoop % 3;
                switch(a)
                {
                    case 1:
                        baseColor = 1;
                        baseColorValue = &rValue;
                        break;
                    case 2:
                        baseColor = 2;
                        baseColorValue = &gValue;
                        break;
                    case 0:
                        baseColor = 0;
                        baseColorValue = &bValue;
                        break;
                }
                break;

            case KEY_LEFT:
                colorLoop--;
                a = colorLoop % 3;
                switch(a)
                {
                    case 1:
                        baseColor = 1;
                        baseColorValue = &rValue;
                        break;
                    case 2:
                        baseColor = 2;
                        baseColorValue = &gValue;
                        break;
                    case 0:
                        baseColor = 0;
                        baseColorValue = &bValue;
                        break;
                }
                break;
            default:
                break;
        }

    }


    while(1)
    getch();
    endwin();
    return 0;
    return 0;
}



/********** Main function Ends Here *************/




// initialize all colors and form the color cubes in bottom window
void init_color_ncubes(WINDOW * winColorCubes)
{
    int rgb[6] = {0,199,399,599,799,999};
    int index = 11;
    for(int a = 0; a < 6; a++) //forms whole block of 6 lines each of 6 packs
    {
        wmove(winColorCubes, 1+a ,2);
        for(int b = 0; b < 6; b++) //forms signle line of 6 packs
        {
            for(int c = 0; c < 6; c++) //forms single pack of 6 colors
            {
                init_color(index, rgb[a], rgb[b], rgb[c]);
                init_pair(index - 10, index, index);

                wattron(winColorCubes, COLOR_PAIR(index - 10));
                wprintw(winColorCubes, "  ");
                wattroff(winColorCubes, COLOR_PAIR(index - 10));

                index++;
            }
            wprintw(winColorCubes, " ");
        }
        wrefresh(winColorCubes);
    }
}

void increase_colorValue(short int* baseColorValue, short int upperLimit)
{
    if (*baseColorValue == upperLimit) (*baseColorValue) --;
    (*baseColorValue)++;
}

void decrease_colorValue(short int* baseColorValue)
{
    if (*baseColorValue == 0) (*baseColorValue)++;
    (*baseColorValue)--;
}

void dim_slider_window(WINDOW * win)
{
    wborder(win, 32, 32, 32, 32, 32, 32, 32, 32);
}

void highlight_slider_window(WINDOW * win)
{
    box(win, 0, 0);
}

void fill8_vl(WINDOW * win, int8_t height)
{

    switch(height)
    {
        case 8:
            wprintw(win, "███");
            break;
        case 7:
            wprintw(win, "▇▇▇");
            break;
        case 6:
            wprintw(win, "▆▆▆");
            break;
        case 5:
            wprintw(win, "▅▅▅");
            break;
        case 4:
            wprintw(win, "▄▄▄");
            break;
        case 3:
            wprintw(win, "▃▃▃");
            break;
        case 2:
            wprintw(win, "▂▂▂");
            break;
        case 1:
            wprintw(win, "▁▁▁");
            break;
        case 0:
            break;
    }
}

int8_t count_steps(short int b, short int u)
{
    return std::round(static_cast<float>(b)*64/u);
}

void do_solid_fill_slider(WINDOW * win, int8_t blocks)
{
    for(int i = 1; i <= blocks; i++)
    {
        wmove(win, getmaxy(win)-i, 1);
        fill8_vl(win, 8);
    }
}



// colours tha pessed RGB bar window to it's color
// uses 2 user defined functions
// - count_steps()
// -
void modify_slider(WINDOW * win, short int* baseColorValue, short int upperLimit, short int pairNumber)
{
    int8_t steps = count_steps(*baseColorValue, upperLimit);
    int8_t solidFills = steps/8;

    /* init_pair(218, colorNumber, COLOR_BLACK); */
    refresh();
    wattron(win, COLOR_PAIR(pairNumber));
    for(int i = 1; i <= solidFills; i++)
    {
        mvwprintw(win, getmaxy(win)-i-1, 1, "███");
    }
    wmove(win, getmaxy(win)-solidFills-1, 1);
    fill8_vl(win, 9 - solidFills);
    wattroff(win, COLOR_PAIR(pairNumber));

    //######## debugging prints
    mvprintw(10,4,"steps %d", steps);
    mvprintw(11,4,"solidFills %d", solidFills);
    mvprintw(12,4,"slice %d", steps - solidFills*8);
    refresh();
}


void fill_window(WINDOW * win,short int r,short int g,short int b, int8_t winFillH)
{

    init_color(217, r*999/255, g*999/255, b*999/255);
    init_pair(221, 217, 217);
    refresh();
    wattron(win, COLOR_PAIR(221));
    for(int i = 0; i < (winFillH-2); i++)
    {
        wmove(win, i+1, 1);
        for(int j = 0; j < (winFillH*2 - 2); j++)
        {
           wprintw(win, " ");
        }
    }
    wattroff(win, COLOR_PAIR(221));
    wrefresh(win);
}
