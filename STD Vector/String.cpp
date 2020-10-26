/***********************************************************************
Alexis Lopez
01/31/18
String.cpp

Implementation of constructors and member functions defined in String.h.
***********************************************************************/

#include <cassert>
#include "String.h"

//default constructor
String::String()
{
    size = 0;
    buffer = nullptr;
}

// copy constructor
String::String(const String & source)
{
    size = source.size;
    buffer = new char[size];
    assert(buffer != nullptr);

    for (int i = 0; i < size; i++)
        buffer[i] = source.buffer[i];
}

// move constructor
String::String(String && source): size{source.size}, buffer{source.buffer}
{
    source.size = 0;
    source.buffer = nullptr;
}

// constructor from "char string" to String
// find size of p, allocate space, assign p to buffer
String::String(const char * p)
{
    size = 0;
    for (const char *q = p; *q; q++)
        size++;
    buffer = new char[size];
    assert(buffer != nullptr);

    for (int i = 0; i < size; i++)
        buffer[i] = p[i];
}

String::String(char)
{

}

String::~String()
{
    delete [] buffer;
}

int String::length()
{
    return size;
}

char & String::operator[](const int i)
{
    return buffer[i];
}

// copy assignment
// similar to char string constructor, but here
// create a temp buffer based on source,
// delete existing buffer, then assign temp buffer to buffer
String & String::operator=(const String & source)
{
    char * temp = new char[source.size];
    assert(temp != nullptr);

    for (int i = 0; i < source.size; i++)
        temp[i] = source.buffer[i];

    delete [] buffer;
    buffer = temp;
    size = source.size;

    return *this;
}

// move assignment
String & String::operator=(String && source)
{
    size = source.size;
    source.size = 0;
    buffer = source.buffer;
    source.buffer = nullptr;
    return *this;
}

String & String::operator+=(const String  & arg)
{
    char * temp;
    int tempSize = size + arg.size;
    temp = new char[tempSize];
    int i;

    for (i = 0; i < size; i++)
    {
        temp[i] = buffer[i];
    }
    
    for(int p = 0; p < arg.size;p++, i++)
    {
        temp[i] = arg.buffer[p];
    }

    size = tempSize;
    delete [] buffer;
    buffer = temp;

    return * this;
}
bool operator==(const String & left, const String & right)
{
    if (left.size != right.size)
        return false;

    for (int i = 0; i < left.size; i++)
        if (left.buffer[i] != right.buffer[i])
            return false;
    return true;
}

bool operator<=(const String & left, const String & right)
{
    for (int i = 0; i < left.size & i < right.size; i++)
    {
        if (left.buffer[i] > right.buffer[i])
        {
            return false;
        }
    }
    return true;
}

bool operator<(const String & left, const String & right)
{
    for(int i = 0; i < left.size & i < right.size; i++)
    {
        if(left.size > right.size)
        {
            return false;
        }
    }

    for (int i = 0; i < left.size & i < right.size; i++)
    {
        if (left.buffer[i] > right.buffer[i])
        {
            return false;
        }
    }
    return true;
}

ostream & operator<<(ostream & out, const String & s)
{
    for (int i = 0; i < s.size; i++)
        out << s.buffer[i];
    return out;
}
