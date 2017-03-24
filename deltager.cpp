//deltager.cpp

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "DELTAGER.H"
#include "NASJONER.H"
#include "CONST.H"
#include "FUNKSJONER.H"
#include <iostream>
#include <cstring>
#include <fstream>



using namespace std;


extern Nasjoner nasjonObj;                          // Nasjoner-objekt fra main.



Deltager::Deltager()
{
	cout << "\n\tDet har skjedd en feil! Deltager-objekter skal ikke lages uten parametre!";
}

                                                    // Sender med ID til constructor.
Deltager :: Deltager(char *nyNasjon, int in) : NumElement(in) {
  char buffer[STRLEN];

    nasjon = nyNasjon;                              // Setter nasjon på deltageren, fra param.

    cout << "\nNavnet paa deltageren: ";
    cin.getline(buffer, STRLEN);                    // Leser inn full navn på nasjon.
    fullNavn = konverter(buffer);                   // Gjør om størrelsen.

    cout << "\nAnnet: ";
    cin.getline(buffer, STRLEN);                    // Leser inn full navn på nasjon.
    data = konverter(buffer);                       // Gjør om størrelsen.

    nasjonObj.oppdaterNasjon(nyNasjon);             // Oppdaterer Nasjon obj. med antDeltagere +1.
}
/*
Deltager::~Deltager()
{
//		foreløpig ubrukt		//
}
*/
void Deltager::endreInfo()
{


}

void Deltager::display()							//	Skriver ut alle data om en deltager.
{
	cout << "\nDeltagers id:           " << number
		 << "\nDeltagers navn:         " << fullNavn
		 << "\nDeltagers kj>nn:        " << deltagerKjonn
		 << "\nDeltagers nasjonalitet: " << nasjon;
}

void Deltager::displayHoved()
{													//	Skriver kun ut hoveddataene for en deltager.
	cout << "\nDeltagers id:    " << number
		 << "\nDeltagers navn:  " << fullNavn
		 << "\nDeltagers kj>nn: " << deltagerKjonn;
}

void Deltager :: skrivDeltagerTropp(char *n) {
  if (strcmp(n, nasjon) == 0)                       // Hvis nasjonens navn er like parameterens:
    cout << "\nID:    " << number
         << "\nNavn:  " << fullNavn
         << "\nKjonn: " << deltagerKjonn;
}

