#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>
#include <ctype.h>
#include <conio.h>

#define Max_Alunos 3
#define Max_Professores 3
#define Max_Disciplinas 3
#define Max_Alunos_Disciplinas 100
#define Max_Matricula 12

# define prefixo_Professor "2024117"
#define prefixo_Aluno "2024106"

// Definição das structs
typedef struct {
    int dia, mes, ano;
} data;

typedef struct {
    char matricula[Max_Matricula];
    char sexo, nome[50], cpf[14];
    data aniversario;
    int disciplinas;
} pessoas;

typedef struct {
    char nome[50], codigo[8], professor[50];
    float semestre;
    pessoas aluno[Max_Alunos_Disciplinas];
    int numAlunos;
    int numVagas;
} materias;

//Definindo as funções 
void cadastrarPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa);
void cadastrarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores);
void gerarMatriculaAluno(char matricula[]);
void gerarMatriculaProfessor(char matricula[]);

void gerarMatriculaAluno(char matricula[]);
void gerarMatriculaProfessor(char matricula[]);
int validarNome(char nome[]);
int validarCPF(char cpf[]);
int validarSexo(char sexo);
int validarData(data aniversario);
int validarMatricula(int matricula);
int validarCodigoDisciplina(char codigo[]);
int validarSemestre(float semestre);
void toUpperString(char *str);


int contadorAluno = 0; // Contador de alunos
int contadorProfessor = 0; // Contador de professores

// Implementação de separador
void separadorTexto(void) {
    printf("\n");
    for (int i = 0; i < 80; i++) {
        printf("-");
    }
}

// Implementação de cabeçalho
void cabecalho(char nomeMenu[12]) {
    printf("Cabecalho chamado para: %s\n", nomeMenu); // Debug
    separadorTexto();
    printf("\n");
    if (strcmp(nomeMenu, "principal") == 0) {
        printf("\t\t\t\tProjeto Escola");
    } else if (strcmp(nomeMenu, "professor") == 0) {
        printf("\t\t\t\tProfessor");
    } else if (strcmp(nomeMenu, "aluno") == 0) {
        printf("\t\t\t\tAluno");
    } else if (strcmp(nomeMenu, "disciplina") == 0) {
        printf("\t\t\t\tDisciplina");
    } else if (strcmp(nomeMenu, "ajuste") == 0) {
        printf("\t\t\t\tAjuste de Matrículas");
    } else if (strcmp(nomeMenu, "relatorio") == 0) {
        printf("\t\t\t\tRelatórios");
    }
    separadorTexto();
    printf("\n");
}

// Implementação de menus
int menu(char tipoMenu[20]) {
    int opcao;
    if (strcmp(tipoMenu, "principal") == 0) { //Menu principal
        printf("0 - Sair\n");
        printf("1 - Aluno\n");
        printf("2 - Professor\n");
        printf("3 - Disciplina\n");
        printf("4 - Ajuste de matrículas em disciplinas\n");
        printf("5 - Relatório\n");
        // Adicione mais opções se necessário
        printf("\n");
    } else if (strcmp(tipoMenu, "cadastro") == 0) { //Menu alunos, professor e disciplina
        printf("0 - Voltar\n");
        printf("1 - Cadastrar\n");
        printf("2 - Atualizar\n");
        printf("3 - Excluir\n");
        // Adicione mais opções se necessário
        printf("\n");
    } else if (strcmp(tipoMenu, "ajuste") == 0) { //Menu ajuste de matrícula
        printf("0 - Voltar\n");
        printf("1 - Matricular aluno em uma disciplina\n");
        printf("2 - Desmatricular aluno de uma disciplina\n");
        // Adicione mais opções se necessário
        printf("\n");
    } else if (strcmp(tipoMenu, "relatorio") == 0) { //Menu relatórios
        printf("0 - Voltar\n");
        printf("\nRelatórios de Alunos:\n\n");
        printf("%-46s %-30s\n","1 - Sem ordenação","2 - Por sexo");
        printf("%-45s %-30s\n","3 - Em ordem alfabética","4 - Em ordem de nascimento");
        printf("%-45s\n","5 - Matriculados em menos de 3 disciplinas");
        printf("\nRelatórios de Professores:\n\n");
        printf("%-46s %-30s\n","6 - Sem ordenação","7 - Por sexo");
        printf("%-45s %-30s\n","8 - Em ordem alfabética","9 - Em ordem de nascimento");
        printf("\nRelatórios de Disciplinas:\n\n");
        printf("%-44s %-30s\n","10 - Disciplinas cadastradas","12 - Dados de disciplina");
        printf("%-43s\n","11 - Disciplinas com mais de 40 vagas");
        printf("\nDemais Relatórios:\n\n");
        printf("%-45s %-30s\n","13 - Aniversariantes do mês","14 - Todas as pessoas cadastradas");
        // Adicione mais opções se necessário
        printf("\n");
    }
    
    scanf("%d", &opcao);
    return opcao;
}

//Implementação Impressão de dados de uma pessoas

void printCadastroPessoa(pessoas *pessoa,int index){
    printf("Nome: %s\n", pessoa[index].nome);
    printf("Matrícula: %s\n", pessoa[index].matricula);
    printf("CPF: %s\n", pessoa[index].cpf);
    printf("Sexo: %c\n", pessoa[index].sexo);
    printf("Data de nascimento: %02d/%02d/%04d \n", pessoa[index].aniversario.dia, pessoa[index].aniversario.mes, pessoa[index].aniversario.ano);
    separadorTexto();
    printf("\n");
}

//Implementação Impressão de dados de uma disciplina

void printCadastroDisciplina(materias *disciplina, int index, bool comAluno){
    printf("Nome: %s\n", disciplina[index].nome);
    printf("Código: %s\n", disciplina[index].codigo);
    printf("Semestre: %.1f\n", disciplina[index].semestre);
    printf("Total de vagas: %d / %d\n", disciplina[index].numAlunos,disciplina[index].numVagas);
    printf("Professor responsável: %s\n",disciplina[index].professor);
    if(comAluno){
    	    printf("Alunos matriculados: ");
            for(int i=0; i < disciplina[index].numAlunos; i++){
            printf("%s|",disciplina[index].aluno[i].nome);
        }
    }
    separadorTexto();
    printf("\n");
}

// Implementação dos Getters e Setters

pessoas getProfessor(pessoas professores[], int index) {
    return professores[index];
}


void setProfessor(pessoas professores[], int index, pessoas novoProfessor) {
    if (strlen(novoProfessor.nome) > 0 && strlen(novoProfessor.cpf) == 14) {
        professores[index] = novoProfessor;
    } else {
        printf("Erro: Nome ou CPF inválido.\n");
    }
}

pessoas getAluno(pessoas alunos[], int index) {
    return alunos[index];
}

