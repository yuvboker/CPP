//
// Created by Yuval Boker on 12/15/2019.
//
#include "Tree.h"


/********* Node implementation *********/


template<typename T>
Node<T>::Node(T data): data_(data), parent_(nullptr), left_(nullptr), right_(nullptr){}

/** Getters **/

template<typename T> T Node<T>::data() const {return data_;}

template<typename T>
Node<T> *Node<T>::left() const {return this->left_;}

template<typename T>
Node<T> *Node<T>::right() const {return this->right_;}

template<typename T>
Node<T> *Node<T>::parent() const {return this->parent_;}

/** Setters **/

template<typename T>
void Node<T>::setLeft(Node<T>* other){this->left_ = other;}

template<typename T>
void Node<T>::setRight(Node<T>* other){this->right_ = other;}

template<typename T>
void Node<T>::setParent(Node<T>* other){this->parent_ = other;}

/**** Methods ****/

template <typename T>
Node<T>* Node<T>::insert(T key) {
    if (this->data() > key){
        if(this->left())
            return this->left()->insert(key);
        this->setLeft(new Node<T>(key));
        this->left()->setParent(this);
        return this->left();
    }
    else{
        if(this->right())
            return this->right()->insert(key);
        this->setRight(new Node<T>(key));
        this->right()->setParent(this);
        return this->right();
    }
}

template<typename T>
Node<T>* Node<T>::remove(){
    //The hard case, there are two children
    if (this->left() && this->right()){
        // go to left child and then search for the right most child
        Node* rightMost = this->left()->rightMostChild();
        // detach from parent, if exists
        if(rightMost->parent()->data() > rightMost->data())
            rightMost->parent()->setLeft(nullptr);
        else
            rightMost->parent()->setRight(nullptr);
        // attach to this's parent
        if(this->parent()){
            if(this->parent()->data() > this->data())
                this->parent()->setLeft(rightMost);
            else
                this->parent()->setRight(rightMost);
        }
        // connect to this's children
        rightMost->setLeft(this->left());
        this->left()->setParent(rightMost);
        rightMost->setRight(this->right());
        this->right()->setParent(rightMost);
        // connect to this's parent
        rightMost->setParent(this->parent());
        // remove this
        this->setLeft(nullptr);
        this->setRight(nullptr);
        this->setParent(nullptr);
        delete this;
        return rightMost;
    }

        // A simpler case: there is only one child
        // Just replace current node with its only child
    else if(this->left()){
        if(this->parent()){
            if(this->parent()->data() > this->data())
                this->parent()->setLeft(this->left());
            else
                this->parent()->setRight(this->left());
        }
        this->left()->setParent(this->parent());
        Node* retNode = this->left();
        this->setLeft(nullptr);
        delete this;
        return retNode;
    }
    else if(this->right()){
        if(this->parent()){
            if(this->parent()->data() > this->data())
                this->parent()->setLeft(this->right());
            else
                this->parent()->setRight(this->right());
        }
        this->right()->setParent(this->parent());
        Node* retNode = this->right();
        this->setRight(nullptr);
        delete this;
        return retNode;
    }
        // The simplest case: current node has no children
    else{
        Node* retNode = nullptr;
        if(this->parent()){
            if(this->parent()->data() > this->data())
                this->parent()->setLeft(nullptr);
            else
                this->parent()->setRight(nullptr);
            retNode = this->parent();
            this->setParent(nullptr);
        }
        delete this;
        return retNode;
    }

}
template<typename T>
void Node<T>::clear() {
    if(this->right())
        this->right()->clear();
    if(this->left())
        this->left()->clear();
    this->setLeft(nullptr);
    this->setRight(nullptr);
    this->setParent(nullptr);
    delete(this);
}

template<typename T>
Node<T> *Node<T>::search(T key) {
    if(this->data() == key)
        return this;
    if(this->data() > key) {
        if (this->left())
            return this->left()->search(key);
    }
    else{
        if (this->right())
            return this->right()->search(key);
    }
    return nullptr;

}

template<typename T>
void Node<T>::inOrder(Node<T>* rightmost) {
    if(this->left())
        this->left()->inOrder(rightmost);
    if(this == rightmost)
        cout << this->data() << "";
    else
        cout << this->data() << ", ";
    if(this->right())
        this->right()->inOrder(rightmost);
}

template<typename T>
void Node<T>::preOrder(Node<T>* rightmost) {
    if(this == rightmost)
        cout << this->data() << "";
    else
        cout << this->data() << ", ";
    if(this->left())
        this->left()->preOrder(rightmost);
    if(this->right())
        this->right()->preOrder(rightmost);
}

/** Helping methods **/

template<typename T>
Node<T>* Node<T>::rightMostChild() {
    Node* rightMost = this;
    while(rightMost->right())
        rightMost = rightMost->right();
    return rightMost;
}



template class Node<int>;