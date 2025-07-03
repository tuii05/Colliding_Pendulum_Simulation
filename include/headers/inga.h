//Turú István (MLVT2A)
#include <cstdio>
#include <iostream>
#include "Coords.h"
#include <stdexcept>
#include <string>
#include <fstream>

#ifndef INGA_H_INCLUDED
#define INGA_H_INCLUDED

//struct xypt{double x, y, phi, phidot, t;};

//typedef std::vector<xypt> Coords;
//double pi = 3.14;

class inga {
private:
    double phi0, L, m, k; //m, k, L negatív, akkor hiba
    const double g = 9.81;
public:
    const double pi = 3.14;
    //static constexpr double pi = 3.14;
    // Inicializálás
    inga (double phi0 = 0.2, double L = 1, double m = 2, double k = 0.4) {
        if (L < 0) {throw std::domain_error("Az inga h, ssza (L) csak nemnegativ lehet!");}
        if (m <= 0) {throw std::domain_error("Az inga tömege (m) csak pozitiv lehet!");}
        if (k < 0) {throw std::domain_error("Az inga kozegellenallasi tenyezoje (k) csak nemnegativ lehet!");}
        this->phi0 = phi0*pi/180; this->L = L; this->m = m; this->k =k;
    }
    //Ctor
    inga (inga &other) {
        phi0 = other.phi0; L = other.L; m = other.m; k = other.k;
    }
    const inga & operator=(const inga &inga) {
        phi0 = inga.phi0; L = inga.L; m = inga.m; k = inga.k;
        return *this;
    }
    //Getterek
    double getPhi0() const {return phi0;}
    double getL() const {return L;}
    double getM() const {return m;}
    double getK() const {return k;}
    //Setterek
    void setPhi0(double phi0) {this->phi0 = phi0;}
    void setL(double L) {this->L = L;}
    void setM(double m) {this->m = m;}
    void setK(double k) {this->k = k;}
    //Operátorok
    friend std::istream& operator>>(std::istream &is, inga &inga1) {
        double phi0,L,m,k;
        std::cout<<"\n| - Beolvasas - | \n";
        std::cout<<"\n  Phi(0) = "; is >> phi0;
        std::cout<<"\n  L = "; is >> L;
        std::cout<<"\n  m = "; is >> m;
        std::cout<<"\n  k = "; is >> k;
        std::cout<<"\n| - - - - - - - |\n\n";
        if (L < 0) {throw std::domain_error("Az inga hossza (L) csak nemnegativ lehet!");}
        if (m <= 0) {throw std::domain_error("Az inga tömege (m) csak pozitiv lehet!");}
        if (k < 0) {throw std::domain_error("Az inga kozegellenallasi tenyezoje (k) csak nemnegativ lehet!");}
        inga1.setPhi0(phi0*3.14/180); inga1.setL(L); inga1.setM(m); inga1.setK(k);
        return is;
    }
    friend std::ostream& operator<<(std::ostream &os, const inga &inga1) {
        os << "\n| - Adatok - |\n";
        os << "\n   Phi(0) = " << inga1.getPhi0() << " (rad) \n";
        os << "\n   L = " << inga1.getL() << " (m) \n";
        os << "\n   m = " << inga1.getM() << " (kg) \n";
        os << "\n   k = " << inga1.getK() << " (N*s/m) \n";
        os << "\n| - - -- - - |\n\n";
        return os;
    }
    //Tagfüggvények
    double iteracio(xypt &c0, double dt); // erőtörvény iterációja
    void refine_dt(const xypt c0, double &dt); // dt finomítása, megfelelő időpont keresése
    Coords ujcoords(double T); //
    void konvert(std::string file, int sorszam);
};

#endif // INGA_H_INCLUDED