void setAluno(pessoas alunos[], int index, pessoas novoAluno) {
    if (strlen(novoAluno.nome) > 0 && strlen(novoAluno.cpf) == 14) {
        alunos[index] = novoAluno;
    } else {
        printf("Erro: Nome ou CPF inválido.\n");
    }
}

materias getDisciplina(materias disciplinas[], int index) {
    return disciplinas[index];
}

void setDisciplina(materias disciplinas[], int index, materias novaDisciplina) {
    if (strlen(novaDisciplina.nome) > 0 && strlen(novaDisciplina.codigo) <= 8) {
        disciplinas[index] = novaDisciplina;
    } else {
        printf("Erro: Nome ou Código da disciplina inválido.\n");
    }
}

//Função para gerar a matrícula para aluno
void gerarMatriculaAluno(char matricula[]) {
    if (contadorAluno >= 9999) {
        printf("Erro: Limite de matrículas atingido para alunos.\n");
        return;
    } 
    sprintf(matricula, "%s%04d", prefixo_Aluno, contadorAluno + 1);
    contadorAluno++;
}

//Função para gerar a matrícula para professor
void gerarMatriculaProfessor(char matricula[]) {
    if (contadorProfessor >= 9999) {
        printf("Erro: Limite de matrículas atingido para professores.\n");
        return;
    }
    
    sprintf(matricula, "%s%04d", prefixo_Professor, contadorProfessor + 1);
    contadorProfessor++;
}

//FUnção cadastrar pessoa
void cadastrarPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa) {
    printf("Entrou na função cadastrarPessoa\n"); // Debug
    int i;

    for (i = 0; i < maxPessoas; i++) {
        if (cadastro[i].matricula[0] == '\0') {  // Verifica se o campo matrícula está vazio
            pessoas novoCadastro; 

            if (tipoPessoa == 1) {
                printf("Cadastro de Aluno:\n\n");
                gerarMatriculaAluno(novoCadastro.matricula);
                printf("Matrícula gerada: %s\n", novoCadastro.matricula);
            } else if (tipoPessoa == 2) {
                printf("Cadastro de Professor:\n");
                gerarMatriculaProfessor(novoCadastro.matricula);
                printf("Matrícula gerada: %s\n", novoCadastro.matricula);
            }

            // Loop para o nome
            do {
                printf("Informe o nome:\n");
                getchar();
                fgets(novoCadastro.nome, sizeof(novoCadastro.nome), stdin);
                novoCadastro.nome[strcspn(novoCadastro.nome, "\n")] = '\0';  
                toUpperString(novoCadastro.nome); 
            } while (!validarNome(novoCadastro.nome));

           //Loop para o cpf
           do {
                char cpf[15];  // Buffer para ler o CPF
                printf("Informe o CPF no seguinte formato XXX.XXX.XXX-XX:\n");
                fgets(cpf, sizeof(cpf), stdin); // Lê o CPF para o buffer
                cpf[strcspn(cpf, "\n")] = '\0';  // Remove a nova linha

                if (validarCPF(cpf)) { // Valida o CPF
                    strcpy(novoCadastro.cpf, cpf); // Copia para a estrutura
                } else {
                    printf("CPF inválido. Tente novamente.\n");
                }
            } while (strlen(novoCadastro.cpf) == 0); 
            
            // Loop para o sexo
            do {
                printf("Informe o sexo (M/F):\n");
                scanf(" %c", &novoCadastro.sexo);
                getchar(); 
            } while (!validarSexo(novoCadastro.sexo));

            // Loop para a data de nascimento
            do {
                printf("Informe a data de nascimento separada por um espaço (dd mm aaaa):\n");
                if (scanf("%d %d %d", &novoCadastro.aniversario.dia, &novoCadastro.aniversario.mes, &novoCadastro.aniversario.ano) != 3) {
                    printf("Formato inválido. Tente novamente.\n");
                    while (getchar() != '\n');  
                }
            } while (!validarData(novoCadastro.aniversario));

            // Usa o setter apropriado para atualizar o cadastro
            if (tipoPessoa == 1) {
                setAluno(cadastro, i, novoCadastro); 
                printf("Aluno cadastrado com sucesso!\n");
            } else if (tipoPessoa == 2) {
                setProfessor(cadastro, i, novoCadastro); 
                printf("Professor cadastrado com sucesso!\n");
            }
            break;
        }

    // Se o loop terminar sem encontrar uma posição vazia, exibe mensagem
    if (i == maxPessoas) {
        if (tipoPessoa == 1) {
            printf("Não há espaço para cadastrar mais alunos.\n");
        } else if (tipoPessoa == 2) {
            printf("Não há espaço para cadastrar mais professores.\n");
        }
    }
}
}

//Função para validar nome
  int validarNome(char nome[]) {
    //printf("Entrou na função validarNome.\n"); // Debug

    // Verifica se o nome foi inserido
    if (strlen(nome) == 0) {
        printf("O nome não pode ser vazio. Tente novamente.\n");
        return 0;
    }

    // Converte o nome para letras maiúsculas e verifica se contém números
    for (int i = 0; i < strlen(nome); i++) {
        if (isdigit(nome[i])) {  // Verifica se é um dígito
            printf("Erro: O nome não deve conter números.\n");
            return 0;
        }
        nome[i] = toupper(nome[i]);  // Converte para maiúsculo
    }

    // Verifica se o nome tem pelo menos 3 caracteres após a conversão
    if (strlen(nome) < 3) {
        printf("Erro: O nome deve ter pelo menos 3 caracteres.\n");
        return 0;
    }

    return 1; // Nome é válido
}

//Função validar CPF
int validarCPF(char cpf[]){
    //printf("Entrou na função validarCPF.\n"); // debug

    // Verificar se o CPF tem exatamente 14 caracteres
    if (strlen(cpf) != 14) {
        printf("Erro: O CPF deve ser informado com 14 dígitos no formato XXX.XXX.XXX-XX.\n");
        return 0;
    }
    return 1; 
}
// Função Validar Sexo
int validarSexo(char sexo) {
    // Converte o caractere para maiúsculo
    sexo = toupper(sexo);

    // Verifica se o sexo é 'M' ou 'F'
    if (sexo != 'M' && sexo != 'F') {
        printf("Sexo inválido. Use 'M' para sexo masculino ou 'F' para o sexo feminino.\n");
        return 0;
    }
    return 1;
}

// Função validar data
int validarData(data aniversario) {
    //printf("Entrou na função validarData.\n"); // debug
    if (aniversario.dia < 1 || aniversario.dia > 31 || aniversario.mes < 1 || aniversario.mes > 12 || aniversario.ano < 1900 || aniversario.ano >2024) {
        printf("Formato de data inválido. Tente novamente.\n");
        return 0;
    }
    return 1;
}

