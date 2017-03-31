//ovelse.cpp alex

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>
#include <sstream>
#include <string.h>
#include "OVELSE.H"
#include"ENUM.H"

using namespace std;



Ovelse :: Ovelse () {
  cout << "\nAdvarsel, Ovelse-objekter skal ikke lages uten parameter";
}
                                                    //constructor, får param. navn,sisteOvelse fra Gren.
Ovelse :: Ovelse(char *ovelseNavn, registerTidPoeng typeMaaling) {

  nr = lagUniktNr();						        // Faar et unikt nummer basert på static int navnTeller.
  maaling = typeMaaling;							// Faar enumen fra Gren.

  endreNavn(ovelseNavn);                            // Setter navn fra parameter.
                                                    // Les inn antall deltagere.
  antDeltagere = les("Skriv inn antall deltagere i ovelsen", MINDELTAGERE, MAXDELTAGERE);

  endreDato();                                      // Setter dato.

  endreKlokkeslett();                               // Setter klokkeslett

  deltagerListe = new int[MAXDELTAGERE + 1];	    // Setter deltagerListe peker til en int array.
  resultatListe = new int[MAXDELTAGERE + 1];		// Setter resultatListe peker til en int array.

  for (int i = 0; i <= ANTALLVINNERE + 1; i++)      // Nullstiller log arrayen.
    log[i] = 0;
}

Ovelse::~Ovelse()	//destructor
{
	delete[] navn;
	delete[] deltagerListe;
	delete[] resultatListe;
}

void Ovelse::skrivData()	//Displayer egne datamedlemmer
{
	skriv("ID: ", nr);
	skriv("Fullt navn: ", navn);
	skriv("Dato: ", dato);
	skriv("Klokkeslett: ", klokkeslett);
	skriv("Antall deltagere: ", antDeltagere);
}

char * Ovelse::filNavn(int type)		//send med 1 for .RES eller ingenting for .STA
{
		char name[11] = "OV";
		char end[5] = ".STA";
		char* middle;
		stringstream strs;
		string buffer;

		if (type == 1)					//avhengi av medsent arg.  er 1 eller den statisk satte verdien 0
		{	strcpy(end, ".RES");	}	//saa blir slutten entn .RES eller .STA

					//konverterer int "nr til String
		strs << nr;								//Ovelse sitt unike nr brukkes til delen xxxx i filnavnet
		buffer = strs.str();
		middle = (char*)buffer.c_str();
						//limmer sammen de 3 delende av filnavnet

		strcat(name, middle);
		strcat(name, end);

		return name;													//returnerer det unike filnavnet
}

void Ovelse::skrivTilFil(ofstream & ut)
{
				//skriver egne datamedlemmer til fil
	skriv(ut, nr);
	skriv(ut, dato);
	skriv(ut, klokkeslett);
	skriv(ut, antDeltagere);
	skriv(ut, navn);
	skriv(ut, navnTeller);

//!!!!!!!!!! maa lages!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//deltager array skriv til fil
		//resultat array skriv til fil
}

void Ovelse::lesFraFil(ifstream & inn)
{
				//leser egne datamedlemmer fra fil
	nr = lesInt(inn);
	dato = lesInt(inn);
	klokkeslett = lesInt(inn);
	antDeltagere = lesInt(inn);
	navn = lesTxt(inn);
	navnTeller = lesInt(inn);


	//!!!!!!!!!! maa lages!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//deltager array les fra fil
	//resultat array les fra fil
}

void Ovelse::nyResultatListe()	//lager ny resultatliste
{
	int dummy;
	int temp;

	ifstream inn(filNavn(0));
	ofstream ut(filNavn(1));

	if (inn)																//hvis en deltagerliste finnes
	{
		if (!ut )														//hvis en resultatliste ikke finnes
		{

			skriv("Skriv in resultater (hvis en deltager har brutt, ikke moott eller blit disket tast -1):", "");
			for (int i = 1; i <= antDeltagere; i++)
			{
					skriv("Skriv inn resutatet for deltager: ", *(deltagerListe + i));
					skaffVerdi();
			}

		}
		else
		{		//lukk filer og skriv ut feilmelding			//noe usikker paa denne				//$$$$$$$$$$$$ ma testes
			ut.close();
			inn.close();
			skriv("Resultatlisten finnes alerede!", "");
		}
	}
	else
	{			//lukk filer og skriv ut feilmelding			//noe usikker paa denne				//$$$$$$$$$$$$ ma testes
		ut.close();
		inn.close();
		skriv("Deltagerlisten finnes ikke! lag den foor Resultatliste", "");
	}
}

int Ovelse::lagUniktNr() //returnerer et unikt tall til datamedlemm "nr"
{
	return (++navnTeller);	//advarsel ma aldri telles ned
}

