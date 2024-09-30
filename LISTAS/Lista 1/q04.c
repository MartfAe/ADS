#include <stdio.h>
#include <stdlib.h> 

int ler3Numeros(int numeros[]){
    for(int i =0; i < 3; i++){
        printf("Digite o numero %d: ", i+1);
        scanf("%d", &numeros[i]);
    }
}

int main(){
    int numeros[3];
    ler3Numeros(numeros);

    printf("Os numeros lidos foram: %d, %d, %d .\n", numeros[0], numeros[1], numeros[2]);

    return 0;
}