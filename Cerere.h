#pragma once
#include <string>
#include <ctime>
#include "Electrocasnic.h"

using namespace std;

class Tehnician;

class Cerere
{
    static int cerere_id;

    int ID;
    string marca, model;
    Electrocasnic *aparat;
    time_t timestamp;

    int complexitate, timp_estimat, timp_ramas;
    double pret;

    Tehnician *tehnician;

public:
    Cerere(string m, string mod, Electrocasnic *e, int comp);

    int getId() const;
    string getMarca() const;
    string getModel() const;

    int get_timp_ramas() const;
    void proceseaza();
    void timp() { proceseaza(); }

    bool finalizata() const;
    time_t getTimestamp() const
    {
        return timestamp;
    }

    double get_pret() const;
    void set_tehnician(Tehnician *t);
    Tehnician *get_tehnician() const;
};
