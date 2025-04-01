/* Classe pilha encadeada
 *
 * Implemente uma função que realize a remoção dos jogos com valores inferiores a um valor informado, denominada remoção especial. Você poderá utilizar somente como estrutura auxiliar outra pilha. Os demais valores da pilha devem permanecer na posição original. Os valores removidos devem ser impressos no momento da remoção.

   Você pode (e deve!) utilizar o código que você desenvolveu na atividade "Pilha com encadeamento - Inventário de itens de jogo" como base.

   Entradas:

   Com essa finalidade, você deverá adicionar mais um comando, como segue:

   x: seguido de um inteiro: para remover (e imprimir) todos os elementos com valor inferiores ao informado
   Saídas:

   Todas as saídas de comandos já estão implementadas na função principal código entregue, somente falta implementar a chamada para a remoção especial. Ao terminar a execução do programa, todos os itens da pilha são desempilhados e escritos.
   -> Ex:
   r
   Erro: pilha vazia!
   i um a 1
   i dois b 2
   i dez j 10
   i quatro d 4
   i sete g 7
   i oito h 8
   r
   Nome: oito Tipo: h Valor: 8
   e
   Nome: sete Tipo: g Valor: 7
   x 4
   Nome: dois Tipo: b Valor: 2
   Nome: um Tipo: a Valor: 1
   f
   Nome: sete Tipo: g Valor: 7
   Nome: quatro Tipo: d Valor: 4
   Nome: dez Tipo: j Valor: 10

 ESSE DEU 54 NO DREDD
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
        void RemocaoEspecial(int limite);
    private:
        Noh* mPtTopo;
};

Pilha::Pilha() {
	mPtTopo = NULL;
}

Pilha::~Pilha() {
	LimparTudo();
}

void Pilha::RemocaoEspecial(int limite){
    Pilha pilhaAux;

    while (!Vazia()) {
        Dado desempilhado = Desempilhar();
        if (desempilhado.valor >= limite) {
            pilhaAux.Empilhar(desempilhado);
        } else {
            imprimir_dado(desempilhado);
        }
    }

    while (!pilhaAux.Vazia()) {
        this->Empilhar(pilhaAux.Desempilhar());
    }
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
    int limite;
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
                case 'x':
					cin >> limite;
					pilha.RemocaoEspecial(limite);
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
