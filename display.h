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

    void draw_snake_(const wchar_t *head, const wchar_t *tail);

    void clear_snake();

    void draw_food() override;

    void draw_food_(const wchar_t *food);

    void clear_food();

    void draw_score() override;

    void draw_game() override;

    void clear_game() override;

    void draw_game_over() override;

    void draw_welcome_message() override;

    void clear_screen();

    // colors
    static const wchar_t *RED;

    static const wchar_t *WHITE;

    static const wchar_t *GREEN;

    static const wchar_t *YELLOW;

    static const wchar_t *DEFAULT;

    // draw chars
    static const wchar_t *WALL;

    static const wchar_t *HEAD;

    static const wchar_t *TAIL;

    static const wchar_t *FOOD;

    static const wchar_t *WALL_COLOR;

    static const wchar_t *HEAD_COLOR;

    static const wchar_t *TAIL_COLOR;

    static const wchar_t *FOOD_COLOR;
};

#endif