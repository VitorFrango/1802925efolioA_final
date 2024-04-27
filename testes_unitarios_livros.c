/*
 Elimina um livro da biblioteca por ID 2
 int id_do_livro_a_remover = 2;  // ID do livro a ser removido alterar conforme necessário


gcc -o testes_unitarios_livros testes_unitarios_livros.c gestao_livros.c
./testes_unitarios_livros

 */

#include <stdio.h>
#include <string.h>
#include "gestao_livros.h"


// Função para testar a adição de um livro
void test_adicionar_livro(void) {
    Livro *livros = NULL;
    int count = 0;

    inicializar_biblioteca("livros.csv", &livros, &count);  // Usando 'livros.csv'
    int old_count = count;
    adicionar_livro(&livros, &count);

    if (count != old_count + 1) {
        printf("Teste falhou: esperava-se que o count fosse %d, mas era %d\n", old_count + 1, count);
    } else {
        guardar_livros("livros.csv", livros, count);  // Salva após adicionar
    }
}

// Função para testar a remoção de um livro por ID
void test_remover_livro_por_id(void) {
    Livro *livros = NULL;
    int count = 0;

    inicializar_biblioteca("livros.csv", &livros, &count);  // Usando 'livros.csv'
    int old_count = count;
    int id_do_livro_a_remover = 2;  // ID do livro a ser removido alterar conforme necessário
    remover_livro_por_id(&livros, &count, id_do_livro_a_remover);

    if (count != old_count - 1) {
        printf("Teste falhou: esperava-se que o count fosse %d, mas era %d\n", old_count - 1, count);
    } else {
        guardar_livros("livros.csv", livros, count);  // guarda após remover
    }
}

// Função principal para testar as funções de gestão de livros
int main() {
    printf("---------------------------------------\n");
    printf("Iniciando testes...\n");
    printf("---------------------------------------\n\n");
    printf("Testa a função adicionar_livro...\n");
    test_adicionar_livro();
    printf("---------------------------------------\n\n");
    printf("Testa a função remover_livro_por_id...\n");
    test_remover_livro_por_id();

    printf("Testes concluídos.\n");

    return 0;
}
