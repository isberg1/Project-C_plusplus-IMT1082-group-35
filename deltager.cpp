//deltager.cpp

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "DELTAGER.H"
#include "NASJONER.H"
#include "CONST.H"
#include "FUNKSJONER.H"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>



using namespace std;


extern Nasjoner nasjonObj;                          // Nasjoner-objekt fra main.



Deltager::Deltager()
{
	cout << "\n\tDet har skjedd en feil! Deltager-objekter skal ikke lages uten parametre!";
}

                                                    // Sender med ID til constructor.
Deltager :: Deltager(char *nyNasjon, int ID) : NumElement(ID) {
  char buffer[STRLEN];
  char valg;

  nasjon = nyNasjon;                                // Setter nasjon p� deltageren, fra param.

  les("\nNavnet paa deltageren: ", buffer, NVLEN);  // Leser in nnavet p� deltageren.
  fullNavn = konverter(buffer);                     // Gj�r om st�rrelsen og lager ny.

  do {                                              // Loop hvis M eller K ikke blir valg.
    valg = les("\nKjonn (m/k): ");
  } while (valg != 'M' && valg != 'K');

  if (valg == 'M')
    deltagerKjonn = Mann;                           // kj�nn blir satt til Mann.
  else
    deltagerKjonn = Kvinne;                         // kj�nn blir satt til Kvinne.

  les("\nAnnet", buffer, STRLEN);                   // Leser inn annet.
  data = konverter(buffer);                         // Gj�r om st�rrelsen og lager ny.

  nasjonObj.oppdaterNasjon(nyNasjon);               // Oppdaterer Nasjon obj. med antDeltagere +1.
}

                                                    // Sender med ID til constructor.
Deltager :: Deltager(ifstream & inn, int ID) : NumElement(ID) {
  int tempKjonn;

  fullNavn = lesTxt(inn);                           // Leser datastruktur fra fil via les funksjon.
  nasjon = lesTxt(inn);
  data = lesTxt(inn);

  tempKjonn = lesInt(inn);

  if (tempKjonn == 0)                               // Hvis det som ble lest inn = 0.
    deltagerKjonn = Mann;                           // Setter kj�nn til � v�re Mann.
  else
    deltagerKjonn = Kvinne;                         // Setter kj�nn til � v�re Kvinne.
}

Deltager::~Deltager()
{
  delete[] nasjon;
  delete[] fullNavn;
  delete[] data;
}

void Deltager::endreNavn()
{
	strcpy(fullNavn, "");
	les("Skriv inn nytt navn", fullNavn, NVLEN);
	cout << "\nNavn endret til: " << fullNavn;
}

void Deltager::endreNasjon()						// Endrer nasjonen til en deltager
{
	char *forkortelse;

	forkortelse = nasjonsForkortelse("\nSkriv inn den nye nasjonens forkortelse"); //les ny nasjon

	if (nasjonObj.finnesNasjon(forkortelse)) {									//hvis ny najon finnes

		nasjonObj.reduserAntDeltagere(nasjon);									//reduser antall deltagere i aktuelt obj.
		delete[]nasjon;															//slett navnet p� laget nasjon
		nasjonObj.okAntalletDeltagere(forkortelse);								//ook antallet deltagere i aktuell obj
		nasjon = forkortelse;													//sett nytt navn p� nasjon
		nasjonObj.skrivTilFil();												//skriv til fil
	}
	else
	{
		skriv("Finner ikke nasjon med forkortelsen: ", forkortelse);	//feilmelding
		delete[]forkortelse;										//slett navnet p� ny nasjon hvis den ikke eksisterer
	}
}

void Deltager::endreData()
{
	char buffer[STRLEN];

	delete[] data;									// Slett gammel data.
	les("\nSkriv inn ny info", buffer, STRLEN);		// Spor etter ny data.
	data = konverter(buffer);						// Konverter fra array til peker.
}

void Deltager::endreKjonn()						    // Endre kjonn p� deltager.
{
	char valg;
	do {                                            // Loop om input ikke er M eller K.
		valg = les("\nKjonn (m/k): ");
	} while (valg != 'M' && valg != 'K');

	if (valg == 'M')
		deltagerKjonn = Mann;                       // Kjonn blir satt til Mann.
	else
		deltagerKjonn = Kvinne;						// Kjonn blir satt til Kvinne.
	cout << "\nKjonn endret til: " << ((deltagerKjonn == Mann) ? "Mann" : "Kvinne");
}

void Deltager::display()							// Skriver ut alle data om en deltager.
{
	cout << "\n\nDeltagers id:           " << number
		 << "\nDeltagers navn:         " << fullNavn
		 << "\nDeltagers kjonn:        " << ((deltagerKjonn == Mann) ? "Mann" : "Kvinne")
		 << "\nDeltagers nasjonalitet: " << nasjon
		 << "\nAnnet:                  " << data;
}

void Deltager::displayHoved()
{													// Skriver kun ut hoveddataene for en deltager.
	cout << "\n\nDeltagers id:    " << number
		 << "\nDeltagers navn:  " << fullNavn
		 << "\nDeltagers kjonn: " << ((deltagerKjonn == Mann) ? "Mann" : "Kvinne");
}

void Deltager :: skrivDeltagerTropp(char *n) {
  if (strcmp(n, nasjon) == 0)                       // Hvis nasjonens navn er like parameterens:
    cout << "\n\nID:    " << number
         << "\nNavn:  " << fullNavn
         << "\nKjonn: " << ((deltagerKjonn == Mann) ? "Mann" : "Kvinne");
}

void Deltager :: skrivTilFil(ofstream & ut) {       // Skriver til fil.
  /* Filoppsett:

     antObjekter    -   Antall objeketer i liste.
     number         -   Deltager ID-en.
     fullnavn       -   Navnet til deltageren.
     nasjon         -   Nasjonstilh�righet.
     data           -   Ekstra informasjon om deltageren.
     kjonn          -   Kj�nnet til deltageren.
  */

  skriv(ut, number);                                // Skriver ut data til fil via Skriv funksjon.
  skriv(ut, fullNavn);
  skriv(ut, nasjon);
  skriv(ut, data);
  skriv(ut, deltagerKjonn);
}

char* Deltager :: hentNavn() {                      // Returnerer navnet til deltageren.                Brukes ikke?
  return fullNavn;
}

char * Deltager::hentNajon()                        // Returnerer en deltagers najon, brukes til aa lage en Statistikk Raport.
{
	char temp[NASJONLEN +1];

	strcpy(temp, nasjon);
	return temp;
}

void Deltager :: skrivNavn() {                      // Skriver ut navnet til deltageren.
  cout << "\tNavn: " << fullNavn << '\n';
}
