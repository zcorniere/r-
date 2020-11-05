#ifndef SF_LOCAL_DISPLAY_HPP
#define SF_LOCAL_DISPLAY_HPP

#include "Modules.hpp"
#include <string>

class SfLocalDisplay : public IDisplayModule {
public:
    SfLocalDisplay();
    void setAssetPath(const string &path) override;
    void drawSprite(const string &name, Transform const &transform, unsigned id) override;
    Dimensional getCursorLocation() override;
    ~SfLocalDisplay();
}

#endif
