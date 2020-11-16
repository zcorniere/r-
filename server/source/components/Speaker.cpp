#include "components/Speaker.hpp"

Speaker::Speaker(std::string _asset) : asset(_asset), status(Status::Inactive)
{}

void Speaker::play()
{
    status = Status::Starting;
}
