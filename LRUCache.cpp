#include <unordered_map>
#include <list>
#include <iostream>

using namespace std;

class LRUCache
{
private:
    int capacity;
    list<pair<int, char>> cacheList;
    unordered_map<int, list<pair<int, char>>::iterator> cacheMap;

public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key)
    {
        // Implementation of get method
        if (cacheList.empty())
            return -1;
        int value = -1;
        if (cacheMap.find(key) != cacheMap.end())
        {
            value = cacheMap[key]->second;
            cacheList.erase(cacheMap[key]);
            cacheList.push_front({key, value});
            cacheMap[key] = cacheList.begin();
        }
        return value;
    }

    void put(int key, int value)
    {
        // Implementation of put method
        if (cacheMap.find(key) != cacheMap.end())
        {
            cacheList.erase(cacheMap[key]);
            cacheMap.erase(key);
        }
        else if (cacheList.size() == capacity)
        {
            int lastKey = cacheList.back().first;
            cacheList.pop_back();
            cacheMap.erase(lastKey);
        }
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
    }
};
int main()
{
    LRUCache cache(2); // Cache capacity of 2

    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl; // returns 1
    cache.put(3, 3);              // evicts key 2
    cout << cache.get(2) << endl; // returns -1 (not found)
    cache.put(4, 4);              // evicts key 1
    cout << cache.get(3) << endl; // returns 3 (not found)
    cout << cache.get(4) << endl; // returns 4

    return 0;
}