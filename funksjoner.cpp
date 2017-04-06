/*
    funksjoner.cpp
    Globale funksjoner
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif



#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */
#include <regex>        // For numeric_limits.
#include "CONST.H"
#include "FUNKSJONER.H"
#include"DELTAGERE.H"
#include"ENUM.H"
#include"POENG.H"
#include"MEDALJER.H"
#include <ctype.h>

using namespace std;


extern Deltagere deltagerObj;
extern Medaljer medaljeObj;
extern Poeng poengObj;


char les() {			                            // Henter ett ikke-blankt upcaset tegn:
	char ch;
	cin >> ch;                                      //  Leser ETT tegn.
	cin.ignore(numeric_limits <streamsize> :: max(), '\n');

	return (toupper(ch));                           //  Upcaser og returnerer.
}


char les(char menyPlass[]) {			            // Henter ett ikke-blankt upcaset tegn:
	char ch;
	cout << menyPlass;                              // Skriver ut menyplass.
	cin >> ch;                                      // Leser ETT tegn. Forkaster '\n'.
	cin.ignore(numeric_limits <streamsize> :: max(), '\n');// Forkaster flere bokstaver enn 1 og '\n'.

	return (toupper(ch));                           // Upcaser og returnerer.
}

                                                    //  Leser et tall i et visst intervall:
													//  Leser et tall i et visst intervall:
int les(const char t[], const int min, const int max) {
	int i;
	char buffer[256];
	bool erDetIkkeTall = false;
	do {                                            // Skriver ledetekst:
		cout << '\t' << t << " (" << min << '-' << max << "): ";
		fgets(buffer, 256, stdin);
		if (isdigit(buffer[0]))			//sjekker om foorste inleste char er et siffer
		{
			i = atoi(buffer);			//hvis siffer, konverter char[] til tall
			erDetIkkeTall = false;
		}
		else
		{	erDetIkkeTall = true;	}
	} while ((i < min || i > max) || erDetIkkeTall);      // Sjekker at i lovlig intervallo gat det er et tall.
	return i;                                       // Returnerer innlest tall.
}

void les(const char t[], char s[], const int LEN)
{
	char buffer[STRLEN*2];
	do {

		cout << '\t' << t << ": "; cin.getline(buffer, LEN);//Ledetekst og leser.
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	} while (strlen(buffer) == 0 && strlen(buffer)> LEN);						 //Sjekker at tekstlengden er ulik 0.

	fjernBlankeForanOgBak(buffer);
	strcpy(s, buffer);
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
	cout << "\n\nPROGRAMMETS HOVEDMENY:"
		 << "\n\tN - Nasjoner"
		 << "\n\tD - Deltagere"
		 << "\n\tG - Grener"
		 << "\n\tO - Ovelse"
		 << "\n\tM - Medaljer"
		 << "\n\tP - Poeng"
		 << "\n\tX - Avslutt";
}


void skriv(const char * text, const char * string)
{
	cout << '\n' << text << '\t' << string;
}

//displayer int med ledetext på standarformat
void skriv(const char * text, const int dataMedlem)
{
	cout << '\n' << text << '\t' << dataMedlem;
}

///   !!!!!!!!!!   FIL FUNKSJONER()  !!!!!!!!!!!!!!!!!!!!!!!!

//skriver en int til fil på standarformat
void skriv(ofstream& ut, int tall)
{
	ut << tall << '\n';
}
//skriver en string til fil på standarformat
void skriv(ofstream & ut, char * string)
{
	ut << string << '\n';
}

int lesInt(ifstream& inn)			//leser en int fra fil på standarformat
{
	int a;
	inn >> a; inn.ignore();
	return a;
}
//leser en string fra fil på stamdarformat, konvertert og retutnerer char*
char *lesTxt(ifstream & inn)
{
	char dummy[STRLEN];
	char *string = nullptr;

	inn.getline(dummy, STRLEN);									//les fra fil
	string = new char[strlen(dummy) + 1];	//konverterer char array til char*
	strcpy(string, dummy);
	return string;											 //returner char*
}

void lesTxt2(ifstream & inn, char string[])
{	inn.getline(string, STRLEN); }

void fjernBlankeForanOgBak(char txt[])
{
	char buff[STRLEN];
	int t = 0;
	int a = 0;

	while (txt[t] == ' ')
	{
		t++;
	}
	while (t <= strlen(txt))
	{
		buff[a] = txt[t];
		a++;
		t++;
	}
	buff[t] = '\0';

	t = strlen(buff);

	while (buff[t - 1] == ' ')
	{
		t--;
	}
	buff[t] = '\0';
	strcpy(txt, buff);
}

