#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
using namespace std;

#define SIZE 10000



class Element{
    public:
    int element;
    Element* next;

};

class List{

    public:
    Element* head;
    int size;

    List();
    void timeMesure(int index);
    void pushBack( int number);
    void popBack();
    void showAll();
    Element* getElement(int num);
    void merge(List* list);



};

    List::List(){
        head = nullptr;
        size = 0;
    }





    void List::pushBack( int number){

        Element *newNode= (Element*)malloc(sizeof(Element));
        newNode->element = number;
        newNode->next = nullptr;
        if(head==nullptr){
            head = newNode;
        }
        else{
            Element *curr= head;
            while(curr->next !=nullptr){
                curr = curr->next;
            }
            curr->next = newNode;
        }  
        size++;

    }



void List::popBack(){
    Element *curr= (Element*)malloc(sizeof(Element));
    curr = head;
    if(head!=nullptr){
        if(curr->next == nullptr){
            head = nullptr;
            delete curr;
        }

        else{
            while(curr->next->next!=nullptr){
                curr = curr->next;
            }
            Element *deleteElement = curr->next;
            curr->next = nullptr; 
            delete deleteElement;
        }
        size--;
    }

    else{
        cout<<"Lista jest pusta"<<endl;
    }

}



void List::showAll(){
    Element *curr= head;
    while(curr!= nullptr){
        printf("%d\n",curr->element);
        curr=curr->next;

    }

}





Element* List::getElement(int num){
    if(num<=size){

        Element *curr= head;
        for(int i=1;i<num;i++){
            curr=curr->next;
        }
        return curr;
    }
    return nullptr;

}







void List::merge(List* list){

    if(head==nullptr){
        head = list->head;
    }

    else{
        Element *curr= head;
        for(int i =1;i<size;i++){
            curr=curr->next;
        }
        curr->next=list->head;
        }
    size = size + list->size;



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

