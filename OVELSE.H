//OVELSE.H alle
#if !defined(__OVELSE_H)
#define  __OVELSE_H

#include"ListTool2B.h"
#include"FUNKSJONER.H"
#include"CONST.H"
#include"ENUM.H"



class Ovelse
{
private:
	static int navnTeller;		                    // Brukes til datamedlemm  int "nr".
 	int nr;
	registerTidPoeng maaling;		                // Hvilken type maaling skal registrers.
	char *navn;									    // Ovelsens navn.
	int antDeltagere;								// Antal deltagere i startliste.
	int dato;
	int klokkeslett;
	int *deltagerListe;                             // Deltager array.
	int *resultatListe;                             // Resultat array ( MinSECTidel;	MinSecHundredel; MinSekTusendel; PoengX; PoengXX;).
	int log[ANTALLVINNERE + 1];                     // Loggfører seiersrekkefolgen brukes til R <id> S NB!

public:
	Ovelse();                                       // Constructor.
	Ovelse(ifstream & inn);                         // Constructor med filargunent.
	Ovelse(char *ovelseNavn, registerTidPoeng typeMaaling);// Constructor, får et arg. fra Grener som viser hva slags maaling som skal registreres.
	~Ovelse();

	/// Diverse
	char *filNavn(int type = 0);                    // Genererer et unik filnavn basert på ovelsens unike "nr" og send med 1 for .RES eller ingenting for .STA
	void skrivTilFil(ofstream & ut);				// Skriv ovelse til fil.
	void lesFraFil(ifstream & inn);					// Les ovelse fra fil.
	void bubbleSort();							    // Sorterer 2 int array.
	void fjernPoeng();							    // Reduserer tidliger fordelte poeng og medaljer.
	void okPoengPoeng();						    // Oker antall poeng naar maaletypen er poeng.
	void okPoengTid();							    // Oker antall poeng naar maaletypen er tid.
	void alokerMinne();
	void frigiMinne();
	void sjekkID(int & temp, char buffer[]);		// Brukes til aa skrive ut data.
	int lagUniktNr();								// Lager et unikt tall som brukes til datamedlemm  int "nr".
	int skaffVerdi();							    // Henter inn og sikkrer riktig verdi til resultatlisten.
	char *hentNavn();                               // Returnerer navnet til Ovelsen.
	int datoSjekk(int dato);                        // Sjekker om dato er på riktig format.
	int klokkeSjekk(int kl);                        // Sjekker om kl. er på riktig format.
	void skrivNavn();                               // Skriver ut ovelsens navn.
	int hentId();									// Henter en ovelses id.
	void nullstillLister();							// Nullstiller strart og resultatlister.
	void logResett();								// Nullstiller log.

	/// StartListe
	void menyValgDelListe();						// Switch for deltagerLister.		   Valg : O L
	void skrivDelListeMeny();						// KomandoMeny for deltagerListe.
	void skrivDelListe();							// Skriver ut en deltagerListe.		   Valg : O L S
	void nyDelListe();								// Lager ny deltagerListe.			   Valg : O L N
	void endreDelListe();							// Endrer en deltagerListe.			   Valg : O L E
	void fjernDelListe();							// Fjerner en deltagerListe.		   Valg : O L F
	void deltagerSkrivtilFil();
	void deltagerLesFraFil();

	/// ResListe
	void menyValgResListe();						// Switch for resultatLister.		   Valg : O R
	void skrivResListeMeny();						// KommandoMeny for resultatListe.
	void skrivResultatliste();						// Skriv resultatlisten til skjerm
	void nyResultatListe();							// Lager en ny resultatListe.		   Valg : O R N
	bool fjernResultatliste();						// Fjern resultatliste.
	void resultaterSkrivTilFil();					// Skriv resultatliste til fil.
	void resultaterLesFraFil();						// Les resultatliste fra fil.
	void endreNavn(char *ovelseNavn);               // Endrer navnet til ovelsen.
	void endreDato();                               // Endrer datoen til ovelsen.
	void endreKlokkeslett();                        // Endrer kl. til ovelsen.
	void skrivHovedData();                          // Skriver hoveddata for en ovelse.
	void korigerVinnerePoeng();
	void korigerVinnereTid();
};

#endif
