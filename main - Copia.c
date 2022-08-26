
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <string.h>
#include "Func.h"

Player jogador;

//VARIAVEIS GLOBAIS
FONT *Fira_Code_16;
FONT *Minecraft_20;
FONT *Minecraft_16;
FONT *Minecraft_10;

BITMAP *chave;
BITMAP *menu;
BITMAP *master_box;
SAMPLE *select;

int control;

int delay = 0;
int timer = 0;
int som = 0;
int go = 0;

void tempo(){timer++;}

int main(){
	
	init();
	set_window_title("Jogo Do Bicho Simulator");  // Titulo da janela;
	
	//BITMAPS
	BITMAP *buff  = create_bitmap(1280, 720);
	select = load_sample("../Sounds/select.wav"); //som select
	
	if(Menu(buff) == 1){
		if(JogoDoBicho(buff) == 1){
			Blackjack(buff);
		}
	}
	
	//Blackjack(buff);
	
	return 0;	
}

END_OF_MAIN();

void init(){
	allegro_init(); 
	install_keyboard();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1280, 720, 0, 0);
	install_timer();
	install_int_ex(tempo, MSEC_TO_TIMER(10)); //N SEI PRA QUE SERVE, MAS N Ã‰ PRA TIRAR
}

void deinit() {
	clear_keybuf();
	exit(0);
}

int Menu(BITMAP *buff){
	menu = load_bitmap("../Main_Menu/main_menu.bmp", NULL);
	chave = load_bitmap("../Main_Menu/main_chave.bmp", NULL);

	//VARIAVEIS LOCAIS
	int py[3]= {337, 387, 437};
	int linha = 0, chx  =  534;
	
	while(!key[KEY_ESC]){
		int chy = py[linha];
		delay = timer;
		
		clear_bitmap(buff);
		
		draw_sprite(buff, menu, 0, 0);	

		//KEYS SETAS
		if(key[KEY_DOWN]){rest(100);if(linha <= 1){linha++;som = 1;}}
		
		if(key[KEY_UP]){rest(100);if(linha >= 1){linha--;som = 1;}}
		
		//TRATAMENTO DE ERRO DE SOM
		if(key[KEY_UP] && key[KEY_DOWN]){rest(100);som = 0;}
		
		//BOTÕES
		if(key[KEY_ENTER] && linha == 0){rest(100);return 1;}//JOGAR
		
		else if(key[KEY_ENTER] && linha == 1){rest(100);control = 2;return 2;}//CARREGAR JOGO
		
		if(key[KEY_ENTER] && linha == 2){rest(100);return 0;} //SAIR
		
		//TRATAMENTO DE DELAY
		rest(30);
		
		//SOM
		if(som){play_sample(select, 80, 128, 1000, 0); som = 0;}
		
		//DRAW CHAVE
		draw_sprite(buff, chave, chx, chy);
		
		//DRAW BUFFER
		draw_sprite(screen, buff, 0, 0);
		
		while(timer == delay){};
	}
	return 0;
}

int SelectScreen(BITMAP *buff){
	
	menu = load_bitmap("../Menu_Select/menu_select.bmp", NULL);
	chave = load_bitmap("../Menu_select/chave_menu_select.bmp", NULL);
	
	_sleep(200); //DELAY ENTRE TELAS
	
	//VARIAVEIS LOCAIS
	int py[2] = {87, 391}, coluna = 0, chx  =  283;
	
	while(!key[KEY_ESC]){
		int chy = py[coluna];
		
		clear_bitmap(buff);
		draw_sprite(buff, menu, 0, 0);
		
		//KEYS SETAS
		if(key[KEY_DOWN]){if(coluna <= 0){rest(100);coluna++;som = 1;}}
		if(key[KEY_UP]){if(coluna >= 1){rest(100);coluna--;som = 1;}}
		if(key[KEY_UP] && key[KEY_DOWN]){rest(100);som = 0;}//TRATAMENTO DE ERRO DE SOM
		
		//KEY BUTTONS
		if(key[KEY_ENTER] && coluna == 0){	//SELECT JOHN
			strcpy(jogador.personagem, "Jhon");
			jogador.felicidade = 100;
			jogador.dinheiro = 100;
			jogador.estresse = 0;
			jogador.dia = 1;
			
			SaveScreen(buff, jogador);
			return 1;
		}
		
		else if(key[KEY_ENTER] && coluna == 1){ //SELECT ELENA
			strcpy(jogador.personagem, "Elena");
			jogador.dinheiro = 100;
			jogador.felicidade = 100;
			jogador.estresse = 0;
			jogador.dia = 1;
		
			SaveScreen(buff, jogador);
			return 1;
		}
		
		//TRATAMENTO DE DELAY ?
		rest(50);
		
		//SOM
		if(som){play_sample(select, 80, 128, 1000, 0); som = 0;}
		
		//DRAW CHAVE
		if(timer > 2) draw_sprite(buff, chave, chx, chy);
		
		//DRAW BUFFER
		draw_sprite(screen, buff, 0, 0);
	}
	return 0;
}
 
