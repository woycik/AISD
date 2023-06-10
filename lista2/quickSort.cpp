#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

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

void quickSort(int *array,int first,int last,int length){
    if(first<last){
        int j = partition(array,first,last);
        printArray(array,length,j);
        quickSort(array,first,j,length);
        quickSort(array,j+1,last, length);
        
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
    quickSort(array,0,length-1,length);
    cout<<"Liczba przestawien: "<<conversionCounter<<endl;
    cout<<"Liczba porownan: "<<comparisonCounter<<endl;
    delete []array;
    return 0;

}
