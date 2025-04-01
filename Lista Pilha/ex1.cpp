/* Classe pilha encadeada
 *
 * Implemente uma estrutura de dados pilha, utilizando encadeamento de nós, para implementar um inventário de itens em um jogo digital. A estrutura deve possibilitar, pelo menos, as seguintes ações: empilhamento e desempilhamento de itens, verificação do item no topo da pilha e limpeza do inventário (remoção de todos os elementos da pilha). O desempilhamento deve escrever mensagem de erro na saída ("Erro: pilha vazia!"), quando a pilha já estiver vazia. Os itens do inventários possuem os seguintes atributos: nome (uma string sem espaços), tipo (um único caracter) e valor (um inteiro).

   Entradas:

   O programa deve aceitar os seguintes comandos:

   i: seguido de uma string, um caracter e um inteiro: para inserir um item no inventário
   r: para retirar um item do inventário
   l: para limpar (remover todos) os itens do inventário
   e: para espiar o topo do inventário (escreve o topo sem removê-lo)
   f: para finalizar a execução do programa
   Saídas:

   Todas as saídas de comandos já estão implementadas na função principal desse código exemplo fornecido. Ao terminar a execução do programa, todos os itens da pilha são desempilhados e escritos.

   Exemplo de Entrada e Saída juntas:
   r
   Erro: pilha vazia!
   i um a 1
   i dois b 2
   i quatro d 4
   i sete g 7
   i oito h 8
   r
   Nome: oito Tipo: h Valor: 8
   e
   Nome: sete Tipo: g Valor: 7
   r
   Nome: sete Tipo: g Valor: 7
   f
   Nome: quatro Tipo: d Valor: 4
   Nome: dois Tipo: b Valor: 2
   Nome: um Tipo: a Valor: 1
 *
 */
#include <iostream>
#include <stdexcept>

using namespace std;

struct Dado {
    string nome;
    char tipo;
    int valor;
};

// Imprime as informações de um dado qualquer
void imprimir_dado(const Dado& umDado) {
		 cout << "Nome: " << umDado.nome
         << " Tipo: " << umDado.tipo
         << " Valor: " << umDado.valor
         << endl;
}

class Noh {
    friend class Pilha;
    private:
        Dado mDado; // poderia ser outro tipo de variável
        Noh* mProx;
    public:
        Noh(Dado v) {
            mDado = v;
            mProx = NULL;
        }
};

class Pilha {
    public:
        // Constrói pilha vazia.
        Pilha();
        // Destrutor que desaloca memória.
        ~Pilha();
        // Retira e retorna o valor que estiver no mPtTopo da pilha.
        // Escreve uma mensagem de erro se não for possível desempilhar.
        Dado Desempilhar(); // retorna o mPtTopo da Pilha.
        // Insere um valor na pilha.
        void Empilhar(const Dado& d);
        // Apagar todos os dados da pilha.
        void LimparTudo();
        // Imprime o valor que está no mPtTopo sem desempilhar.
        inline void Topo();
        // Informa se a pilha está Vazia.
        inline bool Vazia();
    private:
        Noh* mPtTopo;
};

Pilha::Pilha() {
	mPtTopo = NULL;
}

Pilha::~Pilha() {
	LimparTudo();
}

Dado Pilha::Desempilhar() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    Noh* auxiliar = mPtTopo;
    Dado rm = mPtTopo->mDado;
    mPtTopo = mPtTopo->mProx;
    auxiliar->mProx = NULL;
    delete auxiliar;
    return rm;
}

void Pilha::Empilhar(const Dado& d) {
	Noh *mPtNovo = new Noh(d);

	mPtNovo->mProx = mPtTopo;
	mPtTopo = mPtNovo;
}

void Pilha::LimparTudo() {
	while(not Vazia()){
		this->Desempilhar();
	}
}

void Pilha::Topo() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    Dado valorMostrar = mPtTopo->mDado;
    cout << "Nome: " << valorMostrar.nome
         << " Tipo: " << valorMostrar.tipo
         << " Valor: " << valorMostrar.valor
         << endl;
}

bool Pilha::Vazia() {
	return mPtTopo == NULL;
}


int main() {
    Pilha pilha;
    Dado info;
    char comando;
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.tipo >> info.valor;
                    pilha.Empilhar(info);
                    break;
                case 'r': // remover
                    imprimir_dado(pilha.Desempilhar());
                    break;
                case 'l': // limpar tudo
                    pilha.LimparTudo();
                    break;
                case 'e': // espiar
                    pilha.Topo();
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    while (not pilha.Vazia()) {
        imprimir_dado(pilha.Desempilhar());
    }
    cout << endl;
    return 0;
}
