/* Classe pilha estatica
 *
 *  Implemente uma função que realize a remoção dos dados da estrutura pilha de um determinado tipo utilizando somente como estrutura auxiliar outra pilha.

    Você pode (e deve!) utilizar o código que você desenvolveu na atividade "Pilha com armazenamento em vetor - Lista de tarefas para robô doméstico" como base.

    Entradas:

    Com essa finalidade, você deverá adicionar mais um comando, como segue:

    x seguido de um caracter: para remover os dados que possuem o determinado tipo.
    Saídas:

    Todas as saídas de comandos já estão implementadas na função principal código entregue, somente falta implementar a chamada para a remoção. Ao terminar a execução do programa, todos os itens da pilha são desempilhados e escritos.

    Exemplo de Entrada e Saída juntas: ->
    r
    Erro: pilha vazia!
    i sala s 150
    i quarto1 q 45
    i quarto2 q 60
    i quarto3 q 45
    i cozinha c 130
    r
    Nome: cozinha Tipo: c Valor: 130
    i cozinha c 143
    e
    Nome: cozinha Tipo: c Valor: 143
    i varanda v 111
    i banheiro b 33
    Erro: pilha cheia!
    x q
    f
    Nome: varanda Tipo: v Valor: 111
    Nome: cozinha Tipo: c Valor: 143
    Nome: sala Tipo: s Valor: 150
 *
 */
#include <iostream>

using namespace std;

const int PILHAVAZIA = -1;
const int TAMANHOPILHA = 6;

struct Dado {
    string nome;
    char tipo;
    int valor;
};

// Imprime informações de um dado qualquer.
void imprimir_dado(const Dado& umDado){
    cout<< "Nome: " << umDado.nome << " ";
    cout<< "Tipo: " << umDado.tipo << " ";
    cout<< "Valor: " << umDado.valor << endl;
}

class Pilha {
    private:
        Dado mPilha[TAMANHOPILHA];
        int posTopo;
    public:
        // Constrói pilha vazia.
        Pilha();
        // Destrutor que desaloca memória.
        ~Pilha();
        // Retira e retorna o valor que estiver no topo da pilha.
        Dado Desempilhar();
        // Insere um elemento na pilha.
        void Empilhar(const Dado& d);
        // Apagar todos os dados da pilha.
        void LimparTudo();
        // Imprime o valor que está no topo sem desempilhar.
        inline void Topo();
        // Informa se a pilha está Vazia.
        inline bool Vazia();
        // Informa se a pilha está Cheia.
        inline bool Cheia();
        void RemoverPorTipo(char tipo);
};

Pilha::Pilha(){
	posTopo = PILHAVAZIA;

}

Pilha::~Pilha() {
	    posTopo = PILHAVAZIA;
}

Dado Pilha::Desempilhar() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    return mPilha[posTopo--];
}

void Pilha::Empilhar(const Dado& d) {
    if (this->Cheia()) throw runtime_error("Erro: pilha cheia!");
    mPilha[++posTopo] = d;
}

void Pilha::LimparTudo() {
	while(! this->Vazia()){
		this->Desempilhar();
	}

}

void Pilha::Topo() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    imprimir_dado(mPilha[posTopo]);

}

bool Pilha::Vazia() {
    return posTopo == PILHAVAZIA;
}

bool Pilha::Cheia() {
    return posTopo == TAMANHOPILHA - 1;
}

void Pilha::RemoverPorTipo(char tipo) {
    Pilha auxiliar;
    while (!Vazia()) {
        Dado temp = Desempilhar();
        if (temp.tipo != tipo) {
            auxiliar.Empilhar(temp);
        }
    }
    while (!auxiliar.Vazia()) {
        Empilhar(auxiliar.Desempilhar());
    }
}


int main() {
    Pilha pilha;
    Dado info;
    char comando;
    char tipoRemover;
    do {
        try {
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
                    if(!pilha.Vazia())
                        pilha.Topo();
                    else
                        cout << " Pilha vazia!"<< endl;
                    break;
                case 'x':
                    cin >> tipoRemover;
                    pilha.RemoverPorTipo(tipoRemover);
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
