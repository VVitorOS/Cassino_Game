#include "structs.h"
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>


//FUNÇÕES DIVERSAS ----------------

int size_of(char vetor[]){  //RECEBE UM VETOR DE CHAR E RETORNA O TAMANHO DELE
    int i, size = 0;

    for(i = 0; i < 100; i++){
        if(vetor[i] != '\0'){
            size++;
        }
        else{
            break;
        }
    }

    return size;
}

_Bool CmpStrValues(char s1[], char s2[]){   //COMPARA DUAS STRING -> RETORNA 1 SE AS DUAS STRINGS FOREM IGUAIS OU 0 SE NÃO FOREM
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

void Loading(char palavra[], int tempo){   //CRIA UMA "ANIMAÇÃO" DE LOADING (PRINTA "." COM INTEVALOS DE 1 SEGUNDO)
    system("cls");
    printf("%s", palavra);
    printf(".");
    _sleep(tempo);
    printf(".");
    _sleep(tempo);
    printf(".");

    system("cls");
}

void SetDados(Player jogador, char arquivo[]){//DADOS DO "jogador" SERÃO GRAVADOS EM "arquivo"

    //nome, idade, sexo, dinheiro, felicidade, dia 
    FILE *file = fopen(arquivo, "a");

    fprintf(file, "\n%s %i %c %.2f %i %i", jogador.nome, jogador.idade, jogador.sexo, jogador.dinheiro, jogador.felicidade, jogador.dia);
    fclose(file);

}

Player GetDados(Player jogador, char arquivo[]){

    FILE *file = fopen(arquivo, "r");
    fscanf(file, "%s %i %c %f %i %i", &jogador.nome, &jogador.idade, &jogador.sexo, &jogador.dinheiro, &jogador.felicidade, &jogador.dia);
    fclose(file);

    return jogador;
}

void tectec(char vetor[]){  //TECTEC DE STRINGS
    int i;

    for(i = 0; i < size_of(vetor); i++){
        printf("%c", vetor[i]);
        _sleep(140);
    }
}


//FUNÇÕES DE BOTÕES ---------------

void Sair(void){    //QUANDO CHAMADA A FUNÇÃO FECHA O JOGO E O TERMINAL
    system("cls");
    Loading("Saindo", 800);
    system("exit");
}

void Jogar(void){   //FUNÇÃO DO "BOTÃO JOGAR", PEDE OS DADOS DO USUARIO E SALVA NO ARQUIVO "jogador.txt"

    //JOGADOR { NOME, SEXO, IDADE, DINHEIRO, ESTAMINA, FELICIDADE } NESSA ORDEM 
    int ctrl = 0;
    jogador.felicidade = 100;
    jogador.dinheiro = 100;
    jogador.dia = 1;

    system("cls");
    Loading("Iniciando", 700);

    //PEDINDO DADOS AO JOGADOR (E TRATANDO-OS)
    printf("Nome: ");   //pedindo nome
    scanf("%s", &jogador.nome);

    fflush(stdin);

    printf("Sexo F/M: ");   //pedindo sexo
    scanf("%c", &jogador.sexo);

    while(jogador.sexo != 'm' && jogador.sexo != 'f' && jogador.sexo != 'M' && jogador.sexo != 'F'){    //tratando erros (so é aceito M/F)
        fflush(stdin);
        printf("Digite apenas M/F: ");
        scanf("%c", &jogador.sexo);
    }

    jogador.sexo = toupper(jogador.sexo);

    fflush(stdin);

    printf("Idade: ");  //pedindo idade
    scanf("%d", &jogador.idade);

    if(jogador.idade < 18){ // Não é aceito menores
        system("cls");
        printf("Menores não podem apostar, volte quando tiver idade!!");
        exit(0);
    }
    else{   //salvando em arquivo
        FILE * file = fopen("jogadores.txt", "r");
        Player cPlayer;
        int res = 0;

        char ani[100];

        while(fgets(ani, 100, file) != NULL){   //VERIFICANDO SAVES
            fscanf(file, "%s %i %c %f %i %i", &cPlayer.nome, &cPlayer.idade, &cPlayer.sexo, &cPlayer.dinheiro, &cPlayer.felicidade, &cPlayer.dia);

            if(CmpStrValues(cPlayer.nome, jogador.nome)){
                res = 1;
            }
        }

        fclose(file);

        if(res == 1){   //SO É POSSIVEL CRIAR SE NAO EXISTIR OUTRO SAVE COM O NOME DIGITADO
            printf("Já existe um save com o nome %s.", jogador.nome);
            printf("\nAperte enter para voltar ao menu.");
            getch();
            Menu();
            exit(0);
        }
        else{
            SetDados(jogador, "jogadores.txt");
            Jogo(jogador);
        }
    
    }
}

void CarregarJogo(void){
    system("cls");
    Loading("Obtendo Dados", 1300);

    char ani[100], nomesave[15];
    int res; // 1 sim - 0 nao

    Player tPlayer; //Player temporario usado somente para print de informações (ani e IndiceSave tambem sao variaveis de controle)

    FILE *file = fopen("jogadores.txt", "r");

    while(fgets(ani, 100, file) != NULL){
        fscanf(file, "%s %i %c %f %i %i", &tPlayer.nome, &tPlayer.idade, &tPlayer.sexo, &tPlayer.dinheiro, &tPlayer.felicidade, &tPlayer.dia);
        printf("Nome: %s   Dinheiro: R$ %.2f   Dia: %i\n", tPlayer.nome, tPlayer.dinheiro, tPlayer.dia);
    }

    if(tPlayer.sexo != 'm' && tPlayer.sexo != 'M' && tPlayer.sexo != 'f' && tPlayer.sexo != 'F'){ // SE O ARQUIVO ESTIVER VAZIO MOSTRA A MENSAGEM "NENHUM SAVE"
        printf("Nenhum Save, aperte enter para voltar ao menu. ");
        getch();
        Menu();
        exit(0);
    }
    else{            //SE TIVER ALGUM SAVE PEDE PARA O USUARIO ESCOLHER UM
        fflush(stdin);
        printf("\nDigite voltar para voltar ao menu, ou digite o nome do seu save: ");
        gets(nomesave);
    }
    
    rewind(file);

    if(CmpStrValues(nomesave, "voltar")){
        Menu();
        exit(0);
    }
    else{
        while(fgets(ani, 100, file) != NULL){

            fscanf(file, "%s %i %c %f %i %i", &tPlayer.nome, &tPlayer.idade, &tPlayer.sexo, &tPlayer.dinheiro, &tPlayer.felicidade, &tPlayer.dia);
            
            if(CmpStrValues(nomesave, tPlayer.nome)){
                res = 1;
                break;
            }
            else{
                res = 0;
            }
        }
    }

    if(res == 0){
        system("cls");
        printf("Save não encontrado, aperte enter para voltar ao menu");
        getch();
        Menu();
        exit(0);
    }

    fclose(file);
    Jogo(tPlayer);
}


//FUNÇÕES DE "INTERFACE" ----------

void Menu(void){    //CHAMA O MENU
    char res;

    while(res != '1' && res != '2' && res != '3'){  //PRINTANDO OPÇÕES E TRATANDO POSSIVEIS ERROS NO MENU

        system("cls");
        printf("\nBEM-VINDO AO CASSINO\n");

        printf("\n1 - JOGAR");
        printf("\n2 - CARREGAR JOGO");
        printf("\n3 - SAIR\n");

        scanf("%c", &res);

    }

    switch(res){    //OPÇÕES DO MENU CHAMANDO SUAS RESPECTIVAS FUNÇÕES
        case '1':
            Jogar();
            break;

        case '2':
            CarregarJogo();
            break;

        case '3':
            Sair();
            break;
        
        default:
            printf("error");
            exit(0);
    }
}

void Jogo(Player jogador){
    switch (jogador.dia)
    {
    case 1:
        //Historia1();
        JogoDoBicho(jogador);
        break;

    case 2:
        //Historia2();
        //Jogo2();
        break;
    
    default:
        printf("Save corrompido ou não existente");
        break;
    }
}

void JogoDoBicho(Player jogador){  //QUANDO CHAMADA ESTA FUNÇÃO EXECUTA O JOGO DO BICHO
    struct jdb info; //INFO GUARDARÁ AS INFORMAÇÕES DO JOGO DO BICHO
    info.meta = 200;
    info.odd = 200 / jogador.felicidade;

    while(jogador.dinheiro > 0 && jogador.dinheiro < info.meta){
        system("cls");
        srand(time(NULL));

        printf("Dia %d - jogo do bicho - %s R$ %.2f\n\n", jogador.dia, jogador.nome, jogador.dinheiro);

        int ctrl = 0;

        for(int ani = 0; ani < 25; ani++){ //PRINTA A LISTA DE ANIMAIS
            printf("%s ", animais[ani]);

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

            for(int lin = 0; lin < 25; lin++){
                if(CmpStrValues(aposta, animais[lin])){
                    ctrl = 1;
                    res = 1;
                }
            }

            if(res == 0){
                printf("\nDigite um animal valido");
            }
        }

        ctrl = 0;

        while(ctrl == 0){ //PEDE AO USUARIO QUE ESCOLHA UM ANIMAL (REPETE ATE QUE O USUARIO ESCREVA UM ANIMAL DA LISTA)
            printf("Digite o valor que você deseja apostar: ");
            scanf("%f", &info.ValorAposta);

            if(jogador.dinheiro < info.ValorAposta){
                printf("Você não tem dinheiro suficiente para esta aposta.");
            }
            else{
                ctrl = 1;
            }
        }

        system("cls");
        Loading("Sorteando", 800);

        strcpy(sorteio, animais[rand() % 1]);  //SORTEANDO UM ANIMAL E COLOCANDO DENTRO DE "sorteio"

        printf("\nSUA APOSTA = %s", aposta);
        printf("\nSORTEADO = %s", sorteio);

        if(CmpStrValues(aposta, sorteio)){  //COMPARA O ANIMAL ESCOLHIDO COM O ANIMAL SORTEADO
            printf("\nVoce ganhou %.2f", info.ValorAposta);
            jogador.dinheiro += info.ValorAposta * info.odd;
            jogador.felicidade += 10;
            getch();

        }
        else{
            printf("\nVoce perdeu %.2f", info.ValorAposta);
            jogador.dinheiro -= info.ValorAposta;
            jogador.felicidade -= 10;
            getch();
        }

        if(jogador.dinheiro == 0){
            system("cls");
            printf("Você faliu, parabéns idiota.");
        }
        else if(jogador.dinheiro >= info.meta){
            system("cls");
            BlackJack(jogador);
        }
    }
}

void BlackJack(Player jogador){
    printf("Blackjack -> %s", jogador.nome);
}