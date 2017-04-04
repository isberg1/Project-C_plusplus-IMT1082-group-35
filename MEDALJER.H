#if !defined(__MEDALJER_H)
#define  __MEDALJER_H

#include"ENUM.H"
#include"CONST.H"
#include"STATISTIKK.H"



class Medaljer : public Statisikk
{
private:
	int medaljer[MAXNASJONER + 1];															//arry med en medaljene
public:
	Medaljer();		//constructor															  nullstiller hele arrayen 
	void endreAntMedaljer(char nasjon[], seiersType medaljeType, positivNegativ posNeg);	//endrer en nasjons medaljefordeling med +- 1
	
	void skrivMedaljer();																	//display 2 arrayer
	void testFunksjon();																	// brukes kun til testing. fjernes før siste innlevering
	void skrivTilFil();																		//skriv til fil
	void lesFraFil();																		//les fra fil
};


#endif
