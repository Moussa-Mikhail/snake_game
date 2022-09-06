// Implementation file for SnakeGame class

#include "snake_game.h"

#include <iostream>
#include <string>
#include <vector>

int SnakeGame::get_score() const {
    return snake.get_length() - INITIAL_LENGTH;
}

Pos SnakeGame::get_head_pos() const {
    return snake.head.pos;
}

std::vector<Pos> SnakeGame::get_tail_pos() const {
    std::vector<Pos> tail_pos;

    for (const auto &piece : snake.tail) {
        tail_pos.push_back(piece.pos);
    }

    return tail_pos;
}

Pos SnakeGame::get_fruit_pos() const {
    return fruit.pos;
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