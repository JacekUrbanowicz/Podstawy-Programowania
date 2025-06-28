#include <iostream>
#include <string>

using namespace std;

struct ElementListy
{
    char element = '*';
    struct ElementListy* nastepny_element = nullptr;
    struct ElementListy* poprzedni_element = nullptr;
};

struct Lista
{
    int licznik = 0;
    bool utworzenie_znaku = false;
    struct ElementListy* pierwszy_element = nullptr;
    struct Lista* nastepna_lista = nullptr;
    struct Lista* poprzednia_lista = nullptr;
};

struct STOS
{
    char* wskaznik_instrukcji = nullptr;
    int licznik_wskaznika = 0;
    bool utworzenie_listy = false;
    struct Lista* pierwsza_lista = nullptr;
};

void stworz_liste(STOS& Stos);
void inkrementuj_licznik(Lista* aktualna_lista);
void usun_liste(STOS& Stos);
void usun_elementy_z_listy(ElementListy* element_listy);
void dekrementuj_licznik(Lista* aktualna_lista);
void dodaj_element(Lista* aktualna_lista, char instrukcja);
void kopiuj_liste(STOS& Stos);
void kopiuj_pierwszy_elementy(Lista* aktualna_lista, ElementListy* element_starej_lista);
void zamien_dwie_pierwsze(STOS& Stos);
void kopiuj_z_pozycji(STOS& Stos);
void znadz_pozycje(ElementListy* element_listy, int& suma, int& ilosc_wywolan);
void zlicz_sume(const ElementListy* element_listy, int& suma, int& ilosc_wywolan);
void doglebne_kopiowanie(STOS& Stos, Lista* aktualna_lista, int& suma);
void kopiuj_wybrana_liste(STOS& Stos, Lista* aktualna_lista);
void wypisz_listy(const Lista* aktualna_lista);
void wypisz_char(const ElementListy* element_listy);
void negacja(STOS& Stos, Lista* aktualna_lista, ElementListy* element_listy);
void dodaj_element_koncowy(STOS& Stos, Lista* aktualna_lista, ElementListy* element_listy);
void modul(STOS& Stos, Lista* aktualna_lista, ElementListy* element_listy);
void modul_ostatni_element(Lista* aktualna_lista, ElementListy* element_listy);
void pierwszy_znak(STOS& Stos, Lista* aktualna_lista, ElementListy* element_listy);
void obsluga_kropki(STOS& Stos);
void odlacz_pierwszy_znak(STOS& Stos);
void asci_na_liczbe(STOS& Stos);
void liczba_na_asci(STOS& Stos);
void tworz_liste_z_liczby(STOS& Stos, int& liczba_do_stworzenia);
void element_z_liczby(STOS& Stos, int& pojedyncza_cyfra, char& element_listy);
void suma_odwrocona_liczba(ElementListy* element_listy, int& suma, int& ilosc_wywolan);
void zlicz_sume_odwrotna(ElementListy* element_listy, int& suma, int& ilosc_wywolan);
void scal_listy(STOS& Stos);
void scal_elementy(STOS& Stos, ElementListy* element_pierwszej_listy, ElementListy* element_drugiej_listy);
void scal_znaczki(STOS& Stos, ElementListy* element_pierwszej_listy, ElementListy* element_drugiej_listy);
void negacja_logiczna(STOS& Stos);
void lista_z_licznika(STOS& Stos);
void tworz_liste_z_liczby_wskaznika(STOS& Stos, int& liczba_do_stworzenia);
void sprawdz_rownosc(STOS& Stos);
void czy_sa_puste(STOS& Stos, ElementListy* element_listy, bool& lista_pusta);
void odwroc_listy(STOS& Stos, ElementListy* element_listy);
void sprawdz_elementy(STOS& Stos, ElementListy* element_pierwszej_listy, ElementListy* element_drugiej_listy, bool& rowne_listy);
void mniejsze_liczby(STOS& Stos);
void sprawdz_dlugosc(ElementListy* element_listy, int& dlugosc);
void sprawdz_minus(STOS& Stos, ElementListy* element_listy, bool& lista_ujemna);
void sprawdz_elementy_mniejszy_wiekszy(STOS& Stos, ElementListy* element_pierwszej_listy, ElementListy* element_drugiej_listy, bool& pierwsza_ujemna, bool& druga_ujemna, bool& druga_wieksza);
void sprawdz_znaczek_mniejszy_wiekszy(STOS& Stos, ElementListy* element_pierwszej_listy, ElementListy* element_drugiej_listy, bool& pierwsza_ujemna, bool& druga_ujemna, bool& druga_wieksza);
void utnij_zera(Lista* aktualna_lista, ElementListy* element_listy);
void skok_warunkowy(STOS& Stos, bool& skok_wykonany);
void dodawnie_list(STOS& Stos);
void obie_ten_sam_znak(STOS& Stos, ElementListy* element_wiekszej_listy, ElementListy* element_mniejszej_listy, int& nadwyzka_bitowa);
void dodaj_pojedynczy_znak(STOS& Stos, char& element_wiekszej_listy, char& element_mniejszej_listy, int& nadwyzka_bitowa);
void obie_rozny_znak(STOS& Stos, ElementListy* element_wiekszej_listy, ElementListy* element_mniejszej_listy, int& pozyczka_bitowa);
void odejmij_pojedynczy_znak(STOS& Stos, char& element_wiekszej_listy, char& element_mniejszej_listy, int& pozyczka_bitowa);
void zamien_elementy(STOS& Stos);
void utnij_zera_koncowe(Lista* aktualna_lista, ElementListy* element_listy);
void sprawdz_minus_koncowy(ElementListy* element_listy, bool& lista_ujemna);

void pobierz_instrukcje(STOS& Stos);
void wykonaj_instrukcje(STOS& Stos, int rozmiar, bool& koniec_programu);

int main()
{
    STOS Stos;
    pobierz_instrukcje(Stos);

    return 0;
}

void stworz_liste(STOS& Stos)
{
    Lista* lista = new Lista;
    if (Stos.utworzenie_listy == false)
    {
        lista->licznik = 0;
        lista->poprzednia_lista = nullptr;
        lista->nastepna_lista = nullptr;
        Stos.pierwsza_lista = lista;
        Stos.utworzenie_listy = true;
    }
    else
    {
        Lista* stara_lista = Stos.pierwsza_lista;
        Stos.pierwsza_lista = lista;
        lista->nastepna_lista = stara_lista;
        lista->poprzednia_lista = nullptr;
        lista->licznik = 0;
        stara_lista->poprzednia_lista = lista;
        inkrementuj_licznik(stara_lista);
    }
}

void inkrementuj_licznik(Lista* aktualna_lista)
{
    aktualna_lista->licznik++;
    if (aktualna_lista->nastepna_lista != nullptr)
    {
        inkrementuj_licznik(aktualna_lista->nastepna_lista);
    }
}

void usun_liste(STOS& Stos)
{
    if (Stos.pierwsza_lista == nullptr)
    {
        return;
    }

    Lista* usuwana_lista = Stos.pierwsza_lista;

    usun_elementy_z_listy(Stos.pierwsza_lista->pierwszy_element);

    if (Stos.pierwsza_lista->nastepna_lista == nullptr)
    {
        Stos.pierwsza_lista = nullptr;
        Stos.utworzenie_listy = false;
        delete usuwana_lista;
    }
    else
    {
        Stos.pierwsza_lista = Stos.pierwsza_lista->nastepna_lista;
        Stos.pierwsza_lista->poprzednia_lista = nullptr;
        usuwana_lista->nastepna_lista = nullptr;
        delete usuwana_lista;
        dekrementuj_licznik(Stos.pierwsza_lista);
    }
}

