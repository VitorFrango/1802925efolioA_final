/*
 utilizar o ficheiro emprestimos_testes.csv para testar a função adicionar_livro


 gcc -o testes_unitarios_emprestimos testes_unitarios_emprestimos.c gestao_emprestimos.c gestao_livros.c
  ./testes_unitarios_emprestimos


  para emprestar e devolver um livro testar com ID 1
  int id_do_livro_a_emprestar = 1;  // ID do livro "O nome da rosa"

 *
 */

#include <stdio.h>
#include "gestao_livros.h"
#include "gestao_emprestimos.h"

// Adicione mais funções de teste conforme necessário
void test_empresta_livro(void) {
    Livro *livros = NULL;
    Emprestimo *emprestimos = NULL;
    int livro_count = 0;
    int emprestimo_count = 0;

    // Carregar os livros e empréstimos dos arquivos CSV
    inicializar_biblioteca("livros.csv", &livros, &livro_count);
    carregar_emprestimos("emprestimos.csv", &emprestimos, &emprestimo_count);

    // Encontre um livro para emprestar
    int id_do_livro_a_emprestar = 1;  // ID do livro "O nome da rosa"
    int old_copias = 0;
    for (int i = 0; i < livro_count; i++) {
        if (livros[i].id == id_do_livro_a_emprestar) {
            old_copias = livros[i].copias;
            break;
        }
    }

    // Empréstimo do livro
    empresta_livro(livros, livro_count, &emprestimos, &emprestimo_count);

    // Verifique se o número de cópias do livro diminuiu
    for (int i = 0; i < livro_count; i++) {
        if (livros[i].id == id_do_livro_a_emprestar) {
            if (livros[i].copias != old_copias - 1) {
                printf("Teste falhou: esperava-se que o número de cópias fosse %d, mas era %d\n", old_copias - 1,
                       livros[i].copias);
            }
            break;
        }
    }
}

// função para testar a devolução de um livro
void teste_devolver_livro(void) {
    Livro *livros = NULL;
    Emprestimo *emprestimos = NULL;
    int livro_count = 0;
    int emprestimo_count = 0;

    // Carregar os livros e empréstimos dos arquivos CSV
    inicializar_biblioteca("livros.csv", &livros, &livro_count);
    carregar_emprestimos("emprestimos.csv", &emprestimos, &emprestimo_count);

    // Encontre um livro para devolver
    int id_do_livro_a_devolver = 1;  // ID do livro "O nome da rosa"
    int old_copias = 0;
    for (int i = 0; i < livro_count; i++) {
        if (livros[i].id == id_do_livro_a_devolver) {
            old_copias = livros[i].copias;
            break;
        }
    }

    // Devolução do livro
    devolver_livro(livros, livro_count, &emprestimos, &emprestimo_count);

    // Verifique se o número de cópias do livro aumentou
    for (int i = 0; i < livro_count; i++) {
        if (livros[i].id == id_do_livro_a_devolver) {
            if (livros[i].copias != old_copias + 1) {
                printf("Teste falhou: esperava-se que o número de cópias fosse %d, mas era %d\n", old_copias + 1,
                       livros[i].copias);
            }
            break;
        }
    }
}

// função principal para testar as funções de empréstimos
int main() {
    printf("---------------------------------------\n");
    printf("Iniciando testes...\n");
    printf("---------------------------------------\n\n");
    printf("Testa a função empresta_livro...\n");
    test_empresta_livro();
    printf("---------------------------------------\n\n");

    printf("Testa a função devolve_livro...\n");
    teste_devolver_livro();
    printf("---------------------------------------\n\n");

    printf("Testes concluídos.\n");

    return 0;
}
