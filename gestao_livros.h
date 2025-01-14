//
// Created by Vitor Frango on 12/04/2024.
//
#ifndef GESTAO_LIVROS_H
#define GESTAO_LIVROS_H

// Constantes para o tamanho máximo de strings
#define MAX_LINHA_TAM 100
#define MAX_TITULO 100
#define MAX_AUTOR 100
#define MAX_GENERO 50
#define MAX_LINHA_TAM 100

// Estrutura de dados para armazenar informações sobre um livro
typedef struct Livro {
    int id;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    char genero[MAX_GENERO];
    int copias;
} Livro;

void inicializar_biblioteca(const char *filename, Livro **livros, int *count);

void pesquisar_livros(Livro *livros, int count, const char *termo);

void guardar_livros(const char *filename, Livro *livros, int count);

void adicionar_livro(Livro **livros, int *count);

void remover_livro_por_id(Livro **livros, int *count, int id);

void editar_livro(Livro *livros, int count, int id);


#endif //GESTAO_LIVROS_H