#include <cstdint>
#include <ncurses.h>


void init_colors(short int rgb[6]);
void create_color_cubes(WINDOW * winColor);
void add_arrow_indicators(WINDOW * winColor);
void fill_with_spaces(WINDOW * win);
void unbox(WINDOW * win);
void highlight_current_slider_win(WINDOW * winSliderR,WINDOW * winSliderG,WINDOW * winSliderB, int8_t currentColor);
void update_slider_colorLevel(WINDOW * currentWin, short int colorIndex, int8_t currentColor);



int main()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    // Dimention variabke for windows
    int8_t winMainHeight = 17; // topWindow
    int8_t winMainWidth = 50;
    int8_t gap = 4; // gap between top and bottom windows
    int8_t winColorHeight = 10; // below one
    int8_t winColorWidth = 88; // below one

    int8_t winFillH = 8;
    int8_t winFillW = winFillH*2 + 10;
    int8_t winSliderH = 8;
    int8_t winSliderW = 5;
    int8_t winDataH = 5;
    int8_t winDataW = winMainWidth - 4;


    // x y ordinates of windows
    int8_t winMainY = (getmaxy(stdscr)-winMainHeight - winColorHeight)/2;
    int8_t winMainX = (getmaxx(stdscr)-winMainWidth)/2;
    int8_t winColorY = winMainY + 21;
    int8_t winColorX = (getmaxx(stdscr)-88)/2;
    int8_t winFillY = winMainY + 2;
    int8_t winFillX = winMainX + winMainWidth/2 - 5;
    int8_t winColorFillX = winMainX + 27;
    int8_t winSliderY = winFillY;
    int8_t winSliderX = winMainX + 3;
    int8_t winDataY = winFillY + winFillH + 1;
    int8_t winDataX = winMainX +2;


    // Creating windows
    WINDOW * winMain = newwin(winMainHeight, winMainWidth, winMainY, winMainX); //too one
    WINDOW * winColor = newwin(winColorHeight, winColorWidth, winColorY, winColorX); // below one
    WINDOW * winFill = newwin(winFillH, winFillW, winFillY, winFillX);
    WINDOW * winSliderR = newwin(winSliderH, winSliderW, winSliderY, winSliderX);
    WINDOW * winSliderG = newwin(winSliderH, winSliderW, winSliderY, winSliderX+winSliderW);
    WINDOW * winSliderB = newwin(winSliderH, winSliderW, winSliderY, winSliderX + 2*winSliderW);
    WINDOW * winData = newwin(winDataH, winDataW, winDataY, winDataX);



    box(winMain, 0,0);
    box(winColor, 0, 0);
    box(winFill,0,0);
    box(winData, 0, 0);
    box(winSliderR, 0, 0);
    box(winSliderG, 0, 0);
    box(winSliderB, 0, 0);

    refresh();
    wrefresh(winMain);
    wrefresh(winColor);
    wrefresh(winFill);
    wrefresh(winSliderR);
    wrefresh(winSliderG);
    wrefresh(winSliderB);
    wrefresh(winData);

    short int rgb[6] = {0,199,399,599,799,999};
    short int redIndex {3};
    short int greenIndex {3};
    short int blueIndex {3};
    short int& colorIndex = redIndex;
    short int colorNumber = 36*redIndex + greenIndex*6 + blueIndex + 11;
    WINDOW ** currentWin = &winSliderG;
    int8_t currentColor {1}; // 1red 2 green 3 blue

    init_colors(rgb);
    create_color_cubes(winColor);
    add_arrow_indicators(winColor);

    init_color(227, rgb[redIndex], rgb[greenIndex], rgb[blueIndex]);
    init_pair(235, colorNumber, colorNumber); // for winFill
    fill_with_spaces(winFill);

    refresh();
    wrefresh(winColor);

    // Main engine
    int ch;
    keypad(stdscr, TRUE);
    while(1)
    {
        ch = getch();

        // take arrow key inputs
        // unhighlight highlight  slider window
        // changes value of currentColor (int8_t var)
        // changes value of colorIndex (ref var)
        switch(ch)
        {
            case KEY_RIGHT:
                currentColor++;
                if(currentColor == 4) currentColor--;
                highlight_current_slider_win(winSliderR, winSliderG, winSliderB, currentColor); // unhighlights the non-sekected ones also

                // update colorIndex reference if currentColor value changes
                // Update currentWin pointer variable if currentColor changes
                switch(currentColor)
                {
                    case 1:
                        colorIndex = redIndex;
                        currentWin = &winSliderR;
                        break;
                    case 2:
                        colorIndex = greenIndex;
                        currentWin = &winSliderG;
                        break;
                    case 3:
                        colorIndex = blueIndex;
                        currentWin = &winSliderB;
                }
                break;
            case KEY_LEFT:
                currentColor--;
                if(currentColor == -1) currentColor++;
                highlight_current_slider_win(winSliderR, winSliderG, winSliderB, currentColor); // unhighlights the non-sekected ones also

                // update colorIndex reference if currentColor value changes
                // Update currentWin pointer variable if currentColor changes
                switch(currentColor)
                {
                    case 1:
                        colorIndex = redIndex;
                        currentWin = &winSliderR;
                        break;
                    case 2:
                        colorIndex = greenIndex;
                        currentWin = &winSliderG;
                        break;
                    case 3:
                        colorIndex = blueIndex;
                        currentWin = &winSliderB;
                }
                break;
            case KEY_UP:
                colorIndex++;
                if(colorIndex == 6) colorIndex--;
                update_slider_colorLevel(*currentWin, colorIndex, currentColor);
                break;
            case KEY_DOWN:
                colorIndex--;
                if(colorIndex == 6) colorIndex++;
                update_slider_colorLevel(*currentWin, colorIndex, currentColor);
                break;
        }
    }

    endwin();
    return 0;
}


