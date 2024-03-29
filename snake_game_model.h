#ifndef SNAKE_GAME_MODEL_H
#define SNAKE_GAME_MODEL_H

#include <string>
#include <vector>

#include "snake_game_objects.h"

class SnakeGameModel {
   public:
    const int WIDTH;

    const int HEIGHT;

    const int INITIAL_LENGTH = 3;

    SnakeGameModel() = default;

    SnakeGameModel(int width = 30, int height = 15, int length = 3) : WIDTH(width), HEIGHT(height), INITIAL_LENGTH(length) {
        int distance_from_center = 4;

        int init_x = WIDTH / 2 - distance_from_center;

        int init_y = HEIGHT / 2;

        snake = Snake(init_x, init_y, INITIAL_LENGTH);

        food = Food(init_x + 2 * distance_from_center, init_y);
    };

    void update(std::optional<VelDir> dir);

    Pos get_head_pos() const;

    std::vector<Pos> get_tail_pos() const;

    Pos get_food_pos() const;

    int get_score() const;

    bool has_collided() const;

    bool has_collided_with_walls() const;

    bool has_collided_with_tail() const;

    bool has_eaten_food() const;

    bool is_snake_moving() const;

   private:
    Snake snake;

    Food food;

    void replace_food();
};
#endif