#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <unordered_map>
#include <list>
#include <utility>
#include <optional>

template <typename Key, typename Value>
class LRUCache
{
private:
    size_t capacity;

    std::list<std::pair<Key, Value>> cacheList;

    std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> cacheMap;

public:
    LRUCache(size_t capacity) : capacity(capacity) {}

    std::optional<Value> get(const Key &key)
    {
        auto it = cacheMap.find(key);
        if (it == cacheMap.end())
        {
            return std::nullopt; // Key not found
        }

        // Move node to front (splice is O(1) and doesn't destroy/recreate nodes)
        cacheList.splice(cacheList.begin(), cacheList, it->second);
        return it->second->second;
    }

    void put(const Key &key, const Value &value)
    {
        if (capacity == 0)
            return;

        auto it = cacheMap.find(key);
        if (it != cacheMap.end())
        {
            // Key exists: update value and move to front
            it->second->second = value;
            cacheList.splice(cacheList.begin(), cacheList, it->second);
            return;
        }

        // Key doesn't exist: check capacity
        if (static_cast<size_t>(cacheList.size()) >= capacity)
        {
            Key oldestKey = cacheList.back().first;
            cacheList.pop_back();
            cacheMap.erase(oldestKey);
        }

        // Insert new element
        cacheList.push_front({key, value});
        cacheMap[key] = cacheList.begin();
    }
};

#endif
