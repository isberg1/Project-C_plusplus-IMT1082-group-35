#if !defined(  __NASJON_H)
#define  __NASJON_H


#include "ListTool2B.h"                             // Verktøykasse med lister.
#include <fstream>                                  // ifstream, ofstream.

using namespace std;



class Nasjon : public TextElement {                 // Arver lister.
  private:                                          // Nasjonsforkortelse = text fra TextElement.
    char *fulltNavn;                                // Full navn på nasjon.
    char *kontaktNavn;                              // Navn til kontaktperson
    char *andreData;                                // Andre relevante data.
    int antDeltagere;                               // Antall deltagere i nasjonens tropp.
    int kontaktTlf;                                 // Tlf til kontaktperson.

  public:
    Nasjon();                                       // Constructor.
    Nasjon(char *nasjonKort);                       // Constructor med parameter.
    Nasjon(ifstream & inn, char *nasjonKort);       // Constructor som leser data fra fil.
    ~Nasjon();                                      // Deconstructor.
    virtual void display();                         // Display-funksjon.
    void skrivTilFil(ofstream & ut);                // Skriver til fil.
    void endreNasjonsNavn();                        // Endrer det fulle navnet til nasjonen.
    void endreKontaktperson();                      // Endrer navnet til kontaktperson.
    void endreTlf();                                // Endrer TLF til kontaktperson.
    void endreAnnet();                              // Endrer feltet 'Annet'.
    void skrivHoveddata();                          // Skriver ut hoveddata.
    void skrivForkortelse();                        // Skriver text.
    void oppdaterAntDeltagere();                    // Oppdaterer antall deltagere med 1.
    bool harDeltagere();                            // 'True' hvis nasjonen har 1 eller flere deltagere.
};



#endif