int JogoDoBicho(BITMAP *buff){

	//VARIAVEIS LOCAIS E BITMAPS
	menu = load_bitmap("../Jogo_Do_Bicho/jdb_menu.bmp", NULL);
	chave = load_bitmap("../Jogo_Do_Bicho/jdb_chave.bmp", NULL);
	
	//FONTES
	Fira_Code_16  = load_font("../Fontes/Fira_Code_16A.pcx", NULL, NULL);
	
	int linha = 0, coluna = 0, px[6] = {38, 196, 352, 508, 664, 822}, py[4] = {65, 221, 377, 534}; //MOVIMENT
	int py_text[6] = {139, 225, 316, 404, 500, 603}; 
	
	//definindo status do player (4/5)
	jogador.dinheiro = 100; jogador.estresse = 0; jogador.felicidade = 100; jogador.ValorAposta = 10;
	
	//definindo infos do game (2/3)
	jdb.meta = 200; jdb.odd = 200/jogador.felicidade; 
	
	//DELAY ENTRE TELAS
	_sleep(200); 	
	
	while(!key[KEY_ESC]){
		int chx  =  px[coluna], chy = py[linha];
		
		clear_bitmap(buff);
		
		draw_sprite(buff, menu, 0, 0);
		
		//CAIXAS DE TEXTO
		textprintf_centre_ex(buff, Fira_Code_16, 1115, 129, makecol(230, 230, 230), -1, "%i", jogador.dinheiro);
		textprintf_centre_ex(buff, Fira_Code_16, 1115, 221, makecol(230, 230, 230), -1, "%i", jogador.felicidade);
		textprintf_centre_ex(buff, Fira_Code_16, 1115, 312, makecol(230, 230, 230), -1, "%i", jogador.estresse);
		textprintf_centre_ex(buff, Fira_Code_16, 1115, 400, makecol(230, 230, 230), -1, "%i", jdb.meta);
		textprintf_centre_ex(buff, Fira_Code_16, 1115, 495, makecol(230, 230, 230), -1, "%ix", jdb.odd);
		textprintf_centre_ex(buff, Fira_Code_16, 1125, 597, makecol(230, 230, 230), -1, "%i", jogador.ValorAposta);
		
		//KEYS SETAS
		if(key[KEY_DOWN]){if(linha <= 2){rest(100);linha++;som = 1;}}
		
		if(key[KEY_UP]){if(linha >= 1){rest(100);linha--;som = 1;}}
		
		if(key[KEY_RIGHT]){if(coluna <= 4){rest(100);coluna++;som = 1;}}
		
		if(key[KEY_LEFT]){if(coluna >= 1){rest(100);coluna--;som = 1;}}
		
		if(key[KEY_W]){rest(100);if(jogador.ValorAposta + 10 <= jogador.dinheiro){jogador.ValorAposta += 10;som = 1;}}
		
		if(key[KEY_S]){rest(100);if(jogador.ValorAposta - 10 > 0){jogador.ValorAposta -= 10;som = 1;}}
		
		//TRATAMENTO DE ERRO DE SOM0
		if(key[KEY_RIGHT] && key[KEY_LEFT]){som = 0;}
		
		if(key[KEY_UP] && key[KEY_DOWN]){som = 0;}
		
		//BOTÃ•ES
		if(key[KEY_ENTER] && ((linha >= 0 && linha <= 3) && (coluna >= 0 && coluna <= 5))){
			
			strcpy(jogador.aposta, animais[(linha + coluna) + (linha * 5)]);	//jogador.aposta = animal em que o jogador apertou enter
			strcpy(jdb.AnimalSorteado, animais[rand()%1]);	//jdb.AnimalSorteado = animal aleatorio
			
			if(CmpStrValues(jogador.aposta, jdb.AnimalSorteado)){
				jogador.dinheiro += jogador.ValorAposta * jdb.odd;
				if((jogador.felicidade += 10) >= 100){jogador.felicidade = 100;}else{jogador.felicidade += 10;}
				if((jogador.estresse -= 10) <= 0){jogador.estresse = 0;}else{jogador.estresse -= 10;}
			}
			else{
				jogador.dinheiro -= jogador.ValorAposta;
				jogador.felicidade -= 10;
				jogador.estresse += 10;
			}
			jdb.odd = 200/jogador.felicidade;
			
			if(jogador.dinheiro <= 0){
				printf("Vocde Faliu");
			}
			else if(jogador.dinheiro >= jdb.meta){
				return 1;
			}
		}
		
		//TAXA DE ATUALIZAÃ‡ÃƒO DA TELA
		rest(70);
		
		//SOM	
		if(som){play_sample(select, 80, 128, 1000, 0); som = 0;}
		
		//DRAW CHAVE
		if(timer > 2) draw_sprite(buff, chave, chx, chy);
		
		//DRAW BUFFER
		draw_sprite(screen, buff, 0, 0);
	}
	return 0;
}

