#if !defined(__DELTAGER_H)
#define  __DELTAGER_H

#include <fstream>
#include "ListTool2B.h"
#include "CONST.H"

class Deltager : public NumElement
{
private:
	char* fullNavn;
	char nasjon[NASJONLEN], data[STRLEN];

public:
	Deltager();
	Deltager(int in);
//	~Deltager();
	void endreInfo();
	void display();
	void displayHoved();
};

#endif

