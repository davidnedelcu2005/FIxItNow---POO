/*#pragma once
#include "Angajat.h"
#include <vector>
using namespace std;

class Receptioner : public Angajat
{
    vector<pair<string, string>> cereri;

public:
    Receptioner(string p, string n, string c, string o, int an);
    void cerere(string MARCA, string MODEL);
    double salariu() const override;
    const vector<pair<string, string>> &getCereri() const
    {
        return cereri;
    }
};*/
#pragma once
#include "Angajat.h"
#include <vector>
#include "Cerere.h"

class Receptioner : public Angajat
{
    vector<Cerere *> cereri;

public:
    Receptioner(string p, string n, string c, string o, int an);
    void cerere(Cerere *c);
    ~Receptioner() override;
    const vector<Cerere *> &getCereri() const;
    double salariu() const override;
};
