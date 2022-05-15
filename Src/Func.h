
char animais[24][15] = {"Jacare", "Cachorro", "Pavao", "Macaco", "Peixe", "Hipopotamo",
"Gato", "Coelho", "Cobra", "Raposa", "Polvo", "Girafa", "Cavalo", "Coruja", "Porco", 
"Veado", "Camelo", "Tartaruga", "Galinha", "Vaca", "Leao", "Avestruz", "Urso", "Tigre"};

//STRUCT PLAYER
typedef struct {
	char personagem[10];
	int dinheiro, felicidade, estresse, dia;
} Player;

_Bool CmpStrValues(char s1[], char s2[]){   //COMPARA DUAS STRING -> RETORNA 1 SE AS DUAS STRINGS FOREM IGUAIS OU 0 SE N�O FOREM
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
