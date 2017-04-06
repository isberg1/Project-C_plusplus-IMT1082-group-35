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
    void endreNasjonMeny();                         // Menyvalg av hva som skal endres hos en nasjon.
    void registrerNyNasjon();                       // Registrerer ny nasjon                 : Valg N N
    void endreNasjon();                             // Endre data for en nasjon              : Valg N E
    void skrivHoveddata();                          // Skriver ut hoveddataene for nasjoner  : Valg N A
    void skrivDeltagerTropp();                      // Skriver ut data om deltagere i tropp  : Valg N T
    void skrivAllData();                            // Skriver alle data om en gitt nasjon   : Valg N S
    bool finnesNasjon(char *sjekkNasjon);           // Hvis Nasjon finnes                    : Valg D N
    void oppdaterNasjon(char *oppdNasjon);          // Plusser på antDeltagere med 1         : Valg D N
    void skrivTilFil();                             // Skriver til fil.
    void lesFraFil();                               // Leser datastruktur fra fil.
    void skrivUtForkortelse();                      // Skriver ut nasjonens forkortelse.(Hjelpefunksjon)
	void reduserAntDeltagere(char *fultNasjonsNavn);	//reduserer antall deltagere med 1
	void okAntalletDeltagere(char *nasjonsForkortelse);	//oker antall deltagere med 1
};



#endif
