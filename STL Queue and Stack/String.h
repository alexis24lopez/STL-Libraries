#ifndef STRING_H
#define STRING_H

/********************************************************************************************
Alexis Lopez
01/31/18
String.h

String class definition
*********************************************************************************************/

#include <iostream>

using namespace std;

class String
{
    int size;
    char * buffer;
public:
    String();               // default constructor
    String(const String &); // copy constructor
    String(String &&);      // move constructor
    String(const char *);
    String(char);
    ~String();              // destructor

    int length();
    char & operator[](const int);
    String & operator=(const String &); //copy assignment
    String & operator=(String &&);      //move assignment
    String & operator+=(const String &);

    friend bool operator==(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator<(const String &, const String &);

    friend ostream & operator<<(ostream &, const String &);
};

#endif
