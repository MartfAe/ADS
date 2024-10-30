#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define Max_Alunos 100
#define Max_Professores 100
#define Max_Disciplinas 100
#define Max_Vagas_Disciplina 100 // - adicionado- limita o numero de vagas máximo de todas as disciplinas

//adicionados os 4 dígitos dos suxixos aluno e professor

#define prefixo_Aluno "20241060000"
#define prefixo_Professor "20241170000"

// Definição das structs
typedef struct {
    int dia, mes, ano;
} data;

typedef struct {
    char matricula[12]; //transformado em inteiro (não array)
    char sexo, nome[50], cpf[15];
    data aniversario;
    int disciplinas; //adicionado para contar as disciplinas em que os alunos ou professores estão inseridos.
    //Verificar finção de matricula em disciplina
} pessoas;

typedef struct {
    char nome[50], codigo[8];
    int semestre;
    int vagasTot, vagasOcup; // - adicionado- vagasTod limita o que pode ser ocupado e vagasOcup são as vagas ocupadas por alunos (adicionar incremento sempre que um novo aluno for matriculado e decremento no caso contrário
    pessoas alunos[Max_Vagas_Disciplina], professor;
    //int numAlunos; virou vagasOcup
} materias;


void separadorTexto(void) {
    printf("\n");
    for (int i = 0; i < 70; i++) {
        printf("-");
    }
}

void printCadastroPessoa(pessoas *pessoa,int index){
    printf("Nome: %s\n", pessoa[index].nome);
    printf("Matrícula: %s\n", pessoa[index].matricula);
    printf("CPF: %s\n", pessoa[index].cpf);
    printf("Sexo: %c\n", pessoa[index].sexo);
    printf("Data de nascimento: %02d/%02d/%04d \n", pessoa[index].aniversario.dia, pessoa[index].aniversario.mes, pessoa[index].aniversario.ano);
    separadorTexto();
    printf("\n");
}
void printCadastroDisciplina(materias *disciplina, int index, bool comAluno){ // TESTAR
    printf("Nome: %s\n", disciplina[index].nome);
    printf("Código: %s\n", disciplina[index].codigo);
    printf("Semestre: %d\n", disciplina[index].semestre);
    printf("Total de vagas: %d / %d\n", disciplina[index].vagasOcup,disciplina[index].vagasTot);
    printf("Professor responsável: %s\n",disciplina[index].professor.nome);
    if(comAluno){
    	    printf("Alunos matriculados: ");
            for(int i=0; i < disciplina->vagasOcup; i++){
            printf("%s|",disciplina[index].alunos[i].nome);
        }
    }
    separadorTexto();
    printf("\n");
}

