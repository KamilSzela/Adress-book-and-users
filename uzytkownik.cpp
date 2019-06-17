#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include <sstream>
#include "uzytkownik.h"

using namespace std;
int Uzytkownik::konwersjaStringNaInt(string wyraz) {
    int i;
    istringstream iss(wyraz);
    iss >> i;
    return i;
}
void Uzytkownik::wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy)
{
    fstream plik;
    string odczytywanaLinia;
    Uzytkownik nowyUzytkownik;
    plik.open("uzytkownicy.txt",ios::in);
    while(plik.good()==true) {
        while(plik.eof()==false) {
            getline(plik,odczytywanaLinia,'|');
            if(odczytywanaLinia=="\n"||odczytywanaLinia=="") {
                break;
            }
            nowyUzytkownik.id=konwersjaStringNaInt(odczytywanaLinia);
            getline(plik,odczytywanaLinia,'|');
            nowyUzytkownik.nazwa=odczytywanaLinia;
            getline(plik,odczytywanaLinia,'|');
            nowyUzytkownik.haslo=odczytywanaLinia;
            uzytkownicy.push_back(nowyUzytkownik);
        }
    }
    plik.close();
}
void Uzytkownik::rejestracja(vector <Uzytkownik> &uzytkownicy)
{
     Uzytkownik nowyUzytkownik;
    cout<<"podaj swoj login: ";
    cin>>nowyUzytkownik.nazwa;
    vector <Uzytkownik>:: iterator i=uzytkownicy.begin();
    while(i != uzytkownicy.end()) {
        if (nowyUzytkownik.nazwa == i->nazwa) {
            cout<<"Podana nazwa uzytkownika jest juz uzywana, prosze podac inna nazwe uzytkownika: ";
            cin>>nowyUzytkownik.nazwa;
            i=uzytkownicy.begin();
        } else {
            i++;
        }
    }
    cout<<"Prosze podac haslo: ";
    cin>>nowyUzytkownik.haslo;
    if (uzytkownicy.size()>0) {
        int idPoprzedniegoUzytkownika=uzytkownicy.back().id;
        nowyUzytkownik.id=idPoprzedniegoUzytkownika+1;
    } else
        nowyUzytkownik.id=1;
    uzytkownicy.push_back(nowyUzytkownik);
    fstream plikt;
    plikt.open("uzytkownicy.txt",ios::out);
    for(vector<Uzytkownik>::iterator i=uzytkownicy.begin(); i<uzytkownicy.end(); i++) {
        plikt<<i->id<<'|';
        plikt<<i->nazwa<<'|';
        plikt<<i->haslo<<'|';
        plikt<<endl;
    }
    plikt.close();
    cout<<endl<<"konto zalozone!";
    Sleep(1000);
}
int Uzytkownik::logowanie(vector <Uzytkownik> &uzytkownicy)
{
      string login,haslo;
    cout<<"podaj swoj login: ";
    cin>>login;
    vector<Uzytkownik>::iterator i=uzytkownicy.begin();
    while(i!=uzytkownicy.end()) {
        if (login == i->nazwa) {
            for(int proby=0; proby<3; proby++) {
                cout<<"prosze podac haslo, zostalo Ci "<<3-proby<<" prob: ";
                cin>>haslo;
                if(i->haslo == haslo) {
                    cout<<"logowanie poprawne! ";
                    Sleep(1000);
                    return i->id;
                }
            }
            cout<<"podales 3 razy bledne haslo, program za 3 sekundy przejdzie do menu glownego";
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout<<"Nie znalezniono uzytkownika z podanym loginem";
    Sleep(1000);
    return 0;
}
void Uzytkownik::zmianaHasla(vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
      string haslo;
    cout<<"Prosze podac nowe haslo: ";
    cin>>haslo;
    for(vector<Uzytkownik>::iterator i=uzytkownicy.begin(); i!=uzytkownicy.end(); i++) {
        if(i->id == idZalogowanegoUzytkownika) {
            i->haslo=haslo;
            cout<<"zmieniono haslo! ";
            Sleep(1000);
        }
    }
    fstream plik;
    plik.open("uzytkownicy.txt", ios::out);
    for(vector<Uzytkownik>::iterator i=uzytkownicy.begin(); i!=uzytkownicy.end(); i++) {
        plik<<i->id<<'|';
        plik<<i->nazwa<<'|';
        plik<<i->haslo<<'|'<<endl;
    }
    plik.close();
}