//leser inn gyldige verdier til resultatliste
int Ovelse::skaffVerdi()
{
	int min, sec, tidel, hundredel,tusendel, poengX, poengXX;

	//hvis en deltager har brutt, ikke moott eller blit disket saa skal det tastes - 1):",

	if (maaling== MinSECTidel)
	{
		min = les("Skriv resultat i minutter: ", -1, 120);
		if (min != -1)
		{
			sec = les("Skriv resultat i sekunder: ", -1, 59);
			tidel = les("Skriv resultat i tidelssekunder: ", -1, 9);
			return ((min * 1000) + (sec * 10) + tidel); 					// maxverdi 120 59 9
		}
	}
	else if (maaling== MinSecHundredel)
	{
		min = les("Skriv resultat i minutter: ", -1, 120);
		if (min != -1)
		{
			sec = les("Skriv resultat i sekunder: ", -1, 59);
			hundredel = les("Skriv resultat i hundredelssekunder: ", -1, 99);
			return ((min * 10000) + (sec * 100) + hundredel); 					// maxverdi 120 59 99
		}
	}
	else if (maaling== MinSekTusendel)
	{
		min = les("Skriv resultat i minutter: ", -1, 120);
		if (min != -1)
		{
			sec = les("Skriv resultat i sekunder: ", -1, 59);
			tusendel = les("Skriv resultat i tusendelssekunder: ", -1, 999);
			return ((min * 100000) + (sec * 1000) + tusendel); 					// maxverdi 120 59 999
		}
	}
	else if (maaling== PoengX)
	{
		poengX = les("Skriv resultat i minutter: ", -1, 9);
		return poengX;															// maxverdi 9
	}
	else if (maaling== PoengXX)
	{
		poengXX = les("Skriv resultat i minutter: ", -1, 99);
		return PoengXX;															// maxverdi 99
	}

	return -1;
}

char* Ovelse :: hentNavn() {                        // Returnerer navnet til Ovelsen.
  return navn;
}

int Ovelse :: datoSjekk(int dato) {                 // Sjekker om dato er på riktig format.
  int maaned, dag;

  maaned = (dato / 100) % 100;                      // Finner hvilke måned det er.
  dag = dato % 100;                                 // Finner hvilke dag det er.

  while ((maaned < 1 || maaned > 12) ||             // Looper hvis måned ikke er fra 1-12
         (dag < 1 || dag > 31)) {                   // og dag fra 1-31.
    dato = les("\n\tDato", 20170101, 21161231);
    maaned = (dato / 100) % 100;                    // Oppdaterer måned.
    dag = dato % 100;                               // Oppdaterer dag.
  }
  return dato;
}

int Ovelse :: klokkeSjekk(int kl) {                 // Sjekker om kl. er på riktig format.
  int time, minutt;

  time = kl / 100;                                  // Finner time fra klokkeslett.
  minutt = kl % 100;                                // Finner minutt fra klokkeslett.

  while ((time < 00 || time > 24) ||                // Looper hvis time ikke er fra 00-24
         (minutt < 00 || minutt > 60)) {            // og minutt fra 00-60.
    klokkeslett = les("\n\tKlokkeslett", 0000, 2459);
    time = kl / 100;                                // Oppdaterer time.
    minutt = kl % 100;                              // Oppdaterer minutt.
  }
  return klokkeslett;
}

void Ovelse :: skrivNavn() {                        // Skriver ut ovelsens navn.
  cout << "  -  " << navn;
}

void Ovelse :: endreNavn(char *ovelseNavn) {        // Endrer navnet til ovelsen.
  navn = ovelseNavn;
}

void Ovelse :: endreDato() {                        // Endrer datoen til ovelsen.
  cout << "\nSkriv inn dato for ovelsen (aaaa mm dd)"; // Lovelig dato-interval: 2017.01.01-2116.12.31.
  dato = les("\nDato", 20170101, 21161231);
  dato = datoSjekk(dato);                           // Sjekker at dato er på riktig format.
}

void Ovelse :: endreKlokkeslett() {                 // Endrer kl. til ovelsen.
  cout << "\nKlokkeslett for ovelsen (ttmm)";
  klokkeslett = les("\nKlokkeslett", 0000, 2459);   // Leser inn klokkeslett.
  klokkeslett = klokkeSjekk(klokkeslett);           // Sjekker at kl. er på riktig format.
}

void Ovelse :: skrivHovedData() {                   // Skriver hoveddata for en ovelse.
  cout << "\nNummer:            " << nr
       << "\nNavn:              " << navn
       << "\nAntall deltagere:  " << antDeltagere
       << "\nDato:              " << dato
       << "\nKlokkeslett:       " << klokkeslett;

// Må testes, vente på switch.
//  switch (registerTidPoeng) {
//    case "MinSECTidel"      :
//    case "MinSecHundredel"  :
//    case "MinSekTusendel"   :
//    case "PoengX"           :
//    case "PoengXX"          :
//  }
}





