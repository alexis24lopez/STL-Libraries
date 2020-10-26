/*************************************************************************************
* Alexis Lopez
* Priority_queue.h
* 03/19/18
* This implementation keeps the largest number on the top for easy access. It checks
* if is empty, size, and adds and deletes from the Priority_queue.
*************************************************************************************/

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>

using namespace std;

template <class T> 
class Priority_queue {
public:
    bool empty() { return c.empty(); }
    unsigned int size() { return c.size(); }
    void push(const T & x);
    void push(T && x);
    void pop();
    T & top() { return c.front(); }
    const T & top() const { return c.front(); }

private:
    vector<T> c;
};

template<typename T>
void Priority_queue<T>::push(const T & x)
{
    c.push_back(x);

    unsigned n = c.size() -1;
    unsigned parent = (n-1)/2;

    while(n > 0 and c[parent] < c[n])
    {
	swap(c[n], c[parent]);
	n = parent;
	parent = (n-1)/2;
    }
}

template<typename T>
void Priority_queue<T>::push(T && x)
{
    c.push_back(move(x));

    unsigned n = c.size() -1;
    unsigned parent = (n-1)/2;

    while(n > 0 and c[parent] < c[n])
    {
	swap(c[n], c[parent]);
	n = parent;
	parent = (n-1)/2;
    }
}

template<typename T>
void Priority_queue<T>::pop()
{
    if(empty())
	return;

    c[0] = c.back();
    c.pop_back();

    unsigned n = 0;
    unsigned leftChild = 1;
    unsigned rightChild = 2;

    while(leftChild < c.size())
    {
	unsigned biggest_child = leftChild;

	if(rightChild < c.size() && c[leftChild] < c[rightChild])
	    biggest_child = rightChild;
	if(c[n] < c[biggest_child])
	{
	    swap(c[n], c[biggest_child]);
	    n = biggest_child;
	    leftChild = 2*n + 1;
	    rightChild = leftChild + 1;
	}
	else
	    break;
    }
}

#endif
