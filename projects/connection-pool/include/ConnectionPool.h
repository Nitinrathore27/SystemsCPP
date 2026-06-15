#include <iostream>
#include <queue>
#include <memory>
#include "Connection.h"
#include <string>
class ConnectionPool
{
private:
    int poolSize;
    std::queue<std::unique_ptr<Connection>> availableConnections;

public:
    ConnectionPool(int size) : poolSize(size)
    {
        for (int i = 0; i < poolSize; ++i)
        {
            availableConnections.push(std::make_unique<Connection>(i + 1));
        }
    }
    std::unique_ptr<Connection> acquireConnection()
    {
        if (availableConnections.empty())
        {
            std::cout << "No available connections. Please wait.\n";
            return std::unique_ptr<Connection>{};;
        }
        auto conn = std::move(availableConnections.front());
        availableConnections.pop();
        return conn;
    }

    void releaseConnection(std::unique_ptr<Connection> conn)
    {
        availableConnections.push(std::move(conn));
    }
};