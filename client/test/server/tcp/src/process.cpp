
#include "utils.hpp"

static void send(socket_ptr sock, protocol::MessageToSend<TcpCode> msg)
{
    print(msg);
    std::size_t length = sizeof(msg.head) + msg.head.body_size;
    std::vector<std::byte> buffer;
    buffer.resize(length);
    std::memcpy(buffer.data(), &msg.head, sizeof(msg.head));
    std::memcpy(buffer.data() + sizeof(msg.head), msg.body.data(), msg.head.body_size);
    boost::asio::write(*sock, boost::asio::buffer(buffer, length));
}

void process(socket_ptr sock, protocol::MessageReceived<TcpCode> receive)
{
    if (receive.head().code == TcpCode::AssetAsk) {
        long id;
        std::memcpy(&id, receive.body().data(), sizeof(long));
        if (id == 1) {  // My Texture (orange.jpg)
            protocol::tcp::AssetPackage asset;
            asset.type = protocol::tcp::AssetPackage::Type::Texture;
            asset.id_asset = id;
            asset.config = getTextFile(ASSETS + "/config.json");
            asset.size_config = asset.config.size();
            asset.data = getBinFile(ASSETS + "/orange.jpg");
            asset.size_data = asset.data.size();
            protocol::MessageToSend<TcpCode> msg;
            msg.head.code = TcpCode::AssetPackage;
            msg.body = assetPackageToMsgBody(std::move(asset));
            msg.head.body_size = msg.body.size();
            send(sock, std::move(msg));
        } else if (id == 2) {   // My sound (beep.wav)
            protocol::tcp::AssetPackage asset;
            asset.type = protocol::tcp::AssetPackage::Type::Sound;
            asset.id_asset = id;
            asset.size_config = 0;
            asset.data = getBinFile(ASSETS + "/beep.ogg");
            asset.size_data = asset.data.size();
            protocol::MessageToSend<TcpCode> msg;
            msg.head.code = TcpCode::AssetPackage;
            msg.body = assetPackageToMsgBody(std::move(asset));
            msg.head.body_size = msg.body.size();
            send(sock, std::move(msg));
        } else {
            std::cerr << "[TCP][AssetAsk] Wrong id : " << id << std::endl;
        }
    } else {
        std::cerr << "[UDP] Wrong data received : wrong code" << std::endl;
    }
}