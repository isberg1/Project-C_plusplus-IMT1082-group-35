#if !defined(__GREN_H)
#define  __GREN_H

#include"OVELSE.H"
#include"CONST.H"
#include"ENUM.H"

class Gren :public TextElement {
private:
	//navn lagres i TextElement
	registerTidPoeng typeMaaling;
	int antOvelser;
	int antSifre;
	Ovelse array[MAXOVELSER + 1];
	char *annet;
public:
	Gren();
	Gren(char* a);
	~Gren();
	void endreNavn(char *navn);
	void skrivData();
	void skrivOvelse();
	void skrivTilFIl(ofstream & ut);
};



#endif
