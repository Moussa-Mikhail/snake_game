// Implementation file for SnakeGame class

#include "snake_game.h"

#include <iostream>
#include <string>
#include <vector>

SnakeGame::SnakeGame() {
    int distance_from_center = 4;

    int init_x = MAX_X / 2 - distance_from_center;

    int init_y = MAX_Y / 2;

    Snake snake = Snake(init_x, init_y, INITIAL_LENGTH);

    Fruit fruit = Fruit(init_x + 2 * distance_from_center, init_y);
}

int SnakeGame::get_score() const {
    return snake.get_length() - INITIAL_LENGTH;
}

void SnakeGame::update(std::optional<VelDir> dir) {
    if (dir) {
        snake.update_head(dir.value());
    }

    snake.update_tail();
}

bool SnakeGame::has_collided() const {
    return has_collided_with_walls() || has_collided_with_tail();
}

bool SnakeGame::has_collided_with_walls() const {
    const auto [x, y] = snake.head.pos;

    return x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y;
}

bool SnakeGame::has_collided_with_tail() const {
    const auto head_pos = snake.head.pos;

    for (const auto &tail_piece : snake.tail) {
        if (tail_piece.pos == head_pos) {
            return true;
        }
    }

    return false;
}