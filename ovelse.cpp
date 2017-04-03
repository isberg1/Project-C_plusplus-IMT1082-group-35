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
#include"GRENER.H"
#include"DELTAGERE.H"
#include"DELTAGER.H"
#include<iomanip>


using namespace std;

extern Deltagere deltagerObj;


Ovelse::Ovelse() {
	cout << "\nAdvarsel, Ovelse-objekter skal ikke lages uten parameter";
}

Ovelse::Ovelse(ifstream & inn)
{	
	lesFraFil(inn);	

	deltagerListe = new int[MAXDELTAGERE + 1];	    // Setter deltagerListe peker til en int array.
	resultatListe = new int[MAXDELTAGERE + 1];		// Setter resultatListe peker til en int array.
	
	for (int i = 1; i <= antDeltagere; i++)
	{
	*(resultatListe + i) = *(deltagerListe + i) = 0;
	}

	if (navnTeller < nr)					//setter verdien til navnteller.
	{
	navnTeller = nr;
	}

	for (int i = 0; i <= ANTALLVINNERE + 1; i++)      // Nullstiller log arrayen.
	{	log[i] = 0;	}
}

                                                    // Constructor,får param. navn,sisteOvelse fra Gren.
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

  for (int i = 1; i <= antDeltagere; i++)
  {
	  *(resultatListe + i) = *(deltagerListe + i) = 0;
  }

  for (int i = 0; i <= ANTALLVINNERE + 1; i++)      // Nullstiller log arrayen.
    log[i] = 0;

  if (navnTeller < nr)					            // Setter verdien til navnteller.
  {
	  navnTeller = nr;
  }
}

Ovelse::~Ovelse()	//destructor
{
	/*delete[] navn;
	delete[] deltagerListe;
	delete[] resultatListe;*/
}

