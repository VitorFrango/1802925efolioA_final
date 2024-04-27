// Created by Vitor Frango on 12/04/2024.
// Funções para gerir livros.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gestao_livros.h"


// Inicializa a biblioteca de livros a partir de um arquivo CSV
void inicializar_biblioteca(const char *filename, Livro **livros, int *count) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", filename);
        return;
    }

    char linha[MAX_LINHA_TAM];
    *count = 0;
    *livros = NULL;

    Livro *temp;

    while (fgets(linha, sizeof(linha), file) != NULL) {
        linha[strcspn(linha, "\n")] = 0;

        temp = realloc(*livros, (*count + 1) * sizeof(Livro));
        if (temp == NULL) {
            fprintf(stderr, "Erro ao alocar memória para os livros.\n");
            free(*livros);  // Liberar memória antes alocada
            return;  // Evite o uso de goto, retorne diretamente
        }
        *livros = temp;

        memset(&(*livros)[*count], 0, sizeof(Livro));

        int itemsRead = sscanf(linha, "%d,%[^,],%[^,],%[^,],%d",
                               &(*livros)[*count].id,
                               (*livros)[*count].titulo,
                               (*livros)[*count].autor,
                               (*livros)[*count].genero,
                               &(*livros)[*count].copias);
        if (itemsRead != 5) {
            fprintf(stderr, "Linha malformada: %s\n", linha);
            continue;
        }

        (*count)++;
    }

    if (ferror(file)) {
        perror("Erro ao ler o arquivo");
        free(*livros);  // Limpa a memória alocada
        *livros = NULL;
        *count = 0;
    }

    fclose(file);  // Fecha o arquivo após a leitura
}

// Guarda os livros no arquivo CSV
void guardar_livros(const char *filename, Livro *livros, int count) {
    FILE *file = fopen(filename, "w");  // Abre o arquivo para escrita
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para salvar.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%s,%s,%d\n",
                livros[i].id,
                livros[i].titulo,
                livros[i].autor,
                livros[i].genero,
                livros[i].copias);
    }

    fclose(file);  // Fecha o arquivo após a escrita
}

// Adiciona um livro à biblioteca
void adicionar_livro(Livro **livros, int *count) {
    Livro *temp = realloc(*livros, (*count + 1) * sizeof(Livro));
    if (temp == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o livro.\n");
        return;
    }
    *livros = temp;  // utiliza o ponteiro realocado

    printf("Digite o ID do livro: ");
    scanf("%d", &(*livros)[*count].id);
    getchar();  // limpa o buffer do stdin

    printf("Digite o título do livro: ");
    fgets((*livros)[*count].titulo, MAX_TITULO, stdin);
    (*livros)[*count].titulo[strcspn((*livros)[*count].titulo, "\n")] = '\0';

    printf("Digite o autor do livro: ");
    fgets((*livros)[*count].autor, MAX_AUTOR, stdin);
    (*livros)[*count].autor[strcspn((*livros)[*count].autor, "\n")] = '\0';

    printf("Digite o gênero do livro: ");
    fgets((*livros)[*count].genero, MAX_GENERO, stdin);
    (*livros)[*count].genero[strcspn((*livros)[*count].genero, "\n")] = '\0';

    printf("Digite o número de cópias do livro: ");
    scanf("%d", &(*livros)[*count].copias);
    getchar();  // limpa o buffer do stdin

    (*count)++;

    // guarda os livros no arquivo
    guardar_livros("livros.csv", *livros, *count);
}

// função que pesquisa um livro na biblioteca pelo título, autor ou gênero
void pesquisar_livros(Livro *livros, int count, const char *termo) {
    int encontrado = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(livros[i].titulo, termo) != NULL ||
            strstr(livros[i].autor, termo) != NULL ||
            strstr(livros[i].genero, termo) != NULL) {
            printf("Livro encontrado:\n");
            printf("ID: %d\n", livros[i].id);
            printf("Título: %s\n", livros[i].titulo);
            printf("Autor: %s\n", livros[i].autor);
            printf("Gênero: %s\n", livros[i].genero);
            printf("Cópias: %d\n", livros[i].copias);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nenhum livro encontrado com o termo '%s'.\n", termo);
    }
}


// Remove um livro da biblioteca pelo ID
void remover_livro_por_id(Livro **livros, int *count, int id) {
    int encontrado = 0;
    for (int i = 0; i < *count; i++) {
        if ((*livros)[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                (*livros)[j] = (*livros)[j + 1];
            }
            (*count)--;
            *livros = realloc(*livros, *count * sizeof(Livro));  // Realoca a memória
            if (*livros == NULL && *count > 0) {
                fprintf(stderr, "Falha ao realocar memória após remover um livro.\n");
                return;
            }
            encontrado = 1;
            printf("Livro removido com sucesso.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Livro com ID %d não encontrado.\n", id);
    }

    // Guarda os livros no arquivo após a remoção
    guardar_livros("livros.csv", *livros, *count);
}

// Edita um livro da biblioteca pelo ID
void editar_livro(Livro *livros, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (livros[i].id == id) {
            printf("Editando livro com ID: %d\n", id);
            printf("Novo título: ");
            fgets(livros[i].titulo, MAX_TITULO, stdin);
            livros[i].titulo[strcspn(livros[i].titulo, "\n")] = '\0';
            printf("Novo autor: ");
            fgets(livros[i].autor, MAX_AUTOR, stdin);
            livros[i].autor[strcspn(livros[i].autor, "\n")] = '\0';
            printf("Novo gênero: ");
            fgets(livros[i].genero, MAX_GENERO, stdin);
            livros[i].genero[strcspn(livros[i].genero, "\n")] = '\0';
            printf("Nova quantidade de cópias: ");
            scanf("%d", &livros[i].copias);
            getchar();  // Clear stdin buffer after reading an integer1

            // guarda os livros no arquivo após a edição
            guardar_livros("livros.csv", livros, count);
            return;
        }
    }
    printf("Livro com ID %d não encontrado.\n", id);
}