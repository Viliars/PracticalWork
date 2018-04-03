#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED
#include <string>
#include <stdio.h>
#include <cstdlib>
using namespace std;

struct AVLNode {
    AVLNode *left, *right;
    string key;
    int height;
    AVLNode(string const &_key) : key(_key) {
       left = right = NULL;
       height = 1;
    }
    int getBalanceFactor() const {
        int r = right == NULL ? 0 : right->height;
        int l = left == NULL ? 0 : left->height;
        return r - l;
    }
    void fix() {
        int r = right == NULL ? 0 : right->height;
        int l = left == NULL ? 0 : left->height;
        height = (r > l ? r : l) + 1;
    }

     AVLNode *insert(string const &_key) {
         if (_key < key)
            left = left == NULL ? new AVLNode(_key) : left->insert(_key);
         else
            right = right == NULL ? new AVLNode(_key) : right->insert(_key);
         return balance();
     }
     AVLNode *findMinimum() {
        return left != NULL ? left->findMinimum() : this;
     }

     AVLNode *removeMinimum() {
        if (left == NULL) return right;
        left = left->removeMinimum();
        return balance();
     }

     AVLNode* balance()
     {
         fix();
         switch(getBalanceFactor())
         {
             case -2: if(left->getBalanceFactor()>0)
             {
                 left=left->rotateLeft();
             }
             return rotateRight();
             case 2: if(right->getBalanceFactor()<0)
             {
                 right=right->rotateRight();
             }
             return rotateLeft();
             default:
                return this;
         }
     }

     AVLNode* rotateLeft()
     {
        AVLNode* t=right;
        right=t->left;
        t->left=this;
        fix();
        t->fix();
        return t;
     }

     AVLNode* rotateRight()
     {
        AVLNode* t=left;
        left=t->right;
        t->right=this;
        fix();
        t->fix();
        return t;
     }

     void print()
     {
         if(right!=NULL) right->print();
         for(int i=6;i>=height;--i)
         {
             printf("   ");
         }
         printf("%s\n",key.c_str());
         if(left!=NULL) left->print();
     }

     static AVLNode *remove(AVLNode *p, string const &_key) {
        if (p == NULL) return NULL;
        if (_key < p->key) {
           p->left = remove(p->left, _key);
           return p->balance();
        } else if (_key > p->key) {
           p->right = remove(p->right, _key);
           return p->balance();
        } else {
           AVLNode *l = p->left;
           AVLNode *r = p->right;
           delete p;
           if (r == NULL) return l;
           AVLNode *min = r->findMinimum();
           min->right = r->removeMinimum();
           min->left = l;
           return min->balance();
        }
    }
};

struct AVLTree {
    AVLNode *root;
    AVLTree() {
        root = NULL;
    }
    void print() const {
        if (root != NULL) root->print();
    }

    bool insert(string const &_key) {
        if (root == NULL) root = new AVLNode(_key);
        else root = root->insert(_key);
        return true;
    }

    bool remove(string const &_key) {
        root = AVLNode::remove(root, _key);
        return true;
    }
};


#endif // AVL_H_INCLUDED
