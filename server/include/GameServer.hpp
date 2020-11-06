#include <array>
#include <unordered_map>

#ifndef _GAMESERVER_HPP_
#define _GAMESERVER_HPP_

#include "Modules.hpp"
#include "interface/UdpServer.hpp"

struct Player {
    bool ready = false;
    short nb_key = 0;
    std::array<protocol::udp::Event, protocol::udp::keys::ArraySize> input;
    Dimensional cur_pos = {0, 0};
};

class GameServer:
    public ecs::udp::Server<protocol::udp::CodeSendServer>,
    public IAudioModule,
    public IDisplayModule,
    public IInputModule
{
    public:
        GameServer(const unsigned port);
        ~GameServer();

        // Required by IModule
        virtual void update()final;

        // Required by ecs::udp::Server
        virtual void onMessage(Message<protocol::udp::CodeSendServer> msg)final;

        // Required by IAudioModule
        virtual void playSound(const std::string &name, float volume, float pitch)final;

        // Required by IDisplayModule
        virtual void drawSprite(const std::string &name, Transform const &transf, unsigned tile_id)final;

        // Required by IInputModule
        virtual Dimensional getCursorLocation()final;
        virtual std::vector<Input> getInputEvents()final;

    private:
        std::unordered_map<std::shared_ptr<ecs::IClient<protocol::udp::CodeSendServer>>, Player> list;
        std::string path;

};

#endif //_GAMESERVER_HPP_
