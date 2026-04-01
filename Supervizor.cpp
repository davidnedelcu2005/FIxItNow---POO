#include "Supervizor.h"

Supervizor::Supervizor(string p, string n, string c, string o, int an) : Angajat(p, n, c, o, an) {}

double Supervizor::salariu() const
{
    const double salariu_baza = 4000;
    double bonus_loialitate = ((2025 - an_angajare) / 3) * (0.05 * 4000);
    double bonus_transport = 0;
    if (oras != "Bucuresti")
        bonus_transport = 400;

    double spor_conducere = 0.20 * 4000;

    return salariu_baza + bonus_loialitate + bonus_transport + spor_conducere;
}