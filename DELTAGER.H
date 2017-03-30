#if !defined(__DELTAGER_H)
#define  __DELTAGER_H

#include <fstream>
#include "ListTool2B.h"
#include "CONST.H"
#include "ENUM.H"

using namespace std;



class Deltager : public NumElement                  // Arver lister.
{
private:                                            // Deltager ID = number fra NumElement.
	char *fullNavn;
	char *nasjon;
	char *data;
	kjonn deltagerKjonn;

public:
	Deltager();                                     // Constructor.
	Deltager(char *nyNasjon, int ID);               // Constructor med parametre.
	Deltager(ifstream & inn, int ID);               // Constructor som leser data fra fil.
    ~Deltager();                                    // Deconstructor.
	virtual void display();                         // ?
    void skrivTilFil(ofstream & ut);                // Skriver til fil.
	void skrivDeltagerTropp(char *n);               // Skriver ut alle deltagere for gitt nasjon.
	void endreNavn();								// Endrer navnet til en deltager.
	void endreNasjon();								// Endrer nasjonen til en deltager.
	void endreData();								// Endrer den ekstra infoen til en deltager.
	void endreKjonn();								// Endrer kjonnet til en deltager.			// // // NB! Flytter ikke deltager til motsatt ovelse NB! // // //
	void displayHoved();                            // Skriver ut Hoveddata for en deltager.
	char *hentNavn();                               // Returnerer navnet til deltageren.
	char *hentNajon();								// Returnerer en deltagers najon	brukes til aa lage en Statistikk Raport
};

#endif