// Implementação da função de cadastrar disciplina
void cadastrarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores) {
    //printf("Entrou na função cadastro de disciplina.\n"); // Debug
    int i;

    for (i = 0; i < max_Disciplinas; i++) {
        if (disciplinas[i].codigo[0] == '\0') { // Verifica se a disciplina não foi cadastrada
            materias novaDisciplina;

            // Validação do nome da disciplina
            do {
                printf("Informe o nome da disciplina:\n");
                getchar();
                fgets(novaDisciplina.nome, sizeof(novaDisciplina.nome), stdin);
                novaDisciplina.nome[strcspn(novaDisciplina.nome, "\n")] = '\0';

                if (strlen(novaDisciplina.nome) < 3) {
                    printf("O nome da disciplina deve ter no mínimo 3 caracteres.\n");
                } else {
                    toUpperString(novaDisciplina.nome); // Converte o nome para maiúsculas
                }
            } while (strlen(novaDisciplina.nome) < 3);

            // Validação do código da disciplina
            do {
                printf("Informe o código da disciplina (máx 8 caracteres):\n");
                
                fgets(novaDisciplina.codigo, sizeof(novaDisciplina.codigo), stdin);
                novaDisciplina.codigo[strcspn(novaDisciplina.codigo, "\n")] = '\0';

                if (strlen(novaDisciplina.codigo) > 8 || strlen(novaDisciplina.codigo) == 0) {
                    printf("O código deve ter entre 1 e 8 caracteres.\n");
                } else {
                    toUpperString(novaDisciplina.codigo); // Converte o código para maiúsculas
                }
            } while (strlen(novaDisciplina.codigo) > 8 || strlen(novaDisciplina.codigo) == 0);
            

            novaDisciplina.semestre = 0 ;

            // Validação do semestre
            int validInput = 0; 
            do {
                
                printf("Informe o semestre da disciplina (ex xxxx.y):\n");
                char input[20]; 
                fgets(input, sizeof(input), stdin);
                // Tenta ler o semestre
                if (sscanf(input, "%f", &novaDisciplina.semestre) != 1 || novaDisciplina.semestre <= 0) {
                    printf("Semestre inválido. Informe um número positivo.\n");
                } else {
                    validInput = 1; // Semestre válido
                }
            } while (!validInput);

            // Solicita o número de vagas da disciplina
            do {
                printf("Informe o número de vagas da disciplina:\n");
                if (scanf("%d", &novaDisciplina.numVagas) != 1 || novaDisciplina.numVagas <= 0) {
                    printf("Número de vagas inválido. Informe um número positivo.\n");
                } else {
                    while (getchar() != '\n'); 
                    break; 
                }
            } while (1); 

            // Seleção do professor
            int encontrou = 0;

            if (max_Professores <= 0) {
                printf("Não há professores cadastrados.\n");
                return;
            }
            char matriculaProf[15]; 
            do {
                printf("Informe a matrícula do professor:\n");
                fgets(matriculaProf, sizeof(matriculaProf), stdin);
                matriculaProf[strcspn(matriculaProf, "\n")] = '\0'; 

                for (int j = 0; j < max_Professores; j++) {
                    if (strncmp(professores[j].matricula, prefixo_Professor, strlen(prefixo_Professor)) == 0) { 
                        if (strcmp(professores[j].matricula, matriculaProf) == 0) {
                            strcpy(novaDisciplina.professor, professores[j].nome);
                            encontrou = 1; // Professor encontrado
                            printf("Professor encontrado: %s - %s\n", professores[j].matricula, professores[j].nome);
                            break; // Sai do loop se o professor foi encontrado
                        }
                    }
                }

                if (!encontrou) {
                    printf("Professor não encontrado. Tente novamente.\n");
                }
            } while (!encontrou);
            // Exibe os dados cadastrados para confirmação
            printf("\nConfirme os dados da disciplina:\n");
            printf("Nome: %s\n", novaDisciplina.nome);
            printf("Código: %s\n", novaDisciplina.codigo);
            printf("Semestre: %.1f\n", novaDisciplina.semestre); // Formatação adequada para impressão
            printf("Número de Vagas: %d\n", novaDisciplina.numVagas);
            printf("Professor: %s\n", novaDisciplina.professor);
            
            char confirmacao;
            printf("Deseja realmente salvar esta disciplina? (s/n): ");
            scanf(" %c", &confirmacao);

            // Verifica a confirmação do usuário
            if (confirmacao == 's' || confirmacao == 'S') {
                novaDisciplina.numAlunos = 0;
                setDisciplina(disciplinas, i, novaDisciplina); 
                printf("Disciplina cadastrada com sucesso!\n");
            } else {
                printf("Cadastro da disciplina cancelado.\n");
            }
            return;  // Sai da função após o cadastro
        }
    }

    // Mensagem caso não haja espaço
    if (i == max_Disciplinas) {
        printf("Não há espaço para cadastrar mais disciplinas.\n");
    }
}

//Função para adicionar aluno em uma disciplina
void adicionarAlunoDisciplina(materias *disciplinas, int maxDisciplinas, pessoas *alunos, int maxAlunos, char matriculaAluno[]) {
    int alunoEncontrado = -1, disciplinaEncontrada = -1;

    // Verificar se há alunos cadastrados
    if (maxAlunos <= 0) {
        printf("Erro: Não há alunos cadastrados.\n");
        return;
    }

    // Buscar o aluno pela matrícula
    for (int i = 0; i < maxAlunos; i++) {
        if (strcmp(getAluno(alunos, i).matricula, matriculaAluno) == 0) {
            alunoEncontrado = i;
            break;
        }
    }

    if (alunoEncontrado == -1) {
        printf("Erro: Aluno com matrícula %s não encontrado.\n", matriculaAluno);
        return;
    }

    // Exibir disciplinas cadastradas
    printf("Disciplinas cadastradas:\n");
    for (int i = 0; i < maxDisciplinas; i++) {
        if (disciplinas[i].codigo[0] != '\0') {  // Exibir apenas disciplinas cadastradas
            printf("Código: %s - Nome: %s\n", disciplinas[i].codigo, disciplinas[i].nome);
        }
    }

    // Seleção da disciplina pelo código
    char codigoDisciplina[9];
    printf("Informe o código da disciplina para adicionar o aluno:\n");
    getchar();
    fgets(codigoDisciplina, sizeof(codigoDisciplina), stdin);
    codigoDisciplina[strcspn(codigoDisciplina, "\n")] = '\0';  // Remover newline

    for (int i = 0; i < maxDisciplinas; i++) {
        if (strcmp(disciplinas[i].codigo, codigoDisciplina) == 0) {
            disciplinaEncontrada = i;
            break;
        }
    }

    if (disciplinaEncontrada == -1) {
        printf("Erro: Disciplina com código %s não encontrada.\n", codigoDisciplina);
        return;
    }

    // Verificar limite de alunos na disciplina em relação ao número de vagas
    if (disciplinas[disciplinaEncontrada].numAlunos >= disciplinas[disciplinaEncontrada].numVagas) {
        printf("Erro: A disciplina já atingiu o limite de alunos (vagas: %d).\n", disciplinas[disciplinaEncontrada].numVagas);
        return;
    }

    // Confirmação antes de adicionar o aluno
    char confirmacao;
    printf("Você está prestes a adicionar o aluno %s à disciplina %s. Deseja continuar? (s/n): ", 
            getAluno(alunos, alunoEncontrado).nome, disciplinas[disciplinaEncontrada].nome);
    scanf(" %c", &confirmacao); // Espaço antes de %c para consumir qualquer newline remanescente

    if (confirmacao == 's' || confirmacao == 'S') {
        // Adicionar aluno na disciplina
        setAluno(disciplinas[disciplinaEncontrada].aluno, disciplinas[disciplinaEncontrada].numAlunos, getAluno(alunos, alunoEncontrado)); // Usando o setter para adicionar o aluno
        disciplinas[disciplinaEncontrada].numAlunos++; // Atualiza o número de alunos
        printf("Aluno %s adicionado com sucesso à disciplina %s.\n", getAluno(alunos, alunoEncontrado).nome, disciplinas[disciplinaEncontrada].nome);
        alunos->disciplinas++;
    } else {
        printf("Operação cancelada. O aluno não foi adicionado à disciplina.\n");
    }
}

