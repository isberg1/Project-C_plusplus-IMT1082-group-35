
#if !defined(__FUNKSJONER_H)
#define  __FUNKSJONER_H


#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

char les();											//leser en char
char les(char menyPlass[]);                          // Leser en char og skriver ut plassering i meny.
void les(const char t[], char s[], const int LEN);	//leser text string
int  les(const char t[], const int min, const int max);//leser en int med ledetext
int lesInt(ifstream& inn);			                //leser en int fra fil i et standardforman
char *lesTxt(ifstream& inn);                        //leser en string fra fil i et standardforman returnerer peker
void lesTxt2(ifstream& inn, char string[]);			//leser inn en char[] fra fil
void skriv(const char* text, const char* string);   //display string med ledetext
void skriv(const char* text, const int dataMedlem); //display int med ledetext
void skriv(ofstream& ut, int tall);	                //skriver en int til fil i et standardforman
void skriv(ofstream& ut, char *string);			    //skriver en string til fil

void skrivTilFil();				                    //styrer andre filfunksjoner.	  til komando (U)
void lesFraFil(int alternativ = 0);                 //funksjonen kan gjør noe extra.  til komando (I)

char *konverter(char t[]);					        //konverter char [] til char *

void MainMeny();

char *nasjonsForkortelse(char t[]);                 // Sjekker at chars=3, gjør dem store. Med ledetext.
bool erBokstaver(char tekst[]);                     // Sjekker om alle indekser i array er bokstav.
bool erBokstaverEllerSpace(char tekst[]);           // Sjekker om indekser i array er bokstaver/ space.
char *konverterTilStore(char *tekst);               // Gjør om til store bokstaver.
bool slettFil(char fil[]);                          // Sletter fil fra disk, send med filnavn.

void bubbleSort(int array[]);							//sorterer 1 int array

#endif

