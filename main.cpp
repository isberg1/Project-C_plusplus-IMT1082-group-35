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


///  BRUK AV GLOBALE VARIABLE I ANDRE FILER:
Nasjoner nasjonObj;
Medaljer medaljeObj;
Poeng poengObj;
Deltagere deltagerObj;
Grener grenenerObj;

//extern Nasjoner nasjonObj;
//extern Deltagere deltagerObj;
//extern Grener grenenerObj;
//extern Medaljer medaljeObj;
//extern 



// **********************************  H O V E D P R O G R A M M E T  **********************************

int main() {
  char valgMain;

  nasjonObj.lesFraFil();                            // Leser nasjoners data fra fil.
  grenenerObj.lesFraFil();							//leser grener fra fil
  medaljeObj.lesFraFil();							//leser medaljer fra fil
  poengObj.lesFraFil();								//leser poeng fra fil
  deltagerObj.lesFraFil();                          // Leser deltagers data fra fil.
				
  


  MainMeny();                                       // Skriver ut meny.
  valgMain = les("\nHovedmeny: ");

  while (valgMain != 'X') {                         // Så lenge valg ikke er 'X':
    switch (valgMain) {
      case 'N' : nasjonObj.menyValg();	     break; // Kaller Nasjoner sin meny.
      case 'D' : deltagerObj.menyValg();     break; // Kaller Deltagere sin meny.
	  case 'G' : grenenerObj.skrivMeny();    break; // kaller Grener sin meny.
      case 'O' :        break;
	  case 'M' : medaljeObj.skrivMedaljer(); break; // viser medaljeoversikt
	  case 'P' : poengObj.skrivPoeng();      break;	// viser poengoversikt
    }
    MainMeny();
    valgMain = les("\nHovedmeny: ");
  }
  return 0;

}
