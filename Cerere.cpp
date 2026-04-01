#include "Cerere.h"
#include <ctime>

int Cerere::cerere_id = 1;

Cerere::Cerere(string m, string mod, Electrocasnic *e, int comp)
    : marca(m), model(mod), aparat(e), complexitate(comp), tehnician(nullptr)
{
    ID = cerere_id++;
    timestamp = time(nullptr);

    if (aparat == nullptr)
    {
        timp_estimat = 0;
        timp_ramas = 0;
        pret = 0;
    }
    else
    {
        int vechime = 2025 - aparat->getAn();
        timp_estimat = vechime * complexitate;
        timp_ramas = timp_estimat;
        pret = aparat->get_pret() * timp_estimat;
    }
}

int Cerere::getId() const { return ID; }
string Cerere::getMarca() const { return marca; }
string Cerere::getModel() const { return model; }

int Cerere::get_timp_ramas() const { return timp_ramas; }

void Cerere::proceseaza()
{
    if (timp_ramas > 0)
        timp_ramas--;
}

bool Cerere::finalizata() const
{
    return timp_ramas == 0;
}

double Cerere::get_pret() const { return pret; }

void Cerere::set_tehnician(Tehnician *t)
{
    tehnician = t;
}

Tehnician *Cerere::get_tehnician() const
{
    return tehnician;
}
