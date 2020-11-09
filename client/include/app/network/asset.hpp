/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _APP_NETWORK_ASSET_HPP_
#define _APP_NETWORK_ASSET_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

struct Asset {
    enum class Type {
        Sound,
        Texture,
    } type;
    long id_asset;
    long id_tile;           // if type is texture (tilesheet)
    sf::Texture texture;
    sf::Sprite sprite;
    sf::SoundBuffer sound;  // if type is Sound
};

#endif