#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

struct ElementDrzewa
{
	int liczba = 0;
	struct ElementDrzewa** dzieci_elementu = nullptr;
};

struct KorzenDrzewa
{
	int liczba_instrukcji = 0;
	int rozmiar_korzenia = 0;
	int ilosc_dzieci_wezlow = 0;
	int liczba_w_korzeniu = 0;
	bool korzen_zajety = false;
	struct ElementDrzewa** elementy_korzenia = nullptr;
};

void wczytaj_drzewo(KorzenDrzewa& Korzen);
void wczytaj_instrukcje(KorzenDrzewa& Korzen);
void dodaj_element(KorzenDrzewa& Korzen);
void wyswietl_drzewo(KorzenDrzewa& Korzen);
void wyswietl_liscie(KorzenDrzewa& Korzen, ElementDrzewa* Lisc);
void sprawdz_czy_zawiera_element(KorzenDrzewa& Korzen);
void usun_element_drzewa(KorzenDrzewa& Korzen);
void szukanie_kasowanie(KorzenDrzewa& Korzen, ElementDrzewa* Rodzic, ElementDrzewa* Dziecko, bool& dokonano_zamiany, int& liczba_do_podmiany);
void znajdz_lewy_pusty_lisc_korzen(KorzenDrzewa& Korzen, ElementDrzewa* Lisc, ElementDrzewa* Rodzic, int& liczba_do_usuniecia, bool& zamieniono_liczbe, int& liczba_do_zamiany);

int main()
{
	KorzenDrzewa Korzen;

	wczytaj_drzewo(Korzen);

	wczytaj_instrukcje(Korzen);
}

void wczytaj_drzewo(KorzenDrzewa& Korzen)
{
	scanf("%d", &Korzen.liczba_instrukcji);

	int minimalna_liczba = 0;
	int maksymalna_liczba = 0;

	scanf("%d", &minimalna_liczba);
	scanf("%d", &maksymalna_liczba);

	scanf("%d", &Korzen.rozmiar_korzenia);
	scanf("%d", &Korzen.ilosc_dzieci_wezlow);

	Korzen.elementy_korzenia = new ElementDrzewa * [Korzen.rozmiar_korzenia];

	for (int i = 0; i < Korzen.rozmiar_korzenia; i++)
	{
		Korzen.elementy_korzenia[i] = nullptr;
	}
}

void wczytaj_instrukcje(KorzenDrzewa& Korzen)
{
	char instrukcja = '*';

	for (int i = 0; i < Korzen.liczba_instrukcji; i++)
	{
		scanf(" %c", &instrukcja);

		switch (instrukcja)
		{
		case 'I':
			dodaj_element(Korzen);
			break;
		case 'P':
			wyswietl_drzewo(Korzen);
			break;
		case 'L':
			sprawdz_czy_zawiera_element(Korzen);
			break;
		case 'D':
			usun_element_drzewa(Korzen);
			break;
		default:
			break;

		}
	}
}

