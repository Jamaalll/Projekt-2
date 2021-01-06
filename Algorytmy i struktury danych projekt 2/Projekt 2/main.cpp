#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <fstream>
using namespace std;

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
   while (gap > 1 || swapped){                          // jezeli gap = 1 i nie dokonano zamiany - wyjœcie z petli
      gap = gap/1.3;
      if(gap==0)
            gap=1;
      swapped = false;
      for ( int i = 0; i + gap < licz.size(); ++i ) {       // wykonuj od 0 do ostatniego elementu tablicy
         if ( licz[i + gap] < licz[i] ) {               // porównanie elementów odleg³ych o rozpiêtoœæ
            tmp = licz[i];                              // zamiana elementów
            licz[i] = licz[i + gap];
            licz[i + gap] = tmp;
            swapped = true;
           }
      }
   }
    return licz;
}

vector<int> babelkowe(vector<int> licz) {
        bool swapped;                                           // Czy zamieniono w ostatnim obrocie?
        int n;
        n=licz.size();
        do {
            swapped = false;
            for (int i = 0; i < n - 1; i++) {           //zwiekszanie iteracji o 1
                if (licz[i] > licz[i + 1]) {                    // jezeli element poprzedni wiekszy niz nastepny zamiana miejsc
                    swap(licz[i], licz[i + 1]);
                    swapped = true;
                }
            }
            n=n-1;                                          //n-1 po kazdym przejsciu petli for pozwala na optymalizacje funcji
        } while (swapped);
        return licz;
    }



void zapisz_do_pliku(vector<int>  licz) {        // funkcja przejmuje wektor za arguemnt i zapisuje wynik w pliku tekstowym
    ofstream plik("wyniki.txt");
    //vector <int> s;
    if (plik.is_open())
    {
        plik<<"liczby po posortowaniu "<<endl;
        cout<<"liczby po posortowaniu "<<endl;
        for (int j = 0; j < licz.size(); j++) {
        plik<<licz[j]<<endl;
        cout<<licz[j]<<" ";

        }
        plik.close();
    }
    else cout << "Dany plik nie istnieje";
}


int main()
{
    vector <int> s,g;
    vector <int> liczby= wczytaj("liczby.txt");
 char x;
 for(;;)            //nieskonczona petla for pozostawia program otwarty dopoki nie zdecydujemy sie go zamknac
 {
 cout<<" Ktora metode sortowania chcesz uzyc"<<endl;    //wyswietlamy menu na ekranie
 cout<<" 1. Sortowanie grzebieniowe"<<endl;
 cout<<" 2. Sortowanie babelkowe"<<endl;
 cout<<" 3. Koniec Programu"<<endl;
 cout<<" Wybierz: "<<endl; x=getch();

 switch(x)          //funkcja switch pozwala nam wybierac z ktorego sortowania chcemy skorzystac
 {
     case '1':{     // pierwszy przypadek to sortowanie grzebieoniowe
        cout<<" grzebieniowe"<<endl<<endl;
       s=grzebieniowe(liczby);
       zapisz_do_pliku(s);
         break;
     //bublesort
     }
     case '2':{        //drugi przypadek to sortowanie babelkowe
         cout<<" babelkowe"<<endl<<endl;
         g=babelkowe(liczby);
         zapisz_do_pliku(g);
         break;

     //sortowanie grzebieniowe
     }
     case '3': exit(0);             //trzeci przypadek oznacza zamkniecie funkcji
     default: cout<<" Wybierz liczbe 1,2 lub 3 !!"<<endl; //gdy wcisniemy inny przycisk niz 1,2 lub 3 na ekranie pojawia sie taki komunikat
 }
 getchar();getchar();       //funkcja poczeka na enter
 system("cls");             //po kazdym obiegu petli ekran zostaje wyczyszczony
 }

return 0;
}
