#include "absenta.h"

Absenta::Absenta(std::string materie, std::string data, bool motivata)
    : materie(materie), data(data), motivata(motivata) {}

std::ostream& operator<<(std::ostream& out, const Absenta& a) {
    out << a.materie << " " << a.data << " " << (a.motivata ? 1 : 0);
    return out;
}

std::istream& operator>>(std::istream& in, Absenta& a) {
    int mot;
    in >> a.materie >> a.data >> mot;
    a.motivata = mot;
    return in;
}