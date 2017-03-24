//deltagere.cpp

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <cstring>
#include "DELTAGER.H"
#include "DELTAGERE.H"
#include "FUNKSJONER.H"

using namespace std;

Deltagere::Deltagere()
{
	antDeltagere = 0;
	DeltagerListe = new List(Sorted);
}

Deltagere::Deltagere(char* t)
{

}

Deltagere::~Deltagere()
{
	delete DeltagerListe;
}

void Deltagere::skrivMeny()
{
	cout << "\n\nFØLGENDE KOMMANDOER ER TILGJENGELIGE:"
		<< "\n\tN - Registrer ny deltager"
		<< "\n\tE - Endre deltager"
		<< "\n\tA - Skriv hoveddataene om alle deltagere"
		<< "\n\tS - Skriv ut alle data om en deltager"
		<< "\n\tQ - Gå tilbake til hovedmeny";
}

void Deltagere::menyValg()
{
	char valg;

	skrivMeny();
	valg = les("\nDeltagere: ");
	while (valg != 'Q') {
		switch (valg) {
		case 'N': nyDeltager();		break;
		case 'E': endreDeltager();	break;
		case 'A': skrivDataAlle();	break;
		case 'S': skrivDataEn();	break;
		default: skrivMeny();		break;
		}
		skrivMeny();
		valg = les("\nDeltagere: ");
	}
}

void Deltagere::nyDeltager()
{
	int tempId;                               
	Deltager* tempDeltager;
														
	tempId = les("\nSkriv inn id for deltager", 0, 9999);

	if (!DeltagerListe->inList(tempId)) 
	{         
		tempDeltager = new Deltager(tempId);          
		DeltagerListe->add(tempDeltager);                 
	}
	else
	{
		cout << "\n\t" << tempId << " finnes allerede";
	}
	skrivTilFil();
}

void Deltagere::endreDeltager()
{

}

void Deltagere::skrivDataAlle()
{
	Deltager* tempDeltager;                                 
	int antDeltagere = 0;
                               
		antDeltagere = DeltagerListe->noOfElements();     

	for (int i = 1; i <= antDeltagere; i++) {          
		tempDeltager = (Deltager*)DeltagerListe->removeNo(i);   
		tempDeltager->displayHoved();                      
		DeltagerListe->add(tempDeltager);                      
	}
}

void Deltagere::skrivDataEn()
{
	int buffer = 0;
	Deltager *tempDeltager;

	buffer = les("Skriv inn id'en til deltageren", 0, 9999);

	if (DeltagerListe->inList(buffer))
	{
		tempDeltager = (Deltager*)DeltagerListe->remove(buffer);
		tempDeltager->display();
		DeltagerListe->add(tempDeltager);
	}
	else
	{
		skriv("finner ikke deltager med id: ", buffer);
	}
}