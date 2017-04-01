//GRENER.H alex
#if !defined(__GRENER_H)
#define  __GRENER_H

#include"ListTool2B.h"
#include"GREN.H"

//Containerklasse
class Grener {
private:
	List *listGren;
//	int sisteOvelse;

public:
	Grener();//constructor
	~Grener();//destructor
	//Ande funksjoner
	void skrivMeny();
	void nyGren();				// G N
	void endreGren();			// G E
	void skrivAllGrener();		// G A
	void skrivEnGren();			// G S
	void skrivTilFIl();
	void lesFraFil();
	void ovelseGrenMeny();          // Meny til Ovelse : O...

	void testResListe();
	void testResSkriv();
	void skrivUtNavn();             // Skriver ut navnene på Gren.
	void addTilLIst(Gren *ptr);
	void fjernFraList(char navn[]);
	void finnGrenOvelse();
};


#endif
