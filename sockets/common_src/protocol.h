#ifndef COMMON_PROTOCOLO_H
#define COMMON_PROTOCOLO_H

#include <string>

#include "common_socket.h"


// Mas adelante va a convenir tener un protocolo para el server y otro para el cliente
// (en el caso de que haya metodos compartidos, lo que podes hacer es tener un ProtocolCommon que
// tenga los metodos en comun y tener otras dos clases (ProtocolServer y ProtocolClient) que hereden
// de ella)
class Protocol {
protected:
    const std::string hostname;
    const std::string servname;
    Socket socket;  // cuando usemos threads el owner de este socket sera el server probablemente
    bool was_closed = false;

public:
    // Constructor para el cliente
    Protocol(const std::string& host, const std::string& service);

    // Constructor para el server
    explicit Protocol(Socket peer);

    bool is_close();

    ~Protocol();
};


class ClientProtocol: public Protocol {
public:
    using Protocol::Protocol;

    ClientProtocol(const std::string& host, const std::string& service);

    // envia un byte desde el cliente al server
    void send_byte(uint8_t& msg);

    // el cliente recibe desde el server (el largo del mensaje (2 bytes) y luego el mensaje)
    std::string get_msg();
};


class ServerProtocol: public Protocol {
public:
    using Protocol::Protocol;

    explicit ServerProtocol(Socket peer);

    // el server recibe un byte del cliente
    uint8_t get_byte();

    // envia un mensaje desde el server al cliente (envia el largo del mensaje (2 bytes) y luego el
    // mensaje)
    void send_msg(const std::string& msg);
};


#endif
