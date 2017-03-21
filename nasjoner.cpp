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
  delete nasjonsListe;                              // Sletter liste.
  nasjonsListe = nullptr;                           // Setter peker til nullptr.
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
      case 'A': skrivHoveddata();       break;      // Skriver hovedata om alle nasjoner.
      case 'T':                         break;      //
      case 'S': skrivAllData();         break;      // Skriver ut all data om en gitt nasjon.
      default : skrivMeny();            break;      // Meny av brukerens valg.
    }
    skrivMeny();
    valg = les("\nNasjoner: ");                     // Leser brukerens ønske/valg.
  }
}

void Nasjoner :: registrerNyNasjon() {              // Registrerer ny nasjon : Valg N N
  char buffer[STRLEN];
  char *forkortelse;                                // Nasjonsforkortelsen.
  Nasjon *nyNasjon;

  if (!nasjonsListe)                                // Hvis listen ikke finnes.
    nasjonsListe = new List(Sorted);                // Lager ny sortert liste.

  forkortelse = nasjonsForkortelse();               // Leser inn tre bokstaver og gjør dem store.

  if (!nasjonsListe->inList(forkortelse)) {         // Hvis nasjonen ikke ligger i lista:
    nyNasjon = new Nasjon(forkortelse);             // Lager nasjonsobjekt, sender med forkortelsen.
    nasjonsListe->add(nyNasjon);                    // Legger objekt til i lista.
  }
  else
    cout << "\n\t" << forkortelse << " finnes allerede";
}

void Nasjoner :: endreNasjon() {                    // Endre data for en nasjon : Valg N E



}

void Nasjoner :: skrivHoveddata() {                 // Skriver ut hoveddataene for nasjoner : Valg N A
  Nasjon *nasjon;                                   // Peker til nasjons-objekt
  int antNasjoner = 0;

  if (nasjonsListe)                                 // Hvis listen har elementer.
    antNasjoner = nasjonsListe->noOfElements();     // Antall nasjoner i lista.

  for (int i = 1; i <= antNasjoner; i++) {          // Looper gjennom alle resepter.
    nasjon = (Nasjon*) nasjonsListe->removeNo(i);   // Tar nasjonen ut av lista.
    nasjon->skrivHoveddata();                       // Skriver ut data om nasjon.
    nasjonsListe->add(nasjon);                      // Legger nasjon tilbake i lista.
  }
}

void Nasjoner :: skrivDeltagerTropp() {             // Skriver ut data om deltagere i tropp : Valg N T



}

void Nasjoner :: skrivAllData() {                   // Skriver alle data om en gitt nasjon : Valg N S
  char *forkortelse;
  Nasjon *nasjon;

  forkortelse = nasjonsForkortelse();               // Leser inn tre bokstaver og gjør dem store.

                                                    // Hvis nasjonenslista finnes
  if (nasjonsListe && nasjonsListe->inList(forkortelse)) { // og nasjonen ligger i lista.
    nasjon = (Nasjon*) nasjonsListe->remove(forkortelse);  // Fjerner fra lista.
    nasjon->display();                              // Skriver ut all data om nasjonen.
    nasjonsListe->add(nasjon);                      // Legger objekt tilbake i lista.
  }
  else
    cout << "\nNasjonen finnes ikke";
}

bool Nasjoner :: finnesNasjon() {                   // Sjekker om nasjonen finnes : Valg D X
  char *forkortelse;

  forkortelse = nasjonsForkortelse();               // Leser inn tre bokstaver og gjør dem store.

                                                    // Hvis nasjonenslista finnes
  if (nasjonsListe && nasjonsListe->inList(forkortelse)) { // og nasjonen ligger i lista.
   return true;                                     // Hvis sant.
  }
  else
    return false;                                   // Hvis usant.
}
