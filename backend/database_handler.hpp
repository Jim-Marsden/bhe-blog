//
// Created by Trembles on 8/28/2020.
//
// The header functions to handle the server connections, validations, initializations, and requests
// Last updated 8/28/2020

#ifndef WEBSERVER_DATABASE_HANDLER_HPP
#define WEBSERVER_DATABASE_HANDLER_HPP

#include <utility>
#include <vector>

#include <string>
#include <algorithm>

#include <pqxx/pqxx>

namespace sfkg::database_handler {
    struct Uri {
    public:
        std::wstring Query_String, Path, Protocol, Host, Port, Connection_String;
    };

    auto Uri_Parse(std::wstring const &uri) -> Uri;
    auto Database_Available(std::string const dbname,
                            std::shared_ptr<pqxx::connection> conn) -> bool;
    auto Database_Connect(sfkg::database_handler::Uri const &uri) -> std::shared_ptr<pqxx::connection>;
    auto Database_Init(std::string const dbname,
                       std::shared_ptr<pqxx::connection> conn);

    enum class Sql_Command {
        ALTER_TABLE,
        AND,
        AS,
        AVG,
        BETWEEN,
        CASE,
        COUNT,
        CREATE_TABLE,
        DELETE,
        GROUP_BY,
        HAVING,
        INNER_JOIN,
        INSERT,
        IS_NULL,
        IS_NOT_NULL,
        LIKE,
        LIMIT,
        MAX,
        MIN,
        OR,
        ORDER_BY,
        OUTER_JOIN,
        ROUND,
        SELECT,
        SELECT_DISTINCT,
        SUM,
        UPDATE,
        WHERE,
        WITH
    };
}

#endif //WEBSERVER_DATABASE_HANDLER_HPP
