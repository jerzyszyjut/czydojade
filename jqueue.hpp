#pragma once
#include "jlist.hpp"

template <typename T>
class JQueue
{
public:
    JQueue();
    JQueue(const JQueue& other);
    JQueue& operator=(const JQueue& other);
    ~JQueue();

    void push(const T& element);
    void pop();
    T front();
    bool empty() const;

private:
    JList<T>* m_data;
};

template <typename T>
JQueue<T>::JQueue()
{
    m_data = new JList<T>();
}

template <typename T>
JQueue<T>::JQueue(const JQueue& other)
{
    m_data = other.m_data;
}

template <typename T>
JQueue<T>& JQueue<T>::operator=(const JQueue& other)
{
    if (this != &other)
    {
        m_data = other.m_data;
    }
    return *this;
}

template <typename T>
JQueue<T>::~JQueue()
{
    delete m_data;
}

template <typename T>
void JQueue<T>::push(const T& element)
{
    m_data->push_back(element);
}

template <typename T>
void JQueue<T>::pop()
{
    m_data->pop_front();
}

template <typename T>
T JQueue<T>::front()
{
    return m_data->front();
}

template <typename T>
bool JQueue<T>::empty() const
{
    return m_data->empty();
}
