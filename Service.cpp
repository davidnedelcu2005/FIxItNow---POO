#include "Service.h"
#include "Supervizor.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

void Service::adauga_angajat(Angajat *nou)
{
    Angajati.push_back(nou);
}

void Service::stergere_angajat(string c)
{
    for (auto i = Angajati.begin(); i != Angajati.end(); ++i)
    {
        if ((*i)->get_cnp() == c)
        {
            delete *i;
            Angajati.erase(i);
            break;
        }
    }
}

void Service::schimbare_nume_angajat(string c, string nume_nou, string prenume_nou)
{
    for (auto a : Angajati)
    {
        if (a->get_cnp() == c)
        {
            a->set_nume(nume_nou, prenume_nou);
            break;
        }
    }
}

Angajat *Service::gaseste_angajat(string c)
{
    for (auto a : Angajati)
    {
        if (a->get_cnp() == c)
            return a;
    }
    return nullptr;
}

void Service::afisare_angajati() const
{

    for (auto a : Angajati)
        cout << *a << endl;
}

void Service::adauga_model(Electrocasnic *e)
{
    Modele_reparabile.push_back(e);
}

void Service::sterge_model(string MARCA, string MODEL)
{
    for (auto r = Modele_reparabile.begin(); r != Modele_reparabile.end(); ++r)
    {
        if ((*r)->getMarca() == MARCA && (*r)->getModel() == MODEL)
        {
            delete *r;
            Modele_reparabile.erase(r);
            break;
        }
    }
}
void Service::afiseaza_reparabile() const
{
    cout << "Aparate reparabile in service:" << endl;
    for (auto e : Modele_reparabile)
    {
        e->afisare();
    }
}

void Service::inregistreaza_nereparabil(string MARCA, string MODEL)
{
    Modele_nereparabile[{MARCA, MODEL}]++;
}

void Service::afiseaza_nereparabile() const
{
    cout << endl;
    cout << "Aparate nereparabile :" << endl;

    vector<pair<pair<string, string>, int>> temp;
    for (const auto &i : Modele_nereparabile)
    {
        temp.push_back(i);
    }

    sort(temp.begin(), temp.end(), [](const auto &a, const auto &b)
         { return a.second > b.second; });

    for (const auto &x : temp)
    {
        string MARCA = x.first.first;
        string MODEL = x.first.second;
        int aparitii = x.second;

        cout << "Marca: " << MARCA << ", Model: " << MODEL
             << " -> Numarul de aparitii: " << aparitii << endl;
    }
}
void Service::proceseaza_cereri_receptioner(Receptioner *r)
{
    for (auto c : r->getCereri())
    {
        Electrocasnic *gasit = nullptr;
        for (auto e : Modele_reparabile)
            if (e->getMarca() == c->getMarca() && e->getModel() == c->getModel())
                gasit = e;

        if (!gasit)
        {
            inregistreaza_nereparabil(c->getMarca(), c->getModel());
            continue;
        }

        Tehnician *ales = nullptr;
        for (auto a : Angajati)
        {
            auto t = dynamic_cast<Tehnician *>(a);
            if (t && t->poate_repara(gasit) && t->disponibil())
            {
                if (!ales || t->durata_totala() < ales->durata_totala())
                    ales = t;
            }
        }

        if (ales)
        {
            ales->adauga_cerere(c);
            time_t t = c->getTimestamp();
            /* cereri_active.push_back(c);*/
            cout << "ATRIBUIT   Cererea " << c->getId();
            cout << " i-a fost distribuita lui " << ales->get_nume() << " si a fost   creata la " << ctime(&t) << endl;
        }
        else
        {
            cereri_asteptare.push(c);
        }
    }
}

void Service::adauga_tehnician(Tehnician *t)
{
    Tehnicieni.push_back(t);
}

void Service::afiseaza_tehnicieni() const
{
    cout << endl;
    cout << "Tehnicieni service:" << endl;
    for (auto t : Tehnicieni)
        cout << *t << endl;
}

Service::~Service()
{
    for (auto a : Angajati)
        delete a;
    for (auto e : Modele_reparabile)
        delete e;
}

