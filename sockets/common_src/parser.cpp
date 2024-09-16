#include "parser.h"


Parser::Parser() {}


// server methods
std::string Parser::byte_to_string(uint8_t byte) {
    std::unordered_map<uint8_t, std::string> map_byte_to_word = {
            {1, "JUMP"}, {2, "RIGHT"}, {3, "LEFT"}, {4, "DUCK"}, {5, "HIT"}};

    if (map_byte_to_word.find(byte) != map_byte_to_word.end()) {
        return map_byte_to_word[byte];
    }
    return "";
}


// client methods
std::vector<uint8_t> Parser::line_to_bytes_parser(const std::string& line) {
    std::unordered_map<std::string, uint8_t> word_map = {{"NOP", 0},  {"JUMP", 1}, {"RIGHT", 2},
                                                         {"LEFT", 3}, {"DUCK", 4}, {"HIT", 5}};
    std::vector<uint8_t> result;

    size_t start = 0;
    // Busco el primer espacio, tabulación o salto de línea
    size_t end = line.find_first_of(" \t\n", start);

    while (start != std::string::npos) {
        std::string palabra = line.substr(start, end - start);

        // Verifica si la palabra está en el mapa
        if (word_map.find(palabra) != word_map.end()) {
            result.push_back(word_map[palabra]);
        }

        // Busco el próximo inicio de palabra
        start = line.find_first_not_of(" \t\n", end);
        // Busco el próximo espacio, tabulación o salto de línea
        end = line.find_first_of(" \t\n", start);
    }
    // agrego el NOP par indicar final de linea
    result.push_back(0);
    return result;
}


Parser::~Parser() {}
