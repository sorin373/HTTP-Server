#pragma once

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>

#define MAX_SCHEMA_L 32

namespace ws_app
{
    namespace __detail
    {
        class my_sql_handler
        {
        public:
             my_sql_handler() noexcept 
                : m_connection(nullptr), m_driver(nullptr), m_schema() { }

            explicit my_sql_handler(char *connection_name, char *username, char *password, char *schema)
                : m_connection(nullptr), m_driver(nullptr), m_schema()
            {
                if (this->mysql_easy_init(connection_name, username, password, schema) == -1)
                    throw std::runtime_error("Failed to connect to the databse!\n");
            }

            int mysql_easy_init(const char *connection_name, const char *username, const char *password, const char *schema);

            sql::ResultSet *send_query(const std::string &query);

            ~my_sql_handler() 
            { 
                if (this->m_connection != nullptr)
                {
                    this->m_connection->close();
                    delete this->m_connection;

                    this->m_connection = nullptr;
                }
            }

            sql::Driver* driver() const noexcept 
            { return this->m_driver; }

            sql::Connection* connection() const noexcept 
            { return this->m_connection; }

        private:
            sql::Connection  *m_connection;
            sql::Driver      *m_driver;
            char              m_schema[MAX_SCHEMA_L];
        };
    }

    using MySQL_Handle = __detail::my_sql_handler;
}   