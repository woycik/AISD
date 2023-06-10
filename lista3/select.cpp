#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>
using namespace std;



int comparisonCounter = 0;
int conversionCounter = 0;


void printArray(int *array,int pivot,int length){
    for(int i=0;i<length;i++){
        if(i==pivot){
            cout<<"["<<array[i]<<"] ";
        }
        else{
            cout<<array[i]<<" ";
        }
    }
    cout<<endl;
}



int partition(int *array,int first,int last,int pivot){
    int pivotIndex;
    for(pivotIndex = first;pivotIndex<=last;pivotIndex++){
        comparisonCounter++;
        if(array[pivotIndex] == pivot){
            break;
        }
    }
    conversionCounter++;
    swap(array[last],array[pivotIndex]);
    int i =first-1;
    for(int m = first;m<=last-1;m++){
        comparisonCounter++;
        if(array[m]<pivot){
            i++;
            conversionCounter++;
            swap(array[i],array[m]);
        }
    }
    conversionCounter++;
    swap(array[i+1],array[last]);
    return i+1;
    
}

void quickSort(int *array,int first,int last){
    if(first<last){
        int i = partition(array,first,last,array[last]);
        quickSort(array,first,i-1);
        quickSort(array,i+1,last);
        
    }
}

int findMedian(int *array, int p, int q) {
    quickSort(array,p,q);
    int length = q - p + 1;
    return array[p+(length+1)/2];
}

int *divideParts(int *array,int p,int q,int n,int div){
    
    int length = q-p+1;
    int *M = new int[n];
    for (int i = 0; i < n; i++) {
        if (length >= div) {
            M[i] = findMedian(array, p + i * div, p + i * div + div-1);
        } else {
            M[i] = findMedian(array, p + i * div, p + i * div + length -1 );
        }
        length = length - div;
    }
    return M;
}

int select(int *array, int p, int q, int i,int div,int arrayLength) {
    if (p == q) {
        return array[p];
    }
    int length = q - p + 1;
    int n =(int) ceil((length) / (float)div);
    
    int *M = divideParts(array,p,q,n,div);

    int median = select(M, 0, n - 1, n/2,div,n);
    int pivot = partition(array, p, q, median);

    printArray(array,pivot,arrayLength);

    if (i == pivot+1) {
        return median;
    } else if (pivot+1 < i) {
        return select(array, pivot+1, q, i, div, arrayLength);
    } else {
        return select(array, p, pivot-1, i, div, arrayLength);
    }
    free(M);
}

int main(int argc, char *argv[]) {
    if(argc>1){
        string input_line;
        int i=0;
        int k = stoi(argv[1]);
        int div = stoi(argv[2]);
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
        
        cout<<select(array,0,length-1,k,div,length)<<endl;
        cout<<"Liczba przestawien: "<<conversionCounter<<endl;
        cout<<"Liczba porownan: "<<comparisonCounter<<endl;
    
        quickSort(array,0,length-1);
        printArray(array,-1,length);
        delete []array;
        return 0;
    }
}