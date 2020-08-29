//
// Created by Trembles on 8/28/2020.
//
// The header functions to handle the server connections, validations, initializations, and requests
// Last updated 8/28/2020

#ifndef WEBSERVER_DATABASE_HANDLER_H
#define WEBSERVER_DATABASE_HANDLER_H

#include <string>

namespace sfkg::database_handler {
    struct Uri {
    public:
        std::wstring Query_String, Path, Protocol, Host, Port;

        static auto Uri::Parse(const std::wstring &uri) -> Uri;

        auto Database_Available(const sfkg::database_handler::Uri &uri) -> bool;

        
    };
}

#endif //WEBSERVER_DATABASE_HANDLER_H
