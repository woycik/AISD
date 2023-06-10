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


void printArray(int *array,int length,int pivot1,int pivot2){
    for(int j=0;j<length;j++){
        if(j==pivot1 || j==pivot2){
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




int findMedian(int *array, int p, int q) {
    sort(array+p,array+q);
    int length = q - p + 1;
    return array[p+(length)/2];
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
    if (i == pivot+1) {
        return median;
    } else if (pivot+1 < i) {
        return select(array, pivot+1, q, i );
    } else {
        return select(array, p, pivot-1, i );
    }
    free(M);
}

std::pair<int,int> partitionQS(int *array,int first,int last){
    int left_pivotIndex;
    int right_pivotIndex;

    int length = last - first + 1;

    int leftArray[3];
    leftArray[0] = array[first];
    leftArray[1] = array[first + length/6];
    leftArray[2] = array[first + length/3];

    int rightArray[3];
    rightArray[0] = array[first + 4*(length/6)];
    rightArray[1] = array[first + 2*(length/3)];
    rightArray[2] = array[last];
    
    int leftPivot = select(leftArray,0,2,2);
    int rightPivot = select(rightArray,0,2,2);


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

    
    swap(array[last],array[right_pivotIndex]);
    swap(array[first],array[left_pivotIndex]);

    if(array[last] < array[first]){
        swap(array[first],array[last]);
    }

    int i =first;
    int n = last-1;
    int p = array[first];
    int q = array[last];
    int smallerNumbers=0;
    int greaterNumbers =0;
    int j=first+1;
    while(j<=n){
        comparisonCounter++;
        if(greaterNumbers>smallerNumbers ){
            comparisonCounter++;
            if(array[j]>= q){
                greaterNumbers++;
                while(array[n]>q && j<n){
                    comparisonCounter++;
                    n--;
                }
                comparisonCounter++;
                conversionCounter++;
                swap(array[n],array[j]);
                n--;
                comparisonCounter++;
                if(array[j]<p){
                    i++;
                    conversionCounter++;
                    swap(array[j],array[i]);
                }
            }
            else if(array[j]< p){
                smallerNumbers++;
                comparisonCounter++;
                conversionCounter++;
                i++;
                swap(array[i],array[j]);
            }
            else{comparisonCounter++;}
            
        }
        else{
            comparisonCounter++;
            if(array[j]<p){
                smallerNumbers++;
                conversionCounter++;
                i++;
                swap(array[i],array[j]);

            }
            else if(array[j]> q){
                greaterNumbers++;
                while(array[n]>q && j<n){
                    comparisonCounter++;
                    n--;
                }
                comparisonCounter++;
                swap(array[n],array[j]);
                conversionCounter++;
                n--;
                comparisonCounter++;
                if(array[j]<p){
                    i++;
                    swap(array[j],array[i]);
                    conversionCounter++;
                }
            }
            else{comparisonCounter++;}
        }
        j++;
    
    }
    n++;

    swap(array[first],array[i]);
    swap(array[last],array[n]);

    return make_pair(i,n);
}

void quickSortForSelect(int *array,int first,int last){
    if(first<last){
        int pivot = array[last];
        int j = partition(array,first,last,pivot);
        quickSortForSelect(array,first,j-1);
        quickSortForSelect(array,j+1,last);
    }
}



void quickSort(int *array,int first,int last,int length){
    if(first<last){
        std::pair<int,int> index = partitionQS(array,first,last);
        int leftPivot = index.first;
        int rightPivot = index.second;
        printArray(array,length,leftPivot,rightPivot);
        quickSort(array,first,leftPivot - 1,length);
        quickSort(array,leftPivot + 1,rightPivot -1,length);
        quickSort(array,rightPivot + 1,last,length);

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

    quickSort(array,0,length-1,length);
    cout<<"Liczba przestawien: "<<conversionCounter<<endl;
    cout<<"Liczba porownan: "<<comparisonCounter<<endl;
    printArray(array,length,-1,-1);
    delete []array;
    return 0;  
    }
            
     
    
    
