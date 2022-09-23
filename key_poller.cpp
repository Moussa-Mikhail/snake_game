#include "key_poller.h"

#include <math.h>
#include <windows.h>

#include <chrono>
#include <optional>
#include <thread>

#include "snake_game_objects.h"

using ms = std::chrono::milliseconds;

using std::chrono::steady_clock;

const double POLLS_PER_SECOND = 50;

const int MILLISECS_PER_SECONDS = int(std::pow(10, 3));

const auto MILLISECS_PER_POLLS = ms((int)(MILLISECS_PER_SECONDS / POLLS_PER_SECOND));

std::optional<VelDir> KeyPoller::get_dir() const {
    return dir;
}

void KeyPoller::update_dir() {
    auto now = steady_clock::now();

    auto last_time = now;

    while (true) {
        now = steady_clock::now();

        auto delta_time = std::chrono::duration_cast<ms>(now - last_time);

        if (delta_time < MILLISECS_PER_POLLS) {
            std::this_thread::sleep_for(MILLISECS_PER_POLLS - delta_time);
        }

        auto new_dir = get_arrow_key();

        if (new_dir.has_value()) {
            dir = new_dir;
        }

        last_time = steady_clock::now();
    }
}

void KeyPoller::start_polling() {
    poller_thread = std::thread([this]() { update_dir(); });

    poller_thread.detach();
}

std::optional<VelDir> KeyPoller::get_arrow_key() {
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

bool KeyPoller::is_key_pressed(int vKey) {
    return GetAsyncKeyState(vKey) & 0x8000;
}