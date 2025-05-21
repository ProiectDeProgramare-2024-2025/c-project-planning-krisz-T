#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "nota.h"
#include "absenta.h"

// FUNCȚIE TEMPLATE — GLOBALĂ
// Pentru a afișa note și absențe
template <typename T>
void afiseazaVector(const std::vector<T>& v) {
    for (const auto& elem : v) {
        std::cout << elem << "\n";
    }
}

// Orice elev are un nume, anumite note și absențe (Compoziție)
class Elev {
public:
    std::string nume;
    std::vector<Nota> note;
    std::vector<Absenta> absente;

    // Constructor
    Elev(std::string nume = "");

    // Funcții pentru a adăuga și șterge note și absențe
    void adaugaNota(const Nota& n);
    void adaugaAbsenta(const Absenta& a);
    void afiseazaNote() const;
    void afiseazaAbsente() const;

    //Supraîncărcarea operatorilor
    friend std::ostream& operator<<(std::ostream& out, const Elev& e);
    friend std::istream& operator>>(std::istream& in, Elev& e);

};
