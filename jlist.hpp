#pragma once

template <typename T>
class JList
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
    };

public:
    JList();
    JList(JList& other);
    JList(JList&& other);
    ~JList();

    void push_front(T data);
    void push_back(T data);
    void pop_front();
    void pop_back();
    T& front();
    T& back();
    bool empty() const;

    JList& operator=(JList& other);

    class iterator
    {
    public:
        iterator();
        iterator(Node* node);
        ~iterator();

        iterator& operator++();
        iterator operator++(int);
        T& operator*();
        T* operator->();
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;

    private:
        Node* m_node;
    };

    iterator begin();
    iterator end();

private:
    Node* m_head;
    Node* m_tail;
    int m_size;
};

template <typename T>
JList<T>::JList()
{
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

template <typename T>
JList<T>::JList(JList& other)
{
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
    for (iterator it = other.begin(); it != other.end(); ++it)
    {
        push_front(*it);
    }
}

template <typename T>
JList<T>::JList(JList&& other)
{
    m_head = other.m_head;
    m_tail = other.m_tail;
    m_size = other.m_size;
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;
}

template <typename T>
JList<T>::~JList()
{
    Node* node = m_head;
    while (node != nullptr)
    {
        Node* next = node->next;
        delete node;
        node = next;
    }
}

template <typename T>
void JList<T>::push_front(T data)
{
    Node* node = new Node();
    node->data = data;
    node->next = m_head;
    node->prev = nullptr;
    if (m_head != nullptr)
    {
        m_head->prev = node;
    }
    m_head = node;
    if (m_tail == nullptr)
    {
        m_tail = node;
    }
    m_size++;
}

template <typename T>
void JList<T>::push_back(T data)
{
    Node* node = new Node();
    node->data = data;
    node->next = nullptr;
    node->prev = m_tail;
    if (m_tail != nullptr)
    {
        m_tail->next = node;
    }
    m_tail = node;
    if (m_head == nullptr)
    {
        m_head = node;
    }
    m_size++;
}

template <typename T>
void JList<T>::pop_front()
{
    if (m_head == nullptr)
    {
        return;
    }
    else if (m_head == m_tail)
    {
        delete m_head;
        m_head = nullptr;
        m_tail = nullptr;
        m_size--;
    }
    else
    {
        Node* node = m_head;
        m_head = m_head->next;
        m_head->prev = nullptr;
        delete node;
        m_size--;
    }
}

template <typename T>
void JList<T>::pop_back()
{
    if (m_tail == nullptr)
    {
        return;
    }
    else if (m_tail == m_head)
    {
        delete m_tail;
        m_tail = nullptr;
        m_head = nullptr;
        m_size--;
    }
    else
    {
        Node* node = m_tail;
        m_tail = m_tail->prev;
        m_tail->next = nullptr;
        delete node;
        m_size--;
    }
}

template <typename T>
T& JList<T>::front()
{
    return m_head->data;
}

template <typename T>
T& JList<T>::back()
{
    return m_tail->data;
}

template <typename T>
bool JList<T>::empty() const
{
    return m_size == 0;
}

template <typename T>
JList<T>& JList<T>::operator=(JList& other)
{
    if (this != &other)
    {
        Node* node = m_head;
        while (node != nullptr)
        {
            Node* next = node->next;
            delete node;
            node = next;
        }

        m_head = nullptr;
        m_tail = nullptr;
        m_size = 0;
        for (iterator it = other.begin(); it != other.end(); ++it)
        {
            push_front(*it);
        }
    }
    return *this;
}

template <typename T>
typename JList<T>::iterator JList<T>::begin()
{
    return iterator(m_head);
}

template <typename T>
typename JList<T>::iterator JList<T>::end()
{
    return iterator(nullptr);
}

template <typename T>
JList<T>::iterator::iterator()
{
    m_node = nullptr;
}

template <typename T>
JList<T>::iterator::iterator(Node* node)
{
    m_node = node;
}

template <typename T>
JList<T>::iterator::~iterator()
{
}

template <typename T>
typename JList<T>::iterator& JList<T>::iterator::operator++()
{
    m_node = m_node->next;
    return *this;
}

template <typename T>
typename JList<T>::iterator JList<T>::iterator::operator++(int)
{
    iterator temp = *this;
    m_node = m_node->next;
    return temp;
}

template <typename T>
T* JList<T>::iterator::operator->()
{
    return &(m_node->data);
}

template <typename T>
T& JList<T>::iterator::operator*()
{
    return m_node->data;
}

template <typename T>
bool JList<T>::iterator::operator==(const iterator& other) const
{
    return m_node == other.m_node;
}

template <typename T>
bool JList<T>::iterator::operator!=(const iterator& other) const
{
    return m_node != other.m_node;
}
