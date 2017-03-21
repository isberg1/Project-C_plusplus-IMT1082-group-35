/*
    nasjon.cpp
    Klassefunksjoner Nasjon
*/
////////////////////////////////////////////////////:://////////////////////////////////////////////////

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include "NASJON.H"                                 // Klassen Nasjon.
#include "FUNKSJONER.H"                             // Globale funksjoner.
#include "CONST.H"                                  // Conster.
#include <iostream>

using namespace std;


                                                    // Sender med forkortelsen til constructor.
Nasjon :: Nasjon(char *nasjonKort) : TextElement(nasjonKort) {
  char buffer[STRLEN];                              // Buffertekst som er 80 lang.
  nasjonsListe = new List(Sorted);                  // Lager ny sortert liste.

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
Nasjon :: Nasjon(ifstream & innfil, char *nasjonKort) : TextElement(nasjonKort)  {



}

Nasjon :: ~Nasjon() {
  delete nasjonsListe;                              // Sletter liste.
  nasjonsListe = nullptr;                           // Setter peker til nullptr.
}

void Nasjon :: display() {
  cout << "\nNasjonsforkortelse:    " << text
       << "\nFullt navn:            " << fulltNavn
       << "\nDeltagere:             " << antDeltagere
       << "\nKontaktperson:         " << kontaktNavn
       << "\nKontaktpersonens tlf:  " << kontaktTlf
       << "\nAnnet:                 " << andreData;
}

void Nasjon :: skrivTilFil(ofstream & utfil) {



}

void Nasjon :: endreNasjon() {



}

