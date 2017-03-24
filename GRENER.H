//GRENER.H alex
#if !defined(__GRENER_H)
#define  __GRENER_H

#include"ListTool2B.h"

//Containerklasse
class Grener {
private:
	List *listGren;
	int sisteOvelse;
		
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
};


#endif
