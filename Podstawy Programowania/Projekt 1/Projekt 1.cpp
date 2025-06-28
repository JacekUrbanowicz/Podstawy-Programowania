//Jacek Urbanowicz 203905 Elektronika i telekomunikacja Gra à la Kono
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>

using namespace std;

struct pionki
{
	int x;
	int y;
};

void wypisz_imie_gracza1(char imie_gracz1[20]);
void wypisz_imie_gracza2(char imie_gracz2[20]);
void start_rozgrywki(char start[6]);
void narysuj_tablice(char tab[11][11], pionki Biale[], pionki Czarne[]);
bool ruch_gracz(pionki Biale[], pionki Czarne[], char imie_gracz1[20]);
bool ruch_komputer(pionki Biale[], pionki Czarne[], char imie_gracz2[20]);
int sprawdz_wygrana(pionki Biale[], pionki Czarne[]);

int main()
{
	srand(time(NULL));
	char tab[11][11];
	pionki Biale[4];
	Biale[0].x = 3;
	Biale[0].y = 7;
	Biale[1].x = 5;
	Biale[1].y = 7;
	Biale[2].x = 7;
	Biale[2].y = 7;
	Biale[3].x = 9;
	Biale[3].y = 7;

	pionki Czarne[4];
	Czarne[0].x = 3;
	Czarne[0].y = 1;
	Czarne[1].x = 5;
	Czarne[1].y = 1;
	Czarne[2].x = 7;
	Czarne[2].y = 1;
	Czarne[3].x = 9;
	Czarne[3].y = 1;

	fstream zapisz("zapisz.txt", ios::out);

	char imie_gracz1[20];
	char imie_gracz2[20];
	double dostepny_czas = 0;

	cout << "Podaj imie pierwszego gracza: ";
	cin >> imie_gracz1;
	cout << "Podaj imie drugiego gracza: ";
	cin >> imie_gracz2;
	cout << "Podaj czas gry w sekundach: ";
	cin >> dostepny_czas;
	system("cls");
	wypisz_imie_gracza1(imie_gracz1);
	wypisz_imie_gracza2(imie_gracz2);
	narysuj_tablice(tab, Biale, Czarne);

	cout << "Aby rozpoczac zrozgrywke wpisz START" << endl;
	char start[6];
	cin >> start;
	start_rozgrywki(start);
	system("cls");

	bool czarne = false;
	bool biale = false;
	bool gra = true;
	bool gameover_c = false;
	bool gameover_b = false;
	int sprawdz = 0;
	int n = 0;

	zapisz << n << ' ';
	for (int i = 0; i < 4; i++)
	{
		zapisz << Biale[i].x << ' ' << Biale[i].y << ' ';
	}
	for (int i = 0; i < 4; i++)
	{
		zapisz << Czarne[i].x << ' ' << Czarne[i].y << ' ';
	}
	zapisz << endl;
	n++;

	double dostepny_czas_b = dostepny_czas;
	double dostepny_czas_c = dostepny_czas;
	clock_t czas_start;
	clock_t czas_stop;

	while (gra)
	{
		narysuj_tablice(tab, Biale, Czarne);
		cout << endl << dostepny_czas_b << " sekund" << endl;
		sprawdz = sprawdz_wygrana(Biale, Czarne);
		if (gameover_c == true)
		{
			cout << "Wygral ";
			wypisz_imie_gracza2(imie_gracz2);
			cout << " przez blok" << endl;
			gra = false;
			continue;
		}
		if (sprawdz == 1)
		{
			cout << "Wygral ";
			wypisz_imie_gracza1(imie_gracz1);
			cout << " przez zbicie pionkow" << endl;
			gra = false;
			continue;
		}
		else if (sprawdz == 2)
		{
			cout << "Wygral ";
			wypisz_imie_gracza2(imie_gracz2);
			cout << " przez zbicie pionkow" << endl;
			gra = false;
			continue;
		}
		czas_start = clock();
		gameover_b = ruch_komputer(Biale, Czarne, imie_gracz2);
		czas_stop = clock();
		dostepny_czas_b = dostepny_czas_b - (double(czas_stop - czas_start) / CLOCKS_PER_SEC);
		zapisz << n << ' ';
		for (int i = 0; i < 4; i++) {
			zapisz << Biale[i].x << ' ' << Biale[i].y << ' ';
		}
		for (int i = 0; i < 4; i++) {
			zapisz << Czarne[i].x << ' ' << Czarne[i].y << ' ';
		}
		zapisz << endl;
		n++;
		if (dostepny_czas_b <= 0)
		{
			cout << "Wygral ";
			wypisz_imie_gracza1(imie_gracz1);
			cout << "Przeciwnikowi ";
			wypisz_imie_gracza2(imie_gracz2);
			cout <<	"skonczyl sie czas" << endl;
			break;
		}
		system("cls");
		narysuj_tablice(tab, Biale, Czarne);
		cout << endl << dostepny_czas_c << " sekund" << endl;
		if (gameover_b == true)
		{
			cout << "Wygral ";
			wypisz_imie_gracza1(imie_gracz1);
			cout << " przez blok" << endl;
			gra = false;
			continue;
		}
		sprawdz = sprawdz_wygrana(Biale, Czarne);
		if (sprawdz == 1)
		{
			cout << "Wygral ";
			wypisz_imie_gracza1(imie_gracz1);
			cout << " przez zbicie pionkow" << endl;
			gra = false;
			continue;
		}
		else if (sprawdz == 2)
		{
			cout << "Wygral ";
			wypisz_imie_gracza2(imie_gracz2);
			cout << " przez zbicie pionkow" << endl;
			gra = false;
			continue;
		}
		czas_start = clock();
		gameover_c = ruch_gracz(Biale, Czarne, imie_gracz1);
		czas_stop = clock();
		dostepny_czas_c = dostepny_czas_c - (double(czas_stop - czas_start) / CLOCKS_PER_SEC);

		zapisz << n << ' ';
		for (int i = 0; i < 4; i++) {
			zapisz << Biale[i].x << ' ' << Biale[i].y << ' ';
		}
		for (int i = 0; i < 4; i++) {
			zapisz << Czarne[i].x << ' ' << Czarne[i].y << ' ';
		}
		zapisz << endl;
		n++;
		if (dostepny_czas_c <= 0)
		{
			cout << "Wygral ";
			wypisz_imie_gracza2(imie_gracz2);
			cout << "Przeciwnikowi ";
			wypisz_imie_gracza1(imie_gracz1);
			cout << "skonczyl sie czas" << endl;
			break;
		}
		system("cls");
	}
	zapisz.close();
	cout << "Jesli chcesz obejrzec gre wpisz TAK" << endl;
	char powtorka[4];
	cin >> powtorka;
	if (powtorka[0] == 'T' && powtorka[1] == 'A' && powtorka[2] == 'K')
	{
		pionki BialeReplay[4];
		pionki CzarneReplay[4];
		fstream zaladuj("zapisz.txt", ios::in);

		for (int j = 0; j < n; j++) {
			system("cls");
			int pomin;
			zaladuj >> pomin;
			for (int i = 0; i < 4; i++) {
				zaladuj >> BialeReplay[i].x >> BialeReplay[i].y;
			}
			for (int i = 0; i < 4; i++) {
				zaladuj >> CzarneReplay[i].x >> CzarneReplay[i].y;
			}
			narysuj_tablice(tab, BialeReplay, CzarneReplay);
			cout << "Aby kontynuowac wpisz dowolny znak. Aby zobaczyc wiecej ruchow wpisz wiecej znakow." << endl;
			char dalej;
			cin >> dalej;
		}
		zaladuj.close();
	}

	return 0;
}
void start_rozgrywki(char start[6])
{
	if (start[0] != 'S' && start[1] != 'T' && start[2] != 'A' && start[3] != 'R' && start[4] != 'T')
	{
		cout << "Nie wpisano START. Podaj imiona jeszcze raz" << endl;
		main();
		return;
	}
}

