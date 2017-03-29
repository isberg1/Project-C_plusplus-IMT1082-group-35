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
	void endreNavn();				// G E
	void display();					// G A
	void skrivOvelse();				// G S
	void skrivGrenNavn();           // Skriver ut navnet på grenen.
	void skrivTilFIl(ofstream & ut);
	int hentAntalOvelser();
	void menyValgOvelse();			// Switch for Ovelse.						Valg : O
	void skrivOvelseMeny();			// KommandoMeny for Ovelse.			  
	void nyOvelse();				// Lager ny Ovelse.							Valg : O N
	void endreOvelse();				// Endrer en Ovelse.						Valg : O E
	void fjernOvelse();				// Fjerner en Ovelse.						Valg : O F
	void skrivAlleOvelse();			// Skriver hoveddata for alle Ovelser.		Valg : O A
	void ovelseDelMeny();			// Henter funksjon for deltagerListe switch	Valg : O L
	void ovelseResMeny();			// henter funksjon for resultatListe switch	Valg : O R
};
#endif