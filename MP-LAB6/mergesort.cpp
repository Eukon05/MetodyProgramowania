#include <iostream>
#include <random>
#include <chrono>
using namespace std;

void merge(int* arr, int left, int mid, int right){
    int maxIndex = right - left;
    int midIndex = mid - left;
    int* arrCopy = new int[maxIndex + 1];

    for(int i = 0; i <= maxIndex ; i++)
        arrCopy[i] = arr[left + i];

    int i = 0;
    int j = midIndex + 1 + i;
    int k = left;

    while(i <= midIndex && j <= maxIndex){
        if(arrCopy[i] <= arrCopy[j]){
            arr[k] = arrCopy[i];
            i++;
        }
        else {
            arr[k] = arrCopy[j];
            j++;
        }
        k++;
    }

    if(i == midIndex + 1){
        for(; j <= maxIndex; j++){
            arr[k] = arrCopy[j];
            k++;
        }
    }
    if(j == maxIndex + 1){
        for(; i <= midIndex; i++){
            arr[k] = arrCopy[i];
            k++;
        }
    }
}

void mergeSort(int* arr, int left, int right){
    if(left < right){
        int mid = (right + left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main(){
    cout << "Program do sortowania tablicy przez scalenie" << endl;
    cout << "Lukasz Konieczny | LK4 | LAB 6" << endl << endl;

    cout << "Podaj wielkosc tablicy: ";
    int input;
    cin >> input;

    if(input < 1){
        cout << "Nieprawidlowy rozmiar tablicy!";
        exit(-1);
    }

    int* arr = new int[input];
    srand(time(0));
    
    for(int i = 0; i < input; i++)
        arr[i] = rand() % 10;

    cout << endl << "Wylosowane liczby: " << endl;
    for(int i = 0 ; i < input; i++)
        cout << arr[i] << " ";

    cout << endl << endl;

    auto start = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, input - 1);
    auto stop = chrono::high_resolution_clock::now();

    cout << "Posortowane liczby: " << endl;
    for(int i = 0 ; i < input; i++)
        cout << arr[i] << " ";

    cout << endl << endl << "Sortowanie zajelo " << chrono::duration<double, std::milli>(stop - start).count() << " milisekund";
}