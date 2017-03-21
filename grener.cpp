//grener.cpp


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <cstring>
#include "GRENER.H"
#include"FUNKSJONER.H"
#include"CONST.H"
#include"GREN.H"
#include"ListTool2B.h"



using namespace std;

Grener::Grener()
{
	sisteOvelse = 0;
	listGren = new List(Sorted);
}

Grener::~Grener()
{
	delete listGren;
	listGren = nullptr;
}
void Grener::skrivMeny()
{
	char valgGrener = 'A';

	do
	{
		cout << "\n(N) Ny gren"
			<< "\n(E) Endre gren"
			<< "\n(A) Display alle grener"
			<< "\n(S) Display en gren"
			<< "\n(T) Tilbake til hovedmeny\n";
		valgGrener = les();

		switch (valgGrener)
		{
		case 'N':	nyGren();			break;
		case 'E':	endreGren();		break;
		case 'A':	skrivAllGrener();	break;
		case 'S':	skrivEnGren();		break;
		default:						break;
		}

	} while (valgGrener != 'T');

}

void Grener::nyGren()
{
	char buffer[NVLEN];
	Gren *temp;
	
	les("Skriv unikt navn: ", buffer, NVLEN);
	if (!listGren->inList(buffer))
	{
		temp = new Gren(buffer);
		listGren->add(temp);
		skriv("Ny gren registrert med navn: ", buffer);
	}
	else
	{	skriv(buffer, "er alerede i bruk"); 	}


}

void Grener::endreGren()
{
	char buffer[NVLEN];
	Gren *temp;

	les("Skriv unikt navn: ", buffer, NVLEN);

	if (listGren->inList(buffer))
	{
		temp=(Gren*) listGren->remove(buffer);
		temp->endreNavn(buffer);
		listGren->add(temp);

	}
}

void Grener::skrivAllGrener()
{
	Gren *temp;

	if (!listGren->isEmpty())
	{
		for (int i = 1; i <= listGren->noOfElements(); i++)
		{
			temp = (Gren*)listGren->remove(i);
			temp->skrivData();
			listGren->add(temp);
		}
		
	}


}

void Grener::skrivEnGren()
{
	char buffer[NVLEN];
	Gren *temp;

	les("Skriv navnet på genen: ", buffer, NVLEN);

	if (listGren->inList(buffer))
	{
		temp = (Gren*)listGren->remove(buffer);
		temp->skrivOvelse();
		listGren->add(temp);
	}
	else
	{	skriv("finner ikke gren med navn: ", buffer);	}
}

void Grener::skrivTilFIl()
{
	ofstream ut("GRENER.DTA");
	Gren *ptr;

	int antalIListe = listGren->noOfElements();
	skriv(ut, antalIListe);
	skriv(ut, sisteOvelse);

	for (int i = 1; i <= antalIListe; i++)
	{
		ptr = (Gren*)listGren->removeNo(i);
		ptr->skrivTilFIl(ut);
		listGren->add(ptr);	}

}



