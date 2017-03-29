//GRENER.H alex
#if !defined(__GRENER_H)
#define  __GRENER_H

#include"ListTool2B.h"

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
	void testResListe();
	void testResSkriv();
	void ovelseMeny();          // Meny til Ovelse : O...
	void skrivUtNavn();         // Skriver ut navnene på Gren : Meny i O...



};


#endif
