#pragma once
#include "Angajat.h"
#include "Electrocasnic.h"
#include "Cerere.h"
#include <vector>
#include <utility>
using namespace std;

class Tehnician : public Angajat
{
    vector<pair<string, string>> seturi;
    vector<Cerere *> cereri_active;
    vector<Cerere *> cereri_finalizate;
    double cost_reparatii = 0;

public:
    Tehnician(string p, string n, string c, string o, int an);
    void add_set(string tip, string marca);
    void pret_reparatie(double val);
    bool poate_repara(const Electrocasnic *e) const;
    double salariu() const override;

    bool disponibil() const;
    int durata_totala() const;
    void adauga_cerere(Cerere *c);
    void rezolva();
};