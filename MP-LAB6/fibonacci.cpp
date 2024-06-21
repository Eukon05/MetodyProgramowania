#include <iostream>
#include <chrono>
using namespace std;

long long fibRek(int n){
    if (n == 0 || n == 1)
        return n;

    return fibRek(n - 1) + fibRek(n - 2);
}

long long fibIter(int n){
    if (n == 0 || n == 1)
        return n;

    long long first = 0, second = 1, tmp;

    for (int i = 2; i <= n; i++){
        tmp = first + second;
        first = second;
        second = tmp;
    }

    return second;
}

int main(){
    cout << "Program do wyznaczania wartosci n-wyrazu ciagu Fibonacciego" << endl;
    cout << "Lukasz Konieczny | LK4 | LAB 6" << endl << endl;

    cout << "Jesli chcesz skorzystac z rekurencji, wpisz 1: ";
    int input;
    cin >> input;

    bool useRec = input == 1;

    cout << "Podaj n: ";
    cin >> input;

    long long result;
    auto start = chrono::high_resolution_clock::now();
    decltype(start) stop;

    if(useRec)
        result = fibRek(input);
    else 
        result = fibIter(input);

    stop = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> ms_double = stop - start;

    cout << "Wynik: " << result << endl;
    cout << "Program wykonal sie w "<< ms_double.count() << " milisekundy";
}