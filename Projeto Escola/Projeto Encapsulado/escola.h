#ifndef ESCOLA_H
#define ESCOLA_H

#define Max_Alunos 6;
#define Max_Professores 6 ;
#define Max_Disciplinas 6 ;
#define Max_Alunos_Disciplinas 3 ;


#define prefixo_Aluno 2024106
#define prefixo_Professor 2024117

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

//Função de cadastro
void cadastrarPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa);
void cadastrarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores);

//Atualização e exclusão
void atualizarPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa);
void excluirPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa);
void adicionarAlunoDisciplina(materias *disciplina, pessoas *alunos, int max_Alunos);
void desmatricularAlunoDisciplina(materias *disciplina);

void atualizarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores);
void excluirDisciplina(materias *disciplinas, int max_Disciplinas);

//Geração de matrícula
void gerarMatriculaAluno(int *matricula);
void gerarMatriculaProfessor(int *matricula);


// Declarações das funções de validação
int validarNome(char nome[]);
int validarCPF(char cpf[]);
int validarSexo(char sexo);
int validarData(data aniversario);
int validarMatricula(int matricula);
int validarCodigoDisciplina(char codigo[]);
int validarSemestre(int semestre);
int verificarMatricula(int matricula, pessoas *cadastro, int Max_Pessoas);


// Contadores para gerenciar matrículas
extern int contadorAluno;
extern int contadorProfessor;

#endif
