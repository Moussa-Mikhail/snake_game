#ifndef SNAKE_GAME_PARTS_H
#define SNAKE_GAME_PARTS_H

#include <vector>
#include <optional>

enum class VelDirection
{
    Up,
    Down,
    Left,
    Right
};

struct Vel
{
    int x;

    int y;

    Vel() = default;

    Vel(int x, int y);

    Vel(VelDirection dir);
};

struct Pos
{
    int x;

    int y;

    Pos() = default;

    Pos(int x, int y);

    Pos &operator+=(const Vel &vel);
};

struct SnakePiece
{
    Pos pos;

    Vel vel;

    void update_pos();

    SnakePiece() = default;

    SnakePiece(int x, int y);

    SnakePiece(Pos pos, Vel vel);

    void display() const;
};

struct Snake
{
    SnakePiece head;

    std::vector<SnakePiece> tail;

    std::optional<VelDirection> curr_dir;

    int get_length() const;

    void time_step();

    void display() const;

    Snake();
};

struct Fruit
{
    Pos pos;

    Fruit() = default;

    Fruit(int x, int y);

    void display() const;
};
#endif