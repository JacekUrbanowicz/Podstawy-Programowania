//Jacek Urbanowicz 203905 Elektronika i telekomunikacja Analiza raportów pogodowych METAR
#include <iostream>
#include <fstream>

using namespace std;

struct wyraz
{
	char znak[150];
	int dlugosc = 0;
};

struct metar
{
	char lotnisko[4];
	char dzien_i_czas[7];
	char wiatr[10];
	bool kopia_zmiany[4];
	char porywy_wiatru[7];
	bool kopia_porywy[4];
	char widzialnosc[4];
	char zjawiska[6][26];
	bool kopia_charakterystyka[26];
	bool kopia_intensywnosc[26];
	bool kopia_plus_lub_minus[26];
	int kopia_liczba_zjawisk[4];
	char zachmurzenie_i_podstawa_chmur[9][26];
	bool kopia_cumulonimbus[26];
	bool kopia_cumulus[26];
	int kopia_liczby_chmur[4];
	char VV[5];
	bool kopia_VV[4];
	char temperatura_i_punkt_rosy[7];
	bool kopia_temperatura_ujemna[4];
	bool kopia_rosa_ujemna[4];
	char cisnienie[8];
	char CAVOK[5];
	bool kopia_CAVOK[4];
	char NSW[3];
	bool kopia_NSW[4];
	char NSC[3];
	bool kopia_NSC[4];
	char SKC[3];
	bool kopia_SKC[4];
	char NCD[3];
	bool kopia_NCD[4];
	char CLR[3];
	bool kopia_CLR[4];
	char kierunek_widzialnosc[6][26];
	int kopia_kierunki_liczba[4];
	bool kopia_wystepuja_kierunki[26];
	bool kopia_wystepuja_2_kierunki[26];
};

struct wyswietlany_metar
{
	char lotnisko[50];
	int dzien;
	int godziny;
	int minuty;
	int sredni_kierunek;
	int srednia_predkosc;
	int szczyty_wiatru;
	int temperatura;
	int cisnienie;
};

int wczytaj_plik_i_wyraz();
char menu(char& chce);
void sprawdz_wyraz(wyraz& wyraz_testowy, metar metar_testowy[], int numer_metaru, bool& zmiany, bool& porywy, bool& temperatura_ujemna, bool& rosa_ujemna, int& liczba_chmur, bool cumulonimbus[], bool cumulus[], int& liczba_zjawisk, bool charakterystyka[], bool intensywnosc[], bool plus_lub_minus[], bool& cavok_wystepuje, bool& nsw_wystepuje, bool& nsc_wystepuje, bool& VV_wystepuje, bool& skc_wystepuje, bool& ncd_wystepuje, bool& clr_wystepuje, bool wystepuje_kierunek[], int& kierunki_liczba, bool wystepuja_2_kierunki[]);
void rozkoduj(metar metar_testowy[], int numer_metaru, bool& zmiany, bool& porywy, bool& temperatura_ujemna, bool& rosa_ujemna, int& liczba_chmur, bool cumulonimbus[], bool cumulus[], bool& koniec_pliku, int& liczba_zjawisk, bool charakterystyka[], bool intensywnosc[], bool plus_lub_minus[], ofstream& plik_wynikowy, bool& cavok_wystepuje, bool& nsw_wystepuje, bool& nsc_wystepuje, bool& VV_wystepuje, bool& skc_wystepuje, bool& ncd_wystepuje, bool& clr_wystepuje, bool wystepuje_kierunek[], int& kierunki_liczba, bool wystepuja_2_kierunki[]);
void tworzenie();
void wypelnij(char tablica[]);
void wyswietl_stworzony_metar(bool& szczyty, bool& ujemna, bool& jednostka, wyswietlany_metar metar_do_wyswietlenia, bool& chopin);
int wczytaj_plik_i_wyraz2();

int main()
{
	char chce = 'b';
	while (true)
	{
		menu(chce);
		if (chce == 'q')
		{
			break;
		}
	}
	return 0;
}

char menu(char& chce)
{
	if (chce == 'b')
	{
		cout << "Witaj jest to program analizujacy depesze metar" << endl;
		cout << "Autor: Jacek Urbanowicz 203905" << endl;
		cout << endl << "--------" << " MENU " << "--------" << endl;
		cout << "1. o wczytanie metarow dla Gdanska" << endl;
		cout << "2. q zamkniecie programu" << endl;
		cout << "3. b powrot do menu" << endl;
		cout << "4. i informacje techniczne" << endl;
		cout << "5. m tworzenie metaru" << endl;
		cout << "6. w wczytanie metarow dla Polski" << endl;
	}
	else
	{
		cout << endl << "--------" << " MENU " << "--------" << endl;
		cout << "1. o wczytanie metarow dla Gdanska" << endl;
		cout << "2. q zamkniecie programu" << endl;
		cout << "3. b powrot do menu" << endl;
		cout << "4. i informacje techniczne" << endl;
		cout << "5. m tworzenie metaru" << endl;
		cout << "6. w wczytanie metarow dla Polski" << endl;
	}
	cin >> chce;
	switch (chce)
	{
	case 'o':
	{
		wczytaj_plik_i_wyraz();
		return chce;
	}
	case 'q':
	{
		return chce;
	}
	case 'b':
	{
		system("cls");
		return chce;
	}
	case 'i':
	{
		system("cls");
		cout << endl << "-----------" << " Informacje " << "-----------" << endl;
		cout << "Porgram jest w stanie przetworzyc maksymalnie" << endl << "25 informacji o zjawiskach pogodowych i chmurach w jednym metarze" << endl;
		cout << "W celu powiekszenia ilosci zjawisk nalezy kontaktowac sie z autorem programu" << endl;
		return chce;
	}
	case 'm':
	{
		system("cls");
		cout << endl << "------------------------" << " Tworzenie metaru " << "------------------------" << endl;
		tworzenie();
		return chce;
	}
	case 'w':
	{
		wczytaj_plik_i_wyraz2();
		return chce;
	}
	default:
	{
		system("cls");
		cout << "Przepraszam, nie ma takiej opcji w menu" << endl << endl;
		return chce;
	}
	}
}

int wczytaj_plik_i_wyraz()
{
	wyraz wyraz_testowy;
	metar metar_testowy[4];

	ifstream plik_wejsciowy("Metar_Gdansk.txt");
	plik_wejsciowy.unsetf(ios_base::skipws);
	if (!plik_wejsciowy.is_open())
	{
		cout << "Nie udalo sie wczytac pliku";
		return 0;
	}

	char znak_testowy = '*';
	int i = 0;
	int numer_metaru = 1;
	bool porywy = false;
	bool zmiany = false;
	bool temperatura_ujemna = false;
	bool rosa_ujemna = false;
	int liczba_chmur = 0;
	bool cumulonimbus[26];
	bool cumulus[26];
	int liczba_zjawisk = 0;
	bool charakterystyka[26];
	bool intensywnosc[26];
	bool plus_lub_minus[26];
	bool koniec_pliku = false;
	bool cavok_wystepuje = false;
	bool nsw_wystepuje = false;
	bool nsc_wystepuje = false;
	bool VV_wystepuje = false;
	bool skc_wystepuje = false;
	bool ncd_wystepuje = false;
	bool clr_wystepuje = false;
	bool wystepuje_kierunek[26];
	int kierunki_liczba = 0;
	bool wystepuja_2_kierunki[26];

	ofstream plik_wynikowy("pogoda_gd.txt");

	while (!plik_wejsciowy.eof())
	{
		plik_wejsciowy >> znak_testowy;

		if (plik_wejsciowy.eof())
		{
			sprawdz_wyraz(wyraz_testowy, metar_testowy, numer_metaru, zmiany, porywy, temperatura_ujemna, rosa_ujemna, liczba_chmur, cumulonimbus, cumulus, liczba_zjawisk, charakterystyka, intensywnosc, plus_lub_minus, cavok_wystepuje, nsw_wystepuje, nsc_wystepuje, VV_wystepuje, skc_wystepuje, ncd_wystepuje, clr_wystepuje, wystepuje_kierunek, kierunki_liczba, wystepuja_2_kierunki);
			rozkoduj(metar_testowy, numer_metaru, zmiany, porywy, temperatura_ujemna, rosa_ujemna, liczba_chmur, cumulonimbus, cumulus, koniec_pliku, liczba_zjawisk, charakterystyka, intensywnosc, plus_lub_minus, plik_wynikowy, cavok_wystepuje, nsw_wystepuje, nsc_wystepuje, VV_wystepuje, skc_wystepuje, ncd_wystepuje, clr_wystepuje, wystepuje_kierunek, kierunki_liczba, wystepuja_2_kierunki);

			koniec_pliku = true;
			system("cls");
			numer_metaru = numer_metaru - 2;
			for (int i = 0; i < 3; i++)
			{
				rozkoduj(metar_testowy, numer_metaru, zmiany, porywy, temperatura_ujemna, rosa_ujemna, liczba_chmur, cumulonimbus, cumulus, koniec_pliku, liczba_zjawisk, charakterystyka, intensywnosc, plus_lub_minus, plik_wynikowy, cavok_wystepuje, nsw_wystepuje, nsc_wystepuje, VV_wystepuje, skc_wystepuje, ncd_wystepuje, clr_wystepuje, wystepuje_kierunek, kierunki_liczba, wystepuja_2_kierunki);
				numer_metaru++;
			}

			i = -1;
			wyraz_testowy.dlugosc = 0;
			numer_metaru++;
		}

		else if (znak_testowy != 32 && znak_testowy != 10)
		{
			wyraz_testowy.znak[i] = znak_testowy;
			wyraz_testowy.dlugosc++;
		}

		else if (znak_testowy == 32)
		{
			sprawdz_wyraz(wyraz_testowy, metar_testowy, numer_metaru, zmiany, porywy, temperatura_ujemna, rosa_ujemna, liczba_chmur, cumulonimbus, cumulus, liczba_zjawisk, charakterystyka, intensywnosc, plus_lub_minus, cavok_wystepuje, nsw_wystepuje, nsc_wystepuje, VV_wystepuje, skc_wystepuje, ncd_wystepuje, clr_wystepuje, wystepuje_kierunek, kierunki_liczba, wystepuja_2_kierunki);
			i = -1;
			wyraz_testowy.dlugosc = 0;
		}

		else if (znak_testowy == 10)
		{
			sprawdz_wyraz(wyraz_testowy, metar_testowy, numer_metaru, zmiany, porywy, temperatura_ujemna, rosa_ujemna, liczba_chmur, cumulonimbus, cumulus, liczba_zjawisk, charakterystyka, intensywnosc, plus_lub_minus, cavok_wystepuje, nsw_wystepuje, nsc_wystepuje, VV_wystepuje, skc_wystepuje, ncd_wystepuje, clr_wystepuje, wystepuje_kierunek, kierunki_liczba, wystepuja_2_kierunki);
			rozkoduj(metar_testowy, numer_metaru, zmiany, porywy, temperatura_ujemna, rosa_ujemna, liczba_chmur, cumulonimbus, cumulus, koniec_pliku, liczba_zjawisk, charakterystyka, intensywnosc, plus_lub_minus, plik_wynikowy, cavok_wystepuje, nsw_wystepuje, nsc_wystepuje, VV_wystepuje, skc_wystepuje, ncd_wystepuje, clr_wystepuje, wystepuje_kierunek, kierunki_liczba, wystepuja_2_kierunki);
			i = -1;
			wyraz_testowy.dlugosc = 0;
			numer_metaru++;
		}

		i++;

	}
	plik_wejsciowy.close();
	plik_wynikowy.close();
}

