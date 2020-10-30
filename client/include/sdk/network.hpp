/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_NETWORK_HPP_
#define _SDK_NETWORK_HPP_

#include "sdk/protocol.hpp"

class Network {
    protocol::PackageClient sending_pkg;
    protocol::PackageServer receiving_pkg;
public:
    void update();
    void send(protocol::PackageClient pkg);
    // TODO receive ?
};

#endif