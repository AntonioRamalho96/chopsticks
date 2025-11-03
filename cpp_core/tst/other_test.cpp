#include "game.hpp"
#include "game_status.hpp"
#include "play.hpp"
#include "player_status.hpp"
#include <cassert>

#include "min_max.hpp"


int main()
{

    GameStatus start{};
    start.player_1_plays = false;
    start.player_1_status = PlayerStatus::S_0_3;
    start.player_1_greater_on_left = false;
    start.player_2_status = PlayerStatus::S_0_4;
    start.player_2_greater_on_left = false;

    Game game{start};

    auto [score, play] = minimax(game, 4);
    assert(play == Play::SPLIT);

    start.player_1_plays = false;
    start.player_1_status = PlayerStatus::S_0_1;
    start.player_1_greater_on_left = false;
    start.player_2_status = PlayerStatus::S_0_4;
    start.player_2_greater_on_left = false;
    game = Game(start);

    game.play(Play::SPLIT);
    auto new_status = game.getStatus();
    assert(new_status.player_1_plays);
    assert(new_status.player_1_status == PlayerStatus::S_0_1);
    assert(new_status.player_1_greater_on_left == false);
    assert(new_status.player_2_status == PlayerStatus::S_2_2);

}