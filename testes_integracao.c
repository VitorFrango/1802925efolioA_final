//
// Created by Vitor Frango on 26/04/2024.
//
/*
    gcc -o testes_integracao testes_integracao.c interface.c gestao_livros.c gestao_emprestimos.c
    ./testes_integracao
 *
 *
 *Para compilar com a flag TESTING:
    gcc -DTESTING -o teste_integracao testes_integracao.c gestao_livros.c gestao_emprestimos.c
    ./teste_integracao
 *
 */

#include <assert.h>
#include <stdio.h>

#include "gestao_livros.h"
#include "gestao_emprestimos.h"
#include "interface.h"

// Adicione mais funções de teste conforme necessário
void test_inicializar_biblioteca() {
    Livro *livros = NULL;
    int count = 0;
    inicializar_biblioteca("livros.csv", &livros, &count);
    assert(count > 0);
    assert(livros != NULL);

}

// Adicione mais funções de teste conforme necessário
void test_adicionar_livro() {
    Livro *livros = NULL;
    int count = 0;
    inicializar_biblioteca("livros.csv", &livros, &count);
    int old_count = count;
    adicionar_livro(&livros, &count);
    assert(count == old_count + 1);
    // Adicione mais asserções conforme necessário
}

// Adicione mais funções de teste conforme necessário
void test_empresta_livro() {
    Livro *livros = NULL;
    int livro_count = 0;
    Emprestimo *emprestimos = NULL;
    int emprestimo_count = 0;
    inicializar_biblioteca("livros.csv", &livros, &livro_count);
    carregar_emprestimos("emprestimos.csv", &emprestimos, &emprestimo_count);
    int old_count = emprestimo_count;
    empresta_livro(livros, livro_count, &emprestimos, &emprestimo_count);
    assert(emprestimo_count == old_count + 1);
    // Adicione mais asserções conforme necessário
}

#ifdef TESTING // Para compilar com a flag TESTING
int main() {
    printf("---------------------------------------\n\n");

    printf("Testa a função inicializar_biblioteca...\n");
    test_inicializar_biblioteca();
    printf("---------------------------------------\n\n");
    printf("Testa a função adicionar_livro...\n");
    test_adicionar_livro();
    printf("---------------------------------------\n\n");
    printf("Testa a função empresta_livro...\n");
    test_empresta_livro();

    return 0;
}
#endif