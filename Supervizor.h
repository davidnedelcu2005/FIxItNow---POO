#pragma once
#include "Angajat.h"

class Supervizor : public Angajat
{

public:
    Supervizor(string p, string n, string c, string o, int an);
    double salariu() const override;
};