void usun_elementy_z_listy(ElementListy* element_listy)
{
    if (element_listy == nullptr)
    {
        return;
    }
    else
    {
        ElementListy* nastepny_element = element_listy->nastepny_element;
        if (element_listy->poprzedni_element == nullptr)
        {

        }
        else
        {
            element_listy->poprzedni_element = nullptr;
        }
        element_listy->nastepny_element = nullptr;
        delete element_listy;
        usun_elementy_z_listy(nastepny_element);
    }
}

void dekrementuj_licznik(Lista* aktualna_lista)
{
    aktualna_lista->licznik--;
    if (aktualna_lista->nastepna_lista != nullptr)
    {
        dekrementuj_licznik(aktualna_lista->nastepna_lista);
    }
}

void dodaj_element(Lista* aktualna_lista, char instrukcja)
{
    ElementListy* nowy_element = new ElementListy;
    if (aktualna_lista->utworzenie_znaku == false)
    {
        nowy_element->element = instrukcja;
        nowy_element->poprzedni_element = nullptr;
        nowy_element->nastepny_element = nullptr;
        aktualna_lista->pierwszy_element = nowy_element;
        aktualna_lista->utworzenie_znaku = true;
    }
    else
    {
        ElementListy* stary_element = aktualna_lista->pierwszy_element;
        aktualna_lista->pierwszy_element = nowy_element;
        nowy_element->element = instrukcja;
        nowy_element->nastepny_element = stary_element;
        nowy_element->poprzedni_element = nullptr;
        stary_element->poprzedni_element = nowy_element;
    }
}

void kopiuj_liste(STOS& Stos)
{
    Lista* stara_lista = Stos.pierwsza_lista;
    Lista* lista = new Lista;
    Stos.pierwsza_lista = lista;
    lista->nastepna_lista = stara_lista;
    lista->poprzednia_lista = nullptr;
    lista->licznik = 0;
    stara_lista->poprzednia_lista = lista;
    inkrementuj_licznik(stara_lista);
    kopiuj_pierwszy_elementy(lista, stara_lista->pierwszy_element);
}

void kopiuj_pierwszy_elementy(Lista* aktualna_lista, ElementListy* element_starej_lista)
{
    if (element_starej_lista == nullptr)
    {
        return;
    }

    if (element_starej_lista->nastepny_element != nullptr)
    {
        kopiuj_pierwszy_elementy(aktualna_lista, element_starej_lista->nastepny_element);
    }
    else
    {
        dodaj_element(aktualna_lista, element_starej_lista->element);
        return;
    }

    dodaj_element(aktualna_lista, element_starej_lista->element);
}

void wypisz_listy(const Lista* aktualna_lista)
{
    if (aktualna_lista == nullptr)
    {
        return;
    }

    if (aktualna_lista->nastepna_lista != nullptr)
    {
        wypisz_listy(aktualna_lista->nastepna_lista);
    }
    else
    {
        cout << aktualna_lista->licznik << ": ";
        wypisz_char(aktualna_lista->pierwszy_element);
        cout << endl;
        return;
    }

    if (aktualna_lista->licznik >= 0)
    {
        cout << aktualna_lista->licznik << ": ";
        wypisz_char(aktualna_lista->pierwszy_element);
        cout << endl;
    }
}

void wypisz_char(const ElementListy* element_listy)
{
    if (element_listy == nullptr)
    {
        return;
    }

    cout << element_listy->element;

    if (element_listy->nastepny_element != nullptr)
    {
        wypisz_char(element_listy->nastepny_element);
    }
}

void zamien_dwie_pierwsze(STOS& Stos)
{
    Lista* pomocincza_pierwsza = Stos.pierwsza_lista;
    Lista* pomocnicza_druga = Stos.pierwsza_lista->nastepna_lista;
    Lista* pomocnicza_trzecia = Stos.pierwsza_lista->nastepna_lista->nastepna_lista;

    Stos.pierwsza_lista = pomocnicza_druga;
    Stos.pierwsza_lista->nastepna_lista = pomocincza_pierwsza;
    Stos.pierwsza_lista->nastepna_lista->licznik = pomocnicza_druga->licznik;
    Stos.pierwsza_lista->licznik = 0;
    Stos.pierwsza_lista->poprzednia_lista = nullptr;
    Stos.pierwsza_lista->nastepna_lista->poprzednia_lista = Stos.pierwsza_lista;

    if (pomocnicza_trzecia != nullptr)
    {
        Stos.pierwsza_lista->nastepna_lista->nastepna_lista = pomocnicza_trzecia;
    }
    else
    {
        Stos.pierwsza_lista->nastepna_lista->nastepna_lista = nullptr;
    }
}

void kopiuj_z_pozycji(STOS& Stos)
{
    if (Stos.pierwsza_lista == nullptr)
    {
        return;
    }

    if (Stos.pierwsza_lista->pierwszy_element->element == '0' && Stos.pierwsza_lista->pierwszy_element->nastepny_element == nullptr && Stos.pierwsza_lista->pierwszy_element->poprzedni_element == nullptr)
    {
        usun_liste(Stos);
        kopiuj_liste(Stos);
    }
    else
    {
        int suma = 0;
        int ilosc_wywolan = 1;
        znadz_pozycje(Stos.pierwsza_lista->pierwszy_element, suma, ilosc_wywolan);
        suma = suma + 1;
        doglebne_kopiowanie(Stos, Stos.pierwsza_lista, suma);
    }
}

void znadz_pozycje(ElementListy* element_listy, int& suma, int& ilosc_wywolan)
{
    if (element_listy != nullptr)
    {
        znadz_pozycje(element_listy->nastepny_element, suma, ilosc_wywolan);
    }
    else
    {
        return;
    }

    zlicz_sume(element_listy, suma, ilosc_wywolan);
    ilosc_wywolan = ilosc_wywolan * 10;
}

void zlicz_sume(const ElementListy* element_listy, int& suma, int& ilosc_wywolan)
{
    int element = 0;
    if (element_listy == nullptr)
    {
        return;
    }

    switch (element_listy->element)
    {
    case '0':
        element = 0;
        suma = suma * 10;
        break;
    case '1':
        element = 1;
        break;
    case '2':
        element = 2;
        break;
    case '3':
        element = 3;
        break;
    case '4':
        element = 4;
        break;
    case '5':
        element = 5;
        break;
    case '6':
        element = 6;
        break;
    case '7':
        element = 7;
        break;
    case '8':
        element = 8;
        break;
    case '9':
        element = 9;
        break;
    default:
        break;
    }

    suma = suma + element * (ilosc_wywolan);
}

void doglebne_kopiowanie(STOS& Stos, Lista* aktualna_lista, int& suma)
{
    if (aktualna_lista->licznik != suma)
    {
        doglebne_kopiowanie(Stos, aktualna_lista->nastepna_lista, suma);
    }
    else
    {
        usun_liste(Stos);
        kopiuj_wybrana_liste(Stos, aktualna_lista);
    }
}

void kopiuj_wybrana_liste(STOS& Stos, Lista* aktualna_lista)
{
    Lista* lista = new Lista;
    if (Stos.utworzenie_listy == false)
    {
        lista->licznik = 0;
        lista->poprzednia_lista = nullptr;
        lista->nastepna_lista = nullptr;
        Stos.pierwsza_lista = lista;
        Stos.utworzenie_listy = true;
    }
    else
    {
        Lista* stara_lista = Stos.pierwsza_lista;
        Stos.pierwsza_lista = lista;
        lista->nastepna_lista = stara_lista;
        lista->poprzednia_lista = nullptr;
        lista->licznik = 0;
        stara_lista->poprzednia_lista = lista;
        inkrementuj_licznik(stara_lista);
    }
    kopiuj_pierwszy_elementy(lista, aktualna_lista->pierwszy_element);
}

