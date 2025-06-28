#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

struct Punkt
{
    int szerokosc_na_planszy = 0;
    int wysokosc_na_planszy = 0;
    int wysokosc = 0;
    int najblizsza_odleglosc = 2147483647;
    bool odwiedzony = false;
    bool poczatek_wyciagu = false;
};

struct PLANSZA
{
    int szerokosc = 0;
    int wysokosc = 0;
    Punkt** mapa = nullptr;
    Punkt* punkt_startowy = nullptr;
    Punkt* punkt_koncowy = nullptr;
    int liczba_wyciagow = 0;
};

struct KOPIEC
{
    Punkt** elementy = nullptr;
    int maksymalna_ilosc_elementow = 0;
    int aktualna_ilosc_elementow = 0;
};

struct WYCIAG
{
    Punkt poczatkowy;
    Punkt koncowy;
    int czas_podrozy = 0;
    int minuty_odjazdow = 0;
};

void stworz_plasze(PLANSZA& Plansza, WYCIAG*& Wyciagi);
void wyswietl_plansze(PLANSZA& Plansza);
void znajdz_droge(KOPIEC& Kopiec, PLANSZA& Plansza, WYCIAG*& Wyciagi);
void znajdz_sasiadow(KOPIEC& Kopiec, PLANSZA& Plansza, Punkt* Sprawdzany_punkt);
void oblicz_odleglosc(KOPIEC& Kopiec, Punkt* Sprawdzany_punkt, Punkt* Sasiedni_punkt);

void stworz_kopiec(KOPIEC& Kopiec);
void dodaj_element_kopca(KOPIEC& Kopiec, Punkt* Dodawany_punkt);
void porzazdkowanie_po_dodaniu(KOPIEC& Kopiec);
void usun_pierwszy_element_kopca(KOPIEC& Kopiec);
void porzazdkowanie_po_usunieciu(KOPIEC& Kopiec);
void wyswietl_kopiec(KOPIEC& Kopiec);

void wczytaj_wyciagi(PLANSZA& Plansza, WYCIAG*& Wyciagi);
void zaznacz_wyciagi_na_mapie(PLANSZA& Plansza, WYCIAG*& Wyciagi);
void znajdz_sasiadow_wyciagi(KOPIEC& Kopiec, PLANSZA& Plansza, WYCIAG*& Wyciagi, Punkt* Sprawdzany_punkt);
void oblicz_odleglosc_wyciagi(KOPIEC& Kopiec, Punkt* Sprawdzany_punkt, Punkt* Sasiedni_punkt, int& czas_podrozy, int& minuty_odjazdow);
void wyswietl_wyciagi(PLANSZA& Plansza, WYCIAG*& Wyciagi);
void wyswietl_plansze_wyciagi(PLANSZA& Plansza);

int main()
{
    PLANSZA Plansza;
    WYCIAG* Wyciagi = nullptr;

    stworz_plasze(Plansza, Wyciagi);
    zaznacz_wyciagi_na_mapie(Plansza, Wyciagi);

    KOPIEC Kopiec;
    Kopiec.maksymalna_ilosc_elementow = Plansza.wysokosc * Plansza.szerokosc;
    stworz_kopiec(Kopiec);

    Plansza.punkt_startowy->najblizsza_odleglosc = 0;
    dodaj_element_kopca(Kopiec, Plansza.punkt_startowy);

    znajdz_droge(Kopiec, Plansza, Wyciagi);

    printf("%d", Plansza.punkt_koncowy->najblizsza_odleglosc);

    return 0;
}

void stworz_plasze(PLANSZA& Plansza, WYCIAG*& Wyciagi)
{
    scanf("%d", &Plansza.szerokosc);
    scanf("%d", &Plansza.wysokosc);

    Plansza.mapa = new Punkt * [Plansza.wysokosc];

    for (int i = 0; i < Plansza.wysokosc; i++)
    {
        Plansza.mapa[i] = new Punkt[Plansza.szerokosc];
    }

    int Punkt_startowy_szerokosc = 0;
    int Punkt_startowy_wysokosc = 0;

    scanf("%d", &Punkt_startowy_szerokosc);
    scanf("%d", &Punkt_startowy_wysokosc);

    Plansza.punkt_startowy = &Plansza.mapa[Punkt_startowy_wysokosc][Punkt_startowy_szerokosc];

    int Punkt_koncowy_szerokosc = 0;
    int Punkt_koncowy_wysokosc = 0;

    scanf("%d", &Punkt_koncowy_szerokosc);
    scanf("%d", &Punkt_koncowy_wysokosc);

    Plansza.punkt_koncowy = &Plansza.mapa[Punkt_koncowy_wysokosc][Punkt_koncowy_szerokosc];

    int liczba_wyciagow = 0;
    scanf("%d", &liczba_wyciagow);

    if (liczba_wyciagow != 0)
    {
        Plansza.liczba_wyciagow = liczba_wyciagow;
        wczytaj_wyciagi(Plansza, Wyciagi);
    }

    for (int i = 0; i < Plansza.wysokosc; i++)
    {
        for (int j = 0; j < Plansza.szerokosc; j++)
        {
            scanf("%d", &Plansza.mapa[i][j].wysokosc);
            Plansza.mapa[i][j].szerokosc_na_planszy = j;
            Plansza.mapa[i][j].wysokosc_na_planszy = i;
        }
    }
}

