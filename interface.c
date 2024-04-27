//
// Created by Vitor Frango on 17/04/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "gestao_livros.h"

// Função para exibir o menu principal
void exibir_menu_principal(Livro **livros, int *livro_count, Emprestimo **emprestimos, int *emprestimo_count) {
    int escolha;

    do {
        printf("\nMenu Principal:\n");
        printf("1. Gestão de Livros\n");
        printf("2. Gestão de Empréstimos\n");
        printf("3. Relatórios\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                menu_gestao_livros(livros, livro_count);
                break;
            case 2:
                copiarDadosLivrosParaEmprestimos("livros.csv", "emprestimos.csv", "pos.csv", *emprestimo_count);
                menu_gestao_emprestimos(livros, livro_count, emprestimos, emprestimo_count);
                break;
            case 3:
                menu_relatorios(emprestimos, emprestimo_count);
                break;
            case 0:
                printf("Adeus!\n");
                exit(0);
        }
    } while (escolha != 0);

}

// Função para exibir o menu de gestão de livros
void menu_gestao_livros(Livro **livros, int *livro_count) {
    int escolha;
    char titulo[MAX_TITULO];


    do {
        printf("\nGestão de Livros:\n");
        printf("1. Adicionar novo livro\n");
        printf("2. Remover livro existente\n");
        printf("3. Editar informação sobre um livro\n");
        printf("4. Pesquisar livros\n");
        printf("5. Guardar livros\n");
        printf("6. Voltar ao menu principal\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Limpa o buffer de entrada após ler um inteiro com scanf
        while (getchar() != '\n');

        switch (escolha) {
            case 1:
                adicionar_livro(livros, livro_count);

                break;
            case 2: {
                int id;
                printf("ID do livro a remover: ");
                scanf("%d", &id);
                remover_livro_por_id(livros, livro_count, id);
            }
                break;
            case 3: {
                int id;
                printf("ID do livro a editar: ");
                scanf("%d", &id);
                editar_livro(*livros, *livro_count, id);
            }
                break;
            case 4: {

                // Declare a variável count antes de chamar exibir_menu_pesquisa_livros
                int count = *livro_count;  // Obter o valor do número de livros
                exibir_menu_pesquisa_livros(*livros, count);

            }
                break;
            case 5:
                guardar_livros("livros.csv", *livros, *livro_count);
                break;

            case 6:
                exibir_menu_principal(livros, livro_count, NULL, NULL);
                break;

            case 0:
                printf("Adeus!\n");
                exit(0);
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 0);
}


// Função para exibir o menu de pesquisa de livros
void exibir_menu_pesquisa_livros(Livro *livros, int count) {
    int escolha;  // Variável para a escolha do menu
    char termo[100];  // Variável para armazenar o termo de pesquisa

    do {
        printf("\nPesquisar Livros:\n");
        printf("1. Pesquisar por título\n");
        printf("2. Pesquisar por autor\n");
        printf("3. Pesquisar por gênero\n");
        printf("4. Voltar ao menu principal\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        // Limpa o buffer de entrada após ler um inteiro com scanf
        while (getchar() != '\n');

        switch (escolha) {
            case 1:
                printf("Insira o título para pesquisa: ");
                fgets(termo, sizeof(termo), stdin);
                termo[strcspn(termo, "\n")] = '\0';  // Remover quebra de linha
                pesquisar_livros(livros, count, termo);  // Use a variável 'count' passada como argumento
                break;

            case 2:
                printf("Insira o autor para pesquisa: ");
                fgets(termo, sizeof(termo), stdin);
                termo[strcspn(termo, "\n")] = '\0';
                pesquisar_livros(livros, count, termo);
                break;

            case 3:
                printf("Insira o gênero para pesquisa: ");
                fgets(termo, sizeof(termo), stdin);
                termo[strcspn(termo, "\n")] = '\0';
                pesquisar_livros(livros, count, termo);
                break;

            case 4:
                exibir_menu_principal(NULL, NULL, NULL, NULL);
                break;

            case 0:
                printf("Adeus!\n");
                exit(0);  // Encerra o programa
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (escolha != 0);
}

// Função para exibir o menu de gestão de empréstimos
void menu_gestao_emprestimos(Livro **livros, int *livro_count, Emprestimo **emprestimos, int *emprestimo_count) {
    int escolha;

    do {
        printf("\nGestão de Empréstimos:\n");
        printf("1. Emprestar livro\n");
        printf("2. Devolver livro\n");
        printf("3. Renovar empréstimo\n");
        printf("4. Guardar empréstimos\n");
        printf("5. Voltar ao menu principal\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                empresta_livro(*livros, *livro_count, emprestimos, emprestimo_count);
                break;
            case 2:
                devolver_livro(*livros, *livro_count, emprestimos, emprestimo_count);

                break;
            case 3:
                renovar_emprestimo(*emprestimos, *emprestimo_count);
                break;
            case 4:
                guardar_emprestimo("emprestimos.csv", *emprestimos, *emprestimo_count);
                break;
            case 5:
                guardar_emprestimo("emprestimos.csv", *emprestimos, *emprestimo_count);
                exibir_menu_principal(livros, livro_count, emprestimos, emprestimo_count);
                break;
            case 0:
                guardar_emprestimo("emprestimos.csv", *emprestimos, *emprestimo_count);
                printf("Adeus!\n");
                exit(0);
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 0);
}

// Função para exibir o menu de relatórios
void menu_relatorios(Emprestimo **emprestimos, int *emprestimo_count) {
    int escolha;

    do {
        printf("\nRelatórios:\n");
        printf("1. Livros mais emprestados\n");
        printf("2. Livros não devolvidos\n");
        printf("3. Maiores locatários\n");
        printf("4. Voltar ao menu principal\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                livros_mais_emprestados(*emprestimos, *emprestimo_count);

                break;
            case 2:
                livros_nao_devolvidos(*emprestimos, *emprestimo_count);

                break;
            case 3:
                locatarios_com_mais_livros_emprestados(emprestimos, emprestimo_count);
                break;
            case 4:
                exibir_menu_principal(NULL, NULL, emprestimos, emprestimo_count);
                break;
            case 0:
                printf("Adeus!\n");
                exit(0);

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 0);
}