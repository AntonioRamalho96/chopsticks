#pragma once

#include <map>
#include <string>
enum class Play
{
    HAND_L_ON_HAND_L,
    HAND_L_ON_HAND_R,
    HAND_R_ON_HAND_L,
    HAND_R_ON_HAND_R,
    SPLIT
};

Play play_from_string(const std::string &play_str);

const std::map<Play, std::string> PlayValues = {
    {Play::HAND_L_ON_HAND_L, "left hand on left hand"},
    {Play::HAND_L_ON_HAND_R, "left hand on right hand"},
    {Play::HAND_R_ON_HAND_L, "right hand on left hand"},
    {Play::HAND_R_ON_HAND_R, "right hand on right hand"},
    {Play::SPLIT, "split"}

};