#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "../shared/data/elev.h"

// Funcția aceasta este definită în alt fișier sursă (../shared/files/catalog_manager.cpp)
extern std::vector<Elev> incarcaCatalog(const std::string&);
extern void salveazaCatalog(const std::string&, const std::vector<Elev>&);

// Funcție pentru afișarea sintaxei
void printSintaxa() {
    std::cout << "Comenzi disponibile:\n";
    std::cout << "./app2.exe adauga_elev <nume>\n";
    std::cout << "./app2.exe sterge_elev <nume>\n";
    std::cout << "./app2.exe motiveaza_absenta <nume_elev> <materie> <data>\n";
    std::cout << "./app2.exe afiseaza_elevi\n";
    std::cout << "./app2.exe afiseaza_note <nume_elev>\n";
    std::cout << "./app2.exe afiseaza_absente <nume_elev>\n";
}

std::string getNumeFromArgs(int argc, char* argv[], int start = 2) {
    std::string nume = argv[start];
    for (int i = start + 1; i < argc; ++i) {
        nume += " ";
        nume += argv[i];
    }
    return nume;
}

int main(int argc, char* argv[]) {

    const std::string catalog_path = "shared/files/catalog.txt";
    auto elevi = incarcaCatalog(catalog_path);

    // Dacă rulăm file-ul fără argumente ne arată sintaxa
    if (argc < 2) {
        printSintaxa();
        return 1;
    }

    // Gestionăm interacțiunea bazat pe argumentul dat
    std::string comanda = argv[1];
    if (comanda == "adauga_elev") {
        if (argc < 3) {
            std::cout << "Sintaxa invalida! ./app2.exe adauga_elev <nume>\n";
            return 1;
        }
        std::string nume = getNumeFromArgs(argc, argv);
        if (std::none_of(elevi.begin(), elevi.end(), [&](const Elev& e){ return e.nume == nume; })) {
            elevi.push_back(Elev(nume));
            salveazaCatalog(catalog_path, elevi);
            std::cout << "Elev adăugat cu succes!\n";
        } else {
            std::cout << "Elevul exista deja.\n";
        }

    } else if (comanda == "sterge_elev") {
        if (argc < 3) {
            std::cout << "Sintaxa invalida! ./app2.exe sterge_elev <nume>\n";
            return 1;
        }
        std::string nume = getNumeFromArgs(argc, argv);
        auto it = std::remove_if(elevi.begin(), elevi.end(), [&](const Elev& e) { return e.nume == nume; });
        if (it != elevi.end()) {
            elevi.erase(it, elevi.end());
            salveazaCatalog(catalog_path, elevi);
            std::cout << "Elev sters cu succes!\n";
        } else {
            std::cout << "Elevul nu a fost gasit.\n";
        }

    } else if (comanda == "motiveaza_absenta") {
        if (argc != 5) {
            std::cout << "Sintaxa invalida! ./app2.exe motiveaza_absenta <nume_elev> <materie> <data>\n";
            return 1;
        }
        std::string nume = argv[2];
        std::string materie = argv[3];
        std::string data = argv[4];

        auto it = std::find_if(elevi.begin(), elevi.end(), [&](const Elev& e) {
            return e.nume == nume;
        });

        if (it != elevi.end()) {
            bool found = false;
            for (auto& abs : it->absente) {
                if (abs.materie == materie && abs.data == data) {
                    abs.motivata = true;
                    found = true;
                    break;
                }
            }
            if (found) {
                salveazaCatalog(catalog_path, elevi);
                std::cout << "Absenta motivata cu succes!\n";
            } else {
                std::cout << "Absenta specificata nu a fost gasita.\n";
            }
        } else {
            std::cout << "Elevul nu a fost gasit.\n";
            }
    } else if (comanda == "afiseaza_elevi") {
        for (const auto& elev : elevi)
            std::cout << elev.nume << "\n";

    } else if (comanda == "afiseaza_note") {
        if (argc < 3) {
            std::cout << "Sintaxa invalida! ./app2.exe afiseaza_note <nume_elev>\n";
            return 1;
        }
        std::string nume = getNumeFromArgs(argc, argv);
        auto it = std::find_if(elevi.begin(), elevi.end(), [&](const Elev& e) { return e.nume == nume; });
        if (it != elevi.end()) {
            it->afiseazaNote();
        } else {
            std::cout << "Elevul nu a fost gasit.\n";
        }

    } else if (comanda == "afiseaza_absente") {
        if (argc < 3) {
            std::cout << "Sintaxa invalida! ./app2.exe afiseaza_absente <nume_elev>\n";
            return 1;
        }
        std::string nume = getNumeFromArgs(argc, argv);
        auto it = std::find_if(elevi.begin(), elevi.end(), [&](const Elev& e) { return e.nume == nume; });
        if (it != elevi.end()) {
            it->afiseazaAbsente();
        } else {
            std::cout << "Elevul nu a fost gasit.\n";
        }

    } else {
        std::cout << "Comandă necunoscuta.\n";
        printSintaxa();
    }

    return 0;
}
