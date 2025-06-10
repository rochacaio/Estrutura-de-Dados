#include "registro.hpp"
#include <iostream>
#include <cstring>

using namespace std;

// Declaração das funções (implementadas em outros arquivos)
void csvToBinary(const string&, const string&);
void inserirNaPosicao(const string&, const Registro&, int);
void visualizarEntre(const string&, int, int);
void alterarRegistro(const string&, int, const Registro&);
void trocarRegistros(const string&, int, int);
void imprimirTodos(const string&);
void ordenarExterno(const string&, const string&);

int main() {
    string csv = "data/data_athlete_event.csv";
    string bin = "data/binario.dat";
    string binOrdenado = "data/ordenado.dat";

    // Converte CSV para arquivo binário
    csvToBinary(csv, bin);

    // Imprime todos os registros do arquivo binário
    imprimirTodos(bin);

    // Cria um novo registro para testar inserção e alteração
    Registro novo;
    novo.id = 999;
    strcpy(novo.name, "Teste");
    strcpy(novo.city, "São Paulo");
    strcpy(novo.sport, "Futebol");
    strcpy(novo.event, "Campeonato Paulista");
    strcpy(novo.noc, "BRA");

    // Insere o novo registro na posição 1
    inserirNaPosicao(bin, novo, 1);

    // Visualiza registros entre posição 0 e 2
    visualizarEntre(bin, 0, 2);

    // Altera o registro na posição 0 com o novo registro
    alterarRegistro(bin, 0, novo);

    // Troca os registros das posições 0 e 1
    trocarRegistros(bin, 0, 1);

    // Ordena o arquivo binário e grava em um novo arquivo
    ordenarExterno(bin, binOrdenado);

    // Imprime todos os registros do arquivo binário ordenado
    imprimirTodos(binOrdenado);

    return 0;
}