int SaveScreen(BITMAP *buff, Player jogador){	//TELA PARA CRIAR UM NOVO SAVE 
	_sleep(100);
	
	//VARIAVEIS LOCAIS E BITMAPS
	menu = load_bitmap("../Others/Slots.bmp", NULL);
	chave = load_bitmap("../Others/chave_slots.bmp", NULL);
	
	int chx = 291, chy = 30, py[3] = {30, 222, 419};
	int linha = 0, control = 1;
	
	//FONTES
	Fira_Code_16  = load_font("../Fontes/Fira_Code_16A.pcx", NULL, NULL);
	
	while(!key[KEY_ESC]){
		chy = py[linha];
		clear_bitmap(buff);
		draw_sprite(buff, menu, 0, 0);
		
		//KEY ARROWS
		if(key[KEY_DOWN]){rest(100);if(linha <= 1){linha++;som = 1;}}
		if(key[KEY_UP]){rest(100);if(linha >= 1){linha--;som = 1;}}
		
		//TRATAMENTO DE ERRO DE SOM
		if(key[KEY_UP] && key[KEY_DOWN]){rest(100);som = 0;}
		
		//KEY BUTTONS
		if(key[KEY_ENTER] && linha == 0){	//PRIMEIRO SLOT
			SetSave(jogador, 1);
			return 1;
		}
		else if(key[KEY_ENTER] && linha == 1){	//PRIMEIRO SLOT
			SetSave(jogador, 2);
			return 1;
		}
		else if(key[KEY_ENTER] && linha == 2){	//PRIMEIRO SLOT
			SetSave(jogador, 3);
			return 1;
		}
		
		//TRATAMENTO DE DELAY
		rest(30);
		
		//SOM
		if(som){play_sample(select, 80, 128, 1000, 0); som = 0;}
		
		//DRAW CHAVE
		draw_sprite(buff, chave, chx, chy);
		
		//DRAW BUFFER
		draw_sprite(screen, buff, 0, 0);
	}
}

int LoadScreen(BITMAP *buff, Player jogador){	//TELA PARA CARREGAR UM SAVE EXISTENTE
	_sleep(100);
	
	//VARIAVEIS LOCAIS E BITMAPS
	menu = load_bitmap("../Others/Slots.bmp", NULL);
	chave = load_bitmap("../Others/chave_slots.bmp", NULL);
	
	int chx = 291, chy = 30, py[3] = {30, 222, 419};
	int linha = 0;
	
	//FONTES
	Fira_Code_16  = load_font("../Fontes/Fira_Code_16A.pcx", NULL, NULL);
	
	while(!key[KEY_ESC]){
		chy = py[linha];
		clear_bitmap(buff);
		draw_sprite(buff, menu, 0, 0);
		
		//KEY ARROWS
		if(key[KEY_DOWN]){rest(100);if(linha <= 1){linha++;som = 1;}}
		if(key[KEY_UP]){rest(100);if(linha >= 1){linha--;som = 1;}}
		
		//KEY BUTTONS
		if(key[KEY_ENTER] && linha == 0){	//PRIMEIRO SLOT
		}
		else if(key[KEY_ENTER] && linha == 1){ //SEGUNDO SLOT
		}
		else if(key[KEY_ENTER] && linha == 2){ //TERCEIRO SLOT
		}
		
		//TRATAMENTO DE ERRO DE SOM
		if(key[KEY_UP] && key[KEY_DOWN]){rest(100);som = 0;}
		
		//TRATAMENTO DE DELAY
		rest(30);
		
		//SOM
		if(som){play_sample(select, 80, 128, 1000, 0); som = 0;}
		
		//DRAW CHAVE
		draw_sprite(buff, chave, chx, chy);
		
		//DRAW BUFFER
		draw_sprite(screen, buff, 0, 0);
		
		while(timer == delay){};
	}
	return 0;
}

