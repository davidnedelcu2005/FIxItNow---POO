/*#include "Receptioner.h"

Receptioner::Receptioner(string p, string n, string c, string o, int an) : Angajat(p, n, c, o, an) {}

void Receptioner::cerere(string MARCA, string MODEL)
{
    cereri.push_back({MARCA, MODEL});
}

double Receptioner::salariu() const
{
    const double salariu_baza = 4000;
    double bonus_loialitate = ((2025 - an_angajare) / 3) * (0.05 * 4000);
    double bonus_transport = 0;
    if (oras != "Bucuresti")
        bonus_transport = 400;

    return salariu_baza + bonus_loialitate + bonus_transport;
}*/
#include "Receptioner.h"

Receptioner::Receptioner(string p, string n, string c, string o, int an)
    : Angajat(p, n, c, o, an) {}

void Receptioner::cerere(Cerere *c)
{
    cereri.push_back(c);
}

const vector<Cerere *> &Receptioner::getCereri() const
{
    return cereri;
}

double Receptioner::salariu() const
{
    const double salariu_baza = 4000;
    double bonus_loialitate = ((2025 - an_angajare) / 3) * (0.05 * 4000);
    double bonus_transport = 0;
    if (oras != "Bucuresti")
        bonus_transport = 400;

    return salariu_baza + bonus_loialitate + bonus_transport;
}

Receptioner::~Receptioner() = default;
