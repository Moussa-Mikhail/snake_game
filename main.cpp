#include <math.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "key_poller.h"
#include "snake_game_model.h"
#include "terminal_display.h"

using ms = std::chrono::milliseconds;

using std::chrono::steady_clock;

const double UPDATES_PER_SECOND = 3;

extern const int MILLISECS_PER_SECONDS = int(std::pow(10, 3));

const auto MILLISECS_PER_UPDATES = ms((int)(MILLISECS_PER_SECONDS / UPDATES_PER_SECOND));

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

    auto key_poller = KeyPoller();

    key_poller.start_polling();

    while (!game.has_collided()) {
        now = steady_clock::now();

        auto delta_time = std::chrono::duration_cast<ms>(now - last_time);

        if (delta_time < MILLISECS_PER_UPDATES) {
            std::this_thread::sleep_for(MILLISECS_PER_UPDATES - delta_time);
        }

        last_time = steady_clock::now();

        auto dir = key_poller.get_dir();

        game.update(dir);

        base_display->draw_game();
    }

    base_display->draw_game_over();

    std::cin.ignore(1);

    base_display->clear_screen();
}
