//
// Created by Yuval Boker on 12/15/2019.
//

#include "Tree.h"

/**
 ****************** Tree Implementation *********************
 */

//Constructor
template<typename T>
Tree<T>::Tree(std::string name): name(std::move(name)), size(0), root(nullptr){
    cout << "Constructor was called" << endl;
}

//Destructor
template<typename T>
Tree<T>::~Tree(){
    cout << "Destructor was called" << endl;
    this->removeTree();
}

//Copy Constructor
template<typename T>
Tree<T>::Tree(const Tree<T>& other): name(other.name), size(other.size-1), root(nullptr){
    cout << "Copy-Constructor was called" << endl;
    this->insert(other.root->data);
    copyHelper(this->root, other.root);
}

//Assignment Operator
template<typename T>
Tree<T>& Tree<T>::operator=(const Tree<T>& other){
    cout << "Assignment-Operator was called" << endl;
    //Delete current Tree.
    this->removeTree();
    //Copy
    this->insert(other.root->data);
    copyHelper(this->root, other.root);
    this->name = other.name;
    this->size = other.size;
    return *this;
}

//Move Constructor
template<typename T>
Tree<T>::Tree(Tree<T>&& other) noexcept : root(other.root), size(other.size), name(other.name)  {
    cout << "Move-Constructor was called" << endl;
    other.root = nullptr;
    other.size = 0;
}

//Move Operator
template<typename T>
Tree<T>& Tree<T>::operator=(Tree<T>&& other) noexcept {
    cout << "Move-Operator was called" << endl;
    this->removeTree();
    this->root = other.root;
    this->size = other.size;
    other.root = nullptr;
    other.size = 0;
    return *this;
}


template<typename T>
Node<T>* Tree<T>::insert(T key) {
    this->size++;
    if (!this->root) {
        root = new Node<T>(key);
        return root;
    }
    return this->root->insert(key);
}

template<typename T>
void Tree<T>::remove(Node<T>* node){
    if(this->root == node)
        this->root = this->root->remove();
    else
        node->remove();
    this->size--;
}

template<typename T>
void Tree<T>::removeTree(){
    if(!this->root)
        return;
    this->root->clear();
    this->root = nullptr;
    this->size = 0;
}

template<typename T>
Node<T>* Tree<T>::search(T key){
    return this->root->search(key);
}

template<typename T>
int Tree<T>::getSize() {
    return this->size;
}

template<typename T>
void Tree<T>::copyHelper(Node<T>* root, const Node<T>* otherRoot) {
    if(otherRoot->left){
        auto* newNode = new Node<T>(otherRoot->left->data);
        root->left = newNode;
        newNode->parent = root;
        copyHelper(newNode, otherRoot->left);
    }
    else if(otherRoot->right){
        auto* newNode = new Node<T>(otherRoot->right->data);
        root->left = newNode;
        newNode->parent = root;
        copyHelper(newNode, otherRoot->right);
    }
}

template<typename T>
void Tree<T>::inOrder(){
    cout << "[ " ;
    if(this->root)
        this->root->inOrder();
    cout << "]" << endl;
}

template<typename T>
void Tree<T>::preOrder(){
    cout << "[ " ;
    if(this->root)
        this->root->preOrder();
    cout << "]" << endl;
}

template class Tree<int>;

