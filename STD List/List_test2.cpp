/****************************************************************************************
* Alexis Lopez
* List_test2.cpp
* 02/14/18
* This program test if List.h works
****************************************************************************************/

#include <iostream>
#include "List.h"

using namespace std;

int main()
{
    List<int> l;
 
    l.push_back(44);
    l.push_back(33); 
    l.push_back(11);  
    l.push_back(22);  // l = 44, 33, 11, 22
 
    List<int> m(l);
 
    List<int>::iterator itr(m.begin());
    for ( ; itr != m.end(); itr++)
        cout << *itr << " ";
    cout << "\n-----------\n";
 
    l.pop_back();
    m = l;
    for (itr = m.begin(); itr != m.end(); itr++)
         cout << *itr << " ";
    cout << "\n-----------\n";

    m.pop_front();
    for (itr = m.begin(); itr != m.end(); itr++)
         cout << *itr << " ";
    cout << "\n-----------\n";

    m.clear();
    for (itr = m.begin(); itr != m.end(); itr++)
         cout << *itr << " ";
    cout << endl;
}
