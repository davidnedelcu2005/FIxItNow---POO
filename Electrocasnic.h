#pragma once
#include <iostream>
#include <string>
using namespace std;

class Electrocasnic
{

protected:
    string tip, marca, model;
    int an_fabricatie;
    double pret_catalog;

public:
    Electrocasnic(string TIP, string MARCA, string MODEL,
                  int AN_FABRICATIE, double PRET_CATALOG)
        : tip(TIP), marca(MARCA), model(MODEL),
          an_fabricatie(AN_FABRICATIE), pret_catalog(PRET_CATALOG) {}

    virtual ~Electrocasnic() {}

    string getTip() const { return tip; }
    string getMarca() const { return marca; }
    string getModel() const { return model; }
    int getAn() const { return an_fabricatie; }
    double get_pret() const { return pret_catalog; }

    virtual void afisare() const = 0;
};