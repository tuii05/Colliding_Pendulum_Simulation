//Turú István (MLVT2A)
#ifndef COORDS_H_INCLUDED
#define COORDS_H_INCLUDED
#include <iostream>
#include <cstdio>
#include "Coords.h"

struct xypt{double x, y, phi, phidot, t;};

class Coords{
private:
    xypt *data;
    int elnum;
public:
    Coords() {elnum=0; data = NULL;}
    ~Coords() {delete[] data;}
    Coords(const Coords &other) {
        elnum = other.elnum;
        data = new xypt[elnum];
        for (int i = 0; i < elnum; ++i) {
            data[i] = other.data[i];
        }
    }
    const Coords &operator=(const Coords &other) {
        if (this != &other) {
            delete[] data;
            elnum = other.elnum;
            data = new xypt[elnum];
            for (int i = 0; i < elnum; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    xypt & operator[] (int n) {return data[n];}
    const xypt &operator[] (int n) const {return data[n];}
    int size() const {return elnum;}
    void clear();
    void push_back(const xypt &val);
};


#endif // COORDS_H_INCLUDED
