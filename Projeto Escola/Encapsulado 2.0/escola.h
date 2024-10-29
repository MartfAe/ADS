#ifndef ESCOLA_H
#define ESCOLA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_Pessoas 100
#define Max_Disciplinas 50
#define prefixo_Aluno 20241060000
#define prefixo_Professor 20241170000
#define Max_Alunos_Discplinas 1000

// Estrutura para armazenar a data de nascimento
typedef struct {
    int dia;
    int mes;
    int ano;
} data;

// Estrutura para representar uma pessoa 
typedef struct {
    long long matricula;
    char sexo;
    char nome[100];
    char cpf[15]; 
    data aniversario; 
} pessoas;

// Estrutura para representar uma disciplina
typedef struct {
    char codigo[9];      
    char nome[50];       
    int semestre;        
    char professor[50];  
    int alunos[Max_Alunos_Discplinas];         
    int numAlunos; 
} materias;

// Funções para gerenciamento de pessoas
void listarPessoa(pessoas *pessoa, int Max_Pessoas, char tipoPessoa);
void atualizarPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa);
void excluirPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa);

// Funções para gerenciamento de disciplinas
void atualizarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores);
void excluirDisciplina(materias *disciplinas, int max_Disciplinas);
void cadastrarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores);

// Funções de verificação
int verificarMatricula(long long matricula, pessoas *cadastro, int Max_Pessoas);
void gerarMatriculaAluno(long long *matricula);
void gerarMatriculaProfessor(long long *matricula);
int validarNome(char nome);
int validarCPF(char cpf);
int validarSexo(char sexo);
int validarData(int aniversario);


// Função para separar texto visualmente
void separadorTexto();

#endif // ESCOLA_H
