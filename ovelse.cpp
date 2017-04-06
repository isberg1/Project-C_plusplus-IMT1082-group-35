//ovelse.cpp alle

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>
#include <sstream>
#include <string.h>
#include <iomanip>
#include "OVELSE.H"
#include "ENUM.H"
#include "GRENER.H"
#include "DELTAGERE.H"
#include "DELTAGER.H"
#include "DELTAGERE.H"


using namespace std;

extern Grener grenenerObj;
extern Deltagere deltagerObj;



Ovelse::Ovelse() {
	cout << "\nAdvarsel, Ovelse-objekter skal ikke lages uten parameter";
}

Ovelse::Ovelse(ifstream & inn)
{
	lesFraFil(inn);

	antDeltagere = 0;
	if (navnTeller < nr)					//setter verdien til navnteller.
	{
	navnTeller = nr;
	}

	for (int i = 0; i <= ANTALLVINNERE + 1; i++)      // Nullstiller log arrayen.
	{	log[i] = 0;	}

	deltagerListe = resultatListe = nullptr;
}

                                                    // Constructor,får param. navn,sisteOvelse fra Gren.
Ovelse :: Ovelse(char *ovelseNavn, registerTidPoeng typeMaaling) {

  nr = lagUniktNr();						        // Faar et unikt nummer basert på static int navnTeller.
  maaling = typeMaaling;							// Faar enumen fra Gren.

  navn = konverter(ovelseNavn);                     // Setter navn fra parameter.
                                                    // Les inn antall deltagere.
  antDeltagere = 0;
  endreDato();                                      // Setter dato.
  endreKlokkeslett();                               // Setter klokkeslett.
  deltagerListe = resultatListe = nullptr;

  for (int i = 0; i <= ANTALLVINNERE + 1; i++)      // Nullstiller log arrayen.
    log[i] = 0;

  if (navnTeller < nr)					            // Setter verdien til navnteller.
  {
	  navnTeller = nr;
  }
}

Ovelse::~Ovelse()	//destructor
{
	delete[] navn;

}

char *Ovelse::filNavn(int type)		                // Send med 1 for .RES eller ingenting for .STA
{
		char name[15] = "OV";
		char end[5] = ".STA";
		char *middle;
		char *fulltnavn;
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
        fulltnavn = konverter(name);                // Gjor om name til peker.

		return fulltnavn;							// Returnerer det unike filnavnet
}

