//statistikk.cpp

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <cstring>
#include "STATISTIKK.H"

using namespace std;

Statisikk::Statisikk()
{
	sistebrukt = 0;

	//går fra 0 til 200 og steer \0 i første indeksplass
	for (int i = 0; i <= MAXNASJONER + 1; i++)
	{	nasjonsForkort[i][1] = '\0';	}
}


void Statisikk::skrivNasjon(int nr)
{
	skriv("Nasjonsforkortelese: ", nasjonsForkort[nr]);
}
