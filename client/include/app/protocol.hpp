/*
** EPITECH PROJECT, 2021
** R-type
** File description:
** R-type
*/

#ifndef _SDK_PROTOCOL_HPP_
#define _SDK_PROTOCOL_HPP_

#include <cstddef>
#include <array>
#include <type_traits>
#include <vector>

// TODO Le client à besoin d'une table de liaison pour lier std::pair<long id_asset, long id_sprite> à sf::Sprite

namespace protocol {
    namespace transform {
        struct Rotation {
            float x;
            float y;
        };
        struct Position {
            float x;
            float y;
        };
        struct Scale {
            float x;
            float y;
        };
    }
    namespace input {
        constexpr short keys_array_size = 5;
        enum Keys {
            LeftClick,
            RightClick,
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,
            Num0,
            Num1,
            Num2,
            Num3,
            Num4,
            Num5,
            Num6,
            Num7,
            Num8,
            Num9,
            Escape,
            LControl,
            LShift,
            LAlt,
            RControl,
            RShift,
            RAlt,
            Tab,
            Space,
            Enter,
            BackSpace,
            Left,
            Right,
            Up,
            Down,
            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12,
            F13,
            F14,
            F15
        };
        struct KeysEvent {
            bool pressed: 1;
            Keys key: 7;
        };
        struct MousePos {
            short y;
            short x;
        };
    }
    constexpr std::pair<std::byte, std::byte> magic_number = {std::byte{0xFA}, std::byte{0xDA}};
    namespace udp {
        // UDP code
        enum class Code {
            Sprite,         // from server
            Sound,          // from server
            AssetList,      // from server
            AskAssetList,   // from client
            Ready,          // from client
            Input,          // from client
            Disconnect,     // Both
        };
        namespace from_server {
            struct Sprite {
                long id_asset;     // the tilesheet
                long id_sprite;    // the sprite id of the tilesheet
                transform::Rotation rot;
                transform::Position pos;
                transform::Scale scale;
            };
            struct Sound {
                long id;
                float pitch;
                bool isLooping;
            };
            struct AssetList {
                unsigned port;          // port of the tcp server (same ip)
                std::size_t size;       // size of list
                std::vector<long> list; // list of asset ids
            };
        }
        namespace from_client {
            struct AskAssetList {};     // ask the server a list of ids representing all game assets
            struct Ready {};            // indicate at the server that all asset are loaded and the client is ready to play
            struct Input {              // return to the server all user inputs (mouse & keyboard)
                short nb_keys = 0;
                std::array<input::KeysEvent, input::keys_array_size> keys;
                input::MousePos pos;
            };
        }
        struct Disconnect {};
    }
    namespace tcp {
        // TCP code
        enum class Code {
            AssetAsk,       // from client
            AssetPackage    // from server
        };
        struct AssetAsk {
            long id;
        };
        struct AssetPackage {
            enum class Type {Sound, Texture} type;
            long id_asset;
            std::size_t size_data;
            std::size_t size_config;
            /**
             * Raw data of the asset (Sound or Texture)
             */
            std::vector<std::byte> data;
            /**
             * json : use it only if type == Texture | define how an image has to be cut in sprites
             */
            std::vector<std::byte> config;
        };
    }
    template<typename T>
    struct MessageHeader {
        std::byte firstbyte;
        std::byte secondbyte;
        T code;
        uint32_t body_size;     // security : must be equal as sizeof(type defined by code)
    };
    template<typename T>
    class Message {
        static_assert(std::is_base_of<tcp::Code, T>::value || std::is_base_of<udp::Code, T>::value, "Template argument must be either udp::Code or tcp::Code");
        MessageHeader<T> head;
        std::vector<std::byte> body;
    };
}

#endif
