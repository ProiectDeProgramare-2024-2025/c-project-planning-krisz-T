#include "nota.h"

Nota::Nota(std::string materie, int valoare) : materie(materie), valoare(valoare) {}

std::ostream& operator<<(std::ostream& out, const Nota& n) {
    out << n.materie << " " << n.valoare;
    return out;
}

std::istream& operator>>(std::istream& in, Nota& n) {
    in >> n.materie >> n.valoare;
    return in;
}
