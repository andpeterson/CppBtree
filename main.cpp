#include "BTree.hpp"
#include <iostream>

int main(){
	BTree<int> t(3); // A B-Tree with minium degree 3
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);
 
    std::cout << "Traversal of the constucted tree is ";
    t.traverse();
 
    return 0;
}