char *nasjonsForkortelse(char t[]) {                // Sjekker at bokstaver = 3 og gjør dem store.

  char buffer[STRLEN];
  char *forkortelse;

  cout << t;                                        // Skriver ut ledetekst.

  do {                                              // Loop:
    les("\nNasjonsforkortelse (3 bokstaver)", buffer, NVLEN);
    forkortelse = konverter(buffer);                // Gjør om størrelsen og lager ny char.
  } while (!erBokstaver(forkortelse) ||             // Så lenge det ikke er bokstaver og
            strlen(forkortelse) != NASJONLEN);      // lengder på array ikke er 3.

  for (int i = 0; i < NASJONLEN; i ++)              // Looper gjennom indeksene.
    forkortelse[i] = toupper(forkortelse[i]);       // Gjør om til stor bokstav.

  return forkortelse;
}

bool erBokstaver(char tekst[]) {                    // Sjekker om alle indekser i array er bokstav.
  int lengde;
  lengde = strlen(tekst);                           // Lengden av array.

  for (int i = 0; i < lengde; i++) {                // Looper gjennom alle indekser.
    if (!isalpha(tekst[i]))                         // Hvis indeks ikke er bokstav så
      return false;                                 // returneres false.
  }
  return true;
}

char *konverterTilStore(char *tekst) {              // Gjor om til store bokstaver.
  char nyTekst[STRLEN];
  char *tekstPeker;
  int lengde = strlen(tekst);

  for (int i = 0; i <= lengde; i++)                 // Looper gjennom arrayen.
    nyTekst[i] = toupper(tekst[i]);                 // Gjør om til stor bokstav.

  tekstPeker = konverter(nyTekst);                  // Lager ny peker og gjør om størrelsen.
  return tekstPeker;                                // Returnerer den nye teksten.
}

bool slettFil(char fil[]) {                         // Sletter fil fra disk, send med filnavn.

  if (remove(fil) == 0)                             // Forsøker å slette fil:
    return true;                                    // Hvis filen finnes og ble sletet.
  else
    return false;                                   // Hvis filen ikke ble slettet (Finnes ikke).
}

//funksjonen sender en rapport til medalje og poeng om aa enten ooke eller redusere antallet til en nasjon
void StatistikkRaport(int deltager, int log, int teller)
{
	/*
	"deltager" brukes til aa finne ut hvilken najson sjom skal okke ant poeng og medaljer
	"log" brukes til aa finne ut hvilken najson som skal redusere ant poeng og medaljer
	"teller" forteller hvor mye og hva det skal ookes/reduseres med
	*/
	seiersType	med;									//{ gull, solv, bronsje };
	positivNegativ	posNeg;								//{ positiv, negativ };
	char nasjon[STRLEN];							// til aa hente deltager og log sin nasjon


	switch (teller)	//hva slags medalje skal det sendes i rapporten
	{
	case 7:	med = gull;		break;		//endret 1,2,3 til 7,6,5,
	case 6: med = solv;		break;
	case 5: med = bronsje;	break;
	default:				break;
	}


	if (deltager != 0)	//hvis det skal sendes en rapport om aa okke ant. medaljer og poeng saa er ikke "deltager" = 0.
	{
		posNeg = positiv;									//settes til default verdi positiv

		strcpy(nasjon, deltagerObj.hentNasjon(deltager));  // hent "deltager" sin nasjon

			//send raport for aa ooke antall poeng
			poengObj.endreAntPoeng(nasjon, teller, posNeg);

			if (teller > 4)							 //hvis det er aktuellt aa sende raport til medaljeObjektet
			{
				medaljeObj.endreAntMedaljer(nasjon, med, posNeg);
			}
	}

	if (log != 0)	//hvis det skal sendes en rapport om aa redusere ant. medaljer og poeng saa er ikke "log" = 0.
	{
		posNeg = negativ;
		strcpy(nasjon, deltagerObj.hentNasjon(log));	 // hent "log" sin nasjon
			poengObj.endreAntPoeng(nasjon, teller, posNeg);  //send rapport for aa redusere antall poeng

			if (teller > 4)			//hvis det er aktuellt aa sende rapport til medalje
			{
				medaljeObj.endreAntMedaljer(nasjon, med, posNeg);
			}			//send raport for aa redusere antall medaljer
    }
}

void HentNavnOgNasjonFraDeltager(char nv[], char nasj[], int nr)
{
	strcpy(nv, deltagerObj.hentNavn(nr));
	strcpy(nasj, deltagerObj.hentNasjon(nr));
}


bool sjekkDeltagerId(int deltagerNv)
{
	return deltagerObj.sjekkId(deltagerNv);
}

//brukes til testing  skriver test med eller uten arg. paa skjerm
void tr(int t)
{
	if (t ==0)
	{	skriv("TEST\t", "TEST"); }
	else
	{	skriv("TEST\t", t);	}
}





