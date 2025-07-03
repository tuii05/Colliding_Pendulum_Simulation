//Tur� Istv�n (MLVT2A)
//Be�p�tett k�nyvt�rak
#include <iostream>
#include <cstdio>
//Saj�t
#include "inga.h"
#include "plot.h"
#include "dpen.h"

using namespace std;


int main()
{
    try{
        //F�jlb�l beolvas�s
        double phi0, L, m, k;
        inga proba1, proba2;
        proba1.konvert("adatok.txt", 1);
        proba2.konvert("adatok.txt", 2);
        //-----------------
        //<<, >> oper�torok tesztel�se
        inga proba3;
        cin >> proba3;
        cout << proba3;
        //----------------------------
        //Szimul�ci� �s kirajzoltat�s
        double e;
        cout << "Mekkora a rugalmassagi egyutthato? e = ";
        cin >> e;
        Coords e1;
        cout << proba1;
        cout << "\n";
        double T;
        cout << "Mennyi ideig szimulaljuk? (s): " << ' ';
        cin >> T;
        e1 = proba1.ujcoords(T);
        Plot abra(120,20);
        abra.graph(e1);
        //inga proba2(-45,1,2,0.9);
        Coords c1, c2;
        dpen teszt(proba1, proba2, e);
        teszt.ujcoords(T, c1, c2);
        cout << '\n';
        cout << "\n| INGA 1 | \n";
        abra.graph(c1);
        cout << '\n';
        cout << "\n| INGA 2 | \n";
        abra.graph(c2);
        //---------------------------
    }
    //Hibakezel�s
    catch(std::exception &e) {
        fprintf(stderr, e.what());
        return -1;
    }
    catch(...) {
        fprintf(stderr, "Ismeretlen hiba");
        return -2;
    }
    return 0;
}
