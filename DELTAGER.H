#if !defined(__DELTAGER_H)
#define  __DELTAGER_H

#include <fstream>
#include "ListTool2B.h"
#include "CONST.H"
#include "ENUM.H"

using namespace std;



class Deltager : public NumElement                  // Arver lister.
{
private:                                            // Deltager ID = number fra NumElement.
	char *fullNavn;
	char *nasjon;
	char *data;
	kjonn deltagerKjonn;

public:
	Deltager();                                     // Constructor.
	Deltager(char *nyNasjon, int ID);               // Constructor med parametre.
	Deltager(ifstream & inn, int ID);               // Constructor som leser data fra fil.
    ~Deltager();                                    // Deconstructor.
	virtual void display();                         // ?
    void skrivTilFil(ofstream & ut);                // Skriver til fil.
	void skrivDeltagerTropp(char *n);               // Skriver ut alle deltagere for gitt nasjon.
    void endreInfo();                               // ?
    void displayHoved();                            // ?
};

#endif

