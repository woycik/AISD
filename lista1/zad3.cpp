#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <cmath>
using namespace std;

#define SIZE 10000



class Element{

    public:
    int element;
    Element* next;
    Element* prev;

};



class List{

    public:
    Element* head;
    int size;

    List();
    void pushBack( int number);
    void popBack();
    void showAll();
    Element* getElement(int num);
    void merge(List* list);
    void timeMesure(int index);

};



List::List(){
    head = nullptr;
    size = 0;

}



void List::pushBack( int number){

    Element *curr= (Element*)malloc(sizeof(Element));

    if(head==nullptr){
        curr->element = number;
        curr->prev = curr;
        curr->next = curr;
        head = curr;

    }

    else{

        Element *last = (Element*)malloc(sizeof(Element));
        last = head->prev;
        curr->element = number;
        curr->next = head;
        curr->prev = last;
        last->next = curr;
        head->prev = curr;
    }  
    size++;  
}



void List::popBack(){

    if(head!=nullptr){
        Element *last= (Element*)malloc(sizeof(Element));
        Element *deleteElement = (Element*)malloc(sizeof(Element));
        Element *beforeLast = (Element*)malloc(sizeof(Element));
        last=head->prev;
        beforeLast = last->prev;
        deleteElement = last;
        head->prev = beforeLast;
        beforeLast->next = head; 
        if(size ==1){
            head = nullptr;
        }
        delete deleteElement;
        size--;

    }

    else{
        cout<<"Lista jest pusta"<<endl;

    }

}



void List::showAll(){
    Element *curr= head;
    for(int i=0;i<size;i++){
        if(curr != nullptr){
            printf("%d\n",curr->element);
            curr=curr->next;

        }

    }

}


Element* List::getElement(int num){

    if(head!=nullptr){
        int half = floor(size/2);
        Element *curr= head;
        if(num<=half){
            for(int i=1;i<num;i++){
                curr=curr->next;
            }

        }

        else{
            curr = curr->prev;
            num = size - num+1;
            for(int i=1;i<num;i++){
                curr=curr->prev;
            }

        }

        return curr;
    }
    return nullptr;

}







void List::merge(List* list){

    if(head ==nullptr){
        head = list->head;
    }

    else{
        Element *currHead= (Element*)malloc(sizeof(Element));
        Element *listhead= (Element*)malloc(sizeof(Element));
        Element *currTail= (Element*)malloc(sizeof(Element));
        Element *listTail= (Element*)malloc(sizeof(Element));

        if(list->head!=nullptr){

            currHead = head;
            listhead = list->head;

            currTail = currHead -> prev;
            listTail = listhead -> prev;
            currTail->next=listhead; 
            listhead->prev = currTail;
            listTail->next = currHead; 
            currHead->prev=listTail; 
            size = size + list->size;

        }

        }

    }



void List::timeMesure(int index){

    if(head!= nullptr){
        double avg = 0;
        for(int i = 0;i<100;i++){
            auto start = chrono::high_resolution_clock::now();
            getElement(index);
            auto stop1 = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(stop1-start);
            avg = avg + duration.count();
        }
        cout<<"Średni czas dostępu do elementu "<<index<<" wynosi: "<<avg/100<<" micro sekund"<<endl;
    }
}





int main(){

    List l = List();
    List l1 = List();
    List l2 = List();

    for(int i = 0;i<SIZE;i++){
        l.pushBack(rand());
    }

    l1.pushBack(1);
    l1.pushBack(2);


    l2.pushBack(3333);
    l2.pushBack(6666);
    l1.merge(&l2);


    cout<<"Lista l1 zawiera elementy 1 i 2, natomiast l2 - elementy 3333 i 6666."
    <<endl<<"Po wykonaniu funkcji merge listy zostają połączone."
    <<endl<<"Poniżej zostaje ukazane zostały wszystkie elementy po połączeniu."<<endl;
    l1.showAll();

    l.timeMesure(2);
    l.timeMesure(9999);
    l.timeMesure(rand()%l.size);

}

