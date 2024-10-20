#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

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

int main(void) {
// Inicialização das listas de pessoas e disciplinas
    pessoas aluno[Max_Alunos];
    pessoas professor[Max_Professores];
    materias disciplinas[Max_Disciplinas];

    bool encerrar = false;
    while (!encerrar)
        {
            int opcao = 6;
            cabecalho('principal');
            opcao = menu('principal');
            switch (opcao) {
                case 0: {
                    encerrar = true;
                    break;
                }
                case 1: {
                    cabecalho('aluno');
                    opcao = menu('cadastro');
                    //tratamento das opções do menu aluno
                    break;
                }
                case 2: {
                    cabecalho('professor');
                    opcao = menu('cadastro');
                    //tratamento das opções do menu professor
                    break;
                }
                case 3: {
                    cabecalho('disciplina');
                    opcao = menu('cadastro');
                    //tratamento das opções do menu disciplina
                    break;
                }
                case 4: {
                    cabecalho('ajuste');
                    opcao = menu('ajuste');
                    //tratamento das opções do menu ajuste de matrículas
                    break;
                }
                case 5:{
                    cabecalho('relatorio');
                    opcao = menu('ajuste');
                    //tratamento das opções do menu relatórios
                }
                default: {
                    printf("Opção inválida.");
            }
        }

}

//---------------------------
//Funções de Interface
//---------------------------

void separadorTexto(void) {
    for(int i=0;i<30;i++) {
        printf("\n");
        printf("-");
    }
}

// Função para apresentação dos cabeçalhos dos menus
void cabecalho(char nomeMenu[20]) {
    separadorTexto();
    if(nomeMenu == 'principal') {
        printf("\t\t\tProjeto Escola\t\t\t");
    }
    else if(nomeMenu == 'professor') {
        printf("\t\t\tProfessor\t\t\t");
    }
    else if(nomeMenu == 'aluno') {
        printf("\t\t\tAluno\t\t\t");
    }
    else if(nomeMenu == 'disciplina') {
        printf("\t\t\tDisciplina\t\t\t");
    }
    else if(nomeMenu == 'ajuste') {
        printf("\t\tAjuste de Matrículas\t\t");
    }
    else if(nomeMenu == 'relatorio') {
        printf("\t\t\tRelatórios\t\t\t");
    }
    separadorTexto();
}

//função para apresentação e registro de opções nos menus
int menu(char tipoMenu[20]) {
    int opcao;
    separadorTexto();
    if(tipoMenu == 'principal') {
        printf("0 - Sair\n");
        printf("1 - Aluno\n");
        printf("2 - Professor\n");
        printf("3 - Disciplina\n");
        printf("4 - Ajuste de matrículas em disciplinas\n");
        printf("5 - Relatório\n");
        separadorTexto();
        scanf("%d", &opcao);
    }
    else if(tipoMenu == 'cadastro') {
        printf("0 - Voltar\n");
        printf("1 - Cadastrar\n");
        printf("2 - Atualizar\n");
        printf("3 - Excluir\n");
        scanf("%d", &opcao);
        printf("\n\n");
    }
    else if(tipoMenu == 'ajuste') {
        printf("0 - Voltar\n");
        printf("1 - Matricular aluno em uma disciplina\n");
        printf("3 - Desmatricular aluno de uma disciplina\n");
        scanf("%d", &opcao);
        printf("\n\n");
    }
    else if(tipoMenu == 'relatorio') {
        printf("0 - Voltar\n");
        
        printf("1 - Listar alunos\n");
        printf("2 - Listar alunos por sexo\n");
        printf("3 - Listar alunos em ordem alfabética\n");
        printf("4 - Listar alunos em ordem de nascimento\n");
        printf("5 - Listar alunos matriculados em menos de 3 disciplinas\n");
        
        printf("6 - Listar professores\n");
        printf("7 - Listar professores por sexo\n");
        printf("8 - Listar professores em ordem alfabética\n");
        printf("9 - Listar professores em ordem de nascimento\n");
        
        printf("10 - Listar disciplinas\n");
        printf("11 - Listar dados de um disciplina\n");
        printf("12 - Listar disciplinas que ultrapassam 40 vagas e professores responsáveis\n");
        
        printf("13 - Listar aniversariantes do mês\n");
        printf("14 - Listar todas as pessoas cadastradas\n");
        
        scanf("%d", &opcao);
        printf("\n\n");
    }
    separadorTexto();
    return opcao;
}

//---------------------------
//Funções de funcionamento (sei que esse não é o nome certo, só esqueci qual é kkkkkkk)
//---------------------------

//Função para o cadastro de alunos ou professores
void cadastrarPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa)  {
    int i;
    for (i = 0; i < maxPessoas; i++) {
        if (cadastro[i].matricula == 0) {  // Verifica se o campo matrícula está vazio
            if (tipoPessoa == 1) {
                printf("Cadastro de Aluno:\n\n");
            } else if (tipoPessoa == 2) {
                printf("Cadastro de Professor:\n");
            }

            printf("Informe o nome:\n");
            scanf(" %[^\n]", cadastro[i].nome);
            
            // Substituir cadastro de matrícula por autoincremento
            printf("Informe a matrícula:\n");
            scanf("%d", &cadastro[i].matricula);

            printf("Informe o CPF:\n");
            scanf("%s", cadastro[i].cpf);

            printf("Informe o sexo (M/F):\n");
            scanf(" %c", &cadastro[i].sexo);  // Corrige o uso do scanf para ler char corretamente

            printf("Informe a data de nascimento separada por um espaço (dd mm aaaa):\n");
            scanf("%d %d %d", &cadastro[i].aniversario.dia, &cadastro[i].aniversario.mes, &cadastro[i].aniversario.ano);//verificar se é possível substituir por gets

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

//função para o cadastro de disciplinas
void cadastrarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores) {
  for(int i = 0; i < max_Disciplinas; i++){
    if(disciplinas[i].codigo[0 == '\0']){ //Verifica se a disciplina foi cadastrada
      printf ("Cadastro de Disciplina:\n");

      printf("Informe o nome da disciplina:\n");
      scanf("%[/n]", &disciplinas[i].nome);

      printf("Informe o código da disciplina (máx 8 caracteres):\n");
      scanf("%s", &disciplinas[i].codigo);

      printf("Informe o semestre da disciplina:\n");
      scanf("%d", &disciplinas[i].semestre);

      printf("Selecione o professor pelo número da matrícula: \n");
      for(int j = 0; j<max_Professores; j++){
        printf("%d - %s .\n", professores[j].matricula, professores[j].nome);
      }
      int matriculaProf; 
      scanf("%d", &matriculaProf);

      //Procura o professor pela matricula e atrela a disciplina

      int encontrou=0;
      for(int j = 0; j < Max_Professores; j++){
        if(professores[j].matricula == matriculaProf){
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


//remover função (substituir por cadastrar pessoa e cadastrar disciplina no main)
int cadastrar(int tipoCadastrar) {
    // Fazer cadastro conforme tipo informado

    switch (tipoCadastrar) {
        case 1: {
            cadastrarPessoa(aluno, Max_Alunos, 1);
            break;
        }
        case 2: {
            cadastrarPessoa(professor, Max_Professores, 2);
            break;
        }
        case 3: {
            cadastrarDisciplina(disciplinas, Max_Disciplinas, professor, Max_Professores);
            break;
        }
    }
    return 0;
}
