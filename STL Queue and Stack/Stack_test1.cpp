/*****************************************************************************
* Alexis Lopez
* Stack_test1.cpp
* This program is to test Stack.h
******************************************************************************/
#include <iostream>

#include "Vector.h"
#include "Stack.h"

main()
{
    Stack<int> s; // uses List as the default container
    s.push(5);
    s.push(6);
    std::cout << s.top() << std::endl;

    Stack<double, Vector> v; // uses Vector as the container
    v.push(1.5);
    v.push(2.3);
    v.pop();
    std::cout << v.top() << std::endl;
}
