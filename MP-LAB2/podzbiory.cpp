#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

ofstream wy("wynik.txt");

void alg(const int n, const int k, const bool exact = false) {
  int *const a = new int[n + 1];
  int *const b = new int[n + 1];
  int c;

  for (int i = 1; i <= n; i++) {
    a[i] = 1;
    b[i] = 1;

    if(!exact)
      wy << a[i] << " ";
  }

  wy << endl;

  while (true) {
    c = n;

    while (a[c] == k || a[c] > b[c]) {
      c--;
    }

    if (c <= 1)
      break;

    a[c]++;

    for (int i = (c + 1); i <= n; i++) {
      a[i] = 1;
      b[i] = max(a[i - 1], b[i - 1]);
    }

    if(exact && (max(a[n], b[n]) != k)){
      for (int i = n, x = k; x > b[i]; i-- , x--) {
        a[i] = x;
        b[i] = x - 1;
      }
    }

    for (int i = 1; i <= n; i++) {
      wy << a[i] << " ";
    }

    wy << endl;
  }

  delete[] a;
  delete[] b;
}

//Funkcja do uproszczonego wywoływania funkcji, gdy nie interesuje nas 'k'
void alg(const int n){
  alg(n, n);
}

int main() {
  auto start = chrono::high_resolution_clock::now();
	auto stop = start;

	if (!wy.is_open()) {
		cout << "Nie udalo sie otworzyc pliku wynik.txt!";
		exit(-1);
	}

  cout << "Łukasz Konieczny LK4" << endl;
  cout << "LAB2 - generowanie podzialow zbioru \"n\" elementowego" << endl;
  cout << "----------------------------------------------" << endl;
  int n;
  cout << "Podaj n: ";
  cin >> n;

  cout << "Czy chcesz wygenerowac WSZYSTKIE podzialy? Jesli tak, wpisz 1, jesli nie, wpisz 0: ";
  int tmp;

  cin >> tmp;

  switch (tmp) {
    case 0 :{
      int k;
      cout << "Podaj k: ";
      cin >> k;

      cout << "Czy chcesz wygenerowac dokladnie k-blokowe podzialy? Jesli tak, wpisz 1, jesli nie, wpisz 0: ";
      cin >> tmp;

      switch (tmp)
      {
        case 0 :{
          start = chrono::high_resolution_clock::now();
          alg(n, k);
          break;
        }

        case 1 :{
          start = chrono::high_resolution_clock::now();
          alg(n, k, true);
          break;
        }

        default: {
          cout << "Niepoprawna wartosc!";
          exit(-1);
        }
      }
      break;
    }

    case 1 :{
      start = chrono::high_resolution_clock::now();
      alg(n);
      break;
    }
  
    default: {
      cout << "Niepoprawna wartosc!";
      exit(-1);
    }
  }

  wy.close();
  stop = chrono::high_resolution_clock::now();
  chrono::duration<double, std::milli> ms_double = stop - start;
  cout << "Wynik zapisano do pliku wynik.txt\n";
  cout << "Czas wykonania: " << ms_double.count() << " ms\n";

  return 0;
}