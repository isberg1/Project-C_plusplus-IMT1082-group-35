
#if !defined(__GRENER_H)
#define  __GRENER_H

#include"ListTool2B.h"


class Grener {
private:
	List *listGren;
	int sisteOvelse;
		
public:
	Grener();//constructor

	~Grener();//destructor
	//Ande funksjoner
	void skrivMeny();
	void nyGren();
	void endreGren();
	void skrivAllGrener();
	void skrivEnGren();
	void skrivTilFIl();
};


#endif
