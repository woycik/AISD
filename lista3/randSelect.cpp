//Randomized Select
#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

random_device rd;
mt19937 gen(rd());


int comparisonCounter = 0;
int conversionCounter = 0;
int arrayLength;

void printArray(int *array,int pivot){
     for(int j=0;j<arrayLength;j++){
        if(j==pivot){
            cout<<"["<<array[j]<<"] ";
        }
        else{
        cout<<array[j]<<" ";
        }

    }
    cout<<endl;
}

int RandPartition(int *array,int first,int last){
    uniform_int_distribution<>dist(last-first);
    int randIndex = first + dist(gen)%(last - first);
    swap(array[last],array[randIndex]);

    int pivot = array[last];


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

int RandSelect(int *array,int p,int q,int k){
    if(p==q){
        return array[p];
    }
    int r = RandPartition(array,p,q);
    printArray(array,r);
    int i = r-p+1; 
    if(i==k){
        return array[r];
    }
    else if(i<k){
        return RandSelect(array,r+1,q,k-i);
    }
    else{
        return RandSelect(array,p,r-1,k);
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
        }while(array[i]<pivot);

        do{
            j--;
        }while(array[j]>pivot);
        if(i>=j){
            return j;
        }
        swap(array[i],array[j]);

    }
    
}

void quickSort(int *array,int first,int last){
    if(first<last){
        int j = partition(array,first,last);
        quickSort(array,first,j);
        quickSort(array,j+1,last);
    }
}

int main(int argc,char *argv[]){
    string input_line;
    int i=0;
    int k = stoi(argv[1]);
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
    arrayLength = length;
    printArray(array,-1);
    cout<<RandSelect(array,0,length-1,k)<<endl;
    cout<<"Liczba przestawien: "<<conversionCounter<<endl;
    cout<<"Liczba porownan: "<<comparisonCounter<<endl;
    quickSort(array,0,length-1);
    printArray(array,-1);
    delete []array;
    return 0;

}