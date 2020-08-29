//
// Created by Trembles on 8/28/2020.
//
// The header functions to handle the server connections, validations, initializations, and requests
// Last updated 8/28/2020

#ifndef WEBSERVER_DATABASE_HANDLER_HPP
#define WEBSERVER_DATABASE_HANDLER_HPP

#include <string>
#include <algorithm>

namespace sfkg::database_handler {
    struct Uri {
    public:
        std::wstring Query_String, Path, Protocol, Host, Port;
    };

    auto Uri_Parse(std::wstring const &uri) -> Uri;
    auto Database_Available(sfkg::database_handler::Uri const &uri) -> bool;
    auto Database_Connect(sfkg::database_handler::Uri const &uri) -> bool;
}

#endif //WEBSERVER_DATABASE_HANDLER_HPP
