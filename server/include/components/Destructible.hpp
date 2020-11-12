#ifndef DESTRUCTIBLE_HPP
#define DESTRUCTIBLE_HPP

struct Destructible {
    enum class Status {
        Alive,
        Dying,
        Dead,
    };
    unsigned health;
    bool hasDeathMontage = false;
    Status status = Status::Alive;
};

#endif
