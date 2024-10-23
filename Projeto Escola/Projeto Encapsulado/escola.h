#ifndef ESCOLA_H
#define ESCOLA_H

#define Max_Alunos 3
#define Max_Professores 3
#define Max_Disciplinas 3
#define Max_Alunos_Disciplinas 3

// Definição das structs
typedef struct {
    int dia, mes, ano;
} data;

typedef struct {
    int matricula;
    char sexo, nome[50], cpf[15];
    data aniversario;
} pessoas;

typedef struct {
    char nome[50], codigo[8], professor[50];
    int semestre;
    int alunos[Max_Alunos_Disciplinas];
    int numAlunos;
} materias;

// Declaração de funções
pessoas getAluno(pessoas alunos[], int index);
void setAluno(pessoas alunos[], int index, pessoas novoAluno);

materias getDisciplina(materias disciplinas[], int index);
void setDisciplina(materias disciplinas[], int index, materias novaDisciplina);

void separadorTexto(void);
void cabecalho(char nomeMenu[20]);
int menu(char tipoMenu[20]);

void cadastrarPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa);
void cadastrarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores);

#endif
