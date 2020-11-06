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

void GameServer::update() {
    this->Server::update();
}

void GameServer::onMessage(Message<CodeSendServer> msg) {
    if (msg.validMagic(protocol::MagicPair) && msg.remote) {
        if (!list.contains(msg.remote)) { list.insert({msg.remote, Player{}}); }
        switch (msg.head.code) {
        case CodeSendServer::Disconnect: msg.remote->disconnect(); break;
        case CodeSendServer::Ready: list.at(msg.remote).ready = true; break;
        case CodeSendServer::Input: {
            auto body = reinterpret_cast<protocol::udp::Input *>(msg.body.data());
            if (!body) { break; }
            list.at(msg.remote).nb_key = body->nb_keys;
            list.at(msg.remote).input = body->keys;
            list.at(msg.remote).cur_pos.y = body->pos.y;
            list.at(msg.remote).cur_pos.x = body->pos.x;
        } break;
        default: break;
        }
    }
}

void GameServer::playSound(const std::string &name, float volume, float pitch) {

}

void GameServer::drawSprite(const std::string &name, const Transform &transf, unsigned int tile_id) {

}

Dimensional GameServer::getCursorLocation() {
    return Dimensional();
}

std::vector<::Input> GameServer::getInputEvents() {
    return std::vector<::Input>(0);
}
