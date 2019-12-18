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

    /** Members **/
    T data_;
    Node<T>* right_;
    Node<T>* left_;
    Node<T>* parent_;

    /** Friends **/
    friend class Tree<T>;

    explicit Node<T>(T); // Constructor

    /** Getters **/
    T data() const;
    Node<T>* left() const;
    Node<T>* right() const;
    Node<T>* parent() const;

    /** Setters **/
    void setLeft(Node<T>*);
    void setRight(Node<T>*);
    void setParent(Node<T>*);

    /**** Methods ****/
    void clear();
    Node<T>* insert(T);
    Node<T>* remove();
    Node<T>* search(T);

    void inOrder(Node<T>*);
    void preOrder(Node<T>*);

    /** Helping methods **/
    Node<T>* rightMostChild(); // Helper for remove
};


template <typename T>
class Tree {
private:

    /** Members **/
    Node<T>* root_;
    string name_;
    int size_;

    /**Helping methods **/
    void copyHelper(Node<T>*, const Node<T>*); // Helper for copy constructor/ Assignment operator

public:

    /** Rule of 5 **/
    explicit Tree<T>(string); // constructor
    ~Tree<T>(); // destructor
    Tree<T>(const Tree<T>&); // Copy Constructor
    Tree<T>& operator=(const Tree<T>&); // Assignment Operator
    Tree<T>(Tree<T>&&) noexcept ; // Move Constructor
    Tree<T>& operator=(Tree<T>&&) noexcept ; // Move Operator

    /** Getters **/
    int size() const;
    Node<T>* root() const;
    string name() const;

    /** Setters **/
    void setSize (int);
    void setRoot(Node<T>*);
    void setName(const string&);

    /** Methods **/
    Node<T>* insert(T);
    void remove(Node<T>*);
    void removeTree();
    Node<T>* search(T);
    void inOrder();
    void preOrder();
};


#endif //PREPARATIONFORAPPLE_TREE_H
