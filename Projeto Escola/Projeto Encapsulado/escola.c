#include "escola.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
    }
    separadorTexto();
    printf("\n");
}

// Implementação de menus
int menu(char tipoMenu[20]) {
    int opcao;
    if (strcmp(tipoMenu, "principal") == 0) {
        printf("0 - Sair\n");
        printf("1 - Aluno\n");
        printf("2 - Professor\n");
        printf("3 - Disciplina\n");
        // Adicione mais opções se necessário
    } else if (strcmp(tipoMenu, "cadastro") == 0) {
        printf("1 - Cadastrar\n");
        // Adicione mais opções se necessário
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
    sprintf(matricula, "%s%04d", prefixo_Aluno, contadorAluno + 1);
    contadorAluno++; // Incrementa o contador
}

//Função para gerar a matrícula para professor
void gerarMatriculaProfessor(char matricula[]) {
    sprintf(matricula, "%s%04d", prefixo_Professor, contadorProfessor + 1);
    contadorProfessor++; // Incrementa o contador
}

// Implementação da função de cadastro de pessoa
void cadastrarPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa) {
    printf("Entrou na função cadastrarPessoa\n"); // Debug
    int i;
    for (i = 0; i < maxPessoas; i++) {
        if (cadastro[i].matricula[0] == 0) {  // Verifica se o campo matrícula está vazio
            if (tipoPessoa == 1) {
                printf("Cadastro de Aluno:\n\n");

                //Gera a matrícula do Aluno
                gerarMatriculaAluno(cadastro[i].matricula);
                printf("Matrícula gerada: %s\n", cadastro[i].matricula);
            } else if (tipoPessoa == 2) {

                printf("Cadastro de Professor:\n");
                //Matricula professor 
                gerarMatriculaProfessor(cadastro[i].matricula);
                printf("Matricula gerada: %s\n", cadastro[i].matricula);
            }

            // Loop para o nome
            do {
                printf("Informe o nome:\n");
                scanf(" %[^\n]", cadastro[i].nome);
            } while (!validarNome(cadastro[i].nome)); // Continua pedindo até um nome válido

            // Loop para o CPF
            do {
                printf("Informe o CPF:\n");
                scanf("%s", cadastro[i].cpf);
            } while (!validarCPF(cadastro[i].cpf)); // Continua pedindo até um CPF válido

            // Loop para o sexo
            do {
                printf("Informe o sexo (M/F):\n");
                scanf(" %c", &cadastro[i].sexo); // Corrige o uso do scanf para ler char corretamente
            } while (!validarSexo(cadastro[i].sexo)); // Continua pedindo até um sexo válido

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


// Implementação da função de cadastro de disciplina
void cadastrarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores) {
  for(int i = 0; i < max_Disciplinas; i++){
    if(disciplinas[i].codigo[0] == '\0'){ // Verifica se a disciplina foi cadastrada
      printf ("Cadastro de Disciplina:\n");

      printf("Informe o nome da disciplina:\n");
      scanf(" %[^\n]", disciplinas[i].nome);


      printf("Informe o código da disciplina (máx 8 caracteres):\n");
      scanf("%s", &disciplinas[i].codigo);

      printf("Informe o semestre da disciplina:\n");
      scanf("%d", &disciplinas[i].semestre);

      printf("Selecione o professor pelo número da matrícula: \n");
      for(int j = 0; j<max_Professores; j++){
        printf("%d - %s .\n", professores[j].matricula, professores[j].nome);
      }
      char matriculaProf[11]; 
      scanf("%s", matriculaProf);

      //Procura o professor pela matricula e atrela a disciplina

      int encontrou=0;
      for(int j = 0; j < Max_Professores; j++){
        if(strcmp(professores[j].matricula, matriculaProf)==0){
          strcpy(disciplinas[i].professor, professores[j].nome);
          encontrou = 1 ;
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

  //Função para validar nome
  int validarNome(char nome[]){
    if(strlen(nome)<3){
        printf("Erro: O nome deve ter pelo menos 3 caracteres.\n");
        return 0;
    }
    return 1;
  }

  //Função validar CPF
  int validarCPF(char cpf[]){
    if(strlen(cpf)!=11 ){
        printf("Erro: O CPF deve ser informado com 11 dígitos.\n");
        return 0;
    }
    return 1;
  }

  //Função Validar Sexo
  int validarSexo(char sexo){
    if(sexo != 'M' && sexo != 'F'){
        printf("Sexo inválido. use 'M' para sexo masculino ou 'F' para o sexo feminino.\n");
        return 0;
    }
    return 1;
  }
  
  //Função validar data
  int validarData(data aniversario){
    if(aniversario.dia<1 || aniversario.dia>31 || aniversario.mes <1 || aniversario.mes >12 || aniversario.ano < 1900){
        printf("Data de nascimento inválida.\n");
        return 0;
    }
    return 1;
  }

void atualizarPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa){
    char matricula[12];
    printf("Informe o número da matrícula do %s que deseja atualizar os dados.\n", (tipoPessoa ==1) ? "aluno":"professor");
    scanf("%s", matricula);

    for(int i = 0; i < maxPessoas; i++){
        if(strcmp(cadastro[i].matricula, matricula)==0){ //Compara a matricula e lista os dados previamente inseridos
            printf("Cadastro encontrado:\n");
            printf("Nome: %s/n", cadastro[i].nome);
            printf("CPF: %s/n", cadastro[i].cpf);
            printf("Data de Nascimento: %02d/%02d/%04d\n", cadastro[i].aniversario.dia , cadastro[i].aniversario.mes, cadastro[i].aniversario.ano);

        //Atualiza o nome
        printf("Informe o novo nome (deixe em branco para não alterar.)\n");
        char novoNome[50];
        scanf(" %[^\n]", novoNome);
        if (strlen(novoNome) > 0) { // Se o nome não estiver vazio
                strcpy(cadastro[i].nome, novoNome);
            }

        //Atualiza o CPF
        printf("Informe o novo cpf (deixe em branco para não alterar.)\n");
        char novoCPF[15];
        scanf("%s", novoCPF);
        if(strlen(novoCPF)>0){
            strcpy(cadastro[i].cpf, novoCPF);
        }

        //Atualiza a data de nascimento
        printf("Informe a nova de data de nascimento separada por espaço: dd mm aaaa (ou pressione enter para manter.)\n");
        int novoDia, novoMes, novoAno; 
        if(scanf("%d %d %d", &novoDia, &novoMes, &novoAno)==3){
            cadastro[i].aniversario.dia = novoDia;
            cadastro[i].aniversario.mes = novoMes;
            cadastro[i].aniversario.ano = novoAno;
        }

        printf("%s atualizado com sucesso.\n", tipoPessoa == 1 ? "Aluno": "Professor");
        return;
        }
    }

    printf("%s não encontrado.", tipoPessoa == 1 ? "Aluno": "Professor");

}