void dodaj_element(KorzenDrzewa& Korzen)
{
	int liczba_do_dodania = 0;
	scanf("%d", &liczba_do_dodania);

	if (Korzen.korzen_zajety == true)
	{
		if (liczba_do_dodania == Korzen.liczba_w_korzeniu)
		{
			printf("%d exist\n", liczba_do_dodania);
			return;
		}
	}
	else
	{
		Korzen.liczba_w_korzeniu = liczba_do_dodania;
		Korzen.korzen_zajety = true;
		return;
	}

	int liczba_do_pozycji = liczba_do_dodania;
	ElementDrzewa* aktualny_rodzic = nullptr;
	ElementDrzewa* aktualny_element = nullptr;

	int aktualny_indeks = liczba_do_pozycji % Korzen.rozmiar_korzenia;
	liczba_do_pozycji = liczba_do_pozycji / Korzen.rozmiar_korzenia;

	aktualny_element = Korzen.elementy_korzenia[aktualny_indeks];

	if (aktualny_element == nullptr)
	{
		ElementDrzewa* nowy_element = new ElementDrzewa;

		Korzen.elementy_korzenia[aktualny_indeks] = nowy_element;
		nowy_element->dzieci_elementu = nullptr;

		nowy_element->liczba = liczba_do_dodania;
		return;
	}
	else if (liczba_do_dodania == aktualny_element->liczba)
	{
		printf("%d exist\n", liczba_do_dodania);
		return;
	}
	else
	{
		aktualny_rodzic = aktualny_element;
	}

	while (true)
	{
		if (liczba_do_dodania == aktualny_rodzic->liczba)
		{
			printf("%d exist\n", liczba_do_dodania);
			return;
		}

		if (aktualny_rodzic->dzieci_elementu == nullptr)
		{
			aktualny_rodzic->dzieci_elementu = new ElementDrzewa * [Korzen.ilosc_dzieci_wezlow];
			for (int i = 0; i < Korzen.ilosc_dzieci_wezlow; i++)
			{
				aktualny_rodzic->dzieci_elementu[i] = nullptr;
			}
		}

		aktualny_indeks = liczba_do_pozycji % Korzen.ilosc_dzieci_wezlow;
		liczba_do_pozycji = liczba_do_pozycji / Korzen.ilosc_dzieci_wezlow;

		aktualny_element = aktualny_rodzic->dzieci_elementu[aktualny_indeks];

		if (aktualny_element == nullptr)
		{
			ElementDrzewa* nowy_element_lisc = new ElementDrzewa;

			aktualny_rodzic->dzieci_elementu[aktualny_indeks] = nowy_element_lisc;

			nowy_element_lisc->liczba = liczba_do_dodania;

			nowy_element_lisc->dzieci_elementu = nullptr;
			return;
		}
		else
		{
			aktualny_rodzic = aktualny_element;
		}
	}
}

void wyswietl_drzewo(KorzenDrzewa& Korzen)
{
	printf("%d ", Korzen.liczba_w_korzeniu);

	for (int i = 0; i < Korzen.rozmiar_korzenia; i++)
	{
		wyswietl_liscie(Korzen, Korzen.elementy_korzenia[i]);
	}

	printf("\n");
}

void wyswietl_liscie(KorzenDrzewa& Korzen, ElementDrzewa* Lisc)
{
	if (Lisc == nullptr)
	{
		return;
	}

	printf("%d ", Lisc->liczba);

	if (Lisc->dzieci_elementu != nullptr)
	{
		for (int i = 0; i < Korzen.ilosc_dzieci_wezlow; i++)
		{
			wyswietl_liscie(Korzen, Lisc->dzieci_elementu[i]);
		}
	}
}

void sprawdz_czy_zawiera_element(KorzenDrzewa& Korzen)
{
	int liczba_do_sprawdzenia = 0;
	scanf("%d", &liczba_do_sprawdzenia);

	if (Korzen.korzen_zajety == true)
	{
		if (liczba_do_sprawdzenia == Korzen.liczba_w_korzeniu)
		{
			printf("%d exist\n", liczba_do_sprawdzenia);
			return;
		}
	}
	else
	{
		printf("%d not exist\n", liczba_do_sprawdzenia);
		return;
	}


	int liczba_do_pozycji = liczba_do_sprawdzenia;
	ElementDrzewa* aktualny_element = nullptr;

	int aktualny_indeks = liczba_do_pozycji % Korzen.rozmiar_korzenia;
	liczba_do_pozycji = liczba_do_pozycji / Korzen.rozmiar_korzenia;

	if (Korzen.elementy_korzenia[aktualny_indeks] == nullptr)
	{
		printf("%d not exist\n", liczba_do_sprawdzenia);
		return;
	}

	aktualny_element = Korzen.elementy_korzenia[aktualny_indeks];

	if (liczba_do_sprawdzenia == aktualny_element->liczba)
	{
		printf("%d exist\n", liczba_do_sprawdzenia);
		return;
	}

	while (true)
	{
		if (aktualny_element->dzieci_elementu == nullptr)
		{
			printf("%d not exist\n", liczba_do_sprawdzenia);
			return;
		}

		int aktualny_indeks_lisc = liczba_do_pozycji % Korzen.ilosc_dzieci_wezlow;
		liczba_do_pozycji = liczba_do_pozycji / Korzen.ilosc_dzieci_wezlow;

		ElementDrzewa* element_liscie = aktualny_element->dzieci_elementu[aktualny_indeks_lisc];

		if (element_liscie == nullptr)
		{
			printf("%d not exist\n", liczba_do_sprawdzenia);
			return;
		}
		else if (liczba_do_sprawdzenia == element_liscie->liczba)
		{
			printf("%d exist\n", liczba_do_sprawdzenia);
			return;
		}

		aktualny_element = element_liscie;
	}
}

