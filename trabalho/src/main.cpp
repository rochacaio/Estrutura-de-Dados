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
void ordering(const string&, const string&);

int main() {
    // string csv = "../data/data_athlete_event_for_test.csv";
    string csv = "../data/data_athlete_event.csv";
    string bin = "../data/binario.dat";
    string binOrdenado = "../data/ordenado.dat";

    // Converte CSV para arquivo binário
    csvToBinary(csv, bin);

    ordering(bin, binOrdenado);

    char comando;
    int posicao;
    Registro novo;

    do{
        cout << "Insira um comando válido: " << endl
        << "r - Imprimir todos os registros" << endl
        << "i - Inserir em determinada posicao" << endl
        << "v - Visualizar certo intervalo" << endl
        << "e - Alterar algum registro" << endl
        << "o - Ordenar por id" << endl
        << "x - Imprimir todos os registros ordenados" << endl
        << "t - Realiza um teste de todas as funcionalidades automaticamente" << endl
        << "f - Finalizar" << endl;

        cin >> comando;

        switch (comando)
        {
        case 'r': //Imprimir todos os registros
            imprimirTodos(bin);
            break;
        case 'i': //Inserir em determinada posicao
            cout << "Em qual posicao deseja inserir?" << endl;
            cin >> posicao;

            novo.id = posicao;
            cout << "Informacoes do novo usuario:" << endl
            << "Nome: " << endl;
            cin >> novo.name;
            cout << "Cidade: " << endl;
            cin >> novo.city;
            cout << "Esporte: " << endl;
            cin >> novo.sport;
            cout << "Evento: " << endl;
            cin >> novo.event;
            cout << "NOC: " << endl;
            cin >> novo.noc;
            
            inserirNaPosicao(bin, novo, posicao);
            cout << "Usuário inserido com sucesso!" << endl;
            break;
        case 'v': //Visualizar certo intervalo
            cout << "Qual intervalo deseja visualizar?" << endl
            << "Inicio: " << endl;
            int inicio;
            cin >> inicio;

            cout << "Fim: " << endl;
            int fim;
            cin >> fim;

            visualizarEntre(bin, inicio, fim);
            break;
        case 'e': //Alterar algum registro
            int posicao;
            cout << "Qual posicao deseja alterar?" << endl;
            cin >> posicao;

            novo.id = posicao;
            cout << "Novas informacoes do usuario:" << endl
            << "Nome: " << endl;
            cin >> novo.name;
            cout << "Cidade: " << endl;
            cin >> novo.city;
            cout << "Esporte: " << endl;
            cin >> novo.sport;
            cout << "Evento: " << endl;
            cin >> novo.event;
            cout << "NOC: " << endl;
            cin >> novo.noc;

            alterarRegistro(bin, posicao, novo);
            break;
        case 'o': //Ordenar por id
            ordering(bin, binOrdenado);
            cout << "Arquivo ordenado com sucesso!" << endl;
            break;
        case 'x': //Imprimir todos os registros
            imprimirTodos(binOrdenado);
            break;
        case 't': //Imprimir todos os registros
            testesAutomaticos();
            break;
        case 'f': //Finalizar
            /* Tratado no while */
            break;
        default:
            cout << "Comando invalido..." << endl;
            break;
        }

    } while (comando != 'f');

    

    return 0;
}

void testesAutomaticos(){
    string csv = "../data/data_athlete_event_for_test.csv";
    // string csv = "../data/data_athlete_event.csv";
    string bin = "../data/binario.dat";
    string binOrdenado = "../data/ordenado.dat";
    // Imprime todos os registros do arquivo binário
    imprimirTodos(bin);

    // Cria um novo registro para testar inserção e alteração
    Registro novo;
    novo.id = 999999;
    strcpy(novo.name, "Teste");
    strcpy(novo.city, "São Paulo");
    strcpy(novo.sport, "Futebol");
    strcpy(novo.event, "Campeonato Paulista");
    strcpy(novo.noc, "BRA");
    
    Registro testeDois;
    testeDois.id = 99999999;
    strcpy(testeDois.name, "Segundo Teste");
    strcpy(testeDois.city, "Rio de Janeiro");
    strcpy(testeDois.sport, "Vôlei");
    strcpy(testeDois.event, "VNL");
    strcpy(testeDois.noc, "USA");
    
    // Insere o novo registro na posição 1
    inserirNaPosicao(bin, novo, 1);

    // Visualiza registros entre posição 0 e 2
    visualizarEntre(bin, 0, 2);

    // Altera o registro na posição 0 com o novo registro
    alterarRegistro(bin, 0, testeDois);

    // Troca os registros das posições 0 e 1
    trocarRegistros(bin, 0, 1);

    // Ordena o arquivo binário e grava em um novo arquivo
    ordering(bin, binOrdenado);

    // Imprime todos os registros do arquivo binário ordenado
    imprimirTodos(binOrdenado);
}
