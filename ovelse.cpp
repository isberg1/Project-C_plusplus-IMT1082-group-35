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

	//les inn dato og klokkeslett. mats har laget sjekk

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



}


void Ovelse::ajourforeLog(int flagg)										//ajourforer log[] etter at en ny resultatliste er skrevet inn 
{											//eller etter at .RES og .STA fil har blitt endret og sender raport til statistikk
	int poengTeller = 7;
	int lupteller;
	ofstream inn(filNavn(1));
	int index = 1;

	if (inn)   //hvis .RES  finnes
	{			
		inn.close();
							//trekk tilbake tidligere poengfordeling
		while (log[index] != 0 && index <= ANTALLVINNERE)
		{

			StatistikkRaport(0, log[index], poengTeller); //reduser poeng og medaljefordelingen til en nasjon
			log[index] = 0;			//ajourfor log	
			poengTeller--;					//tell ned antal poeng som gis neste gang
			index++;					//tell opp index 
		}
	}
		
		// tildel nye poeng
	if (flagg == 0)				// sa lenge filen ikke skal slettes men er usortert og poengfordeling maa gjores pa nytt
	{
		if (maaling != PoengX && maaling != PoengXX)		//hvis det maales tid
		{
			lupteller = antDeltagere;

			// finn de med lavest tid
			while (poengTeller > 0 && lupteller > 0)	// kjor til alle deltagerpos. eller til tomt for poeng
			{
				if (*(resultatListe + lupteller) > 0)	// lupen blar seg frem til den kommer til gyldige resultater
				{
					StatistikkRaport(*(deltagerListe + lupteller), log[index], poengTeller);//ook/reduser poeng og medaljefordelingen til en nasjon
					log[index] = *(deltagerListe + lupteller);			//ajourfor log	
					poengTeller--;		//tell ned antal poeng som gis neste gang
					index++;			//tell opp slik at neste logg innleg sjekkes neste gang
				}
				lupteller--;			//tell ned lupteller 
			}
		}
		else												//hvis vi maaler poeng
		{
			lupteller = 1;
			//finn de med hoyest poengsumm
			// kjor til alle vinnerne har foot poeng eller til resultatet ikke er gyldig
			while (lupteller <= ANTALLVINNERE && *(resultatListe + lupteller) > -1)
			{				
					StatistikkRaport(*(deltagerListe + lupteller), log[lupteller], poengTeller); //ook/reduser poeng og medaljefordelingen til en nasjon
					log[lupteller] = *(deltagerListe + lupteller);			//ajourfor log	
					poengTeller--;					//tell ned antal poeng som gis neste gang
					lupteller++;					//tell opp lupteller 
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
	float temp;
	int min, sec, tid;
	int lupTeller = antDeltagere;

	if (inn)	//hvis fil finnes
	{
		resultaterLesFraFil();
		inn.close();

		skriv("Resultatliste sortert best til minst best","\n(-1 betyr disket, brutt eller ikke moot opp)");
		skriv("\nDeltager:  Navn:  Nasjon  Resultat:", "");

		if (maaling ==PoengX || maaling == PoengXX)		// hvis maaligstypen er poeng
		{
			for (int i = 1; i <= antDeltagere; i++)
			{
				HentNavnOgNasjonFraDeltager(nv, nasj, *(deltagerListe + i));
				temp = (maaling == PoengX) ? (*(resultatListe + i) / 10) : (*(resultatListe + i) / 100);

				cout << *(deltagerListe + i) << "  "
					<< nv << "  " << nasj << "  "
					<< temp << "\n";
			}
		}
		else        // hvis maaligstypen er tid
		{
			while (*(resultatListe + lupTeller) < 1)
			{
				lupTeller--;
			}
			while (lupTeller > 0)
			{
				HentNavnOgNasjonFraDeltager(nv, nasj, *(deltagerListe + lupTeller));	//hent navn og nasjon til en deltager

				if (maaling == MinSECTidel)							// maxverdi 120 59 9
				{
					min = *(resultatListe + lupTeller) / 1000;
					sec = (*(resultatListe + lupTeller) % 1000) / 10;
					tid = *(resultatListe + lupTeller) % 10;
				}
				else if (maaling == MinSecHundredel)				// maxverdi 120 59 99
				{
					min = *(resultatListe + lupTeller) / 10000;
					sec = (*(resultatListe + lupTeller) % 10000) / 100;
					tid = *(resultatListe + lupTeller) % 100;
				}
				else if (maaling == MinSekTusendel)					// maxverdi 120 59 999
				{
					min = *(resultatListe + lupTeller) / 10000;
					sec = (*(resultatListe + lupTeller) % 10000) / 1000;
					tid = *(resultatListe + lupTeller) % 1000;
				}
				cout << *(deltagerListe + lupTeller) << "  "
					<< nv << "  " << nasj << " "
					<< min << ":" << sec << ":" << tid << "\n";

				lupTeller--;
			}

			lupTeller = antDeltagere;
			while (*(resultatListe + lupTeller)<1)
			{
				HentNavnOgNasjonFraDeltager(nv, nasj, *(deltagerListe + lupTeller));	//hent navn og nasjon til en deltager

				if (maaling == MinSECTidel)							// maxverdi 120 59 9
				{
					min = *(resultatListe + lupTeller) / 1000;
					sec = (*(resultatListe + lupTeller) % 1000) / 10;
					tid = *(resultatListe + lupTeller) % 10;
				}
				else if (maaling == MinSecHundredel)				// maxverdi 120 59 99
				{
					min = *(resultatListe + lupTeller) / 10000;
					sec = (*(resultatListe + lupTeller) % 10000) / 100;
					tid = *(resultatListe + lupTeller) % 100;
				}
				else if (maaling == MinSekTusendel)					// maxverdi 120 59 999
				{
					min = *(resultatListe + lupTeller) / 10000;
					sec = (*(resultatListe + lupTeller) % 10000) / 1000;
					tid = *(resultatListe + lupTeller) % 1000;
				}
				cout << *(deltagerListe + lupTeller) << "  "
					<< nv << "  " << nasj << " "
					<< min << ":" << sec << ":" << tid << "\n";

				lupTeller--;
			}
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
		skriv(ut, "S");								// S for sortert liste
		skriv(ut, antDeltagere);

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

	lesTxt2(inn, buffer);		//leser inn om listern er sortert eller ikke
	antDeltagere = lesInt(inn);

	for (int i = 1; i <= antDeltagere * 2; i++)
	{
		*(deltagerListe + i) = lesInt(inn);
		*(resultatListe + i) = lesInt(inn);
	}

	if (buffer[0] != 'S')		// hvis fillen ikke er sortert
	{
		bubbleSort();
		ajourforeLog();
	}
}


int Ovelse::sjekkID()
{
	return nr;
}

bool Ovelse::fjernResultatliste()
{
	/*Fjerne / slette resultatliste:
		Om denne(filen) finnes så slettes den.
		Men, husk først å oppdatere statistikkene.
*/

	
	char temp[STRLEN];
	strcpy(temp, filNavn(1));
	ifstream inn(temp);

	if (inn)	//hvis OVxxxx.RES finnes
	{		
		if (slettFil(temp))
		{
			skriv("Filen er slettet", "");
			ajourforeLog(1);
			return true;
		}
		else
		{
			skriv("Filen ble ikke slettet", "");
			return false;
		}
	}
	else
	{
		skriv("Finner ingen fil med navn: ", temp );
		return false;
	}

}
