#if !defined(__STATISTIKK_H)
#define  __STATISTIKK_H

#include"CONST.H"
#include"FUNKSJONER.H"


class Statisikk
{
protected:
	int sistebrukt;											//teller
	char nasjonsForkort[MAXNASJONER + 1][NASJONLEN +1];		//array med nasjonsforkortelser
public:
	//constructor
	Statisikk();											//nullstiller array			
	void sorter1(int array[]);								//fungerer ikke enda
	void omsorter(int teller, int array[]);					//fungerer ikke enda
};
//ny nasjon kommer fra poeng eller medalje 
//all validering av riktig nasjon skjer i OvelseObj. 


#endif
