#ifndef SNAKE_DISPLAY_INTERFACE_H
#define SNAKE_DISPLAY_INTERFACE_H

#include <vector>

class DisplayInterface {
   public:
    virtual void draw_walls() = 0;

    virtual void draw_snake() = 0;

    virtual void draw_game() = 0;

    virtual void move_tail() = 0;

    virtual void draw_game_over() = 0;

    virtual void draw_welcome_message() = 0;

    virtual void clear_screen() = 0;

    virtual ~DisplayInterface() = default;
};

#endif