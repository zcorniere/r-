#include <unordered_map>
#include <vector>
#include <fstream>
#include <iterator>

#ifndef _ASSETSSERVER_HPP_
#define _ASSETSSERVER_HPP_

#include "interface/TcpServer.hpp"
#include "Protocol.hpp"

class AssetsServer: public ecs::tcp::Server<protocol::tcp::AssetsRequest> {
    public:
        AssetsServer(const unsigned port);
        virtual void onMessage(Message<protocol::tcp::AssetsRequest> msg)final;

    private:
        std::unordered_map<long, std::pair<std::string, protocol::tcp::AssetsPackage::Type>> assets_map;
        std::unordered_map<long, protocol::tcp::AssetsRequest> type_map;
};

#endif //_ASSETSSERVER_HPP_