// Função para desmatricular um aluno de uma disciplina
void desmatricularAlunoDisciplina(materias disciplinas[], pessoas *alunos, int numDisciplinas) {
    char matriculaAluno[Max_Matricula];
    char codigoDisciplina[8];

    printf("Informe o código da disciplina:\n");
    fgets(codigoDisciplina, sizeof(codigoDisciplina), stdin);
    codigoDisciplina[strcspn(codigoDisciplina, "\n")] = '\0';

    // Busca a disciplina pelo código
    int disciplinaEncontrada = -1;
    for (int i = 0; i < numDisciplinas; i++) {
        if (strcmp(getDisciplina(disciplinas, i).codigo, codigoDisciplina) == 0) {
            disciplinaEncontrada = i;
            break;
        }
    }

    if (disciplinaEncontrada == -1) {
        printf("Erro: Disciplina com código %s não encontrada.\n", codigoDisciplina);
        return;
    }

    printf("Informe a matrícula do aluno a ser desmatriculado:\n");
    fgets(matriculaAluno, sizeof(matriculaAluno), stdin);
    matriculaAluno[strcspn(matriculaAluno, "\n")] = '\0';

    int alunoEncontrado = -1;

    // Buscar o aluno pela matrícula
    for (int i = 0; i < getDisciplina(disciplinas, disciplinaEncontrada).numAlunos; i++) {
        if (strcmp(getAluno(disciplinas[disciplinaEncontrada].aluno, i).matricula, matriculaAluno) == 0) {
            alunoEncontrado = i;
            break;
        }
    }

    if (alunoEncontrado == -1) {
        printf("Erro: Aluno com matrícula %s não encontrado na disciplina %s.\n", matriculaAluno, getDisciplina(disciplinas, disciplinaEncontrada).nome);
        return;
    }

    // Solicitar confirmação
    char confirmacao;
    printf("Você tem certeza que deseja desmatricular o aluno %s? (S/N): ", getAluno(disciplinas[disciplinaEncontrada].aluno, alunoEncontrado).nome);
    scanf(" %c", &confirmacao); // Espaço antes de %c para consumir o caractere de nova linha anterior

    // Permitir que S e N sejam lidos tanto em maiúsculo quanto em minúsculo
    if (confirmacao == 'S' || confirmacao == 's') {
        // Remover aluno da disciplina
        for (int i = alunoEncontrado; i < getDisciplina(disciplinas, disciplinaEncontrada).numAlunos - 1; i++) {
            setAluno(disciplinas[disciplinaEncontrada].aluno, i, getAluno(disciplinas[disciplinaEncontrada].aluno, i + 1)); // Usar o setter para mover alunos
        }
        disciplinas[disciplinaEncontrada].numAlunos--;
        printf("Aluno desmatriculado com sucesso!\n");
        alunos->disciplinas--;
    } else {
        printf("Desmatriculação cancelada.\n");
    }
}

//Função para atualizar disciplina.
void atualizarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores) {
    char codigoBusca[9];
    int encontrou = -1;

    // Solicitar o código da disciplina a ser atualizado
    printf("Informe o código da disciplina que deseja atualizar:\n");
    getchar();
    fgets(codigoBusca, sizeof(codigoBusca), stdin);
    codigoBusca[strcspn(codigoBusca, "\n")] = '\0'; 
    toUpperString(codigoBusca); // Aceitar código tanto em maiúsculas quanto minúsculas

    // Procurar a disciplina pelo código
    for (int i = 0; i < max_Disciplinas; i++) {
        if (strcmp(disciplinas[i].codigo, codigoBusca) == 0) {
            encontrou = i;
            break;
        }
    }

    // Verificar se a disciplina foi encontrada
    if (encontrou == -1) {
        printf("Erro: Disciplina com código %s não encontrada.\n", codigoBusca);
        return;
    }

    // Confirmar se o usuário quer realmente editar a disciplina encontrada
    char confirmacao;
    printf("Você deseja realmente atualizar a disciplina %s? (S/N):\n", disciplinas[encontrou].nome);
    scanf(" %c", &confirmacao);
    getchar(); // Limpar o buffer após a leitura de caractere

    if (confirmacao != 'S' && confirmacao != 's') {
        printf("Atualização cancelada.\n");
        return;
    }

    // Atualização do nome da disciplina
    printf("Informe o novo nome da disciplina (ou pressione ENTER para manter o nome atual: %s):\n", disciplinas[encontrou].nome);
    char novoNome[50];
    fgets(novoNome, sizeof(novoNome), stdin);
    novoNome[strcspn(novoNome, "\n")] = '\0';

    if (strlen(novoNome) > 0) {
        toUpperString(novoNome);
        strcpy(disciplinas[encontrou].nome, novoNome);
        printf("Nome da disciplina atualizado.\n");
    } else {
        printf("Nome da disciplina mantido como: %s\n", disciplinas[encontrou].nome);
    }

    // Atualização do professor
    char novaMatriculaProf[15];
    printf("Informe a matrícula do novo professor (ou pressione ENTER para manter o professor atual: %s):\n", disciplinas[encontrou].professor);
    fgets(novaMatriculaProf, sizeof(novaMatriculaProf), stdin);
    novaMatriculaProf[strcspn(novaMatriculaProf, "\n")] = '\0';

    if (strlen(novaMatriculaProf) > 0) {
        strcpy(disciplinas[encontrou].professor, novaMatriculaProf);
        printf("Professor atualizado.\n");
    } else {
        printf("Professor mantido como: %s\n", disciplinas[encontrou].professor);
    }

    // Atualização do semestre
    float novoSemestre;
    printf("Informe o novo semestre (ou pressione ENTER para manter o semestre atual: %.1f):\n", disciplinas[encontrou].semestre);
    if (scanf("%f", &novoSemestre) == 1 && novoSemestre > 0) {
        disciplinas[encontrou].semestre = novoSemestre;
        printf("Semestre atualizado.\n");
    } else {
        printf("Semestre mantido como: %f\n", disciplinas[encontrou].semestre);
    }
    while (getchar() != '\n'); 

    // Atualização do número de vagas
    int novasVagas;
    printf("Informe o novo número de vagas (ou pressione ENTER para manter o número atual: %d):\n", disciplinas[encontrou].numVagas);
    if (scanf("%d", &novasVagas) == 1 && novasVagas > 0) {
        disciplinas[encontrou].numVagas = novasVagas;
        printf("Número de vagas atualizado para: %d\n", novasVagas);
    } else {
        printf("Número de vagas mantido como: %d\n", disciplinas[encontrou].numVagas);
    }
    while (getchar() != '\n'); 

    printf("Atualização concluída.\n");
}

