#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

ofstream wy("wynik.txt");

void getSetSizeFromConsole(int& n) {
	cout << "Podaj wielkosc zbioru: ";
	cin >> n;

	if (n < 1) {
		cout << "Niepoprawna wielkosc zbioru!";
		exit(-1);
	}
}

void lexicographical(const int n, const int k) {
	int* const K = new int[k + 1];
	int* const L = new int[k + 1];

	for (int i = 1; i <= k; i++) {
		K[i] = i;
		L[i] = n - k + i;

		wy << K[i] << " ";
	}

	wy << endl;

	int i;
	while (K[1] != L[1]) {
		i = k;

		if (K[i] < L[i]) {
			K[i] = K[i] + 1;
		}
		else {
			do {
				i = i - 1;
			} while (K[i] >= L[i]);

			K[i] = K[i] + 1;

			for (int j = i + 1; j <= k; j++) {
				K[j] = K[j - 1] + 1;
			}
		}

		for (int x = 1; x <= k; x++) {
			wy << K[x] << " ";
		}

		wy << endl;
	}
}

void semba(const int n) {
	int k = 0;
	int* const K = new int[n + 1];
	K[k] = 0;

	while (K[1] != n) {
		if (K[k] < n) {
			K[k + 1] = K[k] + 1;
			k = k + 1;
		}
		else {
			k = k - 1;
			K[k] = K[k] + 1;
		}

		for (int i = 1; i <= k; i++) {
			wy << K[i] << " ";
		}

		wy << endl;
	}
}

int main() {
	int w, n;

	auto start = chrono::high_resolution_clock::now();
	auto stop = start;

	if (!wy.is_open()) {
		cout << "Nie udalo sie otworzyc pliku wynik.txt!";
		exit(-1);
	}

	cout << "--- Generowanie kombinacji zbioru ---" << endl;
	cout << "1. Algorytm generujacy leksykograficznie rosnaco" << endl << "2. Algorytm Semby" << endl;
	cout << "Wybierz algorytm, z ktorego chcesz skorzystac: ";

	cin >> w;

	switch (w) {
		case 1: {
			getSetSizeFromConsole(n);

			cout << "Podaj wielkosc kombinacji: ";
			int k;
			cin >> k;

			if (k > n || k < 1) {
				cout << "Niepoprawna wielkosc kombinacji!";
				exit(-1);
			}

			start = chrono::high_resolution_clock::now();
			lexicographical(n, k);
			break;
		}
		case 2: {
			getSetSizeFromConsole(n);
			start = chrono::high_resolution_clock::now();
			semba(n);
			break;
		}
		default: {
			cout << "Niepoprawny wybor!";
			exit(-1);
		}
	}

	stop = chrono::high_resolution_clock::now();
	chrono::duration<double, std::milli> ms_double = stop - start;

	wy.close();
	cout << "Wyniki zostaly zapisane w pliku wynik.txt" << endl;
	cout << "Czas dzialania algorytmu: " << ms_double.count() << " milisekud";

	return 0;
}