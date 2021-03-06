#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

struct node{
    int data;
    struct node* left;
    struct node* right;

    struct node* parent;
};

struct node* newNode(int data) 
{  
  struct node* node = (struct node*)malloc(sizeof(struct node)); 
  node->data = data; 
  node->left = NULL; 
  node->right = NULL; 

  node->parent = NULL;

  return(node); 
}

struct binarySearchTree{
    struct node *root = newNode(-1);
    binarySearchTree();
    void insertIter(int value, node* root){
        struct node *cream = newNode(value);
        //case where nothing is in BST
        if(root->data == -1){
            root->data = value;
            return;
        }
        //cases where value is lesser or greater than root
        node* parent = NULL;
        node* current = root;
        while(current!=NULL){
            parent = current;
            if(current->data < value){
                current = current->right;
            }
            else{
                current = current->left;
            }
        }
        if(parent->data < value){
            parent->right = cream;
        }
        else{
            parent->left = cream;
        }
    }
    void deleteIter(int value, node* root){
        node* parent = NULL;
        //node* current = root;
        while(root->data != value){
            parent = root;
            if(root->data < value){
                root = root->right;
            }
            else{
                root = root->left;
            }
        }
    
        if(root->data == value){
            //3 cases
            //leaf case
            if(root->left == NULL && root->right == NULL){
                //if this is root node
                if(root->parent == NULL){
                    root = newNode(-1);
                }
                //not root node
                else if(root->parent != NULL){
                    if(root->parent->data > root->data){
                        root->parent->left = NULL;
                    }
                    if(root->parent->data < root->data){
                        root->parent->right = NULL;
                    }
                }
            }
            //one child case
            else if(root->left != NULL && root->right == NULL){
                root->left->parent = root->parent;
                if(root->parent->data > root->data){
                    root->parent->left = root->left;
                }
                if(root->parent->data < root->data){
                    root->parent->right = root->left;
                }
            }
            else if(root->left == NULL && root->right != NULL){
                root->right->parent = root->parent;
                if(root->parent->data > root->data){
                    root->parent->left = root->right;
                }
                if(root->parent->data < root->data){
                    root->parent->right = root->right;
                }
            }
            //two children case
            else if(root->left != NULL && root->right != NULL){
                int successor = findMinIter(root->right);
                //remove this recursive!
                //deleteIter(successor, root->right);
                root->data = successor;
                root = root->right;
                while(root->data != successor ){
                    root->left->parent = root;
                    root = root->left;
                }
                root->parent->left = NULL;
            }
            return;
        }
        /*else if(value < root->data){
            deleteRec(value, root->left);
        }
        else if(value > root->data){
            deleteRec(value, root->right);
        }*/
        return;
    }

    int findNextIter(node* root){
        int next;
        //ignore edge case where there is no next (no right child and no greater parent)
        //case with right child
        if(root->right != NULL){
            next = findMinIter(root->right);
        }
        //case with no right child, but greater parent exists
        else if(root->right == NULL && (root->parent->data > root->data)){
            next = root->parent->data;
        }
        return next;
    }

    int findPrevIter(node* root){
        int previous;
        //ignore edge case where there is no next (no left child and no lesser parent)
        //case with left child
        if(root->left != NULL){
            previous = findMaxIter(root->left);
        }
        //case with no left child, but lesser parent exists
        else if(root->left == NULL && (root->parent->data < root->data)){
            previous = root->parent->data;
        }
        return previous;
    }

    int findMinIter(node* root){
        while(root->left!=NULL){
            root=root->left;
        }
        return root->data;
    }
    int findMaxIter(node* root){
        while(root->right!=NULL){
            root=root->right;
        }
        return root->data;
    }

    void fromArray(int* array, int size, node* root){
        for(int i = 0; i < size; i++){
            insertIter(array[i], root);
        }
    }
    
};

binarySearchTree :: binarySearchTree(){
    //root = NULL;
}

int main(){
    binarySearchTree Poopy;
    int inputArray[7] = {5,3,7,2,4,6,8};
    Poopy.fromArray(inputArray, 7, Poopy.root);
    cout << Poopy.root->data << endl;
    cout << Poopy.root->right->data << endl;
    cout << Poopy.root->left->data << endl;
    cout << Poopy.root->right->right->data << endl;
    cout << "max is: " << Poopy.findMaxIter(Poopy.root) << endl;
    cout << "min is: " << Poopy.findMinIter(Poopy.root) << endl;
    Poopy.deleteIter(5,Poopy.root);
    cout << Poopy.root->data << endl;
    cout << Poopy.root->right->data << endl;
    cout << Poopy.root->left->data << endl;
    cout << Poopy.root->right->right->data << endl;
    cout << Poopy.findPrevIter(Poopy.root) << endl;
    cout << Poopy.findNextIter(Poopy.root) << endl;
    cout << Poopy.findNextIter(Poopy.root->right) << endl;
    return 0;
}