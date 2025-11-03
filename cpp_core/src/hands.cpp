#include "hands.hpp"
#include "player_status.hpp"
#include <array>
#include <stdexcept>
#include <utility>

Hands::Hands() : Hands(PlayerStatus::S_0_0, false) {}

Hands::Hands(PlayerStatus status, bool greater_on_L) {
    switch (status) {
    case PlayerStatus::S_0_0:
        hand_L = 0;
        hand_R = 0;
        break;
    case PlayerStatus::S_0_1:
        hand_L = 0;
        hand_R = 1;
        break;
    case PlayerStatus::S_0_2:
        hand_L = 0;
        hand_R = 2;
        break;
    case PlayerStatus::S_0_3:
        hand_L = 0;
        hand_R = 3;
        break;
    case PlayerStatus::S_0_4:
        hand_L = 0;
        hand_R = 4;
        break;
    case PlayerStatus::S_1_1:
        hand_L = 1;
        hand_R = 1;
        break;
    case PlayerStatus::S_1_2:
        hand_L = 1;
        hand_R = 2;
        break;
    case PlayerStatus::S_1_3:
        hand_L = 1;
        hand_R = 3;
        break;
    case PlayerStatus::S_1_4:
        hand_L = 1;
        hand_R = 4;
        break;
    case PlayerStatus::S_2_2:
        hand_L = 2;
        hand_R = 2;
        break;
    case PlayerStatus::S_2_3:
        hand_L = 2;
        hand_R = 3;
        break;
    case PlayerStatus::S_2_4:
        hand_L = 2;
        hand_R = 4;
        break;
    case PlayerStatus::S_3_3:
        hand_L = 3;
        hand_R = 3;
        break;
    case PlayerStatus::S_3_4:
        hand_L = 3;
        hand_R = 4;
        break;
    case PlayerStatus::S_4_4:
        hand_L = 4;
        hand_R = 4;
        break;
    }

    if(greater_on_L)
        std::swap(hand_L, hand_R);
}

Hands::Hands(int hand_L, int hand_R) : hand_L(hand_L), hand_R(hand_R) {
}

PlayerStatus Hands::getStatus() const
{
    int greater_hand{};
    int smaller_hand{};
    if(hand_L > hand_R)
    {
        greater_hand = hand_L;
        smaller_hand = hand_R;
    }else
    {
        greater_hand = hand_R;
        smaller_hand = hand_L;
    }
    
    if(smaller_hand == 0 && greater_hand == 0)
        return PlayerStatus::S_0_0;
    if(smaller_hand == 0 && greater_hand == 1)
        return PlayerStatus::S_0_1;
    if(smaller_hand == 0 && greater_hand == 2)
        return PlayerStatus::S_0_2;
    if(smaller_hand == 0 && greater_hand == 3)
        return PlayerStatus::S_0_3;
    if(smaller_hand == 0 && greater_hand == 4)
        return PlayerStatus::S_0_4;
    if(smaller_hand == 1 && greater_hand == 1)
        return PlayerStatus::S_1_1;
    if(smaller_hand == 1 && greater_hand == 2)
        return PlayerStatus::S_1_2;
    if(smaller_hand == 1 && greater_hand == 3)
        return PlayerStatus::S_1_3;
    if(smaller_hand == 1 && greater_hand == 4)
        return PlayerStatus::S_1_4;
    if(smaller_hand == 2 && greater_hand == 2)
        return PlayerStatus::S_2_2;
    if(smaller_hand == 2 && greater_hand == 3)
        return PlayerStatus::S_2_3;
    if(smaller_hand == 2 && greater_hand == 4)
        return PlayerStatus::S_2_4;
    if(smaller_hand == 3 && greater_hand == 3)
        return PlayerStatus::S_3_3;
    if(smaller_hand == 3 && greater_hand == 4)
        return PlayerStatus::S_3_4;
    if(smaller_hand == 4 && greater_hand == 4)
        return PlayerStatus::S_4_4;

    throw std::runtime_error("Invalid hand status");

}
bool Hands::getGreaterOnLeft() const
{
    return hand_L > hand_R;
}

std::ostream& operator<<(std::ostream &os, const Hands &hands)
{
    os << '(' << hands.hand_L << ',' << hands.hand_R << ')';
    return os;
}