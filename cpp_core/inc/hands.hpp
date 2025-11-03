#include "player_status.hpp"
class Hands
{
public:
    int hand_L;
    int hand_R;
    Hands();
    Hands(PlayerStatus status, bool greater_on_L);
    Hands(int hand_L, int hand_R);
    PlayerStatus getStatus() const;
    bool getGreaterOnLeft() const;

};

std::ostream & operator<<(std::ostream & os, const Hands &hands);