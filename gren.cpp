//gren.cpp

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <cstring>
#include "GREN.H"
#include"FUNKSJONER.H"
using namespace std;

Gren::Gren() 
{
	cout << "\nAdvarsel GrenConstructor uten arg, skal ikke brukes\n";
}

Gren::Gren(char * a) : TextElement(a)
{
	char buffer[STRLEN];
	int tilEnum;
	
	antOvelser = les("Skriv antall ovelser: ", 1, MAXOVELSER);

	cout << "\nskriv type maaling: "
		<< "\n(1) MinSECTidel"
		<< "\n(2) MinSecHundredel"
		<< "\n(3) MinSekTusendel"
		<< "\n(4) PoengX"
		<< "\n(5) PoengXX";
	tilEnum = les("skriv type (1),(2),(3),(4),(5)", 1, 5);

	switch (tilEnum)
	{			//usikker på hva "antSifre" skal brukens til
	case 1:	typeMaaling = MinSECTidel;		antSifre = 6; break;
	case 2: typeMaaling = MinSecHundredel;	antSifre = 7; break;
	case 3:	typeMaaling = MinSekTusendel;	antSifre = 8; break;
	case 4: typeMaaling = PoengX;			antSifre = 1; break;
	case 5:	typeMaaling = PoengXX;			antSifre = 2; break;
	}

	les("Skriv in annet: ", buffer, STRLEN);
	annet = konverter(buffer);
}

Gren::~Gren()
{ 
	delete[] annet;
}

void Gren::endreNavn(char *navn)
{
	delete text;
	text = konverter(navn);
}

void Gren::skrivData()
{
	skriv("Grenens navn er: ", text);
	skriv("antall ovelser er:", antOvelser);
	skriv("Annet: ", annet);

	
	if (typeMaaling == MinSECTidel)
	{	skriv("MinSECTidel", " ");		}
	if (typeMaaling == MinSecHundredel)
	{	skriv("MinSecHundredel", " ");	}
	if (typeMaaling == MinSekTusendel)
	{	skriv("MinSekTusendel", " ");	}
	if (typeMaaling == PoengX)
	{	skriv("PoengX", " ");			}
	if (typeMaaling == PoengXX)
	{	skriv("PoengXX", " ");			}
}

void Gren::skrivOvelse()
{
	for (int i = 1; i <= antOvelser; i++)
	{	array[i].skrivData();	}
}

void Gren::skrivTilFIl(ofstream & ut)
{
	/*
	//navn lagres i TextElement
	registerTidPoeng typeMaaling;
	int antOvelser;
	int antSifre;
	
	Ovelse array[MAXOVELSER + 1];
	char *annet;
	*/

	skriv(ut, text);
	skriv(ut, annet);
	skriv(ut, antOvelser);
	skriv(ut, antSifre);

	
	if (typeMaaling == MinSECTidel)
	{	skriv(ut, 0);   }
	if (typeMaaling == MinSecHundredel)
	{	skriv(ut, 1);	}
	if (typeMaaling == MinSekTusendel)
	{	skriv(ut, 2);	}
	if (typeMaaling == PoengX)
	{	skriv(ut, 3);	}
	if (typeMaaling == PoengXX)
	{	skriv(ut, 4);	}

	for (int i = 1; i <=antOvelser; i++)
	{
		array[i].skrivTilFil(ut);
	}
}
