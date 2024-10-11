#include <stdio.h>
#include <stdlib.h>

struct cadastroAluno{
    char nome[50];
    char sexo, dataDeNascimento; 
    double matricula, cpf;
};

int main(void){
    int opcao;
    int sair = 0;

//Laço para ler a opção desejada
    while (!sair){

        printf("0-Sair\n");
        printf("1-Aluno\n");
        printf("2-Professor\n");
        printf("3-Disciplina\n");

        scanf("%d", opcao);

        switch (opcao){
            case 0:{
                sair = 1;
                break;
            }

            case 1:{
                printf("Aluno\n");
                break;
            }

            case 2:{
                printf("Professor\n");
                break;
            }
            case 3:{
                printf("Disciplina\n");
                break;
            }
        }
    }
   
}