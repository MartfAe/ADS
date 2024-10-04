#include <stdio.h>
#include <stdlib.h>

//armazena 3 letras por meio de um vetor
void ler3Letras(char letras[3]){
    for(int i =0; i<3; i++){
        printf("Digite a letra %d: ", i+1);
        scanf(" %c", &letras[i]);
    }
}

int main(){
    //chamando a função
    char letras [3];
    ler3Letras(letras);

    printf("As 3 letras: %c, %c, %c .", letras[0], letras[1], letras[2]);

    return 0;
}