#include "registro.hpp"
#include <fstream>
#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;

const int TAMANHO = 1000; // número de registros por bloco

struct noh {
    Registro reg;
    int origem;
};

// Quicksort decrescente por id
void quickSort(Registro arr[], int esquerda, int direita) {
    if (esquerda >= direita) return;

    int i = esquerda, j = direita;
    Registro pivo = arr[(esquerda + direita) / 2];

    while (i <= j) {
        while (arr[i].id > pivo.id) i++;
        while (arr[j].id < pivo.id) j--;
        if (i <= j) {
            Registro temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    quickSort(arr, esquerda, j);
    quickSort(arr, i, direita);
}

class MaxHeap {
private:
    noh* heap;
    int size;

    void swap(int i, int j) {
        noh temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyDown(int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && heap[left].reg > heap[largest].reg) largest = left;
        if (right < size && heap[right].reg > heap[largest].reg) largest = right;

        if (largest != i) {
            swap(i, largest);
            heapifyDown(largest);
        }
    }

    void heapifyUp(int i) {
        if (i == 0) return;
        int parent = (i - 1) / 2;
        if (heap[i].reg > heap[parent].reg) {
            swap(i, parent);
            heapifyUp(parent);
        }
    }

public:
    MaxHeap(int capacidade) {
        heap = new noh[capacidade];
        size = 0;
    }

    ~MaxHeap() {
        delete[] heap;
    }

    void insert(const Registro& reg, int origem) {
        heap[size] = { reg, origem };
        heapifyUp(size);
        size++;
    }

    noh extractMax() {
        noh max = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return max;
    }

    bool isEmpty() const {
        return size == 0;
    }
};

void ordering(const string& arquivoEntrada, const string& arquivoSaida) {
    ifstream in(arquivoEntrada, ios::binary);
    if (!in) {
        cerr << "Erro ao abrir arquivo de entrada.\n";
        return;
    }

    Registro buffer[TAMANHO];
    int bloco = 0;

    // Fase 1: gera os blocos ordenados e salva em arquivos temporários
    bool algum_lido = true;
    while (algum_lido) {
        int lidos = 0;
        for (; lidos < TAMANHO && in.read((char*)&buffer[lidos], sizeof(Registro)); lidos++);
        if (lidos == 0) algum_lido = false;

        if(algum_lido){
            quickSort(buffer, 0, lidos - 1);
    
            char nomeTemp[32];
            sprintf(nomeTemp, "temp_bloco_%d.dat", bloco);
            ofstream outTemp(nomeTemp, ios::binary);
            for (int i = 0; i < lidos; i++) {
                outTemp.write((char*)&buffer[i], sizeof(Registro));
            }
            outTemp.close();
            bloco++;
        }
    }
    in.close();

    if (bloco == 0) return;

    // Fase 2: merge multiway com alocação dinâmica
    ifstream* arquivos = new ifstream[bloco];
    Registro* topo = new Registro[bloco];
    bool* ativo = new bool[bloco];

    MaxHeap heap(bloco);

    for (int i = 0; i < bloco; i++) {
        char nomeTemp[32];
        sprintf(nomeTemp, "temp_bloco_%d.dat", i);
        arquivos[i].open(nomeTemp, ios::binary);
        if (arquivos[i].read((char*)&topo[i], sizeof(Registro))) {
            ativo[i] = true;
            heap.insert(topo[i], i);
        } else {
            ativo[i] = false;
        }
    }

    ofstream out(arquivoSaida, ios::binary);

    while (!heap.isEmpty()) {
        noh node = heap.extractMax();
        out.write((char*)&node.reg, sizeof(Registro));

        if (arquivos[node.origem].read((char*)&topo[node.origem], sizeof(Registro))) {
            heap.insert(topo[node.origem], node.origem);
        } else {
            arquivos[node.origem].close();
            ativo[node.origem] = false;
            char nomeTemp[32];
            sprintf(nomeTemp, "temp_bloco_%d.dat", node.origem);
            remove(nomeTemp);
        }
    }

    delete[] arquivos;
    delete[] topo;
    delete[] ativo;
    out.close();
}
