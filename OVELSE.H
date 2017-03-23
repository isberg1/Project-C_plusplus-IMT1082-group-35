//OVELSE.H alex
#if !defined(__OVELSE_H)
#define  __OVELSE_H

#include"ListTool2B.h"
#include"FUNKSJONER.H"

class Ovelse 
{
private:
	int nr;
	char *navn;
	int antDeltagere;
	int dato;
	int klokkeslett;
	//deltager array
	//resultat array
public:
	~Ovelse();
	void skrivMeny();
	void skrivData();
	void skrivTilFil(ofstream & ut);
	void lesFraFil(ifstream & inn);
};



#endif
