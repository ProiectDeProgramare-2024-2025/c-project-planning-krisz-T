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
    std::cout << "./app1.exe adauga_nota <nume_elev> <materie> <nota>\n";
    std::cout << "./app1.exe sterge_nota <nume_elev> <materie> <index>\n";
    std::cout << "./app1.exe adauga_absenta <nume_elev> <materie> <data>\n";
    std::cout << "./app1.exe sterge_absenta <nume_elev> <materie> <data>\n";
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
    if (comanda == "adauga_nota") {
        if (argc != 5) {
            std::cout << "Sintaxa invalida! Sintaxa corecta: ./app1.exe adauga_nota <nume_elev> <materie> <nota>\n";
            return 1;
        }
        std::string nume = argv[2];
        std::string materie = argv[3];
        int valoare = std::stoi(argv[4]);

        auto it = std::find_if(elevi.begin(), elevi.end(), [&](const Elev& e) {
            return e.nume == nume;
        });

        if (it != elevi.end()) {
            it->adaugaNota(Nota(materie, valoare));
            salveazaCatalog(catalog_path, elevi);
            std::cout << "Nota adaugata cu succes!\n";
        } else {
            std::cout << "Elevul nu a fost gasit.\n";
        }
    } else if (comanda == "sterge_nota") {
        if (argc != 5) {
            std::cout << "Sintaxa invalida! Sintaxa corecta: ./app1.exe sterge_nota <nume_elev> <materie> <index>\n";
            return 1;
        }
        std::string nume = argv[2];
        std::string materie = argv[3];
        int index = std::stoi(argv[4]);

        auto it = std::find_if(elevi.begin(), elevi.end(), [&](const Elev& e) {
            return e.nume == nume;
        });

        if (it != elevi.end()) {
            auto& note = it->note;
            int count = 0;
            for (auto iter = note.begin(); iter != note.end(); ++iter) {
                if (iter->materie == materie) {
                    if (count == index) {
                        note.erase(iter);
                        salveazaCatalog(catalog_path, elevi);
                        std::cout << "Nota stearsa cu succes!\n";
                        return 0;
                    }
                    ++count;
                }
            }
            std::cout << "Index invalid pentru materia specificata.\n";
        } else {
            std::cout << "Elevul nu a fost gasit.\n";
        }
    } else if (comanda == "adauga_absenta") {
        if (argc != 5) {
            std::cout << "Sintaxa invalida! Sintaxa corecta: ./app1.exe adauga_absenta <nume_elev> <materie> <data>\n";
            return 1;
        }
        std::string nume = argv[2];
        std::string materie = argv[3];
        std::string data = argv[4];

        auto it = std::find_if(elevi.begin(), elevi.end(), [&](const Elev& e) {
            return e.nume == nume;
        });

        if (it != elevi.end()) {
            it->adaugaAbsenta(Absenta(materie, data));
            salveazaCatalog(catalog_path, elevi);
            std::cout << "Absenta adaugata cu succes!\n";
        } else {
            std::cout << "Elevul nu a fost gasit.\n";
        }
    } else if (comanda == "sterge_absenta") {
        if (argc != 5) {
            std::cout << "Sintaxa invalida! Sintaxa corecta: ./app1.exe sterge_absenta <nume_elev> <materie> <data>\n";
            return 1;
        }
        std::string nume = argv[2];
        std::string materie = argv[3];
        std::string data = argv[4];

        auto it = std::find_if(elevi.begin(), elevi.end(), [&](const Elev& e) {
            return e.nume == nume;
        });

        if (it != elevi.end()) {
            auto& absente = it->absente;
            auto abs_it = std::find_if(absente.begin(), absente.end(), [&](const Absenta& a) {
                return a.materie == materie && a.data == data;
            });

            if (abs_it != absente.end()) {
                absente.erase(abs_it);
                salveazaCatalog(catalog_path, elevi);
                std::cout << "Absenta stearsa cu succes!\n";
            } else {
                std::cout << "Absenta nu a fost gasita.\n";
            }
        } else {
            std::cout << "Elevul nu a fost gasit.\n";
        }
    } else {
        std::cout << "Comanda necunoscuta.\n";
        printSintaxa();
    }

    return 0;
}
