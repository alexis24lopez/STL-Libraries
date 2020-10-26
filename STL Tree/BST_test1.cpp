/*****************************************************************************
* Alexis Lopez
* BST_test1.cpp
* This program is to test BinarySearchTree.h
******************************************************************************/
#include <iostream>

#include "BinarySearchTree.h"

//using namespace std;

main()
{
    BinarySearchTree<int> tree;

    tree.insert(6);
    tree.insert(8);
    tree.insert(2);
    tree.insert(1);
    tree.insert(5);
    tree.insert(3);
    tree.insert(4);
    tree.printTree();

    std::cout << "Min = " << tree.findMin() << std::endl;
    std::cout << "Max = " << tree.findMax() << std::endl;

    std::cout << "Remove 2\n";
    tree.remove(2);
    tree.printTree();

    std::cout << "Contains 2? " << tree.contains(2) << std::endl;
    std::cout << "Contains 4? " << tree.contains(4) << std::endl;

    std::cout << "Copy Constructor\n";
    BinarySearchTree<int> copy(tree);
    std::cout << "Remove 6\n";
    copy.remove(6);
    copy.printTree();

    std::cout << "Inorder Traversal\n";
    copy.inorder();
    std::cout << endl;

    std::cout << "Clear Tree\n";
    copy.makeEmpty();
    copy.printTree();
}
