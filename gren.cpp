//gren.cpp alex

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <cstring>
#include "GREN.H"
#include"FUNKSJONER.H"
using namespace std;

Gren::Gren() 	//constructor uten arg.
{
	cout << "\nAdvarsel GrenConstructor uten arg, skal ikke brukes\n";
}
//constructor med string argument
Gren::Gren(char * a) : TextElement(a)
{
	char buffer[STRLEN];
	int tilEnum;
	//leser inn egne datamedlemmer
	antOvelser = les("Skriv antall ovelser: ", 1, MAXOVELSER);
	antallRegistrerteOvelser = 0;

	cout << "\nskriv type maaling: "
		<< "\n(1) MinSECTidel"
		<< "\n(2) MinSecHundredel"
		<< "\n(3) MinSekTusendel"
		<< "\n(4) PoengX"
		<< "\n(5) PoengXX";
	tilEnum = les("\nskriv type (1),(2),(3),(4),(5)", 1, 5);

	switch (tilEnum)
	{//usikker på hva "antSifre" skal brukens til bare gjetter her
	case 1:	typeMaaling = MinSECTidel;		antSifre = 6; break;
	case 2: typeMaaling = MinSecHundredel;	antSifre = 7; break;
	case 3:	typeMaaling = MinSekTusendel;	antSifre = 8; break;
	case 4: typeMaaling = PoengX;			antSifre = 1; break;
	case 5:	typeMaaling = PoengXX;			antSifre = 2; break;
	}

	les("Skriv inn annet: ", buffer, STRLEN);
	annet = konverter(buffer);
}
//constructor med filargument
Gren::Gren(ifstream & inn, char * a) : TextElement(a)
{
	int tilEnum;

	//leser inn egne datamedlemer
	annet = lesTxt(inn);
	antOvelser = lesInt(inn);
	antSifre = lesInt(inn);
	antallRegistrerteOvelser = lesInt(inn);
	tilEnum = lesInt(inn);
	
	switch (tilEnum)//konverterer int fra fil til enum
	{
	case 1:	typeMaaling = MinSECTidel;		 break;
	case 2: typeMaaling = MinSecHundredel;	 break;
	case 3:	typeMaaling = MinSekTusendel;	 break;
	case 4: typeMaaling = PoengX;			 break;
	case 5:	typeMaaling = PoengXX;			 break;
	}

	if (antOvelser > 0) //hvis det er registrert noen ovelser i det hele tatt
	{
		
		//leser inn ovelser fra fil
		for (int i = 1; i <= antallRegistrerteOvelser; i++)
		{
			 array[i]->lesFraFil(inn); 
		}
	}
}
//destructor
Gren::~Gren()
{ 	
	delete[] annet; 
	for (int i = 1; i <= antOvelser; i++)
	{	delete array[i];	}	//sletter alle Ovelsesobjekter 

}

void Gren::endreNavn()// til komado G E
{//sletter exsisterende navn først og så hentes et nytt navn
	char buffer[NVLEN];

	les("Skriv nytt unikt navn: ", buffer, NVLEN);
	delete []text;
	text = konverter(buffer);
}
//skriver alle data om denne grenen
void Gren::display()	//til komando G A
{
	skriv("Grenens navn er: ", text);
	skriv("antall ovelser er:", antOvelser);
	skriv("Annet: ", annet);

	
	if (typeMaaling == MinSECTidel)
	{	skriv("Maalingstype er: ","MinSECTidel");		}
	if (typeMaaling == MinSecHundredel)
	{	skriv("Maalingstype er: ","MinSecHundredel");	}
	if (typeMaaling == MinSekTusendel)
	{	skriv("Maalingstype er: ","MinSekTusendel");	}
	if (typeMaaling == PoengX)
	{	skriv("Maalingstype er: ","PoengX");			}
	if (typeMaaling == PoengXX)
	{	skriv("Maalingstype er: ","PoengXX");			}
}
//skriver alle data om alle ovelser
void Gren::skrivOvelse()//til komando G S
{
	for (int i = 1; i <= antallRegistrerteOvelser; i++)
	{	array[i]->skrivData();	}
}
//til fil
void Gren::skrivTilFIl(ofstream & ut)
{
	//skriver egne datamedlemmer til fil
	skriv(ut, text);	//navnet
	skriv(ut, annet);
	skriv(ut, antOvelser);
	skriv(ut, antSifre);
	skriv(ut, antallRegistrerteOvelser);

	//skriver enum til fil som en int mellom 0 til 4
	if (typeMaaling == MinSECTidel)
	{	skriv(ut, 1);   }
	if (typeMaaling == MinSecHundredel)
	{	skriv(ut, 2);	}
	if (typeMaaling == MinSekTusendel)
	{	skriv(ut, 3);	}
	if (typeMaaling == PoengX)
	{	skriv(ut, 4);	}
	if (typeMaaling == PoengXX)
	{	skriv(ut, 5);	}

	if (antallRegistrerteOvelser > 0) //hvis det er registrer noen ovelser i det hele tatt
	{
		//skriver ovelsesobjekter til fil
		for (int i = 1; i <= antallRegistrerteOvelser; i++)
		{	array[i]->skrivTilFil(ut);	}
	}
	
}

int Gren::hentAntalOvelser()
{
	return antallRegistrerteOvelser;
}