void negacja(STOS& Stos, Lista* aktualna_lista, ElementListy* element_listy)
{
    if (aktualna_lista->pierwszy_element == nullptr)
    {
        dodaj_element(Stos.pierwsza_lista, '-');
        return;
    }
    if (aktualna_lista->pierwszy_element->element == '-')
    {
        usun_liste(Stos);
        stworz_liste(Stos);
        return;
    }

    if (aktualna_lista->pierwszy_element == nullptr)
    {
        return;
    }

    if (element_listy->nastepny_element != nullptr)
    {
        negacja(Stos, aktualna_lista, element_listy->nastepny_element);
    }
    else
    {
        dodaj_element_koncowy(Stos, aktualna_lista, element_listy);
        return;
    }
}

void dodaj_element_koncowy(STOS& Stos, Lista* aktualna_lista, ElementListy* element_listy)
{
    ElementListy* stary_ostatni_element = element_listy;
    if (stary_ostatni_element->element == '-')
    {
        stary_ostatni_element->poprzedni_element->nastepny_element = nullptr;
        stary_ostatni_element->nastepny_element = nullptr;
        stary_ostatni_element->element = '*';
        delete stary_ostatni_element;
    }
    else
    {
        ElementListy* nowy_element = new ElementListy;
        stary_ostatni_element->nastepny_element = nowy_element;
        nowy_element->poprzedni_element = stary_ostatni_element;
        nowy_element->nastepny_element = nullptr;
        nowy_element->element = '-';
    }
}

void modul(STOS& Stos, Lista* aktualna_lista, ElementListy* element_listy)
{
    if (aktualna_lista->pierwszy_element == nullptr)
    {
        return;
    }
    if (aktualna_lista->pierwszy_element->element == '-')
    {
        usun_liste(Stos);
        stworz_liste(Stos);
        return;
    }

    if (element_listy->nastepny_element != nullptr)
    {
        modul(Stos, aktualna_lista, element_listy->nastepny_element);
    }
    else
    {
        modul_ostatni_element(aktualna_lista, element_listy);
        return;
    }
}

void modul_ostatni_element(Lista* aktualna_lista, ElementListy* element_listy)
{
    ElementListy* stary_ostatni_element = element_listy;
    ElementListy* przedostatni_element = element_listy->poprzedni_element;
    if (stary_ostatni_element->element == '-')
    {
        przedostatni_element->nastepny_element = nullptr;
        stary_ostatni_element->nastepny_element = nullptr;
        stary_ostatni_element->poprzedni_element = nullptr;
        stary_ostatni_element->element = '*';
    }
}

void pierwszy_znak(STOS& Stos, Lista* aktualna_lista, ElementListy* element_listy)
{
    if (aktualna_lista->pierwszy_element == nullptr)
    {
        return;
    }
    else
    {
        if (element_listy != nullptr)
        {
            cout << element_listy->element;
        }
        usun_liste(Stos);
        return;
    }
}

void obsluga_kropki(STOS& Stos)
{
    char dane_kropki;
    cin >> dane_kropki;
    if (Stos.utworzenie_listy == false)
    {
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, dane_kropki);
    }
    else
    {
        dodaj_element(Stos.pierwsza_lista, dane_kropki);
    }
}

void odlacz_pierwszy_znak(STOS& Stos)
{
    if (Stos.utworzenie_listy == false)
    {
        return;
    }

    if (Stos.pierwsza_lista->pierwszy_element == nullptr)
    {
        return;
    }

    char nowy_element;
    nowy_element = Stos.pierwsza_lista->pierwszy_element->element;


    if (Stos.pierwsza_lista->pierwszy_element->nastepny_element != nullptr)
    {
        ElementListy* stary_pierwszy = Stos.pierwsza_lista->pierwszy_element;
        Stos.pierwsza_lista->pierwszy_element = Stos.pierwsza_lista->pierwszy_element->nastepny_element;
        Stos.pierwsza_lista->pierwszy_element->poprzedni_element = nullptr;
        delete stary_pierwszy;
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, nowy_element);
    }
    else
    {
        usun_liste(Stos);
        stworz_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, nowy_element);
    }
}


void asci_na_liczbe(STOS& Stos)
{
    if (Stos.utworzenie_listy == false)
    {
        return;
    }

    if (Stos.pierwsza_lista->pierwszy_element == nullptr)
    {
        return;
    }

    int liczba_do_stworzeina;
    liczba_do_stworzeina = static_cast<int>(Stos.pierwsza_lista->pierwszy_element->element);
    usun_liste(Stos);
    stworz_liste(Stos);

    if (liczba_do_stworzeina == 0)
    {
        return;
    }

    tworz_liste_z_liczby(Stos, liczba_do_stworzeina);
}

void liczba_na_asci(STOS& Stos)
{
    if (Stos.utworzenie_listy == false)
    {
        return;
    }

    if (Stos.pierwsza_lista->pierwszy_element == nullptr)
    {
        return;
    }

    int suma = 0;
    int ilosc_wywolan = 1;
    suma_odwrocona_liczba(Stos.pierwsza_lista->pierwszy_element, suma, ilosc_wywolan);
    usun_liste(Stos);
    stworz_liste(Stos);

    char liczba_w_asci = static_cast<char>(suma);
    dodaj_element(Stos.pierwsza_lista, liczba_w_asci);
}

void suma_odwrocona_liczba(ElementListy* element_listy, int& suma, int& ilosc_wywolan)
{
    if (element_listy != nullptr)
    {
        zlicz_sume_odwrotna(element_listy, suma, ilosc_wywolan);
        ilosc_wywolan = ilosc_wywolan * 10;
        suma_odwrocona_liczba(element_listy->nastepny_element, suma, ilosc_wywolan);
    }
    else
    {
        return;
    }
}

void zlicz_sume_odwrotna(ElementListy* element_listy, int& suma, int& ilosc_wywolan)
{
    int element = 0;
    if (element_listy == nullptr)
    {
        return;
    }

    switch (element_listy->element)
    {
    case '0':
        element = 0;
        break;
    case '1':
        element = 1;
        break;
    case '2':
        element = 2;
        break;
    case '3':
        element = 3;
        break;
    case '4':
        element = 4;
        break;
    case '5':
        element = 5;
        break;
    case '6':
        element = 6;
        break;
    case '7':
        element = 7;
        break;
    case '8':
        element = 8;
        break;
    case '9':
        element = 9;
        break;
    default:
        break;
    }

    suma = suma + element * (ilosc_wywolan);
}

void tworz_liste_z_liczby(STOS& Stos, int& liczba_do_stworzenia)
{
    int pojedyncza_cyfra = 0;
    char element_listy;
    if (liczba_do_stworzenia >= 100)
    {
        pojedyncza_cyfra = liczba_do_stworzenia / 100;
        liczba_do_stworzenia = liczba_do_stworzenia - (100 * pojedyncza_cyfra);
        element_z_liczby(Stos, pojedyncza_cyfra, element_listy);
        tworz_liste_z_liczby(Stos, liczba_do_stworzenia);
    }
    else if (liczba_do_stworzenia >= 10)
    {
        pojedyncza_cyfra = liczba_do_stworzenia / 10;
        liczba_do_stworzenia = liczba_do_stworzenia - (10 * pojedyncza_cyfra);
        element_z_liczby(Stos, pojedyncza_cyfra, element_listy);
        tworz_liste_z_liczby(Stos, liczba_do_stworzenia);
    }
    else if (liczba_do_stworzenia > 0)
    {
        pojedyncza_cyfra = liczba_do_stworzenia;
        liczba_do_stworzenia = liczba_do_stworzenia - pojedyncza_cyfra;
        element_z_liczby(Stos, pojedyncza_cyfra, element_listy);
        tworz_liste_z_liczby(Stos, liczba_do_stworzenia);
    }
    else
    {
        return;
    }
}

