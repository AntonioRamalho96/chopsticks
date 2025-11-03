#include "controller.hpp"

#include "backend_conversion.hpp"
#include "game.hpp"
#include "game_status.hpp"
#include "min_max.hpp"
#include "play.hpp"

#include <cstring>
#include <string>
#include <vector>

std::string make_a_computer_move_cpp(const std::string &backend_msg);
std::string make_a_player_move_cpp(const std::string &backend_msg);
std::string get_available_moves_cpp(const std::string &backend_message);



const char * convert_to_c_str(const std::string &cpp_str)
{
    char * c_str = new char[cpp_str.size() + 1];
    std::strcpy(c_str, cpp_str.data());
    return c_str;
}




const char * make_a_computer_move(const char * backend_message)
{
    return convert_to_c_str(make_a_computer_move_cpp(backend_message).c_str());
}
const char * make_a_player_move(const char * backend_message)
{
    return convert_to_c_str(make_a_player_move_cpp(backend_message).c_str());
    
}

const char * get_available_moves(const char *backend_message)
{
    return convert_to_c_str(get_available_moves_cpp(backend_message).c_str());
    
}

std::string make_a_computer_move_cpp(const std::string &backend_msg)
{
    const auto [prev_status, unused] = BackendConversion::from_backend_string(backend_msg);
    Game game{prev_status};

    auto [score, move] = minimax(game, 10);
    game.play(move);

    return BackendConversion::to_backend_string(game.getStatus(), move, score);
}

std::string make_a_player_move_cpp(const std::string &backend_msg)
{
    const auto [prev_status, player_move] = BackendConversion::from_backend_string(backend_msg);
    Game game{prev_status};
    game.play(player_move);


    return BackendConversion::to_backend_string(game.getStatus(), player_move, 0);
}

std::string get_available_moves_cpp(const std::string &backend_msg)
{
    const auto [prev_status, unused] = BackendConversion::from_backend_string(backend_msg);
    Game game{prev_status};
    
    std::vector<Play> possible_moves{};
    for(const auto & [move, descr] : PlayValues)
        if(game.is_valid_play(move))
            possible_moves.push_back(move);
    
    return BackendConversion::to_backend_string(possible_moves);
}
