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



Ovelse::Ovelse(registerTidPoeng typeMaaling)		//constructor    får parameter sisteOvelse fra Gren
{
	nr = lagUniktNr();						// faar en unikt nummer basert på static int navnTeller
	maaling = typeMaaling;													//faar enumen fra Gren
																		//les inn egene datamedlemer
	antDeltagere = les("Skriv inn antall deltagere i ovelsen. ", MINDELTAGERE, MAXDELTAGERE);


	deltagerListe = new int[MAXDELTAGERE + 1];			//setter deltagerListe peker til en int array
	resultatListe = new int[MAXDELTAGERE + 1];			//setter resultatListe peker til en int array


	for (int i = 0; i <= ANTALLVINNERE + 1; i++)
	{	log[i] = 0; 	}											//nullstiller log arryaen
}

Ovelse::~Ovelse()	//destructor
{
	delete[] navn;
	delete[] deltagerListe;
	delete[] resultatListe;
}

void Ovelse::skrivData()	//Displayer egne datamedlemmer
{
	skriv("ID: ", nr);
	skriv("Fullt navn: ", navn);
	skriv("Dato: ", dato);
	skriv("Klokkeslett: ", klokkeslett);
	skriv("Antall deltagere: ", antDeltagere);
}

char * Ovelse::filNavn(int type)		//send med 1 for .RES eller ingenting for .STA
{
		char name[11] = "OV";
		char end[5] = ".STA";
		char* middle;
		stringstream strs;
		string buffer;

		if (type == 1)					//avhengi av medsent arg.  er 1 eller den statisk satte verdien 0
		{	strcpy(end, ".RES");	}	//saa blir slutten entn .RES eller .STA

					//konverterer int "nr til String
		strs << nr;								//Ovelse sitt unike nr brukkes til delen xxxx i filnavnet
		buffer = strs.str();
		middle = (char*)buffer.c_str();
						//limmer sammen de 3 delende av filnavnet

		strcat(name, middle);
		strcat(name, end);

		return name;													//returnerer det unike filnavnet
}

void Ovelse::skrivTilFil(ofstream & ut)
{
				//skriver egne datamedlemmer til fil
	skriv(ut, nr);
	skriv(ut, dato);
	skriv(ut, klokkeslett);
	skriv(ut, antDeltagere);
	skriv(ut, navn);
	skriv(ut, navnTeller);

//!!!!!!!!!! maa lages!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//deltager array skriv til fil
		//resultat array skriv til fil
}

void Ovelse::lesFraFil(ifstream & inn)
{
				//leser egne datamedlemmer fra fil
	nr = lesInt(inn);
	dato = lesInt(inn);
	klokkeslett = lesInt(inn);
	antDeltagere = lesInt(inn);
	navn = lesTxt(inn);
	navnTeller = lesInt(inn);


	//!!!!!!!!!! maa lages!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//deltager array les fra fil
	//resultat array les fra fil
}

int Ovelse::lagUniktNr() //returnerer et unikt tall til datamedlemm "nr"
{
	return (++navnTeller);	//advarsel ma aldri telles ned
}

//leser inn gyldige verdier til resultatliste
int Ovelse::skaffVerdi()
{
	int min, sec, tidel, hundredel,tusendel, poengX, poengXX;

	//hvis en deltager har brutt, ikke moott eller blit disket saa skal det tastes - 1):",

	if (maaling== MinSECTidel)
	{
		min = les("Skriv resultat i minutter: ", -1, 120);
		if (min != -1)
		{
			sec = les("Skriv resultat i sekunder: ", -1, 59);
			tidel = les("Skriv resultat i tidelssekunder: ", -1, 9);
			return ((min * 1000) + (sec * 10) + tidel); 					// maxverdi 120 59 9
		}
	}
	else if (maaling== MinSecHundredel)
	{
		min = les("Skriv resultat i minutter: ", -1, 120);
		if (min != -1)
		{
			sec = les("Skriv resultat i sekunder: ", -1, 59);
			hundredel = les("Skriv resultat i hundredelssekunder: ", -1, 99);
			return ((min * 10000) + (sec * 100) + hundredel); 					// maxverdi 120 59 99
		}
	}
	else if (maaling== MinSekTusendel)
	{
		min = les("Skriv resultat i minutter: ", -1, 120);
		if (min != -1)
		{
			sec = les("Skriv resultat i sekunder: ", -1, 59);
			tusendel = les("Skriv resultat i tusendelssekunder: ", -1, 999);
			return ((min * 100000) + (sec * 1000) + tusendel); 					// maxverdi 120 59 999
		}
	}
	else if (maaling== PoengX)
	{
		poengX = les("Skriv resultat i minutter: ", -1, 9);
		return poengX;															// maxverdi 9
	}
	else if (maaling== PoengXX)
	{
		poengXX = les("Skriv resultat i minutter: ", -1, 99);
		return PoengXX;															// maxverdi 99
	}

	return -1;
}

