#include "Game.hpp"
#include "GameServer.hpp"
#include "load_game.hpp"
#include <boost/dll/runtime_symbol_info.hpp>

int main(void)
{
    Game game("R-Type SOLO");
    std::filesystem::path assets_location =
        std::filesystem::path(boost::dll::program_location().string())
            .parent_path()
            .parent_path()
            .parent_path()
            .append("draft")
            .append("assets");

    std::unique_ptr<IModule> game_server(
        new GameServer(25555, assets_location));

    game.addModule("server", std::move(game_server));
    game.setDisplayModule("server");
    game.setInputModule("server");
    game.setAudioModule("server");

    // Load the R-Type Game
    load_game(game);

    game.run();
}
