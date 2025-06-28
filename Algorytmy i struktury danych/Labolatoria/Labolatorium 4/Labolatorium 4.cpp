#include <iostream>
#include<string>

using namespace std;

struct Macierz
{
    int rozmiar = 0;
    char** macierz;
    int ilosc_mozliwych_przejsc = 0;
};

bool ilosc_stopni(Macierz& Macierz);
bool przejscie_grafu(Macierz& Macierz);

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
            for(int j=0; j<rozmiar;j++)
            {
                Macierz.macierz[i][j] = graf[indeks];
                indeks++;
            }
        }

        bool cykl = ilosc_stopni(Macierz);

        if (cykl == true)
        {
            cykl = przejscie_grafu(Macierz);
        }

        if (cykl == false)
        {
            cout << "0" << endl;
        }
        else
        {
            cout << "1" << endl;
        }
    }
}

bool ilosc_stopni(Macierz& Macierz)
{
    for (int i = 0; i < Macierz.rozmiar; i++)
    {
        int licznik_krawedzi = 0;
        for (int j = 0; j < Macierz.rozmiar; j++)
        {
            if(Macierz.macierz[i][j] == '1')
            {
                licznik_krawedzi++;
                Macierz.ilosc_mozliwych_przejsc++;
            }
        }

        if (licznik_krawedzi != 2)
        {
            return false;
        }
    }

    return true;
}

bool przejscie_grafu(Macierz& Macierz)
{
    int ilosc_przejsc = 0;
    int aktualny_wierzcholek = 0;

    while (true)
    {
        bool przejscie_wykonanae = false;
        for (int i = 0; i < Macierz.rozmiar; i++)
        {
            if(Macierz.macierz[aktualny_wierzcholek][i] == '1')
            {
                ilosc_przejsc++;
                Macierz.macierz[aktualny_wierzcholek][i] = '0';
                Macierz.macierz[i][aktualny_wierzcholek] = '0';
                aktualny_wierzcholek = i;
                przejscie_wykonanae = true;
                break;
            }
        }

        if (przejscie_wykonanae == false)
        {
            break;
        }
    }

    if (ilosc_przejsc != (Macierz.ilosc_mozliwych_przejsc/2))
    {
        return false;
    }
    else
    {
        return true;
    }
}