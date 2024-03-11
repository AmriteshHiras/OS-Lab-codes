#include <iostream>
#include <algorithm>
using namespace std;

void selectionSort(int arr[], int n){
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(arr[i] > arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void bubbleSort(int arr[], int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int n){
    for(int i = 1; i < n; i++){
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int r){
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1];
    int R[n2];
    for(int i = 0; i < n1; i++){
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
    }
    int i, j = 0;
    int k = l;
    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r-l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void quickSort(int arr[], int l, int r){
    if(l < r){
        int pivot = arr[r];
        int i = l - 1;
        for(int j = l; j < r; j++){
            if(arr[j] <= pivot){
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[r];
        arr[r] = temp;
        quickSort(arr, l, i);
        quickSort(arr, i + 1, r);
    }
}

int main(){
    int n;
    cout << "Enter the size of the array you would like to sort: ";
    cin >> n;
    int arr[n];
    cout << "Enter the elements one by one:\n";
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    int choice;
    cout << "Enter the number before the sort you want:\n1. Selection sort\n2. Bubble sort\n3. Insertion sort";
    cout << "\n4. Merge sort\n5. Quick sort\n";
    cin >> choice;
    switch (choice){
        case 1:{
            selectionSort(arr, n);
            break;
        }
        case 2:{
            bubbleSort(arr, n);
            break;
        }
        case 3:{
            insertionSort(arr, n);
            break;
        }
        case 4:{
            mergeSort(arr, 0, n);
            break;
        }
        case 5:{
            quickSort(arr, 0, n);
            break;
        }
        default:{
            cout << "Invalid Input!";
            break;
        }
    }
    cout << "Sorted array: ";
    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
}