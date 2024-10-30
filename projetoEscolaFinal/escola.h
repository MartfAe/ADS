#ifndef ESCOLA_H
#define ESCOLA_H

#define Max_Alunos 3
#define Max_Professores 3
#define Max_Disciplinas 3
#define Max_Alunos_Disciplinas 100
#define Max_Matricula 12

#define prefixo_Professor "2024117"
#define prefixo_Aluno "2024106"

//Definição das structs
typedef struct {
    int dia, mes, ano;
} data;

typedef struct {
    char matricula[Max_Matricula];
    char sexo, nome[50], cpf[14];
    data aniversario;
} pessoas;

typedef struct {
    char nome[50], codigo[8], professor[50];
    float semestre;
    pessoas aluno[Max_Alunos_Disciplinas];
    int numAlunos;
    int numVagas;
} materias;


//Definindo as funções

//Funções de matricula
void gerarMatriculaAluno(char matricula[]);
void gerarMatriculaProfessor(char matricula[]);

//Funções de pessoa
void cadastrarPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa);
void atualizarPessoa(pessoas *cadastro, int maxPessoas, int tipoPessoa);
void excluirPessoa(pessoas *cadastro, int *maxPessoas, int tipoPessoa);

//Funções de disciplina
void cadastrarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores);
void atualizarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores);
void excluirDisciplina(materias *disciplinas, int max_Disciplinas);

//Função de validação
int validarNome(char nome[]);
int validarCPF(char cpf[]);
int validarSexo(char sexo[]);
int validarData(data aniversario);
