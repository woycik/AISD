#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

random_device rd;
mt19937 gen(rd());

int comparisonCounter = 0;
int conversionCounter = 0;

void printArray(int *array,int length){
     for(int j=0;j<length;j++){
        cout<<array[j]<<" ";
    }
    cout<<endl;
}

void insertionSort(int *array,int first,int last){
    for(int i=first+1;i<=last;i++){
        int key = array[i];
        int j=i-1;
        while(j>=0 && array[j]>key){
            comparisonCounter++;
            conversionCounter++;
            array[j+1] = array[j];
            j--;
        }
        comparisonCounter++;
        conversionCounter++;
        array[j+1]=key;
    }

}



int partition(int *array,int first,int last){
    int p =floor((first+last)/2);
    int pivot = array[p];
    int i =first-1;
    int j = last +1;
    while(true){
        do{
            i++;
            comparisonCounter++;
        }while(array[i]<pivot);

        do{
            j--;
            comparisonCounter++;
        }while(array[j]>pivot);
        if(i>=j){
            return j;
        }
        conversionCounter++;
        swap(array[i],array[j]);

    }
    
}

void quickSortHybrid(int *array,int first,int last,int length){
    if(first<last){
        if(last-first<16){
            insertionSort(array,first,last);
            printArray(array,length);
        
        }
        else{
            int pivot;
            pivot = partition(array,first,last);
            printArray(array,length);
            quickSortHybrid(array,first,pivot,length);
            quickSortHybrid(array,pivot+1,last,length);
        }
        
    }
}






int main(int argc,char *argv[]){
    string input_line;
    int i=0;
    if(cin){
        getline(cin,input_line);
    }
    int length = stoi(input_line);
    int *array = new int[length];
    while(i<length) {
        getline(cin, input_line);
        array[i] = stoi(input_line);
        i++;
    }
    printArray(array,length);
    quickSortHybrid(array,0,length-1,length);
    cout<<"Liczba przestawien: "<<conversionCounter<<endl;
    cout<<"Liczba porownan: "<<comparisonCounter<<endl;
    delete []array;
    return 0;


}
