/**
 Crie um programa que seja capaz de armazenar em uma lista encadeada as equipes de uma maratona de programação. Para cada equipe deverá ser informado o seu nome, o nome do líder da equipe, a linguagem de programação que será utilizada e a quantidade de membros. Você poderá utilizar o código fornecido como base de implementação.

 Os comandos que deverão ser utilizados para execução do programa são:

 i: inserir uma nova equipe no inicio da lista. O formato de entrada é: NomeEquipe Lider Linguagem QtdMembros
 h: inserir uma nova equipe no fim da lista. O formato de entrada é: NomeEquipe Lider Linguagem QtdMembros
 m: inserir uma nova equipe na posição informada pelo usuário através de um número inteiro. Considere 0 como a posição inicial da lista. Caso não seja possível inserir na posição indicada imprima "Posição Inexistente!". O formato de entrada é: posiçãoASerInserida NomeEquipe Lider Linguagem QtdMembros
 r: apagar uma determinada equipe do início da lista. Caso não exista a equipe deverá imprimir Remoção em lista vazia!
 a: apagar uma determinada equipe do fim da lista. Caso não exista a equipe deverá imprimir Remoção em lista vazia!
 p: imprimir lista de equipes cadastradas. Imprimir Lista vazia! quando não tiver elemento a ser impresso.
 s: buscar por uma equipe a partir de seu nome. Imprimir a posição em que a equipe foi encontrada ou Nao encontrado quando a busca não obtiver sucesso.
 Nota: o formato de saída das equipes deve ser: (Nome, Lider, Linguagem, QtdMembros). Para mais instâncias de equipes (comando de impressão), cada uma delas devem ser separadas por quebras de linha.

 Entradas:

 Comandos detalhados no exercício
 Saídas:

 Impressões detalhadas no exercício
 Exemplo de Entrada e Saída misturados:
 r
 Remoção em lista vazia!
 a
 Remoção em lista vazia!
 p
 Lista vazia!
 s Thundercats
 Lista vazia!
 i Vingadores Stark Ruby 3
 h LigaDaJustica Batman C++ 4
 m 1 MuppetBabies Kermit Phyton 9
 p
 (Vingadores, Stark, Ruby, 3)
 (MuppetBabies, Kermit, Phyton, 9)
 (LigaDaJustica, Batman, C++, 4)
 s Thundercats
 Nao encontrado
 r
 p
 (MuppetBabies, Kermit, Phyton, 9)
 (LigaDaJustica, Batman, C++, 4)
 a
 p
 (MuppetBabies, Kermit, Phyton, 9)
 f

 NOTA 93 NO DREDD
 */
#include <iostream>
#include <cstdlib>

using namespace std;

struct equipe {
    string nomeEquipe;
    string lider;
    string linguagem;
    int qtdMembros;
};

class noh {
    friend class lista;
private:
    equipe elenco;
    noh* proximo;
public:
    noh(equipe d);
};

noh::noh(equipe d) {
    elenco = d;
    proximo = NULL;
}

class lista {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos();
    void imprimeReversoAux(noh* umNoh);
public:
    lista();
    lista(const lista& umaLista);
    ~lista();
    lista& operator=(const lista& umaLista);
    inline void insere(equipe elenco);
    void insereNoFim(equipe elenco);
    void insereNoInicio(equipe elenco);
    void insereNaPosicao(int posicao, equipe elenco);
    int procura(string valor);
    void imprime();
    void imprimeReverso();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};

lista::lista() {
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

lista::lista(const lista& umaLista) {
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
    noh* aux = umaLista.primeiro;
    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;
    }
}

lista::~lista() {
    while (!vazia()) {
        removeNoFim();
    }
}

// Remove todos os elementos da lista
void lista::removeTodos() {
    while (!vazia()) {
        removeNoInicio();
    }
}

lista& lista::operator=(const lista& umaLista) {
    removeTodos();
    noh* aux = umaLista.primeiro;
    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;
    }
    return *this;
}

void lista::insereNoFim(equipe elenco) {
    noh* novo = new noh(elenco);
    if (vazia()) {
        primeiro = novo;
        ultimo = novo;
    } else {
        ultimo->proximo = novo;
        ultimo = novo;
    }
    tamanho++;
}

void lista::insereNoInicio(equipe elenco) {
    noh* novo = new noh(elenco);
    if (vazia()) {
        primeiro = novo;
        ultimo = novo;
    } else {
        novo->proximo = primeiro;
        primeiro = novo;
    }
    tamanho++;
}

void lista::insereNaPosicao(int posicao, equipe elenco) {
    if (posicao < 0 || posicao > tamanho) {
        throw runtime_error("Posição Inexistente!");
    }

    noh* novo = new noh(elenco);

    if (posicao == 0) {
        novo->proximo = primeiro;
        primeiro = novo;
        if (tamanho == 0) {
            ultimo = novo;
        }
    } else {
        noh* aux = primeiro;
        for (int i = 0; i < posicao - 1; ++i) {
            aux = aux->proximo;
        }
        novo->proximo = aux->proximo;
        aux->proximo = novo;
        if (novo->proximo == NULL) {
            ultimo = novo;
        }
    }

    tamanho++;
}

int lista::procura(string valor) {
    int count = 0;
    noh* aux = primeiro;
    while (aux != NULL) {
        if (aux->elenco.nomeEquipe == valor) {
            return count;
        }
        aux = aux->proximo;
        count++;
    }
    throw runtime_error("Nao encontrado");
}

void lista::imprime() {
    if (vazia()) {
        cout << "Lista vazia!" << endl;
        return;
    }

    noh* aux = primeiro;
    while (aux != NULL) {
        cout << "(" << aux->elenco.nomeEquipe << ", " << aux->elenco.lider << ", "
             << aux->elenco.linguagem << ", " << aux->elenco.qtdMembros << ")" << endl;
        aux = aux->proximo;
    }
}

inline bool lista::vazia() {
    return (primeiro == NULL && ultimo == NULL);
}

void lista::removeNoFim() {
    if (vazia()) {
        throw runtime_error("Remoção em lista vazia!");
    }

    if (primeiro == ultimo) {
        delete primeiro;
        primeiro = NULL;
        ultimo = NULL;
    } else {
        noh* aux = primeiro;
        while (aux->proximo != ultimo) {
            aux = aux->proximo;
        }
        delete ultimo;
        ultimo = aux;
        ultimo->proximo = NULL;
    }

    tamanho--;
}

void lista::removeNoInicio() {
    if (vazia()) {
        throw runtime_error("Remoção em lista vazia!");
    }

    if (tamanho == 1) {
        delete primeiro;
        primeiro = NULL;
        ultimo = NULL;
    } else {
        noh* aux = primeiro->proximo;
        delete primeiro;
        primeiro = aux;
    }
    tamanho--;
}

int main() {
    lista minhaLista;
    equipe info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i':
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h':
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoFim(info);
                    break;
                case 'm':
                    cin >> posicao;
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNaPosicao(posicao, info);
                    break;
                case 's':
                    cin >> nomeEquipe;
                    cout << minhaLista.procura(nomeEquipe) << endl;
                    break;
                case 'r':
                    minhaLista.removeNoInicio();
                    break;
                case 'a':
                    minhaLista.removeNoFim();
                    break;
                case 'p':
                    minhaLista.imprime();
                    break;
                case 'f':
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
