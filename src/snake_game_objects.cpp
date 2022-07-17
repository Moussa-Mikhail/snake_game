
#include "snake_game_objects.h"

#include <stdexcept>

Vel Vel::from_dir(VelDir dir) {
    switch (dir) {
        case VelDir::Up:
            return Vel(0, 1);
            break;

        case VelDir::Down:
            return Vel(0, -1);
            break;

        case VelDir::Left:
            return Vel(-1, 0);
            break;

        case VelDir::Right:
            return Vel(0, 1);
            break;

        default:
            throw std::invalid_argument("Invalid direction");
    }
}

Pos &operator+=(Pos &pos, const Vel &vel) {
    pos.x += vel.x;
    pos.y += vel.y;
    return pos;
}

Pos &operator-=(Pos &pos, const Vel &vel) {
    pos.x -= vel.x;
    pos.y -= vel.y;
    return pos;
}

SnakePiece::SnakePiece(int x, int y) {
    pos = Pos(x, y);

    vel = Vel(0, 0);
}

Fruit::Fruit(int x, int y) {
    pos = Pos(x, y);
}

Snake::Snake(int init_x, int init_y, int init_length) {
    head = SnakePiece(init_y, init_x);

    tail.resize(init_length);

    for (int i = 0; i < init_length; i++) {
        tail[i] = SnakePiece(init_y, init_x - 1 - i);
    }
}

int Snake::get_length() const { return tail.size(); };

void Snake::update_head(VelDir dir) {
    head.vel = Vel::from_dir(dir);
}