void SetSave(Player jogador, int slot){	//FUNÇÃO PARA GRAVAR DADOS EM TXT
	if(slot == 1){
		FILE *file = fopen("../Saves/slot_1.txt", "w");
		fprintf(file, "%s %d %d %d %d", jogador.personagem, jogador.dia, jogador.dinheiro, jogador.estresse, jogador.felicidade);
		fclose(file);
	}
	else if(slot == 2){
		FILE *file = fopen("../Saves/slot_2.txt", "w");
		fprintf(file, "%s %d %d %d %d", jogador.personagem, jogador.dia, jogador.dinheiro, jogador.estresse, jogador.felicidade);
		fclose(file);
	}
	else if(slot == 3){
		FILE *file = fopen("../Saves/slot_3.txt", "w");
		fprintf(file, "%s %d %d %d %d", jogador.personagem, jogador.dia, jogador.dinheiro, jogador.estresse, jogador.felicidade);
		fclose(file);
	}
}

void Blackjack(BITMAP *buff){
	srand(time(NULL));
	
	jogador.ValorAposta = 0;
	
	//VARIAVEIS LOCAIS E BITMAPS
	menu = load_bitmap("../Blackjack/cards/blackjack_table.bmp", NULL);
	
	Minecraft_20 = load_font("../Fontes/Minecraft_20.pcx", NULL, NULL);
	Minecraft_16 = load_font("../Fontes/Minecraft_16.pcx", NULL, NULL);
	Minecraft_10 = load_font("../Fontes/Minecraft_10.pcx", NULL, NULL);
	
	BITMAP *Msg_blackjack = load_bitmap("../Blackjack/MsgBlackjack.bmp", NULL);
	BITMAP *red_card = load_bitmap("../Blackjack/cards/red_card.bmp", NULL); //ouro
	BITMAP *black_card = load_bitmap("../Blackjack/cards/black_card.bmp", NULL); //paus
	
	char cards[] = {'A', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K'};
	int dcards[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	int rx = 773, ry = 315, rc_index = -1;
	
	int n1 = rand() % 14, n2 = rand() % 14;
	
	while(!key[KEY_ESC]){
		srand(time(NULL));
		clear_bitmap(buff);

		draw_sprite(buff, menu, 0, 0);
		draw_sprite(buff, Msg_blackjack, 465, 123);
		
		//DINHEIRO
		textprintf_centre_ex(buff, Minecraft_16, 675, 475, makecol(255, 255, 255), -1, "%i", jogador.dinheiro);
		
		//MSG
		textprintf_centre_ex(buff, Minecraft_10, 640, 138, makecol(0, 0, 0), -1, "%s", "Defina sua aposta atraves das setas");
		
		//APOSTA
		textprintf_centre_ex(buff, Minecraft_16, 1035, 595, makecol(255, 255, 255), -1, "%i", jogador.ValorAposta);
		
		//ARROW KEYS
		if(key[KEY_UP] && (jogador.ValorAposta + 20 <= jogador.dinheiro)){
			rest(200);
			jogador.ValorAposta += 20;
		}
		else if(key[KEY_UP] && jogador.ValorAposta + 20 > jogador.dinheiro){
			jogador.ValorAposta = jogador.dinheiro;
		}
		
		//CARTAS
		//draw_sprite(buff, red_card, 550, 590);
		//draw_sprite(buff, red_card, 650, 590);
		
		
		//DRAW BUFFER
		draw_sprite(screen, buff, 0, 0);
	}
	return 0;
}

int CCards(int n1, int n2, int n3[]){
	if(n1 >= 10){n1 = 10;}
	if(n2 >= 10){n2 = 10;}
	
	if(n1 <= 1){n1 = 1;}
	if(n2 <= 1){n2 = 1;}
	
	int result = n1 + n2;
	
	int i;
	
	for(i = 0; i < 19; i++){
		if(n3[i] >= 10){n3[i] = 10;}
		result += n3[i];
	}

	return result;
}


