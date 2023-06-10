#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

char* left_trace;
char* right_trace;

class SplayNode {
public:
    int key;
    SplayNode* left;
    SplayNode* right;
    SplayNode* parent;

    SplayNode(int key, SplayNode* left, SplayNode* right, SplayNode* parent) {
        this->key = key;
        this->left = left;
        this->right = right;
        this->parent = parent;
    }
};

SplayNode* leftRotate(SplayNode* root, SplayNode* x) {
    SplayNode* y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
        return root;
}

SplayNode* rightRotate(SplayNode* root, SplayNode* x) {
    SplayNode* y = x->left;
	x->left = y->right;
	if (y->right != nullptr) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == nullptr) {
		root = y;
	} else if (x == x->parent->right) {
		x->parent->right = y;
	} else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;

    return root;
}




SplayNode* splay(SplayNode* root, SplayNode* x) {
    while(x->parent) {
			if (!x->parent->parent) {
				if (x == x->parent->left) {
					// zig
					root = rightRotate(root,x->parent);
				} else {
					// zag 
					root =leftRotate(root,x->parent);
				}
			} else if (x == x->parent->left && x->parent == x->parent->parent->left) {
				// zig-zig
				root = rightRotate(root,x->parent->parent);
				root = rightRotate(root,x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->right) {
				// zag-zag 
				root = leftRotate(root,x->parent->parent);
				root = leftRotate(root,x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->left) {
				// zig-zag 
				root = leftRotate(root,x->parent);
				root = rightRotate(root,x->parent);
			} else {
				// zag-zig 
				root = rightRotate(root,x->parent);
				root = leftRotate(root,x->parent);
			}
		}
    return root;
}

SplayNode* insert(SplayNode* root, int key) {
    SplayNode* newNode = new SplayNode(key, nullptr, nullptr, nullptr);
    if (root == nullptr) {
        return newNode;
    }

    SplayNode* current = root;
    SplayNode* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    newNode->parent = parent;
    if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    return splay(root, newNode);
}


SplayNode* maxValue(SplayNode* node) {
    if (node == nullptr) {
        return nullptr;
    }
    SplayNode* current = node;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current;
}

SplayNode* deleteNode(SplayNode* root, int key) {
    if (root == nullptr) {
        return nullptr;
    }

    SplayNode* current = root;
    SplayNode* parent = nullptr;

    while (current != nullptr && current->key != key) {
        if (key > current->key) {
            parent = current;
            current = current->right;
        } else {
            parent = current;
            current = current->left;
        }
    }

    if (current == nullptr) {
        return root; 
    }

    root = splay(root, current);


    SplayNode* leftTree = root->left;
    SplayNode* rightTree = root->right;

    if (leftTree != nullptr) {
        leftTree->parent = nullptr;
    }

    if (rightTree != nullptr) {
        rightTree->parent = nullptr;
    }

    delete root;

    if (leftTree == nullptr) {
        return rightTree;
    }

    SplayNode* maxLeft = maxValue(leftTree);
    root = splay(leftTree, maxLeft);
    root->parent = nullptr;
    root->right = rightTree;

    if (rightTree != nullptr) {
        rightTree->parent = root;
    }

    return root;
}



int getHeight(SplayNode* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return max(leftHeight, rightHeight) + 1;
}

void print_BST( SplayNode* root, int depth,char prefix){
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

int main() {
    std::string input_line;
    int i = 0;
    if (cin) {
        getline(cin, input_line);
    }
    int length = stoi(input_line);
    int array[length];
    while (i < length) {
        getline(cin, input_line);
        array[i] = stoi(input_line);
        i++;
    }
    SplayNode* root = nullptr;
    for (int i : array) {
        root = insert(root, i);
    }
    left_trace = (char*)malloc((length + 1) * sizeof(char));
    right_trace = (char*)malloc((length + 1) * sizeof(char));
    for (int i = 0; i <= length; i++) {
        left_trace[i] = ' ';
        right_trace[i] = ' ';
    }
    print_BST(root, 0, '-');
    for (int i = 0; i <= length; i++) {
        left_trace[i] = ' ';
        right_trace[i] = ' ';
    }
    
    print_BST(root, 0, '-');

    free(left_trace);
    free(right_trace);
    return 0;
}
