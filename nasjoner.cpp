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
      case 'N': registrerNyNasjon();  break;        // Registrerer ny nasjon.
      case 'E': endreNasjon();        break;        // Endrer data for en nasjon.
      case 'A': skrivHoveddata();     break;        // Skriver hovedata om alle nasjoner.
      case 'T': skrivDeltagerTropp(); break;        // Skriver ut alle deltagere i nasjonens tropp.
      case 'S': skrivAllData();       break;        // Skriver ut all data om en gitt nasjon.
      default : skrivMeny();          break;        // Meny av brukerens valg.
    }
    skrivMeny();
    valg = les("\nNasjoner: ");                     // Leser brukerens ønske/valg.
  }
}

void Nasjoner :: registrerNyNasjon() {              // Registrerer ny nasjon                 : Valg N N
  char *forkortelse;                                // Nasjonsforkortelsen.
  Nasjon *nyNasjon;

  if (!nasjonsListe)                                // Hvis listen ikke finnes.
    nasjonsListe = new List(Sorted);                // Lager ny sortert liste.

                                                    // Leser inn tre bokstaver og gjør dem store.
  forkortelse = nasjonsForkortelse("\nSkriv inn nasjonens forkortelse");

  if (!nasjonsListe->inList(forkortelse)) {         // Hvis nasjonen ikke ligger i lista:
    nyNasjon = new Nasjon(forkortelse);             // Lager nasjonsobjekt, sender med forkortelsen.
    nasjonsListe->add(nyNasjon);                    // Legger objekt til i lista.
  }
  else
    cout << "\n\t" << forkortelse << " finnes allerede";

  skrivTilFil();                                    // Skriver ut til fil.
}

void Nasjoner :: endreNasjon() {                    // Endre data for en nasjon              : Valg N E
  Nasjon *nasjon;                                   // Peker til nasjons-objekt.
  char *forkortelse;

  skrivUtForkortelse();                             // Skriv ut tilgjengelige valg.
                                                    // Leser inn tre bokstaver og gjør dem store.
  forkortelse = nasjonsForkortelse("\nHvilke nasjon vil du endre paa?");

                                                    // Hvis nasjonslista finnes og
  if (nasjonsListe && nasjonsListe->inList(forkortelse)) { // nasjonen ligger i lista.
    nasjon = (Nasjon*) nasjonsListe->remove(forkortelse);  // Fjerner fra lista.
    nasjon->endreNasjon();                          // Kaller Nasjon sin funksjon for å endre på data.
    nasjonsListe->add(nasjon);                      // Legger tilbake i lista.
  }
  else
    cout << "\n\tNasjonen finnes ikke";

  skrivTilFil();                                    // Skriver ut til fil.
}