void wyswietl_plansze(PLANSZA& Plansza)
{
    cout << endl;
    for (int i = 0; i < Plansza.wysokosc; i++)
    {
        for (int j = 0; j < Plansza.szerokosc; j++)
        {
            cout << Plansza.mapa[i][j].wysokosc << " ";
        }
        cout << endl;
    }
}

void znajdz_droge(KOPIEC& Kopiec, PLANSZA& Plansza, WYCIAG*& Wyciagi)
{
    while (Kopiec.aktualna_ilosc_elementow > 0)
    {
        Punkt* aktualny = Kopiec.elementy[0];
        aktualny->odwiedzony = true;

        if (aktualny == Plansza.punkt_koncowy)
        {
            break;
        }

        znajdz_sasiadow(Kopiec, Plansza, aktualny);

        if (Plansza.liczba_wyciagow != 0)
        {
            znajdz_sasiadow_wyciagi(Kopiec, Plansza, Wyciagi, aktualny);
        }

        usun_pierwszy_element_kopca(Kopiec);
    }
}

void znajdz_sasiadow(KOPIEC& Kopiec, PLANSZA& Plansza, Punkt* Sprawdzany_punkt)
{
    Punkt* sasiad;

    if (Sprawdzany_punkt->szerokosc_na_planszy - 1 >= 0)
    {
        sasiad = &Plansza.mapa[Sprawdzany_punkt->wysokosc_na_planszy][Sprawdzany_punkt->szerokosc_na_planszy - 1];
        oblicz_odleglosc(Kopiec, Sprawdzany_punkt, sasiad);
    }
    if (Sprawdzany_punkt->szerokosc_na_planszy + 1 < Plansza.szerokosc)
    {
        sasiad = &Plansza.mapa[Sprawdzany_punkt->wysokosc_na_planszy][Sprawdzany_punkt->szerokosc_na_planszy + 1];
        oblicz_odleglosc(Kopiec, Sprawdzany_punkt, sasiad);
    }
    if (Sprawdzany_punkt->wysokosc_na_planszy - 1 >= 0)
    {
        sasiad = &Plansza.mapa[Sprawdzany_punkt->wysokosc_na_planszy - 1][Sprawdzany_punkt->szerokosc_na_planszy];
        oblicz_odleglosc(Kopiec, Sprawdzany_punkt, sasiad);
    }
    if (Sprawdzany_punkt->wysokosc_na_planszy + 1 < Plansza.wysokosc)
    {
        sasiad = &Plansza.mapa[Sprawdzany_punkt->wysokosc_na_planszy + 1][Sprawdzany_punkt->szerokosc_na_planszy];
        oblicz_odleglosc(Kopiec, Sprawdzany_punkt, sasiad);
    }
}

void oblicz_odleglosc(KOPIEC& Kopiec, Punkt* Sprawdzany_punkt, Punkt* Sasiedni_punkt)
{
    int odleglosc = 0;
    odleglosc = Sprawdzany_punkt->najblizsza_odleglosc;

    if (Sprawdzany_punkt->wysokosc >= Sasiedni_punkt->wysokosc)
    {
        odleglosc = odleglosc + 1;
        if (odleglosc < Sasiedni_punkt->najblizsza_odleglosc)
        {
            if (Sasiedni_punkt->odwiedzony == false)
            {
                Sasiedni_punkt->najblizsza_odleglosc = odleglosc;
                dodaj_element_kopca(Kopiec, Sasiedni_punkt);
            }
        }
    }
    else
    {
        odleglosc = odleglosc + Sasiedni_punkt->wysokosc - Sprawdzany_punkt->wysokosc + 1;
        if (odleglosc < Sasiedni_punkt->najblizsza_odleglosc)
        {
            if (Sasiedni_punkt->odwiedzony == false)
            {
                Sasiedni_punkt->najblizsza_odleglosc = odleglosc;
                dodaj_element_kopca(Kopiec, Sasiedni_punkt);
            }
        }
    }
}

