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

namespace protocol {
    namespace event {
        constexpr short KeysArraySize = 5;

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

    namespace assets {
        namespace sprite {
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
            struct Transform {
                Rotation rot;
                Position pos;
                Scale scale;
            };
        }
        namespace sound {
            struct Sound {
                float pitch;
                bool isLooping;
            };
        }
    }

    struct PackageClient {
        short nb_keys = 0;
        std::array<event::KeysEvent, event::KeysArraySize> keys;
        event::MousePos pos;
    };
    struct PackageServer {
        enum PkgType {IMAGE, SOUND} type;
        assets::sprite::Transform img_trans;
        assets::sound::Sound sound_opt;
    };
}

#endif
