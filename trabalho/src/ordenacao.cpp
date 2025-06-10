#include "registro.hpp"
#include <fstream>
#include <cstring>

using namespace std;

const int TAMANHO = 1000; // número de registros por bloco para ordenação interna

// Função para comparar dois registros pelo campo id para ordenação crescente (ou decrescente)
// Altere conforme sua necessidade para ordenar por outro campo ou ordem decrescente
bool registroMenor(const Registro& a, const Registro& b) {
    return a.id < b.id;
}

// Ordenação interna simples por seleção para vetor fixo (TAMANHO)
void ordenaBuffer(Registro buffer[], int n) {
    for(int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for(int j = i + 1; j < n; j++) {
            if(registroMenor(buffer[j], buffer[minIndex])) {
                minIndex = j;
            }
        }
        if(minIndex != i) {
            Registro temp = buffer[i];
            buffer[i] = buffer[minIndex];
            buffer[minIndex] = temp;
        }
    }
}

void ordenarExterno(const string& arquivoEntrada, const string& arquivoSaida) {
    ifstream in(arquivoEntrada, ios::binary);
    if(!in) return;

    // Passo 1: Ler blocos do arquivo original, ordenar em memória e salvar em arquivos temporários
    Registro buffer[TAMANHO];
    int bloco = 0;

    while(true) {
        int lidos = 0;
        for(; lidos < TAMANHO && in.read((char*)&buffer[lidos], sizeof(Registro)); lidos++);

        if(lidos == 0) break; // fim do arquivo

        ordenaBuffer(buffer, lidos);

        // Salva bloco ordenado em arquivo temporário
        char tempFileName[20];
        sprintf(tempFileName, "temp_bloco_%d.dat", bloco);
        ofstream outTemp(tempFileName, ios::binary);
        for(int i = 0; i < lidos; i++) {
            outTemp.write((char*)&buffer[i], sizeof(Registro));
        }
        outTemp.close();
        bloco++;
    }
    in.close();

    if(bloco == 0) return; // arquivo vazio

    // Passo 2: Intercalação dos arquivos temporários para o arquivo final

    // Abre todos os arquivos temporários para leitura
    ifstream* arquivosTemp = new ifstream[bloco];
    for(int i = 0; i < bloco; i++) {
        char tempFileName[20];
        sprintf(tempFileName, "temp_bloco_%d.dat", i);
        arquivosTemp[i].open(tempFileName, ios::binary);
    }

    ofstream out(arquivoSaida, ios::binary);

    // Lê o primeiro registro de cada arquivo temporário
    Registro* cabecalho = new Registro[bloco];
    bool* arquivosAtivos = new bool[bloco];
    for(int i = 0; i < bloco; i++) {
        if(arquivosTemp[i].read((char*)&cabecalho[i], sizeof(Registro))) {
            arquivosAtivos[i] = true;
        } else {
            arquivosAtivos[i] = false;
        }
    }

    while(true) {
        // Encontra o menor registro entre os arquivos ativos
        int indiceMenor = -1;
        for(int i = 0; i < bloco; i++) {
            if(arquivosAtivos[i]) {
                if(indiceMenor == -1 || registroMenor(cabecalho[i], cabecalho[indiceMenor])) {
                    indiceMenor = i;
                }
            }
        }
        if(indiceMenor == -1) break; // nenhum arquivo ativo

        // Escreve o menor registro no arquivo de saída
        out.write((char*)&cabecalho[indiceMenor], sizeof(Registro));

        // Lê o próximo registro do arquivo temporário que forneceu o menor
        if(!arquivosTemp[indiceMenor].read((char*)&cabecalho[indiceMenor], sizeof(Registro))) {
            arquivosAtivos[indiceMenor] = false;
            arquivosTemp[indiceMenor].close();
            // Apaga o arquivo temporário
            char tempFileName[20];
            sprintf(tempFileName, "temp_bloco_%d.dat", indiceMenor);
            remove(tempFileName);
        }
    }

    delete[] cabecalho;
    delete[] arquivosAtivos;
    delete[] arquivosTemp;
    out.close();
}
