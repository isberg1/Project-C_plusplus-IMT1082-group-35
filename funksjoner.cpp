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
#include <regex>        // For numeric_limits.
#include "CONST.H"
#include "FUNKSJONER.H"
#include"DELTAGERE.H"
#include"ENUM.H"
#include"POENG.H"
#include"MEDALJER.H"


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
	cin >> ch;                                      // Leser ETT tegn. Forkaster '\n'.                                                    // Forkaster flere bokstaver enn 1 og '\n'.
	cin.ignore(numeric_limits <streamsize> :: max(), '\n');

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
	cout << "\n\nHovedmeny \nMulige brukervalg"
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

void lesTxt2(ifstream & inn, char string[])
{	inn.getline(string, STRLEN); }

// fjern foor siste innlevering
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
// fjern foor siste innlevering
void lesFraFil(int alternativ) {							// leser alt fra fil

	ifstream inn("LEGER.DTA");								//  è≈pner aktuell fil
	int antallObjekter;


	if (inn)												//hvis fillen finnes
	{

		antallObjekter = lesInt(inn);			//leser in antall legeobjekter pÂ filen

		for (int i = 1; i <= antallObjekter; i++)
		{
			//les f¯rste
			//nytt objekt med arg.
			//legg til objekt i liste
		}
	}
	else
	{
		cout << "\n\nFinner ikke filen!\n\n";
	}					 //feilmelding
}

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

char *nasjonsForkortelse(char t[]) {                // Sjekker at bokstaver = 3 og gj¯r dem store.

  char buffer[STRLEN];
  char *forkortelse;

  cout << t;                                        // Skriver ut ledetekst.

  do {                                              // Loop:
    les("\nNasjonsforkortelse (3 bokstaver)", buffer, NVLEN);
    forkortelse = konverter(buffer);                // Gj¯r om st¯rrelsen og lager ny char.
  } while (!erBokstaver(forkortelse) ||             // SÂ lenge det ikke er bokstaver og
            strlen(forkortelse) != NASJONLEN);      // lengder pÂ array ikke er 3.

  for (int i = 0; i < NASJONLEN; i ++)              // Looper gjennom indeksene.
    forkortelse[i] = toupper(forkortelse[i]);       // Gj¯r om til stor bokstav.

  return forkortelse;
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

bool erBokstaverEllerSpace(char tekst[]) {          // Sjekker om indekser i array er bokstaver/space.      //!!! IKKE ENDA I BRUK
  int lengde;
  lengde = strlen(tekst);                           // Lengden av array.

  for (int i = 0; i < lengde; i++) {                // Looper gjennom alle indekser.
    if (!isalpha(tekst[i]) && !isspace(tekst[i]))   // Hvis indeks ikke er bokstav eller space sÂ
      return false;                                 // returneres false.
  }
  return true;
}

char *konverterTilStore(char *tekst) {              // Gj¯r om til store bokstaver.
  char nyTekst[STRLEN];
  char *tekstPeker;
  int lengde = strlen(tekst);

  for (int i = 0; i <= lengde; i++)                 // Looper gjennom arrayen.
    nyTekst[i] = toupper(tekst[i]);                 // Gj¯r om til stor bokstav.

  tekstPeker = konverter(nyTekst);                  // Lager ny peker og gj¯r om st¯rrelsen.
  return tekstPeker;                                // Returnerer den nye teksten.
}

bool slettFil(char fil[]) {                         // Sletter fil fra disk, send med filnavn.

  if (remove(fil) == 0)                             // Fors¯ker Â slette fil:
    return true;                                    // Hvis filen finnes og ble sletet.
  else
    return false;                                   // Hvis filen ikke ble slettet (Finnes ikke).
}

//funksjonen sender en rapport til medalje og poeng om aa enten ooke eller redusere antallet til en nasjon
void StatistikkRaport(int deltager, int log, int teller)
{
	int dummy;
	/*
	"deltager" brukes til aa finne ut hvilken najson sjom skal okke ant poeng og medaljer
	"log" brukes til aa finne ut hvilken najson sjom skal redusere ant poeng og medaljer
	"teller" forteller hvor mye og hva det skal ookes/reduseres med
	*/
	seiersType	med;									//{ gull, solv, bronsje };
	positivNegativ	posNeg;								//{ positiv, negativ };
	char nasjon[STRLEN];							// til aa hente deltager og log sin nasjon


	switch (teller)	//hva slags medalje skal det sendes i rapporten
	{
	case 1:	med = gull;		break;
	case 2: med = solv;		break;
	case 3: med = bronsje;	break;
	default:				break;
	}

	//til testing
	deltager = 1;

	if (deltager != 0)	//hvis det skal sendes en rapport om aa okke ant. medaljer og poeng saa er ikke "deltager" lik 0.
	{
		posNeg = positiv;									//settes til default verdi positiv 	

		strcpy(nasjon, deltagerObj.hentNasjon(deltager));  // hent "deltager" sin nasjon 

			//send raport for aa ooke antall poeng 
			poengObj.endreAntPoeng(nasjon, teller, posNeg);

			if (teller < 4)							 //hvis det er aktuelt aa sende raport til medaljeObjektet
			{
				medaljeObj.endreAntMedaljer(nasjon, med, posNeg);
			}
	}

	//til testing
	cout << "\n" << nasjon << " " << teller << " " << posNeg;
	
	if (log != 0)			//hvis det skal sendes en rapport om aa redusere ant. medaljer og poeng saa er ikke "log" lik 0.
	{	
		posNeg = negativ;
		strcpy(nasjon, deltagerObj.hentNasjon(log));	 // hent "log" sin najon
			poengObj.endreAntPoeng(nasjon, teller, posNeg);  //send raport for aa redusere antall poeng

			if (teller < 4)			//hvis det er aktuellt aa sende rapport til medalje
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



