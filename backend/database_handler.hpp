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
    /**
     * The different segments of the URI
     */
    struct Uri {
    public:
        std::wstring Query_String, Path, Protocol, Host, Port, Connection_String;
    };

    /**
     * Creates a URI struct from a passed in wstring
     * @param uri wstring
     * @return Uri
     */
    auto Uri_Parse(std::wstring const &uri) -> Uri;

    /**
     * Given a connection object and database table name,
     * Tests if the table exists
     * @param dbname string
     * @param conn shared_ptr<pqxx::connection>
     * @return if the database table exists
     */
    auto Database_Available(std::string const dbname,
                            std::shared_ptr<pqxx::connection> conn) -> bool;

    /**
     * Given a URI, attempts to make and return a connection object to the given database
     * @param uri Uri
     * @return shared_ptr<pqxx::connection>
     */
    auto Database_Connect(sfkg::database_handler::Uri const &uri) -> std::shared_ptr<pqxx::connection>;

    /**
     * Using a provided conneciton object:
     * Attempts to create a database table with the given table name
     * @param dbname string
     * @param conn shared_ptr<pqxx::connection>
     * @return if the creation request was made
     */
    auto Database_Init(std::string const dbname,
                       std::shared_ptr<pqxx::connection> conn) -> bool;

    /**
     * Each Command Keyword in SQL as a Enum
     */
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
