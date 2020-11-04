#include <vector>
#include <array>
#include <cstddef>
#include <cstdint>

#ifndef _PROTOCOL_HPP_
#define _PROTOCOL_HPP_

namespace protocol {
constexpr uint8_t MAGIC_NB_1 = 0xFA;
constexpr uint8_t MAGIC_NB_2 = 0xDA;

namespace udp {
    enum class CodeSendClient { Texture, Sound, AssetsList, Disconnect };

    struct AssetsList {
        size_t size;
        unsigned port;
        std::vector<long> list;
    };

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
    struct Sprite {
        long id_rectangle;
        long id_assets;
        transform::Rotation rot;
        transform::Position pos;
        transform::Scale scale;
    };

    struct Sound {
        long id;
        float pitch;
        bool isLooping;
    };

    enum class CodeSendServer { Disconnect, Ready, Input, AskAssets };
    namespace keys {
        constexpr short ArraySize = 5;

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
    };
    struct Event {
        bool pressed: 1;
        keys::Keys key: 7;
    };
    struct MousePos {
        short y;
        short x;
    };
    struct Input {
        short nb_keys = 0;
        std::array<Event, keys::ArraySize> keys;
        MousePos pos;
    };
}

namespace tcp {
    // Given by client
    enum class AssetsRequest { AskAssets };
    struct AssetsAsk { long id; };

    // Reply by the server
    struct AssetsPackage {
        enum Type {Sound, Texture} type;
        long id;
        size_t size_config;
        size_t size_data;
        std::vector<uint8_t> data;
        std::vector<uint8_t> config;
    };
}
}

#endif //_PROTOCOL_HPP_