void sprawdz_wyraz(wyraz& wyraz_testowy, metar metar_testowy[], int numer_metaru, bool& zmiany, bool& porywy, bool& temperatura_ujemna, bool& rosa_ujemna, int& liczba_chmur, bool cumulonimbus[], bool cumulus[], int& liczba_zjawisk, bool charakterystyka[], bool intensywnosc[], bool plus_lub_minus[], bool& cavok_wystepuje, bool& nsw_wystepuje, bool& nsc_wystepuje, bool& VV_wystepuje, bool& skc_wystepuje, bool& ncd_wystepuje, bool& clr_wystepuje, bool wystepuje_kierunek[], int& kierunki_liczba, bool wystepuja_2_kierunki[])
{
	int zmienna_pomocincza = 0;
	zmienna_pomocincza = numer_metaru % 3;

	if (wyraz_testowy.dlugosc == 4 && wyraz_testowy.znak[0] == 'E' && wyraz_testowy.znak[1] == 'P')
	{
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].lotnisko[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 7 && wyraz_testowy.znak[6] == 'Z')
	{
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].dzien_i_czas[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 7 && wyraz_testowy.znak[5] == 'K' && wyraz_testowy.znak[6] == 'T')
	{
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].wiatr[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 10 && wyraz_testowy.znak[5] == 'G')
	{
		porywy = true;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].wiatr[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 7 && wyraz_testowy.znak[3] == 'V')
	{
		zmiany = true;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].porywy_wiatru[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 4 && (wyraz_testowy.znak[0] == '0' || wyraz_testowy.znak[0] == '1' || wyraz_testowy.znak[0] == '2' || wyraz_testowy.znak[0] == '3' || wyraz_testowy.znak[0] == '4' || wyraz_testowy.znak[0] == '5' || wyraz_testowy.znak[0] == '6' || wyraz_testowy.znak[0] == '7' || wyraz_testowy.znak[0] == '8' || wyraz_testowy.znak[0] == '9') && (wyraz_testowy.znak[1] == '0' || wyraz_testowy.znak[1] == '1' || wyraz_testowy.znak[1] == '2' || wyraz_testowy.znak[1] == '3' || wyraz_testowy.znak[1] == '4' || wyraz_testowy.znak[1] == '5' || wyraz_testowy.znak[1] == '6' || wyraz_testowy.znak[1] == '7' || wyraz_testowy.znak[1] == '8' || wyraz_testowy.znak[1] == '9') && (wyraz_testowy.znak[2] == '0' || wyraz_testowy.znak[2] == '1' || wyraz_testowy.znak[2] == '2' || wyraz_testowy.znak[2] == '3' || wyraz_testowy.znak[2] == '4' || wyraz_testowy.znak[2] == '5' || wyraz_testowy.znak[2] == '6' || wyraz_testowy.znak[2] == '7' || wyraz_testowy.znak[2] == '8' || wyraz_testowy.znak[2] == '9') && (wyraz_testowy.znak[3] == '0' || wyraz_testowy.znak[3] == '1' || wyraz_testowy.znak[3] == '2' || wyraz_testowy.znak[3] == '3' || wyraz_testowy.znak[3] == '4' || wyraz_testowy.znak[3] == '5' || wyraz_testowy.znak[3] == '6' || wyraz_testowy.znak[3] == '7' || wyraz_testowy.znak[3] == '8' || wyraz_testowy.znak[3] == '9'))
	{
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].widzialnosc[i] = wyraz_testowy.znak[i];
		}
	}
	else if ((wyraz_testowy.dlugosc == 5 && wyraz_testowy.znak[0] == 'Q') || (wyraz_testowy.dlugosc == 5 && wyraz_testowy.znak[0] == 'A'))
	{
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].cisnienie[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 5 && wyraz_testowy.znak[2] == '/')
	{
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 6 && wyraz_testowy.znak[3] == '/' && wyraz_testowy.znak[0] == 'M')
	{
		temperatura_ujemna = true;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 6 && wyraz_testowy.znak[2] == '/' && wyraz_testowy.znak[3] == 'M')
	{
		rosa_ujemna = true;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 7 && wyraz_testowy.znak[3] == '/' && wyraz_testowy.znak[0] == 'M' && wyraz_testowy.znak[4] == 'M')
	{
		temperatura_ujemna = true;
		rosa_ujemna = true;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 6 && (wyraz_testowy.znak[0] == 'F' || wyraz_testowy.znak[0] == 'S' || wyraz_testowy.znak[0] == 'B' || wyraz_testowy.znak[0] == 'O') && (wyraz_testowy.znak[1] == 'E' || wyraz_testowy.znak[1] == 'C' || wyraz_testowy.znak[1] == 'K' || wyraz_testowy.znak[1] == 'V') && (wyraz_testowy.znak[2] == 'W' || wyraz_testowy.znak[2] == 'T' || wyraz_testowy.znak[2] == 'N' || wyraz_testowy.znak[2] == 'C'))
	{
		liczba_chmur++;
		cumulonimbus[liczba_chmur] = false;
		cumulus[liczba_chmur] = false;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[i][liczba_chmur] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 5 && wyraz_testowy.znak[0] == 'V' && wyraz_testowy.znak[1] == 'V')
	{
		VV_wystepuje = true;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].VV[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 8 && (wyraz_testowy.znak[0] == 'F' || wyraz_testowy.znak[0] == 'S' || wyraz_testowy.znak[0] == 'B' || wyraz_testowy.znak[0] == 'O') && (wyraz_testowy.znak[1] == 'E' || wyraz_testowy.znak[1] == 'C' || wyraz_testowy.znak[1] == 'K' || wyraz_testowy.znak[1] == 'V') && (wyraz_testowy.znak[2] == 'W' || wyraz_testowy.znak[2] == 'T' || wyraz_testowy.znak[2] == 'N' || wyraz_testowy.znak[2] == 'C') && (wyraz_testowy.znak[6] == 'C') && (wyraz_testowy.znak[7] == 'B'))
	{
		liczba_chmur++;
		cumulonimbus[liczba_chmur] = true;
		cumulus[liczba_chmur] = false;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[i][liczba_chmur] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 9 && (wyraz_testowy.znak[0] == 'F' || wyraz_testowy.znak[0] == 'S' || wyraz_testowy.znak[0] == 'B' || wyraz_testowy.znak[0] == 'O') && (wyraz_testowy.znak[1] == 'E' || wyraz_testowy.znak[1] == 'C' || wyraz_testowy.znak[1] == 'K' || wyraz_testowy.znak[1] == 'V') && (wyraz_testowy.znak[2] == 'W' || wyraz_testowy.znak[2] == 'T' || wyraz_testowy.znak[2] == 'N' || wyraz_testowy.znak[2] == 'C') && (wyraz_testowy.znak[6] == 'T') && (wyraz_testowy.znak[7] == 'C') && (wyraz_testowy.znak[8] == 'U'))
	{
		liczba_chmur++;
		cumulus[liczba_chmur] = true;
		cumulonimbus[liczba_chmur] = false;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[i][liczba_chmur] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 2 && (wyraz_testowy.znak[0] == 'B' || wyraz_testowy.znak[0] == 'D' || wyraz_testowy.znak[0] == 'F' || wyraz_testowy.znak[0] == 'G' || wyraz_testowy.znak[0] == 'H' || wyraz_testowy.znak[0] == 'I' || wyraz_testowy.znak[0] == 'P' || wyraz_testowy.znak[0] == 'R' || wyraz_testowy.znak[0] == 'S' || wyraz_testowy.znak[0] == 'U' || wyraz_testowy.znak[0] == 'V') && (wyraz_testowy.znak[1] == 'R' || wyraz_testowy.znak[1] == 'S' || wyraz_testowy.znak[1] == 'U' || wyraz_testowy.znak[1] == 'Z' || wyraz_testowy.znak[1] == 'C' || wyraz_testowy.znak[1] == 'G' || wyraz_testowy.znak[1] == 'E' || wyraz_testowy.znak[1] == 'O' || wyraz_testowy.znak[1] == 'Y' || wyraz_testowy.znak[1] == 'A' || wyraz_testowy.znak[1] == 'N' || wyraz_testowy.znak[1] == 'Q' || wyraz_testowy.znak[1] == 'P'))
	{
		liczba_zjawisk++;
		charakterystyka[liczba_zjawisk] = false;
		intensywnosc[liczba_zjawisk] = false;
		plus_lub_minus[liczba_zjawisk] = false;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].zjawiska[i][liczba_zjawisk] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 4 && (wyraz_testowy.znak[0] == 'B' || wyraz_testowy.znak[0] == 'D' || wyraz_testowy.znak[0] == 'M' || wyraz_testowy.znak[0] == 'P' || wyraz_testowy.znak[0] == 'F' || wyraz_testowy.znak[0] == 'S' || wyraz_testowy.znak[0] == 'T') && (wyraz_testowy.znak[1] == 'C' || wyraz_testowy.znak[1] == 'R' || wyraz_testowy.znak[1] == 'I' || wyraz_testowy.znak[1] == 'L' || wyraz_testowy.znak[1] == 'Z' || wyraz_testowy.znak[1] == 'H' || wyraz_testowy.znak[1] == 'S'))
	{
		liczba_zjawisk++;
		charakterystyka[liczba_zjawisk] = true;
		intensywnosc[liczba_zjawisk] = false;
		plus_lub_minus[liczba_zjawisk] = false;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].zjawiska[i][liczba_zjawisk] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 3 && (wyraz_testowy.znak[0] == '+' || wyraz_testowy.znak[0] == '-'))
	{
		liczba_zjawisk++;
		charakterystyka[liczba_zjawisk] = false;
		intensywnosc[liczba_zjawisk] = true;
		plus_lub_minus[liczba_zjawisk] = true;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].zjawiska[i][liczba_zjawisk] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 5 && (wyraz_testowy.znak[0] == '+' || wyraz_testowy.znak[0] == '-'))
	{
		liczba_zjawisk++;
		charakterystyka[liczba_zjawisk] = true;
		intensywnosc[liczba_zjawisk] = true;
		plus_lub_minus[liczba_zjawisk] = true;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].zjawiska[i][liczba_zjawisk] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 4 && (wyraz_testowy.znak[0] == 'R' || wyraz_testowy.znak[0] == 'V') && (wyraz_testowy.znak[1] == 'E' || wyraz_testowy.znak[1] == 'C'))
	{
		liczba_zjawisk++;
		charakterystyka[liczba_zjawisk] = false;
		intensywnosc[liczba_zjawisk] = true;
		plus_lub_minus[liczba_zjawisk] = false;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].zjawiska[i][liczba_zjawisk] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 6 && (wyraz_testowy.znak[0] == 'R' || wyraz_testowy.znak[0] == 'V') && (wyraz_testowy.znak[1] == 'E' || wyraz_testowy.znak[1] == 'C'))
	{
		liczba_zjawisk++;
		charakterystyka[liczba_zjawisk] = true;
		intensywnosc[liczba_zjawisk] = true;
		plus_lub_minus[liczba_zjawisk] = false;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].zjawiska[i][liczba_zjawisk] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 5 && wyraz_testowy.znak[0] == 'C' && wyraz_testowy.znak[1] == 'A' && wyraz_testowy.znak[2] == 'V' && wyraz_testowy.znak[3] == 'O' && wyraz_testowy.znak[4] == 'K')
	{
		cavok_wystepuje = true;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].CAVOK[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 3 && wyraz_testowy.znak[0] == 'N' && wyraz_testowy.znak[1] == 'S' && wyraz_testowy.znak[2] == 'W')
	{
		nsw_wystepuje = true;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].NSW[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 3 && wyraz_testowy.znak[0] == 'N' && wyraz_testowy.znak[1] == 'S' && wyraz_testowy.znak[2] == 'C')
	{
		nsc_wystepuje = true;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].NSC[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 3 && wyraz_testowy.znak[0] == 'S' && wyraz_testowy.znak[1] == 'K' && wyraz_testowy.znak[2] == 'C')
	{
		skc_wystepuje = true;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].SKC[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 3 && wyraz_testowy.znak[0] == 'N' && wyraz_testowy.znak[1] == 'C' && wyraz_testowy.znak[2] == 'D')
	{
		ncd_wystepuje = true;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].NCD[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 3 && wyraz_testowy.znak[0] == 'C' && wyraz_testowy.znak[1] == 'L' && wyraz_testowy.znak[2] == 'R')
	{
		clr_wystepuje = true;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].CLR[i] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 5 && (wyraz_testowy.znak[4] == 'N' || wyraz_testowy.znak[4] == 'E' || wyraz_testowy.znak[4] == 'S' || wyraz_testowy.znak[4] == 'W') && (wyraz_testowy.znak[0] == '0' || wyraz_testowy.znak[0] == '1' || wyraz_testowy.znak[0] == '2' || wyraz_testowy.znak[0] == '3' || wyraz_testowy.znak[0] == '4' || wyraz_testowy.znak[0] == '5' || wyraz_testowy.znak[0] == '6' || wyraz_testowy.znak[0] == '7' || wyraz_testowy.znak[0] == '8' || wyraz_testowy.znak[0] == '9'))
	{
		kierunki_liczba++;
		wystepuje_kierunek[kierunki_liczba] = true;
		wystepuja_2_kierunki[kierunki_liczba] = false;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[i][kierunki_liczba] = wyraz_testowy.znak[i];
		}
	}
	else if (wyraz_testowy.dlugosc == 6 && (wyraz_testowy.znak[4] == 'N' || wyraz_testowy.znak[4] == 'E' || wyraz_testowy.znak[4] == 'S' || wyraz_testowy.znak[4] == 'W') && (wyraz_testowy.znak[5] == 'N' || wyraz_testowy.znak[5] == 'E' || wyraz_testowy.znak[5] == 'S' || wyraz_testowy.znak[5] == 'W') && (wyraz_testowy.znak[0] == '0' || wyraz_testowy.znak[0] == '1' || wyraz_testowy.znak[0] == '2' || wyraz_testowy.znak[0] == '3' || wyraz_testowy.znak[0] == '4' || wyraz_testowy.znak[0] == '5' || wyraz_testowy.znak[0] == '6' || wyraz_testowy.znak[0] == '7' || wyraz_testowy.znak[0] == '8' || wyraz_testowy.znak[0] == '9'))
	{
		kierunki_liczba++;
		wystepuje_kierunek[kierunki_liczba] = true;
		wystepuja_2_kierunki[kierunki_liczba] = true;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[i][kierunki_liczba] = wyraz_testowy.znak[i];
		}
	}
	else
	{
		cout << endl;
		for (int i = 0; i < wyraz_testowy.dlugosc; i++)
		{
			cout << wyraz_testowy.znak[i];
		}
		cout << " Wyraz nie znany" << endl;
	}
}

