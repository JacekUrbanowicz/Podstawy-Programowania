#include <iostream>
#include <string>

using namespace std;

string* sortowanie(string* liczby, int ilosc_elementow);
string* scalanie(string* pom_tab1, int stala1, string* pom_tab2, int stala2, int ilosc_elementow);
bool porwonanie(const string&a, const string&b)
{
    if (a.length()!= b.length())
    {
        return a.length() < b.length();
    }
    return a < b;
}

int main()
{
    int ilosc_elementow = 0;
    cin >> ilosc_elementow;

    string* liczby = new string[ilosc_elementow];
    for (int i = 0; i < ilosc_elementow; i++)
    {
        cin >> liczby[i];
    }

    liczby = sortowanie(liczby, ilosc_elementow);

    cout << endl;
    for (int i = 0; i < ilosc_elementow; i++)
    {
        cout << liczby[i] << endl;
    }

    delete[] liczby;
    
    return 0;
}

string* sortowanie(string* liczby, int ilosc_elementow)
{
    if (ilosc_elementow == 1)
    {
        return liczby;
    }

    int stala1 = ilosc_elementow / 2;
    int stala2 = ilosc_elementow - stala1;

    string* pom_tab1 = new string[stala1];
    string* pom_tab2 = new string[stala2];

    for (int i = 0; i < stala1; i++)
    {
        pom_tab1[i] = liczby[i];
    }

    for (int i = 0; i < stala2; i++)
    {
        pom_tab2[i] = liczby[stala1 + i];
    }

    pom_tab1 = sortowanie(pom_tab1, stala1);
    pom_tab2 = sortowanie(pom_tab2, stala2);

    string* wynik = scalanie(pom_tab1, stala1, pom_tab2, stala2, ilosc_elementow);

    delete[] pom_tab1;
    delete[] pom_tab2;

    return wynik;
}

string* scalanie(string* pom_tab1, int stala1, string* pom_tab2, int stala2, int ilosc_elementow)
{
    string* tablica_zwrotna = new string[stala1 + stala2];
    int index1 = 0;
    int index2 = 0;
    int index3 = 0;
    while(stala1 > index1 && stala2 > index2)
    {

        if (porwonanie(pom_tab1[index1], pom_tab2[index2]))
        {
            tablica_zwrotna[index3] = pom_tab1[index1];
            index3++;
            index1++;
        }
        else
        {
            tablica_zwrotna[index3] = pom_tab2[index2];
            index3++;
            index2++;
        }
    }

    while (stala1 > index1)
    {
        tablica_zwrotna[index3] = pom_tab1[index1];
        index3++;
        index1++;
    }

    while (stala2 > index2)
    {
        tablica_zwrotna[index3] = pom_tab2[index2];
        index3++;
        index2++;
    }

    return tablica_zwrotna;
}
