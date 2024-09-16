#ifndef CLIENTE_H
#define CLIENTE_H
#include <string>
#include <vector>

#include "../common_src/common_socket.h"
#include "../common_src/parser.h"
#include "../common_src/protocol.h"


class Client {
private:
    ClientProtocol protocol;
    Parser parser;

    // recibe una linea del servidor y la imprime
    void get_and_print_line();

public:
    Client(const std::string& host, const std::string& service);

    // Lee de entrada estandar, procesa la linea, envia informacion al servidor y recibe e imprime
    // la respuesta
    void run();

    // Lee de archivo input, procesa la linea, envia informacion al servidor y recibe e imprime la
    // respuesta
    void run_from_input(const char* input);

    ~Client();
};

#endif
