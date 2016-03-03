//
// Created by louis on 16/1/20.
//

#ifndef INTRODUCTIONTOALGORITHMS_BINARYSEARCHTREE_H
#define INTRODUCTIONTOALGORITHMS_BINARYSEARCHTREE_H

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template <typename T>
struct treenode
{
    T key;
    treenode *lchild;
    treenode *rchild;
    treenode *parent;
    treenode(T k, treenode* l, treenode* r, treenode* p)
    {
        key = k;
        lchild = l;
        rchild = r;
        parent = p;
    }
};

template <typename keytype>
class BinaryTree
{
public:
    BinaryTree();
    BinaryTree(vector<keytype> v);
    BinaryTree(keytype *keys, int n);
    ~BinaryTree();

    int size() {return treesize;};
    vector<keytype> inorder();
    treenode<keytype>* successor(keytype key);
    treenode<keytype>* find(keytype key);
    treenode<keytype>* findmin();
    treenode<keytype>* findmax();
    treenode<keytype>* insert(keytype key);
    int remove(keytype key);
private:
    treenode<keytype> *root;
    int treesize;
};

template <typename keytype>
BinaryTree<keytype>::~BinaryTree()
{
    vector<treenode<keytype>*> v;
    treenode<keytype> *p = root;
    stack<treenode<keytype>*> s;
    while(!s.empty() || p)
    {
        if(p)
        {
            s.push(p);
            p = p->lchild;
        }
        else
        {
            p = s.top();
            s.pop();
            v.push_back(p);
            p = p->rchild;
        }
    }
    for(auto it = v.begin(); it != v.end(); it++)
        delete(*it);
}

template <typename keytype>
BinaryTree<keytype>::BinaryTree()
{
    root = nullptr;
    treesize = 0;
}

template <typename keytype>
BinaryTree<keytype>::BinaryTree(vector<keytype> v)
{
    root = nullptr;
    treesize = 0;
    for(auto it = v.begin(); it != v.end(); it++)
        insert(*it);
}

template <typename keytype>
BinaryTree<keytype>::BinaryTree(keytype *keys, int n)
{
    root = nullptr;
    treesize = 0;
    for(int i = 0; i < n; i++)
        insert(keys[i]);
}

template <typename keytype>
treenode<keytype>* BinaryTree<keytype>::successor(keytype key)
{
    treenode<keytype> *p = find(key);
    if(!p)
        return nullptr;
    if(p->rchild)
    {
        p = p->rchild;
        while(p->lchild)
            p = p->lchild;
        return p;
    }
    treenode<keytype> * pa = p->parent;
    while(!pa && p == pa->rchild)
    {
        p = pa;
        pa = pa->parent;
    }
    return pa;
}
template <typename keytype>
vector<keytype> BinaryTree<keytype>::inorder()
{
    vector<keytype> v;
    treenode<keytype> *p = root;
    stack<treenode<keytype>*> s;
    while(!s.empty() || p)
    {
        if(p)
        {
            s.push(p);
            p = p->lchild;
        }
        else
        {
            p = s.top();
            s.pop();
            v.push_back(p->key);
            p = p->rchild;
        }
    }
    return v;
}

template <typename keytype>
treenode<keytype>* BinaryTree<keytype>::find(keytype key)
{
    treenode<keytype> *p = root;
    while(p)
    {
        if(p->key == key)
            return p;
        if(p->key < key)
            p = p->rchild;
        else
            p = p->lchild;
    }
    return p;
}

template <typename keytype>
treenode<keytype>* BinaryTree<keytype>::findmin()
{
    treenode<keytype> *p = root;
    if(!p)
        return p;
    while(p->lchild)
        p = p->lchild;
    return p;
}

template <typename keytype>
treenode<keytype>* BinaryTree<keytype>::findmax()
{
    treenode<keytype> *p = root;
    if(!p)
        return p;
    while(p->rchild)
        p = p->rchild;
    return p;
}

template <typename keytype>
treenode<keytype>* BinaryTree<keytype>::insert(keytype key)
{
    treenode<keytype> *newnodep = new treenode<keytype>(key, nullptr, nullptr, nullptr);
    treenode<keytype> *p = root;
    treenode<keytype> *pre = p;
    while(p)
    {
        pre = p;
        if(p->key > newnodep->key)
            p = p->lchild;
        else
            p = p->rchild;
    }
    newnodep->parent = pre;
    if(!pre)
        root = newnodep;
    else if(pre->key > newnodep->key)
        pre->lchild = newnodep;
    else
        pre->rchild = newnodep;
    treesize++;
    return newnodep;
}

template <typename keytype>
int BinaryTree<keytype>::remove(keytype key)
{
    treenode<keytype> *keynode = find(key);
    if(keynode->lchild == nullptr)
    {
        if(keynode->parent->lchild == keynode)
            keynode->parent->lchild = keynode->rchild;
        else
            keynode->parent->rchild = keynode->rchild;
        if(keynode->rchild != nullptr)
            keynode->rchild->parent = keynode->parent;
    }
    else if(keynode->rchild == nullptr)
    {
        if(keynode->parent->lchild == keynode)
            keynode->parent->lchild = keynode->lchild;
        else
            keynode->parent->rchild = keynode->lchild;
        if(keynode->lchild != nullptr)
            keynode->lchild->parent = keynode->parent;
    }
    else
    {
        treenode<keytype> *p = keynode->rchild;
        while(p->lchild != nullptr)
            p = p->lchild;
        if(p->parent != keynode)
        {
            p->parent->lchild = p->rchild;
            p->rchild->parent = p->parent;
            p->rchild = keynode->rchild;
        }
        p->lchild = keynode->lchild;
        p->parent = keynode->parent;
    }
    treesize--;
    delete(keynode);
    return 1;
}
#endif //INTRODUCTIONTOALGORITHMS_BINARYSEARCHTREE_H