void usun_element_drzewa(KorzenDrzewa& Korzen)
{
	int liczba_do_usuniecia = 0;
	scanf("%d", &liczba_do_usuniecia);

	int liczba_do_podmiany = 0;

	if (Korzen.korzen_zajety == false)
	{
		printf("%d not exist\n", liczba_do_usuniecia);
		return;
	}

	if (Korzen.korzen_zajety == true && liczba_do_usuniecia == Korzen.liczba_w_korzeniu)
	{
		bool korzen_ma_dzieci = false;

		for (int i = 0; i < Korzen.rozmiar_korzenia; i++)
		{
			if (Korzen.elementy_korzenia[i] != nullptr)
			{
				korzen_ma_dzieci = true;
				break;
			}
		}

		if (korzen_ma_dzieci == false)
		{
			Korzen.liczba_w_korzeniu = 0;
			Korzen.korzen_zajety = false;
		}
		else
		{
			bool znaleziono_odpowiedni_lisc = false;

			for (int i = 0; i < Korzen.rozmiar_korzenia; i++)
			{
				if (Korzen.elementy_korzenia[i] != nullptr)
				{
					znajdz_lewy_pusty_lisc_korzen(Korzen, Korzen.elementy_korzenia[i], nullptr, liczba_do_usuniecia, znaleziono_odpowiedni_lisc, liczba_do_podmiany);
				}

				if (znaleziono_odpowiedni_lisc == true)
				{
					break;
				}
			}

			Korzen.liczba_w_korzeniu = liczba_do_podmiany;
		}

		return;
	}

	int liczba_do_pozycji = liczba_do_usuniecia;
	ElementDrzewa* aktualny_element = nullptr;

	int indeks_usuwanie = liczba_do_pozycji % Korzen.rozmiar_korzenia;
	liczba_do_pozycji = liczba_do_pozycji / Korzen.rozmiar_korzenia;

	if (Korzen.elementy_korzenia[indeks_usuwanie] == nullptr)
	{
		printf("%d not exist\n", liczba_do_usuniecia);
		return;
	}

	aktualny_element = Korzen.elementy_korzenia[indeks_usuwanie];

	if (liczba_do_usuniecia == aktualny_element->liczba)
	{
		bool znaleziono_odpowiedni_lisc = false;

		for (int i = 0; i < Korzen.ilosc_dzieci_wezlow; i++)
		{
			szukanie_kasowanie(Korzen, aktualny_element, aktualny_element->dzieci_elementu[i], znaleziono_odpowiedni_lisc, liczba_do_podmiany);

			if (znaleziono_odpowiedni_lisc == true)
			{
				break;
			}
		}
		Korzen.elementy_korzenia[indeks_usuwanie]->liczba = liczba_do_podmiany;

		return;
	}

	while (true)
	{
		if (aktualny_element->dzieci_elementu == nullptr)
		{
			printf("%d not exist\n", liczba_do_usuniecia);
			return;
		}

		int indeks_liscie = liczba_do_pozycji % Korzen.ilosc_dzieci_wezlow;
		liczba_do_pozycji = liczba_do_pozycji / Korzen.ilosc_dzieci_wezlow;

		ElementDrzewa* nastepny_element = aktualny_element->dzieci_elementu[indeks_liscie];

		if (nastepny_element == nullptr)
		{
			printf("%d not exist\n", liczba_do_usuniecia);
			return;
		}
		else if (liczba_do_usuniecia == nastepny_element->liczba)
		{
			bool znaleziono_odpowiedni_lisc = false;

			for (int i = 0; i < Korzen.ilosc_dzieci_wezlow; i++)
			{
				szukanie_kasowanie(Korzen, aktualny_element, nastepny_element, znaleziono_odpowiedni_lisc, liczba_do_podmiany);

				if (znaleziono_odpowiedni_lisc == true)
				{
					break;
				}
			}
			nastepny_element->liczba = liczba_do_podmiany;

			return;
		}

		aktualny_element = nastepny_element;
	}
}

