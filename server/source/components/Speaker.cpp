#include "components/Speaker.hpp"

Speaker::Speaker(std::string _asset, float _volume, float _variation)
: asset(_asset), status(Status::Inactive), volume(_volume), variation(_variation)
{}

void Speaker::play()
{
    status = Status::Starting;
}
