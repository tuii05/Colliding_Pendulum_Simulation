//Turú István (MLVT2A)
#include <iostream>
#include <cstdio>
#include "inga.h"
#include <stdexcept>
#include <math.h>

#ifndef DPEN_H_INCLUDED
#define DPEN_H_INCLUDED

class dpen{
private:
    inga inga1, inga2;
    double e;
    //const double eps = 0.05;
public:
    dpen(const inga inga_1, const inga inga_2, double e1) { // Ha x1+x2=d és y1=y2, akkor lefusson. (d = kettõ közötti távolság);
        if (e1 < 0 || e1 > 1) {throw std::domain_error("A rugalmassagi egyutthato csak [0,1] intervallumon ertelmezett! (3. koord.)");}
        if ((inga_1.getL()*cos(fabs(inga_1.getPhi0())) - inga_2.getL()*cos(fabs(inga_2.getPhi0()))) > 0.001) {throw std::domain_error("A szogparok mellett nem egy magassagban vannak a kozeppontok!");}
        inga1 = inga_1;
        inga2 = inga_2;
        e = e1;
    }
    void ujcoords(double T, Coords &c1, Coords &c2);
    void ref_dt(const xypt c0_1, const xypt c0_2, double &dt);
};

#endif // DPEN_H_INCLUDED
