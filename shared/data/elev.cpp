#include "elev.h"

Elev::Elev(std::string nume) : nume(nume) {}

void Elev::adaugaNota(const Nota& n) {
    note.push_back(n);
}

void Elev::adaugaAbsenta(const Absenta& a) {
    absente.push_back(a);
}

void Elev::afiseazaNote() const {
    afiseazaVector(note);
}

void Elev::afiseazaAbsente() const {
    afiseazaVector(absente);
}

std::ostream& operator<<(std::ostream& out, const Elev& e) {
    out << e.nume << "\n";
    out << e.note.size();
    for (const auto& n : e.note) out << " " << n;
    out << "\n" << e.absente.size();
    for (const auto& a : e.absente) out << " " << a;
    return out;
}

std::istream& operator>>(std::istream& in, Elev& e) {
    size_t nr_note, nr_absente;
    std::getline(in >> std::ws, e.nume);
    in >> nr_note;
    e.note.clear();
    for (size_t i = 0; i < nr_note; ++i) {
        Nota n;
        in >> n;
        e.note.push_back(n);
    }
    in >> nr_absente;
    e.absente.clear();
    for (size_t i = 0; i < nr_absente; ++i) {
        Absenta a;
        in >> a;
        e.absente.push_back(a);
    }
    return in;
}