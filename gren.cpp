//gren.cpp alex

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>
#include "GREN.H"
#include "OVELSE.H" // fungerer ikke?
#include"FUNKSJONER.H"
using namespace std;

Gren::Gren() 	//constructor uten arg.
{
	cout << "\nAdvarsel GrenConstructor uten arg, skal ikke brukes\n";
}
//constructor med string argument
Gren::Gren(char * a) : TextElement(a)
{
	char buffer[STRLEN];
	int tilEnum;
	//leser inn egne datamedlemmer
	antOvelser = les("Skriv antall ovelser: ", 1, MAXOVELSER);
	antallRegistrerteOvelser = 0;

	cout << "\nskriv type maaling: "
		<< "\n(1) MinSECTidel"
		<< "\n(2) MinSecHundredel"
		<< "\n(3) MinSekTusendel"
		<< "\n(4) PoengX"
		<< "\n(5) PoengXX";
	tilEnum = les("\nskriv type (1),(2),(3),(4),(5)", 1, 5);

	switch (tilEnum)
	{//usikker på hva "antSifre" skal brukens til bare gjetter her
	case 1:	typeMaaling = MinSECTidel;		antSifre = 6; break;
	case 2: typeMaaling = MinSecHundredel;	antSifre = 7; break;
	case 3:	typeMaaling = MinSekTusendel;	antSifre = 8; break;
	case 4: typeMaaling = PoengX;			antSifre = 1; break;
	case 5:	typeMaaling = PoengXX;			antSifre = 2; break;
	}

	les("Skriv inn annet: ", buffer, STRLEN);
	annet = konverter(buffer);
}
//constructor med filargument
Gren::Gren(ifstream & inn, char * a) : TextElement(a)
{
	int tilEnum;

	//leser inn egne datamedlemer
	annet = lesTxt(inn);
	antOvelser = lesInt(inn);
	antSifre = lesInt(inn);
	antallRegistrerteOvelser = lesInt(inn);
	tilEnum = lesInt(inn);

	switch (tilEnum)//konverterer int fra fil til enum
	{
	case 1:	typeMaaling = MinSECTidel;		 break;
	case 2: typeMaaling = MinSecHundredel;	 break;
	case 3:	typeMaaling = MinSekTusendel;	 break;
	case 4: typeMaaling = PoengX;			 break;
	case 5:	typeMaaling = PoengXX;			 break;
	}

	if (antOvelser > 0) //hvis det er registrert noen ovelser i det hele tatt
	{

		//leser inn ovelser fra fil
		for (int i = 1; i <= antallRegistrerteOvelser; i++)
		{
			 array[i]->lesFraFil(inn);
		}
	}
}
//destructor
Gren::~Gren()
{
	delete[] annet;
	for (int i = 1; i <= antOvelser; i++)
	{	delete array[i];	}	//sletter alle Ovelsesobjekter

}

void Gren::endreNavn()// til komado G E
{//sletter exsisterende navn først og så hentes et nytt navn
	char buffer[NVLEN];

	les("Skriv nytt unikt navn: ", buffer, NVLEN);
	delete []text;
	text = konverter(buffer);
}
//skriver alle data om denne grenen
void Gren::display()	//til komando G A
{
	skriv("Grenens navn er: ", text);
	skriv("antall ovelser er:", antOvelser);
	skriv("Annet: ", annet);


	if (typeMaaling == MinSECTidel)
	{	skriv("Maalingstype er: ","MinSECTidel");		}
	if (typeMaaling == MinSecHundredel)
	{	skriv("Maalingstype er: ","MinSecHundredel");	}
	if (typeMaaling == MinSekTusendel)
	{	skriv("Maalingstype er: ","MinSekTusendel");	}
	if (typeMaaling == PoengX)
	{	skriv("Maalingstype er: ","PoengX");			}
	if (typeMaaling == PoengXX)
	{	skriv("Maalingstype er: ","PoengXX");			}
}
//skriver alle data om alle ovelser
void Gren::skrivOvelse()//til komando G S
{
	for (int i = 1; i <= antallRegistrerteOvelser; i++)
	{	array[i]->skrivData();	}
}
//til fil
void Gren::skrivTilFIl(ofstream & ut)
{
	//skriver egne datamedlemmer til fil
	skriv(ut, text);	//navnet
	skriv(ut, annet);
	skriv(ut, antOvelser);
	skriv(ut, antSifre);
	skriv(ut, antallRegistrerteOvelser);

	//skriver enum til fil som en int mellom 0 til 4
	if (typeMaaling == MinSECTidel)
	{	skriv(ut, 1);   }
	if (typeMaaling == MinSecHundredel)
	{	skriv(ut, 2);	}
	if (typeMaaling == MinSekTusendel)
	{	skriv(ut, 3);	}
	if (typeMaaling == PoengX)
	{	skriv(ut, 4);	}
	if (typeMaaling == PoengXX)
	{	skriv(ut, 5);	}

	if (antallRegistrerteOvelser > 0) //hvis det er registrer noen ovelser i det hele tatt
	{
		//skriver ovelsesobjekter til fil
		for (int i = 1; i <= antallRegistrerteOvelser; i++)
		{	array[i]->skrivTilFil(ut);	}
	}

}

