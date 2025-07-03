#include "Coords.h"
#include <iostream>
#include <cstdio>

void Coords::clear() { // kinullázás
    data = NULL;
    elnum = 0;
}

void Coords::push_back(const xypt &val) { // szokásos push_back
    xypt *temp;
    temp = new xypt[elnum+1];
    for (int i = 0; i <= elnum; ++i) {
        if (i == elnum) {
            temp[i] = val;
        }
        else {
            temp[i] = data[i];
        }
    }
    delete[] data;
    data = new xypt[elnum+1];
    for (int i = 0; i < elnum+1; ++i) {
        data[i] = temp[i];
    }
    delete[] temp;
    elnum = elnum + 1;
}
