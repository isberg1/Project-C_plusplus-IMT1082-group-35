#if !defined(__NASJONER_H)
#define  __NASJONER_H


#include "NASJON.H"                                 // Klassen Nasjon.



class Nasjoner {
  private:
    List *nasjonsListe;                             // Peker til liste.

  public:
    ~Nasjoner();                                    // Deconstructor.
    void skrivMeny();                               // Skriver ut meny for Nasjoner.
    void menyValg();                                // Valg av funksjoner.
    void registrerNyNasjon();                       // Registrerer ny nasjon : Valg N N
    void endreNasjon();                             // Endre data for en nasjon : Valg N E
    void skrivHoveddata();                          // Skriver ut hoveddataene for nasjoner : Valg N A
    void skrivDeltagerTropp();                      // Skriver ut data om deltagere i tropp : Valg N T
    void skrivAllData();                            // Skriver alle data om en gitt nasjon : Valg N S
    bool finnesNasjon();                            // Sjekker om nasjonen finnes : Valg D X
};



#endif
