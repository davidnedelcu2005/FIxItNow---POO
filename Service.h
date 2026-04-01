#pragma once
#include "Angajat.h"
#include <vector>
#include "Electrocasnic.h"
#include "Receptioner.h"
#include "Tehnician.h"
#include "Cerere.h"
#include <map>
#include <queue>
using namespace std;

class Service
{
    vector<Angajat *> Angajati;
    vector<Tehnician *> Tehnicieni;

    vector<Electrocasnic *> Modele_reparabile;
    map<pair<string, string>, int> Modele_nereparabile;

    queue<Cerere *> cereri_asteptare;

public:
    void adauga_angajat(Angajat *nou);
    void stergere_angajat(string c);
    void schimbare_nume_angajat(string c, string nume_nou, string prenume_nou);
    Angajat *gaseste_angajat(string c);
    void afisare_angajati() const;

    void adauga_model(Electrocasnic *e);
    void sterge_model(string MARCA, string MODEL);
    void afiseaza_reparabile() const;
    void inregistreaza_nereparabil(string MARCA, string MODEL);
    void afiseaza_nereparabile() const;

    void proceseaza_cereri_receptioner(Receptioner *r);

    void adauga_tehnician(Tehnician *t);
    void afiseaza_tehnicieni() const;

    void timp();

    void incarca_angajati(const string &fisier);
    void incarca_cereri(const string &fisier, Receptioner *r);

    Electrocasnic *gaseste_model(const string &marca, const string &model);
    Receptioner *get_receptioner();

    void top3_salarii(const string &fisier);
    void durata_max_tehnician(const string &fisier);

    ~Service();
};