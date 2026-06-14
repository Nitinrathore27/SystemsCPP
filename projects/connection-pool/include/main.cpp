#include <iostream>
#include "ConnectionPool.h"
using namespace std::string_literals;
int main()
{
    ConnectionPool myPool(2);

    auto conn1 = myPool.acquireConnection();
    if (conn1)
        conn1->executeQuery("SELECT * FROM users;"s);

    auto conn2 = myPool.acquireConnection();
    if (conn2)
        conn2->executeQuery("INSERT INTO orders VALUES (1, 'Book');"s);
    return 0;
}