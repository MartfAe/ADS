
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <locale.h>

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
    char sexo, nome[50], cpf[15];
    data aniversario;
} pessoas;

typedef struct {
    char nome[50], codigo[8], professor[50];
    int semestre;
    pessoas aluno[Max_Alunos_Disciplinas];
    int numAlunos;
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
int validarSemestre(int semestre);


int contadorAluno = 0; // Contador de alunos
int contadorProfessor = 0; // Contador de professores

// Implementação de separador
void separadorTexto(void) {
    printf("\n");
    for (int i = 0; i < 70; i++) {
        printf("-");
    }
}

// Implementação de cabeçalho
void cabecalho(char nomeMenu[20]) {
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

// Implementação dos Getters e Setters
pessoas getAluno(pessoas alunos[], int index) {
    return alunos[index];
}

void setAluno(pessoas alunos[], int index, pessoas novoAluno) {
    if (strlen(novoAluno.nome) > 0 && strlen(novoAluno.cpf) == 11) {
        alunos[index] = novoAluno;
        printf("Aluno atualizado com sucesso!\n");
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
        printf("Disciplina atualizada com sucesso!\n");
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

// Implementação da função de cadastro de pessoa
void cadastrarPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa) {
    printf("Entrou na função cadastrarPessoa\n"); // Debug
    int i;
    for (i = 0; i < maxPessoas; i++) {
        if (cadastro[i].matricula[0] == 0) {  // Verifica se o campo matrícula está vazio
            if (tipoPessoa == 1) {
                printf("Cadastro de Aluno:\n\n");

                // Gera a matrícula do Aluno
                gerarMatriculaAluno(cadastro[i].matricula);
                printf("Matrícula gerada: %s\n", cadastro[i].matricula);
            } else if (tipoPessoa == 2) {
                printf("Cadastro de Professor:\n");
                // Matrícula professor 
                gerarMatriculaProfessor(cadastro[i].matricula);
                printf("Matrícula gerada: %s\n", cadastro[i].matricula);
            }

            // Loop para o nome
            do {
                printf("Informe o nome:\n");
                fgets(cadastro[i].nome, sizeof(cadastro[i].nome), stdin);
                cadastro[i].nome[strcspn(cadastro[i].nome, "\n")] = '\0';
            } while (!validarNome(cadastro[i].nome)); 

            // Loop para o CPF
            do {
                printf("Informe o CPF:\n");
                fgets(cadastro[i].cpf, sizeof(cadastro[i].cpf), stdin);
                cadastro[i].cpf[strcspn(cadastro[i].cpf, "\n")] = '\0';
            } while (!validarCPF(cadastro[i].cpf));
            
            // Loop para o sexo
            do {
                printf("Informe o sexo (M/F):\n");
                scanf(" %c", &cadastro[i].sexo); // Adicionando espaço para evitar problemas com '\n' no buffer
            } while (!validarSexo(cadastro[i].sexo));

            // Loop para a data de nascimento
            do {
                printf("Informe a data de nascimento separada por um espaço (dd mm aaaa):\n");
                scanf("%d %d %d", &cadastro[i].aniversario.dia, &cadastro[i].aniversario.mes, &cadastro[i].aniversario.ano);
            } while (!validarData(cadastro[i].aniversario)); // Continua pedindo até uma data válida

            if (tipoPessoa == 1) {
                printf("Aluno cadastrado com sucesso!\n");
            } else if (tipoPessoa == 2) {
                printf("Professor cadastrado com sucesso!\n");
            }

            break;  // Sai do loop após o cadastro
        }
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

//Função para validar nome
  int validarNome(char nome[]){
    printf("Entrou na função validarNome.\n");//debug
    if(strlen(nome)<3){
        printf("Erro: O nome deve ter pelo menos 3 caracteres.\n");
        return 0;
    }
    return 1;
  }

//Função validar CPF
  int validarCPF(char cpf[]){
    printf("Entrou na função validarCPF.\n");//debug
    if(strlen(cpf)!=14 ){
        printf("Erro: O CPF deve ser informado com 14 dígitos.\n");
        return 0;
    }
    return 1;
  }

//Função Validar Sexo
  int validarSexo(char sexo){
    printf("Entrou na função validarSexo.\n");//debug
    if(sexo != 'M' && sexo != 'F'){
        printf("Sexo inválido. use 'M' para sexo masculino ou 'F' para o sexo feminino.\n");
        return 0;
    }
    return 1;
  }
  
//Função validar data
  int validarData(data aniversario){
    printf("Entrou na função validarData.\n");//debug
    if(aniversario.dia<1 || aniversario.dia>31 || aniversario.mes <1 || aniversario.mes >12 || aniversario.ano < 1900){
        printf("Data de nascimento inválida.\n");
        return 0;
    }
    return 1;
  }

// Implementação da função de cadastro de disciplina
void cadastrarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores) {
    printf("Entrou na função cadastro de disciplina.\n");//Debug
    for(int i = 0; i < max_Disciplinas; i++){
        if(disciplinas[i].codigo[0] == '\0'){ // Verifica se a disciplina foi cadastrada
            printf ("Cadastro de Disciplina:\n");
    
            printf("Informe o nome da disciplina:\n");
            fgets(disciplinas[i].nome, sizeof(disciplinas[i].nome), stdin);
            disciplinas[i].nome[strcspn(disciplinas[i].nome, "\n")] = '\0';

            printf("Informe o código da disciplina (máx 8 caracteres):\n");
            fgets(disciplinas[i].codigo, sizeof(disciplinas[i].codigo), stdin);
            disciplinas[i].codigo[strcspn(disciplinas[i].codigo, "\n")] = '\0'; 

            printf("Informe o semestre da disciplina:\n");
            scanf("%d", &disciplinas[i].semestre);
            getchar();

            printf("Selecione o professor pelo número da matrícula:\n");
            for (int j = 0; j < max_Professores; j++) {
                printf("%s - %s\n", professores[j].matricula, professores[j].nome);
            }
            char matriculaProf[12];
            fgets(matriculaProf, sizeof(matriculaProf), stdin);
            matriculaProf[strcspn(matriculaProf, "\n")] = '\0';

      //Procura o professor pela matricula e atrela a disciplina

           int encontrou = 0;
            for (int j = 0; j < max_Professores; j++) {
                if (strcmp(professores[j].matricula, matriculaProf) == 0) {
                    strcpy(disciplinas[i].professor, professores[j].nome);
                    encontrou = 1;
                    break;
                }
            }

            if(!encontrou){
                printf("Professor não encontrado.\n");
            }else{
                disciplinas[i].numAlunos=0;
                printf("Disciplina cadastrada com sucesso!\n");
            }

        }
    }
  }

//Função para adicionar aluno em uma disciplina
void adicionarAlunoDisciplina(materias *disciplina, int maxDisciplinas, pessoas *alunos, int maxAlunos, char matriculaAluno[]) {
    int alunoEncontrado = -1;
    
    // Buscar o aluno pela matrícula
    for (int i = 0; i < maxAlunos; i++) {
        if (strcmp(alunos[i].matricula, matriculaAluno) == 0) {
            alunoEncontrado = i;
            break;
        }
    }

    if (alunoEncontrado == -1) {
        printf("Erro: Aluno com matrícula %s não encontrado.\n", matriculaAluno);
        return;
    }

    // Verificar limite de alunos na disciplina
    if (disciplina->numAlunos >= Max_Alunos_Disciplinas) {
        printf("Erro: A disciplina já atingiu o limite de alunos.\n");
        return;
    }

    // Adicionar aluno na disciplina
    disciplina->aluno[disciplina->numAlunos] = alunos[alunoEncontrado];
    disciplina->numAlunos++;
    printf("Aluno %s adicionado com sucesso à disciplina %s.\n", alunos[alunoEncontrado].nome, disciplina->nome);
}

// Função para desmatricular um aluno de uma disciplina
void desmatricularAlunoDisciplina(materias disciplinas[], int numDisciplinas) {
    char matriculaAluno[Max_Matricula];
    char codigoDisciplina[8];

    printf("Informe o código da disciplina:\n");
    fgets(codigoDisciplina, sizeof(codigoDisciplina), stdin);
    codigoDisciplina[strcspn(codigoDisciplina, "\n")] = '\0';

    // Busca a disciplina pelo código
    int disciplinaEncontrada = -1;
    for (int i = 0; i < numDisciplinas; i++) {
        if (strcmp(disciplinas[i].codigo, codigoDisciplina) == 0) {
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
    for (int i = 0; i < disciplinas[disciplinaEncontrada].numAlunos; i++) {
        if (strcmp(disciplinas[disciplinaEncontrada].aluno[i].matricula, matriculaAluno) == 0) {
            alunoEncontrado = i;
            break;
        }
    }

    if (alunoEncontrado == -1) {
        printf("Erro: Aluno com matrícula %s não encontrado na disciplina %s.\n", matriculaAluno, disciplinas[disciplinaEncontrada].nome);
        return;
    }

    // Solicitar confirmação
    char confirmacao;
    printf("Você tem certeza que deseja desmatricular o aluno %s? (S/N): ", disciplinas[disciplinaEncontrada].aluno[alunoEncontrado].nome);
    scanf(" %c", &confirmacao); // Espaço antes de %c para consumir o caractere de nova linha anterior

    if (confirmacao == 'S' || confirmacao == 's') {
        // Remover aluno da disciplina
        for (int i = alunoEncontrado; i < disciplinas[disciplinaEncontrada].numAlunos - 1; i++) {
            disciplinas[disciplinaEncontrada].aluno[i] = disciplinas[disciplinaEncontrada].aluno[i + 1];
        }
        disciplinas[disciplinaEncontrada].numAlunos--;
        printf("Aluno desmatriculado com sucesso!\n");
    } else {
        printf("Desmatriculação cancelada.\n");
    }
}

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