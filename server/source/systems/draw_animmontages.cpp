#include "components/AnimMontage.hpp"
#include "components/Destructible.hpp"
#include "Modules.hpp"
#include <iostream>

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
    montage.ticksCount++;
}

void draw_deathmontages
(IDisplayModule &display, const Transform &transform, DeathMontage &montage)
{
    if (montage.getStatus() != AnimMontage::Status::Playing)
        return;
    montage.update();
    if (montage.getStatus() != AnimMontage::Status::Playing)
        return;
    unsigned current = montage.ticksCount / montage.duration;
    display.drawSprite(montage.spritesheet, transform, montage.ids.at(current));
    montage.ticksCount++;
}

void draw_shootmontages
(IDisplayModule &display, const Transform &transform, ShootMontage &montage)
{
    Transform ptransform(transform);

    if (montage.getStatus() != AnimMontage::Status::Playing)
        return;
    montage.update();
    if (montage.getStatus() != AnimMontage::Status::Playing)
        return;
    ptransform.location.x += 90;
    ptransform.location.y += 5;
    unsigned current = montage.ticksCount / montage.duration;
    display.drawSprite(montage.spritesheet, ptransform, montage.ids.at(current));
    montage.ticksCount++;
}

void play_deathmontages(Destructible &destructible, DeathMontage &montage)
{
    if (montage.getStatus() == AnimMontage::Status::Inactive \
&& destructible.status == Destructible::Status::Dying) {
        montage.play();
    }
    if (montage.getStatus() == AnimMontage::Status::Terminated) {
        destructible.status = Destructible::Status::Dead;
    }
}
