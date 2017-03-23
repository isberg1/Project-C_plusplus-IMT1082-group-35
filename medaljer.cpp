//medaljer.cpp

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <cstring>
#include "MEDALJER.H"
#include "STATISTIKK.H"

using namespace std;

Medaljer::Medaljer()//constructor
{
	for (int i = 0; i <= MAXNASJONER+1; i++)
	{	medaljer[i] = 0;	} //nullstiller hele arrayen 

}
//leg til ny medalje og sorter arry
void Medaljer::nyMedalje(char nasjon[], seiersType, int antall)
{
	char temp[4];
	int dummy;
	bool sjekk = true;
	int teller = 0;


	while (teller <= sistebrukt && sjekk) //lupper til hele arrayen er sjekket
	{								
		if (!strcmp(nasjon, nasjonsForkort[++teller])) //hvis nasjonen alerede er registrer med medaljer
		{
			sjekk = false;							//avbryter While lupen
			//tar kopier av aktuell int og char
			dummy = medaljer[teller];
			strcpy(temp, nasjonsForkort[teller]);
			omsorter(teller); //omsorterer arrayer og fjerner det som ble kopiert, sisteBrukt blir ledig til slutt

			if		(medaljeType == gull) //adderer paa korekt verdi
			{	dummy += 10000;		}
			else if (medaljeType == solv)
			{	dummy += 100;		}
			else if (medaljeType == bronsje)
			{	dummy += 1;			}

			medaljer[sistebrukt] = dummy;  //leger int og char tilbake i array helt bakerst
			strcpy(nasjonsForkort[sistebrukt], temp);

			sorter();//sorterer arrayen starter fra sisteBrukt
		}
	}

	if (sjekk && sistebrukt < MAXNASJONER)	//hvis nasjon ikke er registert fra for
	{
		if (medaljeType == gull)					//adderer paa korekt verdi
		{	medaljer[++sistebrukt] += 10000;	}
		else if (medaljeType == solv)
		{	medaljer[++sistebrukt] += 100;	}
		else if (medaljeType == bronsje)
		{	medaljer[++sistebrukt] += 1;		}
								//legger til nasjonsforkortelsen helt bakerst i arrayen
		strcpy(nasjonsForkort[++sistebrukt], nasjon);
		sorter();	//sorterer arrayen starter fra sisteBrukt
	}
}

void Medaljer::sorter()
{
}

void Medaljer::omsorter(int teller)		//!!!!!!!!!!utestet!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{		//flytter verien i en idex ett hakk oppover, nullstiller verdien i index sistebrukt
	for (int i = teller; i <= sistebrukt; i++)
	{
		medaljer[teller] = medaljer[teller + 1];
		strcpy(nasjonsForkort[teller], nasjonsForkort[teller + 1]);
	}
	medaljer[sistebrukt] = 0;
	strcpy(nasjonsForkort[sistebrukt], '\0');	
}
