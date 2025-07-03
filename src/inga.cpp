#include <cstdio>
#include <iostream>
#include "inga.h"
#include <math.h>
#include "Coords.h"


void inga::refine_dt(const xypt c0, double &dt) { // megfelelő dt megtalálása
    double eps = 0.005;
    double phidot_1, phidot_2;
    double theta = m*L*L;
    phidot_1 = (1-k*L*L/theta*dt)*phi0-m*g*L/theta*sin(phi0);
    dt = dt/2;
    phidot_2 = (1-k*L*L/theta*dt)*phi0-m*g*L/theta*sin(phi0);
    while (fabs(phidot_1 - phidot_2) > eps) {
        phidot_1 = phidot_2;
        dt = dt/2;
        phidot_2 = (1-k*L*L/theta*dt)*phi0-m*g*L/theta*sin(phi0);
    }
    //std::cout << '\n' << "dt:" << dt << '\n';
}

double inga::iteracio(xypt &c0, double dt) { // mozgás iterációja
    double phi, phidot;
    double phi0 = c0.phi;
    double phidot0 = c0.phidot;
    double theta = m*L*L;
    double beta;
    //std::cout << "\nTest2: dt:" << dt << '\n';
    phidot = (1-k*L*L/theta*dt)*phidot0-m*g*L/theta*sin(phi0)*dt; // szögsebesség dt idő múlva
    phi = phidot0*dt + phi0; //szögelfordulás dt idő múlva
    beta = (phidot-phidot0)/dt;
    c0.t += dt;
    c0.x = L*sin(phi);
    c0.y = L*cos(phi);
    c0.phi = phi;
    c0.phidot = phidot;
    return beta;
}


Coords inga::ujcoords(double T) { //erőtörvény megoldásának iterálása
    double dt = 0.1;
    double theta = m*L*L;
    double hiba = 0.01;
    xypt c0 = {L*sin(phi0), L*cos(phi0), phi0, 0, 0};
    Coords c;
    c.push_back(c0);
    refine_dt(c0, dt);
    double beta = iteracio(c0, dt);
    while (c0.t < T) {
        c.push_back(c0);
        beta = iteracio(c0, dt);
    }
    std::cout<<'\n';
    return c;
}

using namespace std;
void inga::konvert(string file, int sorszam) {
    ifstream fp(file);
    string line;
    for (int i = 0; i != sorszam; ++i) {
        getline(fp, line);
    }
    string *t;
    t = new string[4];
    string t2;
    int z = 0;
    bool skip = false;
    for(std::string::iterator it = line.begin(); *it != '\0'; ++it) {
        if((isdigit(*it) == true || *it == '-') && (it != line.end())) {
            if (*it == '-') {
                ++it;
                if (isdigit(*it) != true) {
                    skip = true;
                }
                --it;
            }
            if(skip == false) {
                t2 += *it;
                ++it;
                while((isdigit(*it) == true || *it == '.' || *it == ',') && it != line.end()) {
                    if(*it == ',') {
                        t2 += '.';
                    }
                    else {
                        t2 += *it;
                    }
                    ++it;
                }
                t[z] = t2;
                t2 = "";
                ++z;
            }
            skip = false;
        }
    }
    fp.close();
    phi0 = stod(t[0])*3.14/180;
    L = stod(t[1]);
    m = stod(t[2]);
    k = stod(t[3]);
    if(stod(t[0]) > 360) {throw std::domain_error("Az inga kezdeti szogkiterese csak 0<=phi<=360 kozotti erteket vehet fel!");}
    if (L < 0) {throw std::domain_error("Az inga h, ssza (L) csak nemnegativ lehet!");}
    if (m <= 0) {throw std::domain_error("Az inga tömege (m) csak pozitiv lehet!");}
    if (k < 0) {throw std::domain_error("Az inga kozegellenallasi tenyezoje (k) csak nemnegativ lehet!");}
    delete[] t;
}
