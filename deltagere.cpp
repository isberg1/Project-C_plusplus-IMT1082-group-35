//deltagere.cpp

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>
#include "DELTAGER.H"
#include "DELTAGERE.H"
#include "FUNKSJONER.H"
#include "NASJONER.H"

using namespace std;

extern Nasjoner nasjonObj;

Deltagere::~Deltagere()
{
	delete DeltagerListe;
}

void Deltagere::skrivMeny()
{
	cout << "\n\nFØLGENDE KOMMANDOER ER TILGJENGELIGE:"
		<< "\n\tN - Registrer ny deltager"
		<< "\n\tE - Endre deltager"
		<< "\n\tA - Skriv hoveddataene om alle deltagere"
		<< "\n\tS - Skriv ut alle data om en deltager"
		<< "\n\tQ - Tilbake til hovedmeny";
}

void Deltagere::menyValg()
{
	char valg;

	skrivMeny();
	valg = les("\nDeltagere: ");
	while (valg != 'Q') {
		switch (valg) {
		case 'N': nyDeltager();		break;
		case 'E': endreDeltager();	break;
		case 'A': skrivDataAlle();	break;
		case 'S': skrivDataEn();	break;
		default : skrivMeny();		break;
    }
    skrivMeny();
    valg = les("\nDeltagere: ");
	}
}

void Deltagere :: nyDeltager() {                    // Oppretter ny Deltager                  : Valg D N
  int deltagerID;
  char *tempNasjon;
  Deltager *nyDeltager;

  if (!DeltagerListe)                               // Hvis deltagerListen ikke finnes:
    DeltagerListe = new List(Sorted);               // Lager ny liste.

  nasjonObj.skrivUtForkortelse();                   // Skriver ut hvilke nasjoner som er registrert.

                                                    // Passer på at nasjonen skrives inn korrekt.
  tempNasjon = nasjonsForkortelse("\nSkriv inn nasjonens forkortelse");

  if (nasjonObj.finnesNasjon(tempNasjon)) {         // Hvis nasjonen finnes:
                                                    // Leser inn ID-en til deltageren.
    deltagerID = les("\nSkriv inn ID for deltageren:", 1, 9999);

    if (!DeltagerListe->inList(deltagerID)) {       // Hvis deltager ikke allerede er registrert.
                                                    // Lager nytt Deltager obj. Sender med tempNasjon
      nyDeltager = new Deltager(tempNasjon ,deltagerID); // og ID som parameter.
      DeltagerListe->add(nyDeltager);                 // Legger det nye objektet inn i listen.

      // Skriv til fil....
    }
    else                                            // Hvis en deltager med samme ID ligger i lista.
      cout << "\n\tEn deltager med ID: " << deltagerID << " finnes allerede";
  }
  else                                              // Hvis nasjonen ikke finnes.
    cout << "\n\tNasjonen er ikke registrert"
         << "\n\tDu maa registrere nasjonen for du legger til deltagere i den";
}

void Deltagere::endreDeltager()
{

}

void Deltagere::skrivDataAlle()
{
	Deltager* tempDeltager;

	if (DeltagerListe)								// Hvis listen eksisterer
	{
		for (int i = 1; i <= DeltagerListe->noOfElements(); i++)
		{
			tempDeltager = (Deltager*)DeltagerListe->removeNo(i);
			tempDeltager->displayHoved();			// Skriv ut hoveddata for 
			DeltagerListe->add(tempDeltager);		// Alle deltagere i listen.
		}
	}
	
}

void Deltagere::skrivDataEn()
{
	int buffer = 0;
	Deltager *tempDeltager;
																		
	buffer = les("Skriv inn id'en til deltageren", 0, 9999);

	if (DeltagerListe->inList(buffer))
	{
		tempDeltager = (Deltager*)DeltagerListe->remove(buffer);
		tempDeltager->display();
		DeltagerListe->add(tempDeltager);
	}
	else
	{
		skriv("\n\tFinner ikke deltager med id: ", buffer);
	}
}

void Deltagere :: loopDeltagerTropp(char *n) {      // Skriver ut deltagere for en nasjon.    : Valg N T
  int antDeltagere;
  Deltager *deltager;

  antDeltagere = DeltagerListe->noOfElements();     // Antall deltager-objekter i listen.

  if (antDeltagere == 0)                            // Hvis det ikke er noen i listen:
    cout << "\n\tNasjonen har ingen deltagere";     // Skriver ut feilmelding.

  for (int i = 1; i <= antDeltagere; i++) {         // Looper gjennom listen:
    deltager = (Deltager*) DeltagerListe->removeNo(i); // Fjerner element 1 fra listen.
    deltager->skrivDeltagerTropp(n);                // Kaller Deltager sin funksjon.
    DeltagerListe->add(deltager);                   // Legger objekt tilbake i liste.
  }
}

 void Deltagere::skrivTilFil() {                   // Skriver til fil.
	int antDeltagere;
	Deltager *deltager;                               // Peker til Deltager-objekt.
	ofstream ut("DELTAGERE.DTA");                     // Lager fil.
	
		if (DeltagerListe) {                              // Hvis DeltagerListen finnes:
		antDeltagere = DeltagerListe->noOfElements();   // Antall elementer i listen.
		
			skriv(ut, antDeltagere);                        // Skriver ut antall Deltagere.
		
			for (int i = 1; i <= antDeltagere; i++) {       // Looper gjennom alle objekter i lista.
			deltager = (Deltager*)DeltagerListe->removeNo(i); // Fjerner objekt fra lista.
			deltager->skrivTilFil(ut);                    // Kaller Deltager som skriver ut sine data.
			DeltagerListe->add(deltager);                 // Legger Deltager tilbake i lista.
			
		}
		
	}
	ut.close();                                       // Lukker fil.
	
}

void Deltagere::lesFraFil() {                     // Leser datastruktur fra fil.
	int deltagerID, antDeltagere;
	Deltager *nyDeltager;
	
		delete DeltagerListe;                             // Sletter listen.
	DeltagerListe = new List(Sorted);                 // Lager ny liste.
	
		ifstream inn("DELTAGERE.DTA");                    // Åpner fil hvis den eksisterer.
	
		if (inn) {                                        // Hvis filen finnes:
		
			antDeltagere = lesInt(inn);                     // Leser inn int fra fil.
		
			for (int i = 1; i <= antDeltagere; i++) {       // Looper for alle objekter på filen.
			deltagerID = lesInt(inn);                     // Leser inn deltagers ID. (number).
			
				nyDeltager = new Deltager(inn, deltagerID);   // Deltagerobjekt leser inn egne data.
			DeltagerListe->add(nyDeltager);               // Legger deltager til i liste.
			
		}
		inn.close();                                    // Stenger fil.
	}
	else                                              // Hvis filen ikke finnes:
		 cout << "\nFinner ikke filen 'DELTAGERE.DTA'";
	
}