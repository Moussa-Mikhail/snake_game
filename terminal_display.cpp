
#include "terminal_display.h"

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

const wchar_t *TerminalDisplay::RED = L"\x1b[31m";

const wchar_t *TerminalDisplay::WHITE = L"\x1b[37m";

const wchar_t *TerminalDisplay::GREEN = L"\x1b[32m";

const wchar_t *TerminalDisplay::YELLOW = L"\x1b[33m";

const wchar_t *TerminalDisplay::DEFAULT = L"\x1b[0m";

const wchar_t *TerminalDisplay::WALL = L"X";

const wchar_t *TerminalDisplay::WALL_COLOR = TerminalDisplay::RED;

const wchar_t *TerminalDisplay::HEAD = L"H";

const wchar_t *TerminalDisplay::HEAD_COLOR = TerminalDisplay::WHITE;

const wchar_t *TerminalDisplay::TAIL = L"T";

const wchar_t *TerminalDisplay::TAIL_COLOR = TerminalDisplay::GREEN;

const wchar_t *TerminalDisplay::FOOD = L"F";

const wchar_t *TerminalDisplay::FOOD_COLOR = TerminalDisplay::YELLOW;

void TerminalDisplay::set_last_tail_piece_pos() {
    last_tail_piece_pos = game.get_tail_pos().back();
}

void TerminalDisplay::set_VT_mode() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD dwMode = 0;

    GetConsoleMode(hOut, &dwMode);

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    SetConsoleMode(hOut, dwMode);
}

void TerminalDisplay::clear_screen() {
    CONSOLE_SCREEN_BUFFER_INFO s;

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(console, &s);

    DWORD written = s.dwSize.X * s.dwSize.Y;

    DWORD cells = s.dwSize.X * s.dwSize.Y;

    COORD tl = {0, 0};

    FillConsoleOutputCharacter(console, ' ', cells, tl, &written);

    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);

    SetConsoleCursorPosition(console, tl);
}

void TerminalDisplay::draw_walls() {
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

void TerminalDisplay::draw_snake() {
    setCursorPosition(game.get_head_pos());

    std::wcout << HEAD_COLOR << HEAD_COLOR << DEFAULT;

    auto tail_pos = game.get_tail_pos();

    for (const auto pos : tail_pos) {
        setCursorPosition(pos);

        std::wcout << TAIL_COLOR << TAIL << DEFAULT;
    }
}

void TerminalDisplay::draw_game() {
    redraw_snake();

    draw_food();

    draw_score();
}

void TerminalDisplay::redraw_snake() {
    move_tail();

    redraw_head();
}

void TerminalDisplay::move_tail() {
    if (!game.is_snake_moving()) {
        return;
    }

    clear_last_piece();

    const auto prev_head_pos = (game.get_tail_pos())[0];

    setCursorPosition(prev_head_pos);

    std::wcout << TAIL_COLOR << TAIL << DEFAULT;
}

void TerminalDisplay::redraw_head() const {
    setCursorPosition(game.get_head_pos());

    std::wcout << HEAD_COLOR << HEAD << DEFAULT;
}

void TerminalDisplay::draw_food() const {
    setCursorPosition(game.get_food_pos());

    std::wcout << FOOD_COLOR << FOOD << DEFAULT;
}

void TerminalDisplay::draw_score() const {
    setCursorPosition(0, HEIGHT + 1);

    std::cout << "Score: " << game.get_score();
}

void TerminalDisplay::draw_game_over() {
    std::string game_over = "Game Over";

    setCursorPosition(WIDTH / 2 - (int)game_over.length() / 2, HEIGHT / 2);

    std::cout << game_over;

    std::string exit_message = "Press enter to exit.";

    setCursorPosition(WIDTH / 2 - (int)exit_message.length() / 2, HEIGHT / 2 + 1);

    std::cout << exit_message;
}

void TerminalDisplay::draw_welcome_message() {
    std::string welcome = "Welcome to Snake";

    setCursorPosition(WIDTH / 2 - (int)welcome.length() / 2, HEIGHT / 2);

    std::cout << welcome;

    std::string start_message = "Press enter to start.";

    setCursorPosition(WIDTH / 2 - (int)start_message.length() / 2, HEIGHT / 2 + 1);

    std::cout << start_message;
}

void TerminalDisplay::clear_last_piece() {
    setCursorPosition(last_tail_piece_pos);

    std::wcout << L" ";

    set_last_tail_piece_pos();
}