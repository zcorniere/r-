#ifndef RTYPE_LOAD_GAME_H_
#define RTYPE_LOAD_GAME_H_

#include "Game.hpp"

// Loads all the systems and components of the R-Type
// Loads the first Game state of the R-Type
void load_game(Game &game);

// Complex algorythm that create the collision boxes of the walls
void build_walls(Game &instance, float scrolling_speed, float scrolling_ticks);

#endif // RTYPE_LOAD_GAME_H_
