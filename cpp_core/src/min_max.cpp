#include "min_max.hpp"
#include "play.hpp"
#include "player_status.hpp"

#include <memory>
#include <tuple>
#include <unordered_set>

struct MinMaxTreeNode;

struct GameStatusHash {
    std::size_t operator()(const std::unique_ptr<MinMaxTreeNode>& node) const;
};

struct MinMaxTreeNode
{
    Game game;
    int score;
    Play leading_play{};
    Play best_move{};
    std::unordered_set<std::unique_ptr<MinMaxTreeNode>, GameStatusHash> children;
};

inline std::size_t GameStatusHash::operator()(const std::unique_ptr<MinMaxTreeNode>& node) const {
    const GameStatus& status = node->game.getStatus();
    std::size_t result{};
    result += int(status.player_1_plays);
    result = (result << 8);
    result += int(status.player_1_status);
    result = (result << 8);
    result += int(status.player_2_status);
    result = (result << 8);

    return result;
}

bool is_single_hand(PlayerStatus status)
{
    return status == PlayerStatus::S_0_0 ||
           status == PlayerStatus::S_0_1 ||
           status == PlayerStatus::S_0_2 ||
           status == PlayerStatus::S_0_3 ||
           status == PlayerStatus::S_0_4;
}

int minimax_recursive(MinMaxTreeNode& node, int depth) {
    // Terminal conditions
    if (node.game.is_player_1_victory()) {
        node.score = 1000;
        return 1000;
    }
    if (node.game.is_player_2_victory()) {
        node.score = -1000;
        return -1000;
    }
    if (depth == 0) {
        int score = 0;
        if(is_single_hand(node.game.getStatus().player_1_status))
            score -= 10;
        if(is_single_hand(node.game.getStatus().player_2_status))
            score += 10;
        node.score = score; // No winner at this depth, neutral score
        
        return 0;
    }

    // Generate children for all valid plays
    int best_score = node.game.getStatus().player_1_plays ? -10000 : 10000;
    Play best_play{};
    
    for (const auto& [play, descr] : PlayValues) {
        if (!node.game.is_valid_play(play)) {
            continue;
        }

        // Create child node
        Game child_game = node.game;
        child_game.play(play);
        
        auto child = std::make_unique<MinMaxTreeNode>();
        child->game = child_game;
        child->leading_play = play;
        
        // Recursively evaluate child
        int child_score = minimax_recursive(*child, depth - 1);
        child->score = child_score;
        
        // Update best score and best move
        if (node.game.getStatus().player_1_plays) {
            if (child_score > best_score) {
                best_score = child_score;
                best_play = play;
            }
        } else {
            if (child_score < best_score) {
                best_score = child_score;
                best_play = play;
            }
        }
        
        // Add child to the set
        node.children.insert(std::move(child));
    }
    
    node.score = best_score;
    node.best_move = best_play;
    return best_score;
}

std::tuple<int, Play> minimax(const Game& game, int depth) {
    MinMaxTreeNode root;
    root.game = game;
    root.score = 0;
    
    minimax_recursive(root, depth);
    
    return {root.score, root.best_move};
}