#include <iostream>
#include <algorithm>

void PostawZnakKomputer(char** tab, int rozmiar, int skreslenie);
//Rysowanie planszy
void RysujPlansze(char** tab, int rozmiar) {
	for (int i = 1; i <= rozmiar; i++) {
		for (int j = 1; j <= rozmiar; j++) {
			std::cout << " "<<tab[i-1][j-1]<<" ";
			if (j%rozmiar)
				std::cout << "|";
			else if (j == rozmiar && i!=rozmiar) {
				std::cout << std::endl;
				for(int k=0; k<rozmiar;k++)
					std::cout << "--- ";
				std::cout << std::endl;
			}
			else std::cout << std::endl;
		}
	}
}

void StworzTablice(char **tab, int rozmiar) {
	for (int i = 0; i < rozmiar; i++)
		for(int j=0; j<rozmiar; j++)
			tab[i][j] = ' ';
}

void WykonajRuch(char** tab, char& gracz, int rozmiar) {
	int wiersz, kolumna;
	std::cout << "*=======RUCH GRACZA " << gracz << "=======*" << std::endl;
	std::cout << "Wpisz nr pola, w ktorym chcesz postawic znak [nr wiersza][nr kolumny]: ";
	std::cin >> wiersz >> kolumna;
	if ((wiersz >= 1 && wiersz <= rozmiar) && (kolumna >= 1 && kolumna <= rozmiar) && tab[wiersz - 1][kolumna - 1] == ' ') tab[wiersz - 1][kolumna - 1] = gracz;
	else std::cout << "Nie mozna wykonac takiego ruchu!!!" << std::endl;
	if (gracz == 'O') gracz = 'X';
	else if (gracz == 'X') gracz = 'O';
	RysujPlansze(tab,rozmiar);
}

void WykonajRuchKomputer(char** tab, char& gracz, int rozmiar, int skreslenie) {
	int wiersz, kolumna;
	if (gracz == 'O') {
		std::cout << "*=======RUCH GRACZA " << gracz << "=======*" << std::endl;
		std::cout << "Wpisz nr pola, w ktorym chcesz postawic znak [nr wiersza][nr kolumny]: ";
		std::cin >> wiersz >> kolumna;
		if ((wiersz >= 1 && wiersz <= rozmiar) && (kolumna >= 1 && kolumna <= rozmiar) && tab[wiersz - 1][kolumna - 1] == ' ') tab[wiersz - 1][kolumna - 1] = gracz;
		else std::cout << "Nie mozna wykonac takiego ruchu!!!" << std::endl;
		
	}
	else if (gracz == 'X') {
		PostawZnakKomputer(tab, rozmiar, skreslenie);
	}
	if (gracz == 'O') gracz = 'X';
		else if (gracz == 'X') gracz = 'O';
		RysujPlansze(tab, rozmiar);
}

bool Wygrana(char** tab, char gracz, int rozmiar, int skreslenie) {
	int licznik_poziom = 0, licznik_pion = 0, licznik_skos_od_lewej_gora = 0, licznik_skos_od_lewej_dol = 0, licznik_skos_od_prawej_gora = 0, licznik_skos_od_prawej_dol=0, pom;

	//wygrana w poziomie
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++)
			if (tab[i][j] == gracz) licznik_poziom++;
			else if(tab[i][j]!=gracz && licznik_poziom<skreslenie) licznik_poziom = 0;
		if (licznik_poziom == skreslenie) return true;
		else licznik_poziom = 0;
	}
	
	//wygrana w pionie
	for (int i = 0; i < rozmiar; i++) {
		for (int j = 0; j < rozmiar; j++)
			if (tab[j][i] == gracz) licznik_pion++;
			else if (tab[j][i] != gracz && licznik_pion < skreslenie) licznik_pion = 0;
		if (licznik_pion == skreslenie) return true;
		else licznik_pion = 0;
	}
	
	//wygrana po przekatnej
	pom = rozmiar-skreslenie;
	for (int k = 0; k <= pom; k++) {
		for (int i = 0; i < rozmiar - k; i++) {
			if (tab[i][i + k] == gracz) licznik_skos_od_lewej_gora++;
			else if (tab[i][i + k] != gracz && licznik_skos_od_lewej_gora < skreslenie) licznik_skos_od_lewej_gora = 0;
			if (tab[i + k][i] == gracz) licznik_skos_od_lewej_dol++;
			else if (tab[i+k][i] != gracz && licznik_skos_od_lewej_dol < skreslenie) licznik_skos_od_lewej_dol = 0;
			if (tab[i][rozmiar - 1 - i - k] == gracz) licznik_skos_od_prawej_gora++;
			else if (tab[i][rozmiar - 1 - i - k] != gracz && licznik_skos_od_prawej_gora < skreslenie) licznik_skos_od_prawej_gora = 0;
			if (tab[i+k][rozmiar - 1 - i] == gracz) licznik_skos_od_prawej_dol++;
			else if (tab[i+k][rozmiar - 1 - i] != gracz && licznik_skos_od_prawej_dol < skreslenie) licznik_skos_od_prawej_dol = 0;
		}
		if (licznik_skos_od_lewej_gora == skreslenie) return true;
		else if (licznik_skos_od_prawej_gora == skreslenie) return true;
		else if (licznik_skos_od_lewej_dol == skreslenie) return true;
		else if (licznik_skos_od_prawej_dol == skreslenie) return true;
		else {
			licznik_skos_od_lewej_gora = 0;
			licznik_skos_od_lewej_dol = 0;
			licznik_skos_od_prawej_gora = 0;
			licznik_skos_od_prawej_dol = 0;
		}
	}
	return false;
}

