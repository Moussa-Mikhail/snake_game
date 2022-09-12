
#include "display.h"

#include <windows.h>

#include <iostream>

void setCursorPosition(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    std::cout.flush();

    COORD coord = {(SHORT)x, (SHORT)y};

    SetConsoleCursorPosition(hOut, coord);
}

void Display::clear_screen(char fill) {
    CONSOLE_SCREEN_BUFFER_INFO s;

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(console, &s);

    DWORD written, cells = s.dwSize.X * s.dwSize.Y;

    COORD tl = {0, 0};

    FillConsoleOutputCharacter(console, fill, cells, tl, &written);

    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);

    SetConsoleCursorPosition(console, tl);
}

void setCursorPosition(Pos pos) {
    auto [x, y] = pos;

    setCursorPosition(x, y);
}

void Display::draw_walls() {
    for (int i = 0; i < WIDTH; i++) {
        setCursorPosition(i, 0);

        std::cout << WALL;

        setCursorPosition(i, HEIGHT - 1);

        std::cout << WALL;
    }

    for (int i = 1; i < HEIGHT - 1; i++) {
        setCursorPosition(0, i);

        std::cout << WALL;

        setCursorPosition(WIDTH - 1, i);

        std::cout << WALL;
    }
}

void Display::draw_snake_(const char head = HEAD, const char tail = TAIL) {
    setCursorPosition(game.get_head_pos());

    std::cout << head;

    auto tail_pos = game.get_tail_pos();

    for (const auto pos : tail_pos) {
        setCursorPosition(pos);

        std::cout << tail;
    }
}

void Display::clear_snake() {
    draw_snake_(' ', ' ');
}

void Display::draw_snake() {
    draw_snake_();
}

void Display::draw_fruit_(const char fruit = FRUIT) {
    setCursorPosition(game.get_fruit_pos());

    std::cout << fruit;
}

void Display::clear_fruit() {
    draw_fruit_(' ');
}

void Display::draw_fruit() {
    draw_fruit_();
}

void Display::draw_score() {
    setCursorPosition(0, HEIGHT + 1);

    std::cout << "Score: " << game.get_score();
}

void Display::draw_game() {
    draw_fruit();
    draw_snake();
    draw_score();
}

void Display::clear_game() {
    clear_snake();
}

void Display::draw_game_over() {
    std::string game_over = "Game Over";

    setCursorPosition(WIDTH / 2 - game_over.length() / 2, HEIGHT / 2);

    std::cout << game_over;

    std::string exit_message = "Press enter to exit.";

    setCursorPosition(WIDTH / 2 - exit_message.length() / 2, HEIGHT / 2 + 1);

    std::cout << exit_message;
}

void Display::draw_welcome_message() {
    std::string welcome = "Welcome to Snake";

    setCursorPosition(WIDTH / 2 - welcome.length() / 2, HEIGHT / 2);

    std::cout << welcome;

    std::string start_message = "Press enter to start.";

    setCursorPosition(WIDTH / 2 - start_message.length() / 2, HEIGHT / 2 + 1);

    std::cout << start_message;
}