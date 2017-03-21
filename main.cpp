/*
    main.cpp
    Gruppeprosjekt i objekt-orientert programmering.

    Alexander Jakobsen, Mats Ove Mandt Skjærstein og Kristian Lund.
*/

//#pragma warning(disable:xxxx)  bruk til å disable warning


///  INCLUDE:
#include <iostream>                                 // cin, cout.
#include "ListTool2B.h"                             // Verktøykasse for lister.
#include "CONST.H"                                  // Conster.
#include"FUNKSJONER.H"                              // Funksjoner.
#include"NASJONER.H"                                // Klassen Nasjoner.
#include"DELTAGERE.H"                               // Klassen Deltagere.
#include"GRENER.H"                                  // Klassen Grener.
#include"MEDALJER.H"                                // Klassen Medaljer.
#include"POENG.H"                                   // Klassen Poeng.

using namespace std;


///  GLOBALE VARIABLE:
Nasjoner nasjonObj;
//Deltagere deltagerObj;
//Gren grenenObj;
//Medaljer medaljeObj;
//Poeng poengObj;


///  BRUK AV GLOBALE VARIABLE I ANDRE FILER:
//extern Nasjoner nasjonObj;
//extern Deltagere deltagerObj;
//extern Gren grenenObj;
//extern Medaljer medaljeObj;
//extern Poeng poengObj;


// **********************************  H O V E D P R O G R A M M E T  **********************************

int main() {
  char valgMain;

  nasjonObj.lesFraFil();                            // Leser nasjoners data fra fil.

  MainMeny();                                       // Skriver ut meny.
  valgMain = les("\nHovedmeny: ");

  while (valgMain != 'X') {                         // Så lenge valg ikke er 'X':
    switch (valgMain) {
      case 'N' : nasjonObj.menyValg();	    break;  // Kaller Nasjoner sin meny.
      case 'D' :        break;
      case 'G' :        break;
      case 'O' :        break;
      case 'M' :        break;
      case 'P' :        break;
    }
    MainMeny();
    valgMain = les("\nHovedmeny: ");
  }
  return 0;
}
