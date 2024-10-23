#include <stdio.h>
#include <locale.h>
#include "escola.h"
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    setlocale(LC_ALL,"portuguese");

    // Inicialização de listas
    pessoas aluno[Max_Alunos] = {0};
    pessoas professor[Max_Professores] = {0};
    materias disciplinas[Max_Disciplinas] = {0};

    bool encerrar = false;
    while (!encerrar) {
        cabecalho("principal");
        int opcao = menu("principal");
        switch (opcao) {
            case 0:
                encerrar = true;
                break;
            case 1:
                cabecalho("aluno");
                opcao = menu("cadastro");
                // Chamar função de cadastro de alunos
                break;
            case 2:
                cabecalho("professor");
                opcao = menu("cadastro");
                // Chamar função de cadastro de professores
                break;
            case 3:
                cabecalho("disciplina");
                opcao = menu("cadastro");
                // Chamar função de cadastro de disciplinas
                break;
            // Outros cases...
        }
    }
    return 0;
}
