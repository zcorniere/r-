
#include "utils.hpp"

std::string udpCode_interpreter(UdpCode code)
{
    if (code == UdpCode::Sprite) return "Sprite";
    if (code == UdpCode::Sound) return "Sound";
    if (code == UdpCode::AssetList) return "AssetList";
    if (code == UdpCode::AskAssetList) return "AskAssetList";
    if (code == UdpCode::Ready) return "Ready";
    if (code == UdpCode::Input) return "Input";
    if (code == UdpCode::Disconnect) return "Disconnect";
    return "ERROR in UdpCode";
}

void print(protocol::MessageReceived<UdpCode> message)
{
    std::cout << "message received" << std::endl;
    std::cout << "head.firstbyte  : " << std::to_string(static_cast<int>(message.head().firstbyte)) << std::endl;
    std::cout << "head.secondbyte : " << std::to_string(static_cast<int>(message.head().secondbyte)) << std::endl;
    std::cout << "head.code       : " << udpCode_interpreter(message.head().code) << std::endl;
    std::cout << "head.bodysize   : " << std::to_string(message.head().body_size) << std::endl;
    auto body = message.body();
    for (int i = 0; i < message.head().body_size; ++i) {
        std::cout << " | " << static_cast<int>(static_cast<const char *>(body.data())[i]);
    }
    if (message.head().body_size > 0)
        std::cout << std::endl;
}

void print(protocol::MessageToSend<UdpCode> message)
{
    std::cout << "message sended" << std::endl;
    std::cout << "head.firstbyte  : " << std::to_string(static_cast<int>(message.head.firstbyte)) << std::endl;
    std::cout << "head.secondbyte : " << std::to_string(static_cast<int>(message.head.secondbyte)) << std::endl;
    std::cout << "head.code       : " << udpCode_interpreter(message.head.code) << std::endl;
    std::cout << "head.bodysize   : " << std::to_string(message.head.body_size) << std::endl;
    auto body = message.body;
    for (int i = 0; i < message.head.body_size; ++i) {
        std::cout << " | " << static_cast<int>(static_cast<char>(body[i]));
    }
    if (message.head.body_size > 0)
        std::cout << std::endl;
}

void printInput( protocol::MessageReceived<UdpCode> receive)
{
    std::cout << "Inputs:" << std::endl;
    protocol::udp::from_client::Input input;
    auto body_size = receive.head().body_size;
    auto it = receive.body();
    auto keys_size = sizeof(protocol::input::KeysEvent) * protocol::input::keys_array_size;

    std::memcpy(&input.nb_keys, it.data(), sizeof(input.nb_keys));
    it += sizeof(input.nb_keys);
    std::memcpy(input.keys.data(), it.data(), keys_size);
    it += keys_size;
    std::memcpy(&input.pos, it.data(), sizeof(input.pos));
    std::cout << "Keys : ";
    for (auto i = 0; i < input.nb_keys; ++i) {
        std::cout << "[" <<  static_cast<char>(input.keys[i].key);
        std::cout << "|";
        std::cout << (input.keys[i].pressed ? "PRESSED" : "RELEASED");
        std::cout << "] ";
    }
    std::cout << std::endl;
    std::cout << "Cursor : " << input.pos.x << " , " << input.pos.y << std::endl;
}