void szukanie_kasowanie(KorzenDrzewa& Korzen, ElementDrzewa* Rodzic, ElementDrzewa* Dziecko, bool& dokonano_zamiany, int& liczba_do_podmiany)
{
	if (Dziecko == nullptr || dokonano_zamiany == true)
	{
		return;
	}

	if (Dziecko->dzieci_elementu == nullptr)
	{
		liczba_do_podmiany = Dziecko->liczba;

		for (int i = 0; i < Korzen.ilosc_dzieci_wezlow; i++)
		{
			if (Rodzic->dzieci_elementu[i] == Dziecko)
			{
				Rodzic->dzieci_elementu[i] = nullptr;
				break;
			}
		}

		dokonano_zamiany = true;
		return;
	}

	bool wszystkie_dzieci_puste = true;

	for (int i = 0; i < Korzen.ilosc_dzieci_wezlow; i++)
	{
		if (Dziecko->dzieci_elementu[i] != nullptr)
		{
			wszystkie_dzieci_puste = false;
			break;
		}
	}

	if (wszystkie_dzieci_puste && dokonano_zamiany == false)
	{
		liczba_do_podmiany = Dziecko->liczba;

		for (int i = 0; i < Korzen.ilosc_dzieci_wezlow; i++)
		{
			if (Rodzic->dzieci_elementu[i] == Dziecko)
			{
				Rodzic->dzieci_elementu[i] = nullptr;
				break;
			}
		}

		dokonano_zamiany = true;
		return;
	}

	for (int i = 0; i < Korzen.ilosc_dzieci_wezlow; i++)
	{
		szukanie_kasowanie(Korzen, Dziecko, Dziecko->dzieci_elementu[i], dokonano_zamiany, liczba_do_podmiany);

		if (dokonano_zamiany == true)
		{
			return;
		}
	}


}

void znajdz_lewy_pusty_lisc_korzen(KorzenDrzewa& Korzen, ElementDrzewa* Lisc, ElementDrzewa* Rodzic, int& liczba_do_usuniecia, bool& zamieniono_liczbe, int& liczba_do_zamiany)
{
	if (Lisc == nullptr)
	{
		return;
	}

	if (zamieniono_liczbe == true)
	{
		return;
	}

	if (Lisc->dzieci_elementu != nullptr)
	{
		for (int i = 0; i < Korzen.ilosc_dzieci_wezlow; i++)
		{
			znajdz_lewy_pusty_lisc_korzen(Korzen, Lisc->dzieci_elementu[i], Lisc, liczba_do_usuniecia, zamieniono_liczbe, liczba_do_zamiany);
		}
	}

	if (zamieniono_liczbe == false)
	{
		liczba_do_zamiany = Lisc->liczba;
		zamieniono_liczbe = true;

		if (Rodzic != nullptr)
		{
			for (int i = 0; i < Korzen.ilosc_dzieci_wezlow; i++)
			{
				if (Rodzic->dzieci_elementu[i] == Lisc)
				{
					Rodzic->dzieci_elementu[i] = nullptr;
					break;
				}
			}
		}
		else
		{
			for (int i = 0; i < Korzen.rozmiar_korzenia; i++)
			{
				if (Korzen.elementy_korzenia[i] == Lisc)
				{
					Korzen.elementy_korzenia[i] = nullptr;
					break;
				}
			}
		}
	}
}
