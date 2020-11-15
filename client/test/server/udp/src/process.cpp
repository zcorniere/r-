
#include "utils.hpp"

static void send(udp::socket& sock, udp::endpoint &endpoint, protocol::MessageToSend<UdpCode> msg)
{
    print(msg);
    std::size_t length = sizeof(msg.head) + msg.head.body_size;
    std::vector<std::byte> buffer;
    buffer.resize(length);
    std::memcpy(buffer.data(), &msg.head, sizeof(msg.head));
    std::memcpy(buffer.data() + sizeof(msg.head), msg.body.data(), msg.head.body_size);
    sock.send_to(boost::asio::buffer(buffer, length), endpoint);
}

void process(udp::socket &sock, udp::endpoint &endpoint, protocol::MessageReceived<UdpCode> receive)
{
    bool is_send(true);
    protocol::MessageToSend<UdpCode> msg;
    if (receive.head().code == UdpCode::AskAssetList) {
        protocol::udp::from_server::AssetList assetlist;
        assetlist.port = 25545;
        assetlist.list.push_back(1);
        assetlist.list.push_back(2);
        assetlist.size = assetlist.list.size();
        msg.head.code = UdpCode::AssetList;
        msg.head.body_size = sizeof(assetlist.port) + sizeof(assetlist.size) + assetlist.list.size() * sizeof(long);
        msg.body.resize(sizeof(assetlist.port) + sizeof(assetlist.size) + assetlist.list.size() * sizeof(long));
        std::memcpy(msg.body.data(), &assetlist.port, sizeof(assetlist.port));
        std::memcpy(msg.body.data() +  sizeof(assetlist.port), &assetlist.size,  sizeof(assetlist.size));
        std::memcpy(msg.body.data() +  sizeof(assetlist.port) + sizeof(assetlist.size), assetlist.list.data(), assetlist.list.size() * sizeof(long));
    } else if (receive.head().code == UdpCode::Ready) {
        std::cout << "Client is ready ! server send sound !" << std::endl;
        protocol::udp::from_server::Sound sound;
        sound.id = 2;
        sound.isLooping = true;
        sound.pitch = 1.0f;
        msg.head.code = UdpCode::Sound;
        msg.head.body_size = sizeof(sound);
        msg.body.resize(msg.head.body_size);
        std::memcpy(msg.body.data(), &sound, msg.head.body_size);
    } else if (receive.head().code == UdpCode::Input) {
        std::cout << "Client send is inputs ! server send sprite" << std::endl;
        printInput(receive);
        protocol::udp::from_server::Sprite sprite;
        sprite.id_asset = 1;
        sprite.id_sprite = 0;
        sprite.pos = {-300, -300};
        sprite.rot = {0, 0};
        sprite.scale = {10, 10};
        msg.head.code = UdpCode::Sprite;
        msg.head.body_size = sizeof(sprite);
        msg.body.resize(msg.head.body_size);
        std::memcpy(msg.body.data(), &sprite, msg.head.body_size);
    } else if (receive.head().code == UdpCode::Disconnect) {
        std::cout << "Client is disconnected !" << std::endl;
    } else {
        std::cerr << "Unknown message received" << std::endl;
        is_send = false;
    }
    if (is_send) send(sock, endpoint, msg);
}