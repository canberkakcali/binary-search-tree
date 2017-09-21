#include <iostream>
#include "bstree.hpp"

int main() {

    BSTree<int, const char*> tree;

    tree.insert(5, "bes");
    tree.insert(2, "iki");
    tree.insert(3, "uc");
    tree.insert(7, "yedi");
    tree.insert(6, "alti");
    tree.insert(10, "on");
    tree.insert(1, "bir");
    tree.insert(0, "sifir");
    tree.insert(4, "dort");

    tree.del(5);
    tree.print(INORDER);

}