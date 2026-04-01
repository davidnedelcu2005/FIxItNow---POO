#pragma once
#include "Electrocasnic.h"
#include <iostream>

class Televizor : public Electrocasnic
{
    int diagonala; // cm
public:
    Televizor(string MARCA, string MODEL, int AN_FABRICATIE, double PRET_CATALOG, int DIAGONALA)
        : Electrocasnic("tv", MARCA, MODEL, AN_FABRICATIE, PRET_CATALOG),
          diagonala(DIAGONALA) {}

    void afisare() const override
    {
        cout << "TV " << marca << " " << model << " - Diagonala: " << diagonala << " cm";
        cout << endl;
    }
};
