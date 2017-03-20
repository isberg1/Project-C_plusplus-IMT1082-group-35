#if !defined(__OVELSE_H)
#define  __OVELSE_H

#include"ListTool2B.h"

class Ovelse : public NumElement
{
private:
	// nr lagres i NumElement
	char *navn;
	int antDeltagere;
	int dato;
	int klokkeslett;
	//deltager array
	//resultat array
public:
	void skrivMeny();
};



#endif
