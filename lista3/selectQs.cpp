//Select + quickSort

#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>
using namespace std;

random_device rd;
mt19937 gen(rd());

int comparisonCounter = 0;
int conversionCounter = 0;


void printArray(int *array,int length,int pivot){
    for(int j=0;j<length;j++){
        if(j==pivot){
            cout<<"["<<array[j]<<"] ";
        }
        else{
            cout<<array[j]<<" ";
        }
    }
    cout<<endl;
}

int partition(int *array,int first,int last,int pivot){
    int pivotIndex;
    for(pivotIndex = first;pivotIndex<=last;pivotIndex++){
        if(array[pivotIndex] == pivot){
            break;
        }
    }
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



int findMedian(int *array, int p, int q) {
    sort(array+p,array+q);
    int length = q - p + 1;
    return array[p+(length+1)/2];
}

int *divideParts(int *array,int p,int q,int n){
    
    int length = q-p+1;
    int *M = new int[n];
    for (int i = 0; i < n; i++) {
        if (length >= 5) {
            M[i] = findMedian(array, p + i * 5, p + i * 5 + 4);
        } else {
            M[i] = findMedian(array, p + i * 5, p + i * 5 + length -1 );
        }
        length = length - 5;
    }
    return M;
}

int select(int *array, int p, int q, int i) {
    if (p == q) {
        return array[p];
    }
    int length = q - p + 1;
    int n =(int) ceil((length) / 5.0);
    
    int *M = divideParts(array,p,q,n);

    int median = select(M, 0, n - 1, (n)/2);
    int pivot = partition(array, p, q, median); 

    comparisonCounter++;
    if (i == pivot+1) {
        return median;
    } else if (pivot+1 < i) {
        comparisonCounter++;
        return select(array, pivot+1, q, i );
    } else {
        comparisonCounter++;
        return select(array, p, pivot-1, i );
    }
    free(M);
}

int* copyArray(int *array,int first,int length){
    int *a = new int[length];
    for(int i =0;i<length;i++){
        a[i] = array[first + i];
    }
    return a;

}

void quickSort(int *array,int first,int last,int length){
    if(first<last){
        int* copiedArray =  copyArray(array,first,last - first + 1);
        int pivot = select(copiedArray,0,last - first ,(last-first+1)/2 );
        int j = partition(array,first,last,pivot);
        printArray(array,length,j);
        quickSort(array,first,j-1,length);
        quickSort(array,j+1,last,length);
        delete[] copiedArray;
    }
}





int main(int argc, char *argv[]) {
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
    printArray(array,length,-1);
    quickSort(array,0,length-1,length);
    cout<<"Liczba przestawien: "<<conversionCounter<<endl;
    cout<<"Liczba porownan: "<<comparisonCounter<<endl;
    printArray(array,length,-1);
    delete []array;
    return 0;
}