void Nasjoner :: skrivHoveddata() {                 // Skriver ut hoveddataene for nasjoner  : Valg N A
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

void Nasjoner :: skrivDeltagerTropp() {             // Skriver ut data om deltagere i tropp  : Valg N T
  Nasjon *nasjon;
  char *forkortelse;

  skrivUtForkortelse();                             // Skriv ut tilgjengelige valg.
                                                    // Leser inn tre bokstaver og gjør dem store.
  forkortelse = nasjonsForkortelse("\nFor hvilke nasjon skal deltagertroppen skrives ut?");

                                                    // Hvis nasjon finnes
  if (nasjonsListe && nasjonsListe->inList(forkortelse)) { // og ligger i lista

    // Kjør grensesnitt funksjon som displayer deltagere.
    // Loop må skje på Deltagere sin side.
  }
  else                                              // Hvis nasjonsobjektet ikke finnes.
    cout << "\nNasjonen du skrev inn finnes ikke";
}

void Nasjoner :: skrivAllData() {                   // Skriver alle data om en gitt nasjon   : Valg N S
  char *forkortelse;
  Nasjon *nasjon;

  skrivUtForkortelse();                             // Skriv ut tilgjengelige valg.
                                                    // Leser inn tre bokstaver og gjør dem store.
  forkortelse = nasjonsForkortelse("\nHvilke nasjon vil du ha mer informasjon om?");

                                                    // Hvis nasjonenslista finnes
  if (nasjonsListe && nasjonsListe->inList(forkortelse)) { // og nasjonen ligger i lista.
    nasjon = (Nasjon*) nasjonsListe->remove(forkortelse);  // Fjerner fra lista.
    nasjon->display();                              // Skriver ut all data om nasjonen.
    nasjonsListe->add(nasjon);                      // Legger objekt tilbake i lista.
  }
  else
    cout << "\n\tNasjonen finnes ikke";
}

bool Nasjoner :: finnesNasjonOgOppdater() {         // Hvis Nasjon finnes, antDeltagere +1   : Valg D -
  Nasjon *nasjon;
  char *forkortelse;

  skrivUtForkortelse();                             // Skriv ut tilgjengelige valg.
                                                    // Leser inn tre bokstaver og gjør dem store.
  forkortelse = nasjonsForkortelse("\nSkriv inn nasjonens forkortelse");

                                                    // Hvis nasjonenslista finnes
  if (nasjonsListe && nasjonsListe->inList(forkortelse)) { // og nasjonen ligger i lista.

    nasjon = (Nasjon*) nasjonsListe->remove(forkortelse);  // Fjerner objekt fra liste.
    nasjon->oppdaterAntDeltagere();                 // Oppdaterer antDeltagere med 1.
    nasjonsListe->add(nasjon);                      // Legger tilbake i liste.

    skrivTilFil();                                  // Skriver endringer til fil.
    return true;
  }
  else
    return false;                                   // Hvis usant.
}

void Nasjoner :: skrivTilFil() {                    // Skriver til fil.
  int antNasjoner;
  Nasjon *nasjon;                                   // Peker til nasjons-objekt.
  ofstream ut("NASJONER.DTA");                      // Lager fil.

  if (nasjonsListe) {                               // Hvis nasjonsliste finnes.
    antNasjoner = nasjonsListe->noOfElements();     // Antall elementer i liste.

    skriv(ut, antNasjoner);                         // Skriver ut antall nasjoner.

    for (int i = 1; i <= antNasjoner; i++) {        // Looper gjennom alle objekter i liste.
      nasjon = (Nasjon*) nasjonsListe->removeNo(i); // Fjerner objekt fra liste.
      nasjon->skrivTilFil(ut);                      // Kaller Nasjon funksjon som skriver ut sine data.
      nasjonsListe->add(nasjon);                    // Legger nasjon tilbake i lista.
    }
  }
  ut.close();                                       // Stenger fil.
}

void Nasjoner :: lesFraFil() {                      // Leser datastruktur fra fil.
  char *forkortelse;
  int antNasjoner;
  Nasjon *nyNasjon;

  delete nasjonsListe;                              // Sletter listen.
  nasjonsListe = new List(Sorted);                  // Lager ny liste.

  ifstream inn("NASJONER.DTA");                      // Åpner fil hvis den eksisterer.

  if (inn) {                                        // Hvis filen finnes.

    antNasjoner = lesInt(inn);                      // Leser inn int fra fil.

    for (int i = 1; i <= antNasjoner; i++) {
      forkortelse = lesTxt(inn);                    // Leser inn nasjonsforkortelsen.

      nyNasjon = new Nasjon(inn, forkortelse);      // Nasjonsobjekt leser inn egne data.
      nasjonsListe->add(nyNasjon);                  // Legger nasjon til i liste.
    }
    inn.close();                                    // Stenger fil.
  }
  else                                              // Hvis filen ikke finnes.
    cout << "\nFinner ikke filen 'NASJONER.DTA'";
}

void Nasjoner :: skrivUtForkortelse() {             // Skriver ut nasjonens forkortelse.
  Nasjon *nasjon;
  int newLineTeller = 1;

  if (nasjonsListe) {                               // Hvis listen finnes og det er elementer i den.
    cout << "\nTilgjengelige nasjoner:\n";
                                                    // Looper gjennom alle elementer.
    for (int i = 1; i <= nasjonsListe->noOfElements(); i++) {

      nasjon = (Nasjon*) nasjonsListe->removeNo(i); // Fjerner objekt fra liste.
      nasjon->skrivForkortelse();                   // Skriver ut text (forkortelsen).
      nasjonsListe->add(nasjon);                    // Legger tilbake i listen.

      if (newLineTeller % 6 == 0)                   // Skriver ut "new line" hvis 6 nasjoner
        cout << '\n';                               // ligget etter hverandre på skjermen.
      newLineTeller ++;                             // Teller opp med 1.
    }
  }
  else                                              // Hvis ingen ligger i listen.
    cout << "\nIngen nasjoner er registrert";
}
