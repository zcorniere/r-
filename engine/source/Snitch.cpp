#include "Snitch.hpp"

std::ostream &Snitch::output = std::cerr;

std::string Snitch::endl = "\e[0m\n";

std::ostream &Snitch::warn()
{
    Snitch::output << "\e[33m[WARNING]: ";
    return Snitch::output;
}

std::ostream &Snitch::msg(const std::string &msg)
{
    Snitch::output << "[" << msg << "]: ";
    return Snitch::output;
}