void rozkoduj(metar metar_testowy[], int numer_metaru, bool& zmiany, bool& porywy, bool& temperatura_ujemna, bool& rosa_ujemna, int& liczba_chmur, bool cumulonimbus[], bool cumulus[], bool& koniec_pliku, int& liczba_zjawisk, bool charakterystyka[], bool intensywnosc[], bool plus_lub_minus[], ofstream& plik_wynikowy, bool& cavok_wystepuje, bool& nsw_wystepuje, bool& nsc_wystepuje, bool& VV_wystepuje, bool& skc_wystepuje, bool& ncd_wystepuje, bool& clr_wystepuje, bool wystepuje_kierunek[], int& kierunki_liczba, bool wystepuja_2_kierunki[])
{
	int zmienna_pomocincza = 0;
	zmienna_pomocincza = numer_metaru % 3;

	cout << endl << "Jestem metarem nr. " << numer_metaru;
	cout << endl << "Informacje Pogodowe: " << endl;

	if (koniec_pliku == false)
	{
		plik_wynikowy << endl << "Metar nr. " << numer_metaru;
		plik_wynikowy << endl << "Informacje Pogodowe: " << endl;
		plik_wynikowy << "Lotnisko: ";
	}

	if (metar_testowy[zmienna_pomocincza].lotnisko[0] == 'E' && metar_testowy[zmienna_pomocincza].lotnisko[1] == 'P')
	{
		cout << "Lotnisko: ";
		if (metar_testowy[zmienna_pomocincza].lotnisko[2] == 'G' && metar_testowy[zmienna_pomocincza].lotnisko[3] == 'D')
		{
			cout << "Gdansk" << endl;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Gdansk " << endl;
			}
		}
		if (metar_testowy[zmienna_pomocincza].lotnisko[2] == 'W' && metar_testowy[zmienna_pomocincza].lotnisko[3] == 'A')
		{
			cout << "Warszawa" << endl;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Warszawa " << endl;
			}
		}
		if (metar_testowy[zmienna_pomocincza].lotnisko[2] == 'K' && metar_testowy[zmienna_pomocincza].lotnisko[3] == 'K')
		{
			cout << "Krakow" << endl;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Krakow " << endl;
			}
		}
		if (metar_testowy[zmienna_pomocincza].lotnisko[2] == 'K' && metar_testowy[zmienna_pomocincza].lotnisko[3] == 'T')
		{
			cout << "Katowice" << endl;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Katowice " << endl;
			}
		}
		if (metar_testowy[zmienna_pomocincza].lotnisko[2] == 'W' && metar_testowy[zmienna_pomocincza].lotnisko[3] == 'R')
		{
			cout << "Wroclaw" << endl;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Wroclaw " << endl;
			}
		}
		if (metar_testowy[zmienna_pomocincza].lotnisko[2] == 'M' && metar_testowy[zmienna_pomocincza].lotnisko[3] == 'O')
		{
			cout << "Warszawa" << endl;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Warszawa " << endl;
			}
		}
		if (metar_testowy[zmienna_pomocincza].lotnisko[2] == 'P' && metar_testowy[zmienna_pomocincza].lotnisko[3] == 'O')
		{
			cout << "Poznan" << endl;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Poznan " << endl;
			}
		}
		if (metar_testowy[zmienna_pomocincza].lotnisko[2] == 'R' && metar_testowy[zmienna_pomocincza].lotnisko[3] == 'Z')
		{
			cout << "Rzeszow" << endl;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Rzeszow " << endl;
			}
		}
		if (metar_testowy[zmienna_pomocincza].lotnisko[2] == 'S' && metar_testowy[zmienna_pomocincza].lotnisko[3] == 'C')
		{
			cout << "Szczecin" << endl;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Szczecin " << endl;
			}
		}
		if (metar_testowy[zmienna_pomocincza].lotnisko[2] == 'L' && metar_testowy[zmienna_pomocincza].lotnisko[3] == 'B')
		{
			cout << "Lublin" << endl;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Lublin " << endl;
			}
		}
		if (metar_testowy[zmienna_pomocincza].lotnisko[2] == 'B' && metar_testowy[zmienna_pomocincza].lotnisko[3] == 'Y')
		{
			cout << "Bydgoszcz" << endl;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Bydgoszcz " << endl;
			}
		}
		if (metar_testowy[zmienna_pomocincza].lotnisko[2] == 'L' && metar_testowy[zmienna_pomocincza].lotnisko[3] == 'L')
		{
			cout << "Lodz" << endl;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Lodz " << endl;
			}
		}
		if (metar_testowy[zmienna_pomocincza].lotnisko[2] == 'S' && metar_testowy[zmienna_pomocincza].lotnisko[3] == 'Y')
		{
			cout << "Olsztyn" << endl;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Olsztyn " << endl;
			}
		}
		if (metar_testowy[zmienna_pomocincza].lotnisko[2] == 'R' && metar_testowy[zmienna_pomocincza].lotnisko[3] == 'A')
		{
			cout << "Radom" << endl;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Radom " << endl;
			}
		}
		if (metar_testowy[zmienna_pomocincza].lotnisko[2] == 'Z' && metar_testowy[zmienna_pomocincza].lotnisko[3] == 'G')
		{
			cout << "Zielona Gora" << endl;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Zielona Gora " << endl;
			}
		}
	}

	if (metar_testowy[zmienna_pomocincza].dzien_i_czas[6] == 'Z')
	{
		cout << "Data: ";
		int dzien = 0;
		if (metar_testowy[zmienna_pomocincza].dzien_i_czas[0] == '0')
		{
			dzien = dzien;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[0] == '1')
		{
			dzien = dzien + 10;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[0] == '2')
		{
			dzien = dzien + 20;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[0] == '3')
		{
			dzien = dzien + 30;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].dzien_i_czas[1] == '0')
		{
			dzien = dzien;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[1] == '1')
		{
			dzien = dzien + 1;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[1] == '2')
		{
			dzien = dzien + 2;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[1] == '3')
		{
			dzien = dzien + 3;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[1] == '4')
		{
			dzien = dzien + 4;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[1] == '5')
		{
			dzien = dzien + 5;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[1] == '6')
		{
			dzien = dzien + 6;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[1] == '7')
		{
			dzien = dzien + 7;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[1] == '8')
		{
			dzien = dzien + 8;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[1] == '9')
		{
			dzien = dzien + 9;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (dzien >= 29)
		{
			cout << dzien << ".11." << "2024" << endl;
		}
		else
		{
			cout << dzien << ".12." << "2024" << endl;
		}

		if (koniec_pliku == false)
		{
			if (dzien >= 29)
			{
				plik_wynikowy << "Data: " << dzien << ".11." << "2024" << endl;
			}
			else
			{
				plik_wynikowy << "Data: " << dzien << ".12." << "2024" << endl;
			}
		}

		cout << "Czas UTC: ";
		int godziny = 0;
		int minuty = 0;
		if (metar_testowy[zmienna_pomocincza].dzien_i_czas[2] == '0')
		{
			godziny = godziny;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[2] == '1')
		{
			godziny = godziny + 10;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[2] == '2')
		{
			godziny = godziny + 20;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].dzien_i_czas[3] == '0')
		{
			godziny = godziny;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[3] == '1')
		{
			godziny = godziny + 1;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[3] == '2')
		{
			godziny = godziny + 2;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[3] == '3')
		{
			godziny = godziny + 3;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[3] == '4')
		{
			godziny = godziny + 4;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[3] == '5')
		{
			godziny = godziny + 5;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[3] == '6')
		{
			godziny = godziny + 6;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[3] == '7')
		{
			godziny = godziny + 7;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[3] == '8')
		{
			godziny = godziny + 8;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[3] == '9')
		{
			godziny = godziny + 9;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].dzien_i_czas[4] == '0')
		{
			minuty = minuty;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[4] == '1')
		{
			minuty = minuty + 10;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[4] == '2')
		{
			minuty = minuty + 20;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[4] == '3')
		{
			minuty = minuty + 30;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[4] == '4')
		{
			minuty = minuty + 40;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[4] == '5')
		{
			minuty = minuty + 50;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[4] == '6')
		{
			minuty = minuty + 60;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].dzien_i_czas[5] == '0')
		{
			minuty = minuty;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[5] == '1')
		{
			minuty = minuty + 1;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[5] == '2')
		{
			minuty = minuty + 2;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[5] == '3')
		{
			minuty = minuty + 3;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[5] == '4')
		{
			minuty = minuty + 4;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[5] == '5')
		{
			minuty = minuty + 5;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[5] == '6')
		{
			minuty = minuty + 6;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[5] == '7')
		{
			minuty = minuty + 7;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[5] == '8')
		{
			minuty = minuty + 8;
		}
		else if (metar_testowy[zmienna_pomocincza].dzien_i_czas[5] == '9')
		{
			minuty = minuty + 9;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (godziny < 10 && minuty < 10)
		{
			cout << "0" << godziny << ":" << "0" << minuty << endl;
		}
		else if (godziny < 10 && minuty >= 10)
		{
			cout << "0" << godziny << ":" << minuty << endl;
		}
		else if (godziny >= 10 && minuty < 10)
		{
			cout << godziny << ":" << "0" << minuty << endl;
		}
		else
		{
			cout << godziny << ":" << minuty << endl;
		}

		if (koniec_pliku == false)
		{
			plik_wynikowy << "Czas UTC: ";
			if (godziny < 10 && minuty < 10)
			{
				plik_wynikowy << "0" << godziny << ":" << "0" << minuty << endl;
			}
			else if (godziny < 10 && minuty >= 10)
			{
				plik_wynikowy << "0" << godziny << ":" << minuty << endl;
			}
			else if (godziny >= 10 && minuty < 10)
			{
				plik_wynikowy << godziny << ":" << "0" << minuty << endl;
			}
			else
			{
				plik_wynikowy << godziny << ":" << minuty << endl;
			}
		}

	}

	if ((metar_testowy[zmienna_pomocincza].wiatr[5] == 'K' && metar_testowy[zmienna_pomocincza].wiatr[6] == 'T') || (metar_testowy[zmienna_pomocincza].wiatr[5] == 'G'))
	{
		cout << "Wiatr: ";
		int stopnie = 0;
		if (metar_testowy[zmienna_pomocincza].wiatr[0] == '0')
		{
			stopnie = stopnie;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[0] == '1')
		{
			stopnie = stopnie + 100;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[0] == '2')
		{
			stopnie = stopnie + 200;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[0] == '3')
		{
			stopnie = stopnie + 300;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].wiatr[1] == '0')
		{
			stopnie = stopnie;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[1] == '1')
		{
			stopnie = stopnie + 10;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[1] == '2')
		{
			stopnie = stopnie + 20;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[1] == '3')
		{
			stopnie = stopnie + 30;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[1] == '4')
		{
			stopnie = stopnie + 40;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[1] == '5')
		{
			stopnie = stopnie + 50;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[1] == '6')
		{
			stopnie = stopnie + 60;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[1] == '7')
		{
			stopnie = stopnie + 70;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[1] == '8')
		{
			stopnie = stopnie + 80;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[1] == '9')
		{
			stopnie = stopnie + 90;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].wiatr[2] == '0')
		{
			stopnie = stopnie;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[2] == '1')
		{
			stopnie = stopnie + 1;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[2] == '2')
		{
			stopnie = stopnie + 2;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[2] == '3')
		{
			stopnie = stopnie + 3;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[2] == '4')
		{
			stopnie = stopnie + 4;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[2] == '5')
		{
			stopnie = stopnie + 5;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[2] == '6')
		{
			stopnie = stopnie + 6;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[2] == '7')
		{
			stopnie = stopnie + 7;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[2] == '8')
		{
			stopnie = stopnie + 8;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[2] == '9')
		{
			stopnie = stopnie + 9;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		cout << "z kierunku " << stopnie << " stopni, ";

		int wezly = 0;
		if (metar_testowy[zmienna_pomocincza].wiatr[3] == '0')
		{
			wezly = wezly;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[3] == '1')
		{
			wezly = wezly + 10;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[3] == '2')
		{
			wezly = wezly + 20;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[3] == '3')
		{
			wezly = wezly + 30;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[3] == '4')
		{
			wezly = wezly + 40;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[3] == '5')
		{
			wezly = wezly + 50;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[3] == '6')
		{
			wezly = wezly + 60;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[3] == '7')
		{
			wezly = wezly + 70;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[3] == '8')
		{
			wezly = wezly + 80;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[3] == '9')
		{
			wezly = wezly + 90;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].wiatr[4] == '0')
		{
			wezly = wezly;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[4] == '1')
		{
			wezly = wezly + 1;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[4] == '2')
		{
			wezly = wezly + 2;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[4] == '3')
		{
			wezly = wezly + 3;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[4] == '4')
		{
			wezly = wezly + 4;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[4] == '5')
		{
			wezly = wezly + 5;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[4] == '6')
		{
			wezly = wezly + 6;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[4] == '7')
		{
			wezly = wezly + 7;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[4] == '8')
		{
			wezly = wezly + 8;
		}
		else if (metar_testowy[zmienna_pomocincza].wiatr[4] == '9')
		{
			wezly = wezly + 9;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		cout << "predkosc " << wezly << " wezlow" << endl;

		if (koniec_pliku == false)
		{
			plik_wynikowy << "Wiatr: " << "z kierunku " << stopnie << " stopni, " << "predkosc " << wezly << " wezlow" << endl;
		}

		if (koniec_pliku == false)
		{
			metar_testowy[zmienna_pomocincza].kopia_porywy[zmienna_pomocincza] = porywy;
		}
		else
		{
			porywy = metar_testowy[zmienna_pomocincza].kopia_porywy[zmienna_pomocincza];
		}

		if (porywy == true)
		{
			cout << "Porywy wiatru: ";
			int porywy_wiatru = 0;
			if (metar_testowy[zmienna_pomocincza].wiatr[6] == '0')
			{
				porywy_wiatru = porywy_wiatru;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[6] == '1')
			{
				porywy_wiatru = porywy_wiatru + 10;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[6] == '2')
			{
				porywy_wiatru = porywy_wiatru + 20;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[6] == '3')
			{
				porywy_wiatru = porywy_wiatru + 30;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[6] == '4')
			{
				porywy_wiatru = porywy_wiatru + 40;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[6] == '5')
			{
				porywy_wiatru = porywy_wiatru + 50;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[6] == '6')
			{
				porywy_wiatru = porywy_wiatru + 60;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[6] == '7')
			{
				porywy_wiatru = porywy_wiatru + 70;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[6] == '8')
			{
				porywy_wiatru = porywy_wiatru + 80;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[6] == '9')
			{
				porywy_wiatru = porywy_wiatru + 90;
			}
			else
			{
				cout << "Bledny format daty w metarze";
			}

			if (metar_testowy[zmienna_pomocincza].wiatr[7] == '0')
			{
				porywy_wiatru = porywy_wiatru;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[7] == '1')
			{
				porywy_wiatru = porywy_wiatru + 1;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[7] == '2')
			{
				porywy_wiatru = porywy_wiatru + 2;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[7] == '3')
			{
				porywy_wiatru = porywy_wiatru + 3;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[7] == '4')
			{
				porywy_wiatru = porywy_wiatru + 4;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[7] == '5')
			{
				porywy_wiatru = porywy_wiatru + 5;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[7] == '6')
			{
				porywy_wiatru = porywy_wiatru + 6;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[7] == '7')
			{
				porywy_wiatru = porywy_wiatru + 7;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[7] == '8')
			{
				porywy_wiatru = porywy_wiatru + 8;
			}
			else if (metar_testowy[zmienna_pomocincza].wiatr[7] == '9')
			{
				porywy_wiatru = porywy_wiatru + 9;
			}
			else
			{
				cout << "Bledny format daty w metarze";
			}

			cout << "do " << porywy_wiatru << " wezlow" << endl;

			if (koniec_pliku == false)
			{
				plik_wynikowy << "Porywy wiatru: " << "do " << porywy_wiatru << " wezlow" << endl;
			}

			porywy = false;

		}

		if (koniec_pliku == false)
		{
			metar_testowy[zmienna_pomocincza].kopia_zmiany[zmienna_pomocincza] = zmiany;
		}
		else
		{
			zmiany = metar_testowy[zmienna_pomocincza].kopia_zmiany[zmienna_pomocincza];
		}

		if (zmiany == true)
		{
			cout << "Zmiany wiatru: ";
			int od_stopnie = 0;
			int do_stopnie = 0;
			if (metar_testowy[zmienna_pomocincza].porywy_wiatru[0] == '0')
			{
				od_stopnie = od_stopnie;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[0] == '1')
			{
				od_stopnie = od_stopnie + 100;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[0] == '2')
			{
				od_stopnie = od_stopnie + 200;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[0] == '3')
			{
				od_stopnie = od_stopnie + 300;
			}
			else
			{
				cout << "Bledny format daty w metarze";
			}

			if (metar_testowy[zmienna_pomocincza].porywy_wiatru[1] == '0')
			{
				od_stopnie = od_stopnie;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[1] == '1')
			{
				od_stopnie = od_stopnie + 10;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[1] == '2')
			{
				od_stopnie = od_stopnie + 20;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[1] == '3')
			{
				od_stopnie = od_stopnie + 30;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[1] == '4')
			{
				od_stopnie = od_stopnie + 40;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[1] == '5')
			{
				od_stopnie = od_stopnie + 50;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[1] == '6')
			{
				od_stopnie = od_stopnie + 60;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[1] == '7')
			{
				od_stopnie = od_stopnie + 70;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[1] == '8')
			{
				od_stopnie = od_stopnie + 80;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[1] == '9')
			{
				od_stopnie = od_stopnie + 90;
			}
			else
			{
				cout << "Bledny format daty w metarze";
			}

			if (metar_testowy[zmienna_pomocincza].porywy_wiatru[2] == '0')
			{
				od_stopnie = od_stopnie;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[2] == '1')
			{
				od_stopnie = od_stopnie + 1;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[2] == '2')
			{
				od_stopnie = od_stopnie + 2;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[2] == '3')
			{
				od_stopnie = od_stopnie + 3;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[2] == '4')
			{
				od_stopnie = od_stopnie + 4;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[2] == '5')
			{
				od_stopnie = od_stopnie + 5;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[2] == '6')
			{
				od_stopnie = od_stopnie + 6;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[2] == '7')
			{
				od_stopnie = od_stopnie + 7;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[2] == '8')
			{
				od_stopnie = od_stopnie + 8;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[2] == '9')
			{
				od_stopnie = od_stopnie + 9;
			}
			else
			{
				cout << "Bledny format daty w metarze";
			}

			if (metar_testowy[zmienna_pomocincza].porywy_wiatru[4] == '0')
			{
				do_stopnie = do_stopnie;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[4] == '1')
			{
				do_stopnie = do_stopnie + 100;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[4] == '2')
			{
				do_stopnie = do_stopnie + 200;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[4] == '3')
			{
				do_stopnie = do_stopnie + 300;
			}
			else
			{
				cout << "Bledny format daty w metarze";
			}

			if (metar_testowy[zmienna_pomocincza].porywy_wiatru[5] == '0')
			{
				do_stopnie = do_stopnie;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[5] == '1')
			{
				do_stopnie = do_stopnie + 10;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[5] == '2')
			{
				do_stopnie = do_stopnie + 20;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[5] == '3')
			{
				do_stopnie = do_stopnie + 30;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[5] == '4')
			{
				do_stopnie = do_stopnie + 40;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[5] == '5')
			{
				do_stopnie = do_stopnie + 50;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[5] == '6')
			{
				do_stopnie = do_stopnie + 60;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[5] == '7')
			{
				do_stopnie = do_stopnie + 70;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[5] == '8')
			{
				do_stopnie = do_stopnie + 80;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[5] == '9')
			{
				do_stopnie = do_stopnie + 90;
			}
			else
			{
				cout << "Bledny format daty w metarze";
			}

			if (metar_testowy[zmienna_pomocincza].porywy_wiatru[6] == '0')
			{
				do_stopnie = do_stopnie;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[6] == '1')
			{
				do_stopnie = do_stopnie + 1;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[6] == '2')
			{
				do_stopnie = do_stopnie + 2;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[6] == '3')
			{
				do_stopnie = do_stopnie + 3;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[6] == '4')
			{
				do_stopnie = do_stopnie + 4;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[6] == '5')
			{
				do_stopnie = do_stopnie + 5;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[6] == '6')
			{
				do_stopnie = do_stopnie + 6;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[6] == '7')
			{
				do_stopnie = do_stopnie + 7;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[6] == '8')
			{
				do_stopnie = do_stopnie + 8;
			}
			else if (metar_testowy[zmienna_pomocincza].porywy_wiatru[6] == '9')
			{
				do_stopnie = do_stopnie + 9;
			}
			else
			{
				cout << "Bledny format daty w metarze";
			}

			cout << "zmienny od " << od_stopnie << " stopni do " << do_stopnie << " stopni" << endl;

			if (koniec_pliku == false)
			{
				plik_wynikowy << "Zmiany wiatru: " << "zmienny od " << od_stopnie << " stopni do " << do_stopnie << " stopni" << endl;
			}

			zmiany = false;
		}
	}

	if (koniec_pliku == false)
	{
		metar_testowy[zmienna_pomocincza].kopia_temperatura_ujemna[zmienna_pomocincza] = temperatura_ujemna;
	}
	else
	{
		temperatura_ujemna = metar_testowy[zmienna_pomocincza].kopia_temperatura_ujemna[zmienna_pomocincza];
	}

	if (koniec_pliku == false)
	{
		metar_testowy[zmienna_pomocincza].kopia_rosa_ujemna[zmienna_pomocincza] = rosa_ujemna;
	}
	else
	{
		rosa_ujemna = metar_testowy[zmienna_pomocincza].kopia_rosa_ujemna[zmienna_pomocincza];
	}

	if ((metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[2] == '/') || (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[3] == '/' && metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[0] == 'M') || (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[2] == '/' && metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[3] == 'M'))
	{
		int zmienna_temperatura = 0;
		cout << "Temperatura: ";

		if (koniec_pliku == false)
		{
			plik_wynikowy << "Temperatura: ";
		}

		if (temperatura_ujemna == true)
		{
			cout << "-";
			if (koniec_pliku == false)
			{
				plik_wynikowy << "-";
			}

			zmienna_temperatura++;
		}

		int temperatura = 0;
		if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '0')
		{
			temperatura = temperatura;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '1')
		{
			temperatura = temperatura + 10;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '2')
		{
			temperatura = temperatura + 20;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '3')
		{
			temperatura = temperatura + 30;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '4')
		{
			temperatura = temperatura + 40;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '5')
		{
			temperatura = temperatura + 50;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '6')
		{
			temperatura = temperatura + 60;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '7')
		{
			temperatura = temperatura + 70;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '8')
		{
			temperatura = temperatura + 80;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '9')
		{
			temperatura = temperatura + 90;
			zmienna_temperatura++;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '0')
		{
			temperatura = temperatura;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '1')
		{
			temperatura = temperatura + 1;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '2')
		{
			temperatura = temperatura + 2;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '3')
		{
			temperatura = temperatura + 3;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '4')
		{
			temperatura = temperatura + 4;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '5')
		{
			temperatura = temperatura + 5;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '6')
		{
			temperatura = temperatura + 6;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '7')
		{
			temperatura = temperatura + 7;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '8')
		{
			temperatura = temperatura + 8;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '9')
		{
			temperatura = temperatura + 9;
			zmienna_temperatura++;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (temperatura < 10)
		{
			cout << "0" << temperatura << " stopni C" << endl;
		}
		else
		{
			cout << temperatura << " stopni C" << endl;
		}

		if (koniec_pliku == false)
		{
			if (temperatura < 10)
			{
				plik_wynikowy << "0" << temperatura << " stopni C" << endl;
			}
			else
			{
				plik_wynikowy << temperatura << " stopni C" << endl;
			}
		}

		temperatura_ujemna = false;
		zmienna_temperatura++;

		int punkt_rosy = 0;
		cout << "Temperatura punktu rosy: ";
		if (koniec_pliku == false)
		{
			plik_wynikowy << "Temperatura punktu rosy: ";
		}

		if (rosa_ujemna == true)
		{
			cout << "-";
			if (koniec_pliku == false)
			{
				plik_wynikowy << "-";
			}

			zmienna_temperatura++;
		}

		if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '0')
		{
			punkt_rosy = punkt_rosy;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '1')
		{
			punkt_rosy = punkt_rosy + 10;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '2')
		{
			punkt_rosy = punkt_rosy + 20;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '3')
		{
			punkt_rosy = punkt_rosy + 30;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '4')
		{
			punkt_rosy = punkt_rosy + 40;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '5')
		{
			punkt_rosy = punkt_rosy + 50;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '6')
		{
			punkt_rosy = punkt_rosy + 60;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '7')
		{
			punkt_rosy = punkt_rosy + 70;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '8')
		{
			punkt_rosy = punkt_rosy + 80;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '9')
		{
			punkt_rosy = punkt_rosy + 90;
			zmienna_temperatura++;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '0')
		{
			punkt_rosy = punkt_rosy;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '1')
		{
			punkt_rosy = punkt_rosy + 1;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '2')
		{
			punkt_rosy = punkt_rosy + 2;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '3')
		{
			punkt_rosy = punkt_rosy + 3;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '4')
		{
			punkt_rosy = punkt_rosy + 4;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '5')
		{
			punkt_rosy = punkt_rosy + 5;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '6')
		{
			punkt_rosy = punkt_rosy + 6;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '7')
		{
			punkt_rosy = punkt_rosy + 7;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '8')
		{
			punkt_rosy = punkt_rosy + 8;
			zmienna_temperatura++;
		}
		else if (metar_testowy[zmienna_pomocincza].temperatura_i_punkt_rosy[zmienna_temperatura] == '9')
		{
			punkt_rosy = punkt_rosy + 9;
			zmienna_temperatura++;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (punkt_rosy < 10)
		{
			cout << "0" << punkt_rosy << " stopni C" << endl;
		}
		else
		{
			cout << punkt_rosy << " stopni C" << endl;
		}

		if (koniec_pliku == false)
		{
			if (punkt_rosy < 10)
			{
				plik_wynikowy << "0" << punkt_rosy << " stopni C" << endl;
			}
			else
			{
				plik_wynikowy << punkt_rosy << " stopni C" << endl;
			}
		}

		rosa_ujemna = false;

		zmienna_temperatura = 0;
	}

	if (metar_testowy[zmienna_pomocincza].cisnienie[0] == 'Q')
	{
		cout << "Cisnienie: ";
		int cisnienie = 0;
		if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '0')
		{
			cisnienie = cisnienie;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '1')
		{
			cisnienie = cisnienie + 1000;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '2')
		{
			cisnienie = cisnienie + 2000;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '3')
		{
			cisnienie = cisnienie + 3000;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '4')
		{
			cisnienie = cisnienie + 4000;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '5')
		{
			cisnienie = cisnienie + 5000;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '6')
		{
			cisnienie = cisnienie + 6000;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '7')
		{
			cisnienie = cisnienie + 7000;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '8')
		{
			cisnienie = cisnienie + 8000;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '9')
		{
			cisnienie = cisnienie + 9000;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '0')
		{
			cisnienie = cisnienie;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '1')
		{
			cisnienie = cisnienie + 100;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '2')
		{
			cisnienie = cisnienie + 200;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '3')
		{
			cisnienie = cisnienie + 300;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '4')
		{
			cisnienie = cisnienie + 400;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '5')
		{
			cisnienie = cisnienie + 500;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '6')
		{
			cisnienie = cisnienie + 600;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '7')
		{
			cisnienie = cisnienie + 700;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '8')
		{
			cisnienie = cisnienie + 800;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '9')
		{
			cisnienie = cisnienie + 900;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '0')
		{
			cisnienie = cisnienie;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '1')
		{
			cisnienie = cisnienie + 10;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '2')
		{
			cisnienie = cisnienie + 20;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '3')
		{
			cisnienie = cisnienie + 30;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '4')
		{
			cisnienie = cisnienie + 40;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '5')
		{
			cisnienie = cisnienie + 50;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '6')
		{
			cisnienie = cisnienie + 60;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '7')
		{
			cisnienie = cisnienie + 70;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '8')
		{
			cisnienie = cisnienie + 80;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '9')
		{
			cisnienie = cisnienie + 90;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '0')
		{
			cisnienie = cisnienie;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '1')
		{
			cisnienie = cisnienie + 1;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '2')
		{
			cisnienie = cisnienie + 2;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '3')
		{
			cisnienie = cisnienie + 3;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '4')
		{
			cisnienie = cisnienie + 4;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '5')
		{
			cisnienie = cisnienie + 5;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '6')
		{
			cisnienie = cisnienie + 6;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '7')
		{
			cisnienie = cisnienie + 7;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '8')
		{
			cisnienie = cisnienie + 8;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '9')
		{
			cisnienie = cisnienie + 9;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (cisnienie < 10)
		{
			cout << "0" << "0" << "0" << cisnienie << " hPa" << endl;
		}
		else if (cisnienie < 100)
		{
			cout << "0" << "0" << cisnienie << " hPa" << endl;
		}
		else if (cisnienie < 1000)
		{
			cout << "0" << cisnienie << " hPa" << endl;
		}
		else if (cisnienie >= 1000)
		{
			cout << cisnienie << " hPa" << endl;
		}
		else
		{
			cout << "Bledne cisnienie" << endl;
		}

		if (koniec_pliku == false)
		{
			plik_wynikowy << "Cisnienie: ";
			if (cisnienie < 10)
			{
				plik_wynikowy << "0" << "0" << "0" << cisnienie << " hPa" << endl;
			}
			else if (cisnienie < 100)
			{
				plik_wynikowy << "0" << "0" << cisnienie << " hPa" << endl;
			}
			else if (cisnienie < 1000)
			{
				plik_wynikowy << "0" << cisnienie << " hPa" << endl;
			}
			else if (cisnienie >= 1000)
			{
				plik_wynikowy << cisnienie << " hPa" << endl;
			}
			else
			{
				plik_wynikowy << "Bledne cisnienie" << endl;
			}
		}

	}

	if (metar_testowy[zmienna_pomocincza].cisnienie[0] == 'A')
	{
		cout << "Cisnienie: ";
		float slup_rteci = 0;
		if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '0')
		{
			slup_rteci = slup_rteci;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '1')
		{
			slup_rteci = slup_rteci + 10;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '2')
		{
			slup_rteci = slup_rteci + 20;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '3')
		{
			slup_rteci = slup_rteci + 30;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '4')
		{
			slup_rteci = slup_rteci + 40;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '5')
		{
			slup_rteci = slup_rteci + 50;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '6')
		{
			slup_rteci = slup_rteci + 60;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '7')
		{
			slup_rteci = slup_rteci + 70;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '8')
		{
			slup_rteci = slup_rteci + 80;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[1] == '9')
		{
			slup_rteci = slup_rteci + 90;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '0')
		{
			slup_rteci = slup_rteci;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '1')
		{
			slup_rteci = slup_rteci + 1;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '2')
		{
			slup_rteci = slup_rteci + 2;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '3')
		{
			slup_rteci = slup_rteci + 3;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '4')
		{
			slup_rteci = slup_rteci + 4;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '5')
		{
			slup_rteci = slup_rteci + 5;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '6')
		{
			slup_rteci = slup_rteci + 6;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '7')
		{
			slup_rteci = slup_rteci + 7;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '8')
		{
			slup_rteci = slup_rteci + 8;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[2] == '9')
		{
			slup_rteci = slup_rteci + 9;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '0')
		{
			slup_rteci = slup_rteci;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '1')
		{
			slup_rteci = slup_rteci + 0.1;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '2')
		{
			slup_rteci = slup_rteci + 0.2;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '3')
		{
			slup_rteci = slup_rteci + 0.3;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '4')
		{
			slup_rteci = slup_rteci + 0.4;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '5')
		{
			slup_rteci = slup_rteci + 0.5;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '6')
		{
			slup_rteci = slup_rteci + 0.6;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '7')
		{
			slup_rteci = slup_rteci + 0.7;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '8')
		{
			slup_rteci = slup_rteci + 0.8;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[3] == '9')
		{
			slup_rteci = slup_rteci + 0.9;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '0')
		{
			slup_rteci = slup_rteci;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '1')
		{
			slup_rteci = slup_rteci + 0.01;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '2')
		{
			slup_rteci = slup_rteci + 0.02;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '3')
		{
			slup_rteci = slup_rteci + 0.03;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '4')
		{
			slup_rteci = slup_rteci + 0.04;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '5')
		{
			slup_rteci = slup_rteci + 0.05;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '6')
		{
			slup_rteci = slup_rteci + 0.06;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '7')
		{
			slup_rteci = slup_rteci + 0.07;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '8')
		{
			slup_rteci = slup_rteci + 0.08;
		}
		else if (metar_testowy[zmienna_pomocincza].cisnienie[4] == '9')
		{
			slup_rteci = slup_rteci + 0.09;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (slup_rteci < 10)
		{
			cout << "0" << slup_rteci << " inHg" << endl;
		}
		else if (slup_rteci > 10)
		{
			cout << slup_rteci << " inHg" << endl;
		}
		else
		{
			cout << "Bledne cisnienie" << endl;
		}

		if (koniec_pliku == false)
		{
			plik_wynikowy << "Cisnienie: ";
			if (slup_rteci < 10)
			{
				plik_wynikowy << "0" << slup_rteci << " inHg" << endl;
			}
			else if (slup_rteci > 10)
			{
				plik_wynikowy << slup_rteci << " inHg" << endl;
			}
			else
			{
				plik_wynikowy << "Bledne cisnienie" << endl;
			}
		}

	}

	if ((metar_testowy[zmienna_pomocincza].widzialnosc[0] == '0' || metar_testowy[zmienna_pomocincza].widzialnosc[0] == '1' || metar_testowy[zmienna_pomocincza].widzialnosc[0] == '2' || metar_testowy[zmienna_pomocincza].widzialnosc[0] == '3' || metar_testowy[zmienna_pomocincza].widzialnosc[0] == '4' || metar_testowy[zmienna_pomocincza].widzialnosc[0] == '5' || metar_testowy[zmienna_pomocincza].widzialnosc[0] == '6' || metar_testowy[zmienna_pomocincza].widzialnosc[0] == '7' || metar_testowy[zmienna_pomocincza].widzialnosc[0] == '8' || metar_testowy[zmienna_pomocincza].widzialnosc[0] == '9') && (metar_testowy[zmienna_pomocincza].widzialnosc[1] == '0' || metar_testowy[zmienna_pomocincza].widzialnosc[1] == '1' || metar_testowy[zmienna_pomocincza].widzialnosc[1] == '2' || metar_testowy[zmienna_pomocincza].widzialnosc[1] == '3' || metar_testowy[zmienna_pomocincza].widzialnosc[1] == '4' || metar_testowy[zmienna_pomocincza].widzialnosc[1] == '5' || metar_testowy[zmienna_pomocincza].widzialnosc[1] == '6' || metar_testowy[zmienna_pomocincza].widzialnosc[1] == '7' || metar_testowy[zmienna_pomocincza].widzialnosc[1] == '8' || metar_testowy[zmienna_pomocincza].widzialnosc[1] == '9') && (metar_testowy[zmienna_pomocincza].widzialnosc[2] == '0' || metar_testowy[zmienna_pomocincza].widzialnosc[2] == '1' || metar_testowy[zmienna_pomocincza].widzialnosc[2] == '2' || metar_testowy[zmienna_pomocincza].widzialnosc[2] == '3' || metar_testowy[zmienna_pomocincza].widzialnosc[2] == '4' || metar_testowy[zmienna_pomocincza].widzialnosc[2] == '5' || metar_testowy[zmienna_pomocincza].widzialnosc[2] == '6' || metar_testowy[zmienna_pomocincza].widzialnosc[2] == '7' || metar_testowy[zmienna_pomocincza].widzialnosc[2] == '8' || metar_testowy[zmienna_pomocincza].widzialnosc[2] == '9') && (metar_testowy[zmienna_pomocincza].widzialnosc[3] == '0' || metar_testowy[zmienna_pomocincza].widzialnosc[3] == '1' || metar_testowy[zmienna_pomocincza].widzialnosc[3] == '2' || metar_testowy[zmienna_pomocincza].widzialnosc[3] == '3' || metar_testowy[zmienna_pomocincza].widzialnosc[3] == '4' || metar_testowy[zmienna_pomocincza].widzialnosc[3] == '5' || metar_testowy[zmienna_pomocincza].widzialnosc[3] == '6' || metar_testowy[zmienna_pomocincza].widzialnosc[3] == '7' || metar_testowy[zmienna_pomocincza].widzialnosc[3] == '8' || metar_testowy[zmienna_pomocincza].widzialnosc[3] == '9'))
	{
		cout << "Widocznosc: ";
		int widocznosc = 0;
		if (metar_testowy[zmienna_pomocincza].widzialnosc[0] == '0')
		{
			widocznosc = widocznosc;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[0] == '1')
		{
			widocznosc = widocznosc + 1000;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[0] == '2')
		{
			widocznosc = widocznosc + 2000;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[0] == '3')
		{
			widocznosc = widocznosc + 3000;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[0] == '4')
		{
			widocznosc = widocznosc + 4000;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[0] == '5')
		{
			widocznosc = widocznosc + 5000;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[0] == '6')
		{
			widocznosc = widocznosc + 6000;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[0] == '7')
		{
			widocznosc = widocznosc + 7000;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[0] == '8')
		{
			widocznosc = widocznosc + 8000;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[0] == '9')
		{
			widocznosc = widocznosc + 9000;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].widzialnosc[1] == '0')
		{
			widocznosc = widocznosc;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[1] == '1')
		{
			widocznosc = widocznosc + 100;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[1] == '2')
		{
			widocznosc = widocznosc + 200;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[1] == '3')
		{
			widocznosc = widocznosc + 300;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[1] == '4')
		{
			widocznosc = widocznosc + 400;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[1] == '5')
		{
			widocznosc = widocznosc + 500;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[1] == '6')
		{
			widocznosc = widocznosc + 600;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[1] == '7')
		{
			widocznosc = widocznosc + 700;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[1] == '8')
		{
			widocznosc = widocznosc + 800;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[1] == '9')
		{
			widocznosc = widocznosc + 900;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].widzialnosc[2] == '0')
		{
			widocznosc = widocznosc;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[2] == '1')
		{
			widocznosc = widocznosc + 10;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[2] == '2')
		{
			widocznosc = widocznosc + 20;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[2] == '3')
		{
			widocznosc = widocznosc + 30;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[2] == '4')
		{
			widocznosc = widocznosc + 40;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[2] == '5')
		{
			widocznosc = widocznosc + 50;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[2] == '6')
		{
			widocznosc = widocznosc + 60;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[2] == '7')
		{
			widocznosc = widocznosc + 70;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[2] == '8')
		{
			widocznosc = widocznosc + 80;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[2] == '9')
		{
			widocznosc = widocznosc + 90;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (metar_testowy[zmienna_pomocincza].widzialnosc[3] == '0')
		{
			widocznosc = widocznosc;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[3] == '1')
		{
			widocznosc = widocznosc + 1;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[3] == '2')
		{
			widocznosc = widocznosc + 2;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[3] == '3')
		{
			widocznosc = widocznosc + 3;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[3] == '4')
		{
			widocznosc = widocznosc + 4;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[3] == '5')
		{
			widocznosc = widocznosc + 5;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[3] == '6')
		{
			widocznosc = widocznosc + 6;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[3] == '7')
		{
			widocznosc = widocznosc + 7;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[3] == '8')
		{
			widocznosc = widocznosc + 8;
		}
		else if (metar_testowy[zmienna_pomocincza].widzialnosc[3] == '9')
		{
			widocznosc = widocznosc + 9;
		}
		else
		{
			cout << "Bledny format daty w metarze";
		}

		if (widocznosc == 9999)
		{
			cout << "+10 000 metrow" << endl;
		}
		else
		{
			cout << widocznosc << " metrow" << endl;
		}

		if (koniec_pliku == false)
		{
			plik_wynikowy << "Widocznosc: ";
			if (widocznosc == 9999)
			{
				plik_wynikowy << "+10 000 metrow" << endl;
			}
			else
			{
				plik_wynikowy << widocznosc << " metrow" << endl;
			}
		}

	}

	if (koniec_pliku == false)
	{
		metar_testowy[zmienna_pomocincza].kopia_liczby_chmur[zmienna_pomocincza] = liczba_chmur;
	}
	else
	{
		liczba_chmur = metar_testowy[zmienna_pomocincza].kopia_liczby_chmur[zmienna_pomocincza];
	}

	if ((metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[0][liczba_chmur] == 'F' || metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[0][liczba_chmur] == 'S' || metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[0][liczba_chmur] == 'B' || metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[0][liczba_chmur] == 'O') && (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[1][liczba_chmur] == 'E' || metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[1][liczba_chmur] == 'C' || metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[1][liczba_chmur] == 'K' || metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[1][liczba_chmur] == 'V') && (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[2][liczba_chmur] == 'W' || metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[2][liczba_chmur] == 'T' || metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[2][liczba_chmur] == 'N' || metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[2][liczba_chmur] == 'C'))
	{
		while (liczba_chmur != 0)
		{
			cout << "Warstwa chmur nr. " << liczba_chmur;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Warstwa chmur nr. " << liczba_chmur;
			}

			if ((metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[0][liczba_chmur] == 'F') && (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[1][liczba_chmur] == 'E') && (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[2][liczba_chmur] == 'W'))
			{
				cout << " Nieliczne chmury (1/8 lub 2/8 pokrycia)";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " Nieliczne chmury (1/8 lub 2/8 pokrycia)";
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[0][liczba_chmur] == 'S') && (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[1][liczba_chmur] == 'C') && (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[2][liczba_chmur] == 'T'))
			{
				cout << " Rozproszone chmury (3/8 lub 4/8 pokrycia)";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " Rozproszone chmury (3/8 lub 4/8 pokrycia)";
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[0][liczba_chmur] == 'B') && (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[1][liczba_chmur] == 'K') && (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[2][liczba_chmur] == 'N'))
			{
				cout << " Chmury klebiaste (od 5/8 do 7/8 pokrycia)";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " Chmury klebiaste (od 5/8 do 7/8 pokrycia)";
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[0][liczba_chmur] == 'O') && (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[1][liczba_chmur] == 'V') && (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[2][liczba_chmur] == 'C'))
			{
				cout << " Calkowite zachmurzenie (8/8 pokrycia)";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " Calkowite zachmurzenie (8/8 pokrycia)";
				}
			}
			else
			{
				cout << "Bledny format daty w metarze";
			}

			int podstawa_chmur = 0;
			if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[3][liczba_chmur] == '0')
			{
				podstawa_chmur = podstawa_chmur;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[3][liczba_chmur] == '1')
			{
				podstawa_chmur = podstawa_chmur + 10000;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[3][liczba_chmur] == '2')
			{
				podstawa_chmur = podstawa_chmur + 20000;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[3][liczba_chmur] == '3')
			{
				podstawa_chmur = podstawa_chmur + 30000;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[3][liczba_chmur] == '4')
			{
				podstawa_chmur = podstawa_chmur + 40000;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[3][liczba_chmur] == '5')
			{
				podstawa_chmur = podstawa_chmur + 50000;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[3][liczba_chmur] == '6')
			{
				podstawa_chmur = podstawa_chmur + 60000;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[3][liczba_chmur] == '7')
			{
				podstawa_chmur = podstawa_chmur + 70000;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[3][liczba_chmur] == '8')
			{
				podstawa_chmur = podstawa_chmur + 80000;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[3][liczba_chmur] == '9')
			{
				podstawa_chmur = podstawa_chmur + 90000;
			}
			else
			{
				cout << "Bledny format daty w metarze";
			}

			if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[4][liczba_chmur] == '0')
			{
				podstawa_chmur = podstawa_chmur;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[4][liczba_chmur] == '1')
			{
				podstawa_chmur = podstawa_chmur + 1000;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[4][liczba_chmur] == '2')
			{
				podstawa_chmur = podstawa_chmur + 2000;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[4][liczba_chmur] == '3')
			{
				podstawa_chmur = podstawa_chmur + 3000;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[4][liczba_chmur] == '4')
			{
				podstawa_chmur = podstawa_chmur + 4000;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[4][liczba_chmur] == '5')
			{
				podstawa_chmur = podstawa_chmur + 5000;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[4][liczba_chmur] == '6')
			{
				podstawa_chmur = podstawa_chmur + 6000;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[4][liczba_chmur] == '7')
			{
				podstawa_chmur = podstawa_chmur + 7000;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[4][liczba_chmur] == '8')
			{
				podstawa_chmur = podstawa_chmur + 8000;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[4][liczba_chmur] == '9')
			{
				podstawa_chmur = podstawa_chmur + 9000;
			}
			else
			{
				cout << "Bledny format daty w metarze";
			}

			if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[5][liczba_chmur] == '0')
			{
				podstawa_chmur = podstawa_chmur;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[5][liczba_chmur] == '1')
			{
				podstawa_chmur = podstawa_chmur + 100;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[5][liczba_chmur] == '2')
			{
				podstawa_chmur = podstawa_chmur + 200;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[5][liczba_chmur] == '3')
			{
				podstawa_chmur = podstawa_chmur + 300;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[5][liczba_chmur] == '4')
			{
				podstawa_chmur = podstawa_chmur + 400;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[5][liczba_chmur] == '5')
			{
				podstawa_chmur = podstawa_chmur + 500;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[5][liczba_chmur] == '6')
			{
				podstawa_chmur = podstawa_chmur + 600;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[5][liczba_chmur] == '7')
			{
				podstawa_chmur = podstawa_chmur + 700;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[5][liczba_chmur] == '8')
			{
				podstawa_chmur = podstawa_chmur + 800;
			}
			else if (metar_testowy[zmienna_pomocincza].zachmurzenie_i_podstawa_chmur[5][liczba_chmur] == '9')
			{
				podstawa_chmur = podstawa_chmur + 900;
			}
			else
			{
				cout << "Bledny format daty w metarze";
			}

			cout << " na wysokosci " << podstawa_chmur << " stop";
			if (koniec_pliku == false)
			{
				plik_wynikowy << " na wysokosci " << podstawa_chmur << " stop";
			}


			if (koniec_pliku == false)
			{
				metar_testowy[zmienna_pomocincza].kopia_cumulonimbus[liczba_chmur] = cumulonimbus[liczba_chmur];
			}
			else
			{
				cumulonimbus[liczba_chmur] = metar_testowy[zmienna_pomocincza].kopia_cumulonimbus[liczba_chmur];
			}

			if (koniec_pliku == false)
			{
				metar_testowy[zmienna_pomocincza].kopia_cumulus[liczba_chmur] = cumulus[liczba_chmur];
			}
			else
			{
				cumulus[liczba_chmur] = metar_testowy[zmienna_pomocincza].kopia_cumulus[liczba_chmur];
			}

			if (cumulonimbus[liczba_chmur] == false && cumulus[liczba_chmur] == false)
			{
				cout << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << endl;
				}
			}
			if (cumulonimbus[liczba_chmur] == true && cumulus[liczba_chmur] == false)
			{
				cout << " z chmurami cumulonimbus" << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " z chmurami cumulonimbus" << endl;
				}
				cumulonimbus[liczba_chmur] = false;
			}
			if (cumulus[liczba_chmur] == true && cumulonimbus[liczba_chmur] == false)
			{
				cout << " z chmurami cumulus gorojacy" << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " z chmurami cumulus gorojacy" << endl;
				}
				cumulus[liczba_chmur] = false;
			}

			liczba_chmur--;
		}
	}

	if (koniec_pliku == false)
	{
		metar_testowy[zmienna_pomocincza].kopia_liczba_zjawisk[zmienna_pomocincza] = liczba_zjawisk;
	}
	else
	{
		liczba_zjawisk = metar_testowy[zmienna_pomocincza].kopia_liczba_zjawisk[zmienna_pomocincza];
	}

	if ((metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'B' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'D' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'F' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'G' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'H' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'I' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'P' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'R' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'S' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'U' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'V') && ((metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'R' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'S' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'U' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'Z' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'C' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'G' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'E' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'O' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'Y' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'A' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'N' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'Q' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'P') || (metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'B' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'D' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'M' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'P' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'F' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'S' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'T') && (metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'C' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'R' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'I' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'L' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'Z' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'H' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'S')) || (metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == '+' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == '-') || (metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'R' || metar_testowy[zmienna_pomocincza].zjawiska[0][liczba_zjawisk] == 'V') && (metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'E' || metar_testowy[zmienna_pomocincza].zjawiska[1][liczba_zjawisk] == 'C'))
	{
		while (liczba_zjawisk != 0)
		{
			cout << "Zjawisko pogodowe nr. " << liczba_zjawisk;
			if (koniec_pliku == false)
			{
				plik_wynikowy << "Zjawisko pogodowe nr. " << liczba_zjawisk;
			}

			int zmienna_pogodowa = 0;
			int zmienna_pogodowa_plus = 1;


			if (koniec_pliku == false)
			{
				metar_testowy[zmienna_pomocincza].kopia_charakterystyka[liczba_zjawisk] = charakterystyka[liczba_zjawisk];
			}
			else
			{
				charakterystyka[liczba_zjawisk] = metar_testowy[zmienna_pomocincza].kopia_charakterystyka[liczba_zjawisk];
			}

			if (koniec_pliku == false)
			{
				metar_testowy[zmienna_pomocincza].kopia_intensywnosc[liczba_zjawisk] = intensywnosc[liczba_zjawisk];
			}
			else
			{
				intensywnosc[liczba_zjawisk] = metar_testowy[zmienna_pomocincza].kopia_intensywnosc[liczba_zjawisk];
			}

			if (koniec_pliku == false)
			{
				metar_testowy[zmienna_pomocincza].kopia_plus_lub_minus[liczba_zjawisk] = plus_lub_minus[liczba_zjawisk];
			}
			else
			{
				plus_lub_minus[liczba_zjawisk] = metar_testowy[zmienna_pomocincza].kopia_plus_lub_minus[liczba_zjawisk];
			}

			if (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == '+')
			{
				cout << " silna";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " silna";
				}
			}
			else if (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == '-')
			{
				cout << " lekki";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " lekki";
				}
			}
			else if (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'V' && metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'C')
			{
				cout << " w poblizu";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " w poblizu";
				}
			}
			else if (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'R' && metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'E')
			{
				cout << " niedawny";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " niedawny";
				}
			}

			if (intensywnosc[liczba_zjawisk] == true && plus_lub_minus[liczba_zjawisk] == true)
			{
				zmienna_pogodowa = zmienna_pogodowa + 1;
				zmienna_pogodowa_plus = zmienna_pogodowa_plus + 1;
				intensywnosc[liczba_zjawisk] = false;
				plus_lub_minus[liczba_zjawisk] = false;
			}
			else if (intensywnosc[liczba_zjawisk] == false && plus_lub_minus[liczba_zjawisk] == false)
			{
				zmienna_pogodowa = zmienna_pogodowa;
				zmienna_pogodowa_plus = zmienna_pogodowa_plus;
			}
			else if (intensywnosc[liczba_zjawisk] == true && plus_lub_minus[liczba_zjawisk] == false)
			{
				zmienna_pogodowa = zmienna_pogodowa + 2;
				zmienna_pogodowa_plus = zmienna_pogodowa_plus + 2;
				intensywnosc[liczba_zjawisk] = false;
			}

			if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'B') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'C'))
			{
				cout << " plastry";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " plastry";
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'D') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'R'))
			{
				cout << " zamiec przyziemna";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " zamiec przyziemna";
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'M') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'I'))
			{
				cout << " plycizna";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " plycizna";
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'P') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'R'))
			{
				cout << " czesciowy";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " czesciowy";
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'B') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'L'))
			{
				cout << " zawieja";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " zawieja";
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'F') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'Z'))
			{
				cout << " zamrazanie";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " zamrazanie";
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'S') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'H'))
			{
				cout << " przysznice";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " przysznice";
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'T') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'S'))
			{
				cout << " burza";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " burza";
				}
			}

			if (charakterystyka[liczba_zjawisk] == true)
			{
				zmienna_pogodowa = zmienna_pogodowa + 2;
				zmienna_pogodowa_plus = zmienna_pogodowa_plus + 2;
				charakterystyka[liczba_zjawisk] = false;
			}
			else if (charakterystyka[liczba_zjawisk] == false)
			{
				zmienna_pogodowa = zmienna_pogodowa;
				zmienna_pogodowa_plus = zmienna_pogodowa_plus;
			}

			if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'B') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'R'))
			{
				cout << " zamglenie " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " zamglenie " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'D') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'S'))
			{
				cout << " burza pylu " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " burza pylu " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'D') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'U'))
			{
				cout << " rozlegly pyl " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " rozlegly pyl " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'D') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'Z'))
			{
				cout << " mzawka " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " mzawka " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'F') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'C'))
			{
				cout << " chmura lejka " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " chmura lejka " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'F') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'G'))
			{
				cout << " mgla " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " mgla " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'F') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'U'))
			{
				cout << " palic " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " palic " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'G') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'R'))
			{
				cout << " grad " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " grad " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'G') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'S'))
			{
				cout << " krupa sniezna " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " krupa sniezna " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'H') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'Z'))
			{
				cout << " mgla " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " mgla " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'I') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'C'))
			{
				cout << " krysztaly lodu " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " krysztaly lodu " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'P') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'E'))
			{
				cout << " granulki lodu " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " granulki lodu " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'P') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'O'))
			{
				cout << " wiry piasku " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " wiry piasku " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'P') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'Y'))
			{
				cout << " rozpylac " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " rozpylac " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'R') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'A'))
			{
				cout << " deszcz " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " deszcz " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'S') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'A'))
			{
				cout << " piasek " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " piasek " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'S') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'G'))
			{
				cout << " snieg ziarnisty " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " snieg ziarnisty " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'S') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'N'))
			{
				cout << " snieg " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " snieg " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'S') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'Q'))
			{
				cout << " szkwal " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " szkwal " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'S') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'S'))
			{
				cout << " burza piaskowa " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " burza piaskowa " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'U') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'P'))
			{
				cout << " nieznane opady " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " nieznane opady " << endl;
				}
			}
			else if ((metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa][liczba_zjawisk] == 'V') && (metar_testowy[zmienna_pomocincza].zjawiska[zmienna_pogodowa_plus][liczba_zjawisk] == 'A'))
			{
				cout << " pyl wulkaniczny " << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << " pyl wulkaniczny " << endl;
				}
			}
			else
			{
				cout << "Bledny format daty w metarze";
			}

			zmienna_pogodowa = 0;
			zmienna_pogodowa_plus = 0;
			liczba_zjawisk--;
		}
	}

	if (koniec_pliku == false)
	{
		metar_testowy[zmienna_pomocincza].kopia_CAVOK[zmienna_pomocincza] = cavok_wystepuje;
	}
	else
	{
		cavok_wystepuje = metar_testowy[zmienna_pomocincza].kopia_CAVOK[zmienna_pomocincza];
	}

	if (cavok_wystepuje == true && metar_testowy[zmienna_pomocincza].CAVOK[0] == 'C' && metar_testowy[zmienna_pomocincza].CAVOK[1] == 'A' && metar_testowy[zmienna_pomocincza].CAVOK[2] == 'V' && metar_testowy[zmienna_pomocincza].CAVOK[3] == 'O' && metar_testowy[zmienna_pomocincza].CAVOK[4] == 'K')
	{
		cout << "Chmur ponizej 1500 metrow: ";
		cout << "Brak chmur w tym brak chmur cumulunimbus oraz cumulus gorojacy" << endl;
		cout << "Widocznosc: +10 000 metrow" << endl;
		cout << "Zjawiska pogodowe: brak" << endl;
		if (koniec_pliku == false)
		{
			plik_wynikowy << "Chmur ponizej 1500 metrow: ";
			plik_wynikowy << "Brak chmur w tym brak chmur cumulunimbus oraz cumulus gorojacy" << endl;
			plik_wynikowy << "Widocznosc: +10 000 metrow" << endl;
			plik_wynikowy << "Zjawiska pogodowe: brak" << endl;
		}
		cavok_wystepuje = false;
	}

	if (koniec_pliku == false)
	{
		metar_testowy[zmienna_pomocincza].kopia_NSW[zmienna_pomocincza] = nsw_wystepuje;
	}
	else
	{
		nsw_wystepuje = metar_testowy[zmienna_pomocincza].kopia_NSW[zmienna_pomocincza];
	}

	if (nsw_wystepuje == true && metar_testowy[zmienna_pomocincza].NSW[0] == 'N' && metar_testowy[zmienna_pomocincza].NSW[1] == 'S' && metar_testowy[zmienna_pomocincza].NSW[2] == 'W')
	{
		cout << "Zjawiska pogodowe: brak" << endl;
		if (koniec_pliku == false)
		{
			plik_wynikowy << "Zjawiska pogodowe: brak" << endl;
		}
		nsw_wystepuje = false;
	}

	if (koniec_pliku == false)
	{
		metar_testowy[zmienna_pomocincza].kopia_NSC[zmienna_pomocincza] = nsc_wystepuje;
	}
	else
	{
		nsc_wystepuje = metar_testowy[zmienna_pomocincza].kopia_NSC[zmienna_pomocincza];
	}

	if (nsc_wystepuje == true && metar_testowy[zmienna_pomocincza].NSC[0] == 'N' && metar_testowy[zmienna_pomocincza].NSC[1] == 'S' && metar_testowy[zmienna_pomocincza].NSC[2] == 'C')
	{
		cout << "Chmury ponizej 5000: brak" << endl;
		cout << "Chmury powyzej 5000: chmury nie sa typu cumulunimbus ani cumulus" << endl;
		if (koniec_pliku == false)
		{
			plik_wynikowy << "Chmury ponizej 5000: brak" << endl;
			plik_wynikowy << "Chmury powyzej 5000: chmury nie sa typu cumulunimbus ani cumulus" << endl;
		}
		nsc_wystepuje = false;
	}

	if (koniec_pliku == false)
	{
		metar_testowy[zmienna_pomocincza].kopia_VV[zmienna_pomocincza] = VV_wystepuje;
	}
	else
	{
		VV_wystepuje = metar_testowy[zmienna_pomocincza].kopia_VV[zmienna_pomocincza];
	}

	if (VV_wystepuje == true && metar_testowy[zmienna_pomocincza].VV[0] == 'V' && metar_testowy[zmienna_pomocincza].VV[1] == 'V')
	{
		cout << "Widok pionowy: ";
		int widok_pionowy = 0;
		if (metar_testowy[zmienna_pomocincza].VV[2] == '0')
		{
			widok_pionowy = widok_pionowy;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[2] == '1')
		{
			widok_pionowy = widok_pionowy + 10000;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[2] == '2')
		{
			widok_pionowy = widok_pionowy + 20000;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[2] == '3')
		{
			widok_pionowy = widok_pionowy + 30000;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[2] == '4')
		{
			widok_pionowy = widok_pionowy + 40000;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[2] == '5')
		{
			widok_pionowy = widok_pionowy + 50000;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[2] == '6')
		{
			widok_pionowy = widok_pionowy + 60000;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[2] == '7')
		{
			widok_pionowy = widok_pionowy + 70000;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[2] == '8')
		{
			widok_pionowy = widok_pionowy + 80000;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[2] == '9')
		{
			widok_pionowy = widok_pionowy + 90000;
		}

		if (metar_testowy[zmienna_pomocincza].VV[3] == '0')
		{
			widok_pionowy = widok_pionowy;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[3] == '1')
		{
			widok_pionowy = widok_pionowy + 1000;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[3] == '2')
		{
			widok_pionowy = widok_pionowy + 2000;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[3] == '3')
		{
			widok_pionowy = widok_pionowy + 3000;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[3] == '4')
		{
			widok_pionowy = widok_pionowy + 4000;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[3] == '5')
		{
			widok_pionowy = widok_pionowy + 5000;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[3] == '6')
		{
			widok_pionowy = widok_pionowy + 6000;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[3] == '7')
		{
			widok_pionowy = widok_pionowy + 7000;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[3] == '8')
		{
			widok_pionowy = widok_pionowy + 8000;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[3] == '9')
		{
			widok_pionowy = widok_pionowy + 9000;
		}

		if (metar_testowy[zmienna_pomocincza].VV[4] == '0')
		{
			widok_pionowy = widok_pionowy;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[4] == '1')
		{
			widok_pionowy = widok_pionowy + 100;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[4] == '2')
		{
			widok_pionowy = widok_pionowy + 200;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[4] == '3')
		{
			widok_pionowy = widok_pionowy + 300;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[4] == '4')
		{
			widok_pionowy = widok_pionowy + 400;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[4] == '5')
		{
			widok_pionowy = widok_pionowy + 500;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[4] == '6')
		{
			widok_pionowy = widok_pionowy + 600;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[4] == '7')
		{
			widok_pionowy = widok_pionowy + 700;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[4] == '8')
		{
			widok_pionowy = widok_pionowy + 800;
		}
		else if (metar_testowy[zmienna_pomocincza].VV[4] == '9')
		{
			widok_pionowy = widok_pionowy + 900;
		}

		cout << widok_pionowy << " metrow" << endl;
		if (koniec_pliku == false)
		{
			plik_wynikowy << "Widok pionowy: " << widok_pionowy << " metrow" << endl;
		}
		VV_wystepuje = false;
	}

	if (koniec_pliku == false)
	{
		metar_testowy[zmienna_pomocincza].kopia_SKC[zmienna_pomocincza] = skc_wystepuje;
	}
	else
	{
		skc_wystepuje = metar_testowy[zmienna_pomocincza].kopia_SKC[zmienna_pomocincza];
	}

	if (skc_wystepuje == true && metar_testowy[zmienna_pomocincza].SKC[0] == 'S' && metar_testowy[zmienna_pomocincza].SKC[1] == 'K' && metar_testowy[zmienna_pomocincza].SKC[2] == 'C')
	{
		cout << "Zachmurzenie: brak" << endl;
		if (koniec_pliku == false)
		{
			plik_wynikowy << "Zachmurzenie: brak" << endl;
		}
		skc_wystepuje = false;
	}

	if (koniec_pliku == false)
	{
		metar_testowy[zmienna_pomocincza].kopia_NCD[zmienna_pomocincza] = ncd_wystepuje;
	}
	else
	{
		ncd_wystepuje = metar_testowy[zmienna_pomocincza].kopia_NCD[zmienna_pomocincza];
	}

	if (ncd_wystepuje == true && metar_testowy[zmienna_pomocincza].NCD[0] == 'N' && metar_testowy[zmienna_pomocincza].NCD[1] == 'C' && metar_testowy[zmienna_pomocincza].NCD[2] == 'D')
	{
		cout << "Zmierzone chmury: brak" << endl;
		if (koniec_pliku == false)
		{
			plik_wynikowy << "Zmierzone chmury: brak" << endl;
		}
		ncd_wystepuje = false;
	}

	if (koniec_pliku == false)
	{
		metar_testowy[zmienna_pomocincza].kopia_CLR[zmienna_pomocincza] = clr_wystepuje;
	}
	else
	{
		clr_wystepuje = metar_testowy[zmienna_pomocincza].kopia_CLR[zmienna_pomocincza];
	}

	if (clr_wystepuje == true && metar_testowy[zmienna_pomocincza].CLR[0] == 'C' && metar_testowy[zmienna_pomocincza].CLR[1] == 'L' && metar_testowy[zmienna_pomocincza].CLR[2] == 'R')
	{
		cout << "Zachmurzenie ponizej 12 000 stop: brak" << endl;
		if (koniec_pliku == false)
		{
			plik_wynikowy << "Zachmurzenie ponizej 12 000 stop: brak" << endl;
		}
		clr_wystepuje = false;
	}

	if (koniec_pliku == false)
	{
		metar_testowy[zmienna_pomocincza].kopia_kierunki_liczba[zmienna_pomocincza] = kierunki_liczba;
	}
	else
	{
		kierunki_liczba = metar_testowy[zmienna_pomocincza].kopia_kierunki_liczba[zmienna_pomocincza];
	}

	if ((metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[4][kierunki_liczba] == 'N' || metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[4][kierunki_liczba] == 'E' || metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[4][kierunki_liczba] == 'S' || metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[4][kierunki_liczba] == 'W') && (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '0' || metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '1' || metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '2' || metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '3' || metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '4' || metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '5' || metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '6' || metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '7' || metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '8' || metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '9'))
	{
		while (kierunki_liczba != 0)
		{
			cout << "Widocznosc w danym kierunku nr. " << kierunki_liczba << " ";
			int widocznosc_w_kierunku = 0;

			if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '0')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '1')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 1000;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '2')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 2000;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '3')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 3000;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '4')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 4000;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '5')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 5000;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '6')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 6000;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '7')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 7000;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '8')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 8000;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[0][kierunki_liczba] == '9')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 9000;
			}

			if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[1][kierunki_liczba] == '0')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[1][kierunki_liczba] == '1')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 100;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[1][kierunki_liczba] == '2')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 200;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[1][kierunki_liczba] == '3')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 300;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[1][kierunki_liczba] == '4')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 400;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[1][kierunki_liczba] == '5')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 500;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[1][kierunki_liczba] == '6')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 600;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[1][kierunki_liczba] == '7')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 700;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[1][kierunki_liczba] == '8')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 800;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[1][kierunki_liczba] == '9')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 900;
			}

			if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[2][kierunki_liczba] == '0')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[2][kierunki_liczba] == '1')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 10;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[2][kierunki_liczba] == '2')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 20;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[2][kierunki_liczba] == '3')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 30;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[2][kierunki_liczba] == '4')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 40;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[2][kierunki_liczba] == '5')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 50;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[2][kierunki_liczba] == '6')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 60;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[2][kierunki_liczba] == '7')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 70;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[2][kierunki_liczba] == '8')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 80;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[2][kierunki_liczba] == '9')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 90;
			}

			if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[3][kierunki_liczba] == '0')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[3][kierunki_liczba] == '1')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 1;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[3][kierunki_liczba] == '2')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 2;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[3][kierunki_liczba] == '3')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 3;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[3][kierunki_liczba] == '4')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 4;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[3][kierunki_liczba] == '5')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 5;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[3][kierunki_liczba] == '6')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 6;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[3][kierunki_liczba] == '7')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 7;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[3][kierunki_liczba] == '8')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 8;
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[3][kierunki_liczba] == '9')
			{
				widocznosc_w_kierunku = widocznosc_w_kierunku + 9;
			}

			cout << widocznosc_w_kierunku;

			if (koniec_pliku == false)
			{
				metar_testowy[zmienna_pomocincza].kopia_wystepuja_kierunki[kierunki_liczba] = wystepuje_kierunek[kierunki_liczba];
			}
			else
			{
				wystepuje_kierunek[kierunki_liczba] = metar_testowy[zmienna_pomocincza].kopia_wystepuja_kierunki[kierunki_liczba];
			}

			if (koniec_pliku == false)
			{
				metar_testowy[zmienna_pomocincza].kopia_wystepuja_2_kierunki[kierunki_liczba] = wystepuja_2_kierunki[kierunki_liczba];
			}
			else
			{
				wystepuja_2_kierunki[kierunki_liczba] = metar_testowy[zmienna_pomocincza].kopia_wystepuja_2_kierunki[kierunki_liczba];
			}

			if (koniec_pliku == false)
			{
				plik_wynikowy << "Widocznosc w danym kierunku nr. " << kierunki_liczba << " " << widocznosc_w_kierunku;
			}

			if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[4][kierunki_liczba] == 'N')
			{
				cout << " w kierunku polnocnym";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " w kierunku polnocnym";
				}
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[4][kierunki_liczba] == 'E')
			{
				cout << " w kierunku wschodnim";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " w kierunku wschodnim";
				}
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[4][kierunki_liczba] == 'S')
			{
				cout << " w kierunku poludniowym";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " w kierunku poludniowym";
				}
			}
			else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[4][kierunki_liczba] == 'W')
			{
				cout << " w kierunku zachodnim";
				if (koniec_pliku == false)
				{
					plik_wynikowy << " w kierunku zachodnim";
				}
			}

			if (wystepuja_2_kierunki[kierunki_liczba] == true)
			{
				if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[5][kierunki_liczba] == 'N')
				{
					cout << " - polnocnym" << endl;
					if (koniec_pliku == false)
					{
						plik_wynikowy << " - polnocnym" << endl;
					}
				}
				else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[5][kierunki_liczba] == 'E')
				{
					cout << " - wschodnim" << endl;
					if (koniec_pliku == false)
					{
						plik_wynikowy << " - wschodnim" << endl;
					}
				}
				else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[5][kierunki_liczba] == 'S')
				{
					cout << " - poludniowym" << endl;
					if (koniec_pliku == false)
					{
						plik_wynikowy << " - poludniowym" << endl;
					}
				}
				else if (metar_testowy[zmienna_pomocincza].kierunek_widzialnosc[5][kierunki_liczba] == 'W')
				{
					cout << " - zachodnim" << endl;
					if (koniec_pliku == false)
					{
						plik_wynikowy << " - zachodnim" << endl;
					}
				}
				wystepuja_2_kierunki[kierunki_liczba] = false;
			}
			else if (wystepuja_2_kierunki[kierunki_liczba] == false)
			{
				cout << endl;
				if (koniec_pliku == false)
				{
					plik_wynikowy << endl;
				}
			}

			widocznosc_w_kierunku = 0;

			kierunki_liczba--;
		}
	}


}

