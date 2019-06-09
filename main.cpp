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
void dodajPrzyjacielaDoListy(vector<Przyjaciel> &przyjaciele, int *idUzytkownika) {
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

    fstream plikTekstowy;
     plikTekstowy.open("przyjaciele.txt",ios::in);
    if (plikTekstowy.good()==true) {
        nowyPrzyjaciel.id=wczytajIDOstatniegoPrzyjaciela();
        nowyPrzyjaciel.id+=1;
    } else
        nowyPrzyjaciel.id=1;
    przyjaciele.push_back(nowyPrzyjaciel);
    zapiszPrzyjaciolWPlikuTekstowym(nowyPrzyjaciel,*idUzytkownika);
    plikTekstowy.close();
    Sleep(1500);
}
Przyjaciel edytujDanePrzyjaciela(Przyjaciel przyjacielDoEdycji) {
    cout<<"Edytowanie danych znajomego"<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"1.Imie"<<endl;
    cout<<"2.Nazwisko"<<endl;
    cout<<"3.Numer telefonu"<<endl;
    cout<<"4.Email"<<endl;
    cout<<"5.Adres"<<endl;
    cout<<"6.Powrot do menu"<<endl;
    int wybor;

    cin>>wybor;
    switch(wybor) {
    case 1:
        cout<<"podaj zmienione imie: ";
        cin>>przyjacielDoEdycji.imie;
        return przyjacielDoEdycji;
    case 2:
        cout<<"podaj zmienione nazwisko: ";
        cin>>przyjacielDoEdycji.nazwisko;
        return przyjacielDoEdycji;
    case 3:
        cout<<"podaj zmieniony numer telefonu: ";
        cin.sync();
        getline(cin,przyjacielDoEdycji.numerTelefonu);
        return przyjacielDoEdycji;
    case 4:
        cout<<"podaj zmieniony email: ";
        cin>>przyjacielDoEdycji.email;
        return przyjacielDoEdycji;
    case 5:
        cout<<"podaj zmieniony adres: ";
        cin.sync();
        getline(cin,przyjacielDoEdycji.adres);
        return przyjacielDoEdycji;
    case 6:
        return przyjacielDoEdycji;
    }
}
void edytujPrzyjacielaZZapisemDoPliku(vector <Przyjaciel> &przyjaciele, int idZalogowanegoUzytkownika)
{
   int IDprzyjacielaDoEdycji;
     Przyjaciel przyjacielDoZmianyDanych;
     bool znalezieni = false;
            cout<<"Podaj ID przyjaciela do edycji: ";
            cin>>IDprzyjacielaDoEdycji;
            for(vector<Przyjaciel>::iterator i=przyjaciele.begin(); i<przyjaciele.end(); i++) {
                if(i->id==IDprzyjacielaDoEdycji) {
                    wyswietlPrzyjaciela(*i);
                    cout<<endl;
                    *i = edytujDanePrzyjaciela(*i);
                    przyjacielDoZmianyDanych=*i;
                    znalezieni=true;
                }
                 if(i->id==przyjaciele.back().id&&znalezieni==false)
                {
                    cout<<"nie znaleniono przyjaciela o podanym id";
                    return;
                }
            }
    fstream plik, plikTymczasowy;
    string linia;
    plikTymczasowy.open("przyjaciele_tymczasowy.txt",ios::out);
    plik.open("przyjaciele.txt",ios::in);
    while(!plik.eof())
    {
       getline(plik,linia,'|');
        if(linia=="\n"||linia=="") {
                break;
            }
       int iDPobraneZPliku=konwersjaStringNaInt(linia);
       if(iDPobraneZPliku==IDprzyjacielaDoEdycji)
       {
           plikTymczasowy<<przyjacielDoZmianyDanych.id<<'|';
           plikTymczasowy<<przyjacielDoZmianyDanych.idUzytkownika<<'|';
           plikTymczasowy<<przyjacielDoZmianyDanych.imie<<'|';
           plikTymczasowy<<przyjacielDoZmianyDanych.nazwisko<<'|';
           plikTymczasowy<<przyjacielDoZmianyDanych.numerTelefonu<<'|';
           plikTymczasowy<<przyjacielDoZmianyDanych.email<<'|';
           plikTymczasowy<<przyjacielDoZmianyDanych.adres<<'|';
           plikTymczasowy<<endl;
           getline(plik,linia);
       }
       else
       {
           plikTymczasowy<<linia<<'|';
           getline(plik,linia);
           plikTymczasowy<<linia<<endl;
       }
    }
    plik.close();
    plikTymczasowy.close();
    remove("przyjaciele.txt");
    rename("przyjaciele_tymczasowy.txt","przyjaciele.txt");
}
void usunZListyPrzyjaciol(vector <Przyjaciel> &przyjaciele) {
    if(przyjaciele.size()==0)
        cout<<"Brak zapisanych przyjaciol";
    else {
        int numerIDPrzyjaciela;
        cout<<"Podaj numer ID przyjaciela ktorego chcesz usunac z listy: ";
        cin>>numerIDPrzyjaciela;
        bool znalezionoIDPrzyjaciela=false;
        for(vector<Przyjaciel>::iterator i=przyjaciele.begin(); i<przyjaciele.end(); i++) {
            if(i->id==numerIDPrzyjaciela) {
                wyswietlPrzyjaciela(*i);
                cout<<"czy na pewno chcesz usnunac przyjaciela z listy(wcisnij 't' aby potwierdzic): ";
                cin.ignore();
                if(getchar()=='t') {
                    przyjaciele.erase(i);
                    znalezionoIDPrzyjaciela=true;
                    cout<<"Usunieto przyjaciela z listy. ";
                } else {
                    cout<<"Nie usunieto przyjaciela";
                    znalezionoIDPrzyjaciela=true;
                }
            }
        }
        if (znalezionoIDPrzyjaciela==false) {
            cout<<"Nie znalezniono przyjaciela o podanym ID.";
        }
        fstream plik, plikTymczasowy;
    string linia;
    plikTymczasowy.open("przyjaciele_tymczasowy.txt",ios::out);
    plik.open("przyjaciele.txt",ios::in);
    while(!plik.eof())
    {
       getline(plik,linia,'|');
        if(linia=="\n"||linia=="") {
                break;
            }
       int iDPobraneZPliku=konwersjaStringNaInt(linia);
       if(iDPobraneZPliku==numerIDPrzyjaciela)
       {
           getline(plik,linia);
       }
       else
       {
           plikTymczasowy<<linia<<'|';
           getline(plik,linia);
           plikTymczasowy<<linia<<endl;
       }
    }
    plik.close();
    plikTymczasowy.close();
    remove("przyjaciele.txt");
    rename("przyjaciele_tymczasowy.txt","przyjaciele.txt");
    }
    Sleep(3000);
}
void wyszukajPrzyjaciolOPodanymImieniu(vector<Przyjaciel> &przyjaciele) {
    string szukaneImie;
    int znalezieni=0;
    cout<<"Prosze podac imie do wyszukiwania przyjaciol: ";
    cin>>szukaneImie;
    for(vector<Przyjaciel> ::iterator itr=przyjaciele.begin(); itr!=przyjaciele.end(); itr++) {
        if(itr->imie==szukaneImie) {
            wyswietlPrzyjaciela(*itr);
            znalezieni++;
        }
    }
    if(znalezieni==0)
        cout<<"nie znaleziono przyjaciol o tym imieniu"<<endl;
    else
        cout<<"znaleziono "<<znalezieni<<" przyjaciol o podanym imieniu"<<endl;
    system("pause");
}
void wyszukajPrzyjaciolOPodanymNazwisku(vector<Przyjaciel> &przyjaciele) {
    string szukaneNazwisko;
    int znalezieni=0;
    cout<<"Prosze podac nazwisko do wyszukiwania przyjaciol: ";
    cin>>szukaneNazwisko;
    for(vector<Przyjaciel> ::iterator itr=przyjaciele.begin(); itr!=przyjaciele.end(); itr++) {
        if(itr->nazwisko==szukaneNazwisko) {
            wyswietlPrzyjaciela(*itr);
            znalezieni++;
        }
    }
    if(znalezieni==0)
        cout<<"nie znaleziono przyjaciol o tym nazwisku"<<endl;
    else
        cout<<"znaleziono "<<znalezieni<<" przyjaciol o podanym nazwisku"<<endl;
    system("pause");
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
                cout<<idZalogowanegoUzytkownika;
                system("pause");
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
        char wybor;
        vector <Przyjaciel> przyjaciele;
        cout<<endl<<"id uzytk. przed menu"<<idZalogowanegoUzytkownika<<endl;
                system("pause");
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
            dodajPrzyjacielaDoListy(przyjaciele,&idZalogowanegoUzytkownika);
            cout<<endl<<"id uzytk po dodaniu"<<idZalogowanegoUzytkownika<<endl;
                system("pause");
            break;
        }
        case '2': {
            system("cls");
            wyszukajPrzyjaciolOPodanymImieniu(przyjaciele);
            break;
        }
        case '3': {
            system("cls");
            wyszukajPrzyjaciolOPodanymNazwisku(przyjaciele);
            break;
        }
        case '4': {
            system("cls");
            wyswietlWszystkichPrzyjaciol(przyjaciele);
            cout<<endl<<"id uzytk po wyswietleniu"<<idZalogowanegoUzytkownika<<endl;
                system("pause");
            break;
        }
        case '5':
            system("cls");
            usunZListyPrzyjaciol(przyjaciele);
             cout<<endl<<"id uzytk po usunieciu: "<<idZalogowanegoUzytkownika<<endl;
                system("pause");
            break;
        case '6':
            system("cls");
            edytujPrzyjacielaZZapisemDoPliku(przyjaciele,idZalogowanegoUzytkownika);
            cout<<endl<<"id uzytk po edycji"<<idZalogowanegoUzytkownika<<endl;
                system("pause");
            break;
        case '7': {
            zmianaHasla(uzytkownicy,idZalogowanegoUzytkownika);
            break;
        }
        case '8': {
            idZalogowanegoUzytkownika=0;
            break;
        }
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
