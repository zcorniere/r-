#include "GameServer.hpp"

using namespace protocol::udp;

GameServer::GameServer(std::shared_ptr<Storage> stor, const unsigned port) :
    Server(port), stor(stor)
{
    this->start();
};

GameServer::~GameServer()
{
    Message<RequestCode> msg;
    msg.head.code = RequestCode::Disconnect;
    this->msgAll(msg);
    this->stop();
};

void GameServer::update() {
    this->Server::update();
}

void GameServer::onMessage(Message<RequestCode> msg) {
    if (msg.validMagic(protocol::MagicPair) && msg.remote) {
        if (!list.contains(msg.remote)) { list.insert({msg.remote, Player{}}); }
        switch (msg.head.code) {
        case RequestCode::Disconnect: msg.remote->disconnect(); break;
        case RequestCode::Ready: list.at(msg.remote).ready = true; break;
        case RequestCode::Input: {
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

void GameServer::playSound(const unsigned player, const std::string &name, float volume, float pitch) {
    if (!stor)
        throw std::runtime_error("Uninitialized storage");
    Message<RequestCode> rep;
    rep.head.code = protocol::udp::RequestCode::Sound;
    protocol::udp::Sound s;
    s.volume = volume;
    s.pitch = pitch;
    s.isLooping = false;
    auto v = stor->getIdFromPath(name);
    s.id = v ? *v : -1;
    rep.insert(s);
    this->msgAll(rep);
}

void GameServer::drawSprite(const unsigned player, const std::string &name, const Transform &transf, unsigned int tile_id) {
    if (!stor)
        throw std::runtime_error("Uninitialized storage");
}

Dimensional GameServer::getCursorLocation(const unsigned player) {
    for (const auto &[e, i] : list) {
        if (e->getId() == player) {
            return i.cur_pos;
        }
    }
    return Dimensional {-1, -1};
}

std::vector<::Input> GameServer::getInputEvents(const unsigned player) {
    for (const auto &[e, i] : list) {
        if (e->getId() == player) {
            std::vector<::Input> ret(i.input.size());
            for (const auto &i: i.input) {
                ret.emplace_back(i);
            }
            return ret;
        }
    }
    return std::vector<::Input>();
}
