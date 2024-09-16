#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>


class Parser {
public:
    Parser();
    // server methods
    // recive un byte y devuelve un su numero de comando en string
    std::string byte_to_string(uint8_t byte);


    // client methods
    std::vector<uint8_t> line_to_bytes_parser(const std::string& line);

    ~Parser();
};

#endif
