#ifndef _GAMESERVER_HPP_
#define _GAMESERVER_HPP_

#include "interface/UdpServer.hpp"

class GameServer: public ecs::udp::Server<protocol::udp::CodeSendClient> {
    public:
        GameServer(const unsigned port);
        ~GameServer();

        virtual void onMessage(Message<protocol::udp::CodeSendClient> msg)final;
};
#endif //_GAMESERVER_HPP_