void wypisz_imie_gracza1(char imie_gracz1[20])
{
	cout << imie_gracz1 << " pionki: czarne" << endl;
}

void wypisz_imie_gracza2(char imie_gracz2[20])
{
	cout << imie_gracz2 << " pionki: biale" << endl;
}

void narysuj_tablice(char tab[11][11], pionki Biale[], pionki Czarne[])
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (i % 2 == 0 && j % 2 == 1)
			{
				tab[i][j] = 205;
			}
			else if (i % 2 == 1 && j % 2 == 0)
			{
				tab[i][j] = 186;
			}
			else if (i == 0 && j == 0)
			{
				tab[i][j] = 201;
			}
			else if (i == 0 && j == 10)
			{
				tab[i][j] = 187;
			}
			else if (i == 10 && j == 0)
			{
				tab[i][j] = 200;
			}
			else if (i == 10 && j == 10)
			{
				tab[i][j] = 188;
			}
			else if ((i == 0) && (j % 2 == 0) && (j != 0 != 10))
			{
				tab[i][j] = 203;
			}
			else if ((i % 2 == 0) && (i != 0 != 10) && (j == 0))
			{
				tab[i][j] = 204;
			}
			else if ((i % 2 == 0) && (i != 0 != 10) && (j == 10))
			{
				tab[i][j] = 185;
			}
			else if ((i == 10) && (j % 2 == 0) && (j != 0 != 10))
			{
				tab[i][j] = 202;
			}
			else if ((i % 2 == 0) && (i != 0 != 10) && (j % 2 == 0) && (j != 0 != 10))
			{
				tab[i][j] = 206;
			}
			else if (i == 1 && j == 1)
			{
				tab[i][j] = '4';
			}
			else if (i == 3 && j == 1)
			{
				tab[i][j] = '3';
			}
			else if (i == 5 && j == 1)
			{
				tab[i][j] = '2';
			}
			else if (i == 7 && j == 1)
			{
				tab[i][j] = '1';
			}
			else if (i == 9 && j == 3)
			{
				tab[i][j] = 'A';
			}
			else if (i == 9 && j == 5)
			{
				tab[i][j] = 'B';
			}
			else if (i == 9 && j == 7)
			{
				tab[i][j] = 'C';
			}
			else if (i == 9 && j == 9)
			{
				tab[i][j] = 'D';
			}
			else
			{
				tab[i][j] = ' ';
			}
		}
	}

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{

			for (int a = 0; a < 4; a++)
			{
				if (Czarne[a].x == 0 && Czarne[a].y == 0)
				{
					continue;
				}
				else
				{
					if (Czarne[a].x == j && Czarne[a].y == i)
					{
						tab[i][j] = 'c';
					}
				}
			}
			for (int a = 0; a < 4; a++)
			{

				if (Biale[a].x == 0 && Biale[a].y == 0)
				{
					continue;
				}
				else
				{
					if (Biale[a].x == j && Biale[a].y == i)
					{
						tab[i][j] = 'b';
					}
				}
			}
		}
	}

	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			cout << tab[i][j];
		}
		cout << endl;
	}

}

