# Sistema de Gerenciamento de Livros

Este é um sistema para o gerenciamento de livros implementado na linguagem C. 
Esse sistema permite que o usuário realize operações como adicionar, buscar, remover e salvar em um arquivo.

## Instruções para Executar o Código por Linha de Comando

1. Compilar o código fonte:
   - Abra um terminal na pasta contendo o arquivo .c
   - Execute o seguinte comando:
     ```bash
     gcc -o main arquivo.c
     ```

2. Executar o programa:
   - Após a compilação, execute o seguinte comando:
     ```bash
     ./main
     ```

3. Seguir as instruções do menu exibido no console para interagir com o programa.

## Lista de Mudanças no Código Original

- Adição de limpeza do buffer do teclado para evitar falhas nas inserções de livros.
- Modificação na função 'inserirLivro' para garantir a inserção em ordem alfabética.
- Ajuste na leitura do título e autor usando 'fgets' para suportar espaços.
- Adição de tratamento de erro ao tentar abrir o arquivo para salvar.
- Ajuste na mensagem de erro ao não encontrar o livro na remoção.
- Correção de erros gramaticais em mensagens de saída.
- Adição de espaços e quebras de linha para melhor legibilidade do código.
- Criação das funções para adicionar, buscar, remover e salvar em um arquivo.

## Arquivos Adicionais na Pasta Zipada

Nenhum arquivo adicional incluído no projeto.
