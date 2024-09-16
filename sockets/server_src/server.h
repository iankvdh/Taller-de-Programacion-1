#ifndef SERVER_H
#define SERVER_H
#include <string>

#include "../common_src/common_socket.h"
#include "../common_src/game.h"
#include "../common_src/parser.h"
#include "../common_src/protocol.h"

class Server {
private:
    Socket srv_socket;
    // cuando usemos threads tendriamos que agregar aca el socket que actualmente es el peer del
    // protocolo
    ServerProtocol protocol;
    Parser parser;
    Game game;
    int num_cmds;

    std::string get_bytes_to_msg();
    bool is_close();

public:
    explicit Server(const char* servname);

    void run();

    ~Server();
};

#endif
