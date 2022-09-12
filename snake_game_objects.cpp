
#include "snake_game_objects.h"

#include <stdexcept>

Vel Vel::from_dir(VelDir dir) {
    switch (dir) {
        case VelDir::Up:
            return Vel(0, -1);
            break;

        case VelDir::Down:
            return Vel(0, 1);
            break;

        case VelDir::Left:
            return Vel(-1, 0);
            break;

        case VelDir::Right:
            return Vel(1, 0);
            break;

        default:
            throw std::invalid_argument("Invalid direction");
    }
}

bool Vel::operator==(const Vel &rhs) const {
    return x == rhs.x && y == rhs.y;
}

Pos &Pos::operator+=(const Vel &vel) {
    x += vel.x;

    y += vel.y;

    return *this;
}

bool Pos::operator==(const Pos &rhs) const {
    return x == rhs.x && y == rhs.y;
}

SnakePiece::SnakePiece(int x, int y) {
    pos = Pos(x, y);
}

void Head::update_dir(std::optional<VelDir> dir) {
    if (dir) {
        vel = Vel::from_dir(*dir);
    }
}

void Head::update_pos() {
    pos += vel;
}

Fruit::Fruit(int x, int y) {
    pos = Pos(x, y);
}

Snake::Snake(int init_x, int init_y, int init_length) {
    head = Head(init_x, init_y);

    tail.resize(init_length);

    for (int i = 0; i < init_length; i++) {
        tail[i] = SnakePiece(init_x - 1, init_y);
    }
}

int Snake::get_length() const { return tail.size(); };

void Snake::update_head(std::optional<VelDir> dir) {
    head.update_dir(dir);

    head.update_pos();
}

void Snake::update_tail() {
    for (int i = tail.size() - 1; i > 0; i--) {
        tail[i].pos = tail[i - 1].pos;
    }

    tail[0].pos = head.pos;
}

void Snake::update(std::optional<VelDir> dir) {
    if (head.vel == Vel(0, 0) && !dir) {
        ;
    } else {
        update_tail();
    }

    update_head(dir);
}

bool Snake::has_collided_with_tail() const {
    for (const auto &tail_piece : tail) {
        if (tail_piece.pos == head.pos) {
            return true;
        }
    }

    return false;
}