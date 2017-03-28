#if !defined(__GREN_H)
//GREN.H alex
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
	Ovelse *array[MAXOVELSER + 1];
	char *annet;
	int antallRegistrerteOvelser;
public:
	//constructor
	Gren();
	Gren(char* a);
	Gren(ifstream & inn, char* a);
	//destructor
	~Gren();
	void endreNavn();		// G E
	void display();				// G A	
	void skrivOvelse();				// G S
	void skrivTilFIl(ofstream & ut);
	int hentAntalOvelser();
	
};

  

#endif
