/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _ASSETS_HPP_
#define _ASSETS_HPP_

#include <string>
#include <vector>
#include <boost/static_assert.hpp>
#include <unordered_map>

class Image {
    void *data; // TODO
};

class Sound {
    void *data; // TODO
};

template<typename T>
class Asset {
    BOOST_STATIC_ASSERT(
    (std::is_base_of<Image, T>::value) ||
    (std::is_base_of<Sound, T>::value));
    std::string path;
    T data;
};

class Sprite {
    std::string img_id;
    unsigned height;
    unsigned width;
public:
    Sprite(std::string img_id, unsigned height, unsigned width);
    Sprite(std::string img_id);
};

class AssetManager {
    class Music {
        std::string m_sound_id;
        unsigned m_play_speed;
        bool m_is_looping;
    public:
        Music(std::string sound_id, unsigned play_speed = 1, bool is_looping = true) :
        m_sound_id(sound_id), m_play_speed(play_speed), m_is_looping(is_looping)
        {}
    } music;

    std::unordered_map<std::string, Asset<Image>> images;
    std::unordered_map<std::string, Asset<Sound>> souds;

    std::unordered_map<std::string, Sprite> sprites;
    // TODO sound ?
    // TODO animation
};

#endif // _ASSETS_HPP_