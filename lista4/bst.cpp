#include <cmath>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>
using namespace std;

char* left_trace; // needs to be allocaded with size
char* right_trace; // needs to be allocaded with size

//binaryTree
class BinaryTreeNode{
    public:
    int key;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
    BinaryTreeNode* parent;

    BinaryTreeNode(int key,BinaryTreeNode* left,BinaryTreeNode* right,BinaryTreeNode* parent){
        this->key = key;
        this->left = left;
        this->right = right; 
        this->parent = parent;
    }
};


int getHeight(BinaryTreeNode* root){
    if(root==nullptr){
        return 0;
    }
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return std::max(leftHeight,rightHeight) + 1;
}

BinaryTreeNode* insert(BinaryTreeNode* root,BinaryTreeNode* node, int key) {
    BinaryTreeNode* current = root;
    BinaryTreeNode* newNode = new BinaryTreeNode(key, nullptr, nullptr, nullptr);
    BinaryTreeNode* parent = nullptr;

    // Szukanie odpowiedniego miejsca dla wstawienia węzła
    while (current != nullptr) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // Wstawienie nowego węzła do drzewa
    if (parent == nullptr) {
        // Jeśli drzewo jest puste, ustawiamy nowy węzeł jako korzeń
        root = newNode;
    } else if (key < parent->key) {
        // Jeśli klucz jest mniejszy od klucza rodzica, wstawiamy w lewym poddrzewie
        parent->left = newNode;
    } else {
        // W przeciwnym razie wstawiamy w prawym poddrzewie
        parent->right = newNode;
    }

    // Ustawienie wskaźników rodzica
    if (newNode != nullptr) {
        newNode->parent = parent;
    }

    return root;
}


BinaryTreeNode* minValueNode(BinaryTreeNode* root){
    BinaryTreeNode* current = root;
    while(current && current->left != nullptr){
        current = current->left;
    }
    return current;
}

BinaryTreeNode* deleteNode(BinaryTreeNode* root,int key){
    if(root ==nullptr){
        return root;
    }
    if(key < root->key){
        root->left = deleteNode(root->left,key);
    }
    else if(key > root->key){
        root->right = deleteNode(root->right,key);
    }
    else{
        //Jesli węzeł nie ma liści
        if(root->left ==nullptr && root->right==nullptr){
            return nullptr;
        }
        //JEśli węzeł posiada prawy liść
        else if(root->left != nullptr && root->right==nullptr){
            BinaryTreeNode* left = root->left;
            free(root);
            return left;
        }
        else if(root->right != nullptr && root->left==nullptr){
            BinaryTreeNode* right = root->right;
            free(root);
            return right;
        }
        else{

            BinaryTreeNode* current = minValueNode(root->right);
            root->key = current->key;
            root->parent = current->parent;
            root->right = deleteNode(root->right,current->key);
        }

    }
    return root;
}



void print_BST( BinaryTreeNode* root, int depth,char prefix){
  if( root == NULL ) return;
  if( root->left != NULL ){
    print_BST(root->left, depth+1, '/');
  }
  if(prefix == '/') left_trace[depth-1]='|';
  if(prefix == '\\') right_trace[depth-1]=' ';
  if( depth==0) printf("-");
  if( depth>0) printf(" ");
  for(int i=0; i<depth-1; i++)
    if( left_trace[i]== '|' || right_trace[i]=='|' ) {
      printf("| ");
    } else {
      printf("  ");
    }
  if( depth>0 ) printf("%c-", prefix);
  printf("[%d]\n", root->key);
  left_trace[depth]=' ';
  if( root->right != NULL ){
    right_trace[depth]='|';
    print_BST(root->right, depth+1, '\\');
  }
}


int main(){
    std::string input_line;
    int i=0;
    if(cin){
        getline(cin,input_line);
    }
    int length = stoi(input_line);
    int array[length];
    while(i<length) {
        getline(cin, input_line);
        array[i] = stoi(input_line);
        i++;
    }
    BinaryTreeNode *root = nullptr;
    for(int i : array){
        root = insert(root,nullptr,i);
    }
    left_trace= (char*)malloc( length*sizeof(char) );
    right_trace= (char*)malloc( length*sizeof(char) );
    for(int i=0; i<length; i++){
        left_trace[i]=' ';
        right_trace[i]=' ';
    }
    print_BST(root, 0, '-');

    free(left_trace);
    free(right_trace);
    delete root;
}


