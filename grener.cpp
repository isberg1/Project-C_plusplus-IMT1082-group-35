//grener.cpp alex


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
//constructor
Grener::Grener()
{

	listGren = new List(Sorted);
	sisteOvelse = 0;
}
//destructor
Grener::~Grener()
{	delete listGren;  }
//skriver menyen i GrenerObj
void Grener::skrivMeny()
{
	char valgGrener = 'k';

	do			//lupper til brukeren taster 'Q'
	{

		//meny
		cout <<"\nPath: Hovedmeny->Grenermeny"
			<< "\n(N) Ny gren"
			<< "\n(E) Endre gren"
			<< "\n(A) Display alle grener"
			<< "\n(S) Display en gren"
			<< "\n(Q) Tilbake til hovedmeny\n";
		valgGrener = les();		//les brukervalg

		switch (valgGrener) //kjør brukervalg
		{
		case 'N':	nyGren();			break;	// G N
		case 'E':	endreGren();		break;	// G E
		case 'A':	skrivAllGrener();	break;	// G A
		case 'S':	skrivEnGren();		break;	// G S
		default:						break;
		}

	} while (valgGrener != 'Q');

}
	//Registrer ny gren
void Grener::nyGren()	//til komando G E
{
	char buffer[NVLEN];
	Gren *temp;
															//les inn navn på ny gren
	les("Skriv unikt navn: ", buffer, NVLEN);

	if (!listGren->inList(buffer))							//hvis navnet ikke er i bruk
	{												//lag ny gren og legg det til i listen
		temp = new Gren(buffer);
		listGren->add(temp);
		skriv("Ny gren registrert med navn: ", buffer);

		skrivTilFIl();
	}
	else	//feilmelding
	{	skriv(buffer, "er alerede i bruk"); 	}


}
//endre navnet paa en eksisterende gren
void Grener::endreGren()	//til komando G E
{
	char buffer[NVLEN];
	Gren *temp;
	//les navn
	les("Skriv unikt navn: ", buffer, NVLEN);


	if (listGren->inList(buffer))									//hvis navnet  er i bruk
	{									//hent objekten, endre navn og legg tilbake i liste
		temp = (Gren*)listGren->remove(buffer);
		do
		{
			temp->endreNavn();
		} while (listGren->inList(buffer)); //luper til brukeren taster inn et unikt navn
		listGren->add(temp);

		skrivTilFIl();
	}
	else   //feilmelding
	{	skriv("Finner ikke navnet: ", buffer);	}
}

void Grener::skrivAllGrener() //til komando G A
{
	Gren *temp;

	if (!listGren->isEmpty())									// hvis listen ikke er tom
	{													//ga gjennom alle Grenobj i listen

		for (int i = 1; i <= listGren->noOfElements(); i++)
		{
										//ta obj ut av liste, skriv data og legg obj i liste
			temp = (Gren*)listGren->removeNo(i);
			temp->display();
			listGren->add(temp);
		}
	}
}

void Grener::skrivEnGren()//til komando G S
{
	char buffer[NVLEN];
	Gren *temp;
	//les et navn fra bruker
	les("Skriv navnet på genen: ", buffer, NVLEN);

	if ( listGren->inList(buffer))									// hvis navnet finnes
	{									//ta obj ut av liste, skriv data og legg obj i liste
		temp = (Gren*)listGren->remove(buffer);
		temp->display();									//skriv grendata
		if (sisteOvelse > 0 )								//hvis noen ovelser er registrer
		{	temp->skrivOvelse();	}	//skriv data om alle ovelsene
		else
		{	skriv("Ingen ovelse er registrert paa gren: ", buffer);		}
		listGren->add(temp);												 //legg obj i list
	}
	else																		 //feilmelding
	{	skriv("finner ikke gren med navn: ", buffer);	}
}
//skriv til fil
void Grener::skrivTilFIl()
{
	ofstream ut("GRENER.DTA");
	Gren *ptr;

	//skriv egne datamedlemmer til fil
	cout << sisteOvelse;
	int antalIListe = listGren->noOfElements();
	skriv(ut, antalIListe);
	skriv(ut, sisteOvelse);
	//skriv alle grenobj til fil
	for (int i = 1; i <= listGren->noOfElements(); i++)
	{
		ptr = (Gren*)listGren->removeNo(i);
		ptr->skrivTilFIl(ut, sisteOvelse);
		listGren->add(ptr);	}
}
	//les fra fil
void Grener::lesFraFil()
{
	ifstream inn("GRENER.DTA");
	int antallIListe;
	char navn[NVLEN];
	Gren *ptr;

	if (inn)//hvis filen finnes
	{		//les in egne datamedlemmer fra fil
		antallIListe = lesInt(inn);
		sisteOvelse = lesInt(inn);



		if (!listGren->isEmpty()) //hvis listen ikke er tom
		{ //slett listn og lag ny
			delete listGren;
			listGren = new List(Sorted);
		}

		//les in alle Grenobj fra fil
		for (int i = 1; i <= antallIListe; i++)
		{											//lag nytt obj og legg det i listen
			lesTxt2(inn, navn);
			ptr = new Gren(inn, navn, sisteOvelse);
			listGren->add(ptr);
		}
	}
	else  //feilmelding
	{	skriv("\nFinner ikke fil GRENER.DTA\n", "");	}



}

void Grener :: ovelseMeny() {                       // Meny til Ovelse : O...


}

void Grener :: skrivUtNavn() {                      // Skriver ut navnene på Gren : Meny i O.
  Gren *gren;
  int newLineTeller = 1;

  if (listGren) {                                   // Hvis listen finnes og det er elementer i den.
    cout << "\nFor hvilke gren vil du registrere en ovelse?";

                                                    // Looper gjennom alle elementer.
    for (int i = 1; i <= listGren->noOfElements(); i++) {

      gren = (Gren*) listGren->removeNo(i);         // Fjerner objekt fra liste.
      gren->skrivGrenNavn();                        // Skriver ut text (navnet).
      listGren->add(gren);                          // Legger tilbake i listen.

      if (newLineTeller % 6 == 0)                   // Skriver ut "new line" hvis 6 grener
        cout << '\n';                               // ligger etter hverandre på skjermen.
      newLineTeller++;                              // Teller opp med en.
    }
  }
  else                                              // Hvis ingen ligger i listen.
    cout << "\n\tIngen grener er registrert";
}
