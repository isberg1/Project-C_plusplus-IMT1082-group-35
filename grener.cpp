													// grener.cpp alex


#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>
#include "GRENER.H"
#include"FUNKSJONER.H"
#include"CONST.H"
#include"GREN.H"
#include"ListTool2B.h"


using namespace std;
													// constructor
Grener::Grener()
{

	listGren = new List(Sorted);
													// sisteOvelse = 0;
}
													// destructor
Grener::~Grener()
{	delete listGren;  }
													// skriver menyen i GrenerObj
void Grener::skrivMeny()
{
	char valgGrener = 'k';

	do												// lupper til brukeren taster 'Q'
	{

													// meny
		cout <<"\nPath: Hovedmeny->Grenermeny"
			<< "\n(N) Ny gren"
			<< "\n(E) Endre gren"
			<< "\n(A) Display alle grener"
			<< "\n(S) Display en gren"
			<< "\n(Q) Tilbake til hovedmeny\n";
		valgGrener = les();							// les brukervalg

		switch (valgGrener)							// kjor brukervalg
		{
		case 'N':	nyGren();			break;		// G N
		case 'E':	endreGren();		break;		// G E
		case 'A':	skrivAllGrener();	break;		// G A
		case 'S':	skrivEnGren();		break;		// G S
		default:						break;
		}

	} while (valgGrener != 'Q');

}
													// Registrer ny gren
void Grener::nyGren()								// til komando G E
{
	char buffer[NVLEN];
	Gren *temp;
													// les inn navn pa ny gren
	les("Skriv unikt navn: ", buffer, NVLEN);

	if (!listGren->inList(buffer))					// hvis navnet ikke er i bruk
	{												// lag ny gren og legg det til i listen
		temp = new Gren(buffer);
		listGren->add(temp);
		skriv("Ny gren registrert med navn: ", buffer);

		skrivTilFIl();
	}
	else											// feilmelding
	{	skriv(buffer, "er alerede i bruk"); 	}


}
													// endre navnet paa en eksisterende gren
void Grener::endreGren()							// til komando G E
{
	char buffer[NVLEN];
	Gren *temp;
													// les navn
	les("Skriv unikt navn: ", buffer, NVLEN);


	if (listGren->inList(buffer))					// hvis navnet  er i bruk
	{												// hent objekten, endre navn og legg tilbake i liste
		temp = (Gren*)listGren->remove(buffer);
		do
		{
			temp->endreNavn();
		} while (listGren->inList(buffer));			// looper til brukeren taster inn et unikt navn
		listGren->add(temp);

		skrivTilFIl();
	}
	else											// feilmelding
	{	skriv("Finner ikke navnet: ", buffer);	}
}

void Grener::skrivAllGrener()						// til komando G A
{
	Gren *temp;

	if (!listGren->isEmpty())						// hvis listen ikke er tom
	{												// ga gjennom alle Grenobj i listen

		for (int i = 1; i <= listGren->noOfElements(); i++)
		{
													// ta obj ut av liste, skriv data og legg obj i liste
			temp = (Gren*)listGren->removeNo(i);
			temp->display();
			listGren->add(temp);
		}
	}
}

void Grener::skrivEnGren()							// til komando G S
{
	char buffer[NVLEN];
	Gren *temp;
													// les et navn fra bruker
	les("Skriv navnet pa grenen: ", buffer, NVLEN);

	if ( listGren->inList(buffer))					// hvis navnet finnes
	{												// ta obj ut av liste, skriv data og legg obj i liste
		temp = (Gren*)listGren->remove(buffer);
		temp->display();							// skriv grendata
		if (temp->hentAntalOvelser() > 0 )			// hvis noen ovelser er registrer
		{	temp->skrivOvelse();	}				// skriv data om alle ovelsene
		else
		{	skriv("Ingen ovelse er registrert paa gren: ", buffer);		}
		listGren->add(temp);						// legg obj i list
	}
	else											// feilmelding
	{	skriv("finner ikke gren med navn: ", buffer);	}
}
													// skriv til fil
void Grener::skrivTilFIl()
{
	ofstream ut("GRENER.DTA");
	Gren *ptr;

													// skriv egne datamedlemmer til fil

	int antalIListe = listGren->noOfElements();

	skriv(ut, antalIListe);
	//skriv(ut, sisteOvelse);

													// skriv alle grenobj til fil
	for (int i = 1; i <= listGren->noOfElements(); i++)
	{
		ptr = (Gren*)listGren->removeNo(i);
		ptr->skrivTilFIl(ut);
		listGren->add(ptr);	}
}
													// les fra fil
