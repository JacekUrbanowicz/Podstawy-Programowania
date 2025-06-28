#include <iostream>
#include<string>

using namespace std;

struct Macierz
{
    int rozmiar = 0;
    char** macierz;
};

bool czy_zawiera_szpon(Macierz& Macierz);
bool czy_sasiedzi_to_szpon(Macierz& Macierz, int* sasiedzi_punktu, int liczba_sasiadow);

int main()
{
    int ilosc = 0;
    cin >> ilosc;
    for (int w = 0; w < ilosc; w++)
    {
        int rozmiar = 0;
        cin >> rozmiar;

        Macierz Macierz;

        Macierz.rozmiar = rozmiar;
        Macierz.macierz = new char* [rozmiar];

        for (int i = 0; i < rozmiar; i++)
        {
            Macierz.macierz[i] = new char[rozmiar];
        }

        string graf;
        cin >> graf;

        int indeks = 0;
        for (int i = 0; i < rozmiar; i++)
        {
            for (int j = 0; j < rozmiar; j++)
            {
                Macierz.macierz[i][j] = graf[indeks];
                indeks++;
            }
        }

        bool szpon = czy_zawiera_szpon(Macierz);

        if (szpon == false)
        {
            cout << "1" << endl;
        }
        else
        {
            cout << "0" << endl;
        }
    }
}

bool czy_zawiera_szpon(Macierz& Macierz)
{
    int rozmiar = Macierz.rozmiar;

    for (int w = 0; w < rozmiar; w++)
    {
        int* sasiedzi_punktu = new int[rozmiar];
        int liczba_sasiadow = 0;

        for (int u = 0; u < rozmiar; u++)
        {
            if (Macierz.macierz[w][u] == '1')
            {
                sasiedzi_punktu[liczba_sasiadow] = u;
                liczba_sasiadow++;
            }
        }

        if (liczba_sasiadow < 3)
        {
            delete[] sasiedzi_punktu;
            continue;
        }

        bool sasiedzi_to_szpon = czy_sasiedzi_to_szpon(Macierz, sasiedzi_punktu, liczba_sasiadow);

        if (sasiedzi_to_szpon == true)
        {
            delete[] sasiedzi_punktu;
            return true;
        }

        delete[] sasiedzi_punktu;
    }

    return false;
}

bool czy_sasiedzi_to_szpon(Macierz& Macierz, int* sasiedzi_punktu, int liczba_sasiadow)
{
    for (int i = 0; i < liczba_sasiadow; i++)
    {
        for (int j = i + 1; j < liczba_sasiadow; j++)
        {
            for (int k = j + 1; k < liczba_sasiadow; k++)
            {
                int sasiad_1 = sasiedzi_punktu[i];
                int sasiad_2 = sasiedzi_punktu[j];
                int sasiad_3 = sasiedzi_punktu[k];

                if (Macierz.macierz[sasiad_1][sasiad_2] == '0' && Macierz.macierz[sasiad_1][sasiad_3] == '0' && Macierz.macierz[sasiad_2][sasiad_1] == '0' && Macierz.macierz[sasiad_2][sasiad_3] == '0' && Macierz.macierz[sasiad_3][sasiad_1] == '0' && Macierz.macierz[sasiad_3][sasiad_2] == '0')
                {
                    return true;
                }
            }
        }
    }

    return false;
}