//Atualização de pessoa
void atualizarPessoa(pessoas *cadastro, int maxPessoas, int tipoPessoa) {
    char matricula[Max_Matricula];
    printf("Informe a matrícula da pessoa a ser atualizada:\n");
    scanf("%s", matricula);
    getchar(); // Limpa o buffer do teclado

    for (int i = 0; i < maxPessoas; i++) {
        // Verifica se a matrícula corresponde à que está cadastrada
        if ((tipoPessoa == 1 && strncmp(getAluno(cadastro, i).matricula, prefixo_Aluno, strlen(prefixo_Aluno)) == 0) ||
            (tipoPessoa == 2 && strncmp(getProfessor(cadastro, i).matricula, prefixo_Professor, strlen(prefixo_Professor)) == 0)) {
            if (strcmp(getAluno(cadastro, i).matricula, matricula) == 0 || strcmp(getProfessor(cadastro, i).matricula, matricula) == 0) {
                char novoNome[50];  // Tamanho do nome conforme definido na struct
                char novoCPF[15];   // Tamanho do CPF conforme definido na struct
                char novoSexo[2];   // Buffer para o sexo, permitindo também a string vazia
                pessoas pessoaAtual = (tipoPessoa == 1) ? getAluno(cadastro, i) : getProfessor(cadastro, i);

                // Confirmação da pessoa
                printf("Você está prestes a atualizar os dados da seguinte pessoa:\n");
                printf("Nome: %s\n", pessoaAtual.nome);
                printf("Matrícula: %s\n", pessoaAtual.matricula);
                printf("Sexo: %c\n", pessoaAtual.sexo);
                printf("Data de nascimento: %02d/%02d/%04d\n", pessoaAtual.aniversario.dia, pessoaAtual.aniversario.mes, pessoaAtual.aniversario.ano);
                printf("Deseja continuar com a atualização? (S/N): ");
                char confirmacao;
                scanf(" %c", &confirmacao);
                getchar(); // Limpa o buffer do teclado
                if (confirmacao != 'S' && confirmacao != 's') {
                    printf("Atualização cancelada.\n");
                    return;
                }

                // Atualiza o nome
                printf("Digite um novo nome (ou pressione Enter para manter):\n");
                fgets(novoNome, sizeof(novoNome), stdin);
                novoNome[strcspn(novoNome, "\n")] = '\0'; // Remove a nova linha

                // Se o usuário não digitou nada, mantém o nome atual
                if (strlen(novoNome) > 0) {
                    if (validarNome(novoNome)) {
                        printf("Nome alterado de '%s' para '%s'.\n", pessoaAtual.nome, novoNome);
                        if (tipoPessoa == 1) {
                            strcpy(pessoaAtual.nome, novoNome);
                            setAluno(cadastro, i, pessoaAtual);
                        } else {
                            strcpy(pessoaAtual.nome, novoNome);
                            setProfessor(cadastro, i, pessoaAtual);
                        }
                    }
                } else {
                    printf("Nome permanece o mesmo: '%s'.\n", pessoaAtual.nome);
                }

                // Atualiza o sexo
                printf("Digite um novo sexo (M/F ou pressione Enter para manter):\n");
                fgets(novoSexo, sizeof(novoSexo), stdin);
                if (strlen(novoSexo) > 1) {
                    if (novoSexo[0] == 'M' || novoSexo[0] == 'F') {
                        printf("Sexo alterado de '%c' para '%c'.\n", pessoaAtual.sexo, novoSexo[0]);
                        pessoaAtual.sexo = novoSexo[0]; // Atualiza para o novo sexo
                        if (tipoPessoa == 1) {
                            setAluno(cadastro, i, pessoaAtual);
                        } else {
                            setProfessor(cadastro, i, pessoaAtual);
                        }
                    }
                } else {
                    printf("Sexo permanece o mesmo: '%c'.\n", pessoaAtual.sexo);
                }

                // Atualiza a data de nascimento
                printf("Informe a nova data de nascimento separada por espaço: dd mm aaaa (ou pressione enter para manter):\n");
                char dataNascimento[20];
                getchar();
                fgets(dataNascimento, sizeof(dataNascimento), stdin);
                if (sscanf(dataNascimento, "%d %d %d", &cadastro[i].aniversario.dia, &cadastro[i].aniversario.mes, &cadastro[i].aniversario.ano) == 3) {
                    printf("Data de nascimento atualizada para: %02d/%02d/%04d.\n", cadastro[i].aniversario.dia, cadastro[i].aniversario.mes, cadastro[i].aniversario.ano);
                } else {
                    printf("Data de nascimento permanece a mesma: %02d/%02d/%04d.\n", pessoaAtual.aniversario.dia, pessoaAtual.aniversario.mes, pessoaAtual.aniversario.ano);
                }

                printf("Dados atualizados com sucesso!\n");
                return;
            }
        }
    }
    printf("Matrícula não encontrada.\n");
}


// Função para excluir pessoa
void excluirPessoa(pessoas *cadastro, int *maxPessoas, int tipoPessoa) {
    char matricula[Max_Matricula];
    printf("Informe a matrícula da pessoa a ser excluída:\n");
    scanf("%s", matricula);

    for (int i = 0; i < *maxPessoas; i++) {
        // Verifica se a matrícula corresponde à que está cadastrada
        if ((tipoPessoa == 1 && strncmp(cadastro[i].matricula, prefixo_Aluno, strlen(prefixo_Aluno)) == 0) ||
            (tipoPessoa == 2 && strncmp(cadastro[i].matricula, prefixo_Professor, strlen(prefixo_Professor)) == 0)) {
            if (strcmp(cadastro[i].matricula, matricula) == 0) {
                // Encontrou a matrícula, solicita confirmação
                char confirmacao;
                printf("Você tem certeza que deseja excluir a pessoa %s? (s/n): ", cadastro[i].nome);
                scanf(" %c", &confirmacao); 

                if (confirmacao == 's' || confirmacao == 'S') {
                    // Excluindo a pessoa
                    for (int j = i; j < *maxPessoas - 1; j++) {
                        cadastro[j] = cadastro[j + 1]; // Move os registros para preencher a lacuna
                    }
                    (*maxPessoas)--; // Diminui o contador de pessoas
                    printf("Pessoa excluída com sucesso!\n");
                } else {
                    printf("Exclusão cancelada.\n");
                }
                return;
            }
        }
    }
    printf("Matrícula não encontrada.\n");
}

