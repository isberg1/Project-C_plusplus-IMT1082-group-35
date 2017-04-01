#if !defined(__GREN_H)
//GREN.H alex
#define  __GREN_H

#include"OVELSE.H"
#include"CONST.H"
#include"ENUM.H"

class Gren :public TextElement {
private:
	//navn lagres i TextElement
	registerTidPoeng typeMaaling;
	int antOvelser;
	int antSifre;
	Ovelse *array[MAXOVELSER + 1];
	char *annet;
	int antallRegistrerteOvelser;

public:
	//constructor
	Gren();
	Gren(char* a);
	Gren(ifstream & inn, char* a);
	//destructor
	~Gren();
	void endreNavn();				                // G E
	void display();					                // G A
	void skrivOvelse();				                // G S
	void skrivGrenNavn();                           // Skriver ut navnet på grenen.
	void skrivTilFIl(ofstream & ut);
	int hentAntalOvelser();
	
	void menyValgOvelse();							// Switch for Ovelse.						Valg : O
	void skrivOvelseMeny();							// KommandoMeny for Ovelse.
	void registrerNyOvelse();						// Lager ny Ovelse.							Valg : O N
	void skrivAlleOvelse();							// Skriver hoveddata for alle Ovelser.		Valg : O A
	void ovelseDelMeny();							// Henter funksjon for deltagerListe switch	Valg : O L
	void ovelseResMeny();							// henter funksjon for resultatListe switch	Valg : O R
	void testingNyOvelse();
	void testingSkrivResListe();
	void skrivIdTilRegistrerteOvelser();

	                       // Registrerer ny Ovelse.               : O N
	void endreOvelseMeny();                         // Meny for hva som kan endres for en Ovelse.
	void endreOvelse();                             // Endrer data for en Ovelse.           : O E
	void endreOvelseNavn(int indeks);               // Endrer navnet for en Ovelse.
	void fjernOvelse();                             // Fjerner en Ovelse.                   : O F
	void skrivHoveddataOvelser();                   // Skriver hoveddata for alle Ovelser.  : O A
	bool finnesOvelse(char *navn);                  // Sjekk om Ovelsen finnes i array med param. navn.
	void skrivUtRegistrerteOvelser();               // Skriver ut alle registrerte ovelser.
	char *hentNavn();                               // Returnerer navnet (text).


};
#endif
