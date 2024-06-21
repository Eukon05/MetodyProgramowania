#include <iostream>
#include <random>
#include <fstream>
using namespace std;

void rmat(int n, int gestosc, int a, int b, int c, bool czySkierowany, bool czyWazony){
    srand(time(0));

    int rozmiar = pow(2, n);
    int iloscKrawedzi = (long)(gestosc/100. * rozmiar * rozmiar);
    int aktualnaIloscKrawedzi = 0, rozmiarCwiartki = rozmiar;
    int x, y, wyborCwiartki;

    int** tablicaSasiedztwa = new int*[rozmiar];
    for (int i = 0; i < rozmiar; i++){
        tablicaSasiedztwa[i] = new int[rozmiar];
        for(int j = 0; j < rozmiar; j++){
            tablicaSasiedztwa[i][j] = 0;
        }
    }

    do{
        x = 0;
        y = 0;

        do{
            rozmiarCwiartki /= 2;
            wyborCwiartki = rand() % 100 + 1;

            if (a < wyborCwiartki && wyborCwiartki <= a + b)
                x += rozmiarCwiartki;

            else if (a + b < wyborCwiartki && wyborCwiartki <= a + b + c)
                y += rozmiarCwiartki;

            else if (a + b + c < wyborCwiartki && wyborCwiartki <= 100){
                x += rozmiarCwiartki;
                y += rozmiarCwiartki;
            }
        }
        while (rozmiarCwiartki != 1);

        if(tablicaSasiedztwa[x][y] == 0){
            tablicaSasiedztwa[x][y] = 1;
            aktualnaIloscKrawedzi++;

            if(!czySkierowany && x != y){
                tablicaSasiedztwa[y][x] = 1;
                aktualnaIloscKrawedzi++;
            }
        }
        else if (czyWazony){
            tablicaSasiedztwa[x][y]++;

            if(!czySkierowany && x != y)
                tablicaSasiedztwa[y][x]++;
        }

        rozmiarCwiartki = rozmiar;
    }
    while(aktualnaIloscKrawedzi < iloscKrawedzi);

    for(int i = 0; i < rozmiar; i++){
        for(int j = 0; j < rozmiar; j++)
            cout << tablicaSasiedztwa[i][j] << " ";
        cout  << endl;
    }
}

void losowy(int ileWezlow, int ileKrawedzi, bool czySkierowany, bool czyWazony){
    srand(time(0));
    int** tablicaSasiedztwa = new int*[ileWezlow];

    for (int i = 0; i < ileWezlow; i++){
        tablicaSasiedztwa[i] = new int[ileWezlow];
        for(int j = 0; j < ileWezlow; j++)
            tablicaSasiedztwa[i][j] = 0;
    }

    int ki, kj, waga;
    for(int i = 0; i<ileKrawedzi; i++){
        do {
            ki = rand() % ileWezlow;
            kj = rand() % ileWezlow;
        }
        while (tablicaSasiedztwa[ki][kj] != 0);

        waga = 1;

        if(czyWazony)
            waga = rand() % 9 + 1;

        tablicaSasiedztwa[ki][kj] = waga;

        if(!czySkierowany)
            tablicaSasiedztwa[kj][ki] = waga;
    }

    for(int i = 0; i < ileWezlow; i++){
        for(int j = 0; j < ileWezlow; j++)
            cout << tablicaSasiedztwa[i][j] << " ";
        cout  << endl;
    }
}

bool czyProcent(int liczba){
    if(liczba <= 0 || liczba > 100)
        return false;
    return true;
}

int wczytajProcent(){
    int x;
    cin >> x;

    if(!czyProcent(x)){
        cout << "Niepoprawny procent!";
        exit(-1);
    }

    return x;
}

void menuLosowy(){
    int wezly, krawedzie, wybor;
    bool skierowany, wazony;

    cout << "Podaj ilosc wezlow: ";
    cin >> wezly;

    if(wezly <= 1){
        cout << "Nieprawidlowa ilosc wezlow!";
        exit(-1);
    }

    cout << "Podaj ilosc krawedzi: ";
    cin >> krawedzie;

    if(krawedzie > wezly * wezly){
        cout << "Nieprawidlowa ilosc krawedzi!";
        exit(-1);
    }

    cout << "Czy graf ma byc skierowany? Wpisz 1 jesli tak: ";
    cin >> wybor;
    skierowany = wybor == 1;

    cout << "Czy graf ma byc wazony? Wpisz 1 jesli tak: ";
    cin >> wybor;
    wazony = wybor == 1;

    cout << endl;
    losowy(wezly, krawedzie, skierowany, wazony);
}

void menuRmat(){
    int n, gestosc, a, b, c, wybor;
    bool czyWazony, czySkierowany;
    cout << "Podaj N: ";
    cin >> n;

    if(n <= 0){
        cout << "Nieprawidlowe N!";
        exit(-1);
    }

    cout << "Podaj gestosc (w procentach!): ";
    gestosc = wczytajProcent();

    cout << "Podaj prawdopodobienstwo cwiartki a (w procentach!): ";
    a = wczytajProcent();

    cout << "Podaj prawdopodobienstwo cwiartki b (w procentach!): ";
    b = wczytajProcent();

    cout << "Podaj prawdopodobienstwo cwiartki c (w procentach!): ";
    c = wczytajProcent();

    if(a + b + c >= 100){
        cout << "Niepoprawna suma prawdopodobienstw!";
        exit(-1);
    }

    cout << "Na bazie wprowadzonych danych, prawdopodobienstwo d wynosi " << 100 - a - b - c << "%" << endl;

    cout << "Czy graf ma byc skierowany? Wpisz 1 jesli tak: ";
    cin >> wybor;
    czySkierowany = wybor == 1;

    cout << "Czy graf ma byc wazony? Wpisz 1 jesli tak: ";
    cin >> wybor;
    czyWazony = wybor == 1;

    cout << endl;
    rmat(n, gestosc, a, b, c, czySkierowany, czyWazony);
}

int main(){
    cout << "Lukasz Konieczny LK4 LAB4" << endl;
    cout << "Program generujacy macierze sasiedztwa grafow" << endl;

    cout << "MENU: "<< endl << "1. Algorytm losowego tworzenia grafu" << endl << "2. Algorytm R-MAT" << endl;
    cout << "Wpisz swoj wybor: ";
    int wybor;

    cin >> wybor;
    switch(wybor){
        case 1: {
            menuLosowy();
            break;
        }
        case 2 :{
            menuRmat();
            break;
        }
        default: {
            cout << "Nieprawidlowy wybor!";
            exit(-1);
        }
    }

    return 0;
}