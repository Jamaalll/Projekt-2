#include <iostream>
#include <vector>
#include <fstream>
#include<time.h>
#include<chrono>
#include <unistd.h>
#include<limits.h>
#include <numeric>
#include <cstdlib>
//#include <conio.h>
//#include <stdio.h>
using namespace std;

vector<int> generujlosowe(int a)     //funkcja pozwala generowac losowy ciag dowolnej wielkosci
{
    vector<int> ciag_liczb;
    int i,liczba;
    srand ( time(NULL) );
    for(i=1; i<=a;i++)
    {
        liczba=rand()%100000+1;           //generujemy vektor pseudolosowych liczb
        ciag_liczb.push_back(liczba);
    }
    return ciag_liczb;
}


void wypisz_tablice(vector<int> a)
{
    for(int i=0;i<a.size();i++){
        cout<<a[i]<<endl;
    }
}


void zapisz_do_pliku(vector<int>  licz) {        // funkcja przejmuje wektor za arguemnt i zapisuje wynik w pliku tekstowym
    ofstream plik("liczby.txt");
    vector <int> s;
    if (plik.is_open())
    {
        plik<<"liczby "<<endl;
        for (int j = 0; j < licz.size(); j++) {
        plik<<licz[j]<<endl;            //zapisujemy dane do pliku
        }
        plik.close();
    }
    else cout << "Dany plik nie istnieje";
}


vector<int> wczytaj(const char* liczby) {   // wczytywanie danych z pliku do tablicy dynamicznej
    fstream plik(liczby, std::ios_base::in);
        vector<int> wektor;                     //inicjalizacja wektora o nazwie vec typu calkowitego
        int a;
                                            //cout << "Wczytywanie danych: " << endl;
    while (plik >> a){                      // zwracanie funkcji
        wektor.push_back(a);                //dodawanie elementów na koniec tablicy
                                            //cout << "Wczytano " << a << endl; // wczytanie i wypisanie
    }
   plik.close();                            // zamkniecie strumienia po wczytaniu
    return wektor;                           //zwrócenie wektora
}



vector<int> grzebieniowe(vector<int> licz)
{

   int  tmp,gap;
    gap= licz.size();
   bool swapped = true;
   while (gap > 1 || swapped){                               // jezeli gap = 1 i nie dokonano zamiany - wyjscie z petli
      gap = gap/1.3;
      if(gap==0)
            gap=1;
      swapped = false;
      for ( int i = 0; i + gap < licz.size(); ++i ) {       // wykonuj od 0 do ostatniego elementu tablicy
         if ( licz[i + gap] < licz[i] ) {                   // porównanie elementów odleglych o rozpietosc
            tmp = licz[i];                                  // zamiana elementów
            licz[i] = licz[i + gap];
            licz[i + gap] = tmp;
            swapped = true;
           }
      }
   }
    return licz;
}

vector<int> babelkowe(vector<int> licz) {
        bool swapped; // Czy zamieniono w ostatnim obrocie?
        int n;
        n=licz.size();
        do {
            swapped = false;
            for (int i = 0; i < n - 1; i++) { //zwiekszanie iteracji o 1
                if (licz[i] > licz[i + 1]) {        // jezeli element poprzedni wiekszy niz nastepny zamiana miejsc
                    swap(licz[i], licz[i + 1]);
                    swapped = true;
                }
            }
            n=n-1;              //n-1 po kazdym przejsciu petli for pozwala na optymalizacje funcji
        } while (swapped);
        return licz;
    }



 void testy(int a){                                                                                                         // w tej funkcji testujemy w jakim czasie funkcja sortuje dane
    vector<int> s,c;                                                                                                                    //deklarujemy wektory ktore pozniej przydadza nam sie do wywolywania innych funcji
 double sredni_czas=0,tmp=1000000000,tmp1=0;
 int i,liczba_testow = 1000,wynik;
 for(i=1;i<=liczba_testow;i++){

    s=generujlosowe(a);                                                                                                         //wywolujemy funkcje ktora generuje liczby pseudolosowe
    zapisz_do_pliku(s);
    c=wczytaj("liczby.txt");                                                                                            //zapisujemy do pliku a nastepnie wczytujemy by wyniki byly wiarygodne

    auto start =chrono::steady_clock::now();                                                                                             //mierzymy czas w jakim funkcja sortuje dane
    grzebieniowe(c);
    //babelkowe(c);
    auto stop = chrono::steady_clock::now();

    wynik=chrono::duration_cast<chrono::nanoseconds>(stop-start).count();

    if(wynik<tmp)
    tmp=wynik;
    if(wynik>tmp1)
    tmp1=wynik;
    sredni_czas=sredni_czas+wynik;                                                                        //tutaj liczymy sredni czas dzialania funkcji
    }
    sredni_czas=sredni_czas/liczba_testow;
    cout<<endl<<" sredni czas dzialania funkcji przy 10 probach dla ciagu "
    <<a<<" liczb "<<endl<<" to: "<<sredni_czas<<" nanosekund"<<endl;
    cout<<"optymistyczny czas to: "<<tmp<<endl<<"pesymistyczny czas to: "<<tmp1;
 }



int main()
{
    vector<int> s,a,b;
    int ilosc_licz;
    cout<<"podaj dlugosc ciagu dla jakiego chcesz przeprowadzic testy:  ";
    cin>>ilosc_licz;   // podajemy dla jakiej ilosci liczb mamy przeprowadzic testy
   testy(ilosc_licz); //wywolujemy funkcje testujaca
   return 0;
}
