//GRENER.H alex
#if !defined(__GRENER_H)
#define  __GRENER_H

#include"ListTool2B.h"
#include"GREN.H"

//Containerklasse
class Grener {
private:
	List *listGren;

public:
	Grener();//constructor
	~Grener();//destructor
	//Ande funksjoner
	void skrivMeny();
	void nyGren();				                    // G N
	void endreGren();			                    // G E
	void skrivAllGrener();		                    // G A
	void skrivEnGren();			                    // G S
	void skrivTilFIl();
	void lesFraFil();
	void ovelseGrenMeny();                          // Velger navn paa gren og kaller meny for ovelse.
	void addTilLIst(Gren *ptr);
	void fjernFraList(char navn[]);
	void skrivUtRegistrerteGrener();                // Skriver ut alle registrerte gren-objekter.

};


#endif