bool ruch_gracz(pionki Biale[], pionki Czarne[], char imie_gracz1[20])
{
	bool gameover = false;
	int x_test_wygrana;
	int y_test_wygrana;
	int koniec = 0;

	for (int j = 0; j < 4; j++)
	{

		x_test_wygrana = Czarne[j].x;
		y_test_wygrana = Czarne[j].y;
		if (x_test_wygrana == 0 && y_test_wygrana == 0)
		{
			koniec++;
		}
		else
		{


			if (((y_test_wygrana == 1) || (y_test_wygrana == 7)) && ((x_test_wygrana != 3) && (x_test_wygrana != 9)) ||
				((x_test_wygrana == 3) || (x_test_wygrana == 9)) && ((y_test_wygrana != 1) && (x_test_wygrana != 7)))
			{
				int sasiedzi3 = 0;
				for (int i = 0; i < 4; i++)
				{
					if ((Czarne[i].x - 2 == x_test_wygrana && Czarne[i].y == y_test_wygrana) || (Biale[i].x - 2 == x_test_wygrana && Biale[i].y == y_test_wygrana))
					{
						sasiedzi3++;
					}
					if ((Czarne[i].x + 2 == x_test_wygrana && Czarne[i].y == y_test_wygrana) || (Biale[i].x + 2 == x_test_wygrana && Biale[i].y == y_test_wygrana))
					{
						sasiedzi3++;
					}
					if ((Czarne[i].x == x_test_wygrana && Czarne[i].y - 2 == y_test_wygrana) || (Biale[i].x == x_test_wygrana && Biale[i].y - 2 == y_test_wygrana))
					{
						sasiedzi3++;
					}
					if ((Czarne[i].x == x_test_wygrana && Czarne[i].y + 2 == y_test_wygrana) || (Biale[i].x == x_test_wygrana && Biale[i].y + 2 == y_test_wygrana))
					{
						sasiedzi3++;
					}
				}
				if (sasiedzi3 == 3)
				{
					koniec++;
				}
			}
			if (((y_test_wygrana == 3) || (y_test_wygrana == 5)) && ((x_test_wygrana == 5) || (x_test_wygrana == 7)))
			{
				int sasiedzi4 = 0;
				for (int i = 0; i < 4; i++)
				{
					if ((Czarne[i].x - 2 == x_test_wygrana && Czarne[i].y == y_test_wygrana) || (Biale[i].x - 2 == x_test_wygrana && Biale[i].y == y_test_wygrana))
					{
						sasiedzi4++;
					}
					if ((Czarne[i].x + 2 == x_test_wygrana && Czarne[i].y == y_test_wygrana) || (Biale[i].x + 2 == x_test_wygrana && Biale[i].y == y_test_wygrana))
					{
						sasiedzi4++;
					}
					if ((Czarne[i].x == x_test_wygrana && Czarne[i].y - 2 == y_test_wygrana) || (Biale[i].x == x_test_wygrana && Biale[i].y - 2 == y_test_wygrana))
					{
						sasiedzi4++;
					}
					if ((Czarne[i].x == x_test_wygrana && Czarne[i].y + 2 == y_test_wygrana) || (Biale[i].x == x_test_wygrana && Biale[i].y + 2 == y_test_wygrana))
					{
						sasiedzi4++;
					}
				}
				if (sasiedzi4 == 4)
				{
					koniec++;
				}
			}
			if (((y_test_wygrana == 1) || (y_test_wygrana == 7)) && ((x_test_wygrana == 3) || (x_test_wygrana == 9)))
			{
				int sasiedzi2 = 0;
				for (int i = 0; i < 4; i++)
				{
					if ((Czarne[i].x - 2 == x_test_wygrana && Czarne[i].y == y_test_wygrana) || (Biale[i].x - 2 == x_test_wygrana && Biale[i].y == y_test_wygrana))
					{
						sasiedzi2++;
					}
					if ((Czarne[i].x + 2 == x_test_wygrana && Czarne[i].y == y_test_wygrana) || (Biale[i].x + 2 == x_test_wygrana && Biale[i].y == y_test_wygrana))
					{
						sasiedzi2++;
					}
					if ((Czarne[i].x == x_test_wygrana && Czarne[i].y - 2 == y_test_wygrana) || (Biale[i].x == x_test_wygrana && Biale[i].y - 2 == y_test_wygrana))
					{
						sasiedzi2++;
					}
					if ((Czarne[i].x == x_test_wygrana && Czarne[i].y + 2 == y_test_wygrana) || (Biale[i].x == x_test_wygrana && Biale[i].y + 2 == y_test_wygrana))
					{
						sasiedzi2++;
					}
				}
				if (sasiedzi2 == 2)
				{
					koniec++;
				}
			}
		}
	}

	if (koniec == 4)
	{
		gameover = true;
		return gameover;
	}

	cout << "Aktualnie gra ";
	wypisz_imie_gracza1(imie_gracz1);
	cout << "Chcesz zbic TAK/NIE" << endl;
	char chce[15];
	cin >> chce;
	if (chce[0] == 'T' && chce[1] == 'A' && chce[2] == 'K')
	{
		cout << "Podaj ruch czarnego w formacie A1-A3:A4" << endl;
		char ruch_bicie[9];
		cin >> ruch_bicie;
		int X1B, Y1B, X2B, Y2B, X3B, Y3B;

		if (ruch_bicie[0] != 'A' && ruch_bicie[0] != 'B' && ruch_bicie[0] != 'C' && ruch_bicie[0] != 'D')
		{
			cout << "Podane zle dane. Sproboj jeszcze raz" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}
		if (ruch_bicie[1] != '1' && ruch_bicie[1] != '2' && ruch_bicie[1] != '3' && ruch_bicie[1] != '4')
		{
			cout << "Podane zle dane. Sproboj jeszcze raz" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}
		if (ruch_bicie[2] != '-')
		{
			cout << "Podane zle dane. Sproboj jeszcze raz" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}
		if (ruch_bicie[3] != 'A' && ruch_bicie[3] != 'B' && ruch_bicie[3] != 'C' && ruch_bicie[3] != 'D')
		{
			cout << "Podane zle dane. Sproboj jeszcze raz" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}
		if (ruch_bicie[4] != '1' && ruch_bicie[4] != '2' && ruch_bicie[4] != '3' && ruch_bicie[4] != '4')
		{
			cout << "Podane zle dane. Sproboj jeszcze raz" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}

		if (ruch_bicie[5] != ':')
		{
			cout << "Podane zle dane. Sproboj jeszcze raz" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}
		if (ruch_bicie[6] != 'A' && ruch_bicie[6] != 'B' && ruch_bicie[6] != 'C' && ruch_bicie[6] != 'D')
		{
			cout << "Podane zle dane. Sproboj jeszcze raz" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}
		if (ruch_bicie[7] != '1' && ruch_bicie[7] != '2' && ruch_bicie[7] != '3' && ruch_bicie[7] != '4')
		{
			cout << "Podane zle dane. Sproboj jeszcze raz" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}

		if (ruch_bicie[0] == 'A')
		{
			X1B = 3;
		}
		else if (ruch_bicie[0] == 'B')
		{
			X1B = 5;
		}
		else if (ruch_bicie[0] == 'C')
		{
			X1B = 7;
		}
		else if (ruch_bicie[0] == 'D')
		{
			X1B = 9;
		}

		if (ruch_bicie[1] == '1')
		{
			Y1B = 7;
		}
		else if (ruch_bicie[1] == '2')
		{
			Y1B = 5;
		}
		else if (ruch_bicie[1] == '3')
		{
			Y1B = 3;
		}
		else if (ruch_bicie[1] == '4')
		{
			Y1B = 1;
		}

		if (ruch_bicie[3] == 'A')
		{
			X2B = 3;
		}
		else if (ruch_bicie[3] == 'B')
		{
			X2B = 5;
		}
		else if (ruch_bicie[3] == 'C')
		{
			X2B = 7;
		}
		else if (ruch_bicie[3] == 'D')
		{
			X2B = 9;
		}

		if (ruch_bicie[4] == '1')
		{
			Y2B = 7;
		}
		else if (ruch_bicie[4] == '2')
		{
			Y2B = 5;
		}
		else if (ruch_bicie[4] == '3')
		{
			Y2B = 3;
		}
		else if (ruch_bicie[4] == '4')
		{
			Y2B = 1;
		}

		if (ruch_bicie[6] == 'A')
		{
			X3B = 3;
		}
		else if (ruch_bicie[6] == 'B')
		{
			X3B = 5;
		}
		else if (ruch_bicie[6] == 'C')
		{
			X3B = 7;
		}
		else if (ruch_bicie[6] == 'D')
		{
			X3B = 9;
		}

		if (ruch_bicie[7] == '1')
		{
			Y3B = 7;
		}
		else if (ruch_bicie[7] == '2')
		{
			Y3B = 5;
		}
		else if (ruch_bicie[7] == '3')
		{
			Y3B = 3;
		}
		else if (ruch_bicie[7] == '4')
		{
			Y3B = 1;
		}

		int test_pionka_xB = X1B;
		int test_pionka_yB = Y1B;
		bool oszustwo = false;

		for (int i = 0; i < 4; i++)
		{
			if ((Czarne[i].x == test_pionka_xB && Czarne[i].y == Y1B) || (Czarne[i].y == test_pionka_yB && Czarne[i].x == X1B))
			{
				oszustwo = true;
			}

		}
		if (oszustwo == false)
		{
			oszustwo = true;
			cout << "Nie ma pionka na wybranym polu" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}

		int test_x = (X1B + X2B) / 2;
		int test_y = (Y1B + Y2B) / 2;
		bool skok = false;

		for (int i = 0; i < 4; i++)
		{
			if ((Czarne[i].x == test_x && Czarne[i].y == Y2B) || (Czarne[i].y == test_y && Czarne[i].x == X2B))
			{
				skok = true;
			}

		}
		if (skok == false)
		{
			skok = true;
			cout << "Nie ma pionka do przeskoczenia" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}

		for (int i = 0; i < 4; i++)
		{
			if (X2B == Czarne[i].x && Y2B == Czarne[i].y) {
				cout << "Nie ma pustego pola" << endl;
				gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
				return gameover;
			}
			if (X2B == Biale[i].x && Y2B == Biale[i].y) {
				cout << "Nie ma pustego pola" << endl;
				gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
				return gameover;
			}
		}

		if ((((X1B - X3B == 6) || (X1B - X3B == -6)) && Y1B == Y3B) || (X1B == X3B && ((Y1B - Y3B == -6) || (Y1B - Y3B == 6))))
		{

		}
		else
		{
			cout << "Ruch niedozowlony" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}

		bool bicie = false;

		for (int i = 0; i < 4; i++)
		{
			if (Biale[i].x == X3B && Biale[i].y == Y3B)
			{
				bicie = true;
			}
		}

		if (bicie == false)
		{
			cout << "Nie ma pionka bialego do zbicia" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}

		for (int i = 0; i < 4; i++)
		{
			if (Biale[i].x == X3B && Biale[i].y == Y3B)
			{
				Biale[i].x = 0;
				Biale[i].y = 0;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (Czarne[i].x == X1B && Czarne[i].y == Y1B)
			{
				Czarne[i].x = X3B;
				Czarne[i].y = Y3B;
			}
		}

	}
	else if (chce[0] == 'N' && chce[1] == 'I' && chce[2] == 'E')
	{
		cout << "Podaj ruch czarnego w formacie A1-C3" << endl;
		char ruch[8];
		cin >> ruch;
		int X1, Y1, X2, Y2;

		if (ruch[0] != 'A' && ruch[0] != 'B' && ruch[0] != 'C' && ruch[0] != 'D')
		{
			cout << "Podane zle dane. Sproboj jeszcze raz" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}
		if (ruch[1] != '1' && ruch[1] != '2' && ruch[1] != '3' && ruch[1] != '4')
		{
			cout << "Podane zle dane. Sproboj jeszcze raz" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}
		if (ruch[2] != '-')
		{
			cout << "Podane zle dane. Sproboj jeszcze raz" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}
		if (ruch[3] != 'A' && ruch[3] != 'B' && ruch[3] != 'C' && ruch[3] != 'D')
		{
			cout << "Podane zle dane. Sproboj jeszcze raz" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}
		if (ruch[4] != '1' && ruch[4] != '2' && ruch[4] != '3' && ruch[4] != '4')
		{
			cout << "Podane zle dane. Sproboj jeszcze raz" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}

		if (ruch[0] == 'A')
		{
			X1 = 3;
		}
		else if (ruch[0] == 'B')
		{
			X1 = 5;
		}
		else if (ruch[0] == 'C')
		{
			X1 = 7;
		}
		else if (ruch[0] == 'D')
		{
			X1 = 9;
		}

		if (ruch[1] == '1')
		{
			Y1 = 7;
		}
		else if (ruch[1] == '2')
		{
			Y1 = 5;
		}
		else if (ruch[1] == '3')
		{
			Y1 = 3;
		}
		else if (ruch[1] == '4')
		{
			Y1 = 1;
		}

		if (ruch[3] == 'A')
		{
			X2 = 3;
		}
		else if (ruch[3] == 'B')
		{
			X2 = 5;
		}
		else if (ruch[3] == 'C')
		{
			X2 = 7;
		}
		else if (ruch[3] == 'D')
		{
			X2 = 9;
		}

		if (ruch[4] == '1')
		{
			Y2 = 7;
		}
		else if (ruch[4] == '2')
		{
			Y2 = 5;
		}
		else if (ruch[4] == '3')
		{
			Y2 = 3;
		}
		else if (ruch[4] == '4')
		{
			Y2 = 1;
		}

		int test_pionka_x = X1;
		int test_pionka_y = Y1;
		bool oszustwo = false;

		for (int i = 0; i < 4; i++)
		{
			if ((Czarne[i].x == test_pionka_x && Czarne[i].y == Y1) || (Czarne[i].y == test_pionka_y && Czarne[i].x == X1))
			{
				oszustwo = true;
			}

		}
		if (oszustwo == false)
		{
			oszustwo = true;
			cout << "Nie ma pionka na wybranym polu" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}

		for (int i = 0; i < 4; i++) {
			if ((Biale[i].x == X2 && Biale[i].y == Y2) || (Czarne[i].x == X2 && Czarne[i].y == Y2)) {
				cout << "Pionki pokrywaja sie" << endl;
				gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
				return gameover;
			}
		}

		if ((((X1 - X2 == 2) || (X1 - X2 == -2)) && Y1 == Y2) || (X1 == X2 && ((Y1 - Y2 == -2) || (Y1 - Y2 == 2))))
		{

		}
		else
		{
			cout << "Ruch niedozowlony" << endl;
			gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
			return gameover;
		}

		for (int i = 0; i < 4; i++)
		{
			if (Czarne[i].x == X1 && Czarne[i].y == Y1)
			{
				Czarne[i].x = X2;
				Czarne[i].y = Y2;
			}
		}
	}
	else
	{
		cout << "Podane zle dane sproboj jeszcze raz" << endl;
		gameover = ruch_gracz(Biale, Czarne, imie_gracz1);
		return gameover;
	}

	return gameover;
}
bool ruch_komputer(pionki Biale[], pionki Czarne[], char imie_gracz2[20])
{
	bool gameover = false;
	int x_test_wygrana;
	int y_test_wygrana;
	int koniec = 0;

	for (int j = 0; j < 4; j++)
	{
		x_test_wygrana = Biale[j].x;
		y_test_wygrana = Biale[j].y;
		if (x_test_wygrana == 0 && y_test_wygrana == 0)
		{
			koniec++;
		}
		else
		{
			if (((y_test_wygrana == 1) || (y_test_wygrana == 7)) && ((x_test_wygrana != 3) && (x_test_wygrana != 9)) ||
				((x_test_wygrana == 3) || (x_test_wygrana == 9)) && ((y_test_wygrana != 1) && (x_test_wygrana != 7)))
			{
				int sasiedzi3 = 0;
				for (int i = 0; i < 4; i++)
				{
					if ((Czarne[i].x - 2 == x_test_wygrana && Czarne[i].y == y_test_wygrana) || (Biale[i].x - 2 == x_test_wygrana && Biale[i].y == y_test_wygrana))
					{
						sasiedzi3++;
					}
					if ((Czarne[i].x + 2 == x_test_wygrana && Czarne[i].y == y_test_wygrana) || (Biale[i].x + 2 == x_test_wygrana && Biale[i].y == y_test_wygrana))
					{
						sasiedzi3++;
					}
					if ((Czarne[i].x == x_test_wygrana && Czarne[i].y - 2 == y_test_wygrana) || (Biale[i].x == x_test_wygrana && Biale[i].y - 2 == y_test_wygrana))
					{
						sasiedzi3++;
					}
					if ((Czarne[i].x == x_test_wygrana && Czarne[i].y + 2 == y_test_wygrana) || (Biale[i].x == x_test_wygrana && Biale[i].y + 2 == y_test_wygrana))
					{
						sasiedzi3++;
					}
				}
				if (sasiedzi3 == 3)
				{
					koniec++;
				}
			}

			if (((y_test_wygrana == 3) || (y_test_wygrana == 5)) && ((x_test_wygrana == 5) || (x_test_wygrana == 7)))
			{
				int sasiedzi4 = 0;
				for (int i = 0; i < 4; i++)
				{
					if ((Czarne[i].x - 2 == x_test_wygrana && Czarne[i].y == y_test_wygrana) || (Biale[i].x - 2 == x_test_wygrana && Biale[i].y == y_test_wygrana))
					{
						sasiedzi4++;
					}
					if ((Czarne[i].x + 2 == x_test_wygrana && Czarne[i].y == y_test_wygrana) || (Biale[i].x + 2 == x_test_wygrana && Biale[i].y == y_test_wygrana))
					{
						sasiedzi4++;
					}
					if ((Czarne[i].x == x_test_wygrana && Czarne[i].y - 2 == y_test_wygrana) || (Biale[i].x == x_test_wygrana && Biale[i].y - 2 == y_test_wygrana))
					{
						sasiedzi4++;
					}
					if ((Czarne[i].x == x_test_wygrana && Czarne[i].y + 2 == y_test_wygrana) || (Biale[i].x == x_test_wygrana && Biale[i].y + 2 == y_test_wygrana))
					{
						sasiedzi4++;
					}
				}
				if (sasiedzi4 == 4)
				{
					koniec++;
				}
			}

			if (((y_test_wygrana == 1) || (y_test_wygrana == 7)) && ((x_test_wygrana == 3) || (x_test_wygrana == 9)))
			{
				int sasiedzi2 = 0;
				for (int i = 0; i < 4; i++)
				{
					if ((Czarne[i].x - 2 == x_test_wygrana && Czarne[i].y == y_test_wygrana) || (Biale[i].x - 2 == x_test_wygrana && Biale[i].y == y_test_wygrana))
					{
						sasiedzi2++;
					}
					if ((Czarne[i].x + 2 == x_test_wygrana && Czarne[i].y == y_test_wygrana) || (Biale[i].x + 2 == x_test_wygrana && Biale[i].y == y_test_wygrana))
					{
						sasiedzi2++;
					}
					if ((Czarne[i].x == x_test_wygrana && Czarne[i].y - 2 == y_test_wygrana) || (Biale[i].x == x_test_wygrana && Biale[i].y - 2 == y_test_wygrana))
					{
						sasiedzi2++;
					}
					if ((Czarne[i].x == x_test_wygrana && Czarne[i].y + 2 == y_test_wygrana) || (Biale[i].x == x_test_wygrana && Biale[i].y + 2 == y_test_wygrana))
					{
						sasiedzi2++;
					}
				}
				if (sasiedzi2 == 2)
				{
					koniec++;
				}
			}
		}
	}

	if (koniec == 4)
	{
		gameover = true;
		return gameover;
	}

	int x_test;
	int y_test;
	bool strzal = false;
	for (int i = 0; i < 4; i++)
	{
		x_test = Biale[i].x;
		y_test = Biale[i].y;
		for (int b = 0; b < 4; b++)
		{
			if (Biale[b].x == x_test && Biale[b].y == y_test)
			{
				continue;
			}
			else
			{
				if (Biale[b].x == x_test - 2 && Biale[b].y == y_test)
				{
					int A = 0;
					for (int s = 0; s < 4; s++) {
						if ((Biale[s].x == x_test - 4 && Biale[s].y == y_test) || (Czarne[s].x == x_test - 4 && Czarne[s].y == y_test))
						{
							A++;
						}
					}
					if (A == 0)
					{
						for (int c = 0; c < 4; c++)
						{
							if (Czarne[c].x == x_test - 6 && Czarne[c].y == y_test)
							{
								strzal = true;
								Biale[i].x = Czarne[c].x;
								Biale[i].y = Czarne[c].y;
								Czarne[c].x = 0;
								Czarne[c].y = 0;
							}
						}
					}
				}

				if (Biale[b].x == x_test + 2 && Biale[b].y == y_test)
				{
					int B = 0;
					for (int s = 0; s < 4; s++) {
						if ((Biale[s].x == x_test + 4 && Biale[s].y == y_test) || (Czarne[s].x == x_test + 4 && Czarne[s].y == y_test))
						{
							B++;
						}
					}
					if (B == 0)
					{
						for (int c = 0; c < 4; c++)
						{
							if (Czarne[c].x == x_test + 6 && Czarne[c].y == y_test)
							{
								strzal = true;
								Biale[i].x = Czarne[c].x;
								Biale[i].y = Czarne[c].y;
								Czarne[c].x = 0;
								Czarne[c].y = 0;
							}
						}
					}
				}

				if (Biale[b].x == x_test && Biale[b].y == y_test - 2) {
					int C = 0;
					for (int s = 0; s < 4; s++) {
						if ((Biale[s].x == x_test && Biale[s].y == y_test - 4) || (Czarne[s].x == x_test && Czarne[s].y == y_test - 4))
						{
							C++;
						}
					}
					if (C == 0)
					{
						for (int c = 0; c < 4; c++)
						{
							if (Czarne[c].x == x_test && Czarne[c].y == y_test - 6)
							{
								strzal = true;
								Biale[i].x = Czarne[c].x;
								Biale[i].y = Czarne[c].y;
								Czarne[c].x = 0;
								Czarne[c].y = 0;
							}
						}
					}
				}

				if (Biale[b].x == x_test && Biale[b].y == y_test + 2) {
					int D = 0;
					for (int s = 0; s < 4; s++) {
						if ((Biale[s].x == x_test && Biale[s].y == y_test + 4) || (Czarne[s].x == x_test && Czarne[s].y == y_test + 4))
						{
							D++;
						}
					}
					if (D == 0)
					{
						for (int c = 0; c < 4; c++)
						{
							if (Czarne[c].x == x_test && Czarne[c].y == y_test + 6)
							{
								strzal = true;
								Biale[i].x = Czarne[c].x;
								Biale[i].y = Czarne[c].y;
								Czarne[c].x = 0;
								Czarne[c].y = 0;
							}
						}
					}
				}
			}
		}
	}

	int wybor_pionka = 0;
	int kierunek_ruchux = 0;
	int kierunek_ruchuy = 0;
	wybor_pionka = rand() % 4;
	kierunek_ruchux = rand() % 4;
	kierunek_ruchuy = rand() % 4;

	if (strzal == false)
	{
		Biale[wybor_pionka];
		int X, Y;
		if (kierunek_ruchux == 0)
		{
			X = 3;
		}
		else if (kierunek_ruchux == 1)
		{
			X = 5;
		}
		else if (kierunek_ruchux == 2)
		{
			X = 7;
		}
		else if (kierunek_ruchux == 3)
		{
			X = 9;
		}

		if (kierunek_ruchuy == 0)
		{
			Y = 7;
		}
		else if (kierunek_ruchuy == 1)
		{
			Y = 5;
		}
		else if (kierunek_ruchuy == 2)
		{
			Y = 3;
		}
		else if (kierunek_ruchuy == 3)
		{
			Y = 1;
		}

		for (int i = 0; i < 4; i++) {
			if ((Biale[i].x == X && Biale[i].y == Y) || (Czarne[i].x == X && Czarne[i].y == Y)) {
				gameover = ruch_komputer(Biale, Czarne, imie_gracz2);
				return gameover;
			}
		}

		if ((((Biale[wybor_pionka].x - X == 2) || (Biale[wybor_pionka].x - X == -2)) && Biale[wybor_pionka].y == Y) || (Biale[wybor_pionka].x == X && ((Biale[wybor_pionka].y - Y == -2) || (Biale[wybor_pionka].y - Y == 2))))
		{

		}
		else
		{
			gameover = ruch_komputer(Biale, Czarne, imie_gracz2);
			return gameover;
		}

		Biale[wybor_pionka].x = X;
		Biale[wybor_pionka].y = Y;
	}

	cout << "Aktualnie gra ";
	wypisz_imie_gracza2(imie_gracz2);

	clock_t czas_mierzenia;
	czas_mierzenia = clock();
	double minimalny_czas = 4.4 * CLOCKS_PER_SEC;
	double czas_ruchu = 0.0;
	while (minimalny_czas > czas_ruchu)
	{
		czas_ruchu = (clock() - czas_mierzenia);
	}

	return gameover;
}

int sprawdz_wygrana(pionki Biale[], pionki Czarne[])
{
	int A = 4;
	for (int i = 0; i < 4; i++)
	{
		if (Biale[i].x == 0 && Biale[i].y == 0)
		{
			A--;
		}
	}
	int B = 4;
	for (int i = 0; i < 4; i++)
	{
		if (Czarne[i].x == 0 && Czarne[i].y == 0)
		{
			B--;
		}
	}
	if (A == 0)
	{
		return 1;
	}
	else if (B == 0)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}
