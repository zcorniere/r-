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
        constexpr short KEYS_ARRAY_SIZE = 5;
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
    namespace udp {
        constexpr std::pair<std::byte, std::byte> MAGIC_NUMBER = {std::byte{0xFA}, std::byte{0xDA}};
        namespace from_server {
            enum class Code {
                Sprite,
                Sound,
                AssetsList,
                Disconnect,
            };
            struct Sprite {
                long id;
                transform::Rotation rot;
                transform::Position pos;
                transform::Scale scale;
            };
            struct Sound {
                long id;
                float pitch;
                bool isLooping;
            };
            struct AssetsList {
                size_t size;
                unsigned port;
                std::vector<long> list; // list of asset ids
            };
            struct Disconnect {};
        }
        namespace from_client {
            enum class Code {
                Disconnect,
                Ready,
                Input
            };
            struct Disconnect {};
            struct Ready {};
            struct Input {
                short nb_keys = 0;
                std::array<input::KeysEvent, input::KEYS_ARRAY_SIZE> keys;
                input::MousePos pos;
            };
        }
        template<typename T>
        struct MessageHeader {
            static_assert(std::is_base_of<from_server::Code, T>::value || std::is_base_of<from_client::Code, T>::value, "Template parameter must be either from_server::Code or from_client::Code");
            std::byte firstbyte;
            std::byte secondbyte;
            T code;
            uint32_t size;
        };
        template<typename T>
        class Message {
            MessageHeader<T> head;
            std::vector<std::byte> body;
        };
    }
    namespace tcp {
        // what client send to server
        struct AssetsAsk {
            long id;
        };
        // what client receive from server
        struct AssetsPackage {
            enum class Type {Sound, Texture} type;
            long id;
            size_t size;
            std::vector<std::byte> data;
        };
    }
}

#endif
