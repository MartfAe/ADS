#include <stdio.h>
#include <stdlib.h>

int subtracao (float n1, float n2, float n3){
    float resultado;
    resultado = n1 - n2 -n3;
    return(resultado);

}

int main(){
    float v1 , v2, v3 , resultado;
    printf("Informe 3 valores:\n");
    scanf("%f %f %f", &v1, &v2, &v3);
    resultado = subtracao(v1, v2,v3);

    printf("Resultado: %.1f", resultado);

    return 0;

}