bool Remis(char** tab, int rozmiar) {
	for (int i = 0; i < rozmiar; i++)
		for (int j = 0; j < rozmiar; j++)
			if (tab[i][j] == ' ') return false;
	return true;
}



int MinMax(char **tab, char gracz, int rozmiar, int skreslenie,int glebokosc)
{
	int m, minimax;

	if (Wygrana(tab, gracz, rozmiar, skreslenie)) {
		if (gracz == 'X') return 1;
		else return -1;
	}
	if (Remis(tab, rozmiar)) return 0;

	if (gracz == 'X') gracz = 'O';
	else gracz='X';

	minimax = (gracz == 'O') ? 10 : -10;
	if (glebokosc < 4) {
		for (int i = 0; i < rozmiar; i++)
			for (int j = 0; j < rozmiar; j++)
				if (tab[i][j] == ' ')
				{
					tab[i][j] = gracz;
					m = MinMax(tab, gracz, rozmiar, skreslenie, glebokosc + 1);
					tab[i][j] = ' ';
					if (((gracz == 'O') && (m < minimax)) || ((gracz == 'X') && (m > minimax))) minimax = m;
				}
	}
	return minimax;
}

void PostawZnakKomputer(char **tab, int rozmiar, int skreslenie)
{
	int ruch, ruch_pion=0, ruch_poziom=0, m, minimax;

	minimax = -10;
	for (int i = 0; i < rozmiar; i++)
		for(int j=0; j<rozmiar;j++)
		if (tab[i][j] == ' ')
		{
			tab[i][j] = 'X';
			m = MinMax(tab, 'X',rozmiar,skreslenie,0);
			tab[i][j] = ' ';
			if (m > minimax)
			{
				minimax = m; ruch_poziom = i; ruch_pion = j;
			}
		}
	tab[ruch_poziom][ruch_pion]='X';
}

int main() {
	char** tab;
	char gracz;
	int tryb, rozmiar,skreslenie;

	//Menu
	do {	
	std::cout << "Menu:\n" <<
		"1 - gra dla dwoch osob\n" <<
		"2 - gra z komputerem\n" <<
		"3 - Wyswietl menu\n" <<
		"0 - Wyjscie z gry\n";
	
		std::cin >> tryb;
		switch (tryb) {
		case 1:
			std::cout << "GRA DLA DWOCH OSOB\n";
			std::cout << "Podaj rozmiar tablicy NxN\n"; std::cin >> rozmiar;
			std::cout << "Podaj ilosc znakow, ktore daja wygrana po skresleniu:\n"; std::cin >> skreslenie;
			//Tworzenie tablicy
			tab = new char* [rozmiar];
			for (int i = 0; i < rozmiar; i++)
				tab[i] = new char[rozmiar];
			StworzTablice(tab, rozmiar);
			RysujPlansze(tab, rozmiar);
			gracz = 'O';
			do {
				WykonajRuch(tab, gracz, rozmiar);
				if (Wygrana(tab, 'X',rozmiar,skreslenie) == true) std::cout << "Wygral gracz: X" << std::endl;
				else if (Wygrana(tab, 'O',rozmiar,skreslenie) == true) std::cout << "Wygral gracz: O" << std::endl;
				else if (Remis(tab, rozmiar) == true) std::cout << "REMIS!!!" << std::endl;
			} while (!Wygrana(tab, 'X',rozmiar,skreslenie) && !Wygrana(tab, 'O',rozmiar,skreslenie) && !Remis(tab,rozmiar));
			break;
		case 2:
			std::cout << "GRA Z KOMPUTEREM\n";
			std::cout << "Podaj rozmiar tablicy NxN\n"; std::cin >> rozmiar;
			std::cout << "Podaj ilosc znakow, ktore daja wygrana po skresleniu:\n"; std::cin >> skreslenie;
			//Tworzenie tablicy
			tab = new char* [rozmiar];
			for (int i = 0; i < rozmiar; i++)
				tab[i] = new char[rozmiar];
			StworzTablice(tab, rozmiar);
			RysujPlansze(tab, rozmiar);
			gracz = 'O';
			do {
				WykonajRuchKomputer(tab, gracz, rozmiar, skreslenie);
				if (Wygrana(tab, 'X', rozmiar, skreslenie) == true) std::cout << "Wygral gracz: X" << std::endl;
				else if (Wygrana(tab, 'O', rozmiar, skreslenie) == true) std::cout << "Wygral gracz: O" << std::endl;
				else if (Remis(tab, rozmiar) == true) std::cout << "REMIS!!!" << std::endl;
			} while (!Wygrana(tab, 'X', rozmiar, skreslenie) && !Wygrana(tab, 'O', rozmiar, skreslenie) && !Remis(tab, rozmiar));
			break;
		case 3:
			std::cout << "Menu:\n" <<
				"1 - gra dla dwóch osób\n" <<
				"2 - gra z komputerem\n" <<
				"3 - Wyswietl menu\n" <<
				"x - Wyjscie z gry\n";
			break;
		case 0: break;
		default:
			std::cout << "Nie ma takiej opcji. Wybierz ponownie.\n";
			break;
		}
	} while (tryb != 0);
	
}