void tworzenie()
{
	wyswietlany_metar metar_do_wyswietlenia;

	cout << "Informacje nalezy wprowadzac z Caps Lock-iem, bez polskich znakow." << endl;
	cout << "Nie nalezy wprowadzac jednostek program o nie zapyta lub je dopasuje." << endl << endl;
	cout << "Podaj nazwe lotniska (bez spacji w nazwie): ";
	wypelnij(metar_do_wyswietlenia.lotnisko);
	cin >> metar_do_wyswietlenia.lotnisko;
	char pytanie6[10];
	bool chopin = false;
	if (metar_do_wyswietlenia.lotnisko[0] == 'W' && metar_do_wyswietlenia.lotnisko[1] == 'A' && metar_do_wyswietlenia.lotnisko[2] == 'R' && metar_do_wyswietlenia.lotnisko[3] == 'S' && metar_do_wyswietlenia.lotnisko[4] == 'Z' && metar_do_wyswietlenia.lotnisko[5] == 'A' && metar_do_wyswietlenia.lotnisko[6] == 'W' && metar_do_wyswietlenia.lotnisko[7] == 'A')
	{
		cout << "Czy chodzi o lotnisko Chopina: ";
		cin >> pytanie6;
		if (pytanie6[0] == 'T' && pytanie6[1] == 'A' && pytanie6[2] == 'K')
		{
			chopin = true;
		}
		else
		{
			chopin = false;
		}
	}

	cout << "Podaj date: " << endl;
	cout << "Dzien: ";
	cin >> metar_do_wyswietlenia.dzien;
	cout << "Miesiac: ";
	char miesiac[50];
	cin >> miesiac;
	cout << "Rok: ";
	char rok[50];
	cin >> rok;

	cout << "Podaj czas UTC" << endl;
	cout << "Godziny: ";
	cin >> metar_do_wyswietlenia.godziny;
	cout << "Minuty: ";
	cin >> metar_do_wyswietlenia.minuty;

	cout << "Podaj kierunek i predkosc wiatru" << endl;
	cout << "Sredni kierunek wiatru w stopniach: ";
	cin >> metar_do_wyswietlenia.sredni_kierunek;
	cout << "Sredni predkosc wiatru: ";
	cin >> metar_do_wyswietlenia.srednia_predkosc;

	cout << "Czy wystepuja szczyty wiatrow: ";
	char pytanie1[10];
	cin >> pytanie1;

	bool szczyty = false;
	if (pytanie1[0] == 'T' && pytanie1[1] == 'A' && pytanie1[2] == 'K')
	{
		szczyty = true;
		cout << "Podaj szczytowa predkosc wiatru: ";
		cin >> metar_do_wyswietlenia.szczyty_wiatru;
	}
	else
	{
		szczyty = false;
	}

	cout << "Podaj temperature" << endl;
	cout << "Czy temperatura jest ujemna: ";
	char pytanie4[10];
	cin >> pytanie4;
	bool ujemna = false;
	if (pytanie4[0] == 'T' && pytanie4[1] == 'A' && pytanie4[2] == 'K')
	{
		ujemna = true;
	}
	else
	{
		ujemna = false;
	}
	cout << "Podaj wartosc temperatury: ";
	cin >> metar_do_wyswietlenia.temperatura;


	cout << "Podaj cisnienie: ";
	cin >> metar_do_wyswietlenia.cisnienie;

	cout << "Wprowadz jednostke cisnienia hektopaskal (HPA) ; cale slupa rteci (INHG): ";
	char pytanie5[10];
	cin >> pytanie5;

	bool jednostka = true;
	if (pytanie5[0] == 'H' && pytanie5[1] == 'P' && pytanie5[2] == 'A')
	{
		jednostka = true;
	}
	else if (pytanie5[0] == 'I' && pytanie5[1] == 'N' && pytanie5[2] == 'H' && pytanie5[3] == 'G')
	{
		jednostka = false;
	}
	else
	{
		cout << "Bledna jednostka";
	}

	cout << "Sprawdz czy wprowadzone dane sa poprawne" << endl;
	cout << "Czy dane sa poprawne: ";
	char pytanie3[10];
	cin >> pytanie3;
	if (pytanie3[0] == 'T' && pytanie3[1] == 'A' && pytanie3[2] == 'K')
	{
		wyswietl_stworzony_metar(szczyty, ujemna, jednostka, metar_do_wyswietlenia, chopin);
	}
	else
	{
		system("cls");
		cout << "Powrot do menu, wybierz opcje nr. 5 i wprowadz dane ponownie" << endl;
	}
}

