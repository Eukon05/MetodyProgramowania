#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
using namespace std;

vector<int> wyznaczDzielnikiPierwsze(int x, bool wszystkie = false){
    vector<int> czynniki;
    int k = 2;
    int pierwiastek = sqrt(x);

    while(x > 1 && k <= pierwiastek){
        if(x % k == 0){
            czynniki.push_back(k);
            x /= k;

            while(x % k == 0){
                if(wszystkie)
                    czynniki.push_back(k);
                x /= k;
            }
        }

        k++;
    }

    return czynniki;
}

vector<int> generuj(int xmax){
    int m = xmax + 1;

    cout << "Wyznaczone \"m\": " << m << endl;

    vector<int> czynniki = wyznaczDzielnikiPierwsze(m);
    int c = 1;

    for(int cz : czynniki)
        c *= cz;
    c++;

    cout << "Wyznaczone \"c\": " << c << endl;

    int a = 1;
    czynniki = wyznaczDzielnikiPierwsze(m, true);

    for(int cz : czynniki)
        a *= cz;
    a++;

    cout << "Wyznaczone \"a\": " << a << endl;

    vector<int> wynik;
    int xn = 0;
    
    do{
        xn = (a*xn + c) % m;
        wynik.push_back(xn);
    }
    while(xn != 0);

    return wynik;
}


int main(){
    cout << "Algorytm generowania liczb pseudolosowych\n";
	cout << "Lukasz Konieczny | LK4 | LAB-12" << endl;

    int wybor;
    cout << "Czy chcesz zapisac wyniki do pliku? Wpisz 1 jesli tak: ";
    cin >> wybor;

    bool czyDoPliku = wybor == 1;

    cout << "Podaj maksymalna liczbe: ";
    cin >> wybor;

    cout << endl;

    vector<int> w = generuj(wybor);
    cout << endl << "Wygenerowano " << w.size() << " liczb:" << endl;

    for(int x : w)
        cout << x << " ";

    if(czyDoPliku){
        ofstream wy("wyjscie.txt");

        if(!wy.is_open()){
            cout << "Nie mozna otworzyc pliku wyjscie.txt!";
            exit(-1);
        }

        wy << "Wygenerowano " << w.size() << " liczb:" << endl;

        for(int x : w)
        wy << x << " ";
    }

    return 0;
}