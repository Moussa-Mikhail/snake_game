#ifndef SNAKE_GAME_PARTS_H
#define SNAKE_GAME_PARTS_H

#include <optional>
#include <vector>

enum class VelDir {
    Up,
    Down,
    Left,
    Right
};

struct Vel {
    int x;

    int y;

    Vel(int x = 0, int y = 0) : x(x), y(y){};

    static Vel from_dir(VelDir dir);
};

struct Pos {
    int x;

    int y;

    Pos(int x = 0, int y = 0) : x(x), y(y){};

    Pos &operator+=(const Vel &vel);

    Pos &operator-=(const Vel &vel);

    bool operator==(const Pos &pos) const;
};

struct SnakePiece {
    Pos pos;

    Vel vel;

    void update_pos();

    SnakePiece() = default;

    SnakePiece(int x, int y);

    SnakePiece(Pos pos, Vel vel);
};

struct Snake {
    SnakePiece head;

    std::vector<SnakePiece> tail;

    int get_length() const;

    void update_head(VelDir dir);

    void update_tail();

    Snake() = default;

    Snake(int init_x, int init_y, int init_length);
};

struct Fruit {
    Pos pos;

    Fruit() = default;

    Fruit(int x, int y);
};
#endif