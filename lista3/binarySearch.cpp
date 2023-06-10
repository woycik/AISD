//Przeszukiwanie binarne
#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>
#include <chrono>

using namespace std::chrono;
using namespace std;


int comparisonCounter = 0;
int conversionCounter = 0;
int arrayLength;

int partition(int *array,int first,int last,int pivot){
    int i =first-1;
    for(int m = first;m<=last-1;m++){
        if(array[m]<pivot){
            i++;
            swap(array[i],array[m]);
        }
    }
    swap(array[i+1],array[last]);
    return i+1;
}

void quickSort(int *array,int first,int last){
    if(first<last){
        int pivot = array[last];
        int j = partition(array,first,last,pivot);
        quickSort(array,first,j-1);
        quickSort(array,j+1,last);
    }
}

void printArray(int *array,int key){
     for(int j=0;j<arrayLength;j++){
        if(j==key){
            cout<<"["<<array[j]<<"] ";
        }
        else{
        cout<<array[j]<<" ";
        }

    }
    cout<<endl;
}


int binarySearch(int *array, int p, int q, int key) {
    if (p <= q) {
        int n = (p + q) / 2;
        comparisonCounter++;
        printArray(array,n);
        if (array[n] == key) {
            return 1;
        } else if (array[n] > key) {
            comparisonCounter++;
            return binarySearch(array, p, n - 1, key);
        } else {
            comparisonCounter++;
            return binarySearch(array, n + 1, q, key);
        }
    }
    return 0;
}

int main(int argc,char *argv[]){
    if(argc >0){
        string input_line;
        int i=0;
        int k = stoi(argv[1]);
        if(cin){
            getline(cin,input_line);
        }
        arrayLength = stoi(input_line);
        int *array = new int[ arrayLength];
        while(i< arrayLength) {    
            getline(cin, input_line);
            array[i] = stoi(input_line);
            i++;
        }
        quickSort(array,0, arrayLength-1);

        auto start = high_resolution_clock::now();
        cout<<binarySearch(array,0, arrayLength-1,k)<<endl;
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout<<"Czas "<<duration.count()<<" mikro sekund."<<endl;
        cout<<"Liczba porownan: "<<comparisonCounter<<endl;
        
        printArray(array,-1);
        delete []array;
        return 0;
    }

}