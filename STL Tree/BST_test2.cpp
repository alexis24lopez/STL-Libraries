/*****************************************************************************
* Alexis Lopez
* BST_test2.cpp
* This program is to test BinarySearchTree.h
******************************************************************************/
#include <iostream>

#include "BinarySearchTree.h"

using namespace std;

main()
{
    BinarySearchTree<int> complete_tree;

    complete_tree.insert(20);
    complete_tree.insert(10);
    complete_tree.insert(30);
    complete_tree.insert(35);
    complete_tree.insert(25);
    complete_tree.insert(5);
    complete_tree.insert(15);
    complete_tree.printTree();

    cout << "Inorder Traversal\n";
    complete_tree.inorder();
    cout << endl;

   cout << "Postorder Traversal\n";
    complete_tree.postorder();
    cout << endl;

    cout << "Preorder Traversal\n";
    complete_tree.preorder();
    cout << endl;
}

