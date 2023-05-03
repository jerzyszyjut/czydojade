#pragma once
#include <cstring>
#define BLOCK_SIZE 16

class JString
{
public:
	JString();
	JString(const char* str);
	JString(const char* str, int start, int length);
	JString(const JString& other);
	~JString();

	JString& operator=(const JString& other);
	JString& operator=(JString&& other);
	JString& operator=(const char* str);
	bool operator==(const JString& other) const;
	bool operator==(const char* str) const;
	bool operator!=(const JString& other) const;
	bool operator!=(const char* str) const;
	char& operator[](int index);
	const char& operator[](int index) const;

	int length() const;
	const char* c_str() const;

private:
	char* m_str;
	int m_length;
};
