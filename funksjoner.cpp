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
int les(char* t, int min, int max)  {               // returnerer et tall mellom min og max:
  int tall;
  do  {
    cout << '\t' << t << " (" << min << '-' << max <<  "):  ";
    cin >> tall;  cin.ignore();
  } while (tall < min  ||  tall > max);
  return tall;
}
