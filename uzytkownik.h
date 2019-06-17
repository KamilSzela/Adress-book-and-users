#include <iostream>
#include <vector>
using namespace std;

class Uzytkownik
{
    int id;
    string nazwa, haslo;
public:
    int konwersjaStringNaInt(string wyraz);
    void wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy);
    void rejestracja(vector <Uzytkownik> &uzytkownicy);
    int logowanie(vector <Uzytkownik> &uzytkownicy);
    void zmianaHasla(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika);

};
