#include <fstream>
#include <iterator>
#include <algorithm>

#include "AssetsServer.hpp"

AssetsServer::AssetsServer(const unsigned port):
    Server(port)
{
    this->start();
};

AssetsServer::~AssetsServer()
{
    this->stop();
}

void AssetsServer::onMessage(Message<protocol::tcp::AssetsRequest> msg) {
    Message<protocol::tcp::AssetsRequest> rep;
    if (msg.validMagic(protocol::MagicPair) && msg.remote) {
        switch (msg.head.code) {
            case protocol::tcp::AssetsRequest::AskAssets: {
                auto body = reinterpret_cast<protocol::tcp::AssetsAsk *>(msg.body.data());
                if (!assets_map.contains(body->id)) {
                    break;
                }
                protocol::tcp::AssetsPackage reply;
                std::ifstream file;
                file.open(assets_map.at(body->id).first);
                if (file.is_open()) {
                    file >> std::noskipws;
                    std::copy(std::istream_iterator<uint8_t>(file),
                              std::istream_iterator<uint8_t>(),
                              std::back_inserter(reply.data));
                    reply.id = body->id;
                    reply.type = assets_map.at(body->id).second;
                    rep.head.code = msg.head.code;
                    auto ptr = reinterpret_cast<std::byte *>(&reply);
                    rep.body = std::vector<std::byte>(ptr, ptr + sizeof(reply));
                    file.close();
                }
            } break;
            default: break;
        }
    }
    msg.remote->send(rep);
}
