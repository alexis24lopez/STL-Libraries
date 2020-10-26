/*****************************************************************************
* Alexis Lopez
* Queue_test2.cpp
* This program is to test Queue.h
******************************************************************************/
#include <iostream>
#include <cassert>
#include "Queue.h"
#include "String.h"
#include "Vector.h"
#include "List.h"

int main()
{
   Queue<int, Vector> s1;
   assert(s1.size() == 0);
   assert(s1.empty());

   s1.push(16);
   assert(s1.size() == 1);
   assert(s1.front() == 16);

   s1.pop();
   assert(s1.size() == 0);

   s1.push(11);
   assert(s1.size() == 1);
   assert(s1.front() == 11);

   s1.push(22);
   assert(s1.size() == 2);
   assert(s1.back() == 22);

   s1.push(33);
   assert(s1.size() == 3);
   assert(s1.back() == 33);

   s1.pop();
   assert(s1.size() == 2);
   assert(s1.back() == 22);

   Queue<String, List> s2;
   s2.push("abc");
   s2.push("de");
   s2.pop();
   assert(s2.back() == "abc");

   std::cout << "SUCCESS\n";
}

