#if !defined(__NASJONER_H)
#define  __NASJONER_H


#include "NASJON.H"

class Nasjoner {
  private:
    Nasjon *nasjon;                                 // Peker til nasjon-objekt.

  public:
    ~Nasjoner();                                    // Deconstructor.
    void skrivMeny();                               // Skriver ut meny for Nasjoner.
    void menyValg();                                // Valg av funksjoner.
    void registrerNyNasjon();                       // Registrerer ny nasjon.
};



#endif
