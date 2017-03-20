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
  char buffer[STRLEN];                                  // Buffertekst som er 80 lang.
  nasjonsListe = new List(Sorted);                  // Lager ny sortert liste.


  cout << "\nFullt navn: ";
  cin.getline(buffer, STRLEN);
  fulltNavn = konverter(buffer);



  cout << "\nAntall deltagere i troppen: ";
  cin >> antDeltagere;

  while ( cin.fail() &&  antDeltagere <= 0) {     // Så lenge det er et tall og antall > 0.
    cout << "\n\tAntall (heltall over 0): ";
    cin >> antDeltagere;
  }

les("\nKontaktpersonens tlf:", 10000000, 99999999);



}

                                                    // Sender med forkortelsen til constructor.
Nasjon :: Nasjon(ifstream & innfil, char *nasjonKort) : TextElement(nasjonKort)  {



}

Nasjon :: ~Nasjon() {



}

void Nasjon :: display() {



}

void Nasjon :: skrivTilFil(ofstream & utfil) {



}
