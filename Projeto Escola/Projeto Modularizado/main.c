#include <stdio.h>
#include <locale.h>
#include "escola.h"
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    setlocale(LC_ALL,"portuguese");

    // Inicialização de listas
    pessoas aluno[Max_Alunos] = {2};
    pessoas professor[Max_Professores] = {2};
    materias disciplinas[Max_Disciplinas] = {2};

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
                if(opcao ==1){
                    cadastrarPessoa(aluno, Max_Alunos, 1);
                }
                break;
            case 2:
                cabecalho("professor");
                opcao = menu("cadastro");
                if(opcao == 2){
                    cadastrarPessoa(professor, Max_Professores, 2);
                }
                break;
            case 3:
                cabecalho("disciplina");
                opcao = menu("cadastro");
                if(opcao == 3){
                    cadastrarDisciplina(disciplinas, Max_Disciplinas, professor, Max_Professores);
                }
                break;
            // Outros cases...
        }
    }
    return 0;
}
