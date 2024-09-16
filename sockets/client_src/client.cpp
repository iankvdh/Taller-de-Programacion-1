#include "client.h"

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>


Client::Client(const std::string& host, const std::string& service):
        protocol(std::move(host), std::move(service)) {}


void Client::run() {
    std::string line;
    while (std::getline(std::cin, line)) {
        std::vector<uint8_t> serialized_line = this->parser.line_to_bytes_parser(line);
        for (uint8_t& elemento: serialized_line) {
            // this->protocol.send_byte(elemento);
            this->protocol.send_byte(elemento);
        }
        get_and_print_line();
    }
}


void Client::run_from_input(const char* input) {
    // Abrir el archivo para lectura
    std::ifstream archive(input);
    if (!archive.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << input << std::endl;
        return;
    }

    std::string linea;
    std::vector<uint8_t> linea_serealizada;

    while (std::getline(archive, linea)) {
        linea_serealizada = this->parser.line_to_bytes_parser(linea);
        for (uint8_t& elemento: linea_serealizada) {
            this->protocol.send_byte(elemento);
        }
        get_and_print_line();
    }
    archive.close();
}


void Client::get_and_print_line() {
    std::string buf = this->protocol.get_msg();
    std::cout << buf << std::endl;
}


Client::~Client() { this->protocol.~ClientProtocol(); }
