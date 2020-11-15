#include "Game.hpp"
#include "SfmlAudioModule.hpp"
#include "SfmlModule.hpp"
#include "load_game.hpp"
#include "components/CollisionBox.hpp"
#include <iostream>
#include <boost/dll/runtime_symbol_info.hpp>
#include <cstdlib>

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

    /*
    ** MODULES
    ** external objects to interact with the exterior
    */

    std::unique_ptr<IModule> sfml_module(new SfmlModule(
        "R-Type SOLO v0.1",
        assets_location));
    auto audio_module = std::make_unique<SfmlAudioModule>();

    game.addModule("sfml", std::move(sfml_module));
    game.setDisplayModule("sfml");
    game.setInputModule("sfml");
    game.addModule("audio-sfml", std::move(audio_module));
    game.setAudioModule("audio-sfml");

    // Load the R-Type Game
    load_game(game);

    // DEBUG dollision displayer
    game.systemStorage.addSystem([]
    (IDisplayModule &display, const Transform &transform, const CollisionBox &box) {
        sf::RectangleShape rect;
        rect.setPosition(transform.location.x + box.offset_x * transform.scale.x, transform.location.y + box.offset_y * transform.scale.y);
        rect.setSize(sf::Vector2f(box.width * transform.scale.x, box.height * transform.scale.y))    ;
        dynamic_cast<SfmlModule &>(display).drawDebugBox(rect);
    });

    game.run();
}
