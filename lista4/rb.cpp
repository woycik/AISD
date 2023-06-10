//red-black tree
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



enum Color {
    RED,
    BLACK
};

struct RedBlackTree {
    int key;
    Color color;
    RedBlackTree* parent;
    RedBlackTree* left;
    RedBlackTree* right;

    RedBlackTree(int key, Color color, RedBlackTree* parent, RedBlackTree* left, RedBlackTree* right){
        this->key = key;
        this->color = color;
        this->parent = parent;
        this->left = left;
        this->right = right;
    }
        
};

RedBlackTree* leftRotate(RedBlackTree* root, RedBlackTree* x) {
    RedBlackTree* y = x->right;
    x->right = y->left;

    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;

    return root;
}

RedBlackTree* rightRotate(RedBlackTree* root, RedBlackTree* y) {
    RedBlackTree* x = y->left;
    y->left = x->right;

    if (x->right != nullptr)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;

    return root;
}

RedBlackTree* minimum(RedBlackTree* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

RedBlackTree* treeSuccessor(RedBlackTree* node) {
    if (node->right != nullptr) {
        return minimum(node->right);
    }
    RedBlackTree* y = node->parent;
    while (y != nullptr && node == y->right) {
        node = y;
        y = y->parent;
    }
    return y;
}

RedBlackTree* fixInsertion(RedBlackTree* root, RedBlackTree* node) {
    while (node->parent != nullptr && node->parent->color == RED) {
        RedBlackTree* parent = node->parent;
        RedBlackTree* grandparent = parent->parent;

        if (parent == grandparent->left) {
            RedBlackTree* uncle = grandparent->right;

            if (uncle != nullptr && uncle->color == RED) {
                // Przypadek 1: Wujek jest czerwony
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    // Przypadek 2: Wujek jest czarny, a węzeł jest prawym dzieckiem
                    node = parent;
                    root = leftRotate(root, node);
                    parent = node->parent;
                    grandparent = parent->parent;
                }

                // Przypadek 3: Wujek jest czarny, a węzeł jest lewym dzieckiem
                parent->color = BLACK;
                grandparent->color = RED;
                root = rightRotate(root, grandparent);
            }
        } else {
            RedBlackTree* uncle = grandparent->left;

            if (uncle != nullptr && uncle->color == RED) {
                // Przypadek 1: Wujek jest czerwony
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    // Przypadek 2: Wujek jest czarny, a węzeł jest lewym dzieckiem
                    node = parent;
                    root = rightRotate(root, node);
                    parent = node->parent;
                    grandparent = parent->parent;
                }

                // Przypadek 3: Wujek jest czarny, a węzeł jest prawym dzieckiem
                parent->color = BLACK;
                grandparent->color = RED;
                root = leftRotate(root, grandparent);
            }
        }
    }

    root->color = BLACK;

    return root;
}

RedBlackTree* insert(RedBlackTree* root, int key) {
    RedBlackTree* current = root;
    RedBlackTree* newNode = new RedBlackTree(key, RED, nullptr, nullptr, nullptr);
    RedBlackTree* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }


    if (parent == nullptr) {
        root = newNode;
    }
    else if (key < parent->key) {
        
        parent->left = newNode;
    } 
    else {
        parent->right = newNode;
    }


    newNode->parent = parent;
    root = fixInsertion(root, newNode);
    return root;
}

