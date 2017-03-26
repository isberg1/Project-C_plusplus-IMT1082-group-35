#if !defined(__DELTAGERE_H)
#define  __DELTAGERE_H

#include <fstream>
#include "ListTool2B.h"



class Deltagere
{
private:
	List* DeltagerListe;

public:
	~Deltagere();
	void skrivMeny();
	void menyValg();
	void nyDeltager();                              // Oppretter ny Deltager                  : Valg D N
	void endreDeltager();
	void endreDeltagerMeny();
	void skrivDataAlle();
	void skrivDataEn();
	void loopDeltagerTropp(char *n);                // Skriver ut deltagere for en nasjon.    : Valg N T
    void skrivTilFil();                             // Skriver til fil.
    void lesFraFil();                               // Leser datastruktur fra fil.
};

#endif
