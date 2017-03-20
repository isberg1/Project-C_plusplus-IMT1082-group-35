/*
    Main.cpp
    Gruppeprosjekt i objekt-orientert programmering.

    Alexander Jakobsen, Mats Ove Mandt Skjærstein og Kristian Lund.
*/


//  INCLUDE:
#include <iostream>                                 // cin, cout.
#include "ListTool2B.h"                             // Verktøykasse for lister.
#include "CONST.H"                                  // Conster.
#include"FUNKSJONER.H"
#include"NASJONER.H"
#include"DELTAGERE.H"
#include"GRENER.H"
#include"MEDALJER.H"
#include"POENG.H"

using namespace std;

//#pragma warning(disable:xxxx)  bruk til å disable warning

//  GLOBALE VARIABLE:
  Nasjoner nasjonObj;
 //Deltagere deltagerObj
 //Gren grenenObj
 //Medaljer medaljeObj
 //Poeng poengObj

//	HOVEDPROGRAM:
int main()
{
	char valgMain = 'A';

	MainMeny();
	valgMain = les("\nHovedmeny: ");

	while (valgMain != 'X')
	{

		switch (valgMain)
		{
		case 'N':	nasjonObj.menyValg();	break;
		case 'D':		break;
		case 'G':		break;
		case 'O':		break;
		case 'M':		break;
		case 'P':		break;
		case 'X':		break;
		default:		break;
		}

		MainMeny();
		valgMain = les("\nHovedmeny: ");
	}

    return 0;
}
