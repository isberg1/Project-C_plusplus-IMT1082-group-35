//ovelse.cpp alex

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>
#include <sstream>
#include <string.h>
#include "OVELSE.H"
#include"ENUM.H"

using namespace std;



Ovelse::Ovelse(int sisteOvelse)		//constructor    får parameter sisteOvelse fra Grener
{
	nr = sisteOvelse;	// faar et datamedlem som medsendt parameter
						//les inn egene datamedlemer
	antDeltagere = les("Skriv inn antall deltagere i ovelsen. ", MINDELTAGERE, MAXDELTAGERE);
	//endreOvelse()  //samme funksjon som kjores til valg  O E

	deltagerListe = new int[MAXDELTAGERE + 1];  //setter deltagerListe peker til en int array
	resultatListe = new int[MAXDELTAGERE + 1];	//setter resultatListe peker til en int array
}

Ovelse::~Ovelse()
{
	delete[] navn;
	delete[] deltagerListe;
	delete[] resultatListe;
}

void Ovelse :: skrivMeny() {

}

void Ovelse::skrivData()
{
	skriv("ID: ", nr);
	skriv("Fullt navn: ", navn);
	skriv("Dato: ", dato);
	skriv("Klokkeslett: ", klokkeslett);
	skriv("Antall deltagere: ", antDeltagere);

}

char * Ovelse::filNavn(int type)		//send med 1 for .RES ellern none annet for .STA
{
		char name[11] = "OV";
		char end[5];
		char* middle;
		stringstream strs;
		string buffer;

		if (type == 1)		//avhengi av medsent arg. saa blir slutten entn .RES eller .STA
		{	strcpy(end, ".RES");	}
		else
		{	strcpy(end, ".STA");	}

		strs << nr;		//Ovelse sitt unike nr brukkes til delen xxxx i filnavnet
		buffer = strs.str();
		middle = (char*)buffer.c_str();

		strcat(name, middle);
		strcat(name, end);

		return name;
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

void Ovelse::nyResultatListe()
{

}