void Grener::lesFraFil()
{
	ifstream inn("GRENER.DTA");
	int antallIListe;
	char navn[NVLEN];
	Gren *ptr;

	if (inn)										// hvis filen finnes
	{												// les in egne datamedlemmer fra fil
		antallIListe = lesInt(inn);
	 // sisteOvelse = lesInt(inn);


		if (!listGren->isEmpty())					// hvis listen ikke er tom
		{											// slett listn og lag ny
			delete listGren;
			listGren = new List(Sorted);
		}


													// les in alle Grenobj fra fil
		for (int i = 1; i <= antallIListe; i++)
		{											// lag nytt obj og legg det i listen
			lesTxt2(inn, navn);


			ptr = new Gren(inn, navn);
			listGren->add(ptr);
		}
	}
	else											// feilmelding
	{	skriv("\nFinner ikke fil GRENER.DTA\n", "");	}



}

void Grener :: ovelseGrenMeny() 						// Meny til Ovelse : O...
{
	char buffer[NVLEN];
	Gren *temp;

	les("\n\tSkriv inn navn pa Gren", buffer, NVLEN);
	if (listGren->inList(buffer))
	{
		temp = (Gren*)listGren->remove(buffer);
		temp->menyValgOvelse();
		listGren->add(temp);
	}
	else
	{
		cout << "Finner ikke Gren med " << buffer << " som navn.";
	}

}

void Grener::testResListe()
{
	char temp[STRLEN];
	Gren *ptr;
	les("skriv grenens Navn; ", temp, STRLEN);

	if (listGren->inList(temp))
	{
		ptr = (Gren*)listGren->remove(temp);
		ptr->testingNyOvelse();
		listGren->add(ptr);

	}
	else
	{
		skriv("Finner ikke en gren med navn: ", temp);
	}
}

void Grener::testResSkriv()
{
	char temp[STRLEN];
	Gren *ptr;
	les("skriv grenens Navn; ", temp, STRLEN);

	if (listGren->inList(temp))
	{
		ptr = (Gren*)listGren->remove(temp);
		ptr->testingSkrivResListe();
		listGren->add(ptr);

	}
	else
	{
		skriv("Finner ikke en gren med navn: ", temp);
	}
}

char *Grener :: velgGren(char t[]) {                // valg av gren utfra navn.
  Gren *gren;
  int newLineTeller = 1;
  int valg;
  char *returNavn;

  if (listGren && !listGren->isEmpty()) {           // Hvis listen finnes og det er elementer i den.
    cout << t << "\n\n";                            // Skriver ut lederteskt.

                                                    // Looper gjennom alle elementer.
    for (int i = 1; i <= listGren->noOfElements(); i++) {

      gren = (Gren*) listGren->removeNo(i);         // Fjerner objekt fra liste.
      cout << "nr " << i << ": ";
      gren->skrivGrenNavn();                        // Skriver ut text (navnet).
      listGren->add(gren);                          // Legger tilbake i listen.

      if (newLineTeller % 3 == 0)                   // Skriver ut "new line" hvis 6 grener
        cout << '\n';                               // ligger etter hverandre pa skjermen.
      newLineTeller++;                              // Teller opp med en.
    }

                                                    // Bruker velger gren.
    valg = les("\n\nVelg tall", 1, listGren->noOfElements());
    gren = (Gren*) listGren->removeNo(valg);        // Valgt gren fjernes fra liste.
    returNavn = gren->hentNavn();                   // Kaller gren sin funksjon.
    listGren->add(gren);                            // Legger objektet tilbake i lista.

    return returNavn;                               // Returnerer navent på gren.
  }
  else {                                            // Hvis ingen ligger i listen.
    cout << "\n\tIngen grener er registrert";
    return "";                                      // Returnerer "".
  }
}

