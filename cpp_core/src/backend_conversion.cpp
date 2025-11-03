#include "backend_conversion.hpp"

#include "game_status.hpp"
#include "play.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include "hands.hpp"


namespace BackendConversion
{

    rapidjson::Value str_to_value(const std::string &str)
    {
        rapidjson::Value value{};
        value.SetString(str.c_str(), str.size());
        return  value;
    }

    std::tuple<GameStatus, Play>  from_backend_string(const std::string &backend_status)
    {
        rapidjson::Document doc{};
        doc.Parse<0>(backend_status.c_str());
        // Parse json
        int TL_hand = doc["TL_hand"].GetInt();
        int TR_hand = doc["TR_hand"].GetInt();
        int BL_hand = doc["BL_hand"].GetInt();
        int BR_hand = doc["BR_hand"].GetInt();
        std::string move_cpp = doc["move_cpp"].GetString();

        // Process
        Hands player_1_hands{BL_hand, BR_hand};
        Hands player_2_hands{TL_hand, TR_hand};

        // Populate result
        GameStatus result{};
        result.player_1_plays = doc["player1_plays"].GetBool();
        result.player_1_status = player_1_hands.getStatus();
        result.player_1_greater_on_left = player_1_hands.getGreaterOnLeft();
        result.player_2_status = player_2_hands.getStatus();
        result.player_2_greater_on_left = player_2_hands.getGreaterOnLeft();
        
        return {result, play_from_string(move_cpp)};
    }

    std::string to_backend_string(const GameStatus &game_status, const Play & move, int score)
    {
        Hands player_1_hands{game_status.player_1_status, game_status.player_1_greater_on_left};
        Hands player_2_hands{game_status.player_2_status, game_status.player_2_greater_on_left};
        
        rapidjson::Document doc{};
        doc.SetObject();
        auto& allocator = doc.GetAllocator();
        
        doc.AddMember("player1_plays", game_status.player_1_plays, allocator);
        doc.AddMember("TL_hand", player_2_hands.hand_L, allocator);
        doc.AddMember("TR_hand", player_2_hands.hand_R, allocator);
        doc.AddMember("BL_hand", player_1_hands.hand_L, allocator);
        doc.AddMember("BR_hand", player_1_hands.hand_R, allocator);
        
        std::string move_description = PlayValues.at(move);
        rapidjson::Value movedesc{};
        movedesc.SetString(move_description.c_str(), move_description.size(), allocator);
        doc.AddMember("move_cpp", movedesc, allocator);
        doc.AddMember("score", score, allocator);
        
        // To string
        using namespace rapidjson;
        StringBuffer buffer;
        Writer<StringBuffer> writer{buffer};
        doc.Accept(writer);
        return buffer.GetString();
        
    }


    std::string to_backend_string(const std::vector<Play> & possible_moves)
    {
        rapidjson::Document doc{};
        doc.SetObject();
        auto& allocator = doc.GetAllocator();
        
        // Create array for moves
        rapidjson::Value moves_array(rapidjson::kArrayType);
        for (const auto& play : possible_moves)
            moves_array.PushBack(str_to_value(PlayValues.at(play)), allocator);
        
        // Add the array to the document
        doc.AddMember("possible_moves", moves_array, allocator);
        
        // To string
        using namespace rapidjson;
        StringBuffer buffer;
        Writer<StringBuffer> writer{buffer};
        doc.Accept(writer);
        return buffer.GetString();
    }
}