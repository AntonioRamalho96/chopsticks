#include "play.hpp"
#include <stdexcept>

Play play_from_string(const std::string &play_str)
{
    for(const auto & [play, descr] : PlayValues)
        if(descr == play_str)
            return play;
    throw std::invalid_argument("Invalid play: " + play_str);
}