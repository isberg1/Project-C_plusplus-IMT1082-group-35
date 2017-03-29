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

Ovelse::Ovelse(registerTidPoeng typeMaaling, char *nv)		//constructor    får parameter sisteOvelse fra Grener 
{		
	navn = konverter(nv);													//faar navn fra Gren
	maaling = typeMaaling;													//faar enumen fra Gren
	nr = lagUniktNr();						// faar en unikt nummer basert på static int "navnTeller" 
								//les inn egene datamedlemer
	antDeltagere = les("Skriv inn antall deltagere i ovelsen. ", MINDELTAGERE, MAXDELTAGERE);	
	
	deltagerListe = new int[MAXDELTAGERE + 1];			//setter deltagerListe peker til en int array						
	resultatListe = new int[MAXDELTAGERE + 1];			//setter resultatListe peker til en int array

	for (int i = 0; i <= ANTALLVINNERE + 1; i++)
	{	log[i] = 0; 	}											//nullstiller log arryaen

}

Ovelse::~Ovelse()	//destructor
{
	delete[] navn;
	delete[] deltagerListe;
	delete[] resultatListe;
}

void Ovelse :: skrivMeny() {

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

	if (true/*inn*/)																//hvis en deltagerliste finnes
	{
		if (!ut )														//hvis en resultatliste ikke finnes
		{

			skriv("Skriv in resultater (hvis en deltager har brutt, ikke moott eller blit disket tast -1):", "");
			for (int i = 1; i <= antDeltagere; i++)
			{
					skriv("Skriv inn resutatet for deltager: ", *(deltagerListe + i));
					*(resultatListe + i) = skaffVerdi();				//leser inn gyldige verdier til resultatlisten					
			}

			bubbleSort();
			ajourforeLog();			//ma lages
			resultaterSkrivTilFil();	//ma lages

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
	int min, sec, tidel, hundredel,tusendel, poengX, poengXX, desimal;

	//hvis en deltager har brutt, ikke moott eller blit disket saa skal det tastes - 1):",

	if (maaling== MinSECTidel)
	{
		min = les("Skriv resultat i minutter: ", -1, 120);
		if (min != -1)
		{
			sec = les("Skriv resultat i sekunder: ", 0, 59);
			tidel = les("Skriv resultat i tidelssekunder: ", 0, 9);
			return ((min * 1000) + (sec * 10) + tidel); 					// maxverdi 120 59 9
		}
	}
	else if (maaling== MinSecHundredel)
	{
		min = les("Skriv resultat i minutter: ", -1, 120);
		if (min != -1)
		{
			sec = les("Skriv resultat i sekunder: ", 0, 59);
			hundredel = les("Skriv resultat i hundredelssekunder: ", 0, 99);
			return ((min * 10000) + (sec * 100) + hundredel); 					// maxverdi 120 59 99
		}
	}
	else if (maaling== MinSekTusendel)
	{
		min = les("Skriv resultat i minutter: ", -1, 120);
		if (min != -1)
		{
			sec = les("Skriv resultat i sekunder: ", 0, 59);
			tusendel = les("Skriv resultat i tusendelssekunder: ", 0, 999);
			return ((min * 100000) + (sec * 1000) + tusendel); 					// maxverdi 120 59 999
		}
	}
	else if (maaling== PoengX)
	{
		poengX = les("Skriv heltallsdelen av resultatet i poeng: ", -1, 9);
		if (poengX != -1)
		{
			desimal = les("Skriv desimaltallsdelen av resultatet i poeng: ", 0, 9);
			return ((poengX * 10) + desimal);							// maxverdi 99
		}																
	}
	else if (maaling== PoengXX)
	{
		poengXX = les("Skriv heltallsdelen av resultatet i poeng: ", -1, 99);
		if (poengXX != -1)
		{
			desimal = les("Skriv desimaltallsdelen av resultatet i poeng: ", 0, 99);
			return ((poengXX * 100) + (desimal* 10));					// maxverdi 9999
		}
	}

	return -1;										//returnerer brudd/diskvalifiserings verdi		
}

void Ovelse::bubbleSort()    //sorterer 2 int arrayer.  
{	

		int dummy;
		int temp, bytter;

		for (int i = 1; i <= antDeltagere - 1; i++)
		{
			for (int j = i + 1; j <= antDeltagere; j++)
			{
				if (*(resultatListe+i) < *(resultatListe+j))
				{					//swap resultat array
					dummy = *(resultatListe + i);
					*(resultatListe + i) = *(resultatListe + j);
					*(resultatListe + j) = dummy;
									//swap deltager array
					temp = *(deltagerListe + i);
					*(deltagerListe + i) = *(deltagerListe + j);
					*(deltagerListe + j) = temp;

				}
			}
		}
		// sjekker om flere deltagere er registrert med samme resultat og ber bruker om aa bestemme seiersrekkefolge
		for (int j = 1; j <= antDeltagere - 1; j++)
		{

			if (*(resultatListe + j) == *(resultatListe + (j + 1)))				//hvis 2 deltagere har like resultater
			{

				cout << "\nUklarket oppdaget. 2 deltagere har samme resultat, \nvennligst velg hvem av de 2"
					<< "som skal ha den overste resultatplassen. \nFor deltager: "
					<< *(deltagerListe + j) << " skriv " << j
					<< " eller for deltager: " << *(deltagerListe + (j + 1))
					<< " skriv " << (j + 1);

				temp = les(": ", j, (j + 1));
			
				if (temp == (j + 1))									// hvis brukeren har valgt aa endre rekkefolgen
				{								//bytt plasser deltagerliste
					

					bytter = *(deltagerListe + j);
					*(deltagerListe + j) = *(deltagerListe + (j + 1));
					*(deltagerListe + (j + 1)) = bytter;
												//bytt plasser resultatliste
					bytter = *(resultatListe + j);
					*(resultatListe + j) = *(resultatListe + (j + 1));
					*(resultatListe + (j + 1)) = bytter;

					
				}
			}
		}
}


void Ovelse::ajourforeLog()										//ajourforer log[] etter at en ny resultatliste er skrevet inn 
{											//eller etter at .RES og .STA fil har blitt endret og sender raport til statistikk
			// vurder while lup 				
	for (int k = 1; k <= 7; k++)												// gaa gjennom alle som skal ha medalje og poeng
	{
		if ( *(deltagerListe + k) != log[k]	)						//hvis seiersrekkefolgen ikke stemmer med det som er logfort
		{
			if (*(resultatListe + k) > 0)							//hvis resultatlisten har et gyldig resultat for den indexen
			{								//lag raporter til medalje og statistikk
				StatistikkRaport(*(deltagerListe + k), log[k], k);		//ook/reduser poeng og medaljefordelingen til en nasjon
				log[k] = *(deltagerListe + k);			//ajourfor log
			}
		}
	}
}

void Ovelse::skrivResultatliste()
{
	char fil[STRLEN];
	char nv[STRLEN];
	char nasj[STRLEN];



	strcpy(fil, filNavn(1));

	ifstream inn(fil);

	if (true /*inn*/)
	{
		resultaterLesFraFil();
	//	bubbleSort();
	//	ajourforeLog();

		skriv("Resultatliste sortert hoyest til lavest", "\nDeltager:  Resultat:  Navn:  Nasjon");
		for (int i = 1; i <= antDeltagere; i++)
		{
			HentNavnOgNasjonFraDeltager(nv, nasj, *(deltagerListe + i));

			cout << *(deltagerListe + i) << "  "
				<< *(resultatListe + i) << "  "
				<< nv << "  " << nasj << "\n";
		}
	}
	else
	{	skriv("Finner ingen fil med navn: ", fil);	}

}

void Ovelse::deltagerSkrivtilFil()
{
}

void Ovelse::resultaterSkrivTilFil()
{
	//advarsel bubbleSort() ma kjores for denne funksjonen kalles
	deltagerSkrivtilFil();

	ofstream ut(filNavn(1));

	if (ut)
	{
		skriv(ut, antDeltagere);
		skriv(ut, "fra udnder denne linjen saar deltagenr i forste linje og deltagerens resultat under:");
		for (int i = 1; i <= antDeltagere * 2; i++)
		{
			skriv(ut, *(deltagerListe + i));
			skriv(ut, *(resultatListe + i));
			skriv(ut, "\n");
		}
	}
}

void Ovelse::resultaterLesFraFil()
{
	char buffer[100];
	ifstream inn(filNavn(1));

	antDeltagere = lesInt(inn);
	lesTxt2(inn, buffer);

	for (int i = 1; i <= antDeltagere * 2; i++)
	{
		*(deltagerListe + i) = lesInt(inn);
		*(resultatListe + i) = lesInt(inn);
	}

}

int Ovelse::sjekkID()
{
	return nr;
}
