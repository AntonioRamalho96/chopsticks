#include "game_status.hpp"
#include "hands.hpp"
#include <ostream>

std::ostream& operator<<(std::ostream& os, const GameStatus &status)
{
    // player 2
    os << Hands(status.player_2_status, status.player_2_greater_on_left);
    if(!status.player_1_plays)
    {
        os << " P";
    }
    os << std::endl;
    // Player 1
    os << Hands(status.player_1_status, status.player_1_greater_on_left);
    if(status.player_1_plays)
    {
        os << " P";
    }
    
    

    return os;
}

bool GameStatus::operator==(const GameStatus &other)
{
    return this->player_1_plays == other.player_1_plays &&
           this->player_1_greater_on_left == other.player_1_greater_on_left &&
           this->player_2_greater_on_left == other.player_2_greater_on_left &&
           this->player_1_status == other.player_1_status &&
           this->player_2_status == other.player_2_status;
}