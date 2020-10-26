/****************************************************************************************
* Alexis Lopez
* Set.h
* 02/28/18
* This class is and implementation of a sets and its properties of copy, move,
* check if an elemnet exists, add or remove from the set, check if is empty and many more. 
* This lets the user to interact with sets and manipulate them, and one
* great adavantage is that is already sorted which is a nice touch.
****************************************************************************************/
#ifndef SET_H
#define SET_H

#include <ostream>
#include <cassert>
#include <iostream>

using namespace std;

template <typename Comparable> class Set_iterator;

template <typename Comparable>
class Set
{
public:
    typedef Set_iterator<Comparable> iterator;

    Set(): root{nullptr}, theSize{0} { }
    Set(const Set & rhs) { root = clone(rhs.root); theSize = rhs.theSize; }
    Set(Set && rhs);
    ~Set() { makeEmpty(root); }
    Set & operator=(const Set & rhs);
    Set & operator=(Set && rhs);

    const Comparable & findMin() const;
	const Comparable & findMax() const;
	bool contains(const Comparable & x) const { return contains(x, root); }
    unsigned int count(const Comparable & x) const;
    bool empty() const { return root == nullptr; }
    void printTree(ostream & out = cout) const;

    void clear() { makeEmpty(root); theSize = 0; }
    void insert(const Comparable & x) { insert(x, nullptr, root); } //iterator
    void insert(Comparable && x) { insert(move(x), nullptr, root); }
    void erase(const Comparable & x) { erase(x, root); }
    unsigned int size() const {return theSize; }

    iterator begin() const;
    iterator end() const { return iterator(nullptr); }
    iterator find(const Comparable & x) const { return find(x, root); }
	void remove(const Comparable & x) { remove(x, root); }
	void inorder() const { inorder(root); }
	void postorder() const { postorder(root); }
    void preorder() const { preorder(root); }
    void erase(Set<Comparable>::iterator itr);
	void makeEmpty() { makeEmpty(root); }

private:
    struct BinaryNode
    {
        Comparable element;
	BinaryNode * parent;
        BinaryNode * left;
        BinaryNode * right;

        BinaryNode(const Comparable & theElement, BinaryNode * p, BinaryNode * lt, BinaryNode * rt):
            element{theElement}, parent{p}, left{lt}, right{rt} { }
        BinaryNode(Comparable && theElement,BinaryNode * p, BinaryNode * lt, BinaryNode * rt):
            element{move(theElement)}, parent{p}, left{lt}, right{rt} { }
    };

    BinaryNode * root;
    unsigned int theSize = 0;

    void insert(const Comparable & x, BinaryNode * p, BinaryNode * & t);
    void insert(Comparable && x, BinaryNode * p, BinaryNode * & t);
    void erase(const Comparable & x, BinaryNode * & t);
    BinaryNode * findMin(BinaryNode * t) const;
	BinaryNode * findMax(BinaryNode * t) const;
	bool contains(const Comparable & x, BinaryNode * t) const;
    unsigned int count(const Comparable & x, BinaryNode * t) const;
    void makeEmpty(BinaryNode * & t);
    void printTree(ostream & out, BinaryNode * t, string indent, const string & tag) const;
    BinaryNode * clone(BinaryNode * t) const;
    iterator find(const Comparable & x, BinaryNode * t) const;
	void remove(const Comparable & x, BinaryNode * & t);
	void inorder(BinaryNode * t) const;
	void postorder(BinaryNode * t) const;
    void preorder(BinaryNode * t) const;

friend class Set_iterator<Comparable>;
};

template <typename Comparable>
typename Set<Comparable>::BinaryNode * Set<Comparable>::clone(BinaryNode * t) const
{
    if (t == nullptr)
        return nullptr;
    else {
        BinaryNode * temp = new BinaryNode{t->element, nullptr, clone(t->left), clone(t->right)};
        assert(temp);
	if(temp->left != nullptr)
	    temp->left->parent = temp;
	if(temp->right != nullptr)
	    temp->right->parent = temp;
        return temp;
    }
}

template <typename Comparable>
Set<Comparable>::Set(Set && rhs): root{rhs.root}, theSize{rhs.theSize}
{
    rhs.root = nullptr;
    rhs.theSize = 0;
}

