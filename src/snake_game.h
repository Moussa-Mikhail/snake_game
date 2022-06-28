#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <vector>
#include <string>

#include "snake_game_parts.h"

class SnakeGame
{
public:
    SnakeGame();

    void display() const;

    void update(VelDirection);

    int get_score() const;

    const static int MAX_X = 17;

    const static int MAX_Y = 17;

    void time_step();

    bool has_collided() const;

private:
    Snake snake;

    Fruit fruit;
};
#endif