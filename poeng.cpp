//poeng.cpp

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <cstring>
#include "POENG.H"
#include"FUNKSJONER.H"

using namespace std;

Poeng::Poeng()
{
	for (int i = 0; i <= MAXNASJONER; i++)
	{	poeng[i] = 0;	}
}

void Poeng::endreAntPoeng(char nasjon[], int antPoeng, positivNegativ posNeg)
{
	char temp[MAXNASJONER + 1];
	int dummy;
	bool sjekk = true;
	int teller = 0;

	while (teller < sistebrukt && sjekk) //lupper til hele arrayen er sjekket
	{
		if (!strcmp(nasjon, nasjonsForkort[++teller])) //hvis nasjonen alerede er registrer med medaljer
		{
			sjekk = false;											//avbryter While lupen

			((posNeg == positiv) ? poeng[teller] += antPoeng : poeng[teller] -= antPoeng);
																	
			sorter(poeng);

			//hvis en nasjon ikke lenger har noen poeng
			if (poeng[sistebrukt] == 0 && nasjonsForkort[sistebrukt][0] != '\0')
			{							//slett nasjonen fra listen og tell ned "sistebrukt"
				nasjonsForkort[sistebrukt][0] = '\0';
				sistebrukt--;
			}
		}
	}


	if (sjekk && sistebrukt < MAXNASJONER && posNeg == positiv)	//hvis nasjon ikke er registert fra for
	{
		sistebrukt++;

		poeng[sistebrukt] = antPoeng;
		strcpy(nasjonsForkort[sistebrukt], nasjon);
		//legger til nasjonsforkortelsen helt bakerst i arrayen

		sorter(poeng);
	}

	skrivTilFil();
}

void Poeng::skrivPoeng()
{
	
	skriv("Poengoversikt sortert høyest til lavest\n\n", "Nasjonsforkortelse\tPoeng");

	for (int i = 1; i <= sistebrukt; i++)
	{
		cout << "\t" << nasjonsForkort[i] << "\t\t\t   " << poeng[i] << "\n";
	}

}

void Poeng::testFunksjon()
{

	//int antNasj;
	int dummy;
	positivNegativ posNeg;
	int antallPoeng = 0;
	char temp[MAXNASJONER + 1];
	char type;
	skriv("skriv statistikk vedier", "");



	while (les("skriv: ") != 'Q')
	{
		cout << "\nlegge til(+) eller trekke fra(-)\t";
		type = les();
		antallPoeng = les("skriv", 1, 7);
		les("skriv nasjonsforkortelse: ", temp, MAXNASJONER);

		if (type == '+')
		{
			posNeg = positiv;
		}
		else
		{
			posNeg = negativ;
		}

		endreAntPoeng(temp, antallPoeng, posNeg);
		skrivPoeng();
	}

}

void Poeng::skrivTilFil()
{
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

void Poeng::lesFraFil()
{
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
	{	skriv("finner ikke fil POENG.DTA", "");  }
}
