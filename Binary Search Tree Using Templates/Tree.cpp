//
// Created by Yuval Boker on 12/15/2019.
//

#include "Tree.h"

#include <utility>

/******************** Tree Implementation **********************/


/** Rule of 5 **/

//Constructor
template<typename T>
Tree<T>::Tree(string name): name_(std::move(name)), size_(0), root_(nullptr){
    cout << "Constructor of " << name_ << " was called" << endl;
}

//Destructor
template<typename T>
Tree<T>::~Tree(){
    cout << "Destructor of " << name_ << " was called" << endl;
    this->removeTree();
}

//Copy Constructor
template<typename T>
Tree<T>::Tree(const Tree<T>& other): name_(other.name()), size_(other.size()), root_(nullptr){
    cout << "Copy-Constructor of "<< name_ << " was called" << endl;
    if(!other.root())
        return;
    this->setRoot(new Node<T>(other.root()->data()));
    copyHelper(this->root(), other.root());
}

//Assignment Operator
template<typename T>
Tree<T>& Tree<T>::operator=(const Tree<T>& other){
    cout << "Assignment-Operator of " << name_ << " was called" << endl;
    if(this == &other)
        return *this;
    //Delete current Tree.
    this->removeTree();
    //Copy
    this->insert(other.root()->data());
    copyHelper(this->root(), other.root());
    this->setSize(other.size_);
    this->setName(other.name_);
    return *this;
}

//Move Constructor
template<typename T>
Tree<T>::Tree(Tree<T>&& other) noexcept : root_(other.root()), size_(other.size_), name_(move(other.name_))  {
    cout << "Move-Constructor of " << name_ <<" was called" << endl;
    other.setRoot(nullptr);
    other.setSize(0);
}

//Move Operator
template<typename T>
Tree<T>& Tree<T>::operator=(Tree<T>&& other) noexcept {
    cout << "Move-Operator of " << name_ << " was called" << endl;
    if(this == &other)
        return *this;
    this->removeTree();
    this->setRoot(other.root());
    this->setSize(other.size_);
    this->setName(move(other.name_));
    other.setRoot(nullptr);
    other.setSize(0);
    return *this;
}

/** Getters **/

template<typename T>
int Tree<T>::size() const {return size_;}

template<typename T>
string Tree<T>::name() const {return name_;}

template<typename T>
Node<T>* Tree<T>::root() const {return root_;}

/** Setters **/

template<typename T>
void Tree<T>::setSize(int size) {size_ = size;}

template<typename T>
void Tree<T>::setName(const string& name) {name_ = name;}

template<typename T>
void Tree<T>::setRoot(Node<T>* root) {root_ = root;}

/** Methods **/

template<typename T>
Node<T>* Tree<T>::insert(T key) {
    this->size_++;
    if (!this->root()) {
        setRoot(new Node<T>(key));
        return root();
    }
    return this->root()->insert(key);
}

template<typename T>
void Tree<T>::remove(Node<T>* node){
    if(this->root() == node)
        this->setRoot(this->root()->remove());
    else
        node->remove();
    this->size_--;
}

template<typename T>
void Tree<T>::removeTree(){
    if(!this->root())
        return;
    this->root()->clear();
    this->setRoot(nullptr);
    this->setSize(0);
}

template<typename T>
Node<T>* Tree<T>::search(T key){
    return this->root()->search(key);
}


template<typename T>
void Tree<T>::inOrder(){
    if (!this->root())
        return;
    auto* rightMost = this->root()->rightMostChild();
    cout << "In-order traversal: [" ;
    if(this->root())
        this->root()->inOrder(rightMost);
    cout << "]" << endl;
}

template<typename T>
void Tree<T>::preOrder(){
    if (!this->root())
        return;
    auto* rightMost = this->root()->rightMostChild();
    while(rightMost->left())
        rightMost = rightMost->left()->rightMostChild();
    cout << "Pre-order traversal: [" ;
    if(this->root())
        this->root()->preOrder(rightMost);
    cout << "]" << endl;
}

/** Helping methods **/

template<typename T>
void Tree<T>::copyHelper(Node<T>* root, const Node<T>* other) {
    if(other->left()){
        auto* newLeft = new Node<T>(other->left()->data());
        root->setLeft(newLeft);
        newLeft->setParent(root);
        copyHelper(newLeft, other->left());
    }
    if(other->right()){
        auto* newRight = new Node<T>(other->right()->data());
        root->setRight(newRight);
        newRight->setParent(root);
        copyHelper(newRight, other->right());
    }
}

template class Tree<int>;

