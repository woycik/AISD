#include <iostream>
#include <deque>
#include<vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;


random_device rd;
mt19937 gen(rd());

class FibonacciHeapNode {
public:
    int key;
    int degree;

    FibonacciHeapNode* parent;
    FibonacciHeapNode* child;
    FibonacciHeapNode* left;
    FibonacciHeapNode* right;

    FibonacciHeapNode(int key) {
        this->key = key;
        this->degree = 0;
        this->child = nullptr;
        this->left = this;
        this->right = this;
    } 
};

class FibonacciHeap {
private:
    int numberOfNodes; 
    FibonacciHeapNode* minNode;
    FibonacciHeapNode* head;

public:
    FibonacciHeap(){
        numberOfNodes = 0;
        minNode = nullptr;
        head = nullptr;
    } 

    FibonacciHeapNode* minimum() 
    {
        return minNode;
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    FibonacciHeapNode* insert(int key) {
        FibonacciHeapNode* node = new FibonacciHeapNode(key);

        merge_with_root_list(node);

        if (minNode == nullptr || node->key < minNode->key) 
        {
            minNode = node;
        }

        numberOfNodes++;
        return node;
    }

    void merge_with_root_list(FibonacciHeapNode* node) {
        if (head == nullptr) 
        {
            head = node;
        } 
        else 
        {
            node->right = head;
            node->left = head->left;
            head->left->right = node;
            head->left = node;
        }
    }

FibonacciHeap* union_heap(FibonacciHeap* heap2) {
    FibonacciHeap* heap = new FibonacciHeap();
    heap->head = head;

    if(minNode->key < heap2->minNode->key)
    {
        heap->minNode = minNode;
    }
    else
    {
        heap->minNode = heap2->minNode;
    }

    FibonacciHeapNode* lastHeap = heap->head->left;
    FibonacciHeapNode* lastHeap2 = heap2->head->left;

    heap2->head->left = lastHeap;
    heap->head->left->right = heap2->head;
    heap->head->left = lastHeap2;
    heap->head->left->right = heap->head;

    heap->numberOfNodes = numberOfNodes + heap2->numberOfNodes;

    return heap;
}

    
FibonacciHeapNode* extract_min() 
{
    FibonacciHeapNode* z = minNode;
    if (z != nullptr) 
    {
        if (z->child != nullptr) 
        {
            vector<FibonacciHeapNode*> children = getElements(z->child);

            for (int i = 0; i < children.size(); ++i) {
                merge_with_root_list(children[i]);
                children[i]->parent = nullptr;
            }
        }
        remove_from_root_list(z);
        if (z == z->right) 
        {
            minNode = nullptr;
            head = nullptr;
        } 
        else 
        {
            minNode = z->right;
            consolidate();
        }
        numberOfNodes--;
    }
    return z;
}

void remove_from_root_list(FibonacciHeapNode* node)
{
    if(node == head)
    {
        head = node->right;
    }

    node->left->right = node->right;
    node->right->left = node->left;
    
}

std::vector<FibonacciHeapNode*> getElements(FibonacciHeapNode* node)
{
    std::vector<FibonacciHeapNode*> nodes;
    FibonacciHeapNode* curr = node;
    if(node!= nullptr)
    {
        nodes.push_back(node);
    
    curr = curr->right;
    while(curr!=node)
    {
        nodes.push_back(curr);
        curr = curr->right;
    }
    }

    return nodes;
}


void consolidate() 
{
    int size = (log(numberOfNodes) * 2);
    vector<FibonacciHeapNode*> A(size, nullptr);

    vector<FibonacciHeapNode*> nodes;
    nodes = getElements(head);

    for (int i = 0; i < nodes.size(); ++i) {

        FibonacciHeapNode* x = nodes[i];
        int degree = x->degree;

        while (A[degree] != nullptr) {
            FibonacciHeapNode* y = A[degree];

            if (x->key > y->key) 
            {
                FibonacciHeapNode* temp = x;
                x = y;
                y = temp;
            }

            heap_link(y, x);
            A[degree] = nullptr;
            degree++;
        }
        A[degree] = x;
    }

    for (int i = 0; i < size; ++i) 
    {
        if (A[i] != nullptr) {
            if (A[i]->key < minNode->key) 
            {
                minNode = A[i];
            }
        }
    }
}

void heap_link(FibonacciHeapNode* y, FibonacciHeapNode* x) {
    remove_from_root_list(y);
    y->left = y->right = y;
    merge_with_child_list(x,y);
    x->degree =+ 1;
    y->parent = x;
}

void merge_with_child_list(FibonacciHeapNode* parent, FibonacciHeapNode* node) {
    
    if(parent->child == nullptr)
    {
        parent->child = node;
    }
    else
    {
        node->right = parent->child->right;
        node->left = parent->child;
        parent->child->right->left = node;
        parent->child->right = node;
    }
}
};


int main(int argc,  char* argv[]) {
    FibonacciHeap* heap1 = new FibonacciHeap();
    FibonacciHeap* heap2 = new FibonacciHeap();
    int length = stoi(argv[1]);
    uniform_int_distribution<>dist(length);

    int i = 0;
    while (length>i)
    {
        int element1 = dist(gen)%(2*length+1);
        int element2 = dist(gen)%(2*length+1);
        heap1->insert(element1);
        cout<<"Inserted element: "<<element1<<" to heap1."<<endl;
        heap2->insert(element2);
        cout<<"Inserted element: "<<element2<<" to heap2."<<endl;
        i++;
    }
    cout<<endl;


    cout<<"Current minimum element in heap1: "<<heap1->minimum()->key<<endl;
    cout<<"Current minimum element in heap2: "<<heap2->minimum()->key<<endl;
    cout<<endl;


    heap1 = heap1->union_heap(heap2);

    cout<<"Minimum element after union: "<<heap1->minimum()->key<<endl;
    cout<<endl;

    for(int i=0;i<2*length;i++){
        cout<<"Deleted element: "<<heap1->extract_min()->key<<endl;
    }
    cout<<endl;

    if(heap1->isEmpty()){
        cout<<"Heap is empty"<<endl;
    }


    return 0;
}

