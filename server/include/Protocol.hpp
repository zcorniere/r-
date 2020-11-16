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
    enum class RequestCode: uint8_t {
        Texture = 0x01,
        Sound = 0x02,
        AssetsList = 0x03,
        AssetsAsk = 0x04,
        Ready = 0x05,
        Input = 0x06,
        Disconnect = 0x07,
    };

    struct AssetsList {
        unsigned port;
        std::size_t size;
        std::vector<uint64_t> list;
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
        uint64_t id_rectangle;
        uint64_t id_assets;
        transform::Rotation rot;
        transform::Position pos;
        transform::Scale scale;
    };

    struct Sound {
        uint64_t id;
        float volume;
        float pitch;
        bool isLooping;
    };

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
    constexpr uint32_t InputSize = sizeof(keys::Keys) * keys::ArraySize;
}

namespace tcp {
    // Given by client
    enum class AssetsRequest: uint8_t {
        AskAssets = 0x01,
        AssetsPackage = 0x02,
    };
    struct AssetsAsk { uint64_t id; };

    // Reply by the server
    struct AssetsPackage {
        enum Type: bool {Sound = 0x00, Texture = 0x01} type;
        uint64_t id;
        std::size_t size_data;
        std::size_t size_config;
        std::vector<uint8_t> data;
        std::vector<uint8_t> config;
    };
}
}

#endif //_PROTOCOL_HPP_
