//GRENER.H alex
#if !defined(__GRENER_H)
#define  __GRENER_H

#include"ListTool2B.h"
#include"GREN.H"

//Containerklasse
class Grener {
private:
	List *listGren;			//liste med Gren Objekter

public:
	Grener();//constructor
	~Grener();//destructor
	//Ande funksjoner
	void skrivMeny();								//meny
	void nyGren();				                    // G N
	void endreGren();			                    // G E
	void skrivAllGrener();		                    // G A
	void skrivEnGren();			                    // G S
	void skrivTilFIl();								//skriv til fil
	void lesFraFil();								//les fra fil
	void ovelseGrenMeny();                          // Velger navn paa gren og kaller meny for ovelse.
	void addTilLIst(Gren *ptr);						//lar et Grenobjekt utenfor listen legge seg selv i listen
	void fjernFraList(char navn[]);					//lar et Grenobjekt i listen fjerne seg selv fra listen
	void skrivUtRegistrerteGrener();                // Skriver ut alle registrerte gren-objekter.

};


#endif
