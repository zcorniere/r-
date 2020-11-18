#include "components/PatternLoop.hpp"

const Pattern &PatternLoop::currentPattern()
{
    return this->pattern.at(this->pattern_id);
}
