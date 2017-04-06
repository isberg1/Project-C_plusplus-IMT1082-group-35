//deltagere.cpp

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>
#include <regex>                                    // For søking i DS.
#include "DELTAGER.H"
#include "DELTAGERE.H"
#include "FUNKSJONER.H"
#include "NASJONER.H"

using namespace std;

extern Nasjoner nasjonObj;


Deltagere::~Deltagere()		//destructor
{
	delete DeltagerListe;
}

void Deltagere::skrivMeny()			//skriver ut meny
{
   cout << "\n\nMENY FOR DELTAGERE:"
		<< "\n\tN - Registrer ny deltager"
		<< "\n\tE - Endre deltager"
		<< "\n\tA - Skriv hoveddataene om alle deltagere"
		<< "\n\tS - Skriv ut alle data om en deltager"
		<< "\n\tQ - Tilbake til hovedmeny";
}

void Deltagere::menyValg()		//lar brukeren velge i menyen
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
    deltagerID = les("\nSkriv inn ID for deltageren:", 0001, 9999);

    if (!DeltagerListe->inList(deltagerID)) {       // Hvis deltager ikke allerede er registrert.
                                                    // Lager nytt Deltager obj. Sender med tempNasjon
      nyDeltager = new Deltager(tempNasjon ,deltagerID); // og ID som parameter.
      DeltagerListe->add(nyDeltager);                 // Legger det nye objektet inn i listen.

      skrivTilFil();                                // Skriver datastruktur til fil.
    }
    else                                            // Hvis en deltager med samme ID ligger i lista.
      cout << "\n\tEn deltager med ID: " << deltagerID << " finnes allerede";
  }
  else                                              // Hvis nasjonen ikke finnes.
    cout << "\n\tNasjonen er ikke registrert"
         << "\n\tDu maa registrere nasjonen for du legger til deltagere i den";
}

void Deltagere::endreDeltager()			//meny for aa endre en deltagers data
{
	char valg;
	int valgID;
	Deltager *tempDeltager;

    cout << "\nTilgjengelige deltagere:\n";
    skrivUtRegistrerteDeltagere();                  // Skriver ut alle tilgjengelige deltagere.
	valgID = les("\nHvilke deltager vil du endra paa? (nr)", 1, DeltagerListe->noOfElements());

	if (DeltagerListe ) {                           // Hvis deltagerlisten finnes:
      tempDeltager = (Deltager*)DeltagerListe->removeNo(valgID);
	  tempDeltager->display();

	  endreDeltagerMeny();
	  valg = les("\nDeltagere/Endre deltager: ");
	  while (valg != 'Q') {
        switch (valg) {
          case 'N': tempDeltager->endreNavn();	break;
		  case 'E': tempDeltager->endreNasjon();break;
		  case 'A': tempDeltager->endreData();	break;
		  case 'K': tempDeltager->endreKjonn();	break;
        }
      tempDeltager->display();
      endreDeltagerMeny();
	  valg = les("\nDeltagere/Endre deltager: ");
	  }
	DeltagerListe->add(tempDeltager);
	skrivTilFil();
	}
	else
	  cout << "\n\tDet finnes ingen deltager med ID-en " << valgID;
}

void Deltagere::endreDeltagerMeny()
{
	cout << "\n\nMENY FOR AA ENDRE PAA EN DELTAGER:"
		<< "\n\tN - Endre navn"
		<< "\n\tE - Endre nasjon"
		<< "\n\tA - Endre annen info"
		<< "\n\tK - Endre kjonn"
		<< "\n\tQ - Tilbake til deltagermeny";
}

void Deltagere::skrivDataAlle()			//skriver ut alle dataene til en deltager paa skjermen
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
	else
	{
		cout << "Det eksisterer ingen deltagere enda!";
	}
}

void Deltagere :: skrivDataEn() {                   // Skriver all data om en gitt deltager.  : Valg D S
  char valg;
  char buffer[STRLEN];
  char *sokEtter, *sokeTekst;
  int id;
  Deltager *deltager;

  cout << "\nVil du sooke etter deltager ved et entydlig navn (A), eller ID? (B)";
  do {
    valg = les("\nValg (A/B): ");
  } while (valg != 'A' && valg != 'B');             // Looper hvis ikke A eller B er valg.

  if (valg == 'A') {
    les("\nNavnet du vil sooke etter", buffer, STRLEN);

    sokEtter = konverter(buffer);                   // Lager string med ny lengde.
    sokEtter = konverterTilStore(sokEtter);         // Gjør om til store bokstaver.

    if (DeltagerListe) {                            // Hvis deltagerListen finnes:
      for (int i = 1; i <= DeltagerListe->noOfElements(); i++) { // Looper gjennom alle elementer.

        deltager = (Deltager*) DeltagerListe->removeNo(i); // Fjerner fra liste.

        sokeTekst = deltager->hentNavn();           // Henter ut navnet til deltageren.
        sokeTekst = konverterTilStore(sokeTekst);   // Gjør om navnet til store bokstaver.

        string ord = sokEtter;                      // Gjør om til string for å bruke søkefunksjoner.
        string tekst = sokeTekst;
        regex r("\\b" + ord + "\\b");               // Bruker regex.
        smatch m;

        if (regex_search(tekst, m, r))              // Hvis søket matcher:
          deltager->display();                      // Displayer objekt.

        DeltagerListe->add(deltager);               // Legger deltageren tilbake i lista.
      }
    }
  }
  else {                                            // Valg == 'B':
    id = les("\nSkriv inn ID-en til deltageren: ", 1, 9999);

    if (DeltagerListe && DeltagerListe->inList(id)) {
      deltager = (Deltager*) DeltagerListe->remove(id);
      deltager->display();                          // Displayer deltager med gitt ID.
      DeltagerListe->add(deltager);
    }
    else
      cout << "\n\tFinner ikke deltager med ID: " << id;
  }
}

