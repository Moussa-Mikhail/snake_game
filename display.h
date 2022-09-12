#ifndef SNAKE_DISPLAY_H
#define SNAKE_DISPLAY_H

#include "display_interface.h"
#include "snake_game_model.h"

class Display : public DisplayInterface {
   public:
    Display(const SnakeGameModel &game) : game{game}, WIDTH(game.WIDTH), HEIGHT(game.HEIGHT){};

    const SnakeGameModel &game;

    const int WIDTH;

    const int HEIGHT;

    void draw_walls() override;

    void draw_snake() override;

    void draw_snake_(const std::string head, const std::string tail);

    void clear_snake();

    void draw_food() override;

    void draw_food_(const std::string food);

    void clear_food();

    void draw_score() override;

    void draw_game() override;

    void clear_game() override;

    void draw_game_over() override;

    void draw_welcome_message() override;

    void clear_screen();

    // draw symbols
    static const std::string WALL;

    static const std::string HEAD;

    static const std::string TAIL;

    static const std::string FOOD;
};

#endif