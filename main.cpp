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
struct Przyjaciel {
    int id, idUzytkownika;
    string imie, nazwisko;
    string numerTelefonu;
    string email, adres;
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
void zmianaHasla(vector<Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string haslo;
    cout<<"Prosze podac nowe haslo: ";
    cin>>haslo;
    for(vector<Uzytkownik>::iterator i=uzytkownicy.begin(); i!=uzytkownicy.end(); i++)
    {
        if(i->id == idZalogowanegoUzytkownika)
        {
            i->haslo=haslo;
            cout<<"zmieniono haslo! ";
            Sleep(1000);
        }
    }
    fstream plik;
    plik.open("uzytkownicy.txt", ios::out);
    for(vector<Uzytkownik>::iterator i=uzytkownicy.begin(); i!=uzytkownicy.end(); i++)
    {
        plik<<i->id<<'|';
        plik<<i->nazwa<<'|';
        plik<<i->haslo<<'|'<<endl;
    }
    plik.close();
}
void wczytajPrzyjaciolzPliku(vector<Przyjaciel> &przyjaciele, int idUzytkownika) {
    fstream plik;
    string odczytywanaLinia;
    Przyjaciel nowyPrzyjaciel;
    plik.open("przyjaciele.txt",ios::in);
    while(plik.good()==true) {
        while( !plik.eof() ) {
            getline(plik,odczytywanaLinia,'|');
            if(odczytywanaLinia=="\n"||odczytywanaLinia=="") {
                break;
            }
            nowyPrzyjaciel.id=konwersjaStringNaInt(odczytywanaLinia);
            getline(plik,odczytywanaLinia,'|');
            nowyPrzyjaciel.idUzytkownika=konwersjaStringNaInt(odczytywanaLinia);
            getline(plik,odczytywanaLinia,'|');
            nowyPrzyjaciel.imie=odczytywanaLinia;
            getline(plik,odczytywanaLinia,'|');
            nowyPrzyjaciel.nazwisko=odczytywanaLinia;
            getline(plik,odczytywanaLinia,'|');
            nowyPrzyjaciel.numerTelefonu=odczytywanaLinia;
            getline(plik,odczytywanaLinia,'|');
            nowyPrzyjaciel.email=odczytywanaLinia;
            getline(plik,odczytywanaLinia,'|');
            nowyPrzyjaciel.adres=odczytywanaLinia;
            if(nowyPrzyjaciel.idUzytkownika==idUzytkownika)
            {
                przyjaciele.push_back(nowyPrzyjaciel);
            }
        }
    }
    plik.close();
}
void wyswietlPrzyjaciela(Przyjaciel przyjaciel) {
    cout<<"ID: "<<przyjaciel.id<<endl;
    cout<<przyjaciel.imie<<endl;
    cout<<przyjaciel.nazwisko<<endl;
    cout<<przyjaciel.numerTelefonu<<endl;
    cout<<przyjaciel.email<<endl;
    cout<<przyjaciel.adres<<endl;
}
void wyswietlWszystkichPrzyjaciol(vector <Przyjaciel> &przyjaciele) {
    for(vector<Przyjaciel> ::iterator itr=przyjaciele.begin(); itr!=przyjaciele.end(); itr++) {
        wyswietlPrzyjaciela(*itr);
    }
    system("pause");
}
int wczytajIDOstatniegoPrzyjaciela()
{
     fstream plik;
     plik.open("przyjaciele.txt",ios::in);
    plik.seekg(-3, ios::end);
    char wskaznik;
   while(wskaznik!='\n')
   {
       plik.seekg(-3,ios::cur);
       wskaznik=plik.get();
   }
     string linia;
    getline(plik,linia,'|');
    int liczba=konwersjaStringNaInt(linia);
    plik.close();
    return liczba;
}
void zapiszPrzyjaciolWPlikuTekstowym(Przyjaciel nowyPrzyjaciel, int idUzytkownika)
{
         fstream plikt;
        plikt.open("przyjaciele.txt",ios::out|ios::app);
        plikt.seekg(0, ios::end);
            plikt<<nowyPrzyjaciel.id<<'|';
            plikt<<idUzytkownika<<'|';
            plikt<<nowyPrzyjaciel.imie<<'|';
            plikt<<nowyPrzyjaciel.nazwisko<<'|';
            plikt<<nowyPrzyjaciel.numerTelefonu<<'|';
            plikt<<nowyPrzyjaciel.email<<'|';
            plikt<<nowyPrzyjaciel.adres<<'|';
            plikt<<endl;
        plikt.close();

}
void dodajPrzyjacielaDoListy(vector<Przyjaciel> &przyjaciele, int idUzytkownika) {
    Przyjaciel nowyPrzyjaciel;
    cout<<"Podaj imie znajomego: ";
    cin>>nowyPrzyjaciel.imie;
    cout<<"Podaj nazwisko znajomego: ";
    cin>>nowyPrzyjaciel.nazwisko;
    cout<<"Podaj email znajomego: ";
    cin>>nowyPrzyjaciel.email;
    cout<<"Podaj numer telefonu znajomego: ";
    cin.sync();
    getline(cin,nowyPrzyjaciel.numerTelefonu);
    cout<<"Podaj adres znajomego: ";
    cin.sync();
    getline(cin,nowyPrzyjaciel.adres);

    if (przyjaciele.size()>0) {
        nowyPrzyjaciel.id=wczytajIDOstatniegoPrzyjaciela();
        nowyPrzyjaciel.id+=1;
    } else
        nowyPrzyjaciel.id=1;
    przyjaciele.push_back(nowyPrzyjaciel);
    zapiszPrzyjaciolWPlikuTekstowym(nowyPrzyjaciel,idUzytkownika);
    Sleep(1500);
}
void wyswietlMenuKsiazkiAdresowej(int idZalogowanegoUzytkownika, vector <Uzytkownik> &uzytkownicy)
{
        system("cls");
        char wybor;
        vector <Przyjaciel> przyjaciele;
        wczytajPrzyjaciolzPliku(przyjaciele,idZalogowanegoUzytkownika);
        cout<<"MENU Ksiazka adresowa"<<endl;
        cout<<"-----------"<<endl;
        cout<<"1.Dodaj nowego przyjaciela"<<endl;
        cout<<"2.Wyswietl wszystkich przyjaciol o podanym imieniu"<<endl;
        cout<<"3.Wyswietl wszystkich przyjaciol o podanym nazwisku"<<endl;
        cout<<"4.Wyswietl wszystkich przyjaciol"<<endl;
        cout<<"5.Usun z listy przyjaciol"<<endl;
        cout<<"6.Edytuj dane wybranego przyjaciela"<<endl;
        cout<<"7.Zmieñ has³o"<<endl;
        cout<<"8.Wyloguj siê"<<endl;
        cout<<"9.Wyjscie z programu"<<endl;
        cin>>wybor;

        switch(wybor) {
        case '1': {
            system("cls");
            dodajPrzyjacielaDoListy(przyjaciele,idZalogowanegoUzytkownika);
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
            wyswietlWszystkichPrzyjaciol(przyjaciele);
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
        case '7': {
            zmianaHasla(uzytkownicy,idZalogowanegoUzytkownika);
            break;
        }
        case '8': {
            idZalogowanegoUzytkownika=0;
            return;
        }
        case '9': {
            exit(0);
        }
        default:
            cout<<"Podano niepoprawna opcje, sprobuj jeszce raz:";
            Sleep(1000);

                }
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
                wyswietlMenuKsiazkiAdresowej(idZalogowanegoUzytkownika,uzytkownicy);
            }
        }

    return 0;
    }
