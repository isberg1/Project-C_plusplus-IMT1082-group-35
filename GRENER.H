//GRENER.H alex
#if !defined(__GRENER_H)
#define  __GRENER_H

#include"ListTool2B.h"
#include"GREN.H"

//Containerklasse
class Grener {
private:
	List *listGren;			                        // Liste med Gren Objekter.

public:
	Grener();                                       // Constructor.
	~Grener();                                      // Destructor.
	void skrivMeny();								// Meny
	void nyGren();				                    // G N
	void endreGren();			                    // G E
	void skrivAllGrener();		                    // G A
	void skrivEnGren();			                    // G S
	void skrivTilFIl();								// Skriv til fil.
	void lesFraFil();								// Les fra fil.
	void ovelseGrenMeny();                          // Velger navn paa gren og kaller meny for ovelse.
	void addTilLIst(Gren *ptr);						// Lar et Grenobjekt utenfor listen legge seg selv i listen.
	void fjernFraList(char navn[]);					// Lar et Grenobjekt i listen fjerne seg selv fra listen.
	void skrivUtRegistrerteGrener();                // Skriver ut alle registrerte gren-objekter.
};


#endif
