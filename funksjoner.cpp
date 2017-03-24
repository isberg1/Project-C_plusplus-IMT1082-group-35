/*
    funksjoner.cpp
    Globale funksjoner
*/
////////////////////////////////////////////////////:://///////////////////////////////

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif



#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */
#include"CONST.H"
#include "FUNKSJONER.H"
using namespace std;


char les() {			                            //  Henter ett ikke-blankt upcaset tegn:
	char ch;
	cin >> ch;   cin.ignore();                      //  Leser ETT tegn. Forkaster '\n'.
	return (toupper(ch));                           //  Upcaser og returnerer.
}


char les(char *menyPlass) {			                // Henter ett ikke-blankt upcaset tegn:
	char ch;
	cout << menyPlass;                              // Skriver ut menyplass.
	cin >> ch;   cin.ignore();                      // Leser ETT tegn. Forkaster '\n'.
	return (toupper(ch));                           // Upcaser og returnerer.
}

                                                    //  Leser et tall i et visst intervall:
int les(const char t[], const int min, const int max) {
	int i;
	char buffer[256];
	do {                                            // Skriver ledetekst:
		cout << '\t' << t << " (" << min << '-' << max << "): ";
		fgets(buffer, 256, stdin);
		i = atoi(buffer);
	} while (i < min || i > max);                   // Sjekker at i lovlig intervall.
	return i;                                       // Returnerer innlest tall.
}

void les(const char t[], char s[], const int LEN)
{
	do {
		cout << '\t' << t << ": ";	cin.getline(s, LEN);//Ledetekst og leser.
	} while (strlen(s) == 0);						 //Sjekker at tekstlengden er ulik 0.
}

                                                    // konverterer og returnerer char [] til char*
char *konverter(char t[]) {
	char *string;

	string = new char[strlen(t) + 1];               //konverterer char array til char *
	strcpy(string, t);
	return string;
}


void MainMeny()
{
	cout << "\nHovedmeny \nMulige brukervalg"
		<< "\n(N) Nasjoner"
		<< "\n(D) Deltagere"
		<< "\n(G) Grener"
		<< "\n(O) Ovelse"
		<< "\n(M) Medaljer"
		<< "\n(P) Poeng"
		<< "\n(X) Avslutt";
}


void skriv(const char * text, const char * string)
{
	cout << '\n' << text << '\t' << string << '\n';
}

//displayer int med ledetext pÂ standarformat
void skriv(const char * text, const int dataMedlem)
{
	cout << '\n' << text << '\t' << dataMedlem << '\n';
}

//   !!!!!!!!!!   FIL FUNKSJONER()  !!!!!!!!!!!!!!!!!!!!!!!!

//skriver en int til fil pÂ standarformat
void skriv(ofstream& ut, int tall)
{
	ut << tall << '\n';
}
//skriver en string til fil pÂ standarformat
void skriv(ofstream & ut, char * string)
{
	ut << string << '\n';
}

int lesInt(ifstream& inn)			//leser en int fra fil pÂ standarformat
{
	int a;
	inn >> a; inn.ignore();
	return a;
}
//leser en string fra fil pÂ stamdarformat, konvertert og retutnerer char*
char *lesTxt(ifstream & inn)
{
	char dummy[STRLEN];
	char *string = nullptr;

	inn.getline(dummy, STRLEN);									//les fra fil
	string = new char[strlen(dummy) + 1];	//konverterer char array til char*
	strcpy(string, dummy);
	return string;											 //returner char*
}

void skrivTilFil() {										//skriver alt til fil

	ofstream ut("LEGER.DTA"); //!!!!endre navn fÂ fil  è≈pner/skaper aktuell fil.

	int antallObjekter = 20; //dummy for Â fjerne feilmld. mÂ fjernes!!!!!!!
													//sortert liste
	if (ut)													//hvis filen finnes
	{

		skriv(ut, antallObjekter);							  //antall legeobjekter

		for (int i = 1; i <= antallObjekter; i++)		//gÂr gjennom alle legeobjektene
		{
			//hent legeobjekt
			//skriv til fil
			//legg legeobjekt tilbake i sortert liste
		}
	}
	else
	{
		cout << "\n\nFinner ikke filene!\n\n";
	}					//feilmeding
}

void lesFraFil(int alternativ) {							// leser alt fra fil

	ifstream inn("LEGER.DTA");								//  è≈pner aktuell fil
	int antallObjekter;


	if (inn)												//hvis fillen finnes
	{

		antallObjekter = lesInt(inn);			//leser in antall legeobjekter pÂ filen

		for (int i = 1; i <= antallObjekter; i++)
		{
			//les f¯rste
			//nytt bjekt med arg.
			//legg til objekt i liste
		}
	}
	else
	{
		cout << "\n\nFinner ikke filen!\n\n";
	}					 //feilmelding
}

bool erBokstaver(char tekst[]) {                    // Sjekker om alle indekser i array er bokstav.
  int lengde;
  lengde = strlen(tekst);                           // Lengden av array.

  for (int i = 0; i < lengde; i++) {                // Looper gjennom alle indekser.
    if (!isalpha(tekst[i]))                         // Hvis indeks ikke er bokstav sÂ
      return false;                                 // returneres false.
  }
  return true;
}

char *nasjonsForkortelse(char *t) {                 // Sjekker at bokstaver = 3 og gj¯r dem store.
    char buffer[STRLEN];
    char *forkortelse;

    cout << t;                                      // Skriver ut ledetekst.
    do {                                            // Loop:
    cout << "\nNasjonsforkortelse (3 bokstaver): ";
    cin.getline(buffer, STRLEN);                    // Leser inn verdi.
    forkortelse = konverter(buffer);                // Gj¯r om st¯rrelsen.

  } while ( !erBokstaver(forkortelse) ||            // SÂ lenge det ikke er bokstaver og
            strlen(forkortelse) != 3);              // lengder pÂ array ikke er 3.

  for (int i = 0; i < 3; i ++)                      // Looper gjennom indeksene.
    forkortelse[i] = toupper(forkortelse[i]);       // Gj¯r om til stor bokstav.

  return forkortelse;
}
