#if !defined(__GREN_H)
#define  __GREN_H



#include"OVELSE.H"
#include"CONST.H"
#include"ENUM.H"

class Grener :public TextElement {
private:
	//navn lagres i TextElement
	enum registerTidPoeng;
	int antOvelser;
	int antSifre;
	Ovelse array[MAXOVELSER + 1];
public:
	void skrivMeny();
};



#endif
