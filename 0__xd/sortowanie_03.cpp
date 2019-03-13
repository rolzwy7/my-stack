/* program realizuje sortowanie liczb */
#include <stdio.h>
#include <climits>
#define MAXTAB 99
#define MAX_INT INT_MAX
int wczytaj_liczbe(int min, int max)
{
	int liczba, wynik;
	do
	{
		wynik = printf("podaj liczbe calkowita z zakresu <%d-%d>?", min, max);
		wynik = scanf("%d", &liczba);
	} while (!(wynik == 1 && liczba <= max) || liczba < min);
	return liczba;
}
main()
{
	int tablica[MAXTAB], tablica2[MAXTAB];
	int ile, i, j, k = 0, minimum, minpos;
	fprintf(stdout, "\n\nJestem program ""sortujacy\n\nile ""liczb chcesz sortowac\n");
	ile = wczytaj_liczbe(0, MAXTAB);
	for (i = 0; i < ile; i++)
	{
		fprintf(stdout, "Wczytuje liczbe nr. %d \n", i + 1);
		tablica[i] = wczytaj_liczbe(0, 999);
	}
	for (i = 0; i < ile; i++)
	{
		minimum = MAX_INT;
		minpos = 0;
		for (j = 0; j < ile; j++)
		{
			if (tablica[j] < minimum)
			{
				minimum = tablica[j];
				minpos = j;
			}
		}
		tablica2[k++] = minimum;
		tablica[minpos] = MAX_INT;
	}
	printf("\nPosortowane:");
	i = 0;
	do {
		printf("\nliczba nr. %d : %d", i, tablica2[i++]);
	} while (i < ile);
	return 0;
}