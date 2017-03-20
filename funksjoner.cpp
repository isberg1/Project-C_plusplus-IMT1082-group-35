/*
    funksjoner.cpp
    Globale funksjoner
*/
////////////////////////////////////////////////////:://///////////////////////////////

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <cstring>

using namespace std;



char les() {                                        // Leser og returnerer ETT upcaset tegn.
  char ch;
  cout << "\n\nKommando:  ";
  cin >> ch;  cin.ignore();
  return (toupper(ch));
}
                                                    // Skriver ledetekst (t), leser og
                                                    // returnerer et tall mellom min og max:
int les(const char t[], const int min, const int max) {
	int i;
	char buffer[256];
	do {                                            // Skriver ledetekst:
		cout << '\t' << t << " (" << min << '-' << max << "): ";
		fgets(buffer, 256, stdin);
		i = atoi(buffer);
	} while (i < min || i > max);                   // Sjekker at i lovlig intervall.
	return i;                                       // Returnerer innlest tall.
}


char *konverter(char t[]) {                         // Konverterer og returnerer char [] til char*
	char *string;
                                                    // Konverterer char array til char *
	string = new char[strlen(t) + 1];
	strcpy(string, t);
	return string;
}
