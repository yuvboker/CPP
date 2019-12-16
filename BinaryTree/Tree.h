//
// Created by Yuval Boker on 12/15/2019.
//

#ifndef PREPARATIONFORAPPLE_TREE_H
#define PREPARATIONFORAPPLE_TREE_H

#include <iostream>
using namespace std;

template <typename T = int> class Tree;

template <typename T = int>
class Node{
private:
    T data;
    Node<T>* right;
    Node<T>* left;
    Node<T>* parent;
    friend class Tree<T>;
    //Methods
    Node<T>(T data);
    void clear();
    Node<T>* insert(T);
//    return node which replaces the position of the current node
    Node<T>* remove();
//    return searched Node, if exists. Else return NULL
    Node<T>* search(T key);
    Node<T>* rightMostChild();
    void inOrder(Node<T>*);
    void preOrder(Node<T>*);

};


template <typename T>
class Tree {
private:
    Node<T>* root;
    string name;
    int size;
//    Private methods:
    void copyHelper(Node<T>* root, const Node<T>* otherRoot);
public:
//    Rule of Seven
    Tree<T>(std::string name); // constructor
    ~Tree<T>(); // destructor
    // Copy before initialization. No deletion is needed
    Tree<T>(const Tree<T>& other); // Copy Constructor
    // Copy after initialization. That is, first delete current Tree.
    Tree<T>& operator=(const Tree<T>& other); // Assignment Operator
    // Before initialization, shallow copy, no deletion.
    Tree<T>(Tree<T>&& other) noexcept ; // Move Constructor
    Tree<T>& operator=(Tree<T>&& other) noexcept ; // Move Operator

//    Methods
    Node<T>* insert(T key);
    void remove(Node<T>*);
    void removeTree();
    Node<T>* search(T key);
    int getSize();
    void inOrder();
    void preOrder();
};


#endif //PREPARATIONFORAPPLE_TREE_H
