#include "game.hpp"
#include "play.hpp"

#include <iostream>

int main()
{
    Game game;

    for (;;) {
        // show game status (expects either operator<< for game or a status() method)
        std::cout << "Current game status:\n";
        std::cout << game.getStatus() << "\n\n";


        std::cout << "Possible plays (enter the number and press Enter):\n";
        for (const auto &val : PlayValues) {
            if(game.is_valid_play(val.first))
                std::cout << "  " << int(val.first) << " - " << val.second << '\n';
        }
        std::cout << "  q) quit\n> ";

        std::string line;
        if (!std::getline(std::cin, line)) break;
        if (line == "q" || line == "Q") break;

        try {
            int sel = std::stoi(line);
            auto choice = static_cast<Play>(sel);
            game.play(choice); // call game.play with the chosen enum value
            std::cout << "\n";
        } catch (...) {
            std::cout << "Invalid input, enter a number or 'q' to quit.\n\n";
        }
    }
}