void element_z_liczby(STOS& Stos, int& pojedyncza_cyfra, char& element_listy)
{
    switch (pojedyncza_cyfra)
    {
    case 0:
        element_listy = '0';
        break;
    case 1:
        element_listy = '1';
        break;
    case 2:
        element_listy = '2';
        break;
    case 3:
        element_listy = '3';
        break;
    case 4:
        element_listy = '4';
        break;
    case 5:
        element_listy = '5';
        break;
    case 6:
        element_listy = '6';
        break;
    case 7:
        element_listy = '7';
        break;
    case 8:
        element_listy = '8';
        break;
    case 9:
        element_listy = '9';
        break;
    default:
        return;
        break;
    }

    dodaj_element(Stos.pierwsza_lista, element_listy);
}

void scal_listy(STOS& Stos)
{
    zamien_dwie_pierwsze(Stos);

    scal_elementy(Stos, Stos.pierwsza_lista->pierwszy_element, Stos.pierwsza_lista->nastepna_lista->pierwszy_element);

    zamien_dwie_pierwsze(Stos);
    usun_liste(Stos);
}

void scal_elementy(STOS& Stos, ElementListy* element_pierwszej_listy, ElementListy* element_drugiej_listy)
{
    if (element_drugiej_listy == nullptr)
    {
        return;
    }

    if (element_pierwszej_listy->nastepny_element == nullptr)
    {
        scal_znaczki(Stos, element_pierwszej_listy, element_drugiej_listy);
        scal_elementy(Stos, element_pierwszej_listy, element_drugiej_listy->nastepny_element);
    }
    else if (element_pierwszej_listy->nastepny_element != nullptr)
    {
        scal_elementy(Stos, element_pierwszej_listy->nastepny_element, element_drugiej_listy);
    }
}

void scal_znaczki(STOS& Stos, ElementListy* element_pierwszej_listy, ElementListy* element_drugiej_listy)
{
    ElementListy* nowy_element = new ElementListy;
    char nowy_znaczek = element_drugiej_listy->element;
    element_pierwszej_listy->nastepny_element = nowy_element;
    nowy_element->poprzedni_element = element_pierwszej_listy;
    nowy_element->element = nowy_znaczek;
    nowy_element->nastepny_element = nullptr;
}

void negacja_logiczna(STOS& Stos)
{
    if (Stos.pierwsza_lista->utworzenie_znaku == false || (Stos.pierwsza_lista->pierwszy_element->element == '0' && Stos.pierwsza_lista->pierwszy_element->nastepny_element == nullptr))
    {
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '1');
    }
    else
    {
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '0');
    }
}

void lista_z_licznika(STOS& Stos)
{
    int liczba_do_stworzeina;
    liczba_do_stworzeina = Stos.licznik_wskaznika;
    stworz_liste(Stos);

    if (liczba_do_stworzeina == 0)
    {
        dodaj_element(Stos.pierwsza_lista, '0');
        return;
    }
    tworz_liste_z_liczby_wskaznika(Stos, liczba_do_stworzeina);
}

void tworz_liste_z_liczby_wskaznika(STOS& Stos, int& liczba_do_stworzenia)
{
    int pojedyncza_cyfra = 0;
    char element_listy;
    if (liczba_do_stworzenia >= 10000)
    {
        pojedyncza_cyfra = liczba_do_stworzenia / 10000;
        liczba_do_stworzenia = liczba_do_stworzenia - (10000 * pojedyncza_cyfra);
        element_z_liczby(Stos, pojedyncza_cyfra, element_listy);
        if (liczba_do_stworzenia == 0)
        {
            dodaj_element(Stos.pierwsza_lista, '0');
            dodaj_element(Stos.pierwsza_lista, '0');
            dodaj_element(Stos.pierwsza_lista, '0');
            dodaj_element(Stos.pierwsza_lista, '0');
        }
        tworz_liste_z_liczby_wskaznika(Stos, liczba_do_stworzenia);
    }
    else if (liczba_do_stworzenia >= 1000)
    {
        pojedyncza_cyfra = liczba_do_stworzenia / 1000;
        liczba_do_stworzenia = liczba_do_stworzenia - (1000 * pojedyncza_cyfra);
        element_z_liczby(Stos, pojedyncza_cyfra, element_listy);
        if (liczba_do_stworzenia == 0)
        {
            dodaj_element(Stos.pierwsza_lista, '0');
            dodaj_element(Stos.pierwsza_lista, '0');
            dodaj_element(Stos.pierwsza_lista, '0');
        }
        tworz_liste_z_liczby_wskaznika(Stos, liczba_do_stworzenia);
    }
    else if (liczba_do_stworzenia >= 100)
    {
        pojedyncza_cyfra = liczba_do_stworzenia / 100;
        liczba_do_stworzenia = liczba_do_stworzenia - (100 * pojedyncza_cyfra);
        element_z_liczby(Stos, pojedyncza_cyfra, element_listy);
        if (liczba_do_stworzenia > 0 && liczba_do_stworzenia < 10)
        {
            dodaj_element(Stos.pierwsza_lista, '0');
        }
        else if (liczba_do_stworzenia == 0)
        {
            dodaj_element(Stos.pierwsza_lista, '0');
            dodaj_element(Stos.pierwsza_lista, '0');
        }
        tworz_liste_z_liczby_wskaznika(Stos, liczba_do_stworzenia);
    }
    else if (liczba_do_stworzenia >= 10)
    {
        pojedyncza_cyfra = liczba_do_stworzenia / 10;
        liczba_do_stworzenia = liczba_do_stworzenia - (10 * pojedyncza_cyfra);
        element_z_liczby(Stos, pojedyncza_cyfra, element_listy);
        if (liczba_do_stworzenia == 0)
        {
            dodaj_element(Stos.pierwsza_lista, '0');
        }
        tworz_liste_z_liczby_wskaznika(Stos, liczba_do_stworzenia);
    }
    else if (liczba_do_stworzenia > 0)
    {
        pojedyncza_cyfra = liczba_do_stworzenia;
        liczba_do_stworzenia = liczba_do_stworzenia - pojedyncza_cyfra;
        element_z_liczby(Stos, pojedyncza_cyfra, element_listy);
        tworz_liste_z_liczby_wskaznika(Stos, liczba_do_stworzenia);
    }
    else
    {
        return;
    }
}

void sprawdz_rownosc(STOS& Stos)
{
    if (Stos.pierwsza_lista->pierwszy_element == nullptr && Stos.pierwsza_lista->nastepna_lista->pierwszy_element != nullptr)
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '0');
        return;
    }

    if (Stos.pierwsza_lista->pierwszy_element == nullptr && Stos.pierwsza_lista->nastepna_lista->pierwszy_element == nullptr)
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '1');
        return;
    }

    if (Stos.pierwsza_lista->nastepna_lista->pierwszy_element == nullptr)
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '0');
        return;
    }

    bool pierwsza_pusta = false;
    bool druga_pusta = false;
    czy_sa_puste(Stos, Stos.pierwsza_lista->pierwszy_element, pierwsza_pusta);
    czy_sa_puste(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element, druga_pusta);
    if (pierwsza_pusta == true && druga_pusta == true)
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '1');
    }
    else if ((pierwsza_pusta == true && druga_pusta == false) || (pierwsza_pusta == false && druga_pusta == true))
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '0');
    }
    else if (pierwsza_pusta == false && druga_pusta == false)
    {
        stworz_liste(Stos);
        odwroc_listy(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element);
        zamien_dwie_pierwsze(Stos);
        usun_liste(Stos);
        zamien_dwie_pierwsze(Stos);
        stworz_liste(Stos);
        odwroc_listy(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element);
        zamien_dwie_pierwsze(Stos);
        usun_liste(Stos);
        zamien_dwie_pierwsze(Stos);
        bool rowne_listy = true;
        sprawdz_elementy(Stos, Stos.pierwsza_lista->pierwszy_element, Stos.pierwsza_lista->nastepna_lista->pierwszy_element, rowne_listy);
        if (rowne_listy == true)
        {
            usun_liste(Stos);
            usun_liste(Stos);
            stworz_liste(Stos);
            dodaj_element(Stos.pierwsza_lista, '1');
        }
        else
        {
            usun_liste(Stos);
            usun_liste(Stos);
            stworz_liste(Stos);
            dodaj_element(Stos.pierwsza_lista, '0');
        }
    }
}