void Service::timp()
{
    static int timp = 0;
    timp++;
    cout << endl;
    cout << "[Timp " << timp << "]" << endl;

    for (auto a : Angajati)
    {
        auto t = dynamic_cast<Tehnician *>(a);
        if (t)
            t->rezolva();
    }
}

Electrocasnic *Service::gaseste_model(const string &marca, const string &model)
{
    for (auto e : Modele_reparabile)
    {
        if (e->getMarca() == marca && e->getModel() == model)
            return e;
    }
    return nullptr;
}

Receptioner *Service::get_receptioner()
{
    for (auto a : Angajati)
    {
        Receptioner *r = dynamic_cast<Receptioner *>(a);
        if (r)
            return r;
    }
    cout << "Nu exista niciun recepționer valid!\n";
    return nullptr;
}

void Service::incarca_angajati(const string &fisier)
{
    ifstream f(fisier);
    string linie;
    int linia_curenta = 0;

    while (getline(f, linie))
    {
        linia_curenta++;
        if (linie.empty())
            continue;

        try
        {
            string tip, nume, prenume, cnp, oras;
            int an;
            char sep = ',';
            stringstream ss(linie);

            getline(ss, tip, sep);
            getline(ss, nume, sep);
            getline(ss, prenume, sep);
            getline(ss, cnp, sep);
            getline(ss, oras, sep);
            ss >> an;

            if (tip == "Tehnician")
            {
                Tehnician *t = new Tehnician(nume, prenume, cnp, oras, an);

                t->add_set("frigider", "NeoFrost");
                t->add_set("masina_de_spalat", "VIVAX");
                t->add_set("tv", "Samsung");
                t->add_set("tv", "LG");

                adauga_angajat(t);
                adauga_tehnician(t);
            }
            else if (tip == "Receptioner")
            {
                Receptioner *r = new Receptioner(nume, prenume, cnp, oras, an);
                adauga_angajat(r);
            }
            else if (tip == "Supervizor")
            {
                Supervizor *s = new Supervizor(nume, prenume, cnp, oras, an);
                adauga_angajat(s);
            }
        }
        catch (const std::exception &e)
        {
            cout << "Eroare la linia " << linia_curenta
                 << ": " << e.what() << endl;
            continue;
        }
    }
}

void Service::incarca_cereri(const string &fisier, Receptioner *r)
{
    ifstream f(fisier);
    string linie;
    int linie_nr = 0;

    while (getline(f, linie))
    {
        linie_nr++;
        if (linie.empty())
            continue;

        string marca, model;
        int complexitate;
        char sep = ',';
        stringstream ss(linie);

        getline(ss, marca, sep);
        getline(ss, model, sep);
        ss >> complexitate;

        Electrocasnic *e = gaseste_model(marca, model);
        if (!e)
        {
            inregistreaza_nereparabil(marca, model);
            cout << "Eroare la linia " << linie_nr;
            cout << ": modelul " << marca << " " << model;
            cout << " nu exista in service." << endl;
            continue;
        }

        Cerere *c = new Cerere(marca, model, e, complexitate);
        r->cerere(c);
    }
}

void Service::top3_salarii(const string &fisier)
{

    Angajat *max1 = nullptr;
    Angajat *max2 = nullptr;
    Angajat *max3 = nullptr;

    for (auto a : Angajati)
    {
        if (!max1 || a->salariu() > max1->salariu())
        {
            max3 = max2;
            max2 = max1;
            max1 = a;
        }
        else if (!max2 || a->salariu() > max2->salariu())
        {
            max3 = max2;
            max2 = a;
        }
        else if (!max3 || a->salariu() > max3->salariu())
        {
            max3 = a;
        }
    }

    ofstream out(fisier);

    out << max1->get_nume() << "," << max1->salariu() << "\n";
    out << max2->get_nume() << "," << max2->salariu() << "\n";
    out << max3->get_nume() << "," << max3->salariu() << "\n";
}

void Service::durata_max_tehnician(const string &fisier)
{
    int maxi = 0;
    Tehnician *maxt = Tehnicieni[0];
    for (int i = 0; i < Tehnicieni.size(); i++)
    {
        if (Tehnicieni[i]->durata_totala() > maxt->durata_totala())
            maxt = Tehnicieni[i];
    }

    ofstream out(fisier);
    out << maxt->get_nume() << endl;
}