// initialises all 216 colors and color pairs
void init_colors(short int rgb[6]){
    int index = 11;
    int pairNumber = 1;
    start_color();

    for(int a = 0; a < 6; a++)
    {
        for(int b = 0; b < 6; b++)
        {
            for(int c = 0; c < 6; c++)
            {
                init_color(index, rgb[a], rgb[b], rgb[c]);
                init_pair(pairNumber, index, index);
                index++;
                pairNumber++;
            }
        }
    }
}


// creates color cubes inside winColor window passed from main function to this
void create_color_cubes(WINDOW * winColor)
{
    // Forming the Color Pallete (Viewer)
    int index = 1;
    int8_t n = 1;
    // this loop forms 6 lines each containg 6 bar each bar has 6 colors
    for(int a = 0; a < 6; a++)
    {
        wmove(winColor,getmaxy(winColor)-9+n, 3);
        // this loop f4oms 6 bars on a line
        for(int b = 0; b < 6; b++)
        {
            // this loop forms one bar on a line
            for(int c = 0; c < 6; c++)
            {
                wattron(winColor, COLOR_PAIR(index));
                wprintw(winColor, "  ");
                wattroff(winColor, COLOR_PAIR(index));
                index++;
            }
            wprintw(winColor, "  ");
        }
        n++;
        wrefresh(winColor);
    }
}




// Adding Arrow Indications around color cubes
void add_arrow_indicators(WINDOW * winColor)
{
    for(int i = 0; i < 6; i++)
    {
        // Red Arrows
        init_pair(217+i, 11+36*i, COLOR_BLACK);
        for(int j = 0; j < 6; j++)
        {
            wattron(winColor,COLOR_PAIR(217+i));
            mvwprintw(winColor, getmaxy(winColor)-8+i, 2+14*j, "┃");
            wattroff(winColor,COLOR_PAIR(217+i));
        }

        // Blue arrows
        init_pair(217+6+i, 11+i, COLOR_BLACK);
        for(int j = 0; j < 6; j++)
        {
            wattron(winColor, COLOR_PAIR(217+6+i));
            mvwprintw(winColor, getmaxy(winColor)-9, 3+2*i + j*14, "━━");
            wattroff(winColor, COLOR_PAIR(217+6+i));
        }
        // Green Arrows
        init_pair(217+12+i, 11+6*i, COLOR_BLACK);
        wattron(winColor, COLOR_PAIR(217+12+i));
        mvwprintw(winColor, getmaxy(winColor)-2, 3+14*i, "━━━━━━━━━━━━");
        wattroff(winColor, COLOR_PAIR(217+12+i));
    }
    wrefresh(winColor);
}


void fill_with_spaces(WINDOW * win)
{
    int8_t h = getmaxy(win);
    int8_t w = getmaxx(win);

    wattron(win, COLOR_PAIR(235));
    for(short int i = 0; i < h; i++)
    {
        wmove(win, i, 0);
        for(short int j = 0; j < w; j++)
        {
            wprintw(win, " ");
        }
    }
    wattroff(win, COLOR_PAIR(235));
    wrefresh(win);
}

void unbox(WINDOW * win)
{
    wborder(win, 32, 32, 32, 32, 32, 32, 32, 32);
}


void highlight_current_slider_win(WINDOW * winSliderR,WINDOW * winSliderG,WINDOW * winSliderB, int8_t currentColor)
{
    // highlight current slider window
    switch(currentColor)
    {
        case 1:
            unbox(winSliderG);
            unbox(winSliderB);
            box(winSliderR, 0, 0);
            break;
        case 2:
            unbox(winSliderR);
            unbox(winSliderB);
            box(winSliderG, 0, 0);
            break;
        case 3:
            unbox(winSliderR);
            unbox(winSliderG);
            box(winSliderB, 0, 0);
            break;
    }
    wrefresh(winSliderR);
    wrefresh(winSliderG);
    wrefresh(winSliderB);

}



void update_slider_colorLevel(WINDOW * currentWin, short int colorIndex, int8_t currentColor)
{
    wclear(currentWin);
    box(currentWin, 0, 0);

    short int pairNumber;

    switch(currentColor)
    {
        case 1:
            pairNumber = 181;
            break;
        case 2:
            pairNumber = 31;
            break;
        case 3:
            pairNumber = 6;
            break;
    }
    wattron(currentWin, COLOR_PAIR(pairNumber));
    for(int8_t i = 0; i <= colorIndex; i++)
    {
        mvwprintw(currentWin, 6-i, 1, "   ");
    }
    wattroff(currentWin, COLOR_PAIR(pairNumber));

    wrefresh(currentWin);
}