void wyswietl_stworzony_metar(bool& szczyty, bool& ujemna, bool& jednostka, wyswietlany_metar metar_do_wyswietlenia, bool& chopin)
{
	system("cls");
	cout << endl << "Metar: " << endl << endl;
	bool przelacznik_bezpieczenstwa = false;

	if (metar_do_wyswietlenia.lotnisko[0] == 'G' && metar_do_wyswietlenia.lotnisko[1] == 'D' && metar_do_wyswietlenia.lotnisko[2] == 'A' && metar_do_wyswietlenia.lotnisko[3] == 'N' && metar_do_wyswietlenia.lotnisko[4] == 'S' && metar_do_wyswietlenia.lotnisko[5] == 'K' && metar_do_wyswietlenia.lotnisko[7] == '*')
	{
		cout << "EPGD ";
	}
	else if (metar_do_wyswietlenia.lotnisko[0] == 'K' && metar_do_wyswietlenia.lotnisko[1] == 'R' && metar_do_wyswietlenia.lotnisko[2] == 'A' && metar_do_wyswietlenia.lotnisko[3] == 'K' && metar_do_wyswietlenia.lotnisko[4] == 'O' && metar_do_wyswietlenia.lotnisko[5] == 'W' && metar_do_wyswietlenia.lotnisko[7] == '*')
	{
		cout << "EPKK ";
	}
	else if (metar_do_wyswietlenia.lotnisko[0] == 'K' && metar_do_wyswietlenia.lotnisko[1] == 'A' && metar_do_wyswietlenia.lotnisko[2] == 'T' && metar_do_wyswietlenia.lotnisko[3] == 'O' && metar_do_wyswietlenia.lotnisko[4] == 'W' && metar_do_wyswietlenia.lotnisko[5] == 'I' && metar_do_wyswietlenia.lotnisko[6] == 'C' && metar_do_wyswietlenia.lotnisko[7] == 'E' && metar_do_wyswietlenia.lotnisko[9] == '*')
	{
		cout << "EPKT ";
	}
	else if (metar_do_wyswietlenia.lotnisko[0] == 'W' && metar_do_wyswietlenia.lotnisko[1] == 'R' && metar_do_wyswietlenia.lotnisko[2] == 'O' && metar_do_wyswietlenia.lotnisko[3] == 'C' && metar_do_wyswietlenia.lotnisko[4] == 'L' && metar_do_wyswietlenia.lotnisko[5] == 'A' && metar_do_wyswietlenia.lotnisko[6] == 'W' && metar_do_wyswietlenia.lotnisko[8] == '*')
	{
		cout << "EPWR ";
	}
	else if (metar_do_wyswietlenia.lotnisko[0] == 'P' && metar_do_wyswietlenia.lotnisko[1] == 'O' && metar_do_wyswietlenia.lotnisko[2] == 'Z' && metar_do_wyswietlenia.lotnisko[3] == 'N' && metar_do_wyswietlenia.lotnisko[4] == 'A' && metar_do_wyswietlenia.lotnisko[5] == 'N' && metar_do_wyswietlenia.lotnisko[7] == '*')
	{
		cout << "EPPO ";
	}
	else if (metar_do_wyswietlenia.lotnisko[0] == 'R' && metar_do_wyswietlenia.lotnisko[1] == 'Z' && metar_do_wyswietlenia.lotnisko[2] == 'E' && metar_do_wyswietlenia.lotnisko[3] == 'S' && metar_do_wyswietlenia.lotnisko[4] == 'Z' && metar_do_wyswietlenia.lotnisko[5] == 'O' && metar_do_wyswietlenia.lotnisko[6] == 'W' && metar_do_wyswietlenia.lotnisko[8] == '*')
	{
		cout << "EPRZ ";
	}
	else if (metar_do_wyswietlenia.lotnisko[0] == 'S' && metar_do_wyswietlenia.lotnisko[1] == 'Z' && metar_do_wyswietlenia.lotnisko[2] == 'C' && metar_do_wyswietlenia.lotnisko[3] == 'Z' && metar_do_wyswietlenia.lotnisko[4] == 'E' && metar_do_wyswietlenia.lotnisko[5] == 'C' && metar_do_wyswietlenia.lotnisko[6] == 'I' && metar_do_wyswietlenia.lotnisko[7] == 'N' && metar_do_wyswietlenia.lotnisko[9] == '*')
	{
		cout << "EPSC ";
	}
	else if (metar_do_wyswietlenia.lotnisko[0] == 'L' && metar_do_wyswietlenia.lotnisko[1] == 'U' && metar_do_wyswietlenia.lotnisko[2] == 'B' && metar_do_wyswietlenia.lotnisko[3] == 'L' && metar_do_wyswietlenia.lotnisko[4] == 'I' && metar_do_wyswietlenia.lotnisko[5] == 'N' && metar_do_wyswietlenia.lotnisko[7] == '*')
	{
		cout << "EPLB ";
	}
	else if (metar_do_wyswietlenia.lotnisko[0] == 'B' && metar_do_wyswietlenia.lotnisko[1] == 'Y' && metar_do_wyswietlenia.lotnisko[2] == 'D' && metar_do_wyswietlenia.lotnisko[3] == 'G' && metar_do_wyswietlenia.lotnisko[4] == 'O' && metar_do_wyswietlenia.lotnisko[5] == 'S' && metar_do_wyswietlenia.lotnisko[6] == 'Z' && metar_do_wyswietlenia.lotnisko[7] == 'C' && metar_do_wyswietlenia.lotnisko[8] == 'Z' && metar_do_wyswietlenia.lotnisko[10] == '*')
	{
		cout << "EPBY ";
	}
	else if (metar_do_wyswietlenia.lotnisko[0] == 'L' && metar_do_wyswietlenia.lotnisko[1] == 'O' && metar_do_wyswietlenia.lotnisko[2] == 'D' && metar_do_wyswietlenia.lotnisko[3] == 'Z' && metar_do_wyswietlenia.lotnisko[5] == '*')
	{
		cout << "EPLL ";
	}
	else if (metar_do_wyswietlenia.lotnisko[0] == 'O' && metar_do_wyswietlenia.lotnisko[1] == 'L' && metar_do_wyswietlenia.lotnisko[2] == 'S' && metar_do_wyswietlenia.lotnisko[3] == 'Z' && metar_do_wyswietlenia.lotnisko[4] == 'T' && metar_do_wyswietlenia.lotnisko[5] == 'Y' && metar_do_wyswietlenia.lotnisko[6] == 'N' && metar_do_wyswietlenia.lotnisko[8] == '*')
	{
		cout << "EPSY ";
	}
	else if (metar_do_wyswietlenia.lotnisko[0] == 'R' && metar_do_wyswietlenia.lotnisko[1] == 'A' && metar_do_wyswietlenia.lotnisko[2] == 'D' && metar_do_wyswietlenia.lotnisko[3] == 'O' && metar_do_wyswietlenia.lotnisko[4] == 'M' && metar_do_wyswietlenia.lotnisko[6] == '*')
	{
		cout << "EPRA ";
	}
	else if (metar_do_wyswietlenia.lotnisko[0] == 'Z' && metar_do_wyswietlenia.lotnisko[1] == 'I' && metar_do_wyswietlenia.lotnisko[2] == 'E' && metar_do_wyswietlenia.lotnisko[3] == 'L' && metar_do_wyswietlenia.lotnisko[4] == 'O' && metar_do_wyswietlenia.lotnisko[5] == 'N' && metar_do_wyswietlenia.lotnisko[6] == 'A' && metar_do_wyswietlenia.lotnisko[7] == 'G' && metar_do_wyswietlenia.lotnisko[8] == 'O' && metar_do_wyswietlenia.lotnisko[9] == 'R' && metar_do_wyswietlenia.lotnisko[10] == 'A' && metar_do_wyswietlenia.lotnisko[12] == '*')
	{
		cout << "EPZG ";
	}
	else if (metar_do_wyswietlenia.lotnisko[0] == 'W' && metar_do_wyswietlenia.lotnisko[1] == 'A' && metar_do_wyswietlenia.lotnisko[2] == 'R' && metar_do_wyswietlenia.lotnisko[3] == 'S' && metar_do_wyswietlenia.lotnisko[4] == 'Z' && metar_do_wyswietlenia.lotnisko[5] == 'A' && metar_do_wyswietlenia.lotnisko[6] == 'W' && metar_do_wyswietlenia.lotnisko[7] == 'A' && metar_do_wyswietlenia.lotnisko[9] == '*' && chopin == true)
	{
		cout << "EPWA ";
	}
	else if (metar_do_wyswietlenia.lotnisko[0] == 'W' && metar_do_wyswietlenia.lotnisko[1] == 'A' && metar_do_wyswietlenia.lotnisko[2] == 'R' && metar_do_wyswietlenia.lotnisko[3] == 'S' && metar_do_wyswietlenia.lotnisko[4] == 'Z' && metar_do_wyswietlenia.lotnisko[5] == 'A' && metar_do_wyswietlenia.lotnisko[6] == 'W' && metar_do_wyswietlenia.lotnisko[7] == 'A' && metar_do_wyswietlenia.lotnisko[9] == '*' && chopin == false)
	{
		cout << "EPMO ";
	}
	else
	{
		cout << "Podano bledny kod lotniska" << endl << endl;
		przelacznik_bezpieczenstwa = true;
	}

	if (metar_do_wyswietlenia.dzien > 31)
	{
		cout << "Podano bledny dzien" << endl << endl;
		przelacznik_bezpieczenstwa = true;
	}
	else if (metar_do_wyswietlenia.dzien > 9)
	{
		cout << metar_do_wyswietlenia.dzien;
	}
	else if (metar_do_wyswietlenia.dzien <= 9)
	{
		cout << "0" << metar_do_wyswietlenia.dzien;
	}
	else
	{
		cout << "Podano bledny dzien" << endl << endl;
		przelacznik_bezpieczenstwa = true;
	}

	if (metar_do_wyswietlenia.godziny > 60)
	{
		cout << "Podano bledna godzine" << endl << endl;
		przelacznik_bezpieczenstwa = true;
	}
	else if (metar_do_wyswietlenia.godziny > 9)
	{
		cout << metar_do_wyswietlenia.godziny;
	}
	else if (metar_do_wyswietlenia.godziny <= 9)
	{
		cout << "0" << metar_do_wyswietlenia.godziny;
	}
	else
	{
		cout << "Podano bledna godzine" << endl << endl;
		przelacznik_bezpieczenstwa = true;
	}

	if (metar_do_wyswietlenia.minuty > 60)
	{
		cout << "Podano bledna godzine" << endl << endl;
		przelacznik_bezpieczenstwa = true;
	}
	else if (metar_do_wyswietlenia.minuty > 9)
	{
		cout << metar_do_wyswietlenia.minuty;
	}
	else if (metar_do_wyswietlenia.minuty <= 9)
	{
		cout << "0" << metar_do_wyswietlenia.minuty;
	}
	else
	{
		cout << "Podano bledna godzine" << endl << endl;
		przelacznik_bezpieczenstwa = true;
	}

	cout << "Z ";

	if (metar_do_wyswietlenia.sredni_kierunek > 360)
	{
		cout << "Podano bledny kierunek wiatru" << endl << endl;
		przelacznik_bezpieczenstwa = true;
	}
	else if (metar_do_wyswietlenia.sredni_kierunek >= 100)
	{
		cout << metar_do_wyswietlenia.sredni_kierunek;
	}
	else if (metar_do_wyswietlenia.sredni_kierunek < 100 && metar_do_wyswietlenia.sredni_kierunek >= 10)
	{
		cout << "0" << metar_do_wyswietlenia.sredni_kierunek;
	}
	else if (metar_do_wyswietlenia.minuty < 10)
	{
		cout << "0" << "0" << metar_do_wyswietlenia.sredni_kierunek;
	}
	else
	{
		cout << "Podano bledna godzine" << endl << endl;
		przelacznik_bezpieczenstwa = true;
	}

	if (metar_do_wyswietlenia.srednia_predkosc >= 100)
	{
		cout << "Podano bledny predkosc wiatru" << endl << endl;
		przelacznik_bezpieczenstwa = true;
	}
	else if (metar_do_wyswietlenia.srednia_predkosc < 100 && metar_do_wyswietlenia.srednia_predkosc >= 10)
	{
		cout << metar_do_wyswietlenia.srednia_predkosc;
	}
	else if (metar_do_wyswietlenia.srednia_predkosc < 10)
	{
		cout << "0" << metar_do_wyswietlenia.srednia_predkosc;
	}
	else
	{
		cout << "Podano bledny predkosc wiatru" << endl << endl;
		przelacznik_bezpieczenstwa = true;
	}

	if (szczyty == true)
	{
		cout << "G";
	}
	else
	{
		cout << "KT ";
	}

	if (szczyty == true)
	{
		if (metar_do_wyswietlenia.szczyty_wiatru >= 100)
		{
			cout << "Podano bledne szczyty wiatru" << endl << endl;
			przelacznik_bezpieczenstwa = true;
		}
		else if (metar_do_wyswietlenia.szczyty_wiatru < 100 && metar_do_wyswietlenia.szczyty_wiatru >= 10)
		{
			cout << metar_do_wyswietlenia.szczyty_wiatru;
		}
		else if (metar_do_wyswietlenia.szczyty_wiatru < 10)
		{
			cout << "0" << metar_do_wyswietlenia.szczyty_wiatru;
		}
		else
		{
			cout << "Podano bledne szczyty wiatru" << endl << endl;
			przelacznik_bezpieczenstwa = true;
		}

		cout << "KT ";

	}

	if (ujemna == true)
	{
		cout << "M";
	}
	else if (ujemna == false)
	{

	}
	else
	{
		cout << "Podano bledna temperature";
		przelacznik_bezpieczenstwa = true;
	}

	if (metar_do_wyswietlenia.temperatura >= 100)
	{
		cout << "Podano bledna temperature" << endl << endl;
		przelacznik_bezpieczenstwa = true;
	}
	else if (metar_do_wyswietlenia.temperatura >= 10)
	{
		cout << metar_do_wyswietlenia.temperatura;
	}
	else if (metar_do_wyswietlenia.temperatura < 10)
	{
		cout << "0" << metar_do_wyswietlenia.temperatura;
	}
	else
	{
		cout << "Podano bledna temperature" << endl << endl;
		przelacznik_bezpieczenstwa = true;
	}

	if (jednostka == true)
	{
		cout << "/// Q";
	}
	else if (jednostka == false)
	{
		cout << "/// A";
	}
	else
	{
		cout << "Podano bledna jednostke" << endl << endl;
		przelacznik_bezpieczenstwa = true;
	}

	if (metar_do_wyswietlenia.cisnienie >= 10000)
	{
		cout << "Podano bledne cisnenie" << endl << endl;
		przelacznik_bezpieczenstwa = true;
	}
	else if (metar_do_wyswietlenia.cisnienie >= 1000)
	{
		cout << metar_do_wyswietlenia.cisnienie;
	}
	else if (metar_do_wyswietlenia.cisnienie >= 100)
	{
		cout << "0" << metar_do_wyswietlenia.cisnienie;
	}
	else if (metar_do_wyswietlenia.cisnienie >= 10)
	{
		cout << "0" << "0" << metar_do_wyswietlenia.cisnienie;
	}
	else if (metar_do_wyswietlenia.cisnienie < 10)
	{
		cout << "0" << "0" << "0" << metar_do_wyswietlenia.cisnienie;
	}
	else
	{
		cout << "Podano bledna jednostke" << endl << endl;
		przelacznik_bezpieczenstwa = true;
	}

	if (metar_do_wyswietlenia.srednia_predkosc >= metar_do_wyswietlenia.szczyty_wiatru && szczyty == true)
	{
		cout << endl << endl << "Srednia predkosc nie moze byc wieksza od porywow wiatru";
		przelacznik_bezpieczenstwa = true;
	}

	if (przelacznik_bezpieczenstwa == true)
	{
		cout << endl << endl << "Ostrzezenie podano bledne informacjie, metar nie jest kompletny";
	}

	cout << endl << endl;
}

