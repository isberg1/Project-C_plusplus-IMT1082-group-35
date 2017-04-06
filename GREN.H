#if !defined(__GREN_H)
//GREN.H alex + mats
#define  __GREN_H

#include"OVELSE.H"
#include"CONST.H"
#include"ENUM.H"

class Gren :public TextElement {
private:                                            // Navn lagres i TextElement.

	registerTidPoeng typeMaaling;		            // Hva slags maalintype er det.
	int antOvelser;						            // Maxismlt antall ovelser for denne ovelsen.
	int antSifre;
	Ovelse *array[MAXOVELSER + 1];		            // Array med pekere til Ovelse Objekter.
	char *annet;						            // Text med div info.
	int antallRegistrerteOvelser;		            // Teller som hviser hvor mange ovelser som er registrert saa langt.

public:
	Gren();                                         // Constructor.
	Gren(char* a);                                  // Constructor med parametre.
	Gren(ifstream & inn, char* a);                  // Constructor til lesing fra fil.
	~Gren();                                        // Destructor
	void endreNavn();				                // G E
	void display();					                // G A
	void skrivOvelse();				                // Skriver ut all data for alle ovelser     Valg : G S og O A
	void skrivGrenNavn();                           // Skriver ut navnet på grenen.
	void skrivTilFIl(ofstream & ut);
	int hentAntalOvelser();
	void menyValgOvelse();							// Switch for Ovelse.						Valg : O
	void skrivOvelseMeny();							// KommandoMeny for Ovelse.
	void registrerNyOvelse();						// Lager ny Ovelse.							Valg : O N
	void ovelseDelMeny();							// Henter funksjon for deltagerListe switch Valg : O L
	void ovelseResMeny();							// henter funksjon for resultatListe switch	Valg : O R
	void skrivIdTilRegistrerteOvelser();
	void skrivListGrenTilFil();
	void endreOvelseMeny();                         // Meny for hva som kan endres for en Ovelse.
	void endreOvelse();                             // Endrer data for en Ovelse.               Valg : O E
	void endreOvelseNavn(int indeks);               // Endrer navnet for en Ovelse.
	void fjernOvelse();                             // Fjerner en Ovelse.                       Valg : O F
	void skrivHoveddataOvelser();                   // Skriver hoveddata for alle Ovelser.      Valg : O A
	bool finnesOvelse(char *navn);                  // Sjekk om Ovelsen finnes i array med param. navn.
	void skrivUtRegistrerteOvelser();               // Skriver ut alle registrerte ovelser.

};
#endif
