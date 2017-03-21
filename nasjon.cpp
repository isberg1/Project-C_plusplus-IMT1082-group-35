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
#include <iostream>

using namespace std;



Nasjon :: Nasjon() {
  cout << "\nAdvarsel, Nasjon-objekter skal ikke lages uten parameter";
}
                                                    // Sender med forkortelsen til constructor.
Nasjon :: Nasjon(char *nasjonKort) : TextElement(nasjonKort) {
  char buffer[STRLEN];                              // Buffertekst som er 80 lang.

  cout << "\nFullt navn: ";
  cin.getline(buffer, STRLEN);                      // Leser inn full navn på nasjon.
  fulltNavn = konverter(buffer);                    // Gjør om størrelsen.

  antDeltagere = les("\nAntall deltagere:", 1, 500);// Leser inn antall deltagere.

  cout << "\nKontaktperson: ";
  cin.getline(buffer, STRLEN);                      // Leser inn navn på kontaktperson.
  kontaktNavn = konverter(buffer);                  // Gjør om størrelsen.
                                                    // Leser inn tlf i interval.
  kontaktTlf = les("\nKontaktpersonens tlf:", 10000000, 99999999);

  cout << "\nAnnet: ";
  cin.getline(buffer, STRLEN);                      // Leser inn annen data.
  andreData = konverter(buffer);                    // Gjør om størrelsen.

}

                                                    // Sender med forkortelsen til constructor.
Nasjon :: Nasjon(ifstream & inn, char *nasjonKort) : TextElement(nasjonKort)  {
  antDeltagere = lesInt(inn);
  fulltNavn = lesTxt(inn);
  kontaktNavn = lesTxt(inn);
  kontaktTlf = lesInt(inn);
  andreData = lesTxt(inn);
}

Nasjon :: ~Nasjon() {
  // Ingenting å slette?
}

void Nasjon :: display() {
  cout << "\n\nNasjonsforkortelse:    " << text
       << "\nFullt navn:            " << fulltNavn
       << "\nDeltagere:             " << antDeltagere
       << "\nKontaktperson:         " << kontaktNavn
       << "\nKontaktpersonens tlf:  " << kontaktTlf
       << "\nAnnet:                 " << andreData;
}

void Nasjon :: skrivTilFil(ofstream & ut) {

  /* Filoppsett:

     text           -   forkortelsesnavn
     antDeltagere   -   Antall deltagere i troppen
     fulltNavn      -   Det fulle navnet til nasjonen
     kontaktNavn    -   Navnet til kontaktpersonen
     kontaktTlf     -   Telefonnr. til kontaktperson
     andreData      -   Ekstra informasjon om nasjonen
  */

  skriv(ut, text);                                  // Skriver data ut til fil.
  skriv(ut, antDeltagere);
  skriv(ut, fulltNavn);
  skriv(ut, kontaktNavn);
  skriv(ut, kontaktTlf);
  skriv(ut, andreData);
}

void Nasjon :: endreNasjon() {                      // Endrer data for en gitt nasjon.
  char buffer[STRLEN];                              // Buffertekst som er 80 lang.

  cout << "\nFullt navn: ";
  cin.getline(buffer, STRLEN);                      // Leser inn full navn på nasjon.
  fulltNavn = konverter(buffer);                    // Gjør om størrelsen.

  cout << "\nKontaktperson: ";
  cin.getline(buffer, STRLEN);                      // Leser inn navn på kontaktperson.
  kontaktNavn = konverter(buffer);                  // Gjør om størrelsen.
                                                    // Leser inn tlf i interval.
  kontaktTlf = les("\nKontaktpersonens tlf:", 10000000, 99999999);

  cout << "\nAnnet: ";
  cin.getline(buffer, STRLEN);                      // Leser inn annen data.
  andreData = konverter(buffer);                    // Gjør om størrelsen.

}

void Nasjon :: skrivHoveddata() {                   // Skriver ut hoveddata.
  cout << "\n\nNasjonsforkortelse:    " << text
       << "\nFullt navn:            " << fulltNavn
       << "\nDeltagere:             " << antDeltagere;
}

int Nasjon :: hentAntDeltagere() {                  // Returnerer antDeltagere.
  return antDeltagere;
}
