#include <fstream>
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include <filesystem>

#include "AssetsServer.hpp"
#include "Snitch.hpp"

using namespace protocol::tcp;

const std::unordered_map<std::string, protocol::tcp::AssetsPackage::Type> ext_to_type {
    {".png", AssetsPackage::Texture},
    {".gif", AssetsPackage::Texture},
    {".mp3", AssetsPackage::Sound}
};

AssetsServer::AssetsServer(const unsigned port, const std::string &path):
    Server(port), stor(std::make_shared<Storage>(path, [](std::filesystem::path p) {
        if (!ext_to_type.contains(p.extension()))
            return false;
        return true;
    }))
{
    for (auto &[i, e]: stor->getStorage()) {
        if (!ext_to_type.contains(std::filesystem::path(i).extension()))
            continue;
        assets_map.insert({e, ext_to_type.at(std::filesystem::path(i).extension())});
    }
    this->start();
};

AssetsServer::~AssetsServer()
{
    this->stop();
}

void AssetsServer::onMessage(Message<AssetsRequest> msg) {
    Message<AssetsRequest> rep(protocol::MAGIC_NB_1, protocol::MAGIC_NB_2);
    if (msg.validMagic(protocol::MagicPair) && msg.remote) {
        switch (msg.head.code) {
            case AssetsRequest::AskAssets: {
                rep.head.code = AssetsRequest::AssetsPackage;
                auto body = reinterpret_cast<AssetsAsk *>(msg.body.data());
                Snitch::debug("AssetsAsk") << sizeof(AssetsAsk) << Snitch::endl;
                Snitch::debug("AssetsPackage") << sizeof(AssetsPackage) << Snitch::endl;
                try {
                    auto path_data = stor->getPathFromId(body->id);
                    if (!path_data) {
                        Snitch::warn("ASSETS_SERVER") << "Invalid data: " << body->id << Snitch::endl;
                        break;
                    }
                    auto data = this->getFileAt(*path_data);
                    auto config = this->getFileAt(this->getConfigForAssets(*path_data));
                    if (data.size() != 0 && config.size() != 0) {
                        rep.insert(assets_map.at(body->id));
                        rep.insert(body->id);
                        rep.insert(data.size());
                        rep.insert(config.size());
                        rep.insert(data);
                        rep.insert(config);
                        Snitch::debug() << rep.head << Snitch::endl;
                    }
                } catch (const std::runtime_error &re) {
                    Snitch::err("ASSETS_SERVER") << "Exception " << re.what() << Snitch::endl;
                }
            } break;
            default: Snitch::warn("ASSETS_SERVER") << "Unknown comand" << Snitch::endl; break;
        }
    }
    msg.remote->send(rep);
}

std::shared_ptr<Storage> AssetsServer::getStorage()const {
    return stor;
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
    Snitch::debug(path) << ret.size() << Snitch::endl;
    return ret;
}

std::string AssetsServer::getConfigForAssets(std::string path) {
    size_t dot = path.find_last_of('.');
    if (dot == std::string::npos)
        throw std::runtime_error("not dot");
    path.replace(dot, 5, ".json");
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("Not a valid path");
    }
    return path;
}
