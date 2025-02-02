#ifndef GESTAO_EMPRESTIMOS_H
#define GESTAO_EMPRESTIMOS_H


#include <time.h>
#include "gestao_livros.h"


#define MAX_LINHA_TAM 100
#define MAX_TITULO 100
#define MAX_UTILIZADOR 50
#define MAX_AUTOR 100
#define MAX_GENERO 50

// Estrutura para guardar os empréstimos
typedef struct Emprestimo {
    int id;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    char genero[MAX_GENERO];
    int copias;
    char user[MAX_UTILIZADOR];
    int copias_atuais;
    int copias_emprestadas;
    int is_devolvido;
    time_t data_emprestimo;
    time_t data_devolucao;
} Emprestimo;

// Estrutura para guardar os utilizadores
typedef struct {
    char nome[MAX_UTILIZADOR];
    int count;
} UserCount;


void
copiarDadosLivrosParaEmprestimos(const char *livrosFilePath, const char *emprestimosFilePath, const char *posFilePath,
                                 int emprestimo_count);

void empresta_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count);

void guardar_emprestimo(const char *filename, Emprestimo *emprestimos, int emprestimo_count);

void renovar_emprestimo(Emprestimo *emprestimos, int emprestimo_count);

void devolver_livro(Livro *livros, int count, Emprestimo **emprestimos, int *emprestimo_count);

void carregar_emprestimos(const char *filename, Emprestimo **emprestimos, int *emprestimo_count);

#endif // GESTAO_EMPRESTIMOS_HH