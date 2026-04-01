#include "Angajat.h"
#include <stdexcept>

int Angajat::nr_angajati = 1;

Angajat::Angajat(string p, string n, string c, string o, int an) : oras(o), an_angajare(an)
{

    set_nume(n, p);
    set_cnp(c);
    int varsta = extrage_an_cnp(c);
    if (2025 - varsta < 16)
        throw invalid_argument("Angajat prea tanar");
    id = nr_angajati++;
}

void Angajat::set_nume(string n, string p)
{
    if (n.size() < 3 || n.size() > 30 || p.size() < 3 || p.size() > 30)
        throw invalid_argument("Nume invalid");
    nume = n;
    prenume = p;
}

void Angajat::set_cnp(string c)
{
    if (c.size() != 13)
        throw invalid_argument("Cnp invalid");
    string constanta = "279146358279";
    int suma = 0;
    for (int i = 0; i < 12; i++)
        suma = suma + (c[i] - '0') * (constanta[i] - '0');
    int rest = suma % 11;
    if (rest != (c[12] - '0'))
        throw invalid_argument("Cnp invalid");
    cnp = c;
}

int Angajat::extrage_an_cnp(string c)
{
    int n = cnp[0] - '0';
    int year = (cnp[1] - '0') * 10 + (cnp[2] - '0');

    if (n == 1 || n == 2)
        return 1900 + year;
    if (n == 5 || n == 6)
        return 2000 + year;
    return 1800 + year;
}

ostream &operator<<(ostream &out, const Angajat &nou)
{
    out << "ID: " << nou.id << endl;
    out << nou.nume << " " << nou.prenume << endl;
    out << "CNP: " << nou.cnp << endl;
    out << "Angajat in service din: " << nou.an_angajare << endl;
    out << "Oras: " << nou.oras << endl;
    out << "Salariu: " << nou.salariu() << endl;
    return out;
}