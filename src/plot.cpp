#include <cstdio>
#include <iostream>
#include "plot.h"
#include <math.h>

void Plot::phimax_keres(const Coords c, double &phi_max) { // phi értékek közül megkeresi a maximumot
    double temp_max = c[0].phi;
    double temp_min = temp_max;
    for (unsigned i = 0; i < unsigned(c.size()); ++i) {
        if (temp_max < c[i].phi) {
            temp_max = c[i].phi;
        }
        if (temp_min > c[i].phi) {
            temp_min = c[i].phi;
        }
    }
    if (fabs(temp_max) > fabs(temp_min)) {
        if (c[0].phi > 0) {
            phi_max = temp_max;
        }
        else {
            phi_max = -temp_max;
        }
    }
    else if (fabs(temp_max) <= fabs(temp_min)){
        if (c[0].phi > 0) {
            phi_max = temp_min;
        }
        else {
            phi_max = -temp_min;
        }
    }
}

void Plot::rajzol() const { //kirajzolja a bitmapet
    for(unsigned i = 0; i < w*h; ++i) {
        if (pmap[i] == true) {
            std::cout << '*';
        }
        else if (pmap[i] == false) {
            std::cout << ' ';
        }
    }
}

void Plot::graph(const Coords c) { // phi-t grafikon elkészítése, és kiírása a konzolra
    int t_e, phi_hely, te_hely, t_hely;
    double phi_max;
    phimax_keres(c, phi_max);
    t_e = c[c.size()-1].t/(w);
    te_hely = (c.size()-1)/(w); // feltételezve, hogy mindig dt-vel haladunk
    int j = 0;
    for(unsigned i = 0; i < w; ++i, ++j) {
        t_hely = j*te_hely;
        phi_hely = h/2*(c[t_hely].phi/phi_max);
        pmap[(h/2-phi_hely)*w+j] = true; // [-phi_max; phi_max] intervallumban
       // std::cout << "(" << j << "," << phi_hely << ")" << '\n';
    }
    std::cout << '\n' << "phi - t \n";
    if (phi_max > 0) {
        std::cout << "phi: [" << (-1)*phi_max << "," << phi_max << "]" << '\n';
    }
    else {
        std::cout << "phi: [" << phi_max << "," << (-1)*phi_max << "]" << '\n';
    }
    std::cout << "t: [0," << c[c.size()-1].t << "]" << '\n';
    rajzol();
    clear();
}