//Exclusão de discplina
void excluirDisciplina(materias *disciplinas, int max_Disciplinas) {
   // printf("Entrou na função excluir disciplina.\n"); // Debug
    char codigo[9]; 
    int encontrada = 0;

    // Solicita o código da disciplina a ser excluída
    printf("Informe o código da disciplina que deseja excluir:\n");
    fgets(codigo, sizeof(codigo), stdin);
    codigo[strcspn(codigo, "\n")] = '\0'; 

    // Converte o código inserido para maiúsculas
    toUpperString(codigo);

    // Procura a disciplina pelo código
    for (int i = 0; i < max_Disciplinas; i++) {
        if (strcmp(disciplinas[i].codigo, codigo) == 0) {
            encontrada = 1;

            // Verifica se há alunos matriculados
            if (disciplinas[i].numAlunos > 0) {
                printf("Não é possível excluir a disciplina, pois existem %d aluno(s) matriculado(s).\n", disciplinas[i].numAlunos);
            } else {
                // Solicita confirmação antes de excluir
                char confirmacao;
                printf("Você tem certeza que deseja excluir a disciplina %s (Cód.: %s)? (S/N)\n", disciplinas[i].nome, disciplinas[i].codigo);
                scanf(" %c", &confirmacao);
                getchar();

                if (confirmacao == 'S' || confirmacao == 's') {
                    // Exclui a disciplina, limpando os dados
                    disciplinas[i].codigo[0] = '\0'; // Marca a disciplina como não cadastrada
                    disciplinas[i].nome[0] = '\0';   // Limpa o nome da disciplina
                    disciplinas[i].semestre = 0;     // Reseta o semestre
                    disciplinas[i].numAlunos = 0;    // Reseta o número de alunos
                    printf("Disciplina excluída com sucesso!\n");
                } else {
                    printf("Exclusão da disciplina cancelada.\n");
                }
            }
            break; 
        }
    }

    if (!encontrada) {
        printf("Disciplina não encontrada.\n");
    }
}

//Função para transformar em maiusculo
void toUpperString(char *str) {
    while (*str) {
        *str = toupper(*str);  // Converte cada caractere para maiúscula
        str++;
    }
}
//----------------------------------------------------------
//Implementação de Funnções para apresentação de Relatórios
//----------------------------------------------------------

//Função para listagem de Pessoas (aluno ou professor)

void listarPessoa(pessoas *pessoa, int Max_Pessoas, int tipoPessoa, char ordenacao[20]){
    //relatórios de listagem de pessoas (alunos ou professores) - tipoPessoa: (1-aluno,2-professor);
    //ordenacao: ("nenhuma","sexo","alfabetica","nascimento","matriculaMenos3")
printf("Entrando na função listarPessoa...\n\n"); // Debug
int contador=0; //conta o número de registros que foram listados
    
    if(strcmp(ordenacao,"nenhuma")==0){
		//se a ordenação não foi especificada, listar todos os registros
        printf("Lista de %s cadastrados:\n\n", (tipoPessoa ==1) ? "Alunos":"Professores");
        for(int i = 0; i< Max_Pessoas; i ++){
            if(strcmp(pessoa[i].matricula, "")!=0){
                //se a matrícula for diferente de "", significa que a posição está ocupada
                //(matrícula não foi excluída)
                printCadastroPessoa(pessoa,i);
                contador++;
            }
        }
    }
    else if (strcmp(ordenacao,"sexo")==0){
		//se a ordenação foi especificada como por sexo)
        char sexo;
        printf("Informe o sexo que deseja listar (M para masculino e F para feminino): ");
        scanf(" %c",&sexo);
        if(sexo!='m' && sexo!='M' && sexo!='f' && sexo!='F'){
            printf("opção inválida\n");
        }
        // system("clear");
        else{
            printf("Lista de %s do sexo %s cadastrados:\n\n", (tipoPessoa ==1) ? "Alunos":"Professores", (sexo == 'M'||sexo == 'm') ? "masculino":"feminino");
            separadorTexto();
            printf("\n");
            for(int i=0;i<Max_Pessoas;i++){
                if((pessoa[i].sexo == sexo||pessoa[i].sexo == sexo-32) && strcmp(pessoa[i].matricula, "")!=0){
                    //verifica se a matrícula é diferente de "" e se o sexo é igual ao informado
                    printCadastroPessoa(pessoa,i);
                    contador++;
                }
            }
        }
    }
    else if (strcmp(ordenacao,"alfabetica")==0){ 
		// se a ordenação foi especificada como por ordem alfabética).
        //É necessário garantir que quando for feito o cadastro de um novo nome, todas as letras estejam maiúculas ou minúsculas
        pessoas alfabetica[Max_Pessoas];
        for(int i=0;i<Max_Pessoas;i++){
                alfabetica[i]=pessoa[i];
            }
        for(int i=1;i<Max_Pessoas;i++) //insertion sort para ordenar os nomes alfabeticamente
            {
                int j=i;
                while (j>0 && strcmp(alfabetica[j].nome,alfabetica[j-1].nome)<0){
                    pessoas aux = alfabetica[j];
                    alfabetica[j] = alfabetica[j-1];
                    alfabetica[j-1] = aux;
                    j--;
                }
            }
        printf("Lista de %s cadastrados em ordem alfabética:\n\n", (tipoPessoa ==1) ? "Alunos":"Professores");
        for(int i = 0; i< Max_Pessoas; i ++){
            if(strcmp(alfabetica[i].matricula, "")!=0){
                //se a matrícula for diferente de "", significa que a posição está ocupada
                //(matrícula não foi excluída)
                printCadastroPessoa(alfabetica,i);
                contador++;
            }
        }
    }
    else if (strcmp(ordenacao,"nascimento")==0){
		// se a ordenação foi especificada como por data de nascimento
        pessoas nascimento[Max_Pessoas];
        for(int i=0;i<Max_Pessoas;i++){// cópia da array para a array auxiliar de nascimento
                nascimento[i]=pessoa[i];
        }
        for(int i=1;i<Max_Pessoas;i++){ //insertion sort para ordenar por datas por ano de nascimento
            pessoas aux = nascimento[i];
            int j=i-1;
            
            while(j>=0 && nascimento[j].aniversario.ano > aux.aniversario.ano || (nascimento[j].aniversario.ano == aux.aniversario.ano && 
                nascimento[j].aniversario.mes > aux.aniversario.mes) || (nascimento[j].aniversario.ano == aux.aniversario.ano && 
                nascimento[j].aniversario.mes == aux.aniversario.mes && nascimento[j].aniversario.dia > aux.aniversario.dia)){
                //Para inverter ordem dos anos, alterar primeira comparação para nascimento.ano < aux.aniversario.ano
                nascimento[j+1] = nascimento[j];
                j--;
            }
            nascimento[j+1] = aux;
        }
        printf("Lista de %s cadastrados em ordem de nascimento:\n\n", (tipoPessoa ==1) ? "Alunos":"Professores");
        for(int i = 0; i< Max_Pessoas; i ++){
            if(strcmp(pessoa[i].matricula, "")!=0){
                //se a matrícula for diferente de "", significa que a posição está ocupada
                //(matrícula não foi excluída)
                printCadastroPessoa(nascimento,i);
                contador++;
            }
        }
    }
    else if (strcmp(ordenacao,"matriculaMenos3")==0){
		// se a ordenação foi especificada para alunos matriculados em menos de 3 disciplinas
        printf("Lista de %s matriculados em menos de três disciplinas:\n\n", (tipoPessoa ==1) ? "Alunos":"Professores");
        for(int i = 0; i< Max_Pessoas; i ++){
            if(strcmp(pessoa[i].matricula, "")!=0 && pessoa[i].disciplinas < 3){
                //se a matrícula for diferente de "", significa que a posição está ocupada
                //(matrícula não foi excluída)
                //foi necessário adicionar uma variável para contar em quantas disciplinas o aluno está matriculado
                printCadastroPessoa(pessoa,i);
                contador++;
            }
        }
    }
    if(contador == 0){
        printf("Não foram encontrados registros");
    }
}

