#include "Tehnician.h"

Tehnician::Tehnician(string p, string n, string c, string o, int an) : Angajat(p, n, c, o, an) {}

void Tehnician::add_set(string tip, string marca)
{
    seturi.push_back({tip, marca});
}

void Tehnician::pret_reparatie(double val)
{
    cost_reparatii = cost_reparatii + val;
}

bool Tehnician::poate_repara(const Electrocasnic *e) const
{
    for (auto &s : seturi)
        if (s.first == e->getTip() && s.second == e->getMarca())
            return true;
    return false;
}

double Tehnician::salariu() const
{

    const double salariu_baza = 4000;
    double bonus_loialitate = ((2025 - an_angajare) / 3) * (0.05 * 4000);
    double bonus_transport = 0;
    if (oras != "Bucuresti")
        bonus_transport = 400;
    double bonus_reparatii = 0.02 * cost_reparatii;
    return salariu_baza + bonus_loialitate + bonus_transport + bonus_reparatii;
}

bool Tehnician::disponibil() const
{
    if (cereri_active.size() < 3)
        return 1;

    return 0;
}

int Tehnician::durata_totala() const
{
    int s = 0;
    for (auto c : cereri_active)
        s = s + c->get_timp_ramas();
    return s;
}

void Tehnician::adauga_cerere(Cerere *c)
{
    cereri_active.push_back(c);
    c->set_tehnician(this);
}

void Tehnician::rezolva()
{
    for (auto i = cereri_active.begin(); i != cereri_active.end();)
    {
        Cerere *c = *i;
        c->timp();

        if (c->get_timp_ramas() > 0)
        {
            cout << "   Tehnicianul  " << c->get_tehnician()->get_nume() << " ";
            cout << "rezolva cererea " << c->getId();
            cout << " (inca " << c->get_timp_ramas() << " unitati de timp)" << endl;
            ++i;
        }
        else
        {
            cout << "   Tehnicianul " << c->get_tehnician()->get_nume();
            cout << " a terminat cererea: " << c->getId() << endl;

            i = cereri_active.erase(i);
            cereri_finalizate.push_back(c);
        }
    }
}
