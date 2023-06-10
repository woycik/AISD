#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <string>
using namespace std;

int comparisonCounter = 0;
int conversionCounter = 0;

void printArray(int *array,int length){
     for(int j=0;j<length;j++){
        cout<<array[j]<<" ";
    }
    cout<<endl;
}

void merge(int *array,int first,int mid,int last){
    int m=0;
    int k=first;
    int j=0;

    int index1 = mid-first+1;
    int index2=last-mid;

    int dup1[index1];
    int dup2[index2];



    for(int i=0;i<index1;i++){
        dup1[i]=array[first+ i];
    }

    for(int i=0;i<index2;i++){
        dup2[i] = array[i+mid+1];
    }
    while(m<index1 && j<index2){

        comparisonCounter++;
        if(dup1[m]<=dup2[j]){
            conversionCounter++;
            array[k]=dup1[m];
            m++;
        }
        else {
            conversionCounter++;
            array[k] = dup2[j];
            j++;
        }
        k++;
    }


    while(m<index1){
        conversionCounter++;
        array[k]=dup1[m];
        k++;
        m++;
    }

    while(j<index2){
        conversionCounter++;
        array[k]=dup2[j];
        j++;
        k++;
    }


}

void mergeSort(int *array,int first,int last,int length){
    if(first<last){
        int mid = floor((first + last)/2);    
        mergeSort(array,first,mid,length);
        mergeSort(array,mid+1,last,length);
        merge(array,first,mid,last);
        printArray(array,length);
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
    mergeSort(array,0,length-1,length);
    cout<<"Liczba przestawien: "<<conversionCounter<<endl;
    cout<<"Liczba porownan: "<<comparisonCounter<<endl;
    delete []array;
    return 0;

}