void Grener::menyValgOvelse()						// MainSwitch for Ovelse.
{
	char valg;

	skrivOvelseMeny();
	valg = les("\nOvelser: ");
	while (valg != 'Q')
	{
		switch (valg)
		{
		case 'N': nyOvelse();		 break;	    // Registrerer en ny Ovelse.
		case 'E': endreOvelse();	 break;		// Endrer informasjon i ne Ovelse.
		case 'F': fjernOvelse();	 break;		// Fjerner en Ovelse.
		case 'A': skrivAlleOvelse(); break;		// Viser hoveddata for alle Ovelser.
		case 'L': menyValgDelListe(); break;	// Sender til deltagerListeSwitch.
		case 'R': menyValgResListe(); break;	// Sender til resultatListeSwitch.
		}
		skrivOvelseMeny();
		valg = les("\nOvelser: ");
	}
}

void Grener::skrivOvelseMeny()					// KommandoMeny for Ovelser.
{
	cout << "\n\nFOLGENDE KOMMANDOER ER TILGJENGELIGE:"
		<< "\n\tN - Ny ovelse"
		<< "\n\tE - Endre ovelse"
		<< "\n\tF - Fjern ovelse"
		<< "\n\tA - Skriv ut alle ovelser"
		<< "\n\tL - Deltagerliste"
		<< "\n\tR - Resultatliste"
		<< "\n\tQ - Tilbake til hovedmeny";
}

void Grener :: nyOvelse() {                     // Hvordan Ny ovelse fungerer atm.
  char *ovelseNavn;
  Gren *gren;

  ovelseNavn = velgGren("\n\nHvilke gren skal det lages ny ovelse for?");

  if (ovelseNavn != "") {                       // Hvis det ble returnert et navn:
    gren = (Gren*) listGren->remove(ovelseNavn);// Fjerner gren fra lista.
    gren->registrerNyOvelse();                  // Registrerer ny Ovelse for gren.
    listGren->add(gren);                        // Legger gren tilbake i lista.
  }
}

void Grener::endreOvelse()
{

}

void Grener::fjernOvelse()
{

}

void Grener::skrivAlleOvelse()
{

}

void Grener::menyValgDelListe()					// ValgSwitch for deltagerLister.
{
	char valg;

	skrivDelListeMeny();
	valg = les("\nDeltagerLister ");
	while (valg != 'Q')
	{
		switch (valg)
		{
		case 'S': skrivDelListe();	    break;	// Skriver ut en deltagerListe.
		case 'N': nyDelListe();			break;	// Lager en ny deltagerListe.
		case 'E': endreDelListe();		break;	// Endrer en deltagerListe.
		case 'F': fjernDelListe();		break;	// Fjerner en deltagerListe.
		default:		break;
		}
		skrivDelListeMeny();
		valg = les("\nDeltagerLister: ");
	}
}

void Grener::skrivDelListeMeny()					// KommandoMeny for deltagerLister.
{
	cout << "\n\nFOLGENDE KOMMANDOER ER TILGJENGELIGE:"
		<< "\n\tS - Skriv ut deltagerliste"
		<< "\n\tN - Lag ny deltagerliste"
		<< "\n\tE - Endre deltagerliste"
		<< "\n\tF - Fjern deltagerliste"
		<< "\n\tQ - Tilbake til hovedmeny";
}

void Grener::skrivDelListe()
{

}

void Grener::nyDelListe()
{

}

void Grener::endreDelListe()
{

}

void Grener::fjernDelListe()
{

}

void Grener::menyValgResListe()					// ValgSwitch for resultatLister.
{
	char valg;

	skrivResListeMeny();
	valg = les("\nResultatLister: ");
	while (valg != 'Q')
	{
		switch (valg)
		{
		case 'S': skrivResListe();		break;	// Skriver ut en resultatListe.
		case 'N': nyResListe();			break;	// Lager en ny resultatListe.
		case 'F': fjernResListe();		break;	// Fjerner en resultatListe.
		default:						break;
		}
		skrivResListeMeny();
		valg = les("\nResultatlister: ");
	}
}

void Grener::skrivResListeMeny()					// KommandoMeny for resultatLister.
{
	cout << "\n\nFOLGENDE KOMMANDOER ER TILGJENGELIGE:"
		<< "\n\tS - Skriv ut resultatliste"
		<< "\n\tN - Ny resultatliste"
		<< "\n\tF - Fjern resultatliste"
		<< "\n\tQ - Tilbake til hovedmeny";
}

void Grener::skrivResListe()
{

}

void Grener::nyResListe()
{

}

void Grener::fjernResListe()
{

}