void czy_sa_puste(STOS& Stos, ElementListy* element_listy, bool& lista_pusta)
{
    if (element_listy != nullptr)
    {
        if (element_listy->element == '0' || element_listy->element == '-')
        {
            lista_pusta = true;
        }
        else
        {
            lista_pusta = false;
            return;
        }

        czy_sa_puste(Stos, element_listy->nastepny_element, lista_pusta);
    }
}

void odwroc_listy(STOS& Stos, ElementListy* element_listy)
{
    if (element_listy != nullptr)
    {
        dodaj_element(Stos.pierwsza_lista, element_listy->element);
        odwroc_listy(Stos, element_listy->nastepny_element);
    }
    if (element_listy == nullptr)
    {
        return;
    }
}

void sprawdz_elementy(STOS& Stos, ElementListy* element_pierwszej_listy, ElementListy* element_drugiej_listy, bool& rowne_listy)
{
    if (element_pierwszej_listy == nullptr || element_drugiej_listy == nullptr)
    {
        return;
    }

    if ((element_pierwszej_listy->element != '-' && element_drugiej_listy->element == '-') || (element_pierwszej_listy->element == '-' && element_drugiej_listy->element != '-'))
    {
        rowne_listy = false;
        return;
    }

    else if (element_pierwszej_listy->element == '-' && element_drugiej_listy->element == '-')
    {
        sprawdz_elementy(Stos, element_pierwszej_listy->nastepny_element, element_drugiej_listy->nastepny_element, rowne_listy);
    }

    else if ((element_pierwszej_listy->element != '0' && element_pierwszej_listy->element != '-') && (element_drugiej_listy->element != '0' && element_drugiej_listy->element != '-'))
    {
        if (element_pierwszej_listy->element == element_drugiej_listy->element)
        {
            sprawdz_elementy(Stos, element_pierwszej_listy->nastepny_element, element_drugiej_listy->nastepny_element, rowne_listy);
        }
        else
        {
            rowne_listy = false;
            return;
        }
    }

    else if (element_pierwszej_listy->element == '0' || element_pierwszej_listy->element == '-')
    {
        sprawdz_elementy(Stos, element_pierwszej_listy->nastepny_element, element_drugiej_listy, rowne_listy);
    }

    else if (element_drugiej_listy->element == '0' || element_drugiej_listy->element == '-')
    {
        sprawdz_elementy(Stos, element_pierwszej_listy, element_drugiej_listy->nastepny_element, rowne_listy);
    }
}

void mniejsze_liczby(STOS& Stos)
{
    stworz_liste(Stos);
    odwroc_listy(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element);
    zamien_dwie_pierwsze(Stos);
    usun_liste(Stos);
    zamien_dwie_pierwsze(Stos);
    stworz_liste(Stos);
    odwroc_listy(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element);
    zamien_dwie_pierwsze(Stos);
    usun_liste(Stos);
    zamien_dwie_pierwsze(Stos);

    bool pierwsza_ujemna = false;
    bool druga_ujemna = false;
    bool pierwsza_pusta = false;
    bool druga_pusta = false;
    czy_sa_puste(Stos, Stos.pierwsza_lista->pierwszy_element, pierwsza_pusta);
    czy_sa_puste(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element, druga_pusta);
    sprawdz_minus(Stos, Stos.pierwsza_lista->pierwszy_element, pierwsza_ujemna);
    sprawdz_minus(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element, druga_ujemna);

    if (pierwsza_pusta == true && druga_pusta == true && pierwsza_ujemna == true && druga_ujemna == false)
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '0');
        return;
    }
    else if (pierwsza_pusta == true && druga_pusta == true && pierwsza_ujemna == false && druga_ujemna == true)
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '0');
        return;
    }
    else if (pierwsza_pusta == true && druga_pusta == true && pierwsza_ujemna == true && druga_ujemna == true)
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '0');
        return;
    }
    else if (pierwsza_pusta == true && druga_pusta == true && pierwsza_ujemna == false && druga_ujemna == false)
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '0');
        return;
    }

    bool druga_wieksza = false;
    utnij_zera(Stos.pierwsza_lista, Stos.pierwsza_lista->pierwszy_element);
    utnij_zera(Stos.pierwsza_lista->nastepna_lista, Stos.pierwsza_lista->nastepna_lista->pierwszy_element);

    int dlugosc_pierwszej_listy = 0;
    int dlugosc_drugiej_listy = 0;
    sprawdz_dlugosc(Stos.pierwsza_lista->pierwszy_element, dlugosc_pierwszej_listy);
    sprawdz_dlugosc(Stos.pierwsza_lista->nastepna_lista->pierwszy_element, dlugosc_drugiej_listy);

    if (pierwsza_pusta == false && druga_pusta == false && pierwsza_ujemna == false && druga_ujemna == true)
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '1');
        return;
    }
    else if (pierwsza_pusta == false && druga_pusta == false && pierwsza_ujemna == true && druga_ujemna == false)
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '0');
        return;
    }
    else if ((dlugosc_pierwszej_listy > dlugosc_drugiej_listy) && pierwsza_ujemna == false && druga_ujemna == false)
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '1');
        return;
    }
    else if ((dlugosc_pierwszej_listy < dlugosc_drugiej_listy) && pierwsza_ujemna == false && druga_ujemna == false)
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '0');
        return;
    }
    else if ((dlugosc_pierwszej_listy > dlugosc_drugiej_listy) && pierwsza_ujemna == true && druga_ujemna == true)
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '0');
        return;
    }
    else if ((dlugosc_pierwszej_listy < dlugosc_drugiej_listy) && pierwsza_ujemna == true && druga_ujemna == true)
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '1');
        return;
    }
    else if (pierwsza_pusta == false && druga_pusta == false && pierwsza_ujemna == false && druga_ujemna == false)
    {
        sprawdz_elementy_mniejszy_wiekszy(Stos, Stos.pierwsza_lista->pierwszy_element, Stos.pierwsza_lista->nastepna_lista->pierwszy_element, pierwsza_ujemna, druga_ujemna, druga_wieksza);
    }
    else if (pierwsza_pusta == false && druga_pusta == false && pierwsza_ujemna == true && druga_ujemna == true)
    {
        sprawdz_elementy_mniejszy_wiekszy(Stos, Stos.pierwsza_lista->pierwszy_element, Stos.pierwsza_lista->nastepna_lista->pierwszy_element, pierwsza_ujemna, druga_ujemna, druga_wieksza);
    }

    if (druga_wieksza == true)
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '0');
    }
    else if (druga_wieksza == false)
    {
        usun_liste(Stos);
        usun_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '1');
    }
}

void sprawdz_dlugosc(ElementListy* element_listy, int& dlugosc)
{
    if (element_listy == nullptr)
    {
        return;
    }

    dlugosc++;
    sprawdz_dlugosc(element_listy->nastepny_element, dlugosc);
}

void sprawdz_minus(STOS& Stos, ElementListy* element_listy, bool& lista_ujemna)
{
    if (element_listy == nullptr)
    {
        return;
    }

    if (element_listy->element == '-')
    {
        lista_ujemna = true;
    }
    else
    {
        lista_ujemna = false;
    }
}

