//
// Created by Trembles on 8/28/2020.
//
// The source file for functions that handle the server connections, validations, initializations, and requests
// Last updated 9/2/2020

#include "database_handler.hpp"

auto sfkg::database_handler::Uri_Parse(std::wstring const &uri) -> Uri {
    using const_iter = std::wstring ::const_iterator;

    //TODO: create uri sanitization

    Uri result;

    if(uri.length() == 0) return result;

    const_iter uri_end = uri.end();
    // In URI and URL's after the '?' is where parameters are put in for GET, POST, PUT, etc
    const_iter query_start = std::find(uri.begin(), uri_end, L'?');

    // Protocol, i.e. http://, https://
    const_iter protocol_start = uri.begin();
    const_iter protocol_end = std::find(protocol_start, uri_end, L':');

    if(protocol_end != uri_end) {

        std::wstring prot = &*(protocol_end);

        if ((prot.length() > 3) && (prot.substr(0,3) == L"://")) {
            result.Protocol = std::wstring(protocol_start, protocol_end);
            protocol_end += 3;
        }
        else {
            // No protocol
            protocol_end = uri.begin();
        }
    }
    else {
        // No protocol
        protocol_end = uri.begin();
    }

    // Host
    const_iter host_start = protocol_end;
    // The start of the actual uri
    const_iter path_start = std::find(host_start, uri_end, L'/');

    const_iter host_end = std::find(protocol_end, (path_start != uri_end) ? path_start : query_start, L':');

    result.Host = std::wstring(host_start, host_end);

    // Port
    if((host_end != uri_end) && ((&*(host_end))[0] == L':')) {// checking for that :8080 in localhost:8080
        host_end++;
        const_iter port_end = (path_start != uri_end) ? path_start : query_start;
        result.Port = std::wstring(host_end, port_end);
    }

    // Path
    if(path_start != uri_end) {
        result.Path = std::wstring(path_start, query_start);
    }

    // Query
    if(query_start != uri_end) {
        result.Query_String = std::wstring(query_start, uri_end);
    }

    result.Connection_String = result.Protocol + result.Host + result.Path;

    if(result.Port.compare(L"") != 0) {
        result.Connection_String += result.Port;
    }


    return result;
}

auto Database_Available(std::string const dbname,
                        std::shared_ptr<pqxx::connection> conn) -> bool {
    if(!conn->is_open()) return false;

    std::string query = "Select datname From pg_catalog.pg_database WHERE lower(datname) = " + dbname;

    try {
        pqxx::work transact(*conn);
        pqxx::row row = transact.exec1(query);
    } catch(pqxx::unexpected_rows err) {
        return false;
    }

    return true;
}

auto Database_Connect(sfkg::database_handler::Uri const &uri) -> std::shared_ptr<pqxx::connection> {
    std::string conn_string(uri.Connection_String.begin(), uri.Connection_String.end());
    return std::make_shared<pqxx::connection>(conn_string);
}

auto Database_Init(std::string const dbname,
                   std::shared_ptr<pqxx::connection> conn) -> bool {
    if(!conn->is_open()) return false;

    std::string init_query = "CREATE TABLE " + dbname + " (ID INT PRIMARY KEY NOT NULL);";

    pqxx::work transact(*conn);
    transact.exec(init_query);
    return true;
}