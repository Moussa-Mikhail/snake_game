// Implementation file for SnakeGame class

#include "snake_game_model.h"

#include <iostream>
#include <random>
#include <string>
#include <vector>

int SnakeGameModel::get_score() const {
    return snake.get_length() - INITIAL_LENGTH;
}

Pos SnakeGameModel::get_head_pos() const {
    return snake.head.pos;
}

std::vector<Pos> SnakeGameModel::get_tail_pos() const {
    std::vector<Pos> tail_pos;

    for (const auto &piece : snake.tail) {
        tail_pos.push_back(piece.pos);
    }

    return tail_pos;
}

Pos SnakeGameModel::get_food_pos() const {
    return food.pos;
}

void SnakeGameModel::update(std::optional<VelDir> dir) {
    snake.update(dir);

    if (has_eaten_food()) {
        replace_food();

        snake.grow_tail();
    }
}

bool SnakeGameModel::has_collided() const {
    return has_collided_with_walls() || has_collided_with_tail();
}

bool SnakeGameModel::has_collided_with_walls() const {
    const auto [x, y] = snake.head.pos;

    return x <= 0 || x >= (WIDTH - 1) || y <= 0 || y >= (HEIGHT - 1);
}

bool SnakeGameModel::has_collided_with_tail() const {
    return snake.has_collided_with_tail();
}

bool SnakeGameModel::has_eaten_food() const {
    return snake.head.pos == food.pos;
}

void SnakeGameModel::replace_food() {
    static std::default_random_engine generator{static_cast<long unsigned int>(time(nullptr))};

    static std::uniform_int_distribution distribution_x(1, WIDTH - 2);

    static std::uniform_int_distribution distribution_y(1, HEIGHT - 2);

    auto x = distribution_x(generator);

    auto y = distribution_y(generator);

    food = Food(x, y);
}

bool SnakeGameModel::is_snake_moving() const {
    return snake.is_moving();
}