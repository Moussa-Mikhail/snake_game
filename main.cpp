#include <math.h>
#include <windows.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "display.h"
#include "display_interface.h"
#include "snake_game.h"

std::optional<VelDir> get_dir();

const auto UPDATES_PER_SECOND = 0.5;

const int MILLISECS_PER_SECONDS = std::pow(10, 3);

const auto MILLISECS_PER_UPDATES = std::chrono::milliseconds((int)(MILLISECS_PER_SECONDS / UPDATES_PER_SECOND));

int main() {
    SnakeGame game(30, 15);

    Display display(game);

    DisplayInterface *base_display = &display;

    base_display->clear_screen();

    base_display->draw_walls();

    base_display->draw_welcome_message();

    std::cin.ignore(1);

    auto now = std::chrono::steady_clock::now();

    auto last_time = now;

    while (!game.has_collided()) {
        now = std::chrono::steady_clock::now();

        auto delta_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time);

        last_time = now;

        if (delta_time < MILLISECS_PER_UPDATES) {
            std::this_thread::sleep_for(MILLISECS_PER_UPDATES - delta_time);
        }

        base_display->draw_game();

        game.update(get_dir());
    }

    base_display->draw_game_over();

    std::cin.ignore(1);

    base_display->clear_screen();
}

std::optional<VelDir> get_dir() {
    if (GetAsyncKeyState(VK_UP)) {
        return VelDir::Up;
    } else if (GetAsyncKeyState(VK_DOWN)) {
        return VelDir::Down;
    } else if (GetAsyncKeyState(VK_LEFT)) {
        return VelDir::Left;
    } else if (GetAsyncKeyState(VK_RIGHT)) {
        return VelDir::Right;
    }
    return std::nullopt;
}
