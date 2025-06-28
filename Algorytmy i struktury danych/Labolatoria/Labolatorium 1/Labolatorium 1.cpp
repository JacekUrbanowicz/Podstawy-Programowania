#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

struct wielokat
{
    double x;
    double y;
    double pole;
    double arctg;
};

void sortowanie(int wierzcholki, wielokat przykladowy_wielokat[]);
bool porownaj(const wielokat &a, const wielokat& b);

int main()
{
    int wielokaty = 0;
    cin >> wielokaty;

    wielokat przykladowy_wielokat[100];
    for (int i = 0; i < wielokaty; i++)
    {
        int wierzcholki = 0;
        int liczba_wspolrzednych = 0;
        cin >> liczba_wspolrzednych;
        wierzcholki = liczba_wspolrzednych / 2;

        int licznik = 0;
        for (int i = 0; i < wierzcholki; i++)
        {
            cin >> przykladowy_wielokat[i].x;
            cin >> przykladowy_wielokat[i].y;
            licznik++;
        }

        sortowanie(wierzcholki, przykladowy_wielokat);

        przykladowy_wielokat[licznik].x = przykladowy_wielokat[0].x;
        przykladowy_wielokat[licznik].y = przykladowy_wielokat[0].y;

        int suma1 = 0;
        int suma2 = 0;
        for (int i = 0; i < wierzcholki; i++)
        {
            suma1 = suma1 + (przykladowy_wielokat[i].x * przykladowy_wielokat[i + 1].y);
        }
        for (int i = 0; i < wierzcholki; i++)
        {
            suma2 = suma2 + (przykladowy_wielokat[i].y * przykladowy_wielokat[i + 1].x);
        }

        przykladowy_wielokat[0].pole = 0.5 * abs(suma1 - suma2);
        int wynik = floor(przykladowy_wielokat[0].pole);
        cout << wynik << endl;
    }

    return 0;
}

void sortowanie(int wierzcholki, wielokat przykladowy_wielokat[])
{
    double xsrodek = 0;
    double ysrodek = 0;
    for (int i = 0; i < wierzcholki; i++)
    {
        xsrodek = xsrodek + przykladowy_wielokat[i].x;
        ysrodek = ysrodek + przykladowy_wielokat[i].y;
    }
    xsrodek = xsrodek / wierzcholki;
    ysrodek = ysrodek / wierzcholki;

    for (int i = 0; i < wierzcholki; i++)
    {
        przykladowy_wielokat[i].arctg = atan2(przykladowy_wielokat[i].x - xsrodek, przykladowy_wielokat[i].y - ysrodek);
    }

    sort(przykladowy_wielokat, przykladowy_wielokat + wierzcholki, porownaj);
}

bool porownaj(const wielokat& a, const wielokat& b)
{
    return a.arctg < b.arctg;
}
