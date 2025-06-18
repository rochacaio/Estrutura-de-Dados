# Projeto Prático - Estrutura de Dados 2025/1

## 🧠 Tema
Tratamento de Arquivos e Ordenação em Memória Secundária

## 👥 Integrantes
- Vinícius Souza Arantes – 202410418  
- Mariana Laura Gonçalves Campos Rufo – 20241016  
- Caio César da Rocha

## 📁 Descrição Geral
Este projeto implementa um sistema que:
1. Converte um arquivo `.csv` para um arquivo binário.
2. Permite manipular registros diretamente no arquivo binário (sem carregá-lo inteiramente na memória).
3. Realiza ordenação em memória secundária com o método **Merge Multiway Decrescente**.

## ⚙️ Funcionalidades da Aplicação
- Conversão de arquivos `.csv` para `.bin`;
- Inserção de um novo registro em posição específica;
- Visualização de registros entre duas posições;
- Alteração de registros em uma posição específica;
- Troca entre dois registros;
- Impressão de todos os registros armazenados;
- Ordenação externa com:
  - **Merge Multiway** utilizando **Max Heap** para garantir ordenação decrescente;
  - **QuickSort** aplicado internamente para ordenação local dos blocos antes do merge externo.

## 🛠️ Compilação e Execução

### ✅ Requisitos
- Compilador `g++` instalado
- Sistema operacional compatível: Linux ou Windows

### 🔧 Compilação
Utilize o seguinte comando no terminal (na pasta com os arquivos):
```bash
g++ -o projeto main.cpp csv_to_bin.cpp bin_services.cpp ordenacao_merge_multiway.cpp registro.cpp
```

### 🚀 Execução
No Windows:
```bash
.\projeto.exe
```

No Linux:
```bash
./projeto
```

## 🗃️ Estrutura de Arquivos
```plaintext
.
├── README.md                       # Este arquivo
├── relatorio.pdf                   # Relatório explicativo
└── src
    ├── main.cpp                       # Lógica principal e menu
    ├── csv_to_bin.cpp                 # Conversão de CSV para binário
    ├── bin_services.cpp               # Operações sobre o binário
    ├── ordenacao_merge_multiway.cpp   # Ordenação externa com Max Heap
    ├── registro.cpp                   # Estrutura e lógica dos registros
    └── registro.hpp                   # Definição da struct Registro
└── data
    ├── data_athlete_event.csv                    # Base de dados sorteada
    └── data_athlete_event_for_teste.csv          # Base de dados reduzida para testes simplificados

```

## 📌 Destaques Técnicos

- 🔽 **Ordenação decrescente** garantida com uso de **Max Heap** no Merge Multiway;
- ⚡ Uso de **QuickSort** interno para ordenação das runs antes do merge;
- 💾 Todas as operações são feitas diretamente sobre o arquivo binário, respeitando a limitação de não carregá-lo inteiro;
- ❌ Sem uso de bibliotecas STL ou funções proibidas;
- ✅ Código modular, organizado e compatível com a norma de programação estruturada.

## 📝 Observações
- O código não utiliza `goto`, `break` fora de `switch`, `continue` ou `return` dentro de laços;
- Indentação padronizada e uso correto de comentários descritivos;
- Organização do código favorece manutenibilidade e entendimento.
