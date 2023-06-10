#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

class Element{
    public:
    int element;
    Element* next;
};

class Queue{
    public:
    Element* head;

    Queue();
    void push(int number);
    void pop();

};

Queue::Queue(){
    head = nullptr;
}

void Queue::push(int number){
    Element *newNode= (Element*)malloc(sizeof(Element));
    newNode->element = number;
    newNode->next = nullptr;
    if(head == nullptr){
        head = newNode;
        printf("Added element: %d\n",head->element);
    }
    else{
        Element *curr= (Element*)malloc(sizeof(Element));
        curr = head;
        while(curr->next!=nullptr){
            curr = curr->next;
        }
        curr->next=newNode;
        printf("Added element: %d\n",curr->next->element);
    }
}

void Queue::pop(){
    Element *curr= head;
    if(curr != nullptr){
        head = curr->next;
        printf("Deleted element: %d\n",curr->element);
        delete curr;  
    }
    else{
        printf("Queue is empty\n");
    }
}   



int main(){
    Queue q = Queue();
    for(int i = 0;i<SIZE;i++){
        q.push(i);
    }
    for(int i = 0;i<SIZE+1;i++){
        q.pop();
    }
}
