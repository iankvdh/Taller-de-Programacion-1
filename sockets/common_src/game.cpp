#include "game.h"

#include <iostream>
#include <sstream>
#include <unordered_map>

Game::Game() {}

std::string Game::search_sequences(const std::string& line) {
    if (line == "") {
        return line;
    }
    std::unordered_map<std::string, std::string> sequences = {{"JUMP JUMP HIT", "UPPERCUT"},
                                                              {"HIT DUCK LEFT", "SIDEKICK"},
                                                              {"LEFT RIGHT JUMP HIT", "HIGHKICK"}};

    std::istringstream stream(line);
    std::string palabra;
    std::string result;

    while (stream >> palabra) {
        result += palabra + " ";
        for (const auto& sequence: sequences) {
            if (result.find(sequence.first) != std::string::npos) {
                result.replace(result.find(sequence.first), sequence.first.length(),
                               sequence.second);
                result.pop_back();  // Eliminar el último espacio
                result += " ";
                break;
            }
        }
    }
    result.pop_back();  // Eliminar el último espacio
    return result;
}

Game::~Game() {}
