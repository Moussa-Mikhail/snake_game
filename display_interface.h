#ifndef SNAKE_DISPLAY_INTERFACE_H
#define SNAKE_DISPLAY_INTERFACE_H

#include <vector>

#include "snake_game_objects.h"

class DisplayInterface {
   public:
    virtual void draw_walls() = 0;

    virtual void draw_snake(const Pos head_pos, const std::vector<Pos> tail_pos) = 0;

    virtual void draw_fruit(const Pos fruit_pos) = 0;

    virtual void draw_score(int score) = 0;

    virtual void draw_game_over() = 0;

    virtual void draw_welcome_message() = 0;

    virtual void draw_game_over_message() = 0;
};

#endif