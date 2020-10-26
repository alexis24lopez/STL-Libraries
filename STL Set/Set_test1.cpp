/*****************************************************************************
* Alexis Lopez
* Set_test1.cpp
* This program is to test Set.h
******************************************************************************/
#include <iostream>

#include "Set.h"

using namespace std;

main()
{
    Set<int> tree;

    tree.insert(6);
    tree.insert(8);
    tree.insert(2);
    tree.insert(1);
    tree.insert(5);
    tree.insert(3);
    tree.insert(4);
    tree.printTree();

    cout << "Min = " << tree.findMin() << endl;
    cout << "Max = " << tree.findMax() << endl;

    cout << "Remove 2\n";
    tree.remove(2);
    tree.printTree();

    cout << "Contains 2? " << tree.contains(2) << endl;
    cout << "Contains 4? " << tree.contains(4) << endl;

    cout << "Copy Constructor\n";
    Set<int> copy(tree);
    cout << "Remove 6\n";
    copy.remove(6);
    copy.printTree();

    cout << "Inorder Traversal\n";
    copy.inorder();
    cout << endl;

    cout << "Clear Tree\n";
    copy.makeEmpty();
    copy.printTree();
}
