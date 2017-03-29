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
	skriv("Antall ovelser er:", antOvelser);
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

void Gren :: skrivGrenNavn() {						// Skriver ut navnet på grenen.
  cout << '\t' << text;
}

int Gren::hentAntalOvelser()
{
	return antallRegistrerteOvelser;
}

void Gren::menyValgOvelse()							// MainSwitch for Ovelse.
{
	char valg;

	skrivOvelseMeny();
	valg = les("\nOvelser: ");
	while (valg != 'Q')
	{
		switch (valg)
		{
		case 'N': nyOvelse();		 break;			// Registrerer en ny Ovelse.
		case 'E': endreOvelse();	 break;			// Endrer informasjon i ne Ovelse.
		case 'F': fjernOvelse();	 break;			// Fjerner en Ovelse.
		case 'A': skrivAlleOvelse(); break;			// Viser hoveddata for alle Ovelser.
		case 'L': ovelseDelMeny();	 break;			// Sender til deltagerListeSwitch.
		case 'R': ovelseResMeny();	 break;			// Sender til resultatListeSwitch.
		default:		break;
		}
		skrivOvelseMeny();
		valg = les("\novelser: ");
	}
}

void Gren::skrivOvelseMeny()						// KommandoMeny for Ovelser.
{
	cout << "\n\nFOLGENDE KOMMANDOER ER TILGJENGELIGE:"
		<< "\n\tN - Ny ovelse"
		<< "\n\tE - Endre ovelse"
		<< "\n\tF - Fjern ovelse"
		<< "\n\tA - Skriv ut alle ovelser"
		<< "\n\tL - Deltagerliste"
		<< "\n\tR - Resultatliste"
		<< "\n\tQ - Tilbake til hovedmeny";
}

void Gren::nyOvelse()
{
	Ovelse::Ovelse(typeMaaling);
}

void Gren::endreOvelse()
{

}

void Gren::fjernOvelse()
{

}

void Gren::skrivAlleOvelse()
{

}

void Gren::ovelseDelMeny()
{
	int buffer, temp;

	Gren::skrivAlleOvelse();
	buffer = les("\n\tSkriv inn IDen til ovelsen du onsker a finne", 1000, 9999);

	for (int i = 0; i < antallRegistrerteOvelser; i++)
	{
		temp = array[i]->hentId();
		if (temp == buffer)
		{
			array[i]->menyValgDelListe();
		}
	}
}

void Gren::ovelseResMeny()
{
	int buffer, temp;

	Gren::skrivAlleOvelse();
	buffer = les("\n\tSkriv inn IDen til ovelsen du onsker a finne", 1000, 9999);

	for (int i = 0; i < antallRegistrerteOvelser; i++)
	{
		temp = array[i]->hentId();
		if (temp == buffer)
		{
			array[i]->menyValgResListe();
		}
	}
}