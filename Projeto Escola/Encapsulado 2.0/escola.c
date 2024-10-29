#include "escola.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>


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

// Função para verificar se a matrícula é válida
int verificarMatricula(long long matricula, pessoas *cadastro, int Max_Pessoas) {
    // Verifica se a matrícula é válida
    if (matricula < 100000 || matricula > 999999) {
        return 0; // Matrícula inválida
    }

    // Verifica se a matrícula começa com os prefixos válidos
    if (matricula / 10000 != prefixo_Aluno && matricula / 10000 != prefixo_Professor) {
        return 0; 
    }

    // Verifica se a matrícula está cadastrada
    for (int i = 0; i < Max_Pessoas; i++) {
        if (cadastro[i].matricula == matricula) {
            return 1; // Matrícula cadastrada
        }
    }
    return 0; // Matrícula não cadastrada
}

// Gerar a matrícula do aluno
void gerarMatriculaAluno(long long *matricula) {
    static int contadorAluno = 0; // Inicialização estática para manter o valor entre chamadas
    *matricula = (prefixo_Aluno + (++contadorAluno)); // Combina o prefixo e o contador
    printf("Matrícula do aluno gerada: %d\n", *matricula); // Exibe a matrícula gerada
}


// Gerar a matrícula do professor
void gerarMatriculaProfessor(long long *matricula) {
     static int contadorProfessor = 0;
    *matricula = prefixo_Professor + (++contadorProfessor); // Combina o prefixo e o contador
    printf("Matrícula do professor gerada: %lld\n", *matricula);
}

