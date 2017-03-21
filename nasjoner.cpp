/*
    nasjoner.cpp
    Klassefunksjoner for Nasjoner
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include "NASJONER.H"                               // Klassen Nasjoner.
#include "CONST.H"                                  // Conster.
#include "FUNKSJONER.H"                             // Globale funksjoner.
#include <iostream>                                 // cin, cout.

using namespace std;



Nasjoner :: ~Nasjoner() {
  delete nasjon;                                    // Sletter nasjonsobjekt. forkortelse
}

void Nasjoner :: skrivMeny() {                      // Tiljgengelige valg.
  cout << "\n\nFØLGENDE KOMMANDOER ER TILGJENGELIGE:"
       << "\n\tN - Registrer en ny nasjon"
       << "\n\tE - Endre en nasjon"
       << "\n\tA - Skriv hoveddataene om alle nasjoner"
       << "\n\tT - Skriv en nasjons deltagertropp"
       << "\n\tS - Skriv alle data om en gitt nasjon"
       << "\n\tQ - Gå tilbake til hovedmeny";
}

void Nasjoner :: menyValg() {                       // Valg av funksjonalitet.
  char valg;

  skrivMeny();
  valg = les("\nNasjoner: ");
  while (valg != 'Q') {
    switch(valg) {
      case 'N': registrerNyNasjon();    break;      // Registrerer ny nasjon.
      case 'E':                         break;      //
      case 'A':                         break;      //
      case 'T':                         break;      //
      case 'S':                         break;      //
      default:  skrivMeny();            break;      // Meny av brukerens valg.
    }
    skrivMeny();
    valg = les("\nNasjoner: ");                     // Leser brukerens ønske/valg.
  }
}

void Nasjoner :: registrerNyNasjon() {
  char buffer[STRLEN];
  char *forkortelse;                                // Nasjonsforkortelsen.

  do {                                              // Loop:
    cout << "\nNasjonsforkortelse (3 blokk-bokstaver): ";
    cin.getline(buffer, STRLEN);                    // Leser inn verdi.
    forkortelse = new char[strlen(buffer)+1];       // Lager ny char med ny lengde.
    strcpy(forkortelse, buffer);                    // Kopierer over data til forkortelse.

  } while ( !erBokstaver(forkortelse) ||            // Så lenge det ikke er bokstaver og
            strlen(forkortelse) != 3);              // lengder på array ikke er 3.

  for (int i = 0; i < 3; i ++)                      // Looper gjennom indeksene.
    forkortelse[i] = toupper(forkortelse[i]);       // Gjør om til stor bokstav.

  nasjon = new Nasjon(forkortelse);                 // Lager nasjonsobjekt, sender med forkortelsen.

  nasjon->display();
  delete[] forkortelse;                             // Sletter char.
}
