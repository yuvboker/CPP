//
// Created by Yuval Boker on 12/15/2019.
//
#include "Tree.h"
/**
 * Node implementation
 */


//Constructor
template<typename T>
Node<T>::Node(T data): data(data), parent(nullptr), left(nullptr), right(nullptr){}


template <typename T>
Node<T>* Node<T>::insert(T key) {
    if (this->data > key){
        if(this->left)
            return this->left->insert(key);
        this->left = new Node<T>(key);
        this->left->parent = this;
        return this->left;
    }
    else{
        if(this->right)
            return this->right->insert(key);
        this->right = new Node<T>(key);
        this->right->parent = this;
        return this->right;
    }
}

template<typename T>
Node<T>* Node<T>::remove(){
    //The hard case, there are two children
    if (this->left && this->right){
        // go to left child and then search for the right most child
        Node* rightMost = this->left->rightMostChild();
        // detach from parent, if exists
        if(rightMost->parent->data > rightMost->data)
            rightMost->parent->left = nullptr;
        else
            rightMost->parent->right = nullptr;
        // attach to this's parent
        if(this->parent){
            if(this->parent->data > this->data)
                this->parent->left = rightMost;
            else
                this->parent->right = rightMost;
        }
        // connect to this's children
        rightMost->left = this->left;
        this->left->parent = rightMost;
        rightMost->right = this->right;
        this->right->parent = rightMost;
        // connect to this's parent
        rightMost->parent = this->parent;
        // remove this
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        delete this;
        return rightMost;
    }

        // A simpler case: there is only one child
        // Just replace current node with its only child
    else if(this->left){
        if(this->parent){
            if(this->parent->data > this->data)
                this->parent->left = this->left;
            else
                this->parent->right = this->left;
        }
        this->left->parent = this->parent;
        Node* retNode = this->left;
        this->left = nullptr;
        delete this;
        return retNode;
    }
    else if(this->right){
        if(this->parent){
            if(this->parent->data > this->data)
                this->parent->left = this->right;
            else
                this->parent->right = this->right;
        }
        this->right->parent = this->parent;
        Node* retNode = this->right;
        this->right = nullptr;
        delete this;
        return retNode;
    }
        // The simplest case: current node has no children
    else{
        Node* retNode = nullptr;
        if(this->parent){
            if(this->parent->data > this->data)
                this->parent->left = nullptr;
            else
                this->parent->right = nullptr;
            retNode = this->parent;
            this->parent = nullptr;
        }
        delete this;
        return retNode;
    }

}
template<typename T>
void Node<T>::clear() {
    if(this->right)
        this->right->clear();
    if(this->left)
        this->left->clear();
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    delete(this);
}

template<typename T>
Node<T>* Node<T>::rightMostChild() {
    Node* rightMost = this;
    while(rightMost->right)
        rightMost = rightMost->right;
    return rightMost;
}

template<typename T>
Node<T> *Node<T>::search(T key) {
    if(this->data == key)
        return this;
    if(this->data > key) {
        if (this->left)
            return this->left->search(key);
    }
    else{
        if (this->right)
            return this->right->search(key);
    }
    return nullptr;

}

template<typename T>
void Node<T>::inOrder(Node<T>* rightmost) {
    if(this->left)
        this->left->inOrder(rightmost);
    if(this == rightmost)
        cout << this->data << "";
    else
        cout << this->data << ", ";
    if(this->right)
        this->right->inOrder(rightmost);
}

template<typename T>
void Node<T>::preOrder(Node<T>* rightmost) {
    if(this == rightmost)
        cout << this->data << "";
    else
        cout << this->data << ", ";
    if(this->left)
        this->left->preOrder(rightmost);
    if(this->right)
        this->right->preOrder(rightmost);
}

template class Node<int>;