template <typename Comparable>
void Set<Comparable>::makeEmpty(BinaryNode * & t)
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

template <typename Comparable>
Set<Comparable> & Set<Comparable>::operator=(const Set & rhs)
{
    Set copy = rhs;
    swap(*this, copy);
    return *this;
}

template <typename Comparable>
Set<Comparable> & Set<Comparable>::operator=(Set && rhs)
{
    root = rhs.root;
    rhs.root = nullptr;
    return *this;
}

template <typename Comparable>
const Comparable & Set<Comparable>::findMin() const
{
    BinaryNode * t = findMin(root);

    if (t == nullptr)
        return move(Comparable());

    return t->element;
}

template <typename Comparable>
const Comparable & Set<Comparable>::findMax() const
{
    BinaryNode * t = findMax(root);

    if (t == nullptr)
        return move(Comparable());

    return t->element;
}

template<typename Comparable>
void Set<Comparable>::erase(const Comparable & x, BinaryNode * & t)
{
    if(t == nullptr)
	return;

    if(x < t->element)
	erase(x, t->left);
    else if(t->element < x)
	erase(x, t->right);
    else if(t->left != nullptr && t->right != nullptr)
    {
	t->element = findMin(t->right)->element;
	erase(t->element, t->right);
    }
    else
    {
	BinaryNode * oldNode = t;
	BinaryNode * p = t->parent;
	t = (t->left != nullptr) ? t->left : t->right;
	if(t != nullptr)
	    t->parent = p;
	delete oldNode;
	theSize--;
    }
}

template <typename Comparable>
typename Set<Comparable>::BinaryNode * Set<Comparable>::findMin(BinaryNode * t) const
{
    if (t == nullptr)
        return nullptr;
    if (t->left == nullptr)
        return t;
    return findMin(t->left);
}

template <typename Comparable>
typename Set<Comparable>::BinaryNode * Set<Comparable>::findMax(BinaryNode * t) const
{
    if (t == nullptr)
        return nullptr;
    if (t->right == nullptr)
        return t;
    return findMax(t->right);
}

template <typename Comparable>
bool Set<Comparable>::contains(const Comparable & x, BinaryNode * t) const
{
    if(t == nullptr) {
		return false;
		
    } else if(x < t->element){
		return contains(x, t->left);
		
    } else if(t->element < x) {
		return contains(x, t->right);
		
    } else
		return true;
}

template<typename Comparable>
void Set<Comparable>::remove(const Comparable & x, BinaryNode * & t)
{
    if(t == nullptr) return;
	
    if(x < t->element) remove(x, t->left);
    else if(t->element < x) remove(x, t->right);
    else if(t->left != nullptr && t->right != nullptr) {
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
    } else {
		BinaryNode * oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
    }
}

//LNR
template <typename Comparable>
void Set<Comparable>::inorder(BinaryNode * t) const
{
    if (t == nullptr)
        return;

    inorder(t->left);
    cout << t->element << " ";
    inorder(t->right);
}

// LRN
template <typename Comparable>
void Set<Comparable>::preorder(BinaryNode * t) const
{
    if (t == nullptr)
        return;

    preorder(t->left);
    preorder(t->right);
    cout << t->element << " ";
}

//NLR
template <typename Comparable>
void Set<Comparable>::postorder(BinaryNode * t) const
{
    if (t == nullptr)
        return;

    cout << t->element << " ";
    postorder(t->left);
    postorder(t->right);
}

template <typename Comparable>
unsigned int Set<Comparable>::count(const Comparable & x, BinaryNode *t) const
{
    if(t == nullptr)
    {
	return 0;
    }
    else if(x < t->element)
    {
	return count(x, t->left);
    }
    else if(t->element < x)
    {
	return count(x, t->right);
    }
    else
	return 1;
}

template <typename Comparable>
void Set<Comparable>::printTree(ostream & out) const
{
    cout << "Print Tree\n";
    printTree(out, root, "", "");
}
template <typename Comparable>
unsigned int Set<Comparable>::count(const Comparable & x) const
{
    return count(x, root);
}

template <typename Comparable>
void Set<Comparable>::printTree(ostream & out, BinaryNode * t, string indent, const string & tag) const
{
    if (t == nullptr)
        return;

    out << indent << tag << t->element << endl;
    indent += "    ";
    printTree(out, t->left, indent, "L ");
    printTree(out, t->right, indent, "R ");
}

