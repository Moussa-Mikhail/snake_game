
#include "display.h"

#include <windows.h>

#include <iostream>

void setCursorPosition(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    std::cout.flush();

    COORD coord = {(SHORT)x, (SHORT)y};

    SetConsoleCursorPosition(hOut, coord);
}

void setCursorPosition(Pos pos) {
    auto [x, y] = pos;

    setCursorPosition(x, y);
}

const std::string Display::WALL = "W";

const std::string Display::HEAD = "H";

const std::string Display::TAIL = "T";

const std::string Display::FOOD = "F";

void Display::clear_screen() {
    CONSOLE_SCREEN_BUFFER_INFO s;

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(console, &s);

    DWORD written, cells = s.dwSize.X * s.dwSize.Y;

    COORD tl = {0, 0};

    FillConsoleOutputCharacter(console, ' ', cells, tl, &written);

    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);

    SetConsoleCursorPosition(console, tl);
}

void Display::draw_walls() {
    for (int i = 0; i < WIDTH; i++) {
        setCursorPosition(i, 0);

        std::cout << WALL;

        setCursorPosition(i, HEIGHT - 1);

        std::cout << WALL;
    }

    for (int j = 1; j < HEIGHT - 1; j++) {
        setCursorPosition(0, j);

        std::cout << WALL;

        setCursorPosition(WIDTH - 1, j);

        std::cout << WALL;
    }
}

void Display::draw_snake_(const std::string head = HEAD, const std::string tail = TAIL) {
    setCursorPosition(game.get_head_pos());

    std::cout << head;

    auto tail_pos = game.get_tail_pos();

    for (const auto pos : tail_pos) {
        setCursorPosition(pos);

        std::cout << tail;
    }
}

void Display::clear_snake() {
    draw_snake_(" ", " ");
}

void Display::draw_snake() {
    draw_snake_();
}

void Display::draw_food_(const std::string food = FOOD) {
    setCursorPosition(game.get_food_pos());

    std::cout << food;
}

void Display::clear_food() {
    draw_food_(" ");
}

void Display::draw_food() {
    draw_food_();
}

void Display::draw_score() {
    setCursorPosition(0, HEIGHT + 1);

    std::cout << "Score: " << game.get_score();
}

void Display::draw_game() {
    draw_food();
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