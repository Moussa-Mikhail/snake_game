// Implementation file for SnakeGame class

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

#include "snake_game.h"

void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hOut, coord);
}

void clear_screen(char fill = ' ')
{
    COORD tl = {0, 0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}

template <typename T>
void setCursorPosition(T obj)
{
    int x = obj.pos.x;

    int y = obj.pos.y;
}

SnakePiece::SnakePiece(int x, int y)
{
    pos = Pos(x, y);

    vel = Vel(0, 0);
}

Snake::Snake()
{
    int init_y = 7;

    int init_x = 4;

    head = SnakePiece(init_y, init_x);

    int length = 3;

    tail.resize(length);

    for (int i = 0; i < length; i++)
    {
        tail[i] = SnakePiece(init_y, init_x - 1 - i);
    }
}

Fruit::Fruit(int x, int y)
{
    pos = Pos(x, y);
}

SnakeGame::SnakeGame()
{
    Snake snake = Snake();

    Fruit fruit = Fruit(7, 12);
}

void SnakeGame::display() const
{
    snake.display();

    fruit.display();
}