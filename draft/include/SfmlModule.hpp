#ifndef SFML_MODULE_HPP
#define SFML_MODULE_HPP

#include "Modules.hpp"
#include <string>

class SfmlModule : public IDisplayModule {
public:
    SfmlModule();
    void drawSprite(const std::string &name, Transform const &transform, unsigned id) override;
    void update() override;
    ~SfmlModule();
};

#endif
