#pragma once

#include "inc/player_status.hpp"
#include <ostream>

struct GameStatus
{
    bool player_1_plays;
    bool player_1_greater_on_left;
    bool player_2_greater_on_left;

    PlayerStatus player_1_status;
    PlayerStatus player_2_status;

    friend std::ostream& operator<<(std::ostream& os, const GameStatus &status);

    bool operator==(const GameStatus &other);
};