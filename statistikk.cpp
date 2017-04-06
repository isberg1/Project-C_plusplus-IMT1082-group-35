//statistikk.cpp

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>
#include "STATISTIKK.H"

using namespace std;



Statisikk::Statisikk()		//constructor
{
	sistebrukt = 0;

	//går fra 0 til 200 og setter '\0' i første indeksplass
	for (int i = 0; i <= MAXNASJONER + 1; i++)
	{	nasjonsForkort[i][0] = '\0';	}
}

void Statisikk::sorter1(int array[])		//sorterer en char array og en int array paa en gang
{
	int teller = sistebrukt;
	int dummy;
	char temp[MAXNASJONER + 1];

												//sorter arrayen etter størst først
	while (teller > 1 && array[teller] > array[teller - 1])
	{						//ta den første ut av arryen
		dummy = array[teller - 1];
		strcpy(temp, nasjonsForkort[teller - 1]);
									//flytt den under ett hakk opp
		array[teller - 1] = array[teller];
		strcpy(nasjonsForkort[teller - 1], nasjonsForkort[teller]);
						//sett den første ett hakk ned
		array[teller] = dummy;
		strcpy(nasjonsForkort[teller], temp);

		teller--;													//tell ned
	}
										//hvis en nasjon ikke lenger har noen medaljer/ poeng
	if (array[sistebrukt] == 0 )
	{							//slett nasjonen fra listen og tell ned "sistebrukt"
		nasjonsForkort[sistebrukt][0] = '\0';
		sistebrukt--;
	}
}

void Statisikk::omsorter(int teller, int array[])
{		//flytter verdien i en idex ett hakk oppover, nullstiller verdien i index sistebrukt
	for (int i = teller; i < sistebrukt; i++)
	{										//flytt den under ett hakk opp
		array[i] = array[i + 1];
		strcpy(nasjonsForkort[i], nasjonsForkort[i + 1]);
	}
							//nullstill den ledige plassen
	array[sistebrukt] = 0;
	nasjonsForkort[sistebrukt][0] = '\0';


}
