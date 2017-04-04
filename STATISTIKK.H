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
	void sorter1(int array[]);								//sorterer  nasjonsForkort array og en medsendt int array
	void omsorter(int teller, int array[]);					//omsorterer  nasjonsForkort array og en medsendt int array
};
//ny nasjon kommer fra poeng eller medalje 
//all validering av riktig nasjon skjer i OvelseObj. 


#endif
