//deltager.cpp

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif 

#include <iostream>
#include <cstring>
#include <fstream>
#include "DELTAGER.H"
#include "CONST.H"

using namespace std;

Deltager::Deltager()
{
	cout << "\nDet har skjedd en feil! Deltager-objekter skal ikke lages uten parametre!";
}

Deltager::Deltager(int in) : NumElement(in)
{
	
}
/*
Deltager::~Deltager()						
{
//		foreløpig ubrukt		//
}
*/
void Deltager::endreInfo()
{


}

void Deltager::display()		
{
	
}

void Deltager::displayHoved()
{
	cout << "\nDeltagers id: " << 	number
		<< "\nDeltagers navn: " << fullNavn
		<< "\nDeltagers nasjon(id)" << nasjon;
}