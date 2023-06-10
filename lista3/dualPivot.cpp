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
            swap(array[i],array[m]);
        }
    }
    swap(array[i+1],array[last]);
    return i+1;
    
}

std::pair<int,int> partitionQS(int *array,int first,int last,int leftPivot, int rightPivot){
    int left_pivotIndex;
    int right_pivotIndex;


    for(left_pivotIndex = first;left_pivotIndex<=last;left_pivotIndex++){
        if(array[left_pivotIndex] == leftPivot){
            break;
        }
    }
    for(right_pivotIndex = first;right_pivotIndex<=last;right_pivotIndex++){
        if(array[right_pivotIndex] == rightPivot){
            break;
        }
    }

    
    //zamiana indeksów z pivotami na pierwsze i ostatnie miejsce w tablicy
    swap(array[last],array[right_pivotIndex]);
    swap(array[first],array[left_pivotIndex]);

    int j =first+1;
    int g = last-1;
    int k = first +1;
    while(k<=g){
        comparisonCounter++;
        if(array[k]<leftPivot){
            swap(array[j],array[k]);
            j++;
        }
        else if(array[k]>=rightPivot){
            while(array[g]> rightPivot && k<g){
                g--;
            }
            swap(array[k],array[g]);
            g--;
            if(array[k] < leftPivot){
                swap(array[j],array[k]);
                j++;
            }
        }
        k++;
    }
    j--;
    g++;

    swap(array[first],array[j]);
    swap(array[last],array[g]);

    return make_pair(j,g);
}

void quickSortForSelect(int *array,int first,int last){
    if(first<last){
        int pivot = array[last];
        int j = partition(array,first,last,pivot);
        quickSortForSelect(array,first,j-1);
        quickSortForSelect(array,j+1,last);
    }
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
    int pivot = partition(array, p, q, median); //jesli jest =3 to to 3 elementy są mniejsze niż pivot czyli jest to 4 statystyka pozycyjna

    if (i == pivot+1) {
        return median;
    } else if (pivot+1 < i) {
        return select(array, pivot+1, q, i );
    } else {
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

void quickSort(int *array,int first,int last){
    if(first<last){
        float length = last-first+1;
        int oneThird = ((length)/4.0);
        int secThird = 3*((length)/4.0);
        int* copiedArray =  copyArray(array,first,last - first + 1);
        int rightPivot = select(copiedArray,0,last - first ,secThird);
        //int* copiedArray2 =  copyArray(array,first,last - first + 1);
        int leftPivot = select(copiedArray,0,last - first ,oneThird);
        std::pair<int,int> index = partitionQS(array,first,last,leftPivot,rightPivot);
        quickSort(array,first,index.first - 1);
        quickSort(array,index.first + 1,index.second -1);
        quickSort(array,index.second + 1,last);
        delete[] copiedArray;
        //delete[] copiedArray2;
    }
}





int main(int argc, char *argv[]) {
    int length = 10;
    int *array = new int[length];
    uniform_int_distribution<>dist(0, 2*length);
    for(int i = 0; i < length; i++) {
        array[i] = dist(gen);
    }
    printArray(array, length, -1);
    quickSort(array, 0, length-1);
    printArray(array, length, -1);
    delete[] array;
    return 0;
}