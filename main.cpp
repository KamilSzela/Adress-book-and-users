#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Uzytkownik {
    int id;
    string nazwa, haslo;
};
int konwersjaStringNaInt(string wyraz) {
    int i;
    istringstream iss(wyraz);
    iss >> i;
    return i;
}
void zapiszUzytkownikowWPlikuTekstowym(vector <Uzytkownik> &uzytkownicy)
{
         fstream plikt;
        plikt.open("uzytkownicy.txt",ios::out);
        for(vector<Uzytkownik>::iterator i=uzytkownicy.begin(); i<uzytkownicy.end(); i++) {
            plikt<<i->id<<'|';
            plikt<<i->nazwa<<'|';
            plikt<<i->haslo<<'|';
            plikt<<endl;
        }
        plikt.close();
}
void wczytajUzytkownikowZPliku(vector <Uzytkownik> &uzytkownicy) {
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
void rejestracja(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik nowyUzytkownik;
    cout<<"podaj swoj login: ";
    cin>>nowyUzytkownik.nazwa;
    vector <Uzytkownik>:: iterator i=uzytkownicy.begin();
    while(i != uzytkownicy.end())
    {
        if (nowyUzytkownik.nazwa == i->nazwa)
        {
            cout<<"Podana nazwa uzytkownika jest juz uzywana, prosze podac inna nazwe uzytkownika: ";
            cin>>nowyUzytkownik.nazwa;
            i=uzytkownicy.begin();
        }
        else
        {
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
    zapiszUzytkownikowWPlikuTekstowym(uzytkownicy);
    cout<<endl<<"konto zalozone!";
    Sleep(1000);
}
int logowanie(vector<Uzytkownik> &uzytkownicy)
{
    string login,haslo;
    cout<<"podaj swoj login: ";
    cin>>login;
    vector<Uzytkownik>::iterator i=uzytkownicy.begin();
    while(i!=uzytkownicy.end())
    {
        if (login == i->nazwa)
        {
            for(int proby=0; proby<3; proby++)
            {
                cout<<"prosze podac haslo, zostalo Ci "<<3-proby<<" prob: ";
                cin>>haslo;
                if(i->haslo == haslo)
                {
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
int main() {
    vector <Uzytkownik> uzytkownicy;
    wczytajUzytkownikowZPliku(uzytkownicy);
    int idZalogowanegoUzytkownika=0;
    char wybor;
    for (vector<Uzytkownik>:: iterator i=uzytkownicy.begin(); i!=uzytkownicy.end(); i++) {
        cout<<i->id<<endl;
        cout<<i->nazwa<<endl;
        cout<<i->haslo<<endl;
    }
   system("pause");
    while(1) {
        if(idZalogowanegoUzytkownika==0) {
            system("cls");
            cout<<"MENU GLOWNE"<<endl;
            cout<<"--------------"<<endl;
            cout<<"1. Rejestracja"<<endl;
            cout<<"2. Logowanie"<<endl;
            cout<<"9. wyjscie z programu"<<endl;
            cin>>wybor;
            switch(wybor) {
            case '1': {
                rejestracja(uzytkownicy);
                break;
            }
            case '2': {
                idZalogowanegoUzytkownika=logowanie(uzytkownicy);
                break;
            }
            case '9':
                exit(0);
            default:
                cout<<"niepoprawna opcja sprobuj jeszcze raz";
            }
            }
            else {
                system("cls");
        cout<<"MENU Ksiazka adresowa"<<endl;
        cout<<"-----------"<<endl;
        cout<<"1.Dodaj nowego przyjaciela"<<endl;
        cout<<"2.Wyswietl wszystkich przyjaciol o podanym imieniu"<<endl;
        cout<<"3.Wyswietl wszystkich przyjaciol o podanym nazwisku"<<endl;
        cout<<"4.Wyswietl wszystkich przyjaciol"<<endl;
        cout<<"5.Usun z listy przyjaciol"<<endl;
        cout<<"6.Edytuj dane wybranego przyjaciela"<<endl;
        cout<<"9.Wyjscie z programu"<<endl;
                  cin>>wybor;

        switch(wybor) {
        case '1': {
            system("cls");
            //dodajPrzyjacielaDoListy(przyjaciele);
            break;
        }
        case '2': {
            system("cls");
            //wyszukajPrzyjaciolOPodanymImieniu(przyjaciele);
            break;
        }
        case '3': {
            system("cls");
            //wyszukajPrzyjaciolOPodanymNazwisku(przyjaciele);
            break;
        }
        case '4': {
            system("cls");
            //wyswietlWszystkichPrzyjaciol(przyjaciele);
            break;
        }
        case '5':
            system("cls");
            //usunZListyPrzyjaciol(przyjaciele);
            break;
        case '6':
           /* system("cls");
            int IDprzyjacielaDoEdycji;
            cout<<"Podaj ID przyjaciela do edycji: ";
            cin>>IDprzyjacielaDoEdycji;
            for(vector<Przyjaciel>::iterator i=przyjaciele.begin(); i<przyjaciele.end(); i++) {
                if(i->id==IDprzyjacielaDoEdycji) {
                    wyswietlPrzyjaciela(*i);
                    cout<<endl;
                    *i = edytujDanePrzyjaciela(*i);
                }
            }
          zapiszPrzyjaciolWPlikuTekstowym(przyjaciele);*/
            break;
        case '9': {
            exit(0);
        }
        default:
            cout<<"Podano niepoprawna opcje, sprobuj jeszce raz:";
            Sleep(1000);

                }
            }
        }

    return 0;
    }
