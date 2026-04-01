#pragma once
#include "Electrocasnic.h"
#include <iostream>

class Frigider : public Electrocasnic
{
    bool ac; // are congelator(0-nu ,1 - DA)

public:
    Frigider(string MARCA, string MODEL, int AN_FABRICATIE, double PRET_CATALOG, bool AC)
        : Electrocasnic("frigider", MARCA, MODEL, AN_FABRICATIE, PRET_CATALOG),
          ac(AC) {}

    void afisare() const override
    {
        cout << "Frigider " << marca << " " << model;
        cout << " (" << an_fabricatie << ") - Pret: " << pret_catalog;
        if (ac == 1)
            cout << " - Congelator: " << ac << endl;
    }
};
