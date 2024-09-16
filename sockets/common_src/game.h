#ifndef GAME_H
#define GAME_H
#include <string>


class Game {
public:
    Game();
    std::string search_sequences(const std::string& line);
    ~Game();
};

#endif
