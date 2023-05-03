#pragma once
#include "City.hpp"
#include "jvector.hpp"

class JPriorityQueue
{
public:
    JPriorityQueue();
    JPriorityQueue(const JPriorityQueue& other);
    JPriorityQueue& operator=(const JPriorityQueue& other);
    ~JPriorityQueue();

    void push(const City::CityEdge& element);
    void pop();
    City::CityEdge top();
    bool empty() const;

private:
    JVector<City::CityEdge> m_data;
};

JPriorityQueue::JPriorityQueue()
{
    m_data = JVector<City::CityEdge>();
}

JPriorityQueue::JPriorityQueue(const JPriorityQueue& other)
{
    m_data = other.m_data;
}

JPriorityQueue& JPriorityQueue::operator=(const JPriorityQueue& other)
{
    if (this != &other)
    {
        m_data = other.m_data;
    }
    return *this;
}

JPriorityQueue::~JPriorityQueue()
{
}

void JPriorityQueue::push(const City::CityEdge& element)
{
    m_data.push_back(element);
    int index = m_data.size() - 1;
    while (index > 0)
    {
        int parentIndex = (index - 1) / 2;
        if (m_data[parentIndex].distance > m_data[index].distance)
        {
            City::CityEdge temp = m_data[parentIndex];
            m_data[parentIndex] = m_data[index];
            m_data[index] = temp;
            index = parentIndex;
        }
        else
        {
            break;
        }
    }
}

void JPriorityQueue::pop()
{
    m_data[0] = m_data[m_data.size() - 1];
    m_data.set_size(m_data.size() - 1);
    int index = 0;
    while (index < m_data.size())
    {
        int leftChildIndex = 2 * index + 1;
        int rightChildIndex = 2 * index + 2;
        if (leftChildIndex >= m_data.size())
        {
            break;
        }
        int minIndex = index;
        if (m_data[leftChildIndex].distance < m_data[minIndex].distance)
        {
            minIndex = leftChildIndex;
        }
        if (rightChildIndex < m_data.size() && m_data[rightChildIndex].distance < m_data[minIndex].distance)
        {
            minIndex = rightChildIndex;
        }
        if (minIndex != index)
        {
            City::CityEdge temp = m_data[minIndex];
            m_data[minIndex] = m_data[index];
            m_data[index] = temp;
            index = minIndex;
        }
        else
        {
            break;
        }
    }
}

City::CityEdge JPriorityQueue::top()
{
    return m_data[0];
}

bool JPriorityQueue::empty() const
{
    return m_data.size() == 0;
}