void wypelnij(char tablica[])
{
	for (int i = 0; i < 50; i++)
	{
		tablica[i] = '*';
	}
}

int wczytaj_plik_i_wyraz2()
{
	wyraz wyraz_testowy;
	metar metar_testowy[4];

	ifstream plik_wejsciowy("Metar lotniskapl.txt");
	plik_wejsciowy.unsetf(ios_base::skipws);
	if (!plik_wejsciowy.is_open())
	{
		cout << "Nie udalo sie wczytac pliku";
		return 0;
	}

	char znak_testowy = '*';
	int i = 0;
	int numer_metaru = 1;
	bool porywy = false;
	bool zmiany = false;
	bool temperatura_ujemna = false;
	bool rosa_ujemna = false;
	int liczba_chmur = 0;
	bool cumulonimbus[26];
	bool cumulus[26];
	int liczba_zjawisk = 0;
	bool charakterystyka[26];
	bool intensywnosc[26];
	bool plus_lub_minus[26];
	bool koniec_pliku = false;
	bool cavok_wystepuje = false;
	bool nsw_wystepuje = false;
	bool nsc_wystepuje = false;
	bool VV_wystepuje = false;
	bool skc_wystepuje = false;
	bool ncd_wystepuje = false;
	bool clr_wystepuje = false;
	bool wystepuje_kierunek[26];
	int kierunki_liczba = 0;
	bool wystepuja_2_kierunki[26];

	ofstream plik_wynikowy("pogoda_lotniska.txt");

	while (!plik_wejsciowy.eof())
	{
		plik_wejsciowy >> znak_testowy;

		if (plik_wejsciowy.eof())
		{
			sprawdz_wyraz(wyraz_testowy, metar_testowy, numer_metaru, zmiany, porywy, temperatura_ujemna, rosa_ujemna, liczba_chmur, cumulonimbus, cumulus, liczba_zjawisk, charakterystyka, intensywnosc, plus_lub_minus, cavok_wystepuje, nsw_wystepuje, nsc_wystepuje, VV_wystepuje, skc_wystepuje, ncd_wystepuje, clr_wystepuje, wystepuje_kierunek, kierunki_liczba, wystepuja_2_kierunki);
			rozkoduj(metar_testowy, numer_metaru, zmiany, porywy, temperatura_ujemna, rosa_ujemna, liczba_chmur, cumulonimbus, cumulus, koniec_pliku, liczba_zjawisk, charakterystyka, intensywnosc, plus_lub_minus, plik_wynikowy, cavok_wystepuje, nsw_wystepuje, nsc_wystepuje, VV_wystepuje, skc_wystepuje, ncd_wystepuje, clr_wystepuje, wystepuje_kierunek, kierunki_liczba, wystepuja_2_kierunki);

			koniec_pliku = true;
			system("cls");
			numer_metaru = numer_metaru - 2;
			for (int i = 0; i < 3; i++)
			{
				rozkoduj(metar_testowy, numer_metaru, zmiany, porywy, temperatura_ujemna, rosa_ujemna, liczba_chmur, cumulonimbus, cumulus, koniec_pliku, liczba_zjawisk, charakterystyka, intensywnosc, plus_lub_minus, plik_wynikowy, cavok_wystepuje, nsw_wystepuje, nsc_wystepuje, VV_wystepuje, skc_wystepuje, ncd_wystepuje, clr_wystepuje, wystepuje_kierunek, kierunki_liczba, wystepuja_2_kierunki);
				numer_metaru++;
			}

			i = -1;
			wyraz_testowy.dlugosc = 0;
			numer_metaru++;
		}

		else if (znak_testowy != 32 && znak_testowy != 10)
		{
			wyraz_testowy.znak[i] = znak_testowy;
			wyraz_testowy.dlugosc++;
		}

		else if (znak_testowy == 32)
		{
			sprawdz_wyraz(wyraz_testowy, metar_testowy, numer_metaru, zmiany, porywy, temperatura_ujemna, rosa_ujemna, liczba_chmur, cumulonimbus, cumulus, liczba_zjawisk, charakterystyka, intensywnosc, plus_lub_minus, cavok_wystepuje, nsw_wystepuje, nsc_wystepuje, VV_wystepuje, skc_wystepuje, ncd_wystepuje, clr_wystepuje, wystepuje_kierunek, kierunki_liczba, wystepuja_2_kierunki);
			i = -1;
			wyraz_testowy.dlugosc = 0;
		}

		else if (znak_testowy == 10)
		{
			sprawdz_wyraz(wyraz_testowy, metar_testowy, numer_metaru, zmiany, porywy, temperatura_ujemna, rosa_ujemna, liczba_chmur, cumulonimbus, cumulus, liczba_zjawisk, charakterystyka, intensywnosc, plus_lub_minus, cavok_wystepuje, nsw_wystepuje, nsc_wystepuje, VV_wystepuje, skc_wystepuje, ncd_wystepuje, clr_wystepuje, wystepuje_kierunek, kierunki_liczba, wystepuja_2_kierunki);
			rozkoduj(metar_testowy, numer_metaru, zmiany, porywy, temperatura_ujemna, rosa_ujemna, liczba_chmur, cumulonimbus, cumulus, koniec_pliku, liczba_zjawisk, charakterystyka, intensywnosc, plus_lub_minus, plik_wynikowy, cavok_wystepuje, nsw_wystepuje, nsc_wystepuje, VV_wystepuje, skc_wystepuje, ncd_wystepuje, clr_wystepuje, wystepuje_kierunek, kierunki_liczba, wystepuja_2_kierunki);
			i = -1;
			wyraz_testowy.dlugosc = 0;
			numer_metaru++;
		}

		i++;

	}
	plik_wejsciowy.close();
	plik_wynikowy.close();
}
