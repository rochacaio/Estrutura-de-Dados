/*
    MaxHeap, para alteração de prioridade
    by joukim & bruno, 2019
    alterado em 2023 by Renato
    modificado em 2025 para usar prioridade como critério principal
*/

#include <iostream>
#include <utility> // para usar swap
#include <stdexcept> // para usar exceção com runtime_error

using namespace std;

struct dado {
    string nomeTarefa;
    char tipoTarefa;
    int energiaGasta;
    int tempoEstimado;
    int prioridade;
};

bool operator>(dado d1, dado d2) {
    return d1.prioridade > d2.prioridade;
}

bool operator<(dado d1, dado d2) {
    return d1.prioridade < d2.prioridade;
}

ostream& operator<<(ostream& output,const dado& d) {
    output << "[" << d.nomeTarefa << "/" << d.tipoTarefa << "/" << d.energiaGasta << "/" << d.tempoEstimado << "/" << d.prioridade <<"]";
    return output;
}

class MaxHeap {
private:
    dado* heap;
    int capacidade;
    int tamanho;
    inline int pai(int i);
    inline int esquerdo(int i);
    inline int direito(int i);
    void corrigeDescendo(int i);
    void corrigeSubindo(int i);
    int buscaIndice(string nome);
public:
    MaxHeap(int cap);
    ~MaxHeap();
    void imprime();
    dado retiraRaiz();
    void insere(dado d);
    void alteraPrioridade(string nome, int novaPrioridade);
};

MaxHeap::MaxHeap(int cap) {
    capacidade = cap;
    tamanho = 0;
    heap = new dado[capacidade];
}

MaxHeap::~MaxHeap() {
    delete[] heap;
}

int MaxHeap::pai(int i) {
    return (i - 1) / 2;
}

int MaxHeap::esquerdo(int i) {
    return 2 * i + 1;
}

int MaxHeap::direito(int i) {
    return 2 * i + 2;
}

void MaxHeap::corrigeDescendo(int i) {
    int maior = i;
    int esq = esquerdo(i);
    int dir = direito(i);

    if (esq < tamanho && heap[esq] > heap[maior])
        maior = esq;

    if (dir < tamanho && heap[dir] > heap[maior])
        maior = dir;

    if (maior != i) {
        swap(heap[i], heap[maior]);
        corrigeDescendo(maior);
    }
}

void MaxHeap::corrigeSubindo(int i) {
    while (i > 0 && heap[i] > heap[pai(i)]) {
        swap(heap[i], heap[pai(i)]);
        i = pai(i);
    }
}

void MaxHeap::imprime() {
if (tamanho == 0)
        throw runtime_error("Heap vazia!");
    for (int i=0; i<tamanho; i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}

dado MaxHeap::retiraRaiz() {
    if (tamanho == 0)
        throw runtime_error("Erro ao retirar raiz");

    dado raiz = heap[0];
    heap[0] = heap[tamanho - 1];
    tamanho--;
    corrigeDescendo(0);
    return raiz;
}

void MaxHeap::insere(dado d){
    if (tamanho == capacidade)
        throw runtime_error("Erro ao inserir");

    heap[tamanho] = d;
    corrigeSubindo(tamanho);
    tamanho++;
}

int MaxHeap::buscaIndice(string nome) {
    for (int i = 0; i < tamanho; i++) {
        if (heap[i].nomeTarefa == nome) {
            return i;
        }
    }
    return -1;
}

void MaxHeap::alteraPrioridade(string nome, int novaPrioridade) {
    int i = buscaIndice(nome);
    if (i == -1)
        throw runtime_error("Tarefa não encontrada");

    int prioridadeAntiga = heap[i].prioridade;
    heap[i].prioridade = novaPrioridade;

    if (novaPrioridade > prioridadeAntiga) {
        corrigeSubindo(i);
    } else {
        corrigeDescendo(i);
    }
}

int main() {
    int capacidade;
    dado info;
    char comando;

    cin >> capacidade;
    MaxHeap meuHeap(capacidade);

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nomeTarefa >> info.tipoTarefa >> info.energiaGasta >> info.tempoEstimado >> info.prioridade;
                    meuHeap.insere(info);
                    break;
                case 'r': // remover
                    cout << meuHeap.retiraRaiz().nomeTarefa << endl;
                    break;
                case 'p': // imprimir
                    meuHeap.imprime();
                    break;
                case 'a': { // alterar prioridade
                    string nome;
                    int novaPrioridade;
                    cin >> nome >> novaPrioridade;
                    meuHeap.alteraPrioridade(nome, novaPrioridade);
                    break;
                }
                case 'f': // finalizar
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f');
    cout << endl;
    return 0;
}