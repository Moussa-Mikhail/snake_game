
#include "snake_game_objects.h"

#include <algorithm>
#include <stdexcept>

Pos &Pos::operator+=(const Vel &vel) {
    x += vel.x;

    y += vel.y;

    return *this;
}

bool Pos::operator==(const Pos &rhs) const {
    return x == rhs.x && y == rhs.y;
}

Vel Vel::from_dir(const VelDir dir) {
    switch (dir) {
        case VelDir::Up:
            return Vel(0, -1);

        case VelDir::Down:
            return Vel(0, 1);

        case VelDir::Left:
            return Vel(-1, 0);

        case VelDir::Right:
            return Vel(1, 0);

        default:
            throw std::invalid_argument("Invalid direction");
    }
}

bool Vel::operator==(const Vel &rhs) const {
    return x == rhs.x && y == rhs.y;
}

bool Vel::operator!=(const Vel &rhs) const {
    return !(rhs == *this);
}

Vel Vel::operator-() const {
    return Vel(-x, -y);
}

void Head::update_pos() {
    pos += vel;
}

Vel Head::get_new_vel(std::optional<VelDir> dir) const {
    if (!dir) {
        return vel;
    }

    auto dir_actual = dir.value();

    auto new_vel = Vel::from_dir(dir_actual);

    if (new_vel == -vel) {
        return vel;
    }

    if (vel == Vel(0, 0) && dir_actual == VelDir::Left) {
        return vel;
    }

    return new_vel;
}

Snake::Snake(int init_x, int init_y, int init_length) : head(init_x, init_y) {
    tail.resize(init_length);

    for (int i = 0; i < init_length; i++) {
        tail[i] = SnakePiece(init_x - i - 1, init_y);
    }
};

void Snake::update(std::optional<VelDir> dir) {
    auto new_vel = head.get_new_vel(dir);

    if (is_moving() || new_vel != Vel(0, 0)) {
        update_tail();
    }

    update_head(new_vel);
}
void Snake::update_head(const Vel new_vel) {
    head.vel = new_vel;

    head.update_pos();
}

void Snake::update_tail() {
    for (auto i = tail.size() - 1; i > 0; i--) {
        tail[i].pos = tail[i - 1].pos;
    }

    tail[0].pos = head.pos;
}

void Snake::grow_tail() {
    auto last_pos = tail.back().pos;

    auto second_to_last_pos = tail[tail.size() - 2].pos;

    auto diff_x = second_to_last_pos.x - last_pos.x;

    auto diff_y = second_to_last_pos.y - last_pos.y;

    auto new_x = last_pos.x - diff_x;

    auto new_y = last_pos.y - diff_y;

    auto new_piece = SnakePiece(new_x, new_y);

    tail.push_back(new_piece);
}

int Snake::get_length() const { return (int)tail.size(); };

bool Snake::overlaps_tail(Pos pos) const {
    return std::any_of(tail.begin(), tail.end(), [pos](const SnakePiece &piece) {
        return piece.pos == pos;
    });
}

bool Snake::has_collided_with_tail() const {
    return overlaps_tail(head.pos);
}

bool Snake::is_moving() const { return !(head.vel == Vel(0, 0)); }