void Deltagere :: loopDeltagerTropp(char *n) {      // Skriver ut deltagere for en nasjon.    : Valg N T
  int antDeltagere;
  Deltager *deltager;

  if (DeltagerListe)                                // Hvis listen finnes:
    antDeltagere = DeltagerListe->noOfElements();   // Antall deltager-objekter i listen.

  for (int i = 1; i <= antDeltagere; i++) {         // Looper gjennom listen:
    deltager = (Deltager*) DeltagerListe->removeNo(i); // Fjerner element 1 fra listen.
    deltager->skrivDeltagerTropp(n);                // Kaller Deltager sin funksjon.
    DeltagerListe->add(deltager);                   // Legger objekt tilbake i liste.
  }
}

void Deltagere :: skrivTilFil() {                   // Skriver til fil.
  int antDeltagere;
  Deltager *deltager;                               // Peker til Deltager-objekt.
  ofstream ut("DELTAGERE.DTA");                     // Lager fil.

  if (DeltagerListe) {                              // Hvis DeltagerListen finnes:
    antDeltagere = DeltagerListe->noOfElements();   // Antall elementer i listen.

    skriv(ut, antDeltagere);                        // Skriver ut antall Deltagere.

    for (int i = 1; i <= antDeltagere; i++) {       // Looper gjennom alle objekter i lista.
      deltager = (Deltager*) DeltagerListe->removeNo(i); // Fjerner objekt fra lista.
      deltager->skrivTilFil(ut);                    // Kaller Deltager som skriver ut sine data.
      DeltagerListe->add(deltager);                 // Legger Deltager tilbake i lista.
    }
  }
  ut.close();                                       // Lukker fil.
}

void Deltagere :: lesFraFil() {                     // Leser datastruktur fra fil.
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

char * Deltagere::hentNasjon(int deltag)	        // Henter en deltagers najon fra deltagerListe.
{											        // Brukes til aa lage en Statistikk Raport.
	Deltager *ptr;
	char temp[STRLEN];


	if (DeltagerListe->inList(deltag))			//hvis en daltager er i listen
	{		// ta detltageren ut av listen hent ut Najonen og legg objektet tilbake i listen
		ptr = (Deltager*)DeltagerListe->remove(deltag);
		strcpy(temp, ptr->hentNajon());
		DeltagerListe->add(ptr);

		return temp;
	}

	strcpy(temp, "deltager finnes ikke");         // feilmelding
	return	temp;
}

char * Deltagere::hentNavn(int deltag)	//henter en deltagers navn via en daltagers ID
{
	Deltager *ptr;
	char temp[STRLEN];

	if (DeltagerListe)		//hvis listen existerer
	{
		if (DeltagerListe->inList(deltag))		//hvis deltageren er i listen
		{			// ta detltageren ut av listen hent ut navnet og legg objektet tilbake i listen
			ptr = (Deltager*)DeltagerListe->remove(deltag);
			strcpy(temp, ptr->hentNavn());
			DeltagerListe->add(ptr);

			return temp;
		}
	}	

	strcpy(temp, "deltager finnes ikke");		//feilmelding
	return	temp;
}

bool Deltagere::sjekkId(int deltagerNr)             // Hent deltager nr og legg objekt tilbake i liste.
{
	if (DeltagerListe)		                        // Hvis deltagerliste finnes.
	{
		if (DeltagerListe->inList(deltagerNr))      // Hvis deltager finnes.
		{
			return true;
		}
		return false;
	}
	return false;
}

void Deltagere :: skrivUtRegistrerteDeltagere() {   // Skriver ut navn og id paa alle deltagere.
  Deltager *deltager;
                                                    // Looper gjennom objekter.
  for (int i = 1; i <= DeltagerListe->noOfElements(); i++) {
    deltager = (Deltager*) DeltagerListe->removeNo(i); // Fjerner deltager fra lista.
    cout << "nr " << i << ": ";
    deltager->skrivNavn();                          // Skriver navnet paa deltageren.
    DeltagerListe->add(deltager);
  }
}

int Deltagere::antallRegistrerteDeltagere()	        // Henter antall elementer i deltagerlisten.
{

	if (DeltagerListe)								//hvis listen eksisterer
	{
		return DeltagerListe->noOfElements();		//returner antaller
	}

	return 0;										//eller returner 0
}
