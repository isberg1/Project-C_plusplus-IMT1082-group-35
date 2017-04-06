#if !defined(__FUNKSJONER_H)
#define  __FUNKSJONER_H


#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;


/// Les
char les();											// Leser en char.
char les(char menyPlass[]);                         // Leser en char og skriver ut plassering i meny.
void les(const char t[], char s[], const int LEN);	// Leser text string.
int  les(const char t[], const int min, const int max);// Leser en int med ledetext.
int lesInt(ifstream& inn);			                // Leser en int fra fil i et standardforman.
char *lesTxt(ifstream& inn);                        // Leser en string fra fil i et standardforman returnerer peker.
void lesTxt2(ifstream& inn, char string[]);			// Leser inn en char[] fra fil.

/// Skriv
void skriv(const char* text, const char* string);   // Display string med ledetext.
void skriv(const char* text, const int dataMedlem); // Display int med ledetext.
void skriv(ofstream& ut, int tall);	                // Skriver en int til fil i et standardforman.
void skriv(ofstream& ut, char *string);			    // Skriver en string til fil.

/// Diverse
void fjernBlankeForanOgBak(char txt[]);				// Fjerner blanke foran og bak i en text.
char *konverter(char t[]);					        // Konverter char [] til char *.
void MainMeny();									// Menyen i int main().
char *nasjonsForkortelse(char t[]);                 // Sjekker at chars=3, gjør dem store. Med ledetext.
bool erBokstaver(char tekst[]);                     // Sjekker om alle indekser i array er bokstav.
char *konverterTilStore(char *tekst);               // Gjør om til store bokstaver.
bool slettFil(char fil[]);                          // Sletter fil fra disk, send med filnavn.
void StatistikkRaport(int deltager, int log, int teller);         // Reduser poeng og medaljefordelingen til en nasjon.
void HentNavnOgNasjonFraDeltager(char nv[], char nasj[], int nr); // Henter en deltagers navn og nasjon.
bool sjekkDeltagerId(int deltagerNv);				// Sjekker om et nummer er likt nummeret til en deltager.
void tr(int t=0);									// Til testing.	skriver ut test text og eventuelt en int.


#endif
