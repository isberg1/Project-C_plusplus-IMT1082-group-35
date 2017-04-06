#if !defined(__POENG_H)
#define  __POENG_H

#include"STATISTIKK.H"
#include"ENUM.H"
#include"CONST.H"



class Poeng : public Statisikk
{
private:
	int poeng[MAXNASJONER + 1];												// Array med poeng.

public:
	Poeng();	                                                            // Constructor, nullstiller array.
	void endreAntPoeng(char nasjon[], int antPoeng, positivNegativ posNeg);	// Endrer ant poeng med +- 1.
	void skrivPoeng();														// Display 2 arrayer.
	void skrivTilFil();														// Skriv til fil.
	void lesFraFil();														// Les fra fil.
};


#endif
