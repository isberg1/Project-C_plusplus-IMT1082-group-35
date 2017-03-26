/*
    nasjon.cpp
    Klassefunksjoner Nasjon
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include "NASJON.H"                                 // Klassen Nasjon.
#include "FUNKSJONER.H"                             // Globale funksjoner.
#include "CONST.H"                                  // Conster.
#include <iostream>                                 // cin, cout.

using namespace std;



Nasjon :: Nasjon() {
  cout << "\nAdvarsel, Nasjon-objekter skal ikke lages uten parameter";
}

                                                    // Sender med forkortelsen til constructor.
Nasjon :: Nasjon(char *nasjonKort) : TextElement(nasjonKort) {
  char buffer[STRLEN];                              // Buffertekst som er 80 lang.

  les("\nFullt navn for nasjonen: ", buffer, NVLEN);// Leser inn full navn på nasjon.
  fulltNavn = konverter(buffer);                    // Gjør om størrelsen.

  // AntDeltagere blir lest inn fra 'finnesNasjonOgOppdater()' fra Nasjoner.
  antDeltagere = 0;

  les("\nKontaktperson: ", buffer, NVLEN);          // Leser inn navn på kontaktperson.
  kontaktNavn = konverter(buffer);                  // Gjør om størrelsen.
                                                    // Leser inn tlf i interval.
  kontaktTlf = les("\nKontaktpersonens tlf:", 10000000, 99999999);

  les("\nAnnet: ", buffer, STRLEN);                  // Leser inn annen data.
  andreData = konverter(buffer);                    // Gjør om størrelsen.
}

                                                    // Sender med forkortelsen til constructor.
Nasjon :: Nasjon(ifstream & inn, char *nasjonKort) : TextElement(nasjonKort)  {
  antDeltagere = lesInt(inn);                       // Leser datastruktur fra fil via les funksjon.
  fulltNavn = lesTxt(inn);
  kontaktNavn = lesTxt(inn);
  kontaktTlf = lesInt(inn);
  andreData = lesTxt(inn);
}

Nasjon :: ~Nasjon() {
  delete[] text;
  delete[] fulltNavn;
  delete[] kontaktNavn;
  delete[] andreData;
}

void Nasjon :: display() {
  cout << "\n\nNasjonsforkortelse:    " << text     // Skriver ut data til skjerm.
       << "\nFullt navn:            " << fulltNavn
       << "\nDeltagere:             " << antDeltagere
       << "\nKontaktperson:         " << kontaktNavn
       << "\nKontaktpersonens tlf:  " << kontaktTlf
       << "\nAnnet:                 " << andreData;
}

void Nasjon :: skrivTilFil(ofstream & ut) {

  /* Filoppsett:

     antObjeketer   -   Antall objeketer i liste.
     text           -   forkortelsesnavn
     antDeltagere   -   Antall deltagere i troppen
     fulltNavn      -   Det fulle navnet til nasjonen
     kontaktNavn    -   Navnet til kontaktpersonen
     kontaktTlf     -   Telefonnr. til kontaktperson
     andreData      -   Ekstra informasjon om nasjonen
  */

  skriv(ut, text);                                  // Skriver data ut til fil via skriv funksjon.
  skriv(ut, antDeltagere);
  skriv(ut, fulltNavn);
  skriv(ut, kontaktNavn);
  skriv(ut, kontaktTlf);
  skriv(ut, andreData);
}

void Nasjon :: endreNasjonsNavn() {                 // Endrer det fulle navnet til nasjonen.
  char buffer[STRLEN];                              // Buffertekst som er 80 lang.

  les("\nNasjonens fulle navn:", buffer, NVLEN);
  delete[] fulltNavn;                               // Sletter fulltNavn før det lages ny.
  fulltNavn = konverter(buffer);                    // Gjør om størrelsen og lager ny peker.
}

void Nasjon :: endreKontaktperson() {               // Endrer navnet til kontaktperson.
  char buffer[STRLEN];

  les("\nKontaktpersonens navn: ", buffer, NVLEN);
  delete[] kontaktNavn;                             // Sletter kontaktnavn før det lages ny.
  kontaktNavn = konverter(buffer);                  // Gjør om størrelsen og lager ny peker.
}

void Nasjon :: endreTlf() {                         // Endrer TLF til kontaktperson.
  kontaktTlf = les("\nKontaktpersonens tlf:", 10000000, 99999999);
}

void Nasjon :: endreAnnet() {                       // Endrer feltet 'Annet'.
  char buffer[STRLEN];

  les("\nAnnet: ", buffer, STRLEN);
  delete[] andreData;                               // Sletter andreData før det lages ny.
  andreData = konverter(buffer);                    // Gjør om størrelsen og lager ny peker.
}

void Nasjon :: skrivHoveddata() {                   // Skriver ut hoveddata.
  cout << "\n\nNasjonsforkortelse:    " << text
       << "\nFullt navn:            " << fulltNavn
       << "\nDeltagere:             " << antDeltagere;
}

void Nasjon :: skrivForkortelse() {                 // Returnerer text.
  cout << '\t' << text;
}

void Nasjon :: oppdaterAntDeltagere() {             // Oppdaterer antall deltagere med 1.
  antDeltagere ++;
}
