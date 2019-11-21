// SoftEng_Activties.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "avlTree.h"
#include <fstream>

int main() {
    avlTree<int, std::string> newTree;
    newTree.insert(22,"Jane");
    newTree.insert(22,"Mary");
    newTree.insert(0,"Harold");
    newTree.insert(9,"Edward");
    newTree.insert(37,"Victoria");
    newTree.insert(4,"Matilda");
    newTree.insert(26,"Oliver");
    newTree.insert(42,"Elizabeth");
    newTree.insert(19,"Henry");
    newTree.insert(4,"Stephen");
    newTree.insert(24,"James");
    newTree.insert(-1,"Edward");
    newTree.insert(31,"Anne");
    newTree.insert(23,"Elizabeth");
    newTree.insert(1,"William");
    newTree.insert(26,"Charles");
    newTree.displayEntries();
    //newTree.displayTree();

}

