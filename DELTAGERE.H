#if !defined(__DELTAGERE_H)
#define  __DELTAGERE_H

#include <fstream>
#include "ListTool2B.h"

class Deltagere
{
private:
	int antDeltagere;                               // Trenger ikke - Bruker ikke array
	List* DeltagerListe;

public:
	Deltagere();                                    // Trenger ikke constructor her
	Deltagere(char* t);                             // Trenger ikke constructor her
	~Deltagere();
	void skrivMeny();
	void menyValg();
	void nyDeltager();                              // Oppretter ny Deltager                  : Valg D N
	void endreDeltager();
	void skrivDataAlle();
	void skrivDataEn();
	bool sjekkId(int in);
	void loopDeltagerTropp(char *n);                // Skriver ut deltagere for en nasjon.    : Valg N T
    void skrivTilFil();                             // Skriver til fil.
    void lesFraFil();                               // Leser datastruktur fra fil.
};

#endif
