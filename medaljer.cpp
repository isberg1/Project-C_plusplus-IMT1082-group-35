//medaljer.cpp

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>
#include "MEDALJER.H"
#include "STATISTIKK.H"
#include"FUNKSJONER.H"


using namespace std;

Medaljer::Medaljer()//constructor
{
	for (int i = 0; i <= MAXNASJONER; i++)
	{	medaljer[i] = 0;	} //nullstiller hele arrayen

}
//legg til eller fjern medalje og sorter array
void Medaljer::endreAntMedaljer(char nasjon[], seiersType medaljeType, positivNegativ posNeg)
{
	char temp[MAXNASJONER + 1];
	int dummy;
	bool sjekk = true;
	int teller = 0;

	while (teller < sistebrukt && sjekk)											//lupper til hele arrayen er sjekket
	{
		if (!strcmp(nasjon, nasjonsForkort[++teller]))					//hvis nasjonen alerede er registrer med medaljer
		{
			sjekk = false;																	//avbryter While lupen
								//legg till eller fjern 1 medalje
			if (medaljeType == gull)
			{
				((posNeg == positiv) ? medaljer[teller] += 10000 : medaljer[teller] -= 10000);	//oker/trekker fra 1 gull
			}
			else if (medaljeType == solv)
			{
				((posNeg == positiv) ? medaljer[teller] += 100 : medaljer[teller] -= 100);		//oker/trekker fra 1 solv
			}
			else if (medaljeType == bronsje)
			{
				((posNeg == positiv) ? medaljer[teller] += 1 : medaljer[teller] -= 1);			//oker/trekker fra 1 bronsje
			}

			dummy = medaljer[teller];					//tar kopier av aktuell int og char
			strcpy(temp, nasjonsForkort[teller]);
							//omsorterer arrayer og fjerner det som ble kopiert, sisteBrukt blir ledig til slutt
			omsorter(teller, medaljer);

			medaljer[sistebrukt] = dummy;  //legger int og char tilbake i array helt bakerst
			strcpy(nasjonsForkort[sistebrukt], temp);

			sorter1(medaljer);	//sorterer 2 arrayer, starter fra sisteBrukt
		}
	}

												//hvis nasjon ikke er registert fra for
	if (sjekk && sistebrukt < MAXNASJONER && posNeg == positiv)
	{
		sistebrukt++;
							//adderer paa korekt verdi
		if (medaljeType == gull)
		{	medaljer[sistebrukt] += 10000; 	}											//ook med 1 gull
		else if (medaljeType == solv)
		{	medaljer[sistebrukt] += 100;	}											//ook med 1 solv
		else if (medaljeType == bronsje)
		{	medaljer[sistebrukt] += 1;		}											//ook med 1 bronsje

		strcpy(nasjonsForkort[sistebrukt], nasjon);		//legger til nasjonsforkortelsen helt bakerst i arrayen

		sorter1(medaljer);									//sorterer 2 arrayer, starter fra sisteBrukt
	}

	skrivTilFil();
}


void Medaljer::skrivMedaljer()		//displayer 2 arrayer med data
{
	skriv("Medaljeoversikt sortert hoyest til lavest\n\n", "Nasjonsforkortelse\t Gull\t Solv\tBronsje\n");

	for (int i = 1; i <= sistebrukt; i++)
	{
		cout <<"\t\t"
			<< nasjonsForkort[i]
			<< "\t\t   " << medaljer[i] / 10000							//skriv Gull
			<< "\t  " << (medaljer[i] % 10000) / 100					//skriv Solv
			<< "\t   "  << medaljer[i] % 100							//skriv Bronsje
			<<"\n";
	}
}
		

void Medaljer::skrivTilFil()		//skriv til fil
{

	/*
	filformat:
	int  sistebrukt
	char nasjonsForkortelse
	int  medaljer
	(gjenta * sistebrukt)
	*/

	ofstream ut("MEDALJER.DTA");

	if (ut)																//hvis filen finnes
	{
		skriv(ut, sistebrukt);								//skriv antall i arrayen til fil
		for (int i = 1; i <= sistebrukt; i++)
		{								//skriv alle datamedlemmer til fil
			skriv(ut, nasjonsForkort[i]);
			skriv(ut, medaljer[i]);
		}
	}
	else
	{	skriv("finner ikke fil MEDALJER.DTA", "");	}
}

void Medaljer::lesFraFil()		// les fra fil
{
	/*
	filformat:
	int  sistebrukt
	char nasjonsForkortelse
	int  medaljer
	(gjenta* sistebrukt)
	*/

	ifstream inn("MEDALJER.DTA");

	if (inn)														//hvis filen finnes
	{
		sistebrukt = lesInt(inn);								//les inn antall i array
		for (int i = 1; i <= sistebrukt; i++)
		{								//les inn egne datamedlemmer
			lesTxt2(inn, nasjonsForkort[i]);
			medaljer[i] = lesInt(inn);
		}
	}
	else
	{	cout << "\nFinner ikke filen 'MEDALJER.DTA'";	}
}

