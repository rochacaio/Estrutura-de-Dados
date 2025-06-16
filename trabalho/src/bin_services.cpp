#include "registro.hpp"
#include <fstream>

using namespace std;

void imprimirTodos(const string& binFile) {
    ifstream in(binFile, ios::binary);
    if (!in.is_open()) {
        cout << "Erro ao abrir o arquivo binário para leitura.\n";
        return;
    }

    Registro reg;
    while (in.read((char*)&reg, sizeof(Registro))) {
        reg.print();
    }

    in.close();
}

void inserirNaPosicao(const string& path, const Registro& r, int pos) {
    fstream file(path, ios::in | ios::out | ios::binary);
    file.seekp(pos * sizeof(Registro));
    file.write(reinterpret_cast<const char*>(&r), sizeof(Registro));
    file.close();
}

void visualizarEntre(const string& path, int x, int y) {
    ifstream file(path, ios::binary);
    Registro r;
    for (int i = x; i <= y; ++i) {
        file.seekg(i * sizeof(Registro));
        file.read(reinterpret_cast<char*>(&r), sizeof(Registro));
        r.print();
    }
    file.close();
}

void alterarRegistro(const string& path, int pos, const Registro& novo) {
    fstream file(path, ios::in | ios::out | ios::binary);
    file.seekp(pos * sizeof(Registro));
    file.write(reinterpret_cast<const char*>(&novo), sizeof(Registro));
    file.close();
}

void trocarRegistros(const string& path, int pos1, int pos2) {
    fstream file(path, ios::in | ios::out | ios::binary);
    Registro r1, r2;
    file.seekg(pos1 * sizeof(Registro));
    file.read(reinterpret_cast<char*>(&r1), sizeof(Registro));
    file.seekg(pos2 * sizeof(Registro));
    file.read(reinterpret_cast<char*>(&r2), sizeof(Registro));

    file.seekp(pos1 * sizeof(Registro));
    file.write(reinterpret_cast<const char*>(&r2), sizeof(Registro));
    file.seekp(pos2 * sizeof(Registro));
    file.write(reinterpret_cast<const char*>(&r1), sizeof(Registro));
    file.close();
}
