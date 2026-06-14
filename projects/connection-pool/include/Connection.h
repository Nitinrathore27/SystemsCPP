#pragma once
#include <iostream>
#include <string>

class Connection
{
private:
    int id;

public:
    Connection(int id) : id(id)
    {
        std::cout << "--> Connection " << id << " created.\n";
    }

    ~Connection()
    {
        std::cout << "--> Connection " << id << " destroyed.\n";
    }

    void executeQuery(const std::string &query)
    {
        std::cout << "[Conn " << id << "] Executing: " << query << "\n";
    }
};