#include <math.h>
#include <windows.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "snake_game_model.h"
#include "terminal_display.h"

using ms = std::chrono::milliseconds;

using std::chrono::steady_clock;

const double UPDATES_PER_SECOND = 3;

const int MILLISECS_PER_SECONDS = int(std::pow(10, 3));

const auto MILLISECS_PER_UPDATES = ms((int)(MILLISECS_PER_SECONDS / UPDATES_PER_SECOND));

bool is_key_pressed(int vKey);

std::optional<VelDir> get_dir();

int main() {
    SnakeGameModel game(30, 15);

    TerminalDisplay display(game);

    DisplayInterface *base_display = &display;

    base_display->clear_screen();

    base_display->draw_walls();

    base_display->draw_welcome_message();

    std::cin.ignore(1);

    auto now = steady_clock::now();

    auto last_time = now;

    base_display->clear_screen();

    base_display->draw_walls();

    base_display->draw_snake();

    base_display->draw_game();

    while (!game.has_collided()) {
        now = steady_clock::now();

        auto delta_time = std::chrono::duration_cast<ms>(now - last_time);

        if (delta_time < MILLISECS_PER_UPDATES) {
            std::this_thread::sleep_for(MILLISECS_PER_UPDATES - delta_time);
        }

        last_time = steady_clock::now();

        game.update(get_dir());

        base_display->draw_game();
    }

    base_display->draw_game_over();

    std::cin.ignore(1);

    base_display->clear_screen();
}

bool is_key_pressed(int vKey) {
    return GetAsyncKeyState(vKey) & 0x8000;
}

std::optional<VelDir> get_dir() {
    if (is_key_pressed(VK_UP)) {
        return VelDir::Up;
    } else if (is_key_pressed(VK_DOWN)) {
        return VelDir::Down;
    } else if (is_key_pressed(VK_LEFT)) {
        return VelDir::Left;
    } else if (is_key_pressed(VK_RIGHT)) {
        return VelDir::Right;
    }
    return std::nullopt;
}
