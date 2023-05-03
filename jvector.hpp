#pragma once
#define DEFAULT_CAPACITY_SIZE 4

template <typename T>
class JVector
{
public:
    JVector();
    JVector(const JVector<T>& other);
    JVector<T>& operator=(const JVector<T>& other);
    ~JVector();

    void push_back(const T& element);

    T& operator[](int index);
    const T& operator[](int index) const;

    int size() const;
    void set_size(int size);
    void resize(int size);

private:
    void copy(const JVector<T>& other);
    void deallocate();
    void resize();

    T* m_data;
    int m_size;
    int m_capacity;
};

template <typename T>
JVector<T>::JVector()
{
    m_data = new T[DEFAULT_CAPACITY_SIZE];
    m_size = 0;
    m_capacity = DEFAULT_CAPACITY_SIZE;
}

template <typename T>
JVector<T>::JVector(const JVector<T>& other)
{
    copy(other);
}

template <typename T>
JVector<T>& JVector<T>::operator=(const JVector<T>& other)
{
    if (this != &other)
    {
        deallocate();
        copy(other);
    }
    return *this;
}

template <typename T>
JVector<T>::~JVector()
{
    deallocate();
}

template <typename T>
void JVector<T>::push_back(const T& element)
{
    if (m_size == m_capacity)
    {
        resize();
    }
    m_data[m_size] = element;
    m_size++;
}

template <typename T>
T& JVector<T>::operator[](int index)
{
    return m_data[index];
}

template <typename T>
const T& JVector<T>::operator[](int index) const
{
    return m_data[index];
}

template <typename T>
int JVector<T>::size() const
{
    return m_size;
}

template <typename T>
void JVector<T>::set_size(int size)
{
    m_size = size;
}

template <typename T>
void JVector<T>::resize(int size)
{
    delete[] m_data;
    m_size = size;
    T* newData = new T[m_size];
    m_data = newData;
}

template <typename T>
void JVector<T>::copy(const JVector<T>& other)
{
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_data = new T[m_capacity];
    for (int i = 0; i < m_size; i++)
    {
        m_data[i] = other.m_data[i];
    }
}

template <typename T>
void JVector<T>::deallocate()
{
    delete[] m_data;
}

template <typename T>
void JVector<T>::resize()
{
    m_capacity = m_capacity == 0 ? DEFAULT_CAPACITY_SIZE : m_capacity * 2;
    T* newData = new T[m_capacity];
    for (int i = 0; i < m_size; i++)
    {
        newData[i] = m_data[i];
    }
    deallocate();
    m_data = newData;
}
