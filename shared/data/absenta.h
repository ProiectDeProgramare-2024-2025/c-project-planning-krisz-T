#pragma once
#include <string>
#include <iostream>

// Orice absență are o materie, data și faptul că este motivat sau nu - ex: Biologie, 2025-11-30, false
class Absenta {
public:
    std::string materie;
    std::string data;
    bool motivata;

    // Constructor
    Absenta(std::string materie = "", std::string data = "", bool motivata = false);

    // Supraîncărcarea operatoriilor
    friend std::ostream& operator<<(std::ostream& out, const Absenta& a);
    friend std::istream& operator>>(std::istream& in, Absenta& a);
};