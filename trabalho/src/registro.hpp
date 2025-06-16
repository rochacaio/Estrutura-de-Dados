#ifndef REGISTRO_HPP
#define REGISTRO_HPP

#include <iostream>

using namespace std;

struct Registro {
    int id;
    char name[255];
    char city[255];
    char sport[255];
    char event[255];
    char noc[255];

    void fromCSVLine(const string& line);
    void print() const;
    bool operator>(const Registro& other) const {
        return id > other.id;
    }
};

#endif
