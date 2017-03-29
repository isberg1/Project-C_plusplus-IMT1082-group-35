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
	void menyValgOvelse();			// Switch for Ovelse.				   Valg : O
	void skrivOvelseMeny();			// KommandoMeny for Ovelse.			  
	void nyOvelse();				// Lager ny Ovelse.					   Valg : O N
	void endreOvelse();				// Endrer en Ovelse.				   Valg : O E
	void fjernOvelse();				// Fjerner en Ovelse.				   Valg : O	F
	void skrivAlleOvelse();			// Skriver hoveddata for alle Ovelser. Valg : O	A
	void menyValgDelListe();		// Switch for deltagerLister.		   Valg : O L
	void skrivDelListeMeny();		// KomandoMeny for deltagerListe.
	void skrivDelListe();			// Skriver ut en deltagerListe.		   Valg : O L S
	void nyDelListe();				// Lager ny deltagerListe.			   Valg : O L N
	void endreDelListe();			// Endrer en deltagerListe.			   Valg : O L E
	void fjernDelListe();			// Fjerner en deltagerListe.		   Valg : O L F
	void menyValgResListe();		// Switch for resultatLister.		   Valg : O R
	void skrivResListeMeny();		// KommandoMeny for resultatListe.
	void skrivResListe();			// Skriver ut en resultatListe.		   Valg : O R S
	void nyResListe();				// Lager en ny resultatListe.		   Valg : O R N
	void fjernResListe();			// Fjerner en resultatListe.		   Valg : O R F
};


#endif
