#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "../data/elev.h"

std::vector<Elev> incarcaCatalog(const std::string& nume_fisier) {
    std::vector<Elev> elevi;
    std::ifstream fin(nume_fisier);

    if (!fin) {
        std::cerr << "Eroare la deschiderea fisierului: " << nume_fisier << "\n";
        return elevi;
    }

    // Verificăm dacă fișierul este gol
    fin.peek(); // Testăm primul caracter
    if (fin.eof()) {
        return elevi;  // Fișierul e gol -> returnăm lista goală
    }

    size_t nr;
    fin >> nr;
    for (size_t i = 0; i < nr; ++i) {
        Elev e;
        fin >> e;
        elevi.push_back(e);
    }

    return elevi;
}


void salveazaCatalog(const std::string& nume_fisier, const std::vector<Elev>& elevi) {
    std::ofstream fout(nume_fisier);
    if (!fout) {
        std::cerr << "Eroare la scrierea fisierului: " << nume_fisier << "\n";
        return;
    }
    fout << elevi.size() << "\n";
    for (const auto& e : elevi) {
        fout << e << "\n";
    }
}