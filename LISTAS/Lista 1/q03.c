#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>


//Cálculo do fatorial
int fatorial(int n, int *erro){
    if(n<0){
        *erro = 1;
        return -1;
    }

    int fat = 1;
    for (int i=1; i<=n; i++){
    fat *= i;
    }

    *erro=0;
    return fat;
}

int main(){
    int num, resultado, erro;

    //Solicitando número
    printf("Digite um numero inteiro: ");
    scanf("%d", &num);

    //Chama a função para fazer o cálculo
    resultado = fatorial(num, &erro);

    //Verificando se teve erro
    if(erro){
        printf("Erro: Nao posso calcular o fatorial de um número negativo.\n");
    }else{
        printf("O fatorial de %d = %d\n", num, resultado);
    }

    return 0;
    }

