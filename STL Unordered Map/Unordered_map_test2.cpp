/****************************************************************************************
* Alexis Lopez
* Unordered_map.h
* 03/07/18
* this test Unordered_map_test2.cpp
****************************************************************************************/

#include <iostream>

#include "Unordered_map.h"

using namespace std;

int main()
{
    Unordered_map<string, string> h(7);

    h.insert(make_pair("Red", "123 Main"));
    h.insert(make_pair("Brown", "45 First"));
    h.insert(make_pair("Blue", "20 2nd St"));
    h["Jack"] = "500 E St";
    h["Jill"] = "400 Lakewood";
    h["Jake"] = "2 Sierra Madre";
    h["Green"] = "Mile";
    h["One more"] = "Something";

    Unordered_map<string, string>::iterator i;
    for (i = h.begin(); i != h.end(); i++)
        cout << (*i).first << ":" << (*i).second << endl;

    cout << "\nErase Jack\n";
    h.erase("Jack");

    cout << "\nFind Green\n";
    i = h.find("Green");
    if (i != h.end())
        cout << *i << endl;
    else
        cout << "Green not found\n";

    cout << "\nFind NotThere\n";
    i = h.find("NotThere");
    if (i != h.end())
        cout << *i << endl;
    else
        cout << "NotThere not found\n\n";

    for (i = h.begin(); i != h.end(); i++)
        cout << i->first << ":" << i->second << endl;
}
