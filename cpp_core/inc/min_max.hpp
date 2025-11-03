#include "game.hpp"
#include "play.hpp"
#include <tuple>


std::tuple<int, Play> minimax(const Game& game, int depth);