
#include "snake_game_objects.h"

#include <algorithm>
#include <stdexcept>

Vel Vel::from_dir(VelDir dir) {
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

Pos &Pos::operator+=(const Vel &vel) {
    x += vel.x;

    y += vel.y;

    return *this;
}

bool Pos::operator==(const Pos &rhs) const {
    return x == rhs.x && y == rhs.y;
}

void Head::update_dir(std::optional<VelDir> dir) {
    if (dir) {
        vel = Vel::from_dir(*dir);
    }
}

void Head::update_pos() {
    pos += vel;
}

Snake::Snake(int init_x, int init_y, int init_length) : head(init_x, init_y) {
    tail.resize(init_length);

    for (int i = 0; i < init_length; i++) {
        tail[i] = SnakePiece(init_x - i - 1, init_y);
    }
};

int Snake::get_length() const { return (int)tail.size(); };

void Snake::update_head(std::optional<VelDir> dir) {
    head.update_dir(dir);

    head.update_pos();
}

void Snake::update_tail() {
    for (auto i = tail.size() - 1; i > 0; i--) {
        tail[i].pos = tail[i - 1].pos;
    }

    tail[0].pos = head.pos;
}

void Snake::update(std::optional<VelDir> dir) {
    if (is_moving() || dir) {
        update_tail();
    }

    update_head(dir);
}

bool Snake::is_moving() const { return !(head.vel == Vel(0, 0)); }

bool Snake::has_collided_with_tail() const {
    return std::any_of(tail.begin(), tail.end(), [this](const auto &tail_piece) {
        return tail_piece.pos == this->head.pos;
    });
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