#include <stdio.h>
#include <stdlib.h>

struct Numeros{
    int num[4];
}; 
//Lê os numeros por meio do for e retorna na struct
struct Numeros ler4Numeros(){
    struct Numeros numeros;
    for (int i=0; i<4; i++){
        printf("Digite 4 numeros %d: ", i +1);
        scanf("%d", &numeros.num[i]); //Armazenando em um vetor
    }

    return numeros;
}

int main(){
    struct Numeros numerosLidos = ler4Numeros();

    printf("Os quatros numeros lidos: ");
    for(int i=0; i<4; i++){
        printf("%d ", numerosLidos.num[i]);
    }
    printf("\n");

    return 0;

}