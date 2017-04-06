#if !defined(__GREN_H)
//GREN.H alex + mats
#define  __GREN_H

#include"OVELSE.H"
#include"CONST.H"
#include"ENUM.H"

class Gren :public TextElement {
private:
				//navn lagres i TextElement
	registerTidPoeng typeMaaling;		//hva slags maalintype er det
	int antOvelser;						//maxismlt antall ovelser for denne ovelsen
	int antSifre;						
	Ovelse *array[MAXOVELSER + 1];		//array med pekere til Ovelse Objekter
	char *annet;						//text med div info
	int antallRegistrerteOvelser;		//teller som hviser hvor mange ovelser som er registrert saa langt 

public:
	Gren();                                         // Constructor.
	Gren(char* a);                                  // Constructor med parametre.
	Gren(ifstream & inn, char* a);                  // Constructor til lesing fra fil.
	void endreNavn();				                // G E
	void display();					                // G A
	void skrivOvelse();				                // Skriver ut all data for alle ovelser     Valg : G S og O A
	void skrivGrenNavn();                           // Skriver ut navnet på grenen.
	void skrivTilFIl(ofstream & ut);
	int hentAntalOvelser();
	void menyValgOvelse();							// Switch for Ovelse.						Valg : O
	void skrivOvelseMeny();							// KommandoMeny for Ovelse.
	void registrerNyOvelse();						// Lager ny Ovelse.							Valg : O N
	void ovelseDelMeny();							// Henter funksjon for deltagerListe switch	Valg : O L
	void ovelseResMeny();							// henter funksjon for resultatListe switch	Valg : O R
	void skrivIdTilRegistrerteOvelser();
	void skrivListGrenTilFil();
	void endreOvelseMeny();                         // Meny for hva som kan endres for en Ovelse.
	void endreOvelse();                             // Endrer data for en Ovelse.           : O E
	void endreOvelseNavn(int indeks);               // Endrer navnet for en Ovelse.
	void fjernOvelse();                             // Fjerner en Ovelse.                   : O F
	void skrivHoveddataOvelser();                   // Skriver hoveddata for alle Ovelser.  : O A
	bool finnesOvelse(char *navn);                  // Sjekk om Ovelsen finnes i array med param. navn.
	void skrivUtRegistrerteOvelser();               // Skriver ut alle registrerte ovelser.

};
#endif
