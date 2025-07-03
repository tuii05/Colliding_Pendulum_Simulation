//Turú István (MLVT2A)
#include <cstdio>
#include <iostream>
#include "inga.h"
#include <stdexcept>
#ifndef PLOT_H_INCLUDED
#define PLOT_H_INCLUDED
class Plot {
private:
    unsigned w, h;
    bool *pmap;
public:
    Plot(signed wi, signed he) {
        if (wi <= 0) {throw std::domain_error("A szelesseg (w) csak pozitiv lehet! (1. koord.)");}
        if (he <= 0) {throw std::domain_error("A magassag (h) csak pozitiv lehet! (2. koord.)");}
        w = wi; h = he; pmap = new bool[w*h];  clear();
    }
    Plot(Plot &other) {
        w = other.w;
        h = other.h;
        if (int(sizeof(pmap)) != int(sizeof(other.pmap))) {
            for(int i = 0; i < int(sizeof(pmap)); ++i) {
                pmap[i] = other.pmap[i];
            }
        }
        else {
            throw std::domain_error("Nem ugyanakkora a két kijelzõ.");
        }
    }
    Plot & operator= (const Plot &other) {
        w = other.w;
        h = other.h;
        if ((sizeof(pmap)) == sizeof(other.pmap)) {
            for(int i = 0; i < int(sizeof(pmap)); ++i) {
                pmap[i] = other.pmap[i];
            }
        }
        else {
            throw std::domain_error("Nem ugyanakkora a ket kijelzo merete.");
        }
        return *this;
    }
    ~Plot() {pmap = NULL; delete[] pmap;}
    void phimax_keres(const Coords c, double &phi_max);
    void clear(){ for(unsigned i = 0; i<w*h; ++i) {pmap[i] = false;} }
    void rajzol() const;
    void graph(const Coords c);
};


#endif // PLOT_H_INCLUDED
