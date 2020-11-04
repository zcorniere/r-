#include "GameServer.hpp"

GameServer::GameServer(const unsigned port) :
    Server(port)
{};

GameServer::~GameServer()
{};

void GameServer::onMessage(Message<protocol::udp::CodeSendClient> msg) {

}
