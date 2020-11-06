#include <vector>
#include <array>
#include <cstddef>
#include <cstdint>

#ifndef _PROTOCOL_HPP_
#define _PROTOCOL_HPP_

#include "Modules.hpp"

namespace protocol {
constexpr uint8_t MAGIC_NB_1 = 0xFA;
constexpr uint8_t MAGIC_NB_2 = 0xDA;

constexpr std::pair<uint8_t, uint8_t> MagicPair = {MAGIC_NB_1, MAGIC_NB_2};

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
        typedef ::Input Keys;
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
