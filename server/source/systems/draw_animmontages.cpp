#include "components/AnimMontage.hpp"
#include "Modules.hpp"

void draw_animmontages
(IDisplayModule &display, const Transform &transform, AnimMontage &montage)
{
    if (montage.getStatus() != AnimMontage::Status::Playing)
        return;
    montage.update();
    if (montage.getStatus() != AnimMontage::Status::Playing)
        return;
    unsigned current = montage.ticksCount / montage.duration;
    display.drawSprite(montage.spritesheet, transform, montage.ids.at(current));
}
