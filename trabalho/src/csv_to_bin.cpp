// csv_to_bin.cpp
#include "registro.hpp"
#include <fstream>
#include <string>

using namespace std;

void csvToBinary(const string& csvFile, const string& binFile) {
    ifstream in(csvFile); // arquivo CSV em modo texto
    ofstream out(binFile, ios::binary); // arquivo binário em modo binário

    if (!in.is_open() || !out.is_open()) {
        cout << "Erro ao abrir arquivos.\n";
        return;
    }

    string line;
    getline(in, line); // pular cabeçalho

    Registro reg;
    while (getline(in, line)) {
        reg.fromCSVLine(line);
        out.write((char*)&reg, sizeof(Registro));
    }

    in.close();
    out.close();
}
