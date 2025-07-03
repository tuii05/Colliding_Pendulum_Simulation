#include "dpen.h"
#include <iostream>
#include <cstdio>
#include "inga.h"
#include <math.h>

void dpen::ref_dt(const xypt c0_1, const xypt c0_2, double &dt) { // dt finomítása
    double dt_1, dt_2;
    double dt_x = 0.1;
    inga1.refine_dt(c0_1,dt_x);
    dt_1 = dt_x;
    inga2.refine_dt(c0_2,dt_x);
    dt_2 = dt_x;
    if (dt_1 < dt_2) {
        dt = dt_1;
    }
    else {
        dt = dt_2;
    }
}

void dpen::ujcoords(double T, Coords &c1, Coords &c2) { //erõtörvény iterációja kettõ darab ingánál
    double dt, x0, y0;
    double phidot_new1, phidot_new2;
    double eps = 0.001;
    c1.clear(); // c1.clear()
    c2.clear(); // c2.clear()
    xypt c0_1, c0_2;
    if (inga1.getPhi0() > inga2.getPhi0()) {
        c0_1 = {inga1.getL()*sin(inga1.getPhi0()), inga1.getL()*cos(inga1.getPhi0()), inga1.getPhi0(), 0, 0};
        c0_2 = {inga2.getL()*sin(inga2.getPhi0()), inga2.getL()*cos(inga2.getPhi0()), inga2.getPhi0(), 0, 0};
    }
    else {
        c0_2 = {inga1.getL()*sin(inga1.getPhi0()), inga1.getL()*cos(inga1.getPhi0()), inga1.getPhi0(), 0, 0};
        c0_1 = {inga2.getL()*sin(inga2.getPhi0()), inga2.getL()*cos(inga2.getPhi0()), inga2.getPhi0(), 0, 0};
    }
    x0 = c0_1.x;
    c0_2.x = x0+c0_2.x;
    ref_dt(c0_1, c0_2, dt);
    c1.push_back(c0_1);
    c2.push_back(c0_2);
    double beta_1 = inga1.iteracio(c0_1, dt);
    double beta_2 = inga2.iteracio(c0_2, dt);
    while(c0_1.t < T) {
        c0_2.x = x0 + c0_2.x;
        c1.push_back(c0_1);
        c2.push_back(c0_2);
        if ((fabs(c0_1.x - c0_2.x) < eps) && (fabs(c0_1.y - c0_2.y) < eps)) {
            phidot_new1 = (inga1.getM()*c0_1.phidot+inga2.getM()*c0_2.phidot+inga2.getM()*e*(c0_2.phidot-c0_1.phidot))/(inga1.getM()+inga2.getM());
            phidot_new2 = (inga1.getM()*c0_1.phidot+inga2.getM()*c0_2.phidot+inga1.getM()*e*(c0_1.phidot-c0_2.phidot))/(inga1.getM()+inga2.getM());
            c0_1.phidot = phidot_new1;
            c0_2.phidot = phidot_new2;
        }
        beta_1 = inga1.iteracio(c0_1, dt);
        beta_2 = inga2.iteracio(c0_2, dt);
    }
}