void stworz_kopiec(KOPIEC& Kopiec)
{
    Kopiec.elementy = new Punkt * [Kopiec.maksymalna_ilosc_elementow];
}

void dodaj_element_kopca(KOPIEC& Kopiec, Punkt* Dodawany_punkt)
{
    Kopiec.elementy[Kopiec.aktualna_ilosc_elementow] = Dodawany_punkt;

    porzazdkowanie_po_dodaniu(Kopiec);

    Kopiec.aktualna_ilosc_elementow++;
}

void porzazdkowanie_po_dodaniu(KOPIEC& Kopiec)
{
    int indeks_dodanego_punktu = Kopiec.aktualna_ilosc_elementow;

    while (indeks_dodanego_punktu > 0)
    {
        int indeks_rodzica_punktu = (indeks_dodanego_punktu - 1) / 2;

        if (Kopiec.elementy[indeks_dodanego_punktu]->najblizsza_odleglosc < Kopiec.elementy[indeks_rodzica_punktu]->najblizsza_odleglosc)
        {
            Punkt* pomocniczy_punkt = Kopiec.elementy[indeks_dodanego_punktu];
            Kopiec.elementy[indeks_dodanego_punktu] = Kopiec.elementy[indeks_rodzica_punktu];
            Kopiec.elementy[indeks_rodzica_punktu] = pomocniczy_punkt;

            indeks_dodanego_punktu = indeks_rodzica_punktu;
        }
        else
        {
            break;
        }
    }
}

void usun_pierwszy_element_kopca(KOPIEC& Kopiec)
{
    Punkt* pomocniczy_punkt = Kopiec.elementy[Kopiec.aktualna_ilosc_elementow - 1];

    Kopiec.elementy[Kopiec.aktualna_ilosc_elementow - 1] = Kopiec.elementy[0];
    Kopiec.elementy[0] = pomocniczy_punkt;
    Kopiec.aktualna_ilosc_elementow--;

    porzazdkowanie_po_usunieciu(Kopiec);
}

void porzazdkowanie_po_usunieciu(KOPIEC& Kopiec)
{
    int indeks_nowego_punktu = 0;

    while (indeks_nowego_punktu < Kopiec.aktualna_ilosc_elementow)
    {
        int indeks_lewgo_syna = (indeks_nowego_punktu * 2) + 1;
        int indeks_prawego_syna = (indeks_nowego_punktu * 2) + 2;

        int indeks_najmniejszego = indeks_nowego_punktu;

        if (indeks_lewgo_syna < Kopiec.aktualna_ilosc_elementow)
        {
            if (Kopiec.elementy[indeks_nowego_punktu]->najblizsza_odleglosc > Kopiec.elementy[indeks_lewgo_syna]->najblizsza_odleglosc)
            {
                indeks_najmniejszego = indeks_lewgo_syna;
            }
        }

        if (indeks_prawego_syna < Kopiec.aktualna_ilosc_elementow)
        {
            if (Kopiec.elementy[indeks_najmniejszego]->najblizsza_odleglosc > Kopiec.elementy[indeks_prawego_syna]->najblizsza_odleglosc)
            {
                indeks_najmniejszego = indeks_prawego_syna;
            }
        }

        if (indeks_najmniejszego == indeks_nowego_punktu)
        {
            break;
        }
        else
        {
            Punkt* pomocniczy_punkt = Kopiec.elementy[indeks_nowego_punktu];

            Kopiec.elementy[indeks_nowego_punktu] = Kopiec.elementy[indeks_najmniejszego];
            Kopiec.elementy[indeks_najmniejszego] = pomocniczy_punkt;

            indeks_nowego_punktu = indeks_najmniejszego;
        }
    }
}

void wyswietl_kopiec(KOPIEC& Kopiec)
{
    for (int i = 0; i < Kopiec.aktualna_ilosc_elementow; i++)
    {
        cout << endl << "Punkt w kopcu o indeksie: " << i << " na pozycji: " << Kopiec.elementy[i]->szerokosc_na_planszy << ":" << Kopiec.elementy[i]->wysokosc_na_planszy << " najblizsza odleglosc: " << Kopiec.elementy[i]->najblizsza_odleglosc;
    }
    cout << endl;
}

void wczytaj_wyciagi(PLANSZA& Plansza, WYCIAG*& Wyciagi)
{
    Wyciagi = new WYCIAG[Plansza.liczba_wyciagow];

    for (int i = 0; i < Plansza.liczba_wyciagow; i++)
    {
        scanf("%d", &Wyciagi[i].poczatkowy.szerokosc_na_planszy);
        scanf("%d", &Wyciagi[i].poczatkowy.wysokosc_na_planszy);

        scanf("%d", &Wyciagi[i].koncowy.szerokosc_na_planszy);
        scanf("%d", &Wyciagi[i].koncowy.wysokosc_na_planszy);

        scanf("%d", &Wyciagi[i].czas_podrozy);
        scanf("%d", &Wyciagi[i].minuty_odjazdow);
    }
}

