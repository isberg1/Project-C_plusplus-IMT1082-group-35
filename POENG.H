#if !defined(__POENG_H)
#define  __POENG_H

#include"STATISTIKK.H"
#include"ENUM.H"
#include"CONST.H"

class Poeng : public Statisikk
{
private:
	int poeng[MAXNASJONER + 1];												//array med poeng

public:
	Poeng();	//constructor												  nullstiller array
	void endreAntPoeng(char nasjon[], int antPoeng, positivNegativ posNeg);	//endrer ant poeng med +- 1
	void skrivPoeng();														//display 2 arrayer
	void testFunksjon();													//testfunksjon fjernes før siste innlevering
	void skrivTilFil();														//skriv til fil
	void lesFraFil();														//les fra fil

};
#endif