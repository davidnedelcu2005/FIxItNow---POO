#include "Receptioner.h"
#include "Tehnician.h"
#include "Supervizor.h"
#include "Service.h"
#include "Frigider.h"
#include "Televizor.h"
#include "Masina_de_Spalat.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int main()
{
    Service S;

    S.incarca_angajati("tests/angajati_valizi.csv");
    S.incarca_angajati("tests/angajati_invalizi.csv");

    S.adauga_model(new Frigider("NeoFrost", "Pro", 2020, 2500, true));
    S.adauga_model(new Masina_de_Spalat("VIVAX", "WFL", 2019, 1800, 7));
    S.adauga_model(new Televizor("Samsung", "UltraHD", 2021, 3200, 55));
    S.adauga_model(new Televizor("LG", "SmartTV", 2022, 2800, 50));

    Receptioner *r = S.get_receptioner();
    if (!r)
    {
        cout << "Nu exista niciun recepționer valid!" << endl;
        return 1;
    }

    S.incarca_cereri("tests/cereri_valide.csv", r);
    S.incarca_cereri("tests/cereri_invalide.csv", r);

    for (auto c : r->getCereri())
        cout << "Cerere incarcata: " << c->getMarca() << " " << c->getModel() << "\n";

    S.proceseaza_cereri_receptioner(r);

    for (int i = 0; i < 15; i++)
    {
        S.timp();
        std::this_thread::sleep_for(std::chrono::milliseconds(700));
    }
    cout << endl;
    cout << "Lista angajatilor " << endl;
    S.afisare_angajati();

    cout << endl;
    cout << " Lista tehnicienilor " << endl;
    S.afiseaza_tehnicieni();

    cout << " Adaugam un tehnician " << endl;

    Tehnician *t_nou = new Tehnician(
        "Radu",
        "Stefan",
        "5050704170029",
        "Bucuresti",
        2017);

    t_nou->add_set("tv", "Samsung");
    t_nou->add_set("frigider", "LG");

    S.adauga_angajat(t_nou);
    S.adauga_tehnician(t_nou);

    S.top3_salarii("top_salarii.csv");
    S.durata_max_tehnician("tehnican_duarata_max.csv");

    cout << endl;
    cout << "Stergem angajatul Nedelcu David" << endl;
    S.stergere_angajat("1800101123450");

    cout << endl;
    cout << " Lista angajatilor (dupa ce l am sters pe David Nedelcu ) " << endl;
    S.afisare_angajati();

    S.afiseaza_reparabile();
    S.afiseaza_nereparabile();
}