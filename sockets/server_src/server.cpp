#include "server.h"

#include <iostream>
#include <sstream>
#include <unordered_map>


Server::Server(const char* servname):
        srv_socket(servname), protocol(srv_socket.accept()), num_cmds(0) {}


void Server::run() {
    std::string line;
    while (not is_close()) {
        line = get_bytes_to_msg();
        if (line == "") {
            break;
        }
        const std::string result = this->game.search_sequences(line);

        std::stringstream ss(result);
        std::string palabra;
        while (ss >> palabra) {
            this->num_cmds++;
        }
        this->protocol.send_msg(result);
    }
}


std::string Server::get_bytes_to_msg() {
    std::string buf;
    while (!this->protocol.is_close()) {
        uint8_t msg = this->protocol.get_byte();

        if (msg == (uint8_t)-1) {
            break;
        }
        buf += this->parser.byte_to_string(msg);
        if (msg == (uint8_t)0) {
            break;
        } else {
            buf += " ";
        }
    }
    return buf;
}


bool Server::is_close() { return this->protocol.is_close(); }


Server::~Server() {
    std::cout << "Actions: " << num_cmds << "\n";
    this->protocol.~ServerProtocol();
}
