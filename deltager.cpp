//deltager.cpp

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "DELTAGER.H"
#include "NASJONER.H"
#include "CONST.H"
#include "FUNKSJONER.H"
#include <iostream>
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

  nasjon = nyNasjon;                                // Setter nasjon på deltageren, fra param.

  cout << "\nNavnet paa deltageren: ";
  cin.getline(buffer, STRLEN);                      // Leser inn navnet til deltageren.
  fullNavn = konverter(buffer);                     // Gjør om størrelsen.

  do {                                              // Loop hvis M eller K ikke blir valg.
    valg = les("\nKjonn (m/k): ");
  } while (valg != 'M' && valg != 'K');

  if (valg == 'M')
    deltagerKjonn = Mann;                           // kjønn blir satt til Mann.
  else
    deltagerKjonn = Kvinne;                         // kjønn blir satt til Kvinne.

  cout << "\nAnnet: ";
  cin.getline(buffer, STRLEN);                      // Leser inn annet.
  data = konverter(buffer);                         // Gjør om størrelsen.

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
    deltagerKjonn = Mann;                           // Setter kjønn til å være Mann.
  else
    deltagerKjonn = Kvinne;                         // Setter kjønn til å være Kvinne.
}

Deltager::~Deltager()
{
//		foreløpig ubrukt
}

void Deltager::endreNavn()
{
	strcpy(fullNavn, "");
	les("Skriv inn nytt navn", fullNavn, NVLEN);
	cout << "\nNavn endret til: " << fullNavn;
}

void Deltager::endreNasjon()
{
//	strcpy(nasjon, "");
//	les("\nSkriv inn ny nasjontilhorighet", nasjon, NASJONLEN);
//	cout << "\nNasjon endret til: " << nasjon;
}

void Deltager::endreData()
{
	strcpy(data, "");
	les("\nSkriv inn ny info", data, STRLEN);
	cout << "\nEkstra info endret til: " << data;
}

void Deltager::endreKjonn()						    // Endre kjonn på deltager.
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

void Deltager::display()							//	Skriver ut alle data om en deltager.
{
	cout << "\n\nDeltagers id:           " << number
		 << "\nDeltagers navn:         " << fullNavn
		 << "\nDeltagers kjonn:        " << ((deltagerKjonn == Mann) ? "Mann" : "Kvinne")
		 << "\nDeltagers nasjonalitet: " << nasjon
		 << "\nAnnet:                  " << data;
}

void Deltager::displayHoved()
{													//	Skriver kun ut hoveddataene for en deltager.
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

     antObjeketer   -   Antall objeketer i liste.
     number         -   Deltager ID-en.
     fullnavn       -   Navnet til deltageren.
     nasjon         -   Nasjonstilhørighet.
     data           -   Ekstra informasjon om deltageren.
     kjonn          -   Kjønnet til deltageren.
  */

  skriv(ut, number);                                // Skriver ut data til fil via Skriv funksjon.
  skriv(ut, fullNavn);
  skriv(ut, nasjon);
  skriv(ut, data);
  skriv(ut, deltagerKjonn);
}
