typedef struct{
    char nome[15], sexo;
    int idade, felicidade, dia;
    float dinheiro;
} Player;

struct jdb{
    float ValorAposta;
    char AnimalAposta[15];
    int odd, meta;
};

Player jogador; //"Player" é um tipo de struct, já "jogador" é um struct deste tipo 

char aposta[15], sorteio[15], animais[25][15] = {"avestruz", "aguia", "burro", "borboleta", "cachorro ", "cabra ",
"carneiro ", "camelo", "cobra", "coelho", "cavalo", "elefante", "galo", "gato", "jacare", "leao", "macaco", "porco",
"pavao", "peru", "touro", "tigre", "urso", "veado", "vaca"};

