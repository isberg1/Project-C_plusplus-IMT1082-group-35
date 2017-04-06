#if !defined(__MEDALJER_H)
#define  __MEDALJER_H

#include"ENUM.H"
#include"CONST.H"
#include"STATISTIKK.H"



class Medaljer : public Statisikk
{
private:
	int medaljer[MAXNASJONER + 1];															// Array med en medaljene.

public:
	Medaljer();		                                                                        // Constructor, nullstiller hele arrayen.
	void endreAntMedaljer(char nasjon[], seiersType medaljeType, positivNegativ posNeg);	// Endrer en nasjons medaljefordeling med +- 1.
	void skrivMedaljer();																	// Display 2 arrayer (brukes kun til testing. fjernes før siste innlevering).
	void skrivTilFil();																		// Skriv til fil.
	void lesFraFil();																		// Les fra fil.
};


#endif