char * Ovelse::filNavn(int type)		//send med 1 for .RES eller ingenting for .STA
{
		char name[15] = "OV";
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

void Ovelse::skrivTilFil(ofstream & ut)		//skriv ovelse til fil
{
				//skriver egne datamedlemmer til fil
	skriv(ut, nr);
	skriv(ut, dato);
	skriv(ut, klokkeslett);
	skriv(ut, antDeltagere);
	skriv(ut, navn);
								//loggen skrives til .RES fil istede  Alex
	if (maaling == PoengX )
	{	skriv(ut, 1);	}
	else if(maaling == PoengXX)
	{	skriv(ut, 2);	}
	else if (maaling == MinSECTidel)
	{	skriv(ut, 3);	}
	else if (maaling == MinSecHundredel)
	{	skriv(ut, 4);	}
	else if (maaling == MinSekTusendel)
	{	skriv(ut, 5);	}
}

void Ovelse::lesFraFil(ifstream & inn)		//les ovelse fra fil
{

	int dummy;
				//leser egne datamedlemmer fra fil
	nr = lesInt(inn);
	dato = lesInt(inn);
	klokkeslett = lesInt(inn);
	antDeltagere = lesInt(inn);
	navn = lesTxt(inn);
						//loggen leser fra .RES fil istede  Alex
	dummy = lesInt(inn);

	switch (dummy)
	{
	case 1:	maaling = PoengX;			break;
	case 2:	maaling = PoengXX;			break;
	case 3:	maaling = MinSECTidel;		break;
	case 4:	maaling = MinSecHundredel;	break;
	case 5:	maaling = MinSekTusendel;	break;
	}

	if (navnTeller < nr)					//setter verdien til navnteller.
	{	navnTeller = nr;	}
}

void Ovelse::nyResultatListe()	//lager ny resultatliste
{
	char x[20];
	char t[20];
	strcpy(t, filNavn(1));
	strcpy(x, filNavn());

	ifstream ut(t);
	ifstream inn(x);

				//$$ testing
	if (inn)																//hvis en deltagerliste finnes
	{
		nullstillLister();
		deltagerLesFraFil();
		inn.close();

		if (!ut )														//hvis en resultatliste ikke finnes
		{

			skriv("Skriv in resultater (hvis en deltager har brutt, ikke moott eller blit disket tast -1):", "");
			for (int i = 1; i <= antDeltagere; i++)
			{
					skriv("Skriv inn resutatet for deltager: ", *(deltagerListe + i));
					*(resultatListe + i) = skaffVerdi();				//leser inn gyldige verdier til resultatlisten
			}
			
			bubbleSort();

			if (maaling == PoengX || maaling == PoengXX)
			{
				okPoengPoeng();	 ;
			}
			else
			{	okPoengTid();		}
					
			resultaterSkrivTilFil();		
			nullstillLister();			
		}
		else
		{		//lukk filer og skriv ut feilmelding			
			ut.close();
			skriv("Resultatlisten finnes alerede!", "");
		}
	}
	else
	{			//lukk filer og skriv ut feilmelding			
		ut.close();
		skriv("Deltagerlisten finnes ikke! lag den foor Resultatliste", "");		
	}
}

int Ovelse::lagUniktNr()						//returnerer et unikt tall til datamedlemm "nr"
{
	return (++navnTeller);					//advarsel ma aldri telles ned
}

//leser inn gyldige verdier til resultatliste
int Ovelse::skaffVerdi()
{
	int min, sec, tidel, hundredel,tusendel, poengX, poengXX, desimal;

	//hvis en deltager har brutt, ikke moott eller blit disket saa skal det tastes - 1):",

	//if else treet leser inn verdier til resultatlisten basert paa maaletypen

	if (maaling== MinSECTidel)						//tid
	{
		min = les("\nSkriv resultat i minutter: ", -1, 120);
		if (min != -1)
		{
			sec = les("\nSkriv resultat i sekunder: ", 0, 59);
			tidel = les("nSkriv resultat i tidelssekunder: ", 0, 9);
			return ((min * 1000) + (sec * 10) + tidel); 					// maxverdi 120 59 9
		}
	}
	else if (maaling== MinSecHundredel)				//tid
	{
		min = les("\nSkriv resultat i minutter: ", -1, 120);
		if (min != -1)
		{
			sec = les("\nSkriv resultat i sekunder: ", 0, 59);
			hundredel = les("\nSkriv resultat i hundredelssekunder: ", 0, 99);
			return ((min * 10000) + (sec * 100) + hundredel); 					// maxverdi 120 59 99
		}
	}
	else if (maaling== MinSekTusendel)			//tid
	{
		min = les("\nSkriv resultat i minutter: ", -1, 120);
		if (min != -1)
		{
			sec = les("\nSkriv resultat i sekunder: ", 0, 59);
			tusendel = les("\nSkriv resultat i tusendelssekunder: ", 0, 999);
			return ((min * 100000) + (sec * 1000) + tusendel); 					// maxverdi 120 59 999
		}
	}
	else if (maaling== PoengX)				//poeng
	{
		poengX = les("\nSkriv heltallsdelen av resultatet i poeng: ", -1, 9);
		if (poengX != -1)
		{
			desimal = les("\nSkriv desimaltallsdelen av resultatet i poeng: ", 0, 9);
			return ((poengX * 10) + desimal);							// maxverdi 99
		}
	}
	else if (maaling== PoengXX)				//poeng
	{
		poengXX = les("\nSkriv heltallsdelen av resultatet i poeng: ", -1, 99);
		if (poengXX != -1)
		{
			desimal = les("\nSkriv desimaltallsdelen av resultatet i poeng: ", 0, 99);
			return ((poengXX * 100) + (desimal));					// maxverdi 9999
		}
	}
	return -1;										//returnerer brudd/diskvalifiserings verdi
}

void Ovelse::bubbleSort()    //sorterer 2 int arrayer.
{
		int dummy;
		int temp, bytter;
					//gaar gjennom alle medlemme i arrayen og sammenlikner den med alle andre
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

void Ovelse::fjernPoeng()				//reduserer tidliger fordelte poeng og medaljer
{
	int poengTeller = 7;

		for (int i = 1; i <= ANTALLVINNERE; i++)	//gaa gjennom alle som har faat poeng tidligere
		{
			if (log[i] != -1)
			{
				tr(log[i]);
				StatistikkRaport(0, log[i], poengTeller); //reduser poeng og medaljefordelingen til nasjoner
				poengTeller--;		//tell ned antal poeng som gis neste gang
			}								
		}
}

void Ovelse::okPoengPoeng()				//oker antall poeng naar maaletypen er poeng
{
	logResett();						//nullstiller log slik at ingern feil verdier blir tatt vare på

	int poeng = 7;
	for (int i = 1; i <= ANTALLVINNERE; i++)		// gaa gjennom alle som kan vinne
	{
		if (*(resultatListe + i) != -1  && i <= antDeltagere)		//hviss gyldig resultat og ikke flere en antall deltagere
		{
			StatistikkRaport(*(deltagerListe + i), 0, poeng);		//ok poeng til nasjonen
			log[i] = *(deltagerListe + i);							//logfoor det
			poeng--;												//reduser antall poeng som gis neste gang		
		}
	}
}

void Ovelse::okPoengTid() // oker antall poeng naar maaletypen er tid
{
	logResett();					//nullstiller log slik at ingern feil verdier blir tatt vare på

	int teller = 1;
	int poeng = 7;

	for (int i = antDeltagere; i >= 1; i--)// gaa gjennom alle som kan vinne
	{
		if (*(resultatListe + i) != -1)//hviss gyldig resultat
		{
			StatistikkRaport(*(deltagerListe + i), 0, poeng);//ok poeng til nasjonen
			log[teller] = *(deltagerListe + i);//logfoor det
			poeng--;								//reduser antall poeng som gis neste gang	
			teller++;								// tellopp indexposisjonen
		}
	}
}


void Ovelse::skrivResultatliste()			//skriv resultatlisten til skjerm
{
	char fil[STRLEN];
	char nv[STRLEN];
	char nasj[STRLEN];
	float temp;
	int min, sec, tid;
	int lupTeller = antDeltagere;

	strcpy(fil, filNavn(1));

	ifstream inn(fil);
	

	if (inn)						//hvis .RES fil finnes
	{
		resultaterLesFraFil();		//les inn resultatliste fra fil
		inn.close();				//lukk fil
		skriv("Resultatliste sortert best til minst best","\n(-1 betyr disket, brutt eller ikke moot opp)");
											
		cout << "\n " << "Deltager:" << setw(17)
			<<"Navn" << setw(26) << "Nasjon" << setw(29)
			<<  "Resultat";

		if (maaling ==PoengX || maaling == PoengXX)		// hvis maaligstypen er poeng
		{
			for (int i = 1; i <= antDeltagere; i++)		//gaa gjennom hele deltagerlisten
			{												
				HentNavnOgNasjonFraDeltager(nv, nasj, *(deltagerListe + i));		//hent deltagers navn og nasjon 

				cout << "\n " << *(deltagerListe + i) << setw(25)
					<< nv << setw(25) << nasj << setw(25);
				if (maaling == PoengXX)			//hvis maaling er poeng med 2 desimaler
				{	cout << *(resultatListe + i) / 100 << "," << *(resultatListe + i) % 100 << "\n";		}
				else
				{	cout << *(resultatListe + i) / 10 << "," << *(resultatListe + i) % 10 << "\n";			}					
			}
		}
		else        // hvis maaligstypen er tid
		{
			while (*(resultatListe + lupTeller) < 1)	//blar seg forbi ikke gyldige resultater	
			{
				lupTeller--;
			}
			while (lupTeller > 0)			//starter fra laveste tid og gaar til hooyeste tid
			{
				HentNavnOgNasjonFraDeltager(nv, nasj, *(deltagerListe + lupTeller));	//hent navn og nasjon til en deltager

				if (maaling == MinSECTidel)							// maxverdi 120 59 9
				{									//konverter fra 1 int til 3
					min = *(resultatListe + lupTeller) / 1000;
					sec = (*(resultatListe + lupTeller) % 1000) / 10;
					tid = *(resultatListe + lupTeller) % 10;
				}
				else if (maaling == MinSecHundredel)				// maxverdi 120 59 99
				{												//konverter fra 1 int til 3
					min = *(resultatListe + lupTeller) / 10000;
					sec = (*(resultatListe + lupTeller) % 10000) / 100;
					tid = *(resultatListe + lupTeller) % 100;
				}
				else if (maaling == MinSekTusendel)					// maxverdi 120 59 999
				{											//konverter fra 1 int til 3
					min = *(resultatListe + lupTeller) / 10000;
					sec = (*(resultatListe + lupTeller) % 10000) / 1000;
					tid = *(resultatListe + lupTeller) % 1000;
				}				//skriv ut paa skjerm
				cout << "\n " << *(deltagerListe + lupTeller) << setw(25)
					<< nv << setw(25) << nasj << setw(25)
					<< min << ":" << sec << ":" << tid << "\n";

				lupTeller--;
			}

								//skriver de ikke gyldige resultatene paa skjermen
			lupTeller = antDeltagere;
			while (*(resultatListe + lupTeller) < 1)			//starter fra bunnen
			{
				HentNavnOgNasjonFraDeltager(nv, nasj, *(deltagerListe + lupTeller));	//hent navn og nasjon til en deltager

				if (maaling == MinSECTidel)							// maxverdi 120 59 9
				{										//konverter fra 1 int til 3
					min = *(resultatListe + lupTeller) / 1000;
					sec = (*(resultatListe + lupTeller) % 1000) / 10;
					tid = *(resultatListe + lupTeller) % 10;
				}
				else if (maaling == MinSecHundredel)				// maxverdi 120 59 99
				{										//konverter fra 1 int til 3
					min = *(resultatListe + lupTeller) / 10000;
					sec = (*(resultatListe + lupTeller) % 10000) / 100;
					tid = *(resultatListe + lupTeller) % 100;
				}
				else if (maaling == MinSekTusendel)					// maxverdi 120 59 999
				{										//konverter fra 1 int til 3
					min = *(resultatListe + lupTeller) / 10000;
					sec = (*(resultatListe + lupTeller) % 10000) / 1000;
					tid = *(resultatListe + lupTeller) % 1000;
				}								//skriv ut paa skjerm
				cout << "\n " << *(deltagerListe + lupTeller) << setw(25)
					<< nv << setw(25) << nasj << setw(25)
					<< tid<< "\n";
				lupTeller--;
			}
		}		
	}
	else
	{	skriv("Finner ingen fil med navn: ", fil);	}
}

void Ovelse::deltagerSkrivtilFil()			//skrid startliste til fil
{
	char fil[20];
	strcpy(fil, filNavn());				//hent riktig filnavn
	
	ofstream ut(fil);

	for (int i = 1; i <= antDeltagere; i++)
	{
		skriv(ut, *(deltagerListe + i) );
	}
	ut.close();				//lukk fil
}


void Ovelse::resultaterSkrivTilFil()
{
	char t[20];
	//advarsel bubbleSort() ma kjores for denne funksjonen kalles
	deltagerSkrivtilFil();

	strcpy(t, filNavn(1));

	ofstream ut(t);

	if (ut)
	{
		skriv(ut, "S");								// S for sortert liste
		skriv(ut, antDeltagere);

		for (int i = 1; i <= antDeltagere; i++)
		{
			skriv(ut, "");
			skriv(ut, *(deltagerListe + i));
			skriv(ut, *(resultatListe + i));			
		}
		//skriv loggen for tidligere poengfordelig til fil
		for (int i = 1; i <= ANTALLVINNERE; i++)
		{	skriv(ut, log[i]); 	}	
	}
}

void Ovelse::resultaterLesFraFil()			//leser inn resultatlista fra fil
{
	char buffer[100];
	char x[20];
	int teller = 1;
	strcpy(x, filNavn(1));					//hent riktig filnavn

	ifstream inn(x);

	lesTxt2(inn, buffer);		//leser inn om listern er sortert eller ikke
	antDeltagere = lesInt(inn);

	for (int i = 1; i <= antDeltagere; i++)		
	{												//leser inn resultatliste
		*(deltagerListe + i) = lesInt(inn);
		*(resultatListe + i) = lesInt(inn);
	}
	//leser inn loggen for tidliger poengfordelig
	for (int i = 1; i <= ANTALLVINNERE; i++)
	{	log[i] = lesInt(inn);	}


	if (buffer[0] != 'S')		// hvis fillen ikke er sortert saa maa det markeres 
	{
		bubbleSort();			//sort
		fjernPoeng();			//trekk tilbake tidligere tildelte poeng
		if (maaling == PoengX || maaling == PoengXX)	//hvis maaling er poeng
		{	okPoengPoeng();		}		// tildel nye poeng og medaljer
		else							//hvis maaling er tid				
		{	okPoengTid();		}		// tildel nye poeng og medaljer

		resultaterSkrivTilFil();
	}
}

void Ovelse::deltagerLesFraFil()			//leser inn deltagerlisten fra fil
{
	char fil[20];
	strcpy(fil, filNavn());					//hent riktig filnavn

	ifstream inn(fil);

	if (inn)					//hvis .STA finnes
	{
		for (int i = 1; i <= antDeltagere; i++)
		{									//les inn deltagerlisten
			*(deltagerListe + i) = lesInt(inn);
		}
	}
	else								//feilmelding
	{	skriv("Finner ingen fil med navn: ", fil); 	}
	inn.close();		//lukk  fill
}


void Ovelse::sjekkID(int & temp, char buffer[])				//reurnerer Ovelsens ID nummer og navn,   brukes til aa skrive ut data 
{
	temp = nr;
	strcpy(buffer, navn);
}

bool Ovelse::fjernResultatliste()					//fjerner en eksisterende resultatliste
{
	/*Fjerne / slette resultatliste:
		Om denne(filen) finnes så slettes den.
		Men, husk først å oppdatere statistikkene.
	*/


	char temp[STRLEN];
	strcpy(temp, filNavn(1));

	ifstream inn(temp);
	nullstillLister();
	logResett();
	if (inn)	//hvis OVxxxx.RES finnes
	{
		resultaterLesFraFil();				//les inn resultatlisten fra fil
		inn.close();						//lukk fil
		
		if (slettFil(temp))					//slett filen fra HDD
		{
			skriv("Filen er slettet", "");	//bekreftelsesmelding
			fjernPoeng();					//trekker tilbake tidligere tildelte poeng
			return true;
		}
		else
		{									//feilmelding
			skriv("Filen ble ikke slettet", "");
			return false;
		}
	}
	else
	{										//feilmelding
		skriv("Finner ingen fil med navn: ", temp );
		return false;
	}
}

int Ovelse::hentId()			//returnerer Ovelsens unike ID nummer
{
	return nr;
}

void Ovelse::nullstillLister()				//nullstiller start- og resultatlister
{
	for (int i = 1; i <= antDeltagere; i++)
	{
		*(deltagerListe + i) = *(resultatListe + i) = 0;
	}
}

void Ovelse::logResett()						//nullstiller log
{
	for (int i = 0; i <= ANTALLVINNERE; i++)
	{
		log[i] = 0;
	}
}

void Ovelse::menyValgDelListe()						// ValgSwitch for deltagerLister.
{
	char valg;
	
	do
	{
		skrivDelListeMeny();
		valg = les("\nDeltagerListe: ");

		switch (valg)
		{
		case 'S': skrivDelListe();	    break;		// Skriver ut en deltagerListe.		maa ¨lages
		case 'N': nyDelListe();			break;		// Lager en ny deltagerListe.
		case 'E': endreDelListe();		break;		// Endrer en deltagerListe.			maa ¨lages
		case 'F': fjernDelListe();		break;		// Fjerner en deltagerListe.		maa ¨lages
		default:		break;
		}

		skrivDelListeMeny();
		valg = les("\nDeltagerListe: ");
		void nullstillLister();
	} while (valg != 'Q');
}

void Ovelse::skrivDelListeMeny()					// KommandoMeny for deltagerLister.
{
	cout << "\n\nFOLGENDE KOMMANDOER ER TILGJENGELIGE:"
		<< "\n\tS - Skriv ut deltagerliste"
		<< "\n\tN - Lag ny deltagerliste"
		<< "\n\tE - Endre deltagerliste"
		<< "\n\tF - Fjern deltagerliste"
		<< "\n\tQ - Tilbake til ovelsemeny";
}

void Ovelse::skrivDelListe()						// Skriver ut info om alle deltagere i en Ovelse.
{
	char navnTemp[NVLEN], nasjonTemp[NVLEN];
	
	for (int i = 0; i < antDeltagere; i++)
	{												// Henter ut deltagerNavn og nasjon.
		HentNavnOgNasjonFraDeltager(navnTemp, nasjonTemp, i + 1);
		skriv("Navn:\t", navnTemp);					// Skriver ut Navn,
		skriv("Startnr:", i);						// StartNr,
		skriv("ID:\t", i + 1);						// ID og
		skriv("Nasjon:\t", nasjonTemp);				// Nasjon.
	}
}

void Ovelse::nyDelListe()			//lager en ny deltager liste
{
	char fil[20];
	bool sjekk=false;
	strcpy(fil, filNavn());		//finner riktig filnavn
	
	ifstream inn(fil);
	
	if (!inn)			//hvis filen ikke alerede eksisterer
	{
		inn.close();  //lukk filen
											//gaar gjennom alle deltagerne som skal skrives inn
		for (int i = 1; i <= antDeltagere; i++)
		{														//leser inn deltagere
			cout << "\nDeltager nr. " << i << " Av: " << antDeltagere;
			*(deltagerListe + i) = les("\nSkriv ID-nr. paa deltager som skal legges til startlisten: ", 1, 9999);			
										//sjekker om en deltager allerede er registrert i samme ovelse
			for (int k = 1; k <= i-1; k++)
			{
			if (*(deltagerListe + i) == *(deltagerListe + k))
			{	sjekk = true;	}
			}

			while (!sjekkDeltagerId(*(deltagerListe + i))  ||  sjekk)  //finnes deltageren eller er han registrert fra foor
			{
			//felimeldinger
				if (sjekk)                          //hvis nummeret allerede er registrert
				{	skriv("numeret er allerede registrert!", "");	}
				else                        //hvis det ikke finnes en deltager med det nummeret
				{	skriv("Finner ingen deltager med det nummeret i arkivet!", ""); 	}

				sjekk = false;
																	//leser inn deltagere
				cout << "\nDeltager nr. " << i << " Av: " << antDeltagere;
				*(deltagerListe + i) = les("\nSkriv ID-nr. paa deltager som skal legges til startlisten: ", 1, 9999);				
											//sjekker om en deltager allerede er registrert i samme ovelse
				for (int a = 1; a <= i-1; a++)
				{
					if (*(deltagerListe + i) == *(deltagerListe + a))
					{	sjekk = true;	}
				}
			}
			skriv("startliste er oppdadert med deltager: ", *(deltagerListe + i));  //bekreftelsesmelding
		}
		deltagerSkrivtilFil();												//skriv deltagerlisten til fil
	}
	else													//feilmelding
	{	skriv("En startliste er allerede registrert.", ""); 	}
}

void Ovelse::endreDelListe()
{

}

void Ovelse::fjernDelListe()					// Sletter spesifisert deltagerListe-fil.
{
	char temp[STRLEN];
	strcpy(temp, filNavn());					// Hent filnavn til temp.

	ifstream inn(temp);							// Apne filstrom for temp.STA.
	if (inn)									// Hvis OVxxxx.STA finnes.
	{
		inn.close();							// Lukk filstrom

		if (slettFil(temp))						// og om sletting fungerte
		{
			skriv("Filen er slettet", "");		// Skriv ut melding
		}
		else									// Ellers skriv ut feilmelding.
		{
			skriv("Filen ble ikke slettet", "");
		}
	}
	else									   // Hvis OVxxxx.STA ikke finnes skriv feilmelding.
	{
		skriv("Finner ingen fil med navn: ", temp);
	}
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
    klokkeslett = les("\n\tKlokkeslett", 0000, 2359);
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
  klokkeslett = les("\nKlokkeslett", 0000, 2359);   // Leser inn klokkeslett.
  klokkeslett = klokkeSjekk(klokkeslett);           // Sjekker at kl. er på riktig format.
}

void Ovelse :: skrivHovedData() {                   // Skriver hoveddata for en ovelse.
  int aar, maaned, dag, time, minutt;


  aar = dato / 10000;                               // Finner hvilke år det er.
  maaned = (dato / 100) % 100;                      // Finner hvilke måned det er.
  dag = dato % 100;                                 // Finner hvilke dag det er.

  time = klokkeslett / 100;                         // Finner time fra klokkeslett.
  minutt = klokkeslett % 100;                       // Finner minutt fra klokkeslett.


  cout << "\n\nID:                " << nr
       << "\nNavn:              " << navn
       << "\nAntall deltagere:  " << antDeltagere
       << "\nDato:              "                   // Skriver ut dato paa leslig form.
       << ((dag < 10) ? "0" : "") << dag << "."
       << ((maaned < 10) ? "0" : "") << maaned << "."
       << aar
       << "\nKlokkeslett:       "                   // Skriver ut klokkeslett paa leslig form.
       << ((time < 10) ? "0" : "") << time << ":"
       << ((minutt < 10) ? "0" : "") << minutt;

// Trenger ikke denne?
//	if (maaling == PoengX )
//	  cout << "\nMaalingsType:      " << "PoengX";  // Skriver ut maalingstypen for ovelsen:
//	else if(maaling == PoengXX)
//	  cout << "\nMaalingsType:      " << "PoengXX";
//	else if (maaling == MinSECTidel)
//	  cout << "\nMaalingsType:      " << "MinSECTidel";
//	else if (maaling == MinSecHundredel)
//	  cout << "\nMaalingsType:      " << "MinSecHundredel";
//	else if (maaling == MinSekTusendel)
//	  cout << "\nMaalingsType:      " << "MinSekTusendel";
}

void Ovelse::menyValgResListe()					    // ValgSwitch for resultatLister.
{
	char valg;
	
	do
	{
		skrivResListeMeny();
		valg = les("\nResultatLister: ");

		switch (valg)
		{
		case 'S': skrivResultatliste(); 		break;	// Skriver ut en resultatListe.
		case 'N': nyResultatListe();			break;	// Lager en ny resultatListe.
		case 'F': fjernResultatliste();			break;	// Fjerner en resultatListe.
		default:								break;
		}

	} while (valg != 'Q');

}

void Ovelse::skrivResListeMeny()					// KommandoMeny for resultatLister.
{
	cout << "\n\nFOLGENDE KOMMANDOER ER TILGJENGELIGE:"
		<< "\n\tS - Skriv ut resultatliste"
		<< "\n\tN - Ny resultatliste"
		<< "\n\tF - Fjern resultatliste"
		<< "\n\tQ - Tilbake til hovedmeny";
}


