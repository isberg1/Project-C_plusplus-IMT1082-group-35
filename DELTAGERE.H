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
	void skrivMeny();								// Deltagere-switch.
	void menyValg();								// KommandoMeny for Deltagere.
	void nyDeltager();                              // Oppretter ny Deltager                  : Valg D N
	void endreDeltager();							// Endrer deltagerens datamedlemmer		  : Valg D E
	void endreDeltagerMeny();						// EndreDeltager-switch
	void skrivDataAlle();							// Skriver ut hoveddata for alle deltagere: Valg D A
	void skrivDataEn();                             // Skriver all data om en gitt deltager.  : Valg D S
	void loopDeltagerTropp(char *n);                // Skriver ut deltagere for en nasjon.    : Valg N T
    void skrivTilFil();                             // Skriver til fil.
    void lesFraFil();                               // Leser datastruktur fra fil.
	char *hentNasjon(int deltager);					// Faar et deltagernr. og returnerer nasjonen.  brukes til aa lage en Statistikk Raport.
	char *hentNavn(int deltager);					// Hent deltagers navn.
	bool sjekkId(int deltagerNr);					// Sjekker deltager nr.
    void skrivUtRegistrerteDeltagere();             // Skriver ut navn og id paa alle deltagere.
	int antallRegistrerteDeltagere();
};

#endif