//Função para listagem de TODAS as Pessoas (aluno e professor)

void listarTodasPessoas(pessoas *pessoas1,int Max_Pessoas1, pessoas *pessoas2, int Max_Pessoas2 ,char ordenacao[20]){
    //relatórios de listagem de todas as pessoas (alunos e professores)
    //ordenacao: ("nenhuma","aniversariantes","letras")
    
    int Max_Todas_Pessoas = Max_Pessoas1 + Max_Pessoas2;
    pessoas todos[Max_Todas_Pessoas];
    int contador=0;
    //Concatenaçãos das duas arrays
    for(int i=0;i<Max_Pessoas1;i++){
        todos[i]=pessoas1[i];
    }
    for(int i=0;i<Max_Pessoas2;i++){
        todos[Max_Pessoas1+i]=pessoas2[i];
    }
    
    //Ordenações da array concatenada conforme especificado na chamada
    if(strcmp(ordenacao,"nenhuma")==0){ 
	//se a ordenação não foi especificada, listar todos os registros
        printf("Lista de pessoas cadastradas:\n\n");
        for(int j = 0; j< Max_Todas_Pessoas; j++){
            if(strcmp(todos[j].matricula, "")!=0){
                //se a matrícula for diferente de "", significa que a posição está ocupada e a matrícula não foi excluída
                printCadastroPessoa(todos,j);
                contador++;
            }
        }
    }
    else if (strcmp(ordenacao,"aniversariantes")==0){ 
        //se a ordenação foi especificada como aniversariantes, listar os aniversariantes do mês
        time_t t = time(NULL);// Obtém o tempo atual 
        struct tm *tm_info = localtime(&t);// Converte para a estrutura tm
        int mes_atual = tm_info->tm_mon + 1;// informa o mês atual
        printf("Lista de aniversariantes do mês:\n\n");
        for(int j = 0; j< Max_Todas_Pessoas; j++){
            if(strcmp(todos[j].matricula, "")!=0 && todos[j].aniversario.mes == mes_atual){
                //se a matrícula for diferente de "", significa que a posição está ocupada e a matrícula não foi excluída
                //verifica se o mês do aniversário é o mês atual
                printCadastroPessoa(todos,j);
                contador++;
            }
        }
    }
    else if (strcmp(ordenacao,"letras")==0){
        //se a ordenação foi especificada como letras, listar os pessoas que contem as letras
        char letras[50];
        printf("Digite o nome a ser pesquisado (mínimo de 3 letras): ");
        getchar();
    	fgets(letras, sizeof(letras), stdin);
        toUpperString(letras);
        letras[strcspn(letras, "\n")] = 0;
        // system("clear");
        if(strlen(letras)<3){
        	printf("Entrada inválida. Devem ser inseridas ao menos 3 letras");
		}
		else{
			printf("Lista de pessoas que contêm as letras '%s':\n\n", letras);
		    for (int j = 0; j < Max_Todas_Pessoas; j++) {
		        if (strcmp(todos[j].matricula, "")!=0) {
		            if (strstr(todos[j].nome, letras) != NULL) {// Verifica se o nome contém a sequência de letras
		                printCadastroPessoa(todos, j);
		                contador++;
		            }
		        }
			}
    	}
	}
    if(contador == 0){
        printf("Não foram encontrados registros");
    }
}

//Função para listagem de disciplinas

void listarDisciplinas(materias *disciplina, int Max_disciplinas, char ordenacao[20]){
    //relatórios de listagem de disciplinas (cadastradas,dados de uma e disciplinas com mais de 40 vagas)
    //ordenacao: ("nenhuma","mais40","uma")

    int contador=0;
    if(strcmp(ordenacao,"nenhuma")==0){ 
		//se a ordenação não foi especificada, listar todos os registros
       printf("Lista de disciplinas cadastradas:\n\n");
       for(int i = 0; i< Max_Disciplinas; i++){
           if(strcmp(disciplina[i].codigo,"")!=0){
               //se o código for diferente de "", significa que a posição está ocupada
               //(disciplina não foi excluída)
               printCadastroDisciplina(disciplina, i, false); // print sem alunos
               contador++;
           }
       }
    }
    else if(strcmp(ordenacao,"mais40")==0){ 
		//se a ordenação foi especificada como disciplinas
		//com mais de 40 vagas
        printf("Lista de disciplinas com mais de 40 vagas cadastradas:\n\n");
        for(int i = 0; i< Max_Disciplinas; i++){
           if(strcmp(disciplina[i].codigo,"")!=0 && disciplina[i].numVagas>40){
               //se o código for diferente de "", significa que a posição está ocupada
               //(disciplina não foi excluída)
               //verifica se tem mais de 40 vagas
               printf("Disciplina: %s\t",disciplina[i].nome);
               printf("Professor responsável: %s\n",disciplina[i].professor);
               contador++;
           }
        }
    }
    else if(strcmp(ordenacao,"uma")==0){ 
		//se a ordenação foi especificada como dados de uma disciplina
        char codigo[8];
        printf("Digite o código da disciplina escolhida: \n");
        getchar();
        fgets(codigo,sizeof(codigo),stdin);
        toUpperString(codigo);
        for(int i=0; i<strlen(codigo); i++){ //Garante que todas as letras armazenadas sejam maíusculas
            if(codigo[i]>= 97 && codigo[i]<=122){
                codigo[i]= codigo[i]-32;
            }
        }
        codigo[strcspn(codigo, "\n")] = '\0';
        // system("clear");
        for(int i = 0; i< Max_Disciplinas; i++){
           if(strcmp(disciplina[i].codigo,"")!=0 && strcmp(disciplina[i].codigo,codigo)==0){
               //se o código for diferente de "", significa que a posição está ocupada
               //(disciplina não foi excluída)
               printCadastroDisciplina(disciplina, i, true); // print com alunos
               contador++;
           }
        }
    }
    if(contador == 0){
        printf("Não foram encontrados registros");
    }
}


