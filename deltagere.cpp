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



Deltagere::Deltagere()
{
	antDeltagere = 0;
	DeltagerListe = new List(Sorted);
}

Deltagere::Deltagere(char* t)
{

}

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
	int antDeltagere = 0;

		antDeltagere = DeltagerListe->noOfElements();

	for (int i = 1; i <= antDeltagere; i++) {
		tempDeltager = (Deltager*)DeltagerListe->removeNo(i);
		tempDeltager->displayHoved();
		DeltagerListe->add(tempDeltager);
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
		skriv("finner ikke deltager med id: ", buffer);
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


