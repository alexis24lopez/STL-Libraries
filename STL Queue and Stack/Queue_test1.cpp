/*****************************************************************************
* Alexis Lopez
* Queue_test1.cpp
* This program is to test Queue.h
******************************************************************************/
#include <iostream>

#include "Vector.h"
#include "Queue.h"

main()
{
    Queue<int> s; // uses List as the default container
    s.push(5);
    s.push(6);
    std::cout << s.front() << std::endl;

    Queue<double, Vector> v; // uses Vector as the container
    v.push(1.5);
    v.push(2.3);
    v.pop();
    std::cout << v.front() << std::endl;
}
