#ifndef SNAKE_DISPLAY_H
#define SNAKE_DISPLAY_H

#include "display_interface.h"

class Display : public DisplayInterface {
   public:
    Display(int width, int height) : width(width), height(height){};

    void draw_walls() override;

    void draw_snake(const Pos head_pos, const std::vector<Pos> tail_pos) override;

    void draw_fruit(const Pos fruit_pos) override;

    void draw_score(int score) override;

    void draw_game_over() override;

    void draw_welcome_message() override;

    void draw_game_over_message() override;

   private:
    const int width;
    const int height;

    const static char wall_char = '#';
};

#endif