#include <iostream>
#include <vector>
using namespace std;
 
struct Punkt
{
    int x, y;
};
 
// 0 kiedy punkty są współliniowe, 1 gdy zgodnie ze wskazówkami zegara, 2 kiedy przeciw wskazówkom
int wyznaczOrientacje(Punkt p, Punkt q, Punkt r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0; 
    return (val > 0) ? 1 : 2;
}
 
void jarvis(Punkt* zbior, int n) {
    // Muszą być co najmniej 3 punkty żeby wyznaczyć otoczkę
    if (n < 3) return;

    vector<Punkt> wynik;
 
    // Wyznacza punkt na samym dole
    int l = 0;

    for(int i = 1; i < n; i++)
        if(zbior[i].y < zbior[l].y || (zbior[i].y == zbior[l].y && zbior[i].x < zbior[l].x))
            l = i;
 
    int p = l, q;
    do
    {
        wynik.push_back(zbior[p]);
 
        // Wyznacza punkt "q", dla którego punkty "p", "q" i "x" są ustawione przeciwnie do wskazówek zegara dla każdego punktu "x"
        q = (p+1)%n;
        for (int i = 0; i < n; i++)
        {
           if (wyznaczOrientacje(zbior[p], zbior[i], zbior[q]) == 2)
               q = i;
        }

        p = q;
 
    } while (p != l);
 
    for (int i = 0; i < wynik.size(); i++)
        cout << "(" << wynik[i].x << ", " << wynik[i].y << ")\n";
}
 
int main(){
    // 0 0; 0 2; -2 2; 4 2; 3 3; 2 5; 5 5; 1 6; 0 8
    //Punkt zbior[] = {{0, 0}, {0, 2}, {-2, 2}, {4, 2}, {3, 3}, {2, 5}, {5, 5}, {1, 6}, {0, 8}};
    //jarvis(zbior, 9);

    cout << "Algorytm generowania otoczki wypuklej\n";
	cout << "Lukasz Konieczny | LK4 | LAB-13" << endl;

    cout << "Podaj ilosc punktow: ";
    int n;
    cin >> n;

    int x, y;
    Punkt* zbior = new Punkt[n];

    for(int i = 0; i < n; i++){
        cout << "Podaj wsp. x: ";
        cin >> x;
        cout << "Podaj wsp. y: ";
        cin >> y;

        zbior[i] = {x, y};
    }
    cout << endl << endl;
    cout << "Otoczka sklada sie z punktow: " << endl;

    jarvis(zbior, n);
    return 0;
}