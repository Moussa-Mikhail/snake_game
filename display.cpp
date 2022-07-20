
#include "display.h"

#include <windows.h>

#include <iostream>

void setCursorPosition(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hOut, coord);
}

void clear_screen(char fill) {
    COORD tl = {0, 0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}

void setCursorPosition(Pos pos) {
    auto [x, y] = pos;

    setCursorPosition(x, y);
}

void Display::draw_walls() {
    for (int i = 0; i < width; i++) {
        setCursorPosition(Pos(i, 0));
        std::cout << wall_char;
        setCursorPosition(Pos(i, height - 1));
        std::cout << wall_char;
    }
    for (int i = 1; i < height - 1; i++) {
        setCursorPosition(Pos(0, i));
        std::cout << wall_char;
        setCursorPosition(Pos(width - 1, i));
        std::cout << wall_char;
    }
}