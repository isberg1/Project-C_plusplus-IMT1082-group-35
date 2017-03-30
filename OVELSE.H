//OVELSE.H alex
#if !defined(__OVELSE_H)
#define  __OVELSE_H

#include"ListTool2B.h"
#include"FUNKSJONER.H"
#include"CONST.H"
#include"ENUM.H"


class Ovelse
{
private:
	static int navnTeller;		                    // Brukes til datamedlemm  int "nr"
 	int nr;
	registerTidPoeng maaling;		                // Hvilken type maaling skal registrers
	char *navn;									    // Ovelsens navn
	int antDeltagere;
	int dato;
	int klokkeslett;
	int *deltagerListe;                             // Deltager array
	int *resultatListe;                             // Resultat array ( MinSECTidel;	MinSecHundredel; MinSekTusendel; PoengX; PoengXX;)
	int log[ANTALLVINNERE + 1];                     // Loggfører seiersrekkefolgen brukes til R <id> S NB!

public:
	Ovelse();                                       // Constructor.
	Ovelse(char *ovelseNavn, registerTidPoeng typeMaaling);// Constructor, får et arg. fra Grener som viser hva slags maaling som skal registreres
	~Ovelse();
	void skrivData();
	char *filNavn(int type = 0);                    // Genererer et unik filnavn basert på ovelsens unike "nr" og send med 1 for .RES eller ingenting for .STA
	void skrivTilFil(ofstream & ut);
	void lesFraFil(ifstream & inn);
	int lagUniktNr();								// Lager et unikt tall som brukes til datamedlemm  int "nr"
	int skaffVerdi();							    // Henter inn og sikkrer riktig verdi til resultatlisten
	char *hentNavn();                               // Returnerer navnet til Ovelsen.
	int datoSjekk(int dato);                        // Sjekker om dato er på riktig format.
	int klokkeSjekk(int kl);                        // Sjekker om kl. er på riktig format.
	void skrivNavn();                               // Skriver ut ovelsens navn.
	int hentId();									// henter en ovelses id.
	void menyValgDelListe();				// Switch for deltagerLister.		   Valg : O L
	void skrivDelListeMeny();				// KomandoMeny for deltagerListe.
	void skrivDelListe();					// Skriver ut en deltagerListe.		   Valg : O L S
	void nyDelListe();						// Lager ny deltagerListe.			   Valg : O L N
	void endreDelListe();					// Endrer en deltagerListe.			   Valg : O L E
	void fjernDelListe();					// Fjerner en deltagerListe.		   Valg : O L F
	void menyValgResListe();				// Switch for resultatLister.		   Valg : O R
	void skrivResListeMeny();				// KommandoMeny for resultatListe.
	void skrivResListe();					// Skriver ut en resultatListe.		   Valg : O R S
	void nyResListe();						// Lager en ny resultatListe.		   Valg : O R N
	void fjernResListe();					// Fjerner en resultatListe.
};

/*
liste over ting som må gjores i ovelse
lag alle 3 menyene. start med aa lagen en meny til i Grener. lag saa 2 menyer i Ovelse
lag en funksjon som lager et unikt filnavn (til OVxxx.STA og OVxxxx.RES)						alex
lag en funksjon som sletter en fil fra HDD( til O F  ,  O L <id> F  og  O R <id> F)				mats

Forslag til implimentasjnsrekkefolge etter at det ovenfor er gjort:
1. valg :O     N  ->  A  ->  E  -> skriv til fil  -> les fra fil  ->  F                         mats
2. Valg :O L   N  ->  S  ->  E  -> skriv til fil  -> les fra fil  ->  F
3. Valg :O S   N  ->  S(før NB!)  -> skriv til fil  -> les fra fil ->  F  ->  S(NB!)			alex

//tror vansklighetsgraden fra lettest til vanskligst er: 2, 1, 3

når 1, er gjort så kan også valg: G S gjøres etterpå, samt å fullføre skriv til og les fra fil i Gren
*/

#endif