void sprawdz_elementy_mniejszy_wiekszy(STOS& Stos, ElementListy* element_pierwszej_listy, ElementListy* element_drugiej_listy, bool& pierwsza_ujemna, bool& druga_ujemna, bool& druga_wieksza)
{
    if (element_pierwszej_listy->nastepny_element == nullptr && element_drugiej_listy->nastepny_element == nullptr)
    {
        if (element_pierwszej_listy->element == element_drugiej_listy->element)
        {
            sprawdz_znaczek_mniejszy_wiekszy(Stos, element_pierwszej_listy, element_drugiej_listy, pierwsza_ujemna, druga_ujemna, druga_wieksza);
            return;
        }
        else
        {
            sprawdz_znaczek_mniejszy_wiekszy(Stos, element_pierwszej_listy, element_drugiej_listy, pierwsza_ujemna, druga_ujemna, druga_wieksza);
            return;
        }
    }

    else if (element_pierwszej_listy->nastepny_element == nullptr && element_drugiej_listy->nastepny_element != nullptr && pierwsza_ujemna == false && druga_ujemna == false)
    {
        druga_wieksza = true;
        return;
    }
    else if (element_pierwszej_listy->nastepny_element != nullptr && element_drugiej_listy->nastepny_element == nullptr && pierwsza_ujemna == false && druga_ujemna == false)
    {
        druga_wieksza = false;
        return;
    }
    else if (element_pierwszej_listy->nastepny_element == nullptr && element_drugiej_listy->nastepny_element != nullptr && pierwsza_ujemna == true && druga_ujemna == true)
    {
        druga_wieksza = false;
        return;
    }
    else if (element_pierwszej_listy->nastepny_element != nullptr && element_drugiej_listy->nastepny_element == nullptr && pierwsza_ujemna == true && druga_ujemna == true)
    {
        druga_wieksza = true;
        return;
    }

    else if (element_pierwszej_listy->element == element_drugiej_listy->element)
    {
        sprawdz_elementy_mniejszy_wiekszy(Stos, element_pierwszej_listy->nastepny_element, element_drugiej_listy->nastepny_element, pierwsza_ujemna, druga_ujemna, druga_wieksza);
    }
    else
    {
        sprawdz_znaczek_mniejszy_wiekszy(Stos, element_pierwszej_listy, element_drugiej_listy, pierwsza_ujemna, druga_ujemna, druga_wieksza);
    }
}

void sprawdz_znaczek_mniejszy_wiekszy(STOS& Stos, ElementListy* element_pierwszej_listy, ElementListy* element_drugiej_listy, bool& pierwsza_ujemna, bool& druga_ujemna, bool& druga_wieksza)
{
    int zmien_na_liczbe_pierwsza_lista = 0;
    int zmien_na_liczbe_druga_lista = 0;

    switch (element_pierwszej_listy->element)
    {
    case '0':
        zmien_na_liczbe_pierwsza_lista = 0;
        break;
    case '1':
        zmien_na_liczbe_pierwsza_lista = 1;
        break;
    case '2':
        zmien_na_liczbe_pierwsza_lista = 2;
        break;
    case '3':
        zmien_na_liczbe_pierwsza_lista = 3;
        break;
    case '4':
        zmien_na_liczbe_pierwsza_lista = 4;
        break;
    case '5':
        zmien_na_liczbe_pierwsza_lista = 5;
        break;
    case '6':
        zmien_na_liczbe_pierwsza_lista = 6;
        break;
    case '7':
        zmien_na_liczbe_pierwsza_lista = 7;
        break;
    case '8':
        zmien_na_liczbe_pierwsza_lista = 8;
        break;
    case '9':
        zmien_na_liczbe_pierwsza_lista = 9;
        break;
    default:
        return;
        break;
    }

    switch (element_drugiej_listy->element)
    {
    case '0':
        zmien_na_liczbe_druga_lista = 0;
        break;
    case '1':
        zmien_na_liczbe_druga_lista = 1;
        break;
    case '2':
        zmien_na_liczbe_druga_lista = 2;
        break;
    case '3':
        zmien_na_liczbe_druga_lista = 3;
        break;
    case '4':
        zmien_na_liczbe_druga_lista = 4;
        break;
    case '5':
        zmien_na_liczbe_druga_lista = 5;
        break;
    case '6':
        zmien_na_liczbe_druga_lista = 6;
        break;
    case '7':
        zmien_na_liczbe_druga_lista = 7;
        break;
    case '8':
        zmien_na_liczbe_druga_lista = 8;
        break;
    case '9':
        zmien_na_liczbe_druga_lista = 9;
        break;
    default:
        return;
        break;
    }
    if ((zmien_na_liczbe_druga_lista == zmien_na_liczbe_pierwsza_lista) && pierwsza_ujemna == true && druga_ujemna == true)
    {
        druga_wieksza = true;
        return;
    }
    else if ((zmien_na_liczbe_druga_lista == zmien_na_liczbe_pierwsza_lista) && pierwsza_ujemna == false && druga_ujemna == false)
    {
        druga_wieksza = true;
        return;
    }
    else if ((zmien_na_liczbe_druga_lista > zmien_na_liczbe_pierwsza_lista) && pierwsza_ujemna == false && druga_ujemna == false)
    {
        druga_wieksza = true;
        return;
    }
    else if ((zmien_na_liczbe_druga_lista > zmien_na_liczbe_pierwsza_lista) && pierwsza_ujemna == true && druga_ujemna == true)
    {
        druga_wieksza = false;
        return;
    }

}

void utnij_zera(Lista* aktualna_lista, ElementListy* element_listy)
{
    if (element_listy == nullptr)
    {
        return;
    }

    if (element_listy->element == '0' || element_listy->element == '-')
    {
        ElementListy* pomociczny_element = element_listy->nastepny_element;
        aktualna_lista->pierwszy_element = aktualna_lista->pierwszy_element->nastepny_element;
        delete element_listy;
        utnij_zera(aktualna_lista, pomociczny_element);
    }
    else
    {
        return;
    }
}


void skok_warunkowy(STOS& Stos, bool& skok_wykonany)
{
    int suma = 0;
    int ilosc_wywolan = 1;

    if (Stos.utworzenie_listy == false || Stos.pierwsza_lista == nullptr || Stos.pierwsza_lista->pierwszy_element == nullptr)
    {
        return;
    }

    suma_odwrocona_liczba(Stos.pierwsza_lista->pierwszy_element, suma, ilosc_wywolan);
    usun_liste(Stos);

    if (Stos.pierwsza_lista->pierwszy_element == nullptr || Stos.pierwsza_lista->pierwszy_element->element == '0')
    {
        skok_wykonany = false;
        usun_liste(Stos);
    }
    else
    {
        usun_liste(Stos);
        Stos.licznik_wskaznika = suma;
        skok_wykonany = true;
    }
}

