#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <string>
#include <vector>

#include "snake_game_objects.h"

class SnakeGame {
   public:
    const static int MAX_X = 15;

    const static int MAX_Y = 15;

    const static int INITIAL_LENGTH = 3;

    SnakeGame();

    void update(std::optional<VelDir> dir);

    int get_score() const;

    bool has_collided() const;

    bool has_collided_with_walls() const;

    bool has_collided_with_tail() const;

   private:
    Snake snake;

    Fruit fruit;
};
#endif