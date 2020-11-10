/****************************************************************************************
* Alexis Lopez
* BinarySearchTree.h
* 02/28/18
* This class is and implementation of a Binary search tree and its properties of copy, move,
* check if an elemnet exists, add or remove from the tree, check if is empty and many more. 
* This lets the user to interact with binary serach tree and manipulate them, and one
* great adavantage is that is already sorted which is a nice touch.
****************************************************************************************/
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <ostream>
#include <cassert>
#include <iostream>

using namespace std;

// Binary Search Tree, no duplicate elements

template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree(): root{nullptr} { }
    BinarySearchTree(const BinarySearchTree & rhs) { root = clone(rhs.root); }
    BinarySearchTree(BinarySearchTree && rhs);
    ~BinarySearchTree() { makeEmpty(root); }
    BinarySearchTree & operator=(const BinarySearchTree & rhs);
    BinarySearchTree & operator=(BinarySearchTree && rhs);

    const Comparable & findMin() const;
    const Comparable & findMax() const;
    bool contains(const Comparable & x) const { return contains(x, root); }
    bool isEmpty() const { return root == nullptr; }
    void printTree(ostream & out = cout) const;

    void makeEmpty() { makeEmpty(root); }
    void insert(const Comparable & x) { insert(x, root); }
    void insert(Comparable && x) { insert(move(x), root); }
    void remove(const Comparable & x) { remove(x, root); }
    void inorder() const { inorder(root); }
    void postorder() const { postorder(root); }
    void preorder() const { preorder(root); }

private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode * left;
        BinaryNode * right;

        BinaryNode(const Comparable & theElement, BinaryNode * lt, BinaryNode * rt):
            element{theElement}, left{lt}, right{rt} { }
        BinaryNode(Comparable && theElement, BinaryNode * lt, BinaryNode * rt):
            element{move(theElement)}, left{lt}, right{rt} { }
    };

    BinaryNode * root;

    void insert(const Comparable & x, BinaryNode * & t);
    void insert(Comparable && x, BinaryNode * & t);
    void remove(const Comparable & x, BinaryNode * & t);
    BinaryNode * findMin(BinaryNode * t) const;
    BinaryNode * findMax(BinaryNode * t) const;
    bool contains(const Comparable & x, BinaryNode * t) const;
    void makeEmpty(BinaryNode * & t);
    void printTree(ostream & out, BinaryNode * t, string indent, const string & tag) const;
    BinaryNode * clone(BinaryNode * t) const;
    void inorder(BinaryNode * t) const;
    void postorder(BinaryNode * t) const;
    void preorder(BinaryNode * t) const;
};

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::clone(BinaryNode * t) const
{
    if (t == nullptr)
        return nullptr;
    else {
        BinaryNode * newNode = new BinaryNode{t->element, clone(t->left), clone(t->right)};
        assert(newNode);
        return newNode;
    }
}

template <typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(BinarySearchTree && rhs)
{
    root = rhs.root;
    rhs.root = nullptr;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode * & t)
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
BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator=(const BinarySearchTree & rhs)
{
    BinarySearchTree copy = rhs;
    swap(*this, copy);
    return *this;
}

template <typename Comparable>
BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator=(BinarySearchTree && rhs)
{
    root = rhs.root;
    rhs.root = nullptr;
    return *this;
}

template <typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin() const
{
    BinaryNode * t = findMin(root);

    if (t == nullptr)
        return move(Comparable());

    return t->element;
}

template <typename Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax() const
{
    BinaryNode * t = findMax(root);

    if (t == nullptr)
        return move(Comparable());

    return t->element;
}

template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable & x, BinaryNode * & t)
{
    if(t == nullptr)
	return;
    if(x < t->element)
	remove(x, t->left);
    else if(t->element < x)
	remove(x, t->right);
    else if(t->left != nullptr && t->right != nullptr)
    {
	t->element = findMin(t->right)->element;
	remove(t->element, t->right);
    }
    else
    {
	BinaryNode * oldNode = t;
	t = (t->left != nullptr) ? t->left : t->right;
	delete oldNode;
    }
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::findMin(BinaryNode * t) const
{
    if (t == nullptr)
        return nullptr;
    if (t->left == nullptr)
        return t;
    return findMin(t->left);
}

template <typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode * BinarySearchTree<Comparable>::findMax(BinaryNode * t) const
{
    if(t != nullptr)
    {
	while(t->right != nullptr)
	{
	    t = t->right;
	}
	return t;
    }
}

template <typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable & x, BinaryNode *t) const
{
    if(t == nullptr)
    {
	return false;
    }
    else if(x < t->element)
    {
	return contains(x, t->left);
    }
    else if(t->element < x)
    {
	return contains(x, t->right);
    }
    else
	return true;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::printTree(ostream & out) const
{
    cout << "Print Tree\n";
    printTree(out, root, "", "");
}

template <typename Comparable>
void BinarySearchTree<Comparable>::printTree(ostream & out, BinaryNode * t, string indent, const string & tag) const
{
    if (t == nullptr)
        return;

    out << indent << tag << t->element << endl;
    indent += "    ";
    printTree(out, t->left, indent, "L ");
    printTree(out, t->right, indent, "R ");
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable & x, BinaryNode * & t)
{
    if (t == nullptr) 
    {
        t = new BinaryNode{ x, nullptr, nullptr };
        assert(t);
    } else if (x < t->element)
        insert(x, t->left);
    else if (x > t->element)
        insert(x, t->right);
    else
        ;
}

template <typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable && x, BinaryNode * & t)
{
    if (t == nullptr) 
    {
        t = new BinaryNode{ move(x), nullptr, nullptr };
        assert(t);
    } else if (x < t->element)
        insert(move(x), t->left);
    else if (x > t->element)
        insert(move(x), t->right);
    else
        ;
}

// LRN
template <typename Comparable>
void BinarySearchTree<Comparable>::preorder(BinaryNode * t) const
{
    if (t == nullptr)
        return;

    cout << t->element << " ";
	preorder(t->left);
    preorder(t->right);
}

//NLR
template <typename Comparable>
void BinarySearchTree<Comparable>::postorder(BinaryNode * t) const
{
    if (t == nullptr)
        return;

    postorder(t->left);
    postorder(t->right);
	cout << t->element << " ";
}

//LNR
template <typename Comparable>
void BinarySearchTree<Comparable>::inorder(BinaryNode * t) const
{
    if (t == nullptr)
        return;

    inorder(t->left);
    cout << t->element << " ";
    inorder(t->right);
}

#endif
