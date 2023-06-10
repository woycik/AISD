#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

class Element{
    public:
    int element;
    Element* next;
};

class Stack{
    public:
    Element* head;

    Stack();
    void push(int number);
    void pop();
};

Stack::Stack(){
        head = nullptr;
    }

void Stack::push(int number){
    Element *curr= (Element*)malloc(sizeof(Element));
    curr->element = number;
    curr->next = head;
    head = curr;
    printf("Added element %d\n",curr->element);
}
void Stack::pop(){
    if(head != nullptr){
        Element *curr= head;
        head = curr->next;  
        printf("Deleted element %d\n",curr->element);
        delete curr;
    }
    else{
        printf("Stack is empty\n");
    }
}   


int main(){
    Stack s = Stack();
    for(int i = 0;i<SIZE;i++){
        s.push(i);
    }
    for(int i = 0;i<SIZE;i++){
        s.pop();
    }
}