// Cadastrar pessoa
void cadastrarPessoa(pessoas *cadastro, int maxPessoas, int tipoPessoa) {
    for (int i = 0; i < maxPessoas; i++) {
        if (cadastro[i].matricula == 0) {  // Verifica se o campo matrícula está vazio
            if (tipoPessoa == 1) {
                gerarMatriculaAluno(&cadastro[i].matricula);
            } else if (tipoPessoa == 2) {
                gerarMatriculaProfessor(&cadastro[i].matricula);
            }

            // Loop para o nome
            do {
                printf("Informe o nome:\n");
                fgets(cadastro[i].nome, sizeof(cadastro[i].nome), stdin);
                cadastro[i].nome[strcspn(cadastro[i].nome, "\n")] = '\0';
            } while (!validarNome(cadastro[i].nome)); // Continua pedindo até um nome válido 

            // Loop para o CPF
            do {
                printf("Informe o CPF no formato xxx.xxx.xxx-xx :\n");
                fgets(cadastro[i].cpf, sizeof(cadastro[i].cpf), stdin);
                cadastro[i].cpf[strcspn(cadastro[i].cpf, "\n")] = '\0';
            } while (!validarCPF(cadastro[i].cpf)); // Continua pedindo até um CPF válido

            // Loop para o sexo
            do {
                printf("Informe o sexo (M/F):\n");
                scanf(" %c", &cadastro[i].sexo); 
            } while (!validarSexo(cadastro[i].sexo));

            // Loop para a data de nascimento
            do {
                printf("Informe a data de nascimento separada por um espaço (dd mm aaaa):\n");
                scanf("%d %d %d", &cadastro[i].aniversario.dia, &cadastro[i].aniversario.mes, &cadastro[i].aniversario.ano);
                getchar();
            } while (!validarData(cadastro[i].aniversario)); // Continua pedindo até uma data válida

            // Mensagem de sucesso
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
//Função cadastrar disciplina
void cadastrarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores) {
    printf("Entrou na função cadastro de disciplina.\n"); // Debug
    for (int i = 0; i < max_Disciplinas; i++) {
        if (disciplinas[i].codigo[0] == '\0') { // Verifica se a disciplina não foi cadastrada
            printf("Cadastro de Disciplina:\n");

            printf("Informe o nome da disciplina:\n");
            fgets(disciplinas[i].nome, sizeof(disciplinas[i].nome), stdin);
            disciplinas[i].nome[strcspn(disciplinas[i].nome, "\n")] = '\0';

            printf("Informe o código da disciplina (máx 8 caracteres):\n");
            fgets(disciplinas[i].codigo, sizeof(disciplinas[i].codigo), stdin);
            disciplinas[i].codigo[strcspn(disciplinas[i].codigo, "\n")] = '\0';

            // Verifica se o código da disciplina não excede 8 caracteres
            if (strlen(disciplinas[i].codigo) > 8) {
                printf("Código da disciplina deve ter no máximo 8 caracteres.\n");
                return; // Indica erro no código
            }

            printf("Informe o semestre da disciplina:\n");
            scanf("%d", &disciplinas[i].semestre);
            getchar(); // Para limpar o buffer do stdin

            // Verifica se o semestre é válido
            if (disciplinas[i].semestre <= 0) {
                printf("Semestre inválido. Deve ser um número positivo.\n");
                return; // Indica erro no semestre
            }

            printf("Selecione o professor pelo número da matrícula:\n");
            for (int j = 0; j < max_Professores; j++) {
                if (professores[j].matricula != 0) { // Verifica se o professor tem matrícula
                    printf("%d - %s\n", professores[j].matricula, professores[j].nome); // Alterado para int
                }
            }

            int matriculaProf;
            scanf("%d", &matriculaProf); // Lê a matrícula como um int

            // Verifica o prefixo da matrícula do professor
            if (matriculaProf / 1000000 != 2024117) { // Verifica se o prefixo está correto
                printf("Matrícula do professor inválida (prefixo errado).\n");
                return; // Indica erro na matrícula
            }

            // Verifica se a matrícula do professor existe
            int encontrou = 0;
            for (int j = 0; j < max_Professores; j++) {
                if (professores[j].matricula == matriculaProf) {
                    strcpy(disciplinas[i].professor, professores[j].nome);
                    encontrou = 1;
                    break;
                }
            }

            if (!encontrou) {
                printf("Professor não encontrado.\n");
                return; // Indica erro, professor não encontrado
            } else {
                disciplinas[i].alunos = 0; // Inicializa o número de alunos
                printf("Disciplina cadastrada com sucesso!\n");
                return; // Indica sucesso
            }
        }
    }
    printf("Erro: limite de disciplinas atingido.\n");
}

// Função para adicionar aluno em uma disciplina
void adicionarAlunoDisciplina(materias *disciplina, pessoas *alunos, int max_Alunos) {
    printf("Entrou na função adicionarAlunoDisciplina.\n"); // Debug

    // Verifica se a disciplina ainda tem espaço para mais alunos
    if (disciplina->alunos >= Max_Alunos_Disciplinas) {
        printf("A disciplina já atingiu o número máximo de alunos.\n");
        return; // Sai da função se não há espaço
    }

    // Procura a matrícula do aluno no cadastro geral
    int matriculaAluno;
    printf("Informe a matrícula do aluno que deseja incluir na disciplina:\n");
    scanf("%d", &matriculaAluno); // Lê a matrícula como um número inteiro

    // Verifica se a matrícula é de um aluno
    if (verificarMatricula(matriculaAluno, alunos, max_Alunos)) {
        // Verifica se o aluno já está matriculado na disciplina
        for (int j = 0; j < disciplina->alunos; j++) {
            if (disciplina->alunos[j] == matriculaAluno) {
                printf("Aluno já está matriculado nessa disciplina.\n");
                return; // Sai da função se já foi encontrado
            }
        }

        // Adiciona o aluno à disciplina
        disciplina->alunos[disciplina->alunos] = matriculaAluno;
        disciplina->alunos++; // Incrementa o contador de alunos matriculados
        printf("Aluno matriculado na disciplina com sucesso.\n");
    } else {
        // Mensagem caso o aluno não tenha sido encontrado
        printf("Aluno não encontrado.\n");
    }
}

// Função para excluir aluno em uma disciplina.
void desmatricularAlunoDisciplina(materias *disciplina) {
    printf("Entrou na função desmatricularAlunoDisciplina.\n"); // Debug

    if (disciplina->numAlunos == 0) { // Use numAlunos em vez de alunos
        printf("Nenhum aluno foi matriculado nessa disciplina.\n");
        return;
    }

    int matriculaAluno;
    printf("Informe a matrícula do aluno que deseja remover:\n");
    scanf("%d", &matriculaAluno);
    
    // Verifica se a matrícula do aluno é válida
    if (!verificarMatricula(matriculaAluno, alunos, max_Alunos)) {
        printf("Matrícula do aluno inválida ou não cadastrada.\n");
        return; // Sai da função se a matrícula for inválida
    }

    int encontrouAluno = 0; // Inicializa a variável para controlar se encontrou o aluno

    for (int i = 0; i < disciplina->numAlunos; i++) { // Usar numAlunos
        if (disciplina->alunos[i] == matriculaAluno) {
            // Move todos os alunos subsequentes para a esquerda
            for (int j = i; j < disciplina->numAlunos - 1; j++) {
                disciplina->alunos[j] = disciplina->alunos[j + 1];
            }
            disciplina->numAlunos--; // Diminui o contador de alunos
            printf("Aluno removido com sucesso da disciplina.\n");
            encontrouAluno = 1; // Marca que encontrou e removeu o aluno
            break; // Sai do loop após encontrar e remover
        }
    }

    // Mensagem caso o aluno não tenha sido encontrado
    if (!encontrouAluno) {
        printf("Aluno não encontrado na disciplina.\n");
    }
}

//Validando nome
int validarNome(char nome) {
    printf("Entrou na função validarNome.\n"); // debug
    if (strlen(nome) < 3) {
        printf("Erro: O nome deve ter pelo menos 3 caracteres.\n");
        return 0;
    }
    // Verifica se o nome contém apenas letras e espaços
    for (int i = 0; i < strlen(nome); i++) {
        if (!isalpha(nome[i]) && nome[i] != ' ') {
            printf("Erro: O nome deve conter apenas letras.\n");
            return 0;
        }
    }
    return 1;
}

//Função validar CPF
  int validarCPF(char cpf) {
    printf("Entrou na função validarCPF.\n");//debug
    if (strlen(cpf) != 14) { // 14 para o formato xxx.xxx.xxx-xx
        printf("Erro: O CPF deve ser informado no formato xxx.xxx.xxx-xx.\n");
        return 0;
    }
    return 1;
}

//Função Validar Sexo
  int validarSexo(char sexo) {
    printf("Entrou na função validarSexo.\n"); // Debug
    sexo = toupper(sexo); // Transforma a entrada em maiúsculo

    if (sexo != 'M' && sexo != 'F') {
        printf("Sexo inválido. Use 'M' para sexo masculino ou 'F' para sexo feminino.\n");
        return 0; // Indica que a validação falhou
    }
    return 1; 
}

//Função validar data
  int validarData(data aniversario) {
    printf("Entrou na função validarData.\n"); // debug
    if (aniversario.dia < 1 || aniversario.dia > 31 || 
        aniversario.mes < 1 || aniversario.mes > 12 || 
        aniversario.ano < 1900) {
        printf("Data de nascimento inválida.\n");
        return 0;
    }
    return 1;
}

//Listar pessoa
void listarPessoa(pessoas *pessoa, int Max_Pessoas, char tipoPessoa) {
    printf("Entrando na função listarPessoa...\n\n");
    int contador = 0; // conta o número de registros que foram listados
    printf("Lista de %s cadastrados:\n", (tipoPessoa == 1) ? "Alunos" : "Professores");

    for (int i = 0; i < Max_Pessoas; i++) {
        if (pessoa[i].matricula != 0) { // Verifica se a matrícula não é zero
            printf("Nome: %s\n", pessoa[i].nome);
            printf("Matrícula: %d\n", pessoa[i].matricula); // Correção aqui
            printf("CPF: %s\n", pessoa[i].cpf);
            printf("Sexo: %c\n", pessoa[i].sexo);
            printf("Data de nascimento: %02d/%02d/%04d\n", pessoa[i].aniversario.dia, pessoa[i].aniversario.mes, pessoa[i].aniversario.ano);
            separadorTexto(); // Certifique-se de que essa função esteja definida
            contador++;
        }
    }

    if (contador == 0) {
        printf("Não foram encontrados registros.\n");
    }
}

//Funções 

//Atualiza os dados de Pessoa
void atualizarPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa) {
    int matricula;
    printf("Informe o número da matrícula do %s que deseja atualizar os dados:\n", (tipoPessoa == 1) ? "aluno" : "professor");
    scanf("%d", &matricula); // Lê a matrícula como um inteiro

    // Valida a matrícula
    if (matricula < 0) {
        printf("Matrícula inválida.\n");
        return;
    }

    int encontrado = 0; // Para verificar se a matrícula foi encontrada
    for (int i = 0; i < maxPessoas; i++) {
        if (cadastro[i].matricula == matricula) { // Compara a matrícula
            encontrado = 1; // Matrícula encontrada
            printf("Cadastro encontrado:\n");
            printf("Nome: %s\n", cadastro[i].nome);
            printf("CPF: %s\n", cadastro[i].cpf);
            printf("Data de Nascimento: %02d/%02d/%04d\n", cadastro[i].aniversario.dia, cadastro[i].aniversario.mes, cadastro[i].aniversario.ano);

            // Atualiza o nome
            printf("Informe o novo nome (deixe em branco para não alterar):\n");
            char novoNome[50];
            getchar(); // Para consumir o caractere de nova linha que ficou no buffer
            fgets(novoNome, sizeof(novoNome), stdin);
            novoNome[strcspn(novoNome, "\n")] = 0; // Remove o '\n' do final da string
            if (strlen(novoNome) > 0) {
                strncpy(cadastro[i].nome, novoNome, sizeof(cadastro[i].nome) - 1);
                cadastro[i].nome[sizeof(cadastro[i].nome) - 1] = '\0'; // Garante que a string esteja terminada
            }

            // Atualiza o CPF
            printf("Informe o novo CPF (deixe em branco para não alterar):\n");
            char novoCPF[15];
            fgets(novoCPF, sizeof(novoCPF), stdin);
            novoCPF[strcspn(novoCPF, "\n")] = 0; // Remove o '\n' do final da string
            if (strlen(novoCPF) > 0) {
                strncpy(cadastro[i].cpf, novoCPF, sizeof(cadastro[i].cpf) - 1);
                cadastro[i].cpf[sizeof(cadastro[i].cpf) - 1] = '\0'; // Garante que a string esteja terminada

                // Validação do CPF
                if (!validarCPF(cadastro[i].cpf)) {
                    printf("CPF inválido.\n");
                    return;
                }
            }

            // Atualiza a data de nascimento
            printf("Informe a nova data de nascimento separada por espaço: dd mm aaaa (ou pressione enter para manter):\n");
            char dataNascimento[20];
            fgets(dataNascimento, sizeof(dataNascimento), stdin);
            if (sscanf(dataNascimento, "%d %d %d", &cadastro[i].aniversario.dia, &cadastro[i].aniversario.mes, &cadastro[i].aniversario.ano) == 3) {
                printf("Data de nascimento atualizada.\n");
            }

            printf("%s atualizado com sucesso!\n", tipoPessoa == 1 ? "Aluno" : "Professor");
            return; // Sai da função após a atualização
        }
    }

    if (!encontrado) {
        printf("%s não encontrado.\n", tipoPessoa == 1 ? "Aluno" : "Professor");
    }
}

//Atualiza a disciplina
void atualizarDisciplina(materias *disciplinas, int max_Disciplinas, pessoas *professores, int max_Professores) {
    char codigoDisciplina[9];
    printf("Informe o código da disciplina que deseja atualizar:\n");
    fgets(codigoDisciplina, sizeof(codigoDisciplina), stdin);
    codigoDisciplina[strcspn(codigoDisciplina, "\n")] = '\0'; // Remove o '\n' ao final

    // Verifica se o código da disciplina foi informado
    if (strlen(codigoDisciplina) == 0) {
        printf("Código da disciplina não pode estar vazio.\n");
        return;
    }

    // Busca a disciplina pelo código
    int encontrou = 0;
    for (int i = 0; i < max_Disciplinas; i++) {
        if (strcmp(disciplinas[i].codigo, codigoDisciplina) == 0) {
            encontrou = 1;
            printf("Disciplina encontrada: %s\n", disciplinas[i].nome);

            // Atualiza o nome da disciplina
            printf("Informe o novo nome da disciplina (deixe em branco para não alterar):\n");
            char novoNome[50];
            fgets(novoNome, sizeof(novoNome), stdin);
            novoNome[strcspn(novoNome, "\n")] = 0; // Remove o '\n'
            if (strlen(novoNome) > 0) {
                strncpy(disciplinas[i].nome, novoNome, sizeof(disciplinas[i].nome) - 1);
                disciplinas[i].nome[sizeof(disciplinas[i].nome) - 1] = '\0'; // Garante que a string esteja terminada
            }

            // Atualiza o semestre da disciplina
            printf("Informe o novo semestre da disciplina (deixe em branco para não alterar):\n");
            int novoSemestre;
            char buffer[10];
            fgets(buffer, sizeof(buffer), stdin);
            if (strlen(buffer) > 0 && sscanf(buffer, "%d", &novoSemestre) == 1) {
                if (novoSemestre >= 1 && novoSemestre <= 10) { // Exemplo de limite para semestre
                    disciplinas[i].semestre = novoSemestre; // Atribui o novo semestre
                } else {
                    printf("Semestre inválido. Mantenha o semestre anterior.\n");
                }
            }

            // Atualiza o professor
            printf("Selecione o novo professor pelo número da matrícula (deixe em branco para não alterar):\n");
            for (int j = 0; j < max_Professores; j++) {
                printf("%s - %s\n", professores[j].matricula, professores[j].nome);
            }

            char matriculaProf[12];
            fgets(matriculaProf, sizeof(matriculaProf), stdin);
            matriculaProf[strcspn(matriculaProf, "\n")] = '\0'; // Remove o '\n'

            if (strlen(matriculaProf) > 0) {
                // Verifica se a matrícula do professor é válida
                if (!verificarMatricula(matriculaProf, "2024117", professores, max_Professores)) {
                    printf("Matrícula do professor inválida ou não cadastrada.\n");
                } else {
                    // Procura o professor pela matrícula e atrela à disciplina
                    int professorValido = 0;
                    for (int j = 0; j < max_Professores; j++) {
                        if (strcmp(professores[j].matricula, matriculaProf) == 0) {
                            strcpy(disciplinas[i].professor, professores[j].nome);
                            professorValido = 1;
                            break;
                        }
                    }

                    if (!professorValido) {
                        printf("Professor não encontrado.\n");
                    }
                }
            }

            printf("Disciplina atualizada com sucesso!\n");
            break;
        }
    }

    if (!encontrou) {
        printf("Disciplina não encontrada.\n");
    }
}

//Funções de exclusão

//Exclusão de disciplina
void excluirDisciplina(materias *disciplinas, int max_Disciplinas) {
    char codigoDisciplina[9];
    printf("Informe o código da disciplina que deseja excluir:\n");
    fgets(codigoDisciplina, sizeof(codigoDisciplina), stdin);
    codigoDisciplina[strcspn(codigoDisciplina, "\n")] = '\0'; // Remove o '\n' ao final

    // Verifica se o código da disciplina foi informado
    if (strlen(codigoDisciplina) == 0) {
        printf("Código da disciplina não pode estar vazio.\n");
        return;
    }

    // Busca a disciplina pelo código
    int encontrou = 0;
    for (int i = 0; i < max_Disciplinas; i++) {
        if (strcmp(disciplinas[i].codigo, codigoDisciplina) == 0) {
            encontrou = 1;
            printf("Disciplina encontrada: %s\n", disciplinas[i].nome);

            // Confirma a exclusão
            char confirmacao;
            printf("Tem certeza que deseja excluir esta disciplina? (s/n): ");
            scanf(" %c", &confirmacao);
            getchar(); // Limpa o buffer do stdin

            if (confirmacao == 's' || confirmacao == 'S') {
                // Limpa os dados da disciplina excluída
                disciplinas[i].codigo[0] = '\0'; // Marca como não cadastrada
                disciplinas[i].nome[0] = '\0';   // Limpa o nome
                disciplinas[i].semestre = 0;      // Limpa o semestre
                disciplinas[i].professor[0] = '\0'; // Limpa o professor
                disciplinas[i].alunos = 0;    // Reseta o número de alunos

                printf("Disciplina excluída com sucesso!\n");
            } else {
                printf("Exclusão cancelada.\n");
            }
            break;
        }
    }

    if (!encontrou) {
        printf("Disciplina não encontrada.\n");
    }
}

//Exclusão de pessoa
void excluirPessoa(pessoas *cadastro, int maxPessoas, char tipoPessoa) {
    int matricula; // Variável para armazenar a matrícula como int
    printf("Informe a matrícula a ser excluída:\n");

    // Validação da entrada da matrícula
    if (scanf("%d", &matricula) != 1) {
        printf("Erro ao ler a matrícula. Tente novamente.\n");
        getchar(); // Limpa o buffer
        return;
    }

    int encontrado = 0; // Para verificar se a matrícula foi encontrada
    for (int i = 0; i < maxPessoas; i++) {
        if (cadastro[i].matricula == matricula) { // Verifica se a matrícula corresponde
            encontrado = 1; // Matrícula encontrada
            
            if (tipoPessoa == 1) { // Aluno
                printf("Aluno %s encontrado. Deseja excluir? (s/n): ", cadastro[i].nome);
            } else if (tipoPessoa == 2) { // Professor
                printf("Professor %s encontrado. Deseja excluir? (s/n): ", cadastro[i].nome);
            }

            char confirmacao;
            scanf(" %c", &confirmacao); // Lê a confirmação
            if (confirmacao == 's' || confirmacao == 'S') {
                // Limpa os dados do registro excluído
                cadastro[i].matricula = 0; // Marca a matrícula como "vazia"
                cadastro[i].nome[0] = '\0'; // Limpa o nome
                cadastro[i].cpf[0] = '\0'; // Limpa o CPF
                cadastro[i].sexo = '\0'; // Limpa o sexo
                cadastro[i].aniversario.dia = 0; // Limpa o dia
                cadastro[i].aniversario.mes = 0; // Limpa o mês
                cadastro[i].aniversario.ano = 0; // Limpa o ano

                printf("Registro excluído com sucesso!\n");
            } else {
                printf("Exclusão cancelada.\n");
            }
            break; // Sai do loop após a exclusão
        }
    }

    if (!encontrado) {
        printf("Matrícula não encontrada.\n");
    }
}

