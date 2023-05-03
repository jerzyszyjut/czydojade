#pragma once
#define HASHMAP_SIZE 10000
#define HASHMAP_PRIME_MULTIPLIER 211
#include "City.hpp"
#include "jvector.hpp"

class JHashMap
{
public:
    struct Entry
    {
        JString key;
        City* value;
    };

    JHashMap();
    ~JHashMap();

    City* operator[](const JString& key);
    City* operator[](JString&& key);

    void insert(JString key, City* city);

private:
    JVector<JVector<Entry>> m_entries;
};

JHashMap::JHashMap()
{
    m_entries.resize(HASHMAP_SIZE);
}

JHashMap::~JHashMap()
{
}

City* JHashMap::operator[](const JString& key)
{
    int hash = 0;
    for (int i = 0; i < key.length(); i++)
    {
        hash = (hash * HASHMAP_PRIME_MULTIPLIER + key[i]) % HASHMAP_SIZE;
    }

    int index = 0;

    for (; index < m_entries[hash].size(); index++)
    {
        if (m_entries[hash][index].key == key)
        {
            break;
        }
    }

    if (index == m_entries[hash].size())
    {
        m_entries[hash].push_back({ key, nullptr });
    }

    return m_entries[hash][index].value;
}

City* JHashMap::operator[](JString&& key)
{
    int hash = 0;
    for (int i = 0; i < key.length(); i++)
    {
        hash = (hash * HASHMAP_PRIME_MULTIPLIER + key[i]) % HASHMAP_SIZE;
    }

    int index = 0;

    for (; index < m_entries[hash].size(); index++)
    {
        if (m_entries[hash][index].key == key)
        {
            break;
        }
    }

    if (index == m_entries[hash].size())
    {
        m_entries[hash].push_back({ key, nullptr });
    }

    return m_entries[hash][index].value;
}

void JHashMap::insert(JString key, City* city)
{
    int hash = 0;
    for (int i = 0; i < key.length(); i++)
    {
        hash = (hash * HASHMAP_PRIME_MULTIPLIER + key[i]) % HASHMAP_SIZE;
    }

    int index = 0;

    for (; index < m_entries[hash].size(); index++)
    {
        if (m_entries[hash][index].key == key)
        {
            break;
        }
    }

    if (index == m_entries[hash].size())
    {
        m_entries[hash].push_back({ key, city });
    }
    else
    {
        m_entries[hash][index].value = city;
    }
}
