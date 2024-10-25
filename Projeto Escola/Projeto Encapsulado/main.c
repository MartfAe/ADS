#include <stdio.h>
#include <locale.h>
#include "escola.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    // Inicialização de listas
    pessoas aluno[Max_Alunos] = {0}; // Inicializa o array com zeros
    pessoas professor[Max_Professores] = {0}; // Inicializa o array com zeros
    materias disciplinas[Max_Disciplinas] = {0}; // Inicializa o array com zeros
    


    bool encerrar = false;
   while (!encerrar) {
    cabecalho("principal");
    int opcao = menu("principal");
    printf("Você escolheu a opção: %d\n", opcao); // Debug
    switch (opcao) {
        case 0:
            encerrar = true;
            break;
        case 1:
            cabecalho("aluno");
            opcao = menu("cadastro");
            printf("Você escolheu a opção de cadastro: %d\n", opcao); // Debug
            if (opcao == 1) {
                printf("Chamando cadastrarPessoa...\n"); // Debug
                cadastrarPessoa(aluno, Max_Alunos, 1);
            }
            break;
        case 2:
            cabecalho("professor");
            opcao = menu("cadastro");
            printf("Você escolheu a opção de cadastro: %d\n", opcao); // Debug
            if (opcao == 1) {
                printf("Chamando cadastrarPessoa...\n"); // Debug
                cadastrarPessoa(professor, Max_Professores, 2);
            }
            break;
        case 3:
            cabecalho("disciplina");
            opcao = menu("cadastro");
            printf("Você escolheu a opção de cadastro: %d\n", opcao); // Debug
            if (opcao == 1) {
                printf("Chamando cadastrarDisciplina...\n"); // Debug
                cadastrarDisciplina(disciplinas, Max_Disciplinas, professor, Max_Professores);
            }
            break;
        // Outros casos...
    }
}
}