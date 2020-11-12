#ifndef DESTRUCTIBLE_HPP
#define DESTRUCTIBLE_HPP

struct Destructible {
    enum class Status {
        Alive,
        Dying,
        Dead,
    };
    unsigned health;
    Status status = Status::Alive;
};

#endif
