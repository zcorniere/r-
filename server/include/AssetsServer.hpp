#include <unordered_map>
#include <vector>

#ifndef _ASSETSSERVER_HPP_
#define _ASSETSSERVER_HPP_

#include "interface/TcpServer.hpp"
#include "Protocol.hpp"

class AssetsServer: public ecs::tcp::Server<protocol::tcp::AssetsRequest> {
    public:
        AssetsServer(const unsigned port, const std::string &path);
        ~AssetsServer();
        virtual void onMessage(Message<protocol::tcp::AssetsRequest> msg)final;

    private:
        std::vector<uint8_t> getFileAt(const std::string &path);
        std::string getConfigForAssets(std::string path);

    private:
        std::string path;
        std::unordered_map<long, std::pair<std::string, protocol::tcp::AssetsPackage::Type>> assets_map;
};

#endif //_ASSETSSERVER_HPP_
