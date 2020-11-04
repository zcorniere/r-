#include "GameServer.hpp"

GameServer::GameServer(const unsigned port) :
    Server(port)
{
    this->start();
};

GameServer::~GameServer()
{
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

void GameServer::onMessage(Message<protocol::udp::CodeSendServer> msg) {
    if (msg.validMagic(protocol::MagicPair) && msg.remote) {
        switch (msg.head.code) {

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
    return cur_pos;
}