void dodawnie_list(STOS& Stos)
{
    zamien_elementy(Stos);

    bool pierwsza_ujemna = false;
    bool druga_ujemna = false;

    sprawdz_minus(Stos, Stos.pierwsza_lista->pierwszy_element, pierwsza_ujemna);
    sprawdz_minus(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element, druga_ujemna);

    utnij_zera(Stos.pierwsza_lista, Stos.pierwsza_lista->pierwszy_element);
    utnij_zera(Stos.pierwsza_lista->nastepna_lista, Stos.pierwsza_lista->nastepna_lista->pierwszy_element);

    zamien_elementy(Stos);

    int nadwyzka_bitowa = 0;
    int pozyczka_bitowa = 0;
    if (pierwsza_ujemna == false && druga_ujemna == false)
    {
        stworz_liste(Stos);
        obie_ten_sam_znak(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element, Stos.pierwsza_lista->nastepna_lista->nastepna_lista->pierwszy_element, nadwyzka_bitowa);
        stworz_liste(Stos);
        odwroc_listy(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element);
        zamien_dwie_pierwsze(Stos);
        usun_liste(Stos);

        zamien_dwie_pierwsze(Stos);
        usun_liste(Stos);
        zamien_dwie_pierwsze(Stos);
        usun_liste(Stos);
        return;
    }
    else if (pierwsza_ujemna == true && druga_ujemna == true)
    {
        stworz_liste(Stos);
        obie_ten_sam_znak(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element, Stos.pierwsza_lista->nastepna_lista->nastepna_lista->pierwszy_element, nadwyzka_bitowa);
        stworz_liste(Stos);
        odwroc_listy(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element);
        zamien_dwie_pierwsze(Stos);
        usun_liste(Stos);
        negacja(Stos, Stos.pierwsza_lista, Stos.pierwsza_lista->pierwszy_element);

        zamien_dwie_pierwsze(Stos);
        usun_liste(Stos);
        zamien_dwie_pierwsze(Stos);
        usun_liste(Stos);
        return;
    }
    else if (pierwsza_ujemna == true && druga_ujemna == false)
    {
        kopiuj_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '2');
        kopiuj_z_pozycji(Stos);
        zamien_dwie_pierwsze(Stos);

        mniejsze_liczby(Stos);

        bool druga_wieksza = false;
        if (Stos.pierwsza_lista->pierwszy_element->element == '0')
        {
            druga_wieksza = true;
            usun_liste(Stos);
        }
        else if (Stos.pierwsza_lista->pierwszy_element->element == '1')
        {
            druga_wieksza = false;
            usun_liste(Stos);
        }

        stworz_liste(Stos);
        if (druga_wieksza == true)
        {
            obie_rozny_znak(Stos, Stos.pierwsza_lista->nastepna_lista->nastepna_lista->pierwszy_element, Stos.pierwsza_lista->nastepna_lista->pierwszy_element, pozyczka_bitowa);
        }
        else if (druga_wieksza == false)
        {
            obie_rozny_znak(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element, Stos.pierwsza_lista->nastepna_lista->nastepna_lista->pierwszy_element, pozyczka_bitowa);
        }

        bool czy_jest_pusta = false;
        czy_sa_puste(Stos, Stos.pierwsza_lista->pierwszy_element, czy_jest_pusta);

        utnij_zera(Stos.pierwsza_lista, Stos.pierwsza_lista->pierwszy_element);

        zamien_dwie_pierwsze(Stos);
        usun_liste(Stos);
        zamien_dwie_pierwsze(Stos);
        usun_liste(Stos);

        stworz_liste(Stos);
        odwroc_listy(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element);
        zamien_dwie_pierwsze(Stos);
        usun_liste(Stos);
        if (pierwsza_ujemna == true && druga_wieksza == false)
        {
            negacja(Stos, Stos.pierwsza_lista, Stos.pierwsza_lista->pierwszy_element);
        }

        if (czy_jest_pusta == true)
        {
            usun_liste(Stos);
            stworz_liste(Stos);
            dodaj_element(Stos.pierwsza_lista, '0');
        }
        return;
    }
    else if (pierwsza_ujemna == false && druga_ujemna == true)
    {
        kopiuj_liste(Stos);
        stworz_liste(Stos);
        dodaj_element(Stos.pierwsza_lista, '2');
        kopiuj_z_pozycji(Stos);
        zamien_dwie_pierwsze(Stos);
        mniejsze_liczby(Stos);

        bool druga_wieksza = false;
        if (Stos.pierwsza_lista->pierwszy_element->element == '0')
        {
            druga_wieksza = true;
            usun_liste(Stos);
        }
        else if (Stos.pierwsza_lista->pierwszy_element->element == '1')
        {
            druga_wieksza = false;
            usun_liste(Stos);
        }

        stworz_liste(Stos);
        if (druga_wieksza == true)
        {
            obie_rozny_znak(Stos, Stos.pierwsza_lista->nastepna_lista->nastepna_lista->pierwszy_element, Stos.pierwsza_lista->nastepna_lista->pierwszy_element, pozyczka_bitowa);
        }
        else if (druga_wieksza == false)
        {
            obie_rozny_znak(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element, Stos.pierwsza_lista->nastepna_lista->nastepna_lista->pierwszy_element, pozyczka_bitowa);
        }

        bool czy_jest_pusta = false;
        czy_sa_puste(Stos, Stos.pierwsza_lista->pierwszy_element, czy_jest_pusta);

        utnij_zera(Stos.pierwsza_lista, Stos.pierwsza_lista->pierwszy_element);

        zamien_dwie_pierwsze(Stos);
        usun_liste(Stos);
        zamien_dwie_pierwsze(Stos);
        usun_liste(Stos);

        stworz_liste(Stos);
        odwroc_listy(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element);
        zamien_dwie_pierwsze(Stos);
        usun_liste(Stos);
        if (druga_ujemna == true && druga_wieksza == true)
        {
            negacja(Stos, Stos.pierwsza_lista, Stos.pierwsza_lista->pierwszy_element);
        }

        if (czy_jest_pusta == true)
        {
            usun_liste(Stos);
            stworz_liste(Stos);
            dodaj_element(Stos.pierwsza_lista, '0');
        }
        return;
    }
}

void obie_ten_sam_znak(STOS& Stos, ElementListy* element_wiekszej_listy, ElementListy* element_mniejszej_listy, int& nadwyzka_bitowa)
{

    if (element_wiekszej_listy == nullptr && element_mniejszej_listy == nullptr)
    {
        if (nadwyzka_bitowa == 0)
        {
            return;
        }
        else if (nadwyzka_bitowa == 1)
        {
            dodaj_element(Stos.pierwsza_lista, '1');
            return;
        }
    }

    else if (element_wiekszej_listy != nullptr && element_mniejszej_listy == nullptr)
    {
        char znaczek = '0';
        dodaj_pojedynczy_znak(Stos, element_wiekszej_listy->element, znaczek, nadwyzka_bitowa);
        obie_ten_sam_znak(Stos, element_wiekszej_listy->nastepny_element, element_mniejszej_listy, nadwyzka_bitowa);
    }
    else if (element_wiekszej_listy == nullptr && element_mniejszej_listy != nullptr)
    {
        char znaczek = '0';
        dodaj_pojedynczy_znak(Stos, znaczek, element_mniejszej_listy->element, nadwyzka_bitowa);
        obie_ten_sam_znak(Stos, element_wiekszej_listy, element_mniejszej_listy->nastepny_element, nadwyzka_bitowa);
    }
    else if (element_wiekszej_listy != nullptr && element_mniejszej_listy != nullptr)
    {
        dodaj_pojedynczy_znak(Stos, element_wiekszej_listy->element, element_mniejszej_listy->element, nadwyzka_bitowa);
        obie_ten_sam_znak(Stos, element_wiekszej_listy->nastepny_element, element_mniejszej_listy->nastepny_element, nadwyzka_bitowa);
    }
}

void dodaj_pojedynczy_znak(STOS& Stos, char& element_wiekszej_listy, char& element_mniejszej_listy, int& nadwyzka_bitowa)
{
    int zmien_na_liczbe_wieksza_lista = element_wiekszej_listy - '0';
    int zmien_na_liczbe_mniejsza_lista = element_mniejszej_listy - '0';
    int suma_elementow = 0;
    char nowy_znak = '*';

    suma_elementow = zmien_na_liczbe_wieksza_lista + zmien_na_liczbe_mniejsza_lista + nadwyzka_bitowa;

    if (suma_elementow >= 10)
    {
        suma_elementow = suma_elementow - 10;
        nadwyzka_bitowa = 1;
    }
    else
    {
        nadwyzka_bitowa = 0;
    }

    switch (suma_elementow)
    {
    case 0:
        nowy_znak = '0';
        break;
    case 1:
        nowy_znak = '1';
        break;
    case 2:
        nowy_znak = '2';
        break;
    case 3:
        nowy_znak = '3';
        break;
    case 4:
        nowy_znak = '4';
        break;
    case 5:
        nowy_znak = '5';
        break;
    case 6:
        nowy_znak = '6';
        break;
    case 7:
        nowy_znak = '7';
        break;
    case 8:
        nowy_znak = '8';
        break;
    case 9:
        nowy_znak = '9';
        break;
    default:
        return;
        break;
    }
    dodaj_element(Stos.pierwsza_lista, nowy_znak);
}

