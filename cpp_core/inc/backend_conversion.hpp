#include "game_status.hpp"
#include "play.hpp"
#include <vector>

namespace BackendConversion
{

    std::tuple<GameStatus, Play> from_backend_string(const std::string &backend_status);   
    std::string to_backend_string(const GameStatus &game_status, const Play& move, int score);
    std::string to_backend_string(const std::vector<Play> & possible_moves);
}