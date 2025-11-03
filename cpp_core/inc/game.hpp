#pragma once

#include "inc/game_status.hpp"
#include "inc/play.hpp"

class Game
{
public:
    Game();
    Game(GameStatus game_status);
    bool is_player_1_victory() const;
    bool is_player_2_victory() const;

    void play(Play play);
    bool is_valid_play(Play play) const;

    GameStatus getStatus() const;

private:
    GameStatus game_status;
};