void obie_rozny_znak(STOS& Stos, ElementListy* element_wiekszej_listy, ElementListy* element_mniejszej_listy, int& pozyczka_bitowa)
{
    if (element_wiekszej_listy == nullptr && element_mniejszej_listy == nullptr)
    {
        return;
    }

    else if (element_wiekszej_listy != nullptr && element_mniejszej_listy != nullptr)
    {
        odejmij_pojedynczy_znak(Stos, element_wiekszej_listy->element, element_mniejszej_listy->element, pozyczka_bitowa);
        obie_rozny_znak(Stos, element_wiekszej_listy->nastepny_element, element_mniejszej_listy->nastepny_element, pozyczka_bitowa);
    }
    else if (element_wiekszej_listy != nullptr && element_mniejszej_listy == nullptr)
    {
        char znaczek = '0';
        odejmij_pojedynczy_znak(Stos, element_wiekszej_listy->element, znaczek, pozyczka_bitowa);
        obie_rozny_znak(Stos, element_wiekszej_listy->nastepny_element, element_mniejszej_listy, pozyczka_bitowa);
    }
}

void odejmij_pojedynczy_znak(STOS& Stos, char& element_wiekszej_listy, char& element_mniejszej_listy, int& pozyczka_bitowa)
{
    int zmien_na_liczbe_wieksza_lista = element_wiekszej_listy - '0';
    int zmien_na_liczbe_mniejsza_lista = element_mniejszej_listy - '0';
    int roznica_elementow = 0;
    char nowy_znak = '*';

    roznica_elementow = zmien_na_liczbe_wieksza_lista - zmien_na_liczbe_mniejsza_lista - pozyczka_bitowa;

    if (roznica_elementow < 0)
    {
        roznica_elementow = roznica_elementow + 10;
        pozyczka_bitowa = 1;
    }
    else
    {
        pozyczka_bitowa = 0;
    }

    switch (roznica_elementow)
    {
    case 0:
        nowy_znak = '0';
        break;
    case 1:
        nowy_znak = '1';
        break;
    case 2:
        nowy_znak = '2';
        break;
    case 3:
        nowy_znak = '3';
        break;
    case 4:
        nowy_znak = '4';
        break;
    case 5:
        nowy_znak = '5';
        break;
    case 6:
        nowy_znak = '6';
        break;
    case 7:
        nowy_znak = '7';
        break;
    case 8:
        nowy_znak = '8';
        break;
    case 9:
        nowy_znak = '9';
        break;
    default:
        return;
        break;
    }

    dodaj_element(Stos.pierwsza_lista, nowy_znak);
}

void zamien_elementy(STOS& Stos)
{
    stworz_liste(Stos);
    odwroc_listy(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element);
    zamien_dwie_pierwsze(Stos);
    usun_liste(Stos);
    zamien_dwie_pierwsze(Stos);
    stworz_liste(Stos);
    odwroc_listy(Stos, Stos.pierwsza_lista->nastepna_lista->pierwszy_element);
    zamien_dwie_pierwsze(Stos);
    usun_liste(Stos);
    zamien_dwie_pierwsze(Stos);
}

void utnij_zera_koncowe(Lista* aktualna_lista, ElementListy* element_listy)
{
    if (element_listy->nastepny_element != nullptr)
    {
        utnij_zera_koncowe(aktualna_lista, element_listy->nastepny_element);
    }

    else if (element_listy->element == '0' || element_listy->element == '-')
    {
        ElementListy* pomociczny_element = element_listy->poprzedni_element;
        pomociczny_element->nastepny_element = nullptr;
        element_listy->poprzedni_element = nullptr;
        delete element_listy;
        utnij_zera(aktualna_lista, pomociczny_element);
    }
    else
    {
        return;
    }
}

void sprawdz_minus_koncowy(ElementListy* element_listy, bool& lista_ujemna)
{
    if (element_listy->nastepny_element == nullptr)
    {
        if (element_listy->element == '-')
        {
            lista_ujemna = true;
        }
        else
        {
            lista_ujemna = false;
        }
    }

    if (element_listy->nastepny_element != nullptr)
    {
        sprawdz_minus_koncowy(element_listy->nastepny_element, lista_ujemna);
    }
}

void pobierz_instrukcje(STOS& Stos)
{
    string instrukcje;
    getline(cin, instrukcje);
    bool koniec_programu = false;

    int rozmiar = 0;
    rozmiar = instrukcje.length();
    char* tablica_instrukcji = new char[rozmiar + 1];

    for (int i = 0; i < instrukcje.length(); i++)
    {
        tablica_instrukcji[i] = instrukcje[i];
    }

    Stos.licznik_wskaznika = 0;
    Stos.wskaznik_instrukcji = tablica_instrukcji;

    while (koniec_programu == false)
    {
        wykonaj_instrukcje(Stos, rozmiar, koniec_programu);
    }
}

void wykonaj_instrukcje(STOS& Stos, int rozmiar, bool& koniec_programu)
{
    if (Stos.licznik_wskaznika == rozmiar)
    {
        koniec_programu = true;
        delete[] Stos.wskaznik_instrukcji;
        return;
    }
    else
    {
        char instrukcja = Stos.wskaznik_instrukcji[Stos.licznik_wskaznika];
        bool skok_wykonany = false;
        switch (instrukcja)
        {
        case '\'':
            stworz_liste(Stos);
            break;
        case ',':
            usun_liste(Stos);
            break;
        case ':':
            kopiuj_liste(Stos);
            break;
        case '&':
            wypisz_listy(Stos.pierwsza_lista);
            break;
        case ';':
            zamien_dwie_pierwsze(Stos);
            break;
        case '@':
            kopiuj_z_pozycji(Stos);
            break;
        case '-':
            negacja(Stos, Stos.pierwsza_lista, Stos.pierwsza_lista->pierwszy_element);
            break;
        case '^':
            modul(Stos, Stos.pierwsza_lista, Stos.pierwsza_lista->pierwszy_element);
            break;
        case '>':
            pierwszy_znak(Stos, Stos.pierwsza_lista, Stos.pierwsza_lista->pierwszy_element);
            break;
        case '.':
            obsluga_kropki(Stos);
            break;
        case '$':
            odlacz_pierwszy_znak(Stos);
            break;
        case '[':
            asci_na_liczbe(Stos);
            break;
        case ']':
            liczba_na_asci(Stos);
            break;
        case '#':
            scal_listy(Stos);
            break;
        case '!':
            negacja_logiczna(Stos);
            break;
        case '~':
            lista_z_licznika(Stos);
            break;
        case '=':
            sprawdz_rownosc(Stos);
            break;
        case '<':
            mniejsze_liczby(Stos);
            break;
        case '?':
            skok_warunkowy(Stos, skok_wykonany);
            break;
        case '+':
            dodawnie_list(Stos);
            break;
        default:
            dodaj_element(Stos.pierwsza_lista, instrukcja);
            break;
        }

        if (instrukcja != '?')
        {
            Stos.licznik_wskaznika++;
        }

        if (instrukcja == '?' && skok_wykonany == false)
        {
            Stos.licznik_wskaznika++;
        }
    }
}
