#if !defined(__MEDALJER_H)
#define  __MEDALJER_H

#include"ENUM.H"
#include"CONST.H"
#include"STATISTIKK.H"

class Medaljer : public Statisikk
{
private:
	
	seiersType medaljeType;
	int medaljer[MAXNASJONER + 1];
public:
	Medaljer();
	~Medaljer();
	void nyMedalje(char nasjon[], seiersType, int antall);
	void sorter(); //ikke laget enda
	void omsorter(int teller);	//utestet
};


#endif
