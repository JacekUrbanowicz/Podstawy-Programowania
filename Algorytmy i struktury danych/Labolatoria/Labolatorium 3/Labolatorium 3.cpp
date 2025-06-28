#include <iostream>
#include<algorithm>

using namespace std;

int maksymalny_zysk(int ladownosc, int* waga, int* cena, int ilosc_przedmitow);

int main()
{
    for (int i = 0; i < 500; i++)
    {
        int ilosc_przedmiotow =0;
        cin >> ilosc_przedmiotow;

        int* cena = new int[ilosc_przedmiotow];
        for (int i = 0; i < ilosc_przedmiotow; i++)
        {
            cin >> cena[i];
        }

        int* waga = new int[ilosc_przedmiotow];
        for (int i = 0; i < ilosc_przedmiotow; i++)
        {
            cin >> waga[i];
        }

        int ladownosc = 0;
        cin >> ladownosc;

        int zarobek = maksymalny_zysk(ladownosc, waga, cena, ilosc_przedmiotow);
        cout << zarobek << endl;
        delete[] waga;
        delete[] cena;
    }
    return 0;
}

int maksymalny_zysk(int ladownosc, int* waga, int* cena, int ilosc_przedmitow)
{
    int** tablica = new int* [ilosc_przedmitow + 1];
    for (int i = 0; i < ilosc_przedmitow + 1; i++)
    {
        tablica[i] = new int[ladownosc + 1];
    }

    for (int i = 0; i < ilosc_przedmitow+1; i++)
    {
        for(int j=0; j<ladownosc+1;j++)
        {
            tablica[i][j] = 0;
        }
    }

    for (int i = 1; i < ilosc_przedmitow+1; i++)
    {
        for (int j = 0; j < ladownosc+1; j++)
        {
            if(i == 0 || j == 0)
            {
                tablica[i][j] = 0;
            }
            else if (j-waga[i-1]>= 0)
            {
                tablica[i][j] = max(tablica[i - 1][j], tablica[i - 1][j - waga[i - 1]] + cena[i - 1]);
            }
            else
            {
                tablica[i][j] = tablica[i - 1][j];
            }
        }
    }

    int wynik = tablica[ilosc_przedmitow][ladownosc];

    for (int i = 0; i < ilosc_przedmitow; i++)
    {
        delete tablica[i];
    }

    delete[] tablica;

    return wynik;
}