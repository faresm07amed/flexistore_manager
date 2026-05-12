#ifndef MYSQL_JDBC_PROXY_H
#define MYSQL_JDBC_PROXY_H

// Proxy header to support #include <mysql/jdbc.h> on Windows
// Maps to the standard MySQL Connector C++ 8.0 JDBC headers.
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#endif // MYSQL_JDBC_PROXY_H
