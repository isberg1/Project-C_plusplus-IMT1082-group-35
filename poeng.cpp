/*
    poeng.cpp
    Klassefunksjoner Poeng
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>
#include "POENG.H"
#include"FUNKSJONER.H"

using namespace std;



Poeng::Poeng()		//constructor
{
	for (int i = 0; i <= MAXNASJONER; i++)	//nullstiller hele arrayen
	{	poeng[i] = 0;	}
}

void Poeng::endreAntPoeng(char nasjon[], int antPoeng, positivNegativ posNeg)	//endre en nasjons antall poeng
{
	char temp[MAXNASJONER + 1];
	int dummy;
	bool sjekk = true;
	int teller = 0;

	while (teller < sistebrukt && sjekk)							//lupper til hele arrayen er sjekket
	{
		if (!strcmp(nasjon, nasjonsForkort[++teller]))				//hvis nasjonen alerede er registrer med poeng
		{
			sjekk = false;												//avbryter While lupen
							//tar kopier av aktuell int og char
			dummy = poeng[teller];
			strcpy(temp, nasjonsForkort[teller]);
												//legg til eller trekk fra "antPoeng" fra riktik posisjon i poeng array
			((posNeg == positiv) ? dummy += antPoeng : dummy -= antPoeng);
									//omsorterer arrayer og fjerner det som ble kopiert, sisteBrukt blir ledig til slutt
			omsorter(teller, poeng);

			poeng[sistebrukt] = dummy;									//legger int og char tilbake i array helt bakerst
			strcpy(nasjonsForkort[sistebrukt], temp);

			sorter1(poeng);													//sorterer 2 arrayer, starter fra sisteBrukt
		}
	}

	if (sjekk && sistebrukt < MAXNASJONER && posNeg == positiv)					//hvis nasjon ikke er registert fra før
	{
		sistebrukt++;

		//legger til nasjonsforkortelsen og poeng helt bakerst i arrayen
		poeng[sistebrukt] = antPoeng;
		strcpy(nasjonsForkort[sistebrukt], nasjon);

		sorter1(poeng);					//sorterer 2 arrayer
	}
	skrivTilFil();						//skriv til fil
}

void Poeng::skrivPoeng()	//displayer 2 arrayer
{

	skriv("Poengoversikt sortert hoyest til lavest\n\n", "Nasjonsforkortelse\tPoeng\n");

	for (int i = 1; i <= sistebrukt; i++)
	{
		cout << "\t\t" << nasjonsForkort[i] << "\t\t  " << poeng[i] << "\n";
	}
}

void Poeng::skrivTilFil()		//skriv til fil
{

	/*
	filformat:
	int  sistebrukt
	char nasjonsForkortelse
	int  medaljer
	(gjenta* sistebrukt)
	*/

	ofstream ut("POENG.DTA");

	if (ut)
	{
		skriv(ut, sistebrukt);
		for (int i = 1; i <= sistebrukt; i++)
		{
			skriv(ut, nasjonsForkort[i]);
			skriv(ut, poeng[i]);
		}
	}
	else
	{	skriv("finner ikke fil POENG.DTA", ""); 	}
}

void Poeng::lesFraFil()		//les fra fil
{
	/*
	filformat:
	int  sistebrukt
	char poeng
	int  medaljer
	(gjenta* sistebrukt)
	*/


	ifstream inn("POENG.DTA");

	if (inn)
	{
		sistebrukt = lesInt(inn);
		for (int i = 1; i <= sistebrukt; i++)
		{
			lesTxt2(inn, nasjonsForkort[i]);
			poeng[i] = lesInt(inn);
		}
	}
	else
	{	cout << "\nFinner ikke filen 'POENG.DTA'";  }
}
