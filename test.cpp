#include <iostream>
#include "bstree.hpp"

int main() {

    BSTree<int, const char*> tree;

    tree.insert(5, "five");
    tree.insert(2, "two");
    tree.insert(3, "three");
    tree.insert(7, "seven");
    tree.insert(6, "six");
    tree.insert(10, "ten");
    tree.insert(1, "one");
    tree.insert(0, "zero");
    tree.insert(4, "four");

    tree.del(5);
    std::cout << "Printing the data in the nodes by preorder traversal:" << std::endl;
    tree.print(PREORDER);

    std::cout << "Iterating through all nodes from beginning to the end of the tree by inorder traversal:" << std::endl;
    BSTree<int, const char*>::iterator i = tree.begin();
    while(i != tree.end()) {
        std::cout << "[" << (*i).key << ", " << (*i).data << "] ";
        i++;
    }
    std::cout << std::endl << "Iterating through all nodes in reverse order:" << std::endl;

    i = tree.rbegin();
    while(i != tree.end()) {
        std::cout << "[" << (*i).key << ", " << (*i).data << "] ";
        i--;
    }
    std::cout << std::endl;

}