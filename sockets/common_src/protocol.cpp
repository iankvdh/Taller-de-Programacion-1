
#include "protocol.h"

#include <iostream>
#include <utility>
#include <vector>

#include <arpa/inet.h>


// Protocol
Protocol::Protocol(const std::string& host, const std::string& service):
        hostname(host), servname(service), socket(host.c_str(), service.c_str()) {}

Protocol::Protocol(Socket peer): socket(std::move(peer)), was_closed(false) {}

bool Protocol::is_close() { return this->was_closed; }

Protocol::~Protocol() { this->socket.~Socket(); }


// ClientProtocol
ClientProtocol::ClientProtocol(const std::string& host, const std::string& service):
        Protocol(host, service) {}

void ClientProtocol::send_byte(uint8_t& msg) {
    this->socket.sendall(&msg, 1, &this->was_closed);  // envio 1 byte
}

std::string ClientProtocol::get_msg() {
    uint16_t largo;
    int sz = this->socket.recvall(&largo, sizeof(largo), &was_closed);
    if (sz <= 0 or this->was_closed) {
        std::cerr << "No se recibio el largo del mensaje o el socket estaba cerrado" << std::endl;
        return "";
    }
    largo = ntohs(largo);

    std::vector<char> vector(largo);
    sz = this->socket.recvall(vector.data(), largo, &was_closed);
    if (sz <= 0 or this->was_closed) {
        std::cerr << "No se recibio el el mensaje o el socket estaba cerrado" << std::endl;
        return "";
    }
    return std::string(vector.begin(), vector.end());
}


// ServerProtocol
ServerProtocol::ServerProtocol(Socket peer): Protocol(std::move(peer)) {}

void ServerProtocol::send_msg(const std::string& msg) {
    uint16_t tamano = htons(msg.size());
    this->socket.sendall(&tamano, sizeof(tamano), &this->was_closed);
    this->socket.sendall(msg.data(), msg.size(), &this->was_closed);
}

uint8_t ServerProtocol::get_byte() {
    uint8_t buf;
    int sz = this->socket.recvall(&buf, sizeof(buf), &was_closed);
    if (sz <= 0) {
        return -1;  // Si no se recibieron bytes o ocurrió un error, retornamos -1
    }
    return buf;
}
