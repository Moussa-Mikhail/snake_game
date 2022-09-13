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

    bool operator==(const Vel &rhs) const;
};

struct Pos {
    int x;

    int y;

    Pos(int x = 0, int y = 0) : x(x), y(y){};

    Pos &operator+=(const Vel &vel);

    bool operator==(const Pos &rhs) const;
};

struct SnakePiece {
    Pos pos;

    SnakePiece() = default;

    SnakePiece(int x, int y) : pos(x, y){};
};

struct Head : SnakePiece {
    using SnakePiece::SnakePiece;

    Vel vel;

    void update_pos();

    void update_dir(std::optional<VelDir> dir);
};

class Snake {
   public:
    Head head;

    std::vector<SnakePiece> tail;

    Snake() = default;

    Snake(int init_x, int init_y, int init_length);

    void update(std::optional<VelDir> dir);

    int get_length() const;

    bool has_collided_with_tail() const;

    void grow_tail();

    bool is_moving() const;

   private:
    void update_head(std::optional<VelDir> dir);

    void update_tail();
};

struct Food {
    Pos pos;

    Food() = default;

    Food(int x, int y) : pos(x, y){};
};
#endif