#include <iostream>
#include <fstream>
using namespace std;

struct Przedmiot{
    int cena;
    int waga;
};

void plecakuj(Przedmiot* przedmioty, int n, int c){
    // Macierz kosztów o wierszach dla danego elementu i kolumnach dla danej pojemności
    int** mPD = new int*[n + 1];
    for(int i = 0; i <= n; i++){
        mPD[i] = new int[c + 1];
    }

    // Dzięki użyciu dodatkowego wiersza wypełnionego zerami, możemy pozbyć się osobnej pętli dla piewrszego przedmiotu
    for(int i = 0; i <= c; i++){
        mPD[0][i] = 0;
    }

    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= c; j++){
            if(przedmioty[i - 1].waga > j){
                mPD[i][j] = mPD[i-1][j];
            }
            else{
                mPD[i][j] = max(mPD[i-1][j], mPD[i - 1][j - przedmioty[i - 1].waga] + przedmioty[i - 1].cena);
            }
        }
    }
    cout << "Uzyskana tabela kosztow: " << endl;;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= c; j++){
            cout << mPD[i][j] << "\t";
        }
        cout << endl;
    }

    cout << endl << endl;
    cout << "Maksymalna uzyskana wartosc plecaka: " << mPD[n][c] << endl;
    cout << "Elementy znajdujace sie w plecaku: ";

    int i = n, j = c;
    while (i != 0){
        if(mPD[i][j] > mPD[i - 1][j]){
            cout << i << ", ";
            j -= przedmioty[i - 1].waga;
        }
        i--;
    }
}

void sprawdzLiczbe(int n){
    if(n < 1){
        cout << "Niepoprawna wartosc!";
        exit(-1);
    }
}

void wczytajZPliku(){
    ifstream we("wejscie.txt");

    if(!we.is_open()){
        cout << "Nie mozna otworzyc pliku wejsciowego!";
        exit(-1);
    }

    int n, c;
    we >> n;
    sprawdzLiczbe(n);

    we >> c;
    sprawdzLiczbe(c);

    int p, w;
    Przedmiot* przedmioty = new Przedmiot[n];
    for(int i = 0; i < n; i++){
        we >> p;
        sprawdzLiczbe(p);

        we >> w;
        sprawdzLiczbe(w);
        przedmioty[i] = {p, w};
    }

    we.close();
    plecakuj(przedmioty, n, c);
}

void wczytajZKlawiatury(){
    int n, c, p, w;
    cout << "Podaj ilosc przedmiotow: ";
    cin >> n;
    sprawdzLiczbe(n);

    cout << "Podaj pojemnosc plecaka: ";
    cin >> c;
    sprawdzLiczbe(c);

    Przedmiot* przedmioty = new Przedmiot[n];
    for(int i = 0; i < n; i++){
        cout << "Podaj wartosc elementu: ";
        cin >> p;
        sprawdzLiczbe(p);

        cout << "Podaj wage elementu: ";
        cin >> w;    
        sprawdzLiczbe(w);

        przedmioty[i] = {p, w};
    }

    cout << endl;
    plecakuj(przedmioty, n, c);
}

int main(){
    cout << "Program do rozwiazywania problemu plecakowego dyskretnego" << endl;
    cout << "Lukasz Konieczny | LK4 | LAB 8" << endl << endl;
    cout << "Jesli chcesz podac dane z klawiaury, wpisz 1. W przeciwnym wypadku sprobujemy pobrac je z pliku wejscie.txt" << endl;
    cout << "Wpisz swoj wybor: ";

    int wybor;
    cin >> wybor;
    cout << endl;

    if(wybor == 1)
        wczytajZKlawiatury();
    else
        wczytajZPliku();
}