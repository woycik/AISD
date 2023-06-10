#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

int comparisonCounter = 0;
int conversionCounter = 0;

void printArray(int *array,int length,int i){
     for(int j=0;j<length;j++){
        if(i==j){
            cout<<"["<<array[j]<<"] ";
        }
        else{
            cout<<array[j]<<" ";
        }
    }
    cout<<endl;
}

void insertionSort(int *array,int size){
    for(int i=1;i<size;i++){
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
        printArray(array,size,j+1);
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
    insertionSort(array,length);
    cout<<"Liczba przestawien: "<<conversionCounter<<endl;
    cout<<"Liczba porownan: "<<comparisonCounter<<endl;
    delete []array;
    return 0;

}