void listarPessoa(pessoas *pessoa, int Max_Pessoas, int tipoPessoa, char ordenacao[20]){
    //relatórios de listagem de pessoas (alunos ou professores) - tipoPessoa: (1-aluno,2-professor);
    //ordenacao: ("nenhuma","sexo","alfabetica","nascimento","matriculaMenos3")
printf("Entrando na função listarPessoa...\n\n"); // Debug
int contador=0; //conta o número de registros que foram listados
    
    if(strcmp(ordenacao,"nenhuma")==0){
		//se a ordenação não foi especificada, listar todos os registros
        printf("Lista de %s cadastrados:\n\n", (tipoPessoa ==1) ? "Alunos":"Professores");
        for(int i = 0; i< Max_Pessoas; i ++){
            if(strcmp(pessoa[i].matricula, "666")!=0){
                //se a matrícula for diferente de 666, significa que a posição está ocupada
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
                if((pessoa[i].sexo == sexo||pessoa[i].sexo == sexo-32) && strcmp(pessoa[i].matricula, "666")!=0){
                    //verifica se a matrícula é diferente de 666 e se o sexo é igual ao informado
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
            if(strcmp(alfabetica[i].matricula, "666")!=0){
                //se a matrícula for diferente de 666, significa que a posição está ocupada
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
            if(strcmp(pessoa[i].matricula, "666")!=0){
                //se a matrícula for diferente de 666, significa que a posição está ocupada
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
            if(strcmp(pessoa[i].matricula, "666")!=0 && pessoa[i].disciplinas < 3){
                //se a matrícula for diferente de 666, significa que a posição está ocupada
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
            if(strcmp(todos[j].matricula, "666")!=0){
                //se a matrícula for diferente de 666, significa que a posição está ocupada e a matrícula não foi excluída
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
            if(strcmp(todos[j].matricula, "666")!=0 && todos[j].aniversario.mes == mes_atual){
                //se a matrícula for diferente de 666, significa que a posição está ocupada e a matrícula não foi excluída
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
    	fgets(letras, sizeof(letras), stdin);
    	for(int i=0; i<strlen(letras); i++){ //Garante que todas as letras armazenadas sejam maíusculas
            if(letras[i]>= 97 && letras[i]<=122){
                letras[i]= letras[i]-32;
            }
        }

        letras[strcspn(letras, "\n")] = 0;
        // system("clear");

        if(strlen(letras)<3){
        	printf("Entrada inválida. Devem ser inseridas ao menos 3 letras");
		}
		else{
			printf("Lista de pessoas que contêm as letras '%s':\n\n", letras);
		    for (int j = 0; j < Max_Todas_Pessoas; j++) {
		        if (strcmp(todos[j].matricula, "666")!=0) {
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

void listarDisciplinas(materias *disciplina, int Max_disciplinas, char ordenacao[20]){ // TESTAR
    //relatórios de listagem de disciplinas (cadastradas,dados de uma e disciplinas com mais de 40 vagas)
    //ordenacao: ("nenhuma","mais40","uma")

    int contador=0;
    if(strcmp(ordenacao,"nenhuma")==0){ 
		//se a ordenação não foi especificada, listar todos os registros
       printf("Lista de disciplinas cadastradas:\n\n");
       for(int i = 0; i< Max_Disciplinas; i++){
           if(strcmp(disciplina[i].codigo,"666")!=0){
               //se o código for diferente de 666, significa que a posição está ocupada
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
           if(strcmp(disciplina[i].codigo,"666")!=0 && disciplina[i].vagasTot>40){
               //se o código for diferente de 666, significa que a posição está ocupada
               //(disciplina não foi excluída)
               //verifica se tem mais de 40 vagas
               printf("Disciplina: %s\t",disciplina[i].nome);
               printf("Professor responsável: %s\n",disciplina[i].professor.nome);
               contador++;
           }
        }
    }
    else if(strcmp(ordenacao,"uma")==0){ 
		//se a ordenação foi especificada como dados de uma disciplina

        char codigo[8];
        printf("Digite o código da disciplina escolhida: \n");
        fgets(codigo,sizeof(codigo),stdin);
        for(int i=0; i<strlen(codigo); i++){ //Garante que todas as letras armazenadas sejam maíusculas
            if(codigo[i]>= 97 && codigo[i]<=122){
                codigo[i]= codigo[i]-32;
            }
        }
        codigo[strcspn(codigo, "\n")] = '\0';
        // system("clear");
        for(int i = 0; i< Max_Disciplinas; i++){
           if(strcmp(disciplina[i].codigo,"666")!=0 && strcmp(disciplina[i].codigo,codigo)==0){
               //se o código for diferente de 666, significa que a posição está ocupada
               //(disciplina não foi excluída)
               printCadastroDisciplina(disciplina, i, true); // print com alunos
               contador++;
           }
        }
    }
    //adicionar demais ordenações
    if(contador == 0){
        printf("Não foram encontrados registros");
    }
}
 
int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    
    // Obtém o tempo atual
    time_t t = time(NULL);

    // Converte para a estrutura tm
    struct tm *tm_info = localtime(&t);

    
    // Inicialização de listas
    pessoas aluno[Max_Alunos] = {0}; // Inicializa o array com zeros
    pessoas professor[Max_Professores] = {0}; // Inicializa o array com zeros
    materias disciplinas[Max_Disciplinas] = {0}; // Inicializa o array com zeros
    char matricula_Aluno[12] = prefixo_Aluno;//adicionados como variável para que seja possivel o autoincremento no teste
    char matricula_Professor[12] = prefixo_Professor;//adicionados como variável para que seja possivel o autoincremento no teste
    int mes_atual = tm_info->tm_mon + 1;// informa o mês atual
    
    for(int i =0;i<Max_Alunos;i++){
        
        matricula_Aluno[10]++;
        strcpy(aluno[i].matricula, matricula_Aluno);
        strcpy(aluno[i].cpf,"000.000.000-00");
        strcpy(aluno[i].nome,"joaoTestes");
        aluno[i].sexo='M';
        aluno[i].aniversario = (data){.dia = tm_info->tm_mday - i,.mes = tm_info->tm_mon + 1 -i,.ano = tm_info->tm_year + 1900 - i};
        aluno[i].disciplinas = i;
    }

    for(int i =0;i<Max_Professores;i++){
        
        matricula_Professor[10]++;
        strcpy(professor[i].matricula, matricula_Professor);
        strcpy(professor[i].nome,"ROMIULÇU");
        strcpy(professor[i].cpf,"000.000.000-00");
        professor[i].sexo='M';
        professor[i].aniversario = (data){.dia = tm_info->tm_mday - i,.mes = tm_info->tm_mon + 1 -i,.ano = tm_info->tm_year + 1900 - i};
        professor[i].disciplinas = i;
    }
  
    strcpy(professor[5].nome,"FREDI");
    strcpy(professor[4].nome,"ARCUNDICIONADU");
    
    for(int i=0;i<Max_Disciplinas;i++){
    	strcpy(disciplinas[i].nome,"TESTE");
		strcpy(disciplinas[i].codigo,"INF01");
		disciplinas[i].semestre = 2;
		disciplinas[i].vagasTot = 38+i;
		disciplinas[i].vagasOcup = i;
		disciplinas[i].alunos[i] = aluno[i];
		disciplinas[i].professor = professor[i];
	}
	

	strcpy(disciplinas[0].nome,"COM PUTAÇÃO");
	strcpy(disciplinas[0].codigo,"INF009");
	strcpy(disciplinas[5].nome,"LOGICA");
	strcpy(disciplinas[5].codigo,"INF002");
	strcpy(disciplinas[3].nome,"ESTRUTURAS");
	strcpy(disciplinas[3].codigo,"INF003");
	
	
	strcpy(aluno[0].nome,"JOAOTESTES");
    aluno[0].aniversario = (data){.dia = 28, .mes = 3, .ano = 1998};
    strcpy(aluno[1].nome,"ANA");
    aluno[1].sexo='F';
    aluno[1].aniversario = (data){.dia = 3, .mes = 10, .ano = 1998};
    strcpy(aluno[2].nome,"CLARA");
    aluno[2].sexo='F';
    aluno[2].aniversario = (data){.dia = 3, .mes = 3, .ano = 1998};
    strcpy(aluno[3].nome,"JORGE");
    aluno[3].aniversario = (data){.dia = 7, .mes = 9, .ano = 1945};
    strcpy(aluno[4].nome,"CLARICE");
    aluno[4].sexo='F';
    aluno[4].aniversario = (data){.dia = 24, .mes = 10, .ano = 2024};
    strcpy(aluno[5].nome,"TARCIO");
    aluno[5].aniversario = (data){.dia = 3, .mes = 3, .ano = 1998};

//	listarPessoa(aluno,Max_Alunos,1,"nenhuma");
	listarTodasPessoas(aluno, Max_Alunos, professor, Max_Professores, "letras");
	
// 	listarDisciplinas(disciplinas,Max_Disciplinas,"uma");
   
    return 0;
}