RedBlackTree* fixDeletion(RedBlackTree* root, RedBlackTree* node, RedBlackTree* parent) {
    while ((node == nullptr || node->color == BLACK) && node != root) {
        if (node == parent->left) {
            RedBlackTree* sibling = parent->right;

            if (sibling != nullptr && sibling->color == RED) {
                // Przypadek 1: Rodzeństwo jest czerwone
                sibling->color = BLACK;
                parent->color = RED;
                root = leftRotate(root, parent);
                sibling = parent->right;
            }

            if ((sibling == nullptr || sibling->left == nullptr || sibling->left->color == BLACK) &&
                (sibling == nullptr || sibling->right == nullptr || sibling->right->color == BLACK)) {
                // Przypadek 2: Oba dzieci rodzeństwa są czarne
                if (sibling != nullptr) {
                    sibling->color = RED;
                }
                node = parent;
                parent = node->parent;
            } else {
                if (sibling == nullptr || sibling->right == nullptr || sibling->right->color == BLACK) {
                    // Przypadek 3: Lewe dziecko rodzeństwa jest czarne, a prawe jest czerwone
                    if (sibling != nullptr && sibling->left != nullptr) {
                        sibling->left->color = BLACK;
                    }
                    if (sibling != nullptr) {
                        sibling->color = RED;
                    }
                    root = rightRotate(root, sibling);
                    sibling = parent->right;
                }

                // Przypadek 4: Lewe dziecko rodzeństwa jest czerwone
                if (sibling != nullptr) {
                    sibling->color = parent->color;
                }
                if (parent != nullptr) {
                    parent->color = BLACK;
                }
                if (sibling != nullptr && sibling->right != nullptr) {
                    sibling->right->color = BLACK;
                }
                root = leftRotate(root, parent);
                node = root;
                break;
            }
        } else {
            RedBlackTree* sibling = parent->left;

            if (sibling != nullptr && sibling->color == RED) {
                // Przypadek 1: Rodzeństwo jest czerwone
                sibling->color = BLACK;
                parent->color = RED;
                root = rightRotate(root, parent);
                sibling = parent->left;
            }

            if ((sibling == nullptr || sibling->left == nullptr || sibling->left->color == BLACK) &&
                (sibling == nullptr || sibling->right == nullptr || sibling->right->color == BLACK)) {
                // Przypadek 2: Oba dzieci rodzeństwa są czarne
                if (sibling != nullptr) {
                    sibling->color = RED;
                }
                node = parent;
                parent = node->parent;
            } else {
                if (sibling == nullptr || sibling->left == nullptr || sibling->left->color == BLACK) {
                    // Przypadek 3: Prawe dziecko rodzeństwa jest czarne, a lewe jest czerwone
                    if (sibling != nullptr && sibling->right != nullptr) {
                        sibling->right->color = BLACK;
                    }
                    if (sibling != nullptr) {
                        sibling->color = RED;
                    }
                    root = leftRotate(root, sibling);
                    sibling = parent->left;
                }

                // Przypadek 4: Prawe dziecko rodzeństwa jest czerwone
                if (sibling != nullptr) {
                    sibling->color = parent->color;
                }
                if (parent != nullptr) {
                    parent->color = BLACK;
                }
                if (sibling != nullptr && sibling->left != nullptr) {
                    sibling->left->color = BLACK;
                }
                root = rightRotate(root, parent);
                node = root;
                break;
            }
        }
    }

    if (node != nullptr) {
        node->color = BLACK;
    }

    return root;
}



RedBlackTree* deleteNode(RedBlackTree* root, int key) {
    RedBlackTree* node = root;
    RedBlackTree* parent = nullptr;
    RedBlackTree* x = nullptr;


    while (node != nullptr && node->key != key) {
        parent = node;
        if (key < node->key) {
            node = node->left;
        } 
        else {
            node = node->right;
        }
    }

    if (node == nullptr) {
        return root;
    }

    if (node->left != nullptr && node->right != nullptr) {

        RedBlackTree* successor = treeSuccessor(node);
        node->key = successor->key;
        node->right = deleteNode(node->right, successor->key);  
        return root;
    }
    

    if (node->left != nullptr) {
        x = node->left;
    } 
    else {
        x = node->right;
    }


    if (x != nullptr) {
        x->parent = parent;
    }

    if (parent == nullptr) {
        root = x;
    } 
    else if (node == parent->left) {
        parent->left = x;
    } 
    else {
        parent->right = x;
    }

    if (node->color == BLACK) {
        root = fixDeletion(root, x, parent);
    }

    delete node;
    node = nullptr;

    return root;
}






void print_BST( RedBlackTree* root, int depth,char prefix){
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
  if(root->color==RED){
    cout<<"\033[31m";
    printf("[%d]", root->key);
    cout<<"\033[0m"<<endl;
  }
  else{
      printf("[%d]\n", root->key);
  }
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
    RedBlackTree *root = nullptr;
    left_trace= (char*)malloc( (length+1)*sizeof(char) );
    right_trace= (char*)malloc( (length+1)*sizeof(char) );
    for(int i : array){
        root = insert(root,i);
    }
    
    for(int i=0; i<=length; i++){
        left_trace[i]=' ';
        right_trace[i]=' ';
    }

    print_BST(root, 0, '-');
    
    delete root;
    free(left_trace);
    free(right_trace);

}
