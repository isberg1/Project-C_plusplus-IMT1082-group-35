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
}
													// destructor
Grener::~Grener()
{	
	delete listGren; 
}

void Grener::skrivMeny()					        // skriver menyen i GrenerObj
{
	char valgGrener = 'k';

	do												// lupper til brukeren taster 'Q'
	{												// meny
		cout  << "\n\nMENY FOR GRENER:"
			  << "\n\tN - Ny gren"
			  << "\n\tE - Endre gren"
			  << "\n\tA - Display alle grener"
			  << "\n\tS - Display en gren"
			  << "\n\tQ - Tilbake til hovedmeny";
		valgGrener = les("\nGrener: ");	    		// les brukervalg

		switch (valgGrener)							// kjor brukervalg
		{
		case 'N':	nyGren();			break;		// G N
		case 'E':	endreGren();		break;		// G E
		case 'A':	skrivAllGrener();	break;		// G A
		case 'S':	skrivEnGren();		break;		// G S
		}

	} while (valgGrener != 'Q');

}
													// Registrer ny gren
void Grener::nyGren()								// til komando G N
{
	char buffer[NVLEN];
	Gren *temp;
													// les inn navn pa ny gren
	les("Skriv unikt navn", buffer, NVLEN);

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

void Grener::endreGren()							// Endre navnet paa en eksisterende gren : Valg G E
{
	int valg;
	Gren *gren;

	if (listGren && !listGren->isEmpty()) {         // Hvis listen finnes og det er elementer i den.
      cout << "\nGrener som kan velges: \n";

      skrivUtRegistrerteGrener();                   // Skriver ut oversikt over tilgjengelige grener.

      valg = les("\n\nVelg nr", 1, listGren->noOfElements());
      gren = (Gren*) listGren->removeNo(valg);      // Tar gren-objektet ut av lista.
      gren->endreNavn();                            // Endrer navnet paa grenen.
      cout << "\n\nGrenen har blitt endret, dataene er naa:";
      gren->display();                              // Displayer endringer.
      listGren->add(gren);                          // Legger tilbake i lista.

      skrivTilFIl();                                // Skriver til fil.
	}
	else
	  cout << "\n\tIngen grener er registrert";
}

void Grener::skrivAllGrener()						// til komando G A
{
	Gren *temp;

	if (!listGren->isEmpty())						// hvis listen ikke er tom
	{												// ga gjennom alle Grenobj i listen

		for (int i = 1; i <= listGren->noOfElements(); i++)
		{													// ta obj ut av liste, skriv data og legg obj i liste
			temp = (Gren*)listGren->removeNo(i);
			temp->display();
			listGren->add(temp);
		}
	}
}

void Grener::skrivEnGren()							// til komando G S
{
  Gren *gren;
  int valg;

  if (listGren && !listGren->isEmpty()) {           // Hvis listen finnes og det er elementer i den.
    cout << "\nGrener som kan velges:\n";

    skrivUtRegistrerteGrener();                     // Skriver ut oversikt over tilgjengelige grener.
                                                    // Bruker velger gren.
    valg = les("\n\nVelg nr", 1, listGren->noOfElements());
    gren = (Gren*) listGren->removeNo(valg);        // Valgt gren fjernes fra liste.
    gren->display();                                // Skriv grendata.

    if (gren->hentAntalOvelser() > 0)               // hvis en eller flere ovelser er registrer:
      gren->skrivOvelse();                          // skriv data om alle ovelsene.
    else
      cout << "\n\tIngen ovelser er registrert paa denne grenen";
    listGren->add(gren);                            // Legger objektet tilbake i lista.
  }
  else                                              // Hvis ingen ligger i listen.
    cout << "\n\tIngen grener er registrert";
}
													// skriv til fil
void Grener::skrivTilFIl()
{
	ofstream ut("GRENER.DTA");
	Gren *ptr;					                    // skriv egne datamedlemmer til fil

	int antalIListe = listGren->noOfElements();

	skriv(ut, antalIListe);
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
	{	cout << "\nFinner ikke filen 'GRENER.DTA'";	}
}

void Grener :: ovelseGrenMeny() {                   // Velger navn paa gren og kaller meny for ovelse.
  Gren *gren;
  int valg;

  if (listGren && !listGren->isEmpty()) {           // Hvis listen finnes og det er elementer i den.
    cout << "\nGrener som kan velges:" << "\n\n";   // Skriver ut lederteskt.
    skrivUtRegistrerteGrener();                     // Skriver ut oversikt over tilgjengelige grener.
                                                    // Bruker velger gren.
    valg = les("\n\nVelg nr", 1, listGren->noOfElements());
    gren = (Gren*) listGren->removeNo(valg);        // Valgt gren fjernes fra liste.
    gren->menyValgOvelse();                         // Kaller gren sin funksjon.
    listGren->add(gren);                            // Legger objektet tilbake i lista.
  }
  else                                              // Hvis ingen ligger i listen.
    cout << "\n\tIngen grener er registrert"
         << "\n\tDu maa registrere grener for du lager ovelser for den";
}

void Grener::addTilLIst(Gren * ptr)		            //lar et Gren Objekt utenfor listen legge seg selv til listen
{										            //brukes til aa lagre endringer i OvelsesObjekter
	if (listGren != nullptr)
	{	listGren->add(ptr); 	}
}

void Grener::fjernFraList(char navn[])			    //lar et Gren Objekt inni listen ta seg selv ut av listen
{													//brukes til aa lagre endringer i OvelsesObjekter
	Gren *ptr;

	if (listGren != nullptr)
	{
		if (listGren->inList(navn))
		{	ptr = (Gren*)listGren->remove(navn);	}
	}
}

void Grener :: skrivUtRegistrerteGrener() {         // Skriver ut alle registrerte gren-objekter.
  Gren *gren;
  int newLineTeller = 1;
                                                    // Looper gjennom alle elementer.
  for (int i = 1; i <= listGren->noOfElements(); i++) {
	gren = (Gren*) listGren->removeNo(i);           // Fjerner objekt fra liste.
    cout << "nr " << i << ": ";
    gren->skrivGrenNavn();                          // Skriver ut text (navnet).
    listGren->add(gren);                            // Legger tilbake i listen.

    if (newLineTeller % 3 == 0)                     // Skriver ut "new line" hvis 3 grener
      cout << '\n';                                 // ligger etter hverandre pa skjermen.
    newLineTeller++;                                // Teller opp med en.
  }
}