void Gren :: skrivGrenNavn() {                      // Skriver ut navnet på grenen.
  cout << '\t' << text;
}

int Gren::hentAntalOvelser()
{
	return antallRegistrerteOvelser;
}

void Gren :: registrerNyOvelse() {                  // Registrerer ny Ovelse.               : O N
  char buffer[STRLEN];
  char *ovelseNavn;

  if (antallRegistrerteOvelser < antOvelser ) {     // Hvis det er plass i array.

    les ("\nNavnet paa ovelsen", buffer, NVLEN);    // Leser inn navnet på ovelsen.
    ovelseNavn = konverter(buffer);                 // Lager ny char og setter korrekt lengde.

    if (!finnesOvelse(ovelseNavn)) {                // Hvis Ovelsen ikke finnes i array:

                                                    // Lager peker til ny Ovelse på neste ledige indeks,
                                                    // oppretter Ovelse-objekt, sender med navn og enum,
      array[++antallRegistrerteOvelser] = new Ovelse(ovelseNavn, typeMaaling); // +1 i array-teller.
    }
    else                                            // Hvis Ovelsen allerede finnes:
      cout << "\n\tDet finnes allerede en ovelse med dette navnet i grenen";
  }
  else                                              // Hvis array er full:
    cout << "\n\tDet er ikke plass til flere ovelser for denne grenen";
}

void Gren :: endreOvelseMeny() {                    // Meny for hva som kan endres for en Ovelse.
  cout << "\n\nFOLGENDE KOMMANDOER ER TILGJENGELIGE:"
       << "\n\tN - Navnet paa ovelsen"
       << "\n\tE - Datoen ovelsen er"
       << "\n\tA - Klokkeslett ovelsen starter"
       << "\n\tQ - Tilbake til Ovelsers meny";
}

void Gren :: endreOvelse() {                        // Endrer data for en Ovelse.           : O E
  int nr, indeks;
  char valg;

  if (antallRegistrerteOvelser != 0) {              // Hvis array med Ovelser ikke er tom:

    cout << "\nTilgjengelige ovelser:\n";
    skrivUtRegistrerteOvelser();                    // Skriver ut nr og navn på ovelser i array.
    nr = les("\nHvilke ovelse vil du endre paa? (tall)", 1, antallRegistrerteOvelser);

    // Finn indeksen til valgt ovelse
    // Trenger funksjon som looper ovelser, hvis nr == nr, return indeks.

    endreOvelseMeny();                              // Skriver ut hvilke valg som kan foretas.
    valg = les("\nOvelser/Endre ovelse: ");
    while (valg != 'Q') {
      switch (valg) {
        case 'N' :      break;
        case 'E' :      break;
        case 'A' :      break;
        default  : endreOvelseMeny(); break;
      }
      endreOvelseMeny();
      valg = les("\nOvelser/Endre ovelse: ");
    }
  }
  else
    cout << "\n\tDet er ikke registrert noen ovelser for denne grenen";

  // cout hvilke ovelse vil du endre på? (skriv in nr)
  // Loop til Nr er skrevet inn korrekt
  // Meny over valg; navn, dato, klokkeslett.
  // 3 funksjoner i Ovelse, hver endrer sin data.

}

void Gren :: fjernOvelse() {                        // Fjerner en Ovelse.                   : O F

}

void Gren :: skrivHoveddataOvelser() {              // Skriver hoveddata for alle Ovelser.  : O A

}

bool Gren :: finnesOvelse(char *navn) {             // Sjekk om Ovelsen finnes i array med param. navn.
  char *navnIarray;
  navn = konverterTilStore(navn);                   // Gjør om parameters navn til store bokstaver.

  for (int i = 1; i <= antallRegistrerteOvelser; i++) { // Looper gjennom array.
    navnIarray = konverterTilStore(array[i]->hentNavn()); // Gjør om til store bokstaver.

    if ( strcmp(navn, navnIarray ) == 0)            // Hvis medsendt param er lik Ovelses navn.
      return true;
  }
}

void Gren :: skrivUtRegistrerteOvelser() {          // Skriver ut alle registrerte ovelser.
  int newLineTeller = 1;
                                                    // Looper gjennom array med ovelser.
  for (int i = 1; i <= antallRegistrerteOvelser; i++) {
    cout << '\t' << i;                              // Skriver ut indeks i array.
    array[i]->skrivNavn();                          // Skriver ut navnet paa ovelsen.

    if (newLineTeller % 6 == 0)                     // Legger paa linjeskift hvis 6 ovelser
      cout << '\n';                                 // ligger etter hverandre på skjermen.
    newLineTeller ++;                               // Teller opp med en.
  }
}


