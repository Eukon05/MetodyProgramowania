#include <iostream>
#include <chrono>
#include <random>
using namespace std;

void restoreHeapOrder(int* dataset, int stopPos, bool max = true){
    for(int i = 1; i < stopPos; i++){
        int k = i;
        int j = (i - 1) / 2;

        while(j >= 0){
            if((dataset[k] > dataset[j] && max) || (dataset[k] < dataset[j] && !max))
                swap(dataset[k], dataset[j]);
            else
                break;
            
            k = j;
            j = (j - 1) / 2;
        }
    }
}

void heapSort(int* dataset, int datasetSize, bool ascending = true){
    for(int i = 0; i < datasetSize; i++){
        restoreHeapOrder(dataset, datasetSize - i, ascending);
        swap(dataset[0], dataset[datasetSize - 1 - i]);
    }
}

int main(){
    cout << "Program do sortowania tablicy przez kopcowanie" << endl;
    cout << "Lukasz Konieczny | LK4 | LAB 7" << endl << endl;

    int input;
    cout << "Czy chcesz posortowac liczby NIEROSNACO (wpisz 1) CZY NIEMALEJACO (wpisz dowolna liczbe): ";
    cin >> input;

    bool czyNiemalejaco = input != 1;

    cout << "Podaj wielkosc tablicy: ";
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
    heapSort(arr, input, czyNiemalejaco);
    auto stop = chrono::high_resolution_clock::now();

    cout << endl << "Posortowane liczby: " << endl;
    for(int i = 0 ; i < input; i++)
        cout << arr[i] << " ";

    cout << endl << endl << "Sortowanie zajelo " << chrono::duration<double, std::milli>(stop - start).count() << " milisekund";
}