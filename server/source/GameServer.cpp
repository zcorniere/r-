#include "GameServer.hpp"

using namespace protocol::udp;

GameServer::GameServer(const unsigned port) :
    Server(port)
{
    this->start();
};

GameServer::~GameServer()
{
    Message<CodeSendServer> msg;
    msg.head.code = CodeSendServer::Disconnect;
    this->msgAll(msg);
    this->stop();
};

void GameServer::update(const size_t maxMessage, const bool wait)
{
    auto &q_in = this->getMsgIn();
    if (wait) q_in.wait();
    for (size_t i = 0; i < maxMessage && !q_in.empty(); i++) {
        auto msg = q_in.pop_front();
        this->onMessage(msg);
    }
}

void GameServer::onMessage(Message<CodeSendServer> msg) {
    if (msg.validMagic(protocol::MagicPair) && msg.remote) {
        if (!list.contains(msg.remote)) { list.insert({msg.remote, Player{}}); }
        switch (msg.head.code) {
        case CodeSendServer::Disconnect: msg.remote->disconnect(); break;
        default: break;
        }
    }
}

void GameServer::setAssetPath(const std::string &path) {

}

void GameServer::playSound(const std::string &name, float volume, float pitch) {

}

void GameServer::drawSprite(const std::string &name, const Transform &transf, unsigned int tile_id) {

}

Dimensional GameServer::getCursorLocation() {
    return Dimensional();
}

