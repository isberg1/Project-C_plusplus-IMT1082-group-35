#if !defined(  __NASJON_H)
#define  __NASJON_H


#include "ListTool2B.h"                             // Verktøykasse med lister.
#include <fstream>

using namespace std;



class Nasjon : public TextElement {                 // Arver lister.
  private:                                          // Nasjonsforkortelse = text fra TextElement.
    char *fulltNavn;                                // Full navn på nasjon.
    char *kontaktNavn;                              // Navn til kontaktperson
    char *andreData;                                // Andre relevante data.
    int antDeltagere;                               // Antall deltagere i nasjonens tropp.
    int kontaktTlf;                                 // Tlf til kontaktperson.
    List *nasjonsListe;                             // Peker til liste.

  public:
    Nasjon();                                       // Constructor.
    Nasjon(char *nasjonKort);                       // Constructor med parameter.
    Nasjon(ifstream & innfil, char *nasjonKort);    // Constructor som leser data fra fil.
    ~Nasjon();                                      // Deconstructor.
    virtual void display();                         // Display-funksjon.
    void skrivTilFil(ofstream & utfil);             // Skriver til fil.
};



#endif