int Ovelse::hentId()
{
	return nr;
}

void Ovelse::menyValgDelListe()						// ValgSwitch for deltagerLister.
{
	char valg;

	skrivDelListeMeny();
	valg = les("\nDeltagerLister ");
	while (valg != 'Q')
	{
		switch (valg)
		{
		case 'S': skrivDelListe();	    break;		// Skriver ut en deltagerListe.
		case 'N': nyDelListe();			break;		// Lager en ny deltagerListe.
		case 'E': endreDelListe();		break;		// Endrer en deltagerListe.
		case 'F': fjernDelListe();		break;		// Fjerner en deltagerListe.
		default:		break;
		}
		skrivDelListeMeny();
		valg = les("\nDeltagerLister: ");
	}
}

void Ovelse::skrivDelListeMeny()					// KommandoMeny for deltagerLister.
{
	cout << "\n\nFOLGENDE KOMMANDOER ER TILGJENGELIGE:"
		<< "\n\tS - Skriv ut deltagerliste"
		<< "\n\tN - Lag ny deltagerliste"
		<< "\n\tE - Endre deltagerliste"
		<< "\n\tF - Fjern deltagerliste"
		<< "\n\tQ - Tilbake til ovelsemeny";
}

void Ovelse::skrivDelListe()
{

}

void Ovelse::nyDelListe()
{

}

void Ovelse::endreDelListe()
{

}

void Ovelse::fjernDelListe()
{

}

void Ovelse::menyValgResListe()						// ValgSwitch for resultatLister.
{
	char valg;

	skrivResListeMeny();
	valg = les("\nResultatLister: ");
	while (valg != 'Q')
	{
		switch (valg)
		{
		case 'S': skrivResListe();		break;		// Skriver ut en resultatListe.
		case 'N': nyResListe();			break;		// Lager en ny resultatListe.
		case 'F': fjernResListe();		break;		// Fjerner en resultatListe.
		default:						break;
		}
		skrivResListeMeny();
		valg = les("\nResultatlister: ");
	}
}

void Ovelse::skrivResListeMeny()					// KommandoMeny for resultatLister.
{
	cout << "\n\nFOLGENDE KOMMANDOER ER TILGJENGELIGE:"
		<< "\n\tS - Skriv ut resultatliste"
		<< "\n\tN - Ny resultatliste"
		<< "\n\tF - Fjern resultatliste"
		<< "\n\tQ - Tilbake til ovelsemeny";
}

void Ovelse::skrivResListe()
{

}

void Ovelse::nyResListe()
{
	ifstream inn(filNavn(0));
	ofstream ut(filNavn(1));

	if (inn)																//hvis en deltagerliste finnes
	{
		if (!ut)														//hvis en resultatliste ikke finnes
		{

			skriv("Skriv in resultater (hvis en deltager har brutt, ikke moott eller blit disket tast -1):", "");
			for (int i = 1; i <= antDeltagere; i++)
			{
				skriv("Skriv inn resutatet for deltager: ", *(deltagerListe + i));
				skaffVerdi();
			}

		}
		else
		{		//lukk filer og skriv ut feilmelding			//noe usikker paa denne				//$$$$$$$$$$$$ ma testes
			ut.close();
			inn.close();
			skriv("Resultatlisten finnes alerede!", "");
		}
	}
	else
	{			//lukk filer og skriv ut feilmelding			//noe usikker paa denne				//$$$$$$$$$$$$ ma testes
		ut.close();
		inn.close();
		skriv("Deltagerlisten finnes ikke! lag den foor Resultatliste", "");
	}
}

void Ovelse::fjernResListe()
{

}
