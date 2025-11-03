#include "game.hpp"
#include "game_status.hpp"
#include "play.hpp"
#include "player_status.hpp"
#include "hands.hpp"
#include <stdexcept>

Game::Game()
{
    game_status.player_1_status = PlayerStatus::S_1_1;
    game_status.player_2_status = PlayerStatus::S_1_1;
    game_status.player_1_plays = true;
}

Game::Game(GameStatus status) : game_status(status) {}


bool Game::is_player_1_victory() const
{
    return !game_status.player_1_plays && game_status.player_2_status == PlayerStatus::S_0_0;
}

bool Game::is_player_2_victory() const
{
    return game_status.player_1_plays && game_status.player_1_status == PlayerStatus::S_0_0;
}

bool Game::is_valid_play(Play play) const
{
    Hands playing_hands{};
    Hands receiving_hands{};
    if(game_status.player_1_plays)
    {
        playing_hands = Hands(game_status.player_1_status, game_status.player_1_greater_on_left);
        receiving_hands = Hands(game_status.player_2_status, game_status.player_2_greater_on_left);
    }else
    {
        playing_hands = Hands(game_status.player_2_status, game_status.player_2_greater_on_left);
        receiving_hands = Hands(game_status.player_1_status, game_status.player_1_greater_on_left);
    }

    switch (play) {
    case (Play::HAND_L_ON_HAND_L):
        return playing_hands.hand_L != 0 && receiving_hands.hand_L != 0;
        
    case (Play::HAND_L_ON_HAND_R):
        return playing_hands.hand_L != 0 && receiving_hands.hand_R != 0;
        
    case (Play::HAND_R_ON_HAND_L):
        return playing_hands.hand_R != 0 && receiving_hands.hand_L != 0;
        
    case (Play::HAND_R_ON_HAND_R):
        return playing_hands.hand_R != 0 && receiving_hands.hand_R != 0;

    case (Play::SPLIT):
        return (playing_hands.hand_L != 0 && playing_hands.hand_L % 2 == 0 && playing_hands.hand_R == 0) ||
               (playing_hands.hand_R != 0 && playing_hands.hand_R % 2 == 0 && playing_hands.hand_L == 0);

    default:
        return false;
    }
}

void Game::play(Play play)
{
    if(!is_valid_play(play))
    {
        throw std::invalid_argument("Invalid play");
    }

    PlayerStatus *playing_player{};
    PlayerStatus *other_player{};
    bool * playing_greater_on_L{};
    bool * other_greater_on_L{};
    Hands playing_player_hands{};
    Hands other_player_hands{};
    if(game_status.player_1_plays)
    {
        playing_player = &game_status.player_1_status;
        playing_player_hands =  Hands(game_status.player_1_status, game_status.player_1_greater_on_left);
        other_player = &game_status.player_2_status;
        other_player_hands =  Hands(game_status.player_2_status, game_status.player_2_greater_on_left);
        playing_greater_on_L = &game_status.player_1_greater_on_left;
        other_greater_on_L = &game_status.player_2_greater_on_left;
    }else
    {
        playing_player = &game_status.player_2_status;
        playing_player_hands =  Hands(game_status.player_2_status, game_status.player_2_greater_on_left);
        other_player = &game_status.player_1_status;
        other_player_hands =  Hands(game_status.player_1_status, game_status.player_1_greater_on_left);
        playing_greater_on_L = &game_status.player_2_greater_on_left;
        other_greater_on_L = &game_status.player_1_greater_on_left;
    }

    game_status.player_1_plays = !game_status.player_1_plays;

    switch (play) {
    
    case(Play::HAND_L_ON_HAND_L):
        other_player_hands.hand_L = (other_player_hands.hand_L + playing_player_hands.hand_L) % 5;
        break;
    case(Play::HAND_L_ON_HAND_R):
        other_player_hands.hand_R = (other_player_hands.hand_R + playing_player_hands.hand_L) % 5;
        break;
    case(Play::HAND_R_ON_HAND_L):
        other_player_hands.hand_L = (other_player_hands.hand_L + playing_player_hands.hand_R) % 5;
        break;
    case(Play::HAND_R_ON_HAND_R):
        other_player_hands.hand_R = (other_player_hands.hand_R + playing_player_hands.hand_R) % 5;
        break;
    case(Play::SPLIT):
        if(playing_player_hands.getGreaterOnLeft())
        {
            playing_player_hands.hand_R = playing_player_hands.hand_L / 2;
            playing_player_hands.hand_L = playing_player_hands.hand_L / 2;
        }else
        {
            playing_player_hands.hand_L = playing_player_hands.hand_R / 2;
            playing_player_hands.hand_R = playing_player_hands.hand_R / 2;
        }
        break;
    }

    *playing_player = playing_player_hands.getStatus();
    *other_player = other_player_hands.getStatus();
    *playing_greater_on_L = playing_player_hands.getGreaterOnLeft();
    *other_greater_on_L = other_player_hands.getGreaterOnLeft();

}

GameStatus Game::getStatus() const
{
    return game_status;
}