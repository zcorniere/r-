#include <fstream>
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include <filesystem>

#include "AssetsServer.hpp"

const std::unordered_map<std::string, protocol::tcp::AssetsPackage::Type> ext_to_type {
    {".png", protocol::tcp::AssetsPackage::Texture},
    {".gif", protocol::tcp::AssetsPackage::Texture},
    {".mp3", protocol::tcp::AssetsPackage::Sound}
};

AssetsServer::AssetsServer(const unsigned port, const std::string &path):
    Server(port), path(path)
{
    long id = 0;
    for (const auto &e: std::filesystem::directory_iterator(path)) {
        auto path = e.path();
        assets_map.insert({id++, {path.string(), ext_to_type.at(path.extension())}});
    }
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
                reply.data = this->getFileAt(assets_map.at(body->id).first);
                reply.config = this->getFileAt(this->getConfigForAssets(assets_map.at(body->id).first));
                if (reply.data.size() != 0 && reply.config.size() != 0) {
                    reply.size_data = reply.data.size();
                    reply.size_config = reply.config.size();
                    reply.id = body->id;
                    reply.type = assets_map.at(body->id).second;
                    rep.head.code = msg.head.code;
                    rep.insert(reply);
                }
            } break;
            default: break;
        }
    }
    msg.remote->send(rep);
}

std::vector<uint8_t> AssetsServer::getFileAt(const std::string &path) {
    std::vector<uint8_t> ret;
    std::ifstream file;
    file.open(path);
    if (file.is_open()) {
        file >> std::noskipws;
        std::copy(std::istream_iterator<uint8_t>(file),
                  std::istream_iterator<uint8_t>(),
                  std::back_inserter(ret));
        file.close();
    }
    return ret;
}

std::string AssetsServer::getConfigForAssets(std::string path) {
    size_t dot = path.find_last_of('0');
    path.insert(dot, "_config");
    return path;
}
