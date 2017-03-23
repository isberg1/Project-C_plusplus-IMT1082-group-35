#if !defined(__STATISTIKK_H)
#define  __STATISTIKK_H

#include"CONST.H"
#include"FUNKSJONER.H"
class Statisikk
{
protected:
	int sistebrukt;
	char nasjonsForkort[MAXNASJONER + 1][NASJONLEN +1];
public:
	Statisikk();
	void skrivNasjon(int nr);
};
//ny nasjon kommer fra poeng eller medalje 
//all validering av riktig nasjon skjer i Ovelseobj. 


#endif
