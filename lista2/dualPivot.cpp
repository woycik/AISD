#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

random_device rd;
mt19937 gen(rd());

int comparisonCounter = 0;
int conversionCounter = 0;

void printArray(int *array,int length,int pivot1,int pivot2){
     for(int j=0;j<length;j++){
        if(j==pivot1 || j == pivot2){
            cout<<"["<<array[j]<<"] ";
        }
        else{
        cout<<array[j]<<" ";
        }

    }
    cout<<endl;
}




int partition(int *array,int first,int last,int *rightPivot){
    comparisonCounter++;
    if(array[first]>array[last]){
        conversionCounter++;
        swap(array[first],array[last]);
    }
    int p = array[first];
    int q = array[last];
    int i =first+1;
    int k= last -1;
    int j = i;
    int d =0;
    while(j<=k){
        if(d>=0){
            comparisonCounter++;
            if(array[j]<p){
                conversionCounter++;
                swap(array[i],array[j]);
                i++;
                j++;
                d++;
            }
            else {
                comparisonCounter++;
                if(array[j]<q){
                    j++;
                }
                else{
                    conversionCounter++;
                    swap(array[j],array[k]);
                    k--;
                    d--;
                }
            }

        }
        else{
            comparisonCounter++;
            if(array[k]>q){
                k--;
                d--;
            }
            else{
                comparisonCounter++;
                if(array[k]<p){
                    conversionCounter++;
                    int tmp = array[k];
                    array[k] = array[j];
                    array[j]=array[i];
                    array[i] = tmp;
                    i++;
                    d--;
                }
                else{
                    conversionCounter++;
                    swap(array[j],array[k]);
                }
                j++;
            }
        }
    }
    conversionCounter+=2;
    swap(array[first],array[i-1]);
    swap(array[last],array[k+1]);
    *rightPivot = k+1;
    return i-1;
}

void quickSort(int *array,int first,int last,int length){
    if(first<last){
        int rightPivot,leftPivot;
        leftPivot = partition(array,first,last,&rightPivot);
        printArray(array,length,leftPivot,rightPivot);
        quickSort(array,first,leftPivot-1,length);
        quickSort(array,leftPivot+1,rightPivot-1,length);
        quickSort(array,rightPivot+1,last, length);
        
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
    printArray(array,length,length,length);
    cout<<"Liczba przestawien: "<<conversionCounter<<endl;
    cout<<"Liczba porownan: "<<comparisonCounter<<endl;
    delete []array;
    return 0;
}
