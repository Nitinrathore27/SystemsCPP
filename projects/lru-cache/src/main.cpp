#include <iostream>
#include <string>
#include "../include/LRUCache.h"

int main()
{
    LRUCache<int, int> cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    std::cout << cache.get(1).value_or(-1) << std::endl; // returns 1

    LRUCache<std::string, std::string> stringCache(3);
    stringCache.put("session_1", "user_data_A");

    return 0;
}
