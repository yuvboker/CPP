#include <set>
#include "BinaryTree/Tree.h"

//
// Created by Yuval Boker on 12/15/2019.
//
void testTree0(){
    Tree<> t1("Yuval");
//    Tree<> t2("Boker");
    t1.insert(7);
    t1.insert(3);
    t1.insert(4);
    t1.insert(9);
    t1.insert(0);
    t1.inOrder();
    t1.preOrder();
    t1.remove(t1.search(7));
    t1.remove(t1.search(3));
    t1.remove(t1.search(0));
    t1.inOrder();
    t1.preOrder();
    t1.getSize();
}

void testTree1(){
    Tree<> t1("Yuval");
    Tree<> t2("Boker");
    t1.insert(7);
    t2.insert(3);
//    Copy-Constructor
    Tree<>temp1(t1);
//    Assignment-Operator
    temp1 = t2;
//    Move-Constructor
    Tree<>temp2 = move (t2);
    temp2 = move(t1);
}


// driver function to test various inference
int main()
{
    testTree0();
    testTree1();
    return 0;
}
