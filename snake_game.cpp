// Implementation file for SnakeGame class

#include "snake_game.h"

#include <iostream>
#include <string>
#include <vector>

SnakeGame::SnakeGame() {
    int distance_from_center = 4;

    int init_x = WIDTH / 2 - distance_from_center;

    int init_y = HEIGHT / 2;

    snake = Snake(init_x, init_y, INITIAL_LENGTH);

    fruit = Fruit(init_x + 2 * distance_from_center, init_y);
}

int SnakeGame::get_score() const {
    return snake.get_length() - INITIAL_LENGTH;
}

void SnakeGame::update(std::optional<VelDir> dir) {
    snake.update_head(dir);

    snake.update_tail();
}

bool SnakeGame::has_collided() const {
    return has_collided_with_walls() || has_collided_with_tail();
}

bool SnakeGame::has_collided_with_walls() const {
    const auto [x, y] = snake.head.pos;

    return x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT;
}

bool SnakeGame::has_collided_with_tail() const {
    return snake.has_collided_with_tail();
}