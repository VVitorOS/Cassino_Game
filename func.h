
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

_Bool CmpStrValues(char s1[], char s2[]){ //COMPARA DUAS STRING > RETORNA 1 SE AS DUAS STRINGS FOREM IGUAIS OU 0 SE NÃO FOREM
    int i = 0;

    while(s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0'){
        i++;
    }
    if(s1[i] == '\0' && s2[i] == '\0'){
        return 1;
    }
    else{
        return 0;
    }
}

void Sorteando(){   //CRIA UMA "ANIMAÇÃO" DE LOADING (PRINTA "." COM INTEVALOS DE 1 SEGUNDO)

    printf("Sorteando");
    printf(".");
    sleep(1);
    printf(".");
    sleep(1);
    printf(".");

    system("cls");
}

void JogoDoBicho(int dia){
    setlocale(LC_ALL, "portuguese");

    srand(time(NULL));

    int lin, ctrl = 0;

    char aposta[15], sorteio[15], animais[25][15] = {"avestruz", "aguia", "burro", "borboleta", "cachorro ", "cabra ", "carneiro ", "camelo", "cobra", "coelho", "cavalo", 
    "elefante", "galo", "gato", "jacare", "leao", "macaco", "porco", "pavao", "peru", "touro", "tigre", "urso", "veado", "vaca"};
    

    printf("DIA %d - JOGO DO BICHO \n\n", dia);

    for(lin = 0; lin < 25; lin++){ //PRINTA A LISTA DE ANIMAIS ACIMA
        printf(" %s", animais[lin]);

        ctrl += 1;

        if(ctrl == 5){
            printf("\n");
            ctrl = 0;
        }
    }
    
    while(ctrl == 0){ //PEDE AO USUARIO QUE ESCOLHA UM ANIMAL (REPETE ATE QUE O USUARIO ESCREVA UM ANIMAL DA LISTA)
        int res = 0;

        printf("\nEscola um animal: ");
        gets(aposta);

        for(lin = 0; lin < 25; lin++){
            if(CmpStrValues(aposta, animais[lin])){
                ctrl = 1;
                res = 1;
            }
        }

        if(res == 0){
            printf("\nDigite um animal valido");
        }

    }

    system("cls");
    Sorteando();

    strcpy(sorteio, animais[rand() % 26]);  //SORTEANDO UM ANIMAL E COLOCANDO DENTRO DE "sorteio"

    printf("\nSUA APOSTA = %s", aposta);
    printf("\nSORTEADO = %s", sorteio);

    if(CmpStrValues(aposta, sorteio)){  //COMPARA O ANIMAL ESCOLHIDO COM O ANIMAL SORTEADO
        printf("\nVoce ganhou");
    }
    else{
        printf("\nVoce perdeu");
    }
}