// função de espera
void espera(){
    char tecla='.';
    printf("\ninsira '0' para voltar ao menu\n");
    while(tecla!='0'){
        scanf("%c",&tecla);
    }
    
}

//----------------------------------------------------------------------------
//main
//----------------------------------------------------------------------------


int main(void) {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    // Inicialização de listas
    pessoas aluno[Max_Alunos] = {0}; // Inicializa o array com zeros
    pessoas professor[Max_Professores] = {0}; // Inicializa o array com zeros
    materias disciplinas[Max_Disciplinas] = {0}; // Inicializa o array com zeros
    
    int maxAlunos = Max_Alunos;
    int maxProfessores = Max_Professores;


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
                            break;
                        }
                        case 2: { //Atualizar dados de aluno
                            atualizarPessoa(aluno, Max_Alunos, 1);
                            break;
                        }
                        case 3: { //Excluir aluno
                            excluirPessoa(aluno, &maxAlunos, 1);
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
                            break;
                        }
                        case 2: { //Atualizar dados de professor
                            atualizarPessoa(professor, Max_Professores, 2);
                            break;
                        }
                        case 3: { //Excluir professor
                            excluirPessoa(professor, &maxProfessores, 2);
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
                            atualizarDisciplina(disciplinas, Max_Disciplinas, professor, Max_Professores);
                            break;
                        }
                        case 3: { //Excluir disciplina
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
                            char matriculaAluno[15];
    
                            printf("Informe a matrícula do aluno que deseja matricular:\n");
                            getchar(); // Consome o newline deixado por scanf
                            fgets(matriculaAluno, sizeof(matriculaAluno), stdin);
                            matriculaAluno[strcspn(matriculaAluno, "\n")] = '\0'; // Remove o newline

                            // Verifica se existe espaço na disciplina
                            if (disciplinas[0].numAlunos < Max_Alunos_Disciplinas) {
                                adicionarAlunoDisciplina(&disciplinas[0], Max_Disciplinas, aluno, Max_Alunos, matriculaAluno);
                            } else {
                                printf("Não há espaço na disciplina para adicionar mais alunos.\n");
                            }
                            break;
                        }
                            
                        
                        case 2: { //Desmatricular aluno de uma disciplina
                            desmatricularAlunoDisciplina(disciplinas, aluno, Max_Disciplinas);
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
                            listarPessoa(aluno,strlen(aluno),1,"nenhuma");
                            espera();
                            break;
                        }
                        case 2: { //listagem de alunos por sexo
                            //inserir função para listagem de pessoas(alunos) por sexo informado
                            listarPessoa(aluno,strlen(aluno),1,"sexo");
                            espera();
                            break;
                        }
                        case 3: { //listagem de alunos por ordem alfabética
                            //inserir função para listagem de pessoas(alunos) com ordenação do vetor em ordem alfabética
                            listarPessoa(aluno,strlen(aluno),1,"alfabetica");
                            espera();
                            break;
                        }
                        case 4: { // listagem de alunos por ordem de nascimento
                            //inserir função para listagem de pessoas(alunos) com ordenação do vetor em ordem de nascimento
                            listarPessoa(aluno,strlen(aluno),1,"nascimento");
                            espera();
                            break;
                        }
                        case 5: { // listagem de alunos matriculados em menos de 3 disciplinas
                            //inserir função para listagem de alunos matriculados em menos de 3 disciplinas
                            listarPessoa(aluno,strlen(aluno),1,"matriculaMenos3");
                            espera();
                            break;
                        }
                        case 6: { //listagem de professor sem ordenação do vetor
                            //inserir função para listagem de pessoas(professor) sem ordenação do vetor
                            listarPessoa(professor,strlen(professor),2,"nenhuma");
                            espera();
                            break;
                        }
                        case 7: { //listagem de professor por sexo
                            //inserir função para listagem de pessoas(professor) por sexo informado
                            listarPessoa(professor,strlen(professor),2,"sexo");
                            espera();
                            break;
                        }
                        case 8: { //listagem de professor por ordem alfabética
                            //inserir função para listagem de pessoas(professor) com ordenação do vetor em ordem alfabética
                            listarPessoa(professor,strlen(professor),2,"alfabetica");
                            espera();
                            break;
                        }
                        case 9: { // listagem de professor por ordem de nascimento
                            //inserir função para listagem de pessoas(professor) com ordenação do vetor em ordem de nascimento
                            listarPessoa(professor,strlen(professor),2,"nascimento");
                            espera();
                            break;
                        }
                        case 10: { //listagem de disciplinas cadastradas
                            //inserir função para listagem de todas as disciplinas cadastradas (nomes das disciplinas)
                            listarDisciplinas(disciplinas,strlen(disciplinas),"nenhuma");
                            espera();
                            break;
                        }
                        case 11: { //listagem de disciplinas com mais de 40 vagas
                            //inserir função para listagem de disciplinas com mais de 40 vagas e pofessor correspondente (nome da disciplina e nome do professor)
                            listarDisciplinas(disciplinas,strlen(disciplinas),"mais40");
                            espera();
                            break;
                        }
                        case 12: { //listagem dos dados de uma disciplina
                            //inserir função para listagem de todos os dados de uma disciplina selecionada pelo usuário
                            listarDisciplinas(disciplinas,strlen(disciplinas),"uma");
                            espera();
                            break;
                        }
                        case 13: { //listagem dos aniversariantes do mês
                            //inserir função para listagem de todos as pessoas que fazem aniversário no mês corrente e suas respectivas datas de aniversário (dia/mês)
                            listarTodasPessoas(aluno,strlen(aluno),professor,strlen(professor),"aniversariantes");
                            espera();
                            break;
                        }
                        case 14: { //listagem de todas as pessoas cadastradas
                            //inserir função para listagem de pessoas(todas) com base nas letras informadas
                            listarTodasPessoas(aluno,strlen(aluno),professor,strlen(professor),"letras");
                            espera();
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
