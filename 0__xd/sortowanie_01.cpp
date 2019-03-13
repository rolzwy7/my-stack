#include <stdio.h>
#define MAXTAB 99
int wczytaj_liczbe(int min, int max)
{
	int liczba,
		wynik;
	do
	{
		printf("podaj liczbe calkowita z zakresu <%d-%d>?", min, max);
		wynik = scanf("%d", &liczba);
	}
	//while ( wynik !=1 || liczba > max || liczba < min);
	while (wynik != 1 || liczba >= max || liczba <= min);
	return liczba;
}
/* funkcja przesuwa zawartość tablicy <tab> od pozycji <from>
do pozycji <to > o jedną pozycję w górę */
void przesun_1_w_gore(int * tab, int from, int to)
{
	int k;
	for (k = to; !(k == from); k--) // tu !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	{
		tab[k] = tab[k - 1];
	}
}
int main()
{
	int tablica[MAXTAB], ile, i, j, min, minpos;
	printf("\n\nJestem program """"\"sortujacy\n\nile ""liczb chcesz sortowac\n");
	ile = wczytaj_liczbe(0, MAXTAB);
	for (i = 0; i < ile; i++) {
		printf("Wczytuje liczbe nr. %d \n", i + 1);
		tablica[i] = wczytaj_liczbe(0, 999);
	}
	for (i = 0; i < ile; i++)
	{
		min = tablica[i];
		minpos = i;
		for (j = i; j < ile; j++)
		{
			if (tablica[j] < min)
			{
				min = tablica[j];
				minpos = j;
			}
		}
		przesun_1_w_gore(tablica, i, minpos);
		tablica[i] = min;
	}
	printf("\nPosortowane:");
	for (i = 0; i < ile; i++)
		printf("\nliczba nr. %d : %d", i + 1, tablica[i]);
	return(0);
}