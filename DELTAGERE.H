#if !defined(__DELTAGERE_H)
#define  __DELTAGERE_H

#include <fstream>
#include "ListTool2B.h"

class Deltagere		
{
private:
	int antDeltagere;
	List* DeltagerListe;

public:
	Deltagere();
	Deltagere(char* t);
	~Deltagere();
	void skrivMeny();
	void menyValg();
	void nyDeltager();
	void endreDeltager();
	void skrivDataAlle();
	void skrivDataEn();
	bool sjekkId(int in);
};

#endif