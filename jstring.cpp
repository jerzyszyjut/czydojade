#define _CRT_SECURE_NO_WARNINGS
#include "jstring.hpp"

JString::JString()
{
    m_str = new char[1];
    m_str[0] = '\0';
    m_length = 0;
}

JString::JString(const char* str)
{
    m_length = strlen(str);
    m_str = new char[m_length + 1];
    strcpy(m_str, str);
    m_str[m_length] = '\0';
}

JString::JString(const char* str, int start, int length)
{
    m_length = length;
    m_str = new char[m_length + 1];
    strncpy(m_str, str + start, length);
    m_str[m_length] = '\0';
}

JString::JString(const JString& other)
{
    m_length = other.m_length;
    m_str = new char[m_length + 1];
    strcpy(m_str, other.m_str);
    m_str[m_length] = '\0';
}

JString::~JString()
{
    delete[] m_str;
}

JString& JString::operator=(const JString& other)
{
    if (this != &other)
    {
        delete[] m_str;
        m_length = other.m_length;
        m_str = new char[m_length + 1];
        strcpy(m_str, other.m_str);
        m_str[m_length] = '\0';
    }
    return *this;
}

JString& JString::operator=(JString&& other)
{
    if (this != &other)
    {
        delete[] m_str;
        m_str = other.m_str;
        m_length = other.m_length;
        other.m_str = nullptr;
        other.m_length = 0;
    }
    return *this;
}

JString& JString::operator=(const char* str)
{
    delete[] m_str;
    m_length = strlen(str);
    m_str = new char[m_length + 1];
    strcpy(m_str, str);
    m_str[m_length] = '\0';
    return *this;
}

bool JString::operator==(const JString& other) const
{
    return strcmp(m_str, other.c_str()) == 0;
}

bool JString::operator==(const char* str) const
{
    return strcmp(m_str, str) == 0;
}

bool JString::operator!=(const JString& other) const
{
    return !(*this == other);
}

bool JString::operator!=(const char* str) const
{
    return !(*this == str);
}

char& JString::operator[](int index)
{
    return m_str[index];
}

const char& JString::operator[](int index) const
{
    return m_str[index];
}

int JString::length() const
{
    return m_length;
}

const char* JString::c_str() const
{
    return m_str;
}
