
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

const wchar_t *Display::RED = L"\x1b[31m";

const wchar_t *Display::WHITE = L"\x1b[37m";

const wchar_t *Display::GREEN = L"\x1b[32m";

const wchar_t *Display::YELLOW = L"\x1b[33m";

const wchar_t *Display::DEFAULT = L"\x1b[0m";

const wchar_t *Display::WALL = L"X";

const wchar_t *Display::WALL_COLOR = Display::RED;

const wchar_t *Display::HEAD = L"H";

const wchar_t *Display::HEAD_COLOR = Display::WHITE;

const wchar_t *Display::TAIL = L"T";

const wchar_t *Display::TAIL_COLOR = Display::GREEN;

const wchar_t *Display::FOOD = L"F";

const wchar_t *Display::FOOD_COLOR = Display::YELLOW;

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

        std::wcout << WALL_COLOR << WALL << DEFAULT;

        setCursorPosition(i, HEIGHT - 1);

        std::wcout << WALL_COLOR << WALL << DEFAULT;
    }

    for (int j = 1; j < HEIGHT - 1; j++) {
        setCursorPosition(0, j);

        std::wcout << WALL_COLOR << WALL << DEFAULT;

        setCursorPosition(WIDTH - 1, j);

        std::wcout << WALL_COLOR << WALL << DEFAULT;
    }
}

void Display::draw_snake_(const wchar_t *head = HEAD, const wchar_t *tail = TAIL) {
    setCursorPosition(game.get_head_pos());

    std::wcout << HEAD_COLOR << head << DEFAULT;

    auto tail_pos = game.get_tail_pos();

    for (const auto pos : tail_pos) {
        setCursorPosition(pos);

        std::wcout << TAIL_COLOR << tail << DEFAULT;
    }
}

void Display::clear_snake() {
    auto last_piece_pos = game.get_tail_pos().back();

    setCursorPosition(last_piece_pos);

    std::wcout << L" ";
}

void Display::draw_snake() {
    draw_snake_();
}

void Display::draw_food_(const wchar_t *food = FOOD) {
    setCursorPosition(game.get_food_pos());

    std::wcout << FOOD_COLOR << food << DEFAULT;
}

void Display::clear_food() {
    draw_food_(L" ");
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