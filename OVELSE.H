//OVELSE.H alex
#if !defined(__OVELSE_H)
#define  __OVELSE_H

#include"ListTool2B.h"
#include"FUNKSJONER.H"
#include"CONST.H"
#include"ENUM.H"


class Ovelse 
{
private:
	static int navnTeller;		//brukes til datamedlemm  int "nr"

	int nr;
	registerTidPoeng maaling;		//hvilken type maaling skal registrers
	char *navn;											//ovelsens navn
	int antDeltagere;	//brukes som teller
	int dato;
	int klokkeslett;
					//deltager array	
	int *deltagerListe;
					//resultat array ( MinSECTidel;	MinSecHundredel; MinSekTusendel; PoengX; PoengXX;)
	int *resultatListe;
	int log[ANTALLVINNERE + 1];  //loggfører seiersrekkefolgen brukes til R <id> S NB!
public:
	Ovelse( registerTidPoeng typeMaaling, char * nv);	//constructor    får et arg. fra Grener som viser hva slags maaling som skal registreres
	~Ovelse();
	void skrivMeny();
	void skrivData();
	char *filNavn(int type = 0);// genererer et unik filnavn basert på ovelsens unike "nr" og send med 1 for .RES eller ingenting for .STA
	void skrivTilFil(ofstream & ut);
	void lesFraFil(ifstream & inn);
	void nyResultatListe();																	//lag en ny resultatliste
	int lagUniktNr();										//lager et unikt tall som brukes til datamedlemm  int "nr"
	int skaffVerdi();										  //henter inn og sikkrer riktig verdi til resultatlisten
	void bubbleSort();							//sorterer 2 int array
	void ajourforeLog();//ma testes		ajourforer log arrayen og sender rapport til medaljer og poeng.  ma teste global funksjon raport
	void skrivResultatliste();
	void deltagerSkrivtilFil();	//ma lages	
	void resultaterSkrivTilFil();//ma lages	
	void resultaterLesFraFil(); //ma lages
	int sjekkID();
};

/*
liste over ting som må gjores i ovelse
lag alle 3 menyene. start med aa lagen en meny til i Grener. lag saa 2 menyer i Ovelse
lag en funksjon som lager et unikt filnavn (til OVxxx.STA og OVxxxx.RES)						
lag en funksjon som sletter en fil fra HDD( til O F  ,  O L <id> F  og  O R <id> F)				

Forslag til implimentasjnsrekkefolge etter at det ovenfor er gjort:
1. valg :O     N  ->  A  ->  E  -> skriv til fil  -> les fra fil  ->  F
2. Valg :O L   N  ->  S  ->  E  -> skriv til fil  -> les fra fil  ->  F							
3. Valg :O S   N  ->  S(før NB!)  -> skriv til fil  -> les fra fil ->  F  ->  S(NB!)			

//tror vansklighetsgraden fra lettest til vanskligst er: 2, 1, 3

når 1, er gjort så kan også valg: G S gjøres etterpå, samt å fullføre skriv til og les fra fil i Gren
*/

#endif