void zaznacz_wyciagi_na_mapie(PLANSZA& Plansza, WYCIAG*& Wyciagi)
{
    for (int i = 0; i < Plansza.liczba_wyciagow; i++)
    {
        int szerokosc_do_zaznaczenia = Wyciagi[i].poczatkowy.szerokosc_na_planszy;
        int wysokosc_do_zaznaczenia = Wyciagi[i].poczatkowy.wysokosc_na_planszy;

        Plansza.mapa[wysokosc_do_zaznaczenia][szerokosc_do_zaznaczenia].poczatek_wyciagu = true;
    }
}

void znajdz_sasiadow_wyciagi(KOPIEC& Kopiec, PLANSZA& Plansza, WYCIAG*& Wyciagi, Punkt* Sprawdzany_punkt)
{
    if (Sprawdzany_punkt->poczatek_wyciagu == false)
    {
        return;
    }

    for (int i = 0; i < Plansza.liczba_wyciagow; i++)
    {
        Punkt* sasiad_wyciagu;

        int szerokosc_poczatku = Wyciagi[i].poczatkowy.szerokosc_na_planszy;
        int wysokosc_poczatku = Wyciagi[i].poczatkowy.wysokosc_na_planszy;

        if ((Sprawdzany_punkt->szerokosc_na_planszy == szerokosc_poczatku) && (Sprawdzany_punkt->wysokosc_na_planszy == wysokosc_poczatku))
        {
            int szerokosc_konca = Wyciagi[i].koncowy.szerokosc_na_planszy;
            int wysokosc_konca = Wyciagi[i].koncowy.wysokosc_na_planszy;

            sasiad_wyciagu = &Plansza.mapa[wysokosc_konca][szerokosc_konca];
            int minuty_odjazdow = Wyciagi[i].minuty_odjazdow;
            int czas_podrozy = Wyciagi[i].czas_podrozy;
            oblicz_odleglosc_wyciagi(Kopiec, Sprawdzany_punkt, sasiad_wyciagu, czas_podrozy, minuty_odjazdow);
        }
    }
}

void oblicz_odleglosc_wyciagi(KOPIEC& Kopiec, Punkt* Sprawdzany_punkt, Punkt* Sasiedni_punkt, int& czas_podrozy, int& minuty_odjazdow)
{
    int czas_dotarcia = Sprawdzany_punkt->najblizsza_odleglosc;

    int czas_czekania = czas_dotarcia % minuty_odjazdow;

    int czas_najblizszego_odjazdu = 0;
    if (czas_czekania != 0)
    {
        czas_najblizszego_odjazdu = minuty_odjazdow - czas_czekania;
    }

    int odleglosc = czas_podrozy + czas_dotarcia + czas_najblizszego_odjazdu;

    if (odleglosc < Sasiedni_punkt->najblizsza_odleglosc)
    {
        if (Sasiedni_punkt->odwiedzony == false)
        {
            Sasiedni_punkt->najblizsza_odleglosc = odleglosc;
            dodaj_element_kopca(Kopiec, Sasiedni_punkt);
        }
    }
}

void wyswietl_wyciagi(PLANSZA& Plansza, WYCIAG*& Wyciagi)
{
    for (int i = 0; i < Plansza.liczba_wyciagow; i++)
    {
        cout << endl << "Wyciag o indeksie: " << i << " punkt poczatkowy (szerokosc:wysokosc) : " << Wyciagi[i].poczatkowy.szerokosc_na_planszy << ":" << Wyciagi[i].poczatkowy.wysokosc_na_planszy;
        cout << endl << "punkt koncowy (szerokosc:wysokosc) : " << Wyciagi[i].koncowy.szerokosc_na_planszy << ":" << Wyciagi[i].koncowy.wysokosc_na_planszy;
        cout << endl << "o czasie jazdy: " << Wyciagi[i].czas_podrozy << " i odjezdzajacy co: " << Wyciagi[i].minuty_odjazdow;
    }
}

void wyswietl_plansze_wyciagi(PLANSZA& Plansza)
{
    cout << endl;
    for (int i = 0; i < Plansza.wysokosc; i++)
    {
        for (int j = 0; j < Plansza.szerokosc; j++)
        {
            if (Plansza.mapa[i][j].poczatek_wyciagu == true)
            {
                cout << "P" << " ";
            }
            else
            {
                cout << Plansza.mapa[i][j].wysokosc << " ";
            }
        }
        cout << endl;
    }
}
