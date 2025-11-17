# Sistema de Pesquisa de Produtos 

Descrição
---------
Programa em C para carregar produtos de um arquivo texto (`produtos.txt`) realizar, via menu, as operações:
1. Adicionar produto
2. Buscar produto por código
3. Imprimir produtos
4. Ordenar por preço e imprimir
5. Sair

Requisitos implementados
- Leitura do arquivo apenas no início da execução; dados ficam em memória durante a execução.
- Uso de struct, vetores e funções separadas para leitura, busca, ordenação e impressão.
- Não grava alterações de volta ao arquivo.
- Código simples e comentado.

Arquivos
--------
- `main.c` - código-fonte em C.
- `produtos.txt` - arquivo de consulta com 20 registros.

Observação
----------
- O arquivo de entrada assume que o "nome" do produto é uma única palavra (sem espaços). A entrada via teclado para adicionar produto aceita nomes com espaços.

Exemplos de uso
---------------
1) Carregar `produtos.txt` (fornecido).
2) Selecionar "3 - Imprimir produtos" para ver a lista.
3) Selecionar "2 - Buscar produto por código" e digitar, por exemplo, `109`.
4) Selecionar "1 - Adicionar produto" para incluir um novo produto (não será salvo em arquivo).
5) Selecionar "4 - Ordenar por preço e imprimir" para ver os produtos ordenados por preço crescente.

