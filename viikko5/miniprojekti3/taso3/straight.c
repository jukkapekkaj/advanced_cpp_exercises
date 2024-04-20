/*

  Harjoitus 3

  Optimoi suorien tunnistus. Älä muuta kääntäjäoptioita.
  Pidä ohjelma yksisäikeisenä.

  Vertaa alkuperäistä ja optimoitua versiota:

  - kuinka paljon enemmän muistia optimoitu versio kuluttaa?
  - kuinka paljon nopeammin optimoitu versio toimii?

  Käännös: gcc straight.c -o straight

*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

inline int is_straight(int *k);
inline int is_quadsorfullhouse(int* k);

// Ohjelma käyttää muistia enemmän. 65536 * 2B =  131072B = 128KB. Koodista luotu .exe tiedoston koko ei kasvanut. 
// Samassa kansiossa sijaitseva .ilk (Incremental Linker File) tiedoston koko taas kasvoi noin 120KB?
// Suoritus aika oli huomattavasti nopeampi 5.8s, edellisen ratkaisun aika oli 40s
short table[65536] = { 0 };


int main()
{
	for (int i = 0; i < 12; i++) {
		for (int j = i + 1; j < 13; j++) {
			short hand = 0;
			hand |= 1 << i;
			hand |= 1 << j;
			table[hand] = 1;
		}
	}

  /*

    Käydään läpi kaikki viiden kortin permutaatiot, ja lasketaan
    kuin monta suoraa (värisuoraa tai tavallista) löytyy.

    Ks. Wikipedia http://en.wikipedia.org/wiki/Poker_probability :

    Royal flush     4      combinations
    Straight flush  36     combinations
    Straight        10,200 combinations

    Koska 5 korttia voi olla 5 x 4 x 3 x 2 x 1 = 120 järjestyksessä,
    pitäisi suoria löytyä (10200 + 36 + 4) x 120 = 1228800 kappaletta. 

  */
  int k0, k1, k2, k3, k4; /* Pakan kortit, 0..51*/
  int k[5]; /* Korttien numeroarvot, 2..14*/
  int suoria; /* Suorien lkm*/
  clock_t t1, t2;

  t1 = clock();
  suoria = 0;
  for (k0 = 0; k0 < 52; ++k0) {
  for (k1 = 0; k1 < 52; ++k1) { if (k1==k0)continue;
  for (k2 = 0; k2 < 52; ++k2) { if (k2==k0||k2==k1)continue;
  for (k3 = 0; k3 < 52; ++k3) { if (k3==k0||k3==k1||k3==k2)continue;
  for (k4 = 0; k4 < 52; ++k4) { if (k4==k0||k4==k1||k4==k2||k4==k3)continue;

	    /*
	      Lasketaan korttien numeroarvot ja
	      tarkistetaan onko suora.
	    */
	    k[0] = (k0 % 13) + 2;
	    k[1] = (k1 % 13) + 2;
	    k[2] = (k2 % 13) + 2;
	    k[3] = (k3 % 13) + 2;
	    k[4] = (k4 % 13) + 2;
	    if (is_quadsorfullhouse(k))
	      ++suoria;
	  }}}}}
  t2 = clock();
  // Nelosia ja täyskäsiä yhteensä: (624 + 3744) * 120 = 524160
  printf("Taysikasi/neloset     : %d kpl (oikea arvo 524160)\n", suoria);
  printf("Aikaa kului: %.1fs\n", (t2 - t1) / (float)CLOCKS_PER_SEC);
 
  return 0;
}


int comp(const int* n1, const int* n2) {
	return *n1 - *n2;
}

/*
  Parametrina 5 pelikortin numeroarvoa k, 2..14 (ei välttämättä
  numerojärjesteyksessä).

  Palauttaa 1, jos numeroarvot voidaan järjestää siten, että
  ne muodostavat suoran (esim. 4,5,6,7,8).

  Huom! Ässää (arvo 14) voidaan käyttää suorissa myös arvona 1
  (esim. 1,2,3,4,5).
*/
inline int is_straight(int *k)
{
  // TODO
	short hand = 0;
#if 0
	// loopin kanssa suoritusaika 6.7s
	for (int i = 0; i < 5; i++, k++) {
		hand |= 1 << (*k - 2);
	}
#else // Suoritusaika 5.8s
	hand |= 1 << (*k++ - 2);
	hand |= 1 << (*k++ - 2);
	hand |= 1 << (*k++ - 2); 
	hand |= 1 << (*k++ - 2);
	hand |= 1 << (*k - 2);
#endif
	
	return table[hand];

}

inline int is_quadsorfullhouse(int* k) {
#if 0
	qsort(k, 5, sizeof(*k), comp);
	// Check for fullhouse
	if (k[0] == k[1] && 
		k[2] == k[3] && 
		k[2] == k[4]) {
		return 1;
	}
	else if (k[0] == k[1] && 
			 k[0] == k[2] && 
			 k[3] == k[4]) {
		return 1;
	}
	else if (k[0] == k[1] && k[0] == k[2] && k[0] == k[3]) {
		return 1;
	}
	else if (k[1] == k[2] && k[1] == k[3] && k[1] == k[4]) {
		return 1;
	}

	return 0;

#else
	short hand = 0;
	hand |= 1 << (*k++ - 2);
	hand |= 1 << (*k++ - 2);
	hand |= 1 << (*k++ - 2);
	hand |= 1 << (*k++ - 2);
	hand |= 1 << (*k - 2);
	return table[hand];
#endif
}


