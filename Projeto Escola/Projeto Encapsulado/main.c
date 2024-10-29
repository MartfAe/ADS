#include "escola.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

int main(void) {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    // Inicialização de listas
    pessoas aluno[Max_Alunos] = {0}; // Inicializa o array com zeros
    pessoas professor[Max_Professores] = {0}; // Inicializa o array com zeros
    materias disciplinas[Max_Disciplinas] = {0}; // Inicializa o array com zeros


    bool encerrar = false;
    bool voltar = false;

    while (!encerrar) {
        cabecalho("principal");
        int opcao = menu("principal");
        printf("Você escolheu a opção: %d\n", opcao); // Debug
        switch (opcao) {
            case 0: { //Encerramento do programa
                encerrar = true;
                break;
            }
            case 1: { //Menu Aluno
                voltar = false;
                while (!voltar) {
                    system("clear");
                    cabecalho("aluno");
                    opcao = menu("cadastro");
                    system("clear");
                    printf("Você escolheu a opção de cadastro: %d\n", opcao); // Debug
                    switch (opcao) {
                        case 0: { //Volta para o menu principal
                            voltar = true;
                            break;
                        }
                        case 1: { //Cadastro de novo aluno
                            printf("Chamando cadastrarPessoa...\n"); // Debug
                            cadastrarPessoa(aluno, Max_Alunos, 1);
                            contadorAluno++;
                            break;
                        }
                        case 2: { //Atualizar dados de aluno
                            printf("Chamando atualizarPessoa...\n"); // Debug
                            atualizarPessoa(aluno, Max_Alunos, 1);
                            break;
                        }
                        case 3: { //Excluir aluno
                            printf("Chamando excluirPessoa...\n"); // Debug
                            excluirPessoa(aluno, Max_Alunos, 1);
                            break;
                        }
                        // Outros casos se forem adicionados ao sistema...
                    }
                }
                break;
            }         
            case 2: { //Menu professor
                voltar = false;
                while (!voltar) {
                    system("clear");
                    cabecalho("professor");
                    opcao = menu("cadastro");
                    system("clear");
                    printf("Você escolheu a opção de cadastro: %d\n", opcao); // Debug
                    switch (opcao) {
                        case 0: { //Volta para o menu principal
                            voltar = true;
                            break;
                        }
                        case 1: { //Cadastro de novo professor
                            printf("Chamando cadastrarPessoa...\n"); // Debug
                            cadastrarPessoa(professor, Max_Professores, 2);
                            contadorProfessor++;
                            break;
                        }
                        case 2: { //Atualizar dados de professor
                            printf("Chamando atualizarPessoa...\n\n");
                            atualizarPessoa(professor, Max_Professores, 2);
                            break;
                        }
                        case 3: { //Excluir professor
                            printf("Chamando excluirPessoa...\n\n");
                             excluirPessoa(professor, Max_Professores, 2);
                            break;
                        }
                        // Outros casos se forem adicionados ao menu professor...
                    }
                }
                break;
            }
            case 3: { //Menu Disciplina
                voltar = false;
                while (!voltar) {
                    system("clear");
                    cabecalho("disciplina");
                    opcao = menu("cadastro");
                    system("clear");
                    printf("Você escolheu a opção de cadastro: %d\n", opcao); // Debug
                    switch (opcao) {
                        case 0: { //Volta para o menu principal
                            voltar = true;
                            break;
                        }
                        case 1: { //Cadastro de nova disciplina
                            printf("Chamando cadastrarDisciplina...\n"); // Debug
                            cadastrarDisciplina(disciplinas, Max_Disciplinas, professor, Max_Professores);
                            break;
                        }
                        case 2: { //Atualizar dados de disciplina
                            printf("CHamando atualizarDisciplina...\n\n");
                            atualizarDisciplina(disciplinas, Max_Disciplinas, professor, Max_Professores);
                            break;
                        }
                        case 3: { //Excluir disciplina
                            printf("Chamando excluirDisciplina...\n\n");
                            excluirDisciplina(disciplinas, Max_Disciplinas);
                            break;
                        }
                        // Outros casos se forem adicionados ao menu disciplina...
                    }
                }
                break;
            }
            case 4: { //Menu Ajuste de matrículas em disciplinas
                voltar = false;
                while (!voltar) {
                    system("clear");
                    cabecalho("ajuste");
                    opcao = menu("ajuste");
                    system("clear");
                    printf("Você escolheu a opção de ajuste: %d\n", opcao); // Debug
                    switch (opcao) {
                        case 0: { //Volta para o menu principal
                            voltar = true;
                            break;
                        }
                        case 1: { //Matricular aluno em uma disciplina
                            adicionarAlunoDisciplina(disciplinas, aluno, Max_Alunos);
                            break;
                        }
                        case 2: { //Desmatricular aluno de uma disciplina
                            desmatricularAlunoDisciplina(disciplinas);
                            break;
                        }
                        // Outros casos se forem adicionados ao menu ajuste de disciplina...
                    }
                }
                break;
            }
            case 5: { //Menu Relatórios
                voltar = false;
                while (!voltar) {
                    system("clear");
                    cabecalho("relatorio");
                    opcao = menu("relatorio");
                    system("clear");
                    printf("Você escolheu a opção de relatório: %d\n", opcao); // Debug
                    switch (opcao) {
                        case 0: { //Volta para o menu principal
                            voltar = true;
                            break;
                        }
                        case 1: { //listagem de alunos sem ordenação do vetor
                            //inserir função para listagem de pessoas(alunos) sem ordenação do vetor
                            break;
                        }
                        case 2: { //listagem de alunos por sexo
                            //inserir função para listagem de pessoas(alunos) por sexo informado
                            break;
                        }
                        case 3: { //listagem de alunos por ordem alfabética
                            //inserir função para listagem de pessoas(alunos) com ordenação do vetor em ordem alfabética
                            break;
                        }
                        case 4: { // listagem de alunos por ordem de nascimento
                            //inserir função para listagem de pessoas(alunos) com ordenação do vetor em ordem de nascimento
                            break;
                        }
                        case 5: { // listagem de alunos matriculados em menos de 3 disciplinas
                            //inserir função para listagem de alunos matriculados em menos de 3 disciplinas
                            break;
                        }
                        case 6: { //listagem de professor sem ordenação do vetor
                            //inserir função para listagem de pessoas(professor) sem ordenação do vetor
                            break;
                        }
                        case 7: { //listagem de professor por sexo
                            //inserir função para listagem de pessoas(professor) por sexo informado
                            break;
                        }
                        case 8: { //listagem de professor por ordem alfabética
                            //inserir função para listagem de pessoas(professor) com ordenação do vetor em ordem alfabética
                            break;
                        }
                        case 9: { // listagem de professor por ordem de nascimento
                            //inserir função para listagem de pessoas(professor) com ordenação do vetor em ordem de nascimento
                            break;
                        }
                        case 10: { //listagem de disciplinas cadastradas
                            //inserir função para listagem de todas as disciplinas cadastradas (nomes das disciplinas)
                            break;
                        }
                        case 11: { //listagem de disciplinas com mais de 40 vagas
                            //inserir função para listagem de disciplinas com mais de 40 vagas e pofessor correspondente (nome da disciplina e nome do professor)
                            break;
                        }
                        case 12: { //listagem dos dados de uma disciplina
                            //inserir função para listagem de todos os dados de uma disciplina selecionada pelo usuário
                            break;
                        }
                        case 13: { //listagem dos aniversariantes do mês
                            //inserir função para listagem de todos as pessoas que fazem aniversário no mês corrente e suas respectivas datas de aniversário (dia/mês)
                            break;
                        }
                        case 14: { //listagem de todas as pessoas cadastradas
                            //inserir função para listagem de pessoas(todas)
                            break;
                        }
                        // Outros casos se forem adicionados ao menu ajuste de relatórios...
                    }
                }
                break;
            }
            // Outros casos se forem adicionados ao menu principal do sistema...
        }
    }
}
