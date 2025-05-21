#pragma once
#include <string>
#include <iostream>

// Orice notă are o materie și o valoare - ex: Matematică, 10
class Nota {
public:
    std::string materie;
    int valoare;

    // Constructor
    Nota(std::string materie = "", int valoare = 0);

    // Supraîncărcarea operatorilor
    friend std::ostream& operator<<(std::ostream& out, const Nota& n);
    friend std::istream& operator>>(std::istream& in, Nota& n);
};
