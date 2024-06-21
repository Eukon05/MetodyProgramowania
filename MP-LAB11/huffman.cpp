#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
using namespace std;

struct Node {
	char value;
	int freq;
	Node *left, *right;

	Node(char value, int freq, Node* left = nullptr, Node* right = nullptr){
		this->value = value;
		this->freq = freq;
		this->left = left;
		this->right = right;
	}
};

struct Comparator {
	bool operator()(Node* l, Node* r) {
		return l->freq > r->freq;
	}
};

void generateCodes(Node* root, string str, unordered_map<char, string>& huffmanCode) {
	if (root == nullptr)
		return;

	// Wezel ktory nie ma dzieci jest wezlem z danymi. Zapisujemy w mapie wartosc wyznaczonego dla niego kodu
	if (!root->left && !root->right) {
		huffmanCode[root->value] = str;
	}

	// Rekurencyjnie sprawdzamy dzieci wezla. Jesli ich nie ma, funkcja przerwie sie dla nich na jej poczatku
	generateCodes(root->left, str + "0", huffmanCode); // Zakladamy, ze lewe krawedzie maja wage "0" a prawe "1"
	generateCodes(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int& index, string str) {
	if (root == nullptr) {
		return;
	}

	// Jesli dotarlismy do wezla ktory nie ma dzieci, wypisujemy przypisana mu liczbe
	if (!root->left && !root->right) {
		cout << root->value;
		return;
	}

	// Jesli nie, przechodzimy o jeden znak dalej w napisie
	index++;

	// A nastepnie powtarzamy rekurencyjnie wyszukiwanie wezla "bezdzietnego"
	if (str[index] == '0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

void menu(unordered_map<char, string> huffmanCode, Node* root){
	cout << "Wyznaczone kody Huffmana :\n" << '\n';
	for (auto pair: huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}

	cout << endl;

	int input = 0;
	while(input != 3){
		cout << "-- MENU --\n";
		cout << "1. Zakoduj tekst\n";
		cout << "2. Dekoduj tekst\n";
		cout << "3. Wyjdz\n";
		cout << "Co chcesz zrobic? Podaj liczbe: ";
		cin >> input;

		switch(input){
			case 1:{
				cout << "\nPodaj tekst do zakodowania: ";
				string we;
				cin >> we;
				string str = "";
				for (char c: we) {
					str += huffmanCode[c];
				}

				cout << "\nZakodowany tekst to: " << str << '\n';
				break;
			}
			case 2:{
				cout << "\nPodaj tekst do odkodowania: ";
				string we;
				cin >> we;
				int index = -1;
				cout << "\nOdkodowany tekst to: ";
				while (index < (int)we.size() - 2) {
					decode(root, index, we);
				}
				cout << endl;
				break;
			}
			case 3:{
				exit(0);
			}
		}
	}
}

void huffman(string text){
	// Mapa zliczajaca czestotliwosc wystapienia znaku w tekscie
	unordered_map<char, int> freq;
	for (char c: text) {
		freq[c]++;
	}

	// Kolejka przechowujaca wezly drzewa Huffmana
	priority_queue<Node*, vector<Node*>, Comparator> pq;

	// Dodajemy do kolejki kazda litere wystepujaca w tekscie wraz z odpowiadajaca czestotliwoscia
	// Kolejka priorytetyzuje litery o jak najnizszej czestotliwosci
	for (auto pair: freq) {
		pq.push(new Node(pair.first, pair.second));
	}

	int sum;
	// Dopoki w kolejce nie pozostal tylko ostatni wezel bez wartosci:
	while (pq.size() != 1) {
		// Wyciagamy z kolejki dwa wezly o najnizszej czestotliwosci i usuwamy je z niej
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();

		// Dodaje do kolejki wezel bez wartosci, o czestotliwosci rownej sumie wybranych wezlow
		sum = left->freq + right->freq;
		pq.push(new Node('\0', sum, left, right));
	}

	// Na poczatku kolejki znajduje sie wezel bez wartosci o sumie wszystkich czestotliwosci liter
	Node* root = pq.top();

	// Tworzymy mape przechowujaca kody, oraz wypelniamy ja funkcja "generateCodes"
	unordered_map<char, string> huffmanCode;
	generateCodes(root, "", huffmanCode);

	menu(huffmanCode, root);
}

int main(){
	cout << "Algorytm kodowania Huffmana\n";
	cout << "Lukasz Konieczny | LK4 | LAB-11" << endl;

	cout << "Jesli chcesz wpisac tekst tworzacy kod z klawiatury, wpisz 1, w przeciwnym przypadku sprobujemy pobrac go z pliku wejscie.txt\n";
	cout << "Wpisz swoj wybor: ";

	int w;
	cin >> w;

	string text;
	if(w == 1){
		cout << "Podaj tekst, na bazie ktorego utworzymy kod: ";
		cin >> text;
	}
	else {
		ifstream we("wejscie.txt");

		if(!we.is_open()){
			cout << "Nie mozna otworzyc pliku wejsciowego!";
			exit(-1);
		}

		we >> text;
	}

	huffman(text);
	return 0;
}