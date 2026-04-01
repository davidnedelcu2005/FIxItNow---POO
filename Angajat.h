#pragma once
#include <iostream>
#include <string>
using namespace std;

class Angajat
{

protected:
    int id;
    string prenume, nume, cnp, oras;
    int an_angajare;
    static int nr_angajati;

public:
    Angajat(string p, string n, string c, string o, int an);
    virtual ~Angajat() { nr_angajati--; }

    int get_id() const { return id; }
    string get_cnp() const { return cnp; }
    string get_nume() const { return nume + " " + prenume; }

    virtual double salariu() const = 0;

    void set_nume(string n, string p);
    void set_cnp(string c);
    int extrage_an_cnp(string c);

    friend ostream &operator<<(ostream &out, const Angajat &nou);
};