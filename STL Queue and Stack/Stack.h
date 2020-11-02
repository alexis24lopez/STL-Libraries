#ifndef STACK_H
#define STACK_H
/*****************************************************************************
* Alexis Lopez
* Stack.h  -- a stack implemented as an adapter (of vector or list or ...)
* This program allows the user to use Stacks and to check if is empty
* the size, and to add element from the top and remove from top. 
******************************************************************************/

#include "List.h"

using namespace std;

//Use the following line for STL containers.
//template <class T, template <class S, class = allocator<S> > class Container = list>
template <class T, template <class S> class Container = List>
class Stack
{
public:
   bool empty() const {return container.empty(); }
   unsigned int size() const {return container.size(); }
   void push(const T & x) {return container.push_back(x); }
   void push(T && x) {return container.push_back(move(x)); }
   void pop() {return container.pop_back(); }
   T & top() {return container.back(); }

private:
   Container<T> container;
};

#endif
