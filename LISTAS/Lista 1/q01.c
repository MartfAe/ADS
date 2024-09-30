#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

int soma(float n1, float n2){ //recebe dois valores, n1 e n2 e retorna a soma de ambos
    float resultado;
    resultado = n1 + n2 ;
    return(resultado);
}
int main(){
    float v1 , v2, resultado; 
    printf("Digite o primeiro valor:\n");
    scanf("%f", &v1);
    printf("Digite o segundo valor:\n");
    scanf("%f", &v2);
    
    //Chama a função e recebe o retorno
    resultado = soma(v1,v2);

    printf("Resultado = %.1f\n", resultado);

   // getch();
    return 0 ; 

}
