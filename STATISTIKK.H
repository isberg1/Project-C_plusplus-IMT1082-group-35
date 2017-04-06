#if !defined(__STATISTIKK_H)
#define  __STATISTIKK_H

#include"CONST.H"
#include"FUNKSJONER.H"


class Statisikk
{
protected:
	int sistebrukt;											// Teller.
	char nasjonsForkort[MAXNASJONER + 1][NASJONLEN +1];		// Array med nasjonsforkortelser.

public:
	Statisikk();											// Constructor, nullstiller array.
	void sorter1(int array[]);								// Sorterer nasjonsForkort array og en medsendt int array.
	void omsorter(int teller, int array[]);					// Omsorterer nasjonsForkort array og en medsendt int array.
};
// Ny nasjon kommer fra poeng eller medalje
// All validering av riktig nasjon skjer i OvelseObj.


#endif