template <typename Comparable>
void Set<Comparable>::insert(const Comparable & x, BinaryNode * p, BinaryNode * & t)
{// typename Set<Comparable>::insert(const Comparable & x, BinaryNode * p, BinaryNode * & t)
    if (t == nullptr) {
        t = new BinaryNode{ x, p, nullptr, nullptr };
        assert(t);
		theSize++;
		//return t;
    } 
    else if (x < t->element)
        //return insert(x, t, t->left);
		insert(x, t, t->left);
    else if (x > t->element)
        //return insert(x, t, t->right);
	insert(x, t, t->right);
    else
        //return t;
		;
}

template <typename Comparable>
void Set<Comparable>::insert(Comparable && x, BinaryNode * p, BinaryNode * & t)
{// typename Set<Comparable>::iterator Set<Comparable>::insert(Comparable && x, BinaryNode * p, BinaryNode * & t)
    if (t == nullptr) 
    {
        t = new BinaryNode{ move(x), p, nullptr, nullptr };
        assert(t);
		theSize++;
		//return t;
    } 
    else if (x < t->element)
        // return insert(move(x), t, t->left);
		insert(move(x), t, t->left);
    else if (x > t->element)
        // return insert(move(x), t, t->right);
		insert(move(x), t, t->right);
    else
        //return t;
		;
}

template <typename Comparable>
class Set_iterator 
{
public:
    typedef typename Set<Comparable>::BinaryNode BinaryNode;

    Set_iterator() = default;
    Set_iterator(const Set_iterator & it) = default;
    Set_iterator(Set_iterator && it) = default;
    ~Set_iterator() = default;
    Set_iterator & operator=(const Set_iterator & itr) = default;
    Set_iterator & operator=(Set_iterator && itr) = default;

    Set_iterator(BinaryNode * t): current{t} {}
    bool operator==(Set_iterator itr) const { return current == itr.current; }
    bool operator!=(Set_iterator itr) const { return current != itr.current; }
    Set_iterator & operator++();
    Set_iterator operator++(int);
    Comparable & operator*() { return current->element; }

protected:
    BinaryNode * current;

friend class Set<Comparable>;
};

template <typename Comparable>
Set_iterator<Comparable> & Set_iterator<Comparable>::operator++()
{
    if (current->right) {
        current = current->right;
        while (current->left)
            current = current->left;
    } else {
        BinaryNode * child = current;
        current = current->parent;
        while (current && current->right == child) {
            child = current;
            current = current->parent;
        }
    }
    return *this;
}

template <typename Comparable>
Set_iterator<Comparable> Set_iterator<Comparable>::operator++(int)
{
    Set_iterator<Comparable> clone(*this);
    ++(*this);
    return clone;
}

template <typename Comparable>
typename Set<Comparable>::iterator Set<Comparable>::find(const Comparable & x, BinaryNode * t) const
{
    if(t == nullptr)
	return iterator{};
    else if(x < t->element)
	return find(x, t->left);
    else if(x > t->element)
	return find(x, t->right);
    else
	return iterator{t};
}

template <typename Comparable>
void Set<Comparable>::erase(Set<Comparable>::iterator itr)
{
    if(itr == end())
	return;
    
    BinaryNode * temp;
    if(itr.current->left != nullptr && itr.current->right != nullptr)
    {
        temp = itr.current->right;
	while(temp->left != nullptr)
	{
	    temp = temp->left;
	}
	itr.current->element = temp->element;
    }
    else
	temp = itr.current;

    BinaryNode * p = temp->parent;
    if(p != nullptr)
    {
	if(p->left == temp)
	    p->left = (temp->left != nullptr) ? temp->left : temp->right;
	else
	    p->right = (temp->left != nullptr) ? temp->left : temp->right;
    }
    if(temp->left != nullptr)
	temp->left->parent = p;
    else if(temp->right != nullptr)
	temp->right->parent = p;

    delete temp;
    theSize--;
}

template<typename Comparable>
typename Set<Comparable>::iterator Set<Comparable>::begin() const
{
    BinaryNode * current = root;
    while(current && current->left)
	current = current->left;
    
    return iterator(current);
}

#endif
