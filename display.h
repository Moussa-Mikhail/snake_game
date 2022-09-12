#ifndef SNAKE_DISPLAY_H
#define SNAKE_DISPLAY_H

#include "display_interface.h"
#include "snake_game_model.h"

class Display : public DisplayInterface {
   public:
    Display(const SnakeGameModel& game) : game{game}, WIDTH(game.WIDTH), HEIGHT(game.HEIGHT){};

    const SnakeGameModel& game;

    const int WIDTH;

    const int HEIGHT;

    void draw_walls() override;

    void draw_snake() override;

    void draw_snake_(const char head, const char tail);

    void clear_snake();

    void draw_fruit() override;

    void draw_fruit_(const char fruit);

    void clear_fruit();

    void draw_score() override;

    void draw_game() override;

    void clear_game() override;

    void draw_game_over() override;

    void draw_welcome_message() override;

    void clear_screen(char fill = ' ');

    // draw symbols
    const static char WALL = 'W';

    const static char HEAD = 'H';

    const static char TAIL = 'T';

    const static char FRUIT = 'F';
};

#endif