void Ovelse::skrivTilFil(ofstream & ut)		        // Skriv ovelse til fil.
{
				//skriver egne datamedlemmer til fil
	skriv(ut, nr);
	skriv(ut, dato);
	skriv(ut, klokkeslett);
	skriv(ut, navn);

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

void Ovelse::lesFraFil(ifstream & inn)		        // Les ovelse fra fil.
{
	int dummy;
				//leser egne datamedlemmer fra fil
	nr = lesInt(inn);
	dato = lesInt(inn);
	klokkeslett = lesInt(inn);
	navn = lesTxt(inn);
						//loggen leser fra .RES fil istede  Alex
	dummy = lesInt(inn);

	antDeltagere = 0;								// AntDeltagere blir satt av DeltagerListen.

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

void Ovelse::nyResultatListe()	                    // Lager ny resultatliste.
{
	char x[20];
	char t[20];
	strcpy(t, filNavn(1));
	strcpy(x, filNavn());

	ifstream inn(x);
	ifstream inn2(t);


	if (inn)																//hvis en deltagerliste finnes
	{
		alokerMinne();
		nullstillLister();
		deltagerLesFraFil();			//leses inn for aa finne akuelle deltagere og "antDeltagere"
		inn.close();

		if (!inn2)														//hvis en resultatliste ikke finnes
		{

			skriv("Skriv in resultater (hvis en deltager har brutt, ikke moott eller blit disket tast -1):", "");
			for (int i = 1; i <= antDeltagere; i++)
			{
					skriv("Skriv inn resutatet for deltager: ", *(deltagerListe + i));
					*(resultatListe + i) = skaffVerdi();				//leser inn gyldige verdier til resultatlisten
			}

			bubbleSort();

			if (maaling == PoengX || maaling == PoengXX)	//hvis det maales poeng
			{
				korigerVinnerePoeng();		//sjekker om to deltagere har samme verdi og spør brukeren om en korreksjon
				okPoengPoeng();	 ;
			}
			else											//hvis det maales tid
			{
				korigerVinnereTid();
				okPoengTid();
			}

			resultaterSkrivTilFil();					//skriv resultater til fil
			nullstillLister();
		}
		else
		{		//lukk filer og skriv ut feilmelding
			inn2.close();
			skriv("Resultatlisten finnes alerede!", "");
		}
		frigiMinne();				//frigi minne og sett pekerne til resultatliste og deltagerliste til nullptr
	}
	else
	{			//lukk filer og skriv ut feilmelding
		inn2.close();
		skriv("Deltagerlisten finnes ikke! lag den foor Resultatliste", "");
	}
}

int Ovelse::lagUniktNr()						    // Returnerer et unikt tall til datamedlemm "nr".
{
	return (++navnTeller);					//advarsel ma aldri telles ned
}

int Ovelse::skaffVerdi()                            // Leser inn gyldige verdier til resultatliste.
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

			if (min + sec == 0)			//en gjennomforingstid paa 0 akksepteres ikke
			{	tidel = les("nSkriv resultat i tidelssekunder: ", 1, 9);	}
			else
			{	tidel = les("nSkriv resultat i tidelssekunder: ", 0, 9);	}

			return ((min * 1000) + (sec * 10) + tidel); 					// maxverdi 120 59 9
		}
	}
	else if (maaling== MinSecHundredel)				//tid
	{
		min = les("\nSkriv resultat i minutter: ", -1, 120);
		if (min != -1)
		{
			sec = les("\nSkriv resultat i sekunder: ", 0, 59);

			if (min + sec == 0)			//en gjennomforingstid paa 0 akksepteres ikke
			{	hundredel = les("\nSkriv resultat i hundredelssekunder: ", 1, 99);	}
			else
			{	hundredel = les("\nSkriv resultat i hundredelssekunder: ", 0, 99);	}

			return ((min * 10000) + (sec * 100) + hundredel); 					// maxverdi 120 59 99
		}
	}
	else if (maaling== MinSekTusendel)			//tid
	{
		min = les("\nSkriv resultat i minutter: ", -1, 120);
		if (min != -1)
		{
			sec = les("\nSkriv resultat i sekunder: ", 0, 59);

			if (min + sec == 0)			//en gjennomforingstid paa 0 akksepteres ikke
			{	tusendel = les("\nSkriv resultat i tusendelssekunder: ", 1, 999);	}
			else
			{	tusendel = les("\nSkriv resultat i tusendelssekunder: ", 0, 999);	}

			return ((min * 10000) + (sec * 1000) + tusendel); 					// maxverdi 120 59 999
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

void Ovelse::bubbleSort()                           // Sorterer 2 int arrayer.
{
		int dummy;
		int temp;
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

void Ovelse::fjernPoeng()				            // Reduserer tidliger fordelte poeng og medaljer.
{
	int poengTeller = 7;

		for (int i = 1; i <= ANTALLVINNERE; i++)	//gaa gjennom alle som har faat poeng tidligere
		{
			if (log[i] != -1)
			{
				StatistikkRaport(0, log[i], poengTeller); //reduser poeng og medaljefordelingen til nasjoner
				poengTeller--;		//tell ned antal poeng som gis neste gang
			}
		}
}

void Ovelse::okPoengPoeng()				            // Oker antall poeng naar maaletypen er poeng.
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

void Ovelse::okPoengTid()                           // Oker antall poeng naar maaletypen er tid.
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

void Ovelse::alokerMinne()		//oppretter 2 int arrayer
{
	deltagerListe = new int[MAXDELTAGERE + 1];	    // Setter deltagerListe peker til en int array.
	resultatListe = new int[MAXDELTAGERE + 1];		// Setter resultatListe peker til en int array.
}

void Ovelse::frigiMinne()		//destruerer 2 int arrayer
{
	delete[]deltagerListe;    // Setter deltagerListe peker til en int array.
	delete[]resultatListe;		// Setter resultatListe peker til en int array.

	deltagerListe = resultatListe = nullptr;

}

void Ovelse::skrivResultatliste()			        // Skriv resultatlisten til skjerm.
{

	char fil[STRLEN];
	char nv[STRLEN];
	char nasj[STRLEN];
	int min, sec, tid;
	int lupTeller;

	strcpy(fil, filNavn(1));
	ifstream inn(fil);

	if (inn)						//hvis .RES fil finnes
	{
		alokerMinne();
		resultaterLesFraFil();		//les inn resultatliste fra fil
		inn.close();				//lukk fil
		lupTeller = antDeltagere;
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
		frigiMinne();
	}
	else
	{	skriv("Finner ingen fil med navn: ", fil);	}
}

void Ovelse::deltagerSkrivtilFil()			        // Skriv startliste til fil.
{
	char fil[20];
	strcpy(fil, filNavn());				//hent riktig filnavn

	ofstream ut(fil);
	skriv(ut, antDeltagere);

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

void Ovelse::resultaterLesFraFil()			        // Leser inn resultatlista fra fil.
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
		{
			korigerVinnerePoeng();		//hvis 2 resultater er like så må vinneren av dem avgjoores
			okPoengPoeng();				// tildel nye poeng og medaljer
		}
		else							//hvis maaling er tid
		{
			korigerVinnereTid();   //hvis 2 resultater er like så må vinneren av dem avgjoores
			okPoengTid();		   // tildel nye poeng og medaljer
		}

		resultaterSkrivTilFil();  //sriv til fil
	}
}

void Ovelse::deltagerLesFraFil()			        // Leser inn deltagerlisten fra fil.
{
	char fil[20];
	strcpy(fil, filNavn());					//hent riktig filnavn

	ifstream inn(fil);

	if (inn)					//hvis .STA finnes
	{
		antDeltagere = lesInt(inn);
		for (int i = 1; i <= antDeltagere; i++)
		{									//les inn deltagerlisten
			*(deltagerListe + i) = lesInt(inn);
		}
	}
	else								//feilmelding
	{	skriv("Finner ingen fil med navn: ", fil); 	}
	inn.close();		//lukk  fill
}

void Ovelse::sjekkID(int & temp, char buffer[])	    // Reurnerer Ovelsens ID nummer og navn,   brukes til aa skrive ut data.
{
	temp = nr;
	strcpy(buffer, navn);
}

bool Ovelse::fjernResultatliste()					// Fjerner en eksisterende resultatliste.
{

	char temp[STRLEN];
	strcpy(temp, filNavn(1));

	ifstream inn(temp);

	logResett();

	if (inn)	//hvis OVxxxx.RES finnes
	{
		alokerMinne();
		nullstillLister();

		resultaterLesFraFil();				//les inn resultatlisten fra fil
		inn.close();						//lukk fil

		if (slettFil(temp))					//slett filen fra HDD
		{
			skriv("Filen er slettet", "");	//bekreftelsesmelding
			fjernPoeng();					//trekker tilbake tidligere tildelte poeng
			frigiMinne();
			return true;
		}
		else
		{									//feilmelding
			skriv("Filen ble ikke slettet", "");
			frigiMinne();
			return false;
		}
	}
	else
	{										//feilmelding
		skriv("Finner ingen fil med navn: ", temp );
		return false;
	}
}

int Ovelse::hentId()			                    // Returnerer Ovelsens unike ID nummer.
{
	return nr;
}

void Ovelse::nullstillLister()				        // Nullstiller start- og resultatlister.
{
	for (int i = 1; i <= antDeltagere; i++)
	{
		*(deltagerListe + i) = *(resultatListe + i) = 0;
	}
}

void Ovelse::logResett()						    // Nullstiller log.
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
		valg = les("\nOvelser/DeltagerListe: ");

		switch (valg)
		{
		case 'S': skrivDelListe();	    break;		// Skriver ut en deltagerListe.		maa ¨lages
		case 'N': nyDelListe();			break;		// Lager en ny deltagerListe.
		case 'E': endreDelListe();		break;		// Endrer en deltagerListe.			maa ¨lages
		case 'F': fjernDelListe();		break;		// Fjerner en deltagerListe.		maa ¨lages
		}

	} while (valg != 'Q');
}

void Ovelse::skrivDelListeMeny()					// KommandoMeny for deltagerLister.
{
	cout << "\n\nMENY FOR DELTAGERLISTE:"
		<< "\n\tS - Skriv ut deltagerliste"
		<< "\n\tN - Lag ny deltagerliste"
		<< "\n\tE - Endre deltagerliste"
		<< "\n\tF - Fjern deltagerliste"
		<< "\n\tQ - Tilbake til ovelsemeny";
}

void Ovelse::skrivDelListe()						// Skriver ut info om alle deltagere i en Ovelse.
{
	char navnTemp[NVLEN], nasjonTemp[NVLEN];

	char fil[NVLEN];
	strcpy(fil, filNavn());

	ifstream inn(fil);

	if (inn)			//hvis en deltagerliste finnes
	{
		alokerMinne();

		deltagerLesFraFil();

		for (int i = 1; i <= antDeltagere; i++)
		{												// Henter ut deltagerNavn og nasjon.
			HentNavnOgNasjonFraDeltager(navnTemp, nasjonTemp, *(deltagerListe + i));
			skriv("\nNavn:\t", navnTemp);					// Skriver ut Navn,
			skriv("ID:\t", *(deltagerListe + i));						// ID og
			skriv("Nasjon:\t", nasjonTemp);				// Nasjon.
		}
		frigiMinne();
	}
	else     //hvis en deltagerliste ikke finnes
	{	skriv("Ingen deltagerliste er registrert.", "");	}
}

