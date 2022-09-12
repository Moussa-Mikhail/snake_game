#ifndef SNAKE_DISPLAY_H
#define SNAKE_DISPLAY_H

#include "display_interface.h"
#include "snake_game_model.h"

class Display : public DisplayInterface {
   public:
    explicit Display(const SnakeGameModel &game) : game{game}, WIDTH(game.WIDTH), HEIGHT(game.HEIGHT) {
        set_VT_mode();
    };

    const SnakeGameModel &game;

    const int WIDTH;

    const int HEIGHT;

    void draw_walls() override;

    void draw_snake() override;

    void draw_game() override;

    void move_tail() override;

    void draw_game_over() override;

    void draw_welcome_message() override;

    void clear_screen() override;

   private:
    static void set_VT_mode();

    void draw_snake_(const wchar_t *head, const wchar_t *tail) const;

    void draw_food_(const wchar_t *food) const;

    void redraw_snake() const;

    void redraw_head() const;

    void clear_last_piece() const;

    void draw_food() const;

    void clear_food() const;

    void draw_score() const;

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