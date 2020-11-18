#include "GameServer.hpp"
#include "Snitch.hpp"
#include <vector>

using namespace protocol::udp;

GameServer::GameServer(unsigned port, std::filesystem::path &p) :
    Server(port), assets(port + 1, p), port(port)
{
    this->stor = this->assets.getStorage();
    this->start();
};

GameServer::~GameServer()
{
    Message<RequestCode> msg;
    msg.head.code = RequestCode::Disconnect;
    this->msgAll(msg);
};

void GameServer::update() {
    this->Server::update();
    if (!pending_sprite.empty()) {
        std::vector<std::shared_ptr<ecs::IClient<RequestCode>>> playes;
        for (const auto &[i, e]: list) {
            if (e.second.ready) {
                playes.push_back(e.first);
            }
        }
        Message<RequestCode> rep(protocol::MAGIC_NB_1, protocol::MAGIC_NB_2);
        rep.head.code = protocol::udp::RequestCode::SpriteBatch;
        auto end_it = pending_sprite.end();
        if (pending_sprite.size() > SpriteBatchMaxSize) {
            Snitch::warn("GAME_SERVER") << "More than " << SpriteBatchMaxSize << " pendign sprites: " << pending_sprite.size() << Snitch::endl;
            end_it = pending_sprite.begin() + SpriteBatchMaxSize;
        }
        SpriteBatch b;
        b.size = pending_sprite.size();
        std::copy(pending_sprite.begin(), end_it, b.array.begin());
        rep.insert(b);
        for (auto &i: playes) {
            i->send(rep);
        }
        pending_sprite.clear();
    }
    assets.update(4);
}

void GameServer::onMessage(Message<RequestCode> msg) {
    if (msg.validMagic(protocol::MagicPair) && msg.remote) {
        if (!list.contains(msg.remote->getId())) {
            list.insert({msg.remote->getId(), {msg.remote, Player{}}});
        }
        switch (msg.head.code) {
        case RequestCode::Disconnect:
            list.erase(msg.remote->getId());
        break;
        case RequestCode::Ready:
            list.at(msg.remote->getId()).second.ready = true;
            Snitch::debug() << "Client " << msg.remote->getId() << " is ready" << Snitch::endl;
            break;
        case RequestCode::Input: {
            protocol::udp::Input body{};
            std::memcpy(&body.nb_keys, msg.body.data(), sizeof(body.nb_keys));
            std::memcpy(body.keys.data(), msg.body.data() + sizeof(body.nb_keys), InputSize);
            std::memcpy(&body.pos, msg.body.data() + sizeof(body.nb_keys) + InputSize, sizeof(body.pos));
            for (unsigned i = 0; i < body.nb_keys; i++ ) {
                if (body.keys.at(i).pressed)
                    list.at(msg.remote->getId())
                        .second.keys.insert(body.keys.at(i).key);
                else
                    list.at(msg.remote->getId())
                        .second.keys.erase(body.keys.at(i).key);
            }
            list.at(msg.remote->getId()).second.cur_pos.y =
                std::move(body.pos.y);
            list.at(msg.remote->getId()).second.cur_pos.x =
                std::move(body.pos.x);
        } break;
        case RequestCode::AssetsAsk: {
            Message<RequestCode> rep(protocol::MAGIC_NB_1, protocol::MAGIC_NB_2);
            rep.head.code = RequestCode::AssetsList;
            protocol::udp::AssetsList ass;
            ass.port = port + 1;
            for (const auto &[_, e]: stor->getStorage()) {
                ass.list.push_back(e.second);
            }
            ass.size = ass.list.size();
            rep.insert(ass.port);
            rep.insert(ass.size);
            rep.insert(ass.list);
            msg.remote->send(rep);
        } break;
        default: Snitch::warn("GAME_SERVER") << "Unknown comand" << Snitch::endl; break;
        }
    }
}

void GameServer::playSound(const std::string &name, float volume, float pitch,
                           bool looping)
{
    if (!stor)
        throw std::runtime_error("Uninitialized storage");
    Message<RequestCode> rep(protocol::MAGIC_NB_1, protocol::MAGIC_NB_2);
    rep.head.code = protocol::udp::RequestCode::Sound;
    protocol::udp::Sound s;
    s.volume = volume;
    s.pitch = pitch;
    s.isLooping = looping;
    s.isPlaying = true;
    auto v = stor->getIdFromName(name);
    if (!v) {
        Snitch::warn() << "Could not find sound " << name << Snitch::endl;
        return;
    }
    s.id = *v;
    rep.insert(s);
    for (const auto &[i, e] : list) {
        if (e.second.ready) {
            e.first->send(rep);
        }
    }
}

void GameServer::stopSound(const std::string &name)
{
    if (!stor)
        throw std::runtime_error("Uninitialized storage");
    Message<RequestCode> rep(protocol::MAGIC_NB_1, protocol::MAGIC_NB_2);
    rep.head.code = protocol::udp::RequestCode::Sound;
    protocol::udp::Sound s;
    s.volume = 0;
    s.pitch = 0;
    s.isLooping = false;
    s.isPlaying = false;
    auto v = stor->getIdFromName(name);
    if (!v) {
        Snitch::warn() << "Could not find sound " << name << Snitch::endl;
        return;
    }
    s.id = *v;
    rep.insert(s);
    for (const auto &[i, e]: list) {
        if (e.second.ready) {
            e.first->send(rep);
        }
    }
}

void GameServer::drawSprite(const std::string &name, const Transform &transf, unsigned tile_id) {
    if (!stor)
        throw std::runtime_error("Uninitialized storage");
    protocol::udp::Sprite s;
    s.rot.x = transf.rotation.x;
    s.rot.y = transf.rotation.y;
    s.pos.x = transf.location.x;
    s.pos.y = transf.location.y;
    s.scale.x = transf.scale.x;
    s.scale.y = transf.scale.y;
    auto v = stor->getIdFromName(name);
    if (!v) {
        Snitch::err("GAME_SERVER") << name << " can't find name";
        throw std::runtime_error("invalid name");
    }
    s.id_assets = *v;
    s.id_rectangle = tile_id;
    pending_sprite.push_back(s);
}

Dimensional GameServer::getCursorLocation(const unsigned player)
{
    if (list.contains(player)) {
        auto &data = list[player].second;
        if (data.ready)
            return data.cur_pos;
    }
    return Dimensional{-1, -1};
}

bool GameServer::isKeyPressed(unsigned player, ::Input key)
{
    if (list.contains(player)) {
        auto &data = list.at(player).second;
        if (data.ready)
            return data.keys.contains(key);
    }
    return false;
}