void Ovelse::nyDelListe()			                // Lager en ny deltager liste.
{
	char fil[20];
	bool sjekk=false;
	strcpy(fil, filNavn());		//finner riktig filnavn

	ifstream inn(fil);

	if (!inn)			//hvis filen ikke alerede eksisterer
	{
		inn.close();  //lukk filen
		alokerMinne();

		do
		{
			//finner ut Hvor mange deltagere som skal registreres
			antDeltagere = les("Skriv inn antall deltagere som skal registreres: ", 2, deltagerObj.antallRegistrerteDeltagere());
			if (antDeltagere >= MAXDELTAGERE)		//sjekker at det ikke er for mange deltagere;
			{	skriv("max antal deltagere er :", MAXDELTAGERE);	}

		} while (antDeltagere >= MAXDELTAGERE);

											//gaar gjennom alle deltagerne som skal skrives inn
		for (int i = 1; i <= antDeltagere; i++)
		{														//leser inn deltagere
			cout << "\nDeltager nr. " << i << " Av: " << antDeltagere;
			*(deltagerListe + i) = les("\nSkriv ID-nr. paa deltager som skal legges til startlisten: ", 100, 9999);
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
				{	skriv("deltageren er allerede registrert!", "");	}
				else                        //hvis det ikke finnes en deltager med det nummeret
				{	skriv("Finner ingen deltager med det nummeret i arkivet!", ""); 	}

				sjekk = false;
																	//leser inn deltagere
				cout << "\nDeltager nr. " << i << " Av: " << antDeltagere;
				*(deltagerListe + i) = les("\nSkriv ID-nr. paa deltager som skal legges til startlisten: ", 100, 9999);
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
		frigiMinne();
	}
	else													//feilmelding
	{	skriv("En startliste er allerede registrert.", ""); 	}
}

void Ovelse::endreDelListe()
{

	bool sjekk=false;
	int valg;
	int temp;
	char buffer[STRLEN];
	char fil[NVLEN];
	strcpy(buffer, filNavn());						// Henter filnavnet til .STA-fil.
	strcpy(fil, filNavn(1));						// Henter filnavnet til .RES-fil.

	ifstream inn(buffer);								// Henter .STA-fil.
	ifstream inn2(fil);									// Henter .RES-fil.

	if (!inn2)		//hvis det ikke finnes en resultatliste
	{
		if (inn)	//hvis det finnes en deltagerliste
		{
			alokerMinne();									// Oppretter arrayer for bruk.
			deltagerLesFraFil();							// Leser inn i memory fra .STA fil.

			valg = les("skriv (1) for aa legge til en deltager, \n\teller\n\tskriv (2) for aa fjerne en deltager: ", 1, 2);


			if (valg == 1) //hvis brukeren valgte  aa legge til en deltager
			{
				if (antDeltagere <  deltagerObj.antallRegistrerteDeltagere())	//sjekker om det er flere deltagere globalt som kan legges til
				{
					if (antDeltagere < MAXDELTAGERE)		//hvis det er plass til flere deltagere
					{
						antDeltagere++;
						*(deltagerListe + antDeltagere) = les("skriv ID-en til deltageren du onsker aa legge til", 100, 9999);

						for (int i = antDeltagere; i >= 2; i--)
						{
							if (*(deltagerListe + antDeltagere) == *(deltagerListe + (i - 1)))  //hvis deltageren er registrert fra for
							{
								tr(i);
								sjekk = true;
							}
						}

						while (!sjekkDeltagerId(*(deltagerListe + antDeltagere)) || sjekk)  //finnes deltageren eller er han registrert fra foor
						{
							//felimeldinger
							if (sjekk)                          //hvis nummeret allerede er registrert
							{	skriv("deltageren er allerede registrert!", "");		}
							else                        //hvis det ikke finnes en deltager med det nummeret
							{	skriv("Finner ingen deltager med det nummeret i arkivet!", "");		}

							sjekk = false;
							//leser inn deltagere
							*(deltagerListe + antDeltagere) = les("\nskriv ID-en til deltageren du onsker aa legge til", 100, 9999);

							//sjekker om en deltager allerede er registrert i samme ovelse
							for (int i = antDeltagere; i >= 2; i--)
							{
								if (*(deltagerListe + antDeltagere) == *(deltagerListe + (i - 1)))  //hvis deltageren er registrert fra for
								{	sjekk = true;	}
							}
						}
						skriv("startliste er oppdadert med deltager: ", *(deltagerListe + antDeltagere));  //bekreftelsesmelding
						deltagerSkrivtilFil();							// Skriver memory til fil.
						frigiMinne();									// Fjerner arrayer fra memory etter bruk.
					}
					else
					{	skriv("Maxsimalt antall deltagere er allerede registert.", "");		}
				}
				else
				{	skriv("Finnes ikke flere deltagere globalt aa legge til", "");			}
		    }

			if (valg==2)													//brukeren har valgt aa slette en deltager
			{
				if (antDeltagere > MINDELTAGERE)	//en startliste maa ha mist 2 deltagere
				{

					for (int i = 1; i <= antDeltagere; i++)						//skriv ut bukervalgene
					{
						cout << "\ntast: " << i << " for a slette deltager: " << *(deltagerListe + i);
					}
					temp = les("\nslett: ", 1, antDeltagere);					//brukeren skriver inn sitt valg

					*(deltagerListe + temp) = *(deltagerListe + antDeltagere);  // Slett deltager fra liste,
					*(deltagerListe + antDeltagere) = 0;						// overskriv med siste deltager og
					antDeltagere--;												// tell ned registrerte deltagere.

					skriv("startliste er oppdadert", "");						//bekreftelsesmelding
					deltagerSkrivtilFil();										// Skriver memory til fil.
					frigiMinne();
					// Fjerner arrayer fra memory etter bruk.
				}
				else   //hvis det er for faa deltagere i startlisten
				{	skriv("en startliste maa ha mist 2 deltagere.", "\ndu maa legge til minst en deltager til, for du kan slette flere");	}
			}
		}
		else   //hvis det ikke finnes en deltagerliste
		{	skriv("Ingen deltagerliste er registrert fra for", "");	}
	}
	else    //hvis det  finnes en resultatliste
	{	skriv("En resultatliste finnes alerede, ", "denne maa slettes forst!"); }

}

void Ovelse::fjernDelListe()						// Sletter spesifisert deltagerListe-fil.
{
	char temp[STRLEN];
	char fil[NVLEN];
	strcpy(fil, filNavn(1));
	strcpy(temp, filNavn());						// Hent filnavn til temp.

	ifstream inn(temp);								// Apne filstrom for temp.STA.
	ifstream inn2(fil);

	if (!inn2)		//hvis en .RES fil allerede finnes saa skal brukeren ikke kunne slette .STA filen
	{
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
	else
	{													//hvis en .RES fil eksisterer
		skriv("En resultatliste er allerede lagret,", "\nDenne maa slettes for du kan slette startlisten");
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
    dato = les("\n\tDato", 170101, 201231);
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
	delete[]navn;
	navn = konverter(ovelseNavn);
}

void Ovelse :: endreDato() {                        // Endrer datoen til ovelsen.
  cout << "\nSkriv inn dato for ovelsen (aa mm dd)"; // Lovelig dato-interval: 17.01.01-20.12.31.
  dato = les("\nDato", 170101, 201231);
  dato = datoSjekk(dato);                           // Sjekker at dato er på riktig format.
}

void Ovelse :: endreKlokkeslett() {                 // Endrer kl. til ovelsen.
  cout << "\nKlokkeslett for ovelsen (ttmm)";
  klokkeslett = les("\nKlokkeslett", 0000, 2359);   // Leser inn klokkeslett.
  klokkeslett = klokkeSjekk(klokkeslett);           // Sjekker at kl. er på riktig format.
}

void Ovelse :: skrivHovedData() {                   // Skriver hoveddata for en ovelse.
  int aar, maaned, dag, time, minutt;
  char fil[NVLEN];
  strcpy(fil, filNavn());

  ifstream inn(fil);

  if (inn)
  {
	  alokerMinne();
	  deltagerLesFraFil();		//leses inn for aa finna antall deltagere i ovelsen
	  frigiMinne();
  }

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
       << "20" << aar
       << "\nKlokkeslett:       "                   // Skriver ut klokkeslett paa leslig form.
       << ((time < 10) ? "0" : "") << time << ":"
       << ((minutt < 10) ? "0" : "") << minutt;
}

void Ovelse::korigerVinnerePoeng()									//korigerer for like resultater
{
	int valg;
	int dummy;
	int temp;

	for (int i = 1; i <= antDeltagere-1; i++)						//luup gjennom alle deltagerne
	{
		if (*(resultatListe + i) > -1)										//hvis gyldig resultat
		{
			if (*(resultatListe + i) == *(resultatListe + (i + 1)))		//hvis 2 resultater er like
			{
				cout << "\nDeltager: " << *(deltagerListe + i) << " og " << *(deltagerListe + (i + 1))
					<< " er registrert med samme verdi. \nHvem av den skal ha den beste pallplaseringen? "
					<< "\ntast (1) for Deltager: " << *(deltagerListe + i) << " eller tast (2) for Deltager: "
					<< *(deltagerListe + (i + 1));

				valg = les("\nVelg vinner: ", 1, 2);							//brukerne velger vinneren av de 2

				if (valg==2)											//hvis brukeren velger aa endre rekkefoolgen
				{							//swap resultat array
					dummy = *(resultatListe + i);
					*(resultatListe + i) = *(resultatListe + (i + 1));
					*(resultatListe + (i + 1)) = dummy;
											//swap deltager array
					temp = *(deltagerListe + i);
					*(deltagerListe + i) = *(deltagerListe + (i + 1));
					*(deltagerListe + (i + 1)) = temp;
				}
			}
		}
	}
}

void Ovelse::korigerVinnereTid()
{
	int valg;
	int dummy;
	int temp;

	tr(antDeltagere);
	for (int i = antDeltagere; i >= 2; i--)										//luup gjennom alle deltagerne
	{
		tr(i);
		if (*(resultatListe + i) > 0)													  //hvis gyldig resultat
		{
			if (*(resultatListe + i) == *(resultatListe + (i - 1)))						//hvis 2 like resultater
			{
				cout << "\nDeltager: " << *(deltagerListe + i) << " og " << *(deltagerListe + (i - 1))
					<< " er registrert med samme verdi. \nHvem av den skal ha den beste pallplaseringen? "
					<< "\ntast (1) for Deltager: " << *(deltagerListe + i) << " eller tast (2) for Deltager: "
					<< *(deltagerListe + (i - 1));

				valg = les("\nVelg vinner: ", 1, 2);							//brukeren velger vinneren av de 2

				if (valg == 2)											//hvis brukeren velger aa endre rekkefoolgen
				{							//swap resultat array
					dummy = *(resultatListe + i);
					*(resultatListe + i) = *(resultatListe + (i - 1));
					*(resultatListe + (i - 1)) = dummy;
											//swap deltager array
					temp = *(deltagerListe + i);
					*(deltagerListe + i) = *(deltagerListe + (i - 1));
					*(deltagerListe + (i - 1)) = temp;
				}
			}
		}
	}
}

void Ovelse::menyValgResListe()					    // ValgSwitch for resultatLister.
{
	char valg;

	do
	{
		skrivResListeMeny();
		valg = les("\nOvelser/DeltagerListe: ");
		switch (valg)
		{
		case 'S': skrivResultatliste(); 	break;	// Skriver ut en resultatListe.
		case 'N': nyResultatListe();		break;	// Lager en ny resultatListe.
		case 'F': fjernResultatliste();		break;	// Fjerner en resultatListe.
		}

	} while (valg != 'Q');

}

void Ovelse::skrivResListeMeny()					// KommandoMeny for resultatLister.
{
	cout << "\n\nMENY FOR RESULTATLISTE:"
		<< "\n\tS - Skriv ut resultatliste"
		<< "\n\tN - Ny resultatliste"
		<< "\n\tF - Fjern resultatliste"
		<< "\n\tQ - Tilbake til hovedmeny";
}
