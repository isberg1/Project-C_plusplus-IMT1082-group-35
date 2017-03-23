//ovelse.cpp alex

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <cstring>
#include "OVELSE.H"

using namespace std;

Ovelse::~Ovelse()
{
	delete[] navn;
	//delete deltager array
	//delete resultat array

}

void Ovelse::skrivMeny()
{
	//dummy kode
}

void Ovelse::skrivData()
{
	skriv("ID: ", nr);
	skriv("Fullt navn: ", navn);
	skriv("Dato: ", dato);
	skriv("Klokkeslett: ", klokkeslett);
	skriv("Antall deltagere: ", antDeltagere);

}

void Ovelse::skrivTilFil(ofstream & ut)
{
	

	skriv(ut, nr);
	skriv(ut, dato);
	skriv(ut, klokkeslett);
	skriv(ut, antDeltagere);
	skriv(ut, navn);

//!!!!!!!!!! maa lages!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//deltager array skriv til fil
		//resultat array skriv til fil


}

void Ovelse::lesFraFil(ifstream & inn)
{
	nr = lesInt(inn);
	dato = lesInt(inn);
	klokkeslett = lesInt(inn);
	antDeltagere = lesInt(inn);
	navn = lesTxt(inn);
}
