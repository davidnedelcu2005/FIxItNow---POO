#pragma once
#include "Electrocasnic.h"
#include <iostream>

class Masina_de_Spalat : public Electrocasnic
{
    int capacitate;

public:
    Masina_de_Spalat(string MARCA, string MODEL, int AN_FABRICATIE, double PRET_CATALOG, int kg)
        : Electrocasnic("masina_de_spalat", MARCA, MODEL, AN_FABRICATIE, PRET_CATALOG),
          capacitate(kg) {}

    void afisare() const override
    {
        cout << "Masina de spalat " << marca << " " << model << " - Capacitate: " << capacitate << " kg";
        cout << endl;
    }
};
