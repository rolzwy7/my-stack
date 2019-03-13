/* program realizuje sortowanie bąbelkow */
#include <stdio.h>
#define MAXTAB 99
int wczytaj_liczbe(int min, int max)
{
	int liczba,
		wynik;
	do
	{
		fflush(stdout);
		fprintf(stdout, "podaj liczbe calkowita z zakresu <%d-%d>?", min, max);
		wynik = fscanf(stdin, "%d", &liczba);
	} while (wynik != 1 || liczba > max || liczba < min);
	return liczba;
}
void zamien_jezeli_wieksza(int * tab, int pos_mn, int pos_wk)
{
	int tmp;
	if (tab[pos_mn] > tab[pos_wk])
	{
		tmp = tab[pos_mn];
		tab[pos_mn] = tab[pos_wk];
		tab[pos_wk] = tmp;
	}
}
int main(int argc, char* argv[])
{
	int tablica[MAXTAB];
	int ile, i, j;
	printf("\n\nJestem program ""sortujacy\n\nile ""liczb chcesz sortowac\n");
	ile = wczytaj_liczbe(0, MAXTAB);
	for (i = 1; i <= ile; i++)
	{
		printf("Wczytuje liczbe nr. %d \n", i);
		tablica[i - 1] = wczytaj_liczbe(0, 999);
	}
	for (i = 0; i < ile; i++)
		for (j = 0; j < ile - 1; j++)
			zamien_jezeli_wieksza(tablica, j, j + 1);
	printf("\nPosortowane:");
	for (i = 0; i < ile; i++)
		printf("\nliczba nr. %d : %d", i + 1, tablica[i]);
	return 0;
}