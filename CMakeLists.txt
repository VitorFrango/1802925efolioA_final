cmake_minimum_required(VERSION 3.27)
project(1802925efolioA C)

set(CMAKE_C_STANDARD 11)

add_executable(1802925efolioA
        principal.c
        gestao_emprestimos.h
        gestao_emprestimos.c
        gera_relatorios.h
        gera_relatorios.c
        gestao_livros.c
        gestao_livros.h
        interface.c
        interface.h
        testes_integracao.c
)

add_executable(testes_unitarios_livros
        testes_unitarios_livros.c
        gestao_emprestimos.h
        gestao_emprestimos.c
        gera_relatorios.h
        gera_relatorios.c
        gestao_livros.c
        gestao_livros.h
        interface.c
        interface.h
)

add_executable(testes_unitarios_emprestimos
        testes_unitarios_emprestimos.c
        gestao_emprestimos.h
        gestao_emprestimos.c
        gera_relatorios.h
        gera_relatorios.c
        gestao_livros.c
        gestao_livros.h
        interface.c
        interface.h
)

add_executable(testes_integracao
        testes_integracao.c
        gestao_emprestimos.h
        gestao_emprestimos.c
        gera_relatorios.h
        gera_relatorios.c
        gestao_livros.c
        gestao_livros.h
        interface.c
        interface.h
)