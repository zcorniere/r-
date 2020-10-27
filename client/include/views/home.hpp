/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _HOME_HPP_
#define _HOME_HPP_

#include "components/interfaces/Iview.hpp"

class HomeView : public Iview {
    void onCreateView() final;
    void onUpdateView() final;
    void onFinishView() final;
};

#endif // _HOME_HPP_