
# Relatório Técnico – Projeto Prático: Estrutura de Dados 2025/1

## 1. Introdução

O presente relatório descreve o desenvolvimento do projeto prático da disciplina de Estrutura de Dados, cujo objetivo é a implementação de um sistema de manipulação e ordenação de arquivos em memória secundária. O sistema foi construído em linguagem C++, sem o uso da STL, respeitando as restrições da disciplina e priorizando o acesso direto a arquivos binários.

A base de dados utilizada foi convertida de CSV para binário e submetida a diversas operações, como inserção, alteração, troca e visualização de registros. Por fim, foi implementado um algoritmo de ordenação externa baseado no método **Merge Multiway**, adaptado para **ordenação decrescente** por meio do uso de **Max Heap**.

## 2. Estruturas de Dados Utilizadas

### 2.1 Struct Registro
A principal estrutura de dados é a `struct Registro`, que representa um registro individual da base. Esta estrutura contém os campos presentes no CSV original, armazenados em tipos primitivos (inteiros e arrays de caracteres) para facilitar o armazenamento binário e o acesso por posição.

### 2.2 Heap (Max Heap)
Durante o processo de ordenação externa com Merge Multiway, foi utilizado um **Max Heap** para garantir que o maior valor entre os candidatos das "runs" seja selecionado a cada passo do merge, de acordo com a ordenação decrescente solicitada.

### 2.3 Vetores auxiliares e buffers
Vetores simples foram utilizados para armazenar temporariamente os registros durante a leitura de blocos (runs), e aplicou-se o **QuickSort** para ordenar os blocos em memória antes de serem escritos em arquivos temporários.

## 3. Lógica Geral do Programa

O sistema foi dividido em módulos, cada um com responsabilidades bem definidas:

- **Conversão CSV → Binário**: Leitura do arquivo CSV linha a linha, conversão dos campos e escrita sequencial em um arquivo `.bin`.
- **Manipulação do arquivo binário**: Funções específicas permitem:
  - Inserção de registro em posição arbitrária;
  - Visualização de um intervalo de registros;
  - Alteração de dados de um registro específico;
  - Troca entre dois registros;
  - Impressão completa dos registros.
- **Ordenação em Memória Secundária**:
  - O arquivo binário é dividido em blocos que cabem na memória (runs);
  - Cada bloco é ordenado com **QuickSort** e salvo em arquivos temporários;
  - Os arquivos temporários são lidos simultaneamente e mesclados com o uso de um **Max Heap**, garantindo a ordem decrescente.

## 4. Considerações Finais

O projeto atendeu todos os requisitos propostos, respeitando as restrições de programação estruturada e evitando carregamento completo dos arquivos binários. O uso de Max Heap e QuickSort em conjunto no Merge Multiway demonstrou-se eficiente, mesmo sob as limitações impostas.

Além disso, o código foi modularizado, comentado e testado em ambiente Linux, assegurando sua portabilidade e organização. O relatório e o README foram produzidos conforme as orientações da disciplina.

---

**Grupo:**
- Vinícius Souza Arantes – 202410418  
- Mariana Laura Gonçalves Campos Rufo – 20241016  
- Caio César da Rocha

**Data de entrega:** 18 de junho de 2025
