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
using namespace std;


//  GLOBALE VARIABLE:


//	HOVEDPROGRAM:
int main()
{
	int test = les("testing", 1, 99);

	skriv("testskriv", test);


    return 0;
}
