
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <string.h>
#include "Func.h"


Player jogador;

//VARIAVEIS GLOBAIS
FONT *Minecraft_20;
FONT *Minecraft_16;
FONT *Minecraft_10;

BITMAP *chave;
BITMAP *menu;
SAMPLE *select;

int control;

int delay = 0;
int timer = 0;
int som = 0;
int go = 0;

volatile int milisegundos;

void msec_time(){
	milisegundos++;
}

Player GetSave(int slot){
	Player getsave;
	if(slot == 1){
		FILE *file = fopen("../Saves/slot_1.txt", "r");
		fscanf(file, "%s %d %d %d %d", &getsave.personagem, &getsave.dia, &getsave.dinheiro, &getsave.estresse, &getsave.felicidade);
		fclose(file);
	}
	if(slot == 2){
		FILE *file = fopen("../Saves/slot_2.txt", "r");
		fscanf(file, "%s %d %d %d %d", &getsave.personagem, &getsave.dia, &getsave.dinheiro, &getsave.estresse, &getsave.felicidade);
		fclose(file);
	}
	if(slot == 3){
		FILE *file = fopen("../Saves/slot_3.txt", "r");
		fscanf(file, "%s %d %d %d %d", &getsave.personagem, &getsave.dia, &getsave.dinheiro, &getsave.estresse, &getsave.felicidade);
		fclose(file);
	}
	
	return getsave;
}

void tempo(){timer++;}

int main(){
	
	init();
	set_window_title("Cassino Simulator");  // Titulo da janela;
	
	//BITMAPS
	BITMAP *buff  = create_bitmap(1280, 720);
	select = load_sample("../Sounds/select.wav"); //som select
	
	Jogo(Menu(buff), buff);

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
	install_int_ex(tempo, MSEC_TO_TIMER(1)); //N SEI PRA QUE SERVE, MAS N É PRA TIRAR
}

void deinit() {
	clear_keybuf();
	exit(0);
}

int Menu(BITMAP *buff){

	menu = load_bitmap("../Main_Menu/main_menu.bmp", NULL);
	chave = load_bitmap("../Main_Menu/main_chave.bmp", NULL);
    BITMAP *select = load_sample("../Sounds/select.wav"); //som select

	//VARIAVEIS LOCAIS
	int py[5]= {358, 405, 457, 505, 551};
	int linha = 0, chx  =  551;
	
	while(!key[KEY_ESC]){
		int chy = py[linha];
		delay = timer;
		
		clear_bitmap(buff);
		
		draw_sprite(buff, menu, 0, 0);

		//KEYS SETAS
		if(key[KEY_DOWN] && linha != 4){rest(150);linha++;som = 1;}else if(key[KEY_DOWN] && linha == 4){rest(150);som = 1;linha = 0;}
		
		if(key[KEY_UP] && linha != 0){rest(150);linha--;;som = 1;}else if(key[KEY_UP] && linha == 0){rest(150);som = 1;linha = 4;}
		
		//TRATAMENTO DE ERRO DE SOM
		if(key[KEY_UP] && key[KEY_DOWN]){rest(100);som = 0;}
		
		//BOT�ES
		if(key[KEY_ENTER] && linha == 0){rest(100);if(SelectScreen(buff) == 1){return 1;}}//JOGAR
		
		else if(key[KEY_ENTER] && linha == 1){rest(100); if(LoadScreen(buff) == 0){rest(100);}else{return jogador.dia;}}//CARREGAR JOGO
		
		if(key[KEY_ENTER] && linha == 2){rest(100); Creditos(buff);} //Creditos

		if(key[KEY_ENTER] && linha == 3){rest(100); Opcoes(buff);} //Opções

		if(key[KEY_ENTER] && linha == 4){rest(100);return 0;} //SAIR
		
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
}
 
int SelectScreen(BITMAP *buff){
	menu = load_bitmap("../Menu_Select/menu_select.bmp", NULL);
	chave = load_bitmap("../Menu_select/chave_menu_select.bmp", NULL);

	//DELAY ENTRE TELAS
	_sleep(200); 
	
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
			jogador.dinheiro = 100;
			jogador.felicidade = 100;
			jogador.estresse = 0;
			jogador.dia = 1;

			if(SaveScreen(buff) == 1){dia(buff, 0); noite(buff, 0); return 1;};
			
		}
		
		else if(key[KEY_ENTER] && coluna == 1){ //SELECT ELENA
			strcpy(jogador.personagem, "Elena");
			jogador.dinheiro = 100;
			jogador.felicidade = 100;
			jogador.estresse = 0;
			jogador.dia = 1;
			
			if(SaveScreen(buff) == 1){dia(buff, 1); noite(buff, 1); return 1;};
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
	destroy_bitmap(menu);
	destroy_bitmap(chave);

	menu = load_bitmap("../Main_Menu/main_menu.bmp", NULL);
	chave = load_bitmap("../Main_Menu/main_chave.bmp", NULL);
	rest(200);
}

int JogoDoBicho(BITMAP *buff){
	
	srand(time(NULL));

	//VARIAVEIS LOCAIS E BITMAPS
	menu = load_bitmap("../Jogo_Do_Bicho/jdb_menu.bmp", NULL);
	chave = load_bitmap("../Jogo_Do_Bicho/jdb_chave.bmp", NULL);
	
	//FONTES
	Minecraft_16  = load_font("../Fontes/Minecraft_16.pcx", NULL, NULL);
	
	int linha = 0, coluna = 0, px[6] = {38, 196, 352, 508, 664, 822}, py[4] = {65, 221, 377, 534}; //MOVIMENT
	int meta = 200, ValorAposta = 10;
	
	//DELAY ENTRE TELAS
	_sleep(200);
	
	while(!key[KEY_ESC]){
		
		int chx  =  px[coluna], chy = py[linha];
		int odd = 16;
		int cor[] = {255, 255, 255};
		
		clear_bitmap(buff);
		
		draw_sprite(buff, menu, 0, 0);	
		
		//KEYS SETAS
		if(key[KEY_DOWN]){if(linha <= 2){rest(100);linha++;som = 1;}}
		
		if(key[KEY_UP]){if(linha >= 1){rest(100);linha--;som = 1;}}
		
		if(key[KEY_RIGHT]){if(coluna <= 4){rest(100);coluna++;som = 1;}}
		
		if(key[KEY_LEFT]){if(coluna >= 1){rest(100);coluna--;som = 1;}}
		
		//TRATAMENTO DE ERRO DE SOM0
		if(key[KEY_RIGHT] && key[KEY_LEFT]){som = 0;}
		
		if(key[KEY_UP] && key[KEY_DOWN]){som = 0;}

		//KEY SET APOSTA
		if(key[KEY_W] && ValorAposta + 10 <= jogador.dinheiro){rest(100);ValorAposta += 10;som = 1;}
		else if(key[KEY_W] && ValorAposta + 10 >= jogador.dinheiro){cor[0] = 210;cor[1] = 100;cor[2] = 100;}

		if(key[KEY_S] && ValorAposta - 10 >= 10){rest(100);ValorAposta -= 10;som = 1;}
		else if(key[KEY_S] && ValorAposta - 10 <= jogador.dinheiro){cor[0] = 210;cor[1] = 100;cor[2] = 100;}

		//TEXT PRINTS
		{
			textprintf_centre_ex(buff, Minecraft_10, 1115, 140, makecol(255, 255, 255), -1, "RS %i,00", jogador.dinheiro);
			textprintf_centre_ex(buff, Minecraft_10, 1115, 230, makecol(255, 255, 255), -1, "%i", jogador.felicidade);
			textprintf_centre_ex(buff, Minecraft_10, 1115, 320, makecol(255, 255, 255), -1, "%i", jogador.estresse);
			textprintf_centre_ex(buff, Minecraft_10, 1115, 410, makecol(255, 255, 255), -1, "%i", meta);
			textprintf_centre_ex(buff, Minecraft_10, 1115, 505, makecol(255, 255, 255), -1, "%ix", odd);
			textprintf_centre_ex(buff, Minecraft_10, 1131, 607, makecol(cor[0], cor[1], cor[2]), -1, "RS %i,00", ValorAposta);
		}
		
			

		//BOT�ES
		if(key[KEY_ENTER] && ((linha >= 0 && linha <= 3) && (coluna >= 0 && coluna <= 5))){
			char animal[15], AnimalAposta[15];
			int numero = (rand() % 24);
			if(numero == 24){numero = 23;}
			
			strcpy(animal, animais[numero]);
			strcpy(AnimalAposta, animais[(linha + coluna) + (linha * 5)]);
			
			if(CmpStrValues(AnimalAposta, animal)){
				jogador.dinheiro += ValorAposta * odd;
				if(jogador.felicidade + 10 < 100){jogador.felicidade += 10;}
				if(jogador.estresse - 10 > 0){jogador.estresse -= 10;}
				Confirm_Box(buff, "../Others/Confirm_Box.bmp", 380, 240, AnimalAposta, animal, jogador.dinheiro);
				rest(100);
			}
			else{
				jogador.dinheiro -= ValorAposta;
				if(jogador.felicidade - 10 >= 0){jogador.felicidade -= 10;}
				if(jogador.estresse + 10 <= 100){jogador.estresse += 10;}
				Confirm_Box(buff, "../Others/Confirm_Box.bmp", 380, 240, AnimalAposta, animal, jogador.dinheiro);
				rest(100);
			}
		}
		if(ValorAposta > jogador.dinheiro){ValorAposta = jogador.dinheiro;}//TRATANDO ERRO DE VALOR DE APOSTA

		if(jogador.dinheiro <= 0 ){Lose_Screen(buff);break;}
		else if(jogador.dinheiro >= meta){jogador.dia = 2;Win_Screen(buff);TeleSena(buff);}

		//TAXA DE ATUALIZAÇÃO DA TELA
		rest(70);
		
		//SOM	
		if(som){play_sample(select, 80, 128, 1000, 0); som = 0;}
		
		//DRAW CHAVE
		if(timer > 2) draw_sprite(buff, chave, chx, chy);
		
		//DRAW BUFFER
		draw_sprite(screen, buff, 0, 0);
	}
	exit(0);
}

int SaveScreen(BITMAP *buff){	//TELA PARA CRIAR UM NOVO SAVE 
	_sleep(100);
	
	//VARIAVEIS LOCAIS E BITMAPS
	menu = load_bitmap("../Others/Slots.bmp", NULL);
	chave = load_bitmap("../Others/chave_slots.bmp", NULL);
	
	Minecraft_10 = load_font("../Fontes/Minecraft_10.pcx", NULL, NULL);
	Minecraft_16 = load_font("../Fontes/Minecraft_16.pcx", NULL, NULL);
	
	int chx = 323, chy = 30, py[3] = {30, 222, 419};
	int linha = 0, control = 1;
	
	
	while(!key[KEY_ESC]){
		chy = py[linha];
		clear_bitmap(buff);
		draw_sprite(buff, menu, 0, 0);

		//PRINT SLOTS
		{
			//TEXT SLOTS
			Player slot1;
			Player slot2;
			Player slot3;
			
			//SLOT 1
			slot1 = GetSave(1);
			if(CmpStrValues(slot1.personagem, "Jhon") || CmpStrValues(slot1.personagem, "Elena")){
				textprintf_centre_ex(buff, Minecraft_10, 653, 95, makecol(255, 255, 255), -1, "Personagem: %s       Dinheiro: %i       Dia: %i", slot1.personagem, slot1.dinheiro, slot1.dia);
				textprintf_centre_ex(buff, Minecraft_10, 658, 145, makecol(255, 255, 255), -1, "Felicidade: %i       Estresse: %i", slot1.felicidade, slot1.estresse);
			}
			else {
				textprintf_centre_ex(buff, Minecraft_16, 675, 115, makecol(255, 255, 255), -1, "%s", "SLOT VAZIO");
			}
			
			//SLOT 2
			slot2 = GetSave(2);
			if(CmpStrValues(slot2.personagem, "Jhon") || CmpStrValues(slot2.personagem, "Elena")){
				textprintf_centre_ex(buff, Minecraft_10, 653, 295, makecol(255, 255, 255), -1, "Personagem: %s       Dinheiro: %i       Dia: %i", slot2.personagem, slot2.dinheiro, slot2.dia);
				textprintf_centre_ex(buff, Minecraft_10, 658, 345, makecol(255, 255, 255), -1, "Felicidade: %i       Estresse: %i", slot2.felicidade, slot2.estresse);
			}
			else{
				textprintf_centre_ex(buff, Minecraft_16, 675, 315, makecol(255, 255, 255), -1, "%s", "SLOT VAZIO");
			}
			
			//SLOT 3
			slot3 = GetSave(3);
			if(CmpStrValues(slot3.personagem, "Jhon") || CmpStrValues(slot3.personagem, "Elena")){
				textprintf_centre_ex(buff, Minecraft_10, 653, 495, makecol(255, 255, 255), -1, "Personagem: %s       Dinheiro: %i       Dia: %i", slot3.personagem, slot3.dinheiro, slot3.dia);
				textprintf_centre_ex(buff, Minecraft_10, 658, 545, makecol(255, 255, 255), -1, "Felicidade: %i       Estresse: %i", slot3.felicidade, slot3.estresse);
			}
			else{
				textprintf_centre_ex(buff, Minecraft_16, 675, 515, makecol(255, 255, 255), -1, "%s", "SLOT VAZIO");
			}
		}
		
		//KEY ARROWS
		if(key[KEY_DOWN]){rest(100);if(linha <= 1){linha++;som = 1;}}
		if(key[KEY_UP]){rest(100);if(linha >= 1){linha--;som = 1;}}
		
		//TRATAMENTO DE ERRO DE SOM
		if(key[KEY_UP] && key[KEY_DOWN]){rest(100);som = 0;}
		
		//KEY BUTTONS
		if(key[KEY_ENTER] && linha == 0){	//PRIMEIRO SLOT
			return SetSave(jogador, 1);
		}
		else if(key[KEY_ENTER] && linha == 1){	//PRIMEIRO SLOT
			//dia();
			return SetSave(jogador, 2);
		}
		else if(key[KEY_ENTER] && linha == 2){	//PRIMEIRO SLOT
			//dia();
			return SetSave(jogador, 3);
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
	destroy_bitmap(menu);
	destroy_bitmap(chave);

	menu = load_bitmap("../Menu_Select/menu_select.bmp", NULL);
	chave = load_bitmap("../Menu_select/chave_menu_select.bmp", NULL);
}

int LoadScreen(BITMAP *buff){	//TELA PARA CARREGAR UM SAVE EXISTEN
	_sleep(100);
	
	//VARIAVEIS LOCAIS E BITMAPS
	menu = load_bitmap("../Others/Slots.bmp", NULL);
	chave = load_bitmap("../Others/chave_slots.bmp", NULL);
	
	int chx = 323, chy = 30, py[3] = {30, 222, 419};
	int linha = 0;
	
	//FONTES
	Minecraft_10  = load_font("../Fontes/Minecraft_10.pcx", NULL, NULL);
	Minecraft_16  = load_font("../Fontes/Minecraft_16.pcx", NULL, NULL);
	
	while(!key[KEY_ESC]){
		chy = py[linha];
		clear_bitmap(buff);
		draw_sprite(buff, menu, 0, 0);
		
		//TEXT SLOTS
		Player slot1;
		Player slot2;
		Player slot3;
		
		//SLOT 1
		slot1 = GetSave(1);
		if(CmpStrValues(slot1.personagem, "Jhon") || CmpStrValues(slot1.personagem, "Elena")){
			textprintf_centre_ex(buff, Minecraft_10, 653, 95, makecol(255, 255, 255), -1, "Personagem: %s       Dinheiro: %i       Dia: %i", slot1.personagem, slot1.dinheiro, slot1.dia);
			textprintf_centre_ex(buff, Minecraft_10, 658, 145, makecol(255, 255, 255), -1, "Felicidade: %i       Estresse: %i", slot1.felicidade, slot1.estresse);
		}
		else {
			textprintf_centre_ex(buff, Minecraft_16, 675, 115, makecol(255, 255, 255), -1, "%s", "SLOT VAZIO");
		}
		
		//SLOT 2
		slot2 = GetSave(2);
		if(CmpStrValues(slot2.personagem, "Jhon") || CmpStrValues(slot2.personagem, "Elena")){
			textprintf_centre_ex(buff, Minecraft_10, 653, 295, makecol(255, 255, 255), -1, "Personagem: %s       Dinheiro: %i       Dia: %i", slot2.personagem, slot2.dinheiro, slot2.dia);
			textprintf_centre_ex(buff, Minecraft_10, 658, 345, makecol(255, 255, 255), -1, "Felicidade: %i       Estresse: %i", slot2.felicidade, slot2.estresse);
		}
		else{
			textprintf_centre_ex(buff, Minecraft_16, 675, 315, makecol(255, 255, 255), -1, "%s", "SLOT VAZIO");
		}
		
		//SLOT 3
		slot3 = GetSave(3);
		if(CmpStrValues(slot3.personagem, "Jhon") || CmpStrValues(slot3.personagem, "Elena")){
			textprintf_centre_ex(buff, Minecraft_10, 653, 495, makecol(255, 255, 255), -1, "Personagem: %s       Dinheiro: %i       Dia: %i", slot3.personagem, slot3.dinheiro, slot3.dia);
			textprintf_centre_ex(buff, Minecraft_10, 658, 545, makecol(255, 255, 255), -1, "Felicidade: %i       Estresse: %i", slot3.felicidade, slot3.estresse);
		}
		else{
			textprintf_centre_ex(buff, Minecraft_16, 675, 515, makecol(255, 255, 255), -1, "%s", "SLOT VAZIO");
		}
		
		//KEY ARROWS 
		if(key[KEY_DOWN]){rest(100);if(linha <= 1){linha++;som = 1;}}
		if(key[KEY_UP]){rest(100);if(linha >= 1){linha--;som = 1;}}
		
		//KEY BUTTONS
		if(key[KEY_ENTER] && linha == 0){	//PRIMEIRO SLOT
			jogador = GetSave(1);
			return jogador.dia;
		}
		else if(key[KEY_ENTER] && linha == 1){ //SEGUNDO SLOT
			jogador = GetSave(2);
			return jogador.dia;
		}
		else if(key[KEY_ENTER] && linha == 2){ //TERCEIRO SLOT
			jogador = GetSave(3);
			return jogador.dia;
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
	destroy_bitmap(menu);
	destroy_bitmap(chave);
	destroy_font(Minecraft_10);
	destroy_font(Minecraft_16);

	menu = load_bitmap("../Main_Menu/main_menu.bmp", NULL);
	chave = load_bitmap("../Main_Menu/main_chave.bmp", NULL);
	return 0;
}

int SetSave(Player jogador, int slot){	//FUNÇÃO PARA GRAVAR DADOS EM TXT
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
	return 1;	
}

void Confirm_Box(BITMAP *buff, char arquivo[], int x, int y, char aposta[], char animal[], int dinheiro){
	BITMAP *confirm_box = load_bitmap(arquivo, NULL);
	
	while(!key[KEY_ESC]){
		draw_sprite(buff, confirm_box, x, y);
		textprintf_centre_ex(buff, Minecraft_16, 640, 260, makecol(255, 255, 255), -1, "Escolhido = %s", aposta);
		textprintf_centre_ex(buff, Minecraft_16, 640, 300, makecol(255, 255, 255), -1, "Sorteado = %s", animal);
		textprintf_centre_ex(buff, Minecraft_16, 640, 340, makecol(255, 255, 255), -1, "Seu novo saldo e = R$ %i,00", dinheiro);
		draw_sprite(screen, buff, 0, 0);
	}
	rest(30);
}

void Jogo(int dia, BITMAP *buff){
	switch (dia){
	case 1:
		JogoDoBicho(buff);
		break;

	case 2:
		//TeleSena(buff);
		break;
	
	default:
		printf("Algo deu errado");
		break;
	}
}

void Win_Screen(BITMAP *buff){
	int NFrames = 20;
	int frame = 0;
	int TempoDeTroca = 60;

	BITMAP *monkey[20];

	char *path;

	for(int i = 0; i <= 19; i++){
		asprintf(&path, "../gifs/Monkey/monkey (%d).bmp", i+1);
		monkey[i] = load_bitmap(path, NULL);
	}

	BITMAP *background = load_bitmap("../Others/win_screen.bmp", NULL);

	while(1){
		clear(buff);

		frame = (timer / TempoDeTroca) % NFrames;
		
		draw_sprite(buff, background, 0, 0);

		if(key[KEY_ENTER] || key[KEY_ESC]){break;}

		draw_sprite(buff, monkey[frame], 600, 210);

		draw_sprite(screen, buff, 0, 0);
	}
}

void Lose_Screen(BITMAP *buff){
	int NFrames = 91;
	int frame = 0;
	int TempoDeTroca = 30;

	BITMAP *crash[91];

	char *path;

	for(int i = 0; i <= 90; i++){
		asprintf(&path, "../gifs/creu_crash/crash (%d).bmp", i+1);
		crash[i] = load_bitmap(path, NULL);
	}

	BITMAP *background = load_bitmap("../Others/lose_screen.bmp", NULL);

	while(!key[KEY_ESC]){
		clear(buff);

		draw_sprite(buff, background, 0, 0);

		frame = (timer / TempoDeTroca) % NFrames;

		if(key[KEY_ENTER] || key[KEY_ESC]){break;}

		draw_sprite(buff, crash[frame], 520, 170);

		draw_sprite(screen, buff, 0, 0);
	}
}

void TeleSena(BITMAP *buff){
	//srand(time(NULL));
	jogador.dinheiro = 300;
	menu = load_bitmap("../TeleSena/TeleSena.bmp", NULL);
	chave = load_bitmap("../TeleSena/chave_telesena.bmp", NULL);

	Minecraft_16  = load_font("../Fontes/Minecraft_16.pcx", NULL, NULL);
	Minecraft_20  = load_font("../Fontes/Minecraft_20.pcx", NULL, NULL);

	int xs[2] = {985, 1095}, ys = 468, coluna = 0;
	int dezena = 0, unidade = 0, apostas[6] = {0, 0, 0, 0, 0, 0}, sorteados[6], enter = 0, acertos = 0;
	int valor_aposta = 30;

	while(!key[KEY_ESC]){
		clear_bitmap(buff);
		draw_sprite(buff, menu, 0, 0);

		if(key[KEY_W] && valor_aposta + 30 <= jogador.dinheiro){rest(150); valor_aposta += 30; som = 1;}
		if(key[KEY_S] && valor_aposta - 30 >= 30){rest(150); valor_aposta -= 30; som = 1;}

		if(key[KEY_RIGHT] && coluna == 0){rest(100);coluna++;som = 1;}
		if(key[KEY_LEFT] && coluna == 1){rest(100);coluna--;som = 1;}

		if(key[KEY_UP] && coluna == 0 && dezena < 5){rest(150);dezena++;som = 1;}
		if(key[KEY_DOWN] && coluna == 0 && dezena > 0){rest(150);dezena--;som = 1;}

		if(key[KEY_UP] && coluna == 1 && unidade < 9){rest(150);unidade++;som = 1;}
		if(key[KEY_DOWN] && coluna == 1 && unidade > 0){rest(150);unidade--;som = 1;}

		if(key[KEY_ENTER] &&((dezena * 10 + unidade > 0) && (enter < 6))){
			int resp = 0;

			for(int i = 0; i < 6; i++){
				if(apostas[i] == dezena * 10 + unidade){
					resp = 1;
				}
				sorteados[i] = i+1;//(rand() % 59) + 1;
			}

			if(resp == 0){
				apostas[enter] = dezena * 10 + unidade;
				if(enter < 6){enter++;}
			}

			rest(150);
		}
		else if(key[KEY_ENTER] && enter == 6){
			enter = 0;

			if(acertos == 6){
				jogador.dinheiro = valor_aposta * 100;
			}
			else {
				jogador.dinheiro -= valor_aposta;
			}

			for(int pos = 0; pos < 6; pos++){
				apostas[pos] = 0;
			}
		}

		if(enter == 6){
			textprintf_centre_ex(buff, Minecraft_16, 464, 495, makecol(255, 255, 255), -1, "%i %i %i %i %i %i", sorteados[0], sorteados[1], sorteados[2], sorteados[3], sorteados[4], sorteados[5]);
			textprintf_centre_ex(buff, Minecraft_20, 464, 311, makecol(255, 255, 255), -1, "Voce acertou %i numeros", acertos);
			textprintf_centre_ex(buff, Minecraft_20, 640, 680, makecol(255, 255, 255), -1, "Aperte enter");
		}

		acertos = conta(apostas, sorteados);

		if(jogador.dinheiro <= 0){
			rest(200);
			Lose_Screen(buff);
		}
		else if(jogador.dinheiro >= 1200){
			rest(200);
			enter = 0;
			Win_Screen(buff);
		}

		textprintf_centre_ex(buff, Minecraft_16, 464, 195, makecol(255, 255, 255), -1, "%i %i %i %i %i %i", apostas[0], apostas[1], apostas[2], apostas[3], apostas[4], apostas[5]);

		textprintf_centre_ex(buff, Minecraft_16, 1015, 490, makecol(255, 255, 255), -1, "%i", dezena);
		textprintf_centre_ex(buff, Minecraft_16, 1125, 490, makecol(255, 255, 255), -1, "%i", unidade);
		
		textprintf_centre_ex(buff, Minecraft_16, 1074, 209, makecol(255, 255, 255), -1, "RS %i,00", jogador.dinheiro);
		textprintf_centre_ex(buff, Minecraft_16, 1074, 355, makecol(255, 255, 255), -1, "RS %i,00", valor_aposta);

		draw_sprite(buff, chave, xs[coluna], ys);

		if(som){play_sample(select, 80, 128, 1000, 0); som = 0;}
		draw_sprite(screen, buff, 0, 0);

	}
	
	return 0;
}

int conta(int vetor1[], int vetor2[]){
	int acertos = 0;

	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			if(vetor1[i] == vetor2[j]){acertos++;}
		}
	}

	return acertos;
}

void Creditos(BITMAP *buffer){
	
	BITMAP * background = load_bitmap("../Creditos/creditos.bmp", NULL);

	Minecraft_16  = load_font("../Fontes/Minecraft_16.pcx", NULL, NULL);

	while(!key[KEY_ESC])
	{
		clear_bitmap(buffer);
		draw_sprite(buffer, background, 0, 0);

		/*textprintf_ex(buffer, Minecraft_16, 400, 15, makecol(255, 255 , 255), -1, "%s", "CREDITOS");
		textprintf_ex(buffer, Minecraft_16, 50, 100, makecol(255, 255 , 255), -1, "%s", "Codificacao por: Luiz Otavio de Souza Porto Neves, Pedro Henrique de Paula Crepaldi e Vitor Silva Oliveira");
		textprintf_ex(buffer, Minecraft_16, 50, 150, makecol(255, 255 , 255), -1, "%s", "Design grafico por: Pedro Arthur Goncalves de Paula e Vitor Silva Oliveira");
		textprintf_ex(buffer, Minecraft_16, 50, 200, makecol(255, 255 , 255), -1, "%s", "Documentacao por: Jose Carlos e Pedro Arthur Goncalves de Paula");
		textprintf_ex(buffer, Minecraft_16, 50, 250, makecol(255, 255 , 255), -1, "%s", "Gestao de tarefas por: Luiz Otavio de Souza Porto Neves");
		textprintf_ex(buffer, Minecraft_16, 50, 300, makecol(255, 255 , 255), -1, "%s", "Video de divulgacao por: Pedro Arthur Goncalves de Paula e Pedro Henrique de Paula Crepaldi");

		textprintf_ex(buffer, Minecraft_16, 50, 350, makecol(255, 255 , 255), -1, "%s", "Relatorios por: Jose Carlos e Pedro Henrique de Paula Crepaldi");
		*/
		draw_sprite(screen, buffer, 0, 0);
		rest(35);
	}
	rest(200);
	destroy_bitmap(background);
	destroy_font(Minecraft_16);

	menu = load_bitmap("../Main_Menu/main_menu.bmp", NULL);
	chave = load_bitmap("../Main_Menu/main_chave.bmp", NULL);
}

void Opcoes(BITMAP *buff){

	BITMAP *background = load_bitmap("../Opções/background.bmp", NULL);
	int cor[] = {255, 48, 48}, x[] = {752, 813}, pos = 0;

	while(!key[KEY_BACKSPACE]){
		clear_bitmap(buff);
		draw_sprite(buff, background, 0, 0);

		if(key[KEY_ENTER] && pos == 0){rest(150); pos = 1; cor[0] = 44; cor[1] = 191; cor[2] = 69; set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1280, 720, 0, 0);}
		if(key[KEY_ENTER] && pos == 1){rest(150); pos = 0; cor[0] = 255; cor[1] = 48; cor[2] = 48; set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1280, 720, 0, 0);}


		circlefill(buff, x[pos], 362, 21, makecol(cor[0], cor[1], cor[2]));

		draw_sprite(screen, buff, 0, 0);
	}
	destroy_bitmap(background);
	
	menu = load_bitmap("../Main_Menu/main_menu.bmp", NULL);
	chave = load_bitmap("../Main_Menu/main_chave.bmp", NULL);
}

void dia(BITMAP *buffer, int sexo){
	int x = 0, y = 0;//COORDENADAS X E Y
	int num_frames = 3;
	int frame_atual = 0;
	int tempo_troca = 100;

	BITMAP* player_right[3];
	BITMAP* player_left[3];
	BITMAP* face;//CARREGAR PERSONAGEM DIREITA

	BITMAP* fundo = load_bitmap("../Animations_assets/ceu.bmp", NULL);//CARRREGAR O FUNDO DO JOGO
	BITMAP* casa = load_bitmap("../Animations_assets/CASA2.bmp", NULL);//CARREGAR CASA
	BITMAP* predio = load_bitmap("../Animations_assets/predio_pablo.bmp", NULL);//CARREGAR PREDIO DO TRABALHO

	FONT *courrier_new;
	courrier_new = load_font("../Fontes/CourrierNew.pcx", NULL, NULL);

	if(sexo == 0){
		player_right[0] = load_bitmap("../Personagens/direita1.bmp", NULL);//CARREGAR PERSONAGEM DIREITA
		player_right[1] = load_bitmap("../Personagens/direita2.bmp", NULL);//CARREGAR PERSONAGEM ESQUERDA
		player_right[2] = load_bitmap("../Personagens/direita3.bmp", NULL);//CARREGAR PERSONAGEM ESQUERDA
		
		player_left[0] = load_bitmap("../Personagens/esquerda1.bmp", NULL);//CARREGAR PERSONAGEM DIREITA
		player_left[1] = load_bitmap("../Personagens/esquerda2.bmp", NULL);//CARREGAR PERSONAGEM ESQUERDA
		player_left[2] = load_bitmap("../Personagens/esquerda3.bmp", NULL);//CARREGAR PERSONAGEM FemLeft_

		face = load_bitmap("../Personagens/direita1.bmp", NULL);
	}
	else if(sexo == 1){
		player_right[0] = load_bitmap("../Personagens/FemRight_1.bmp", NULL);//CARREGAR PERSONAGEM DIREITA
		player_right[1] = load_bitmap("../Personagens/FemRight_2.bmp", NULL);//CARREGAR PERSONAGEM ESQUERDA
		player_right[2] = load_bitmap("../Personagens/FemRight_3.bmp", NULL);//CARREGAR PERSONAGEM ESQUERDA
		
		player_left[0] = load_bitmap("../Personagens/FemLeft_1.bmp", NULL);//CARREGAR PERSONAGEM DIREITA
		player_left[1] = load_bitmap("../Personagens/FemLeft_2.bmp", NULL);//CARREGAR PERSONAGEM ESQUERDA
		player_left[2] = load_bitmap("../Personagens/FemLeft_3.bmp", NULL);//CARREGAR PERSONAGEM FemLeft_

		face = load_bitmap("../Personagens/FemRight_1.bmp", NULL);
	}

	//LOOP PRINCIPAL, EXECUTA TUDO QUE ESTA LA DENTRO, ATE QUE O <<<ALT>>> SEJA PRESSIONADO
	while (1)
	{
		if(x >= 950)
		{
			break;
		}
		while(x >= 950 || x <= 220)
		{ 
			if(x >= 950)
			{
				x -= 5;
			}
			else if(x <= 220)
			{
				x += 5;
			}
		}

		clear(buffer);

		//ATUALIZAÇÃO DE ALGUMAS VARIAVEIS
		frame_atual = (timer / tempo_troca) % num_frames;

		if(key[KEY_RIGHT])
		{
			x += 5;
			face = player_right[frame_atual];
		}
		else if(key[KEY_LEFT])
		{
			x-=5;
			face = player_left[frame_atual];
		}

		draw_sprite(buffer, fundo , 0, 0);////DESENHA A VARIAVEVL FUNDO NO BUFFER

		textprintf_ex(buffer, font, 300, 0, makecol(0, 255, 0), -1, "X: %i", x);//MOSTRA A COORDENADA X EM TEMPO REAL

		if(x == 950)
		{
			textprintf_ex(fundo, courrier_new, 100, 0, makecol(255, 0, 0), -1, "PRESSIONE 'ALT' PARA IR PARA A PROXIMA PARTE");
		}

		draw_sprite(buffer, face , 100 + x, 530 + y);//DESENHA A VARIAVEVL FACE NO BUFFER
		draw_sprite(buffer, casa , -25, 365);//DESENHA A VARIAVEVL CASA NO BUFFER
		draw_sprite(buffer, predio , 1000 , 225);//DESENHA A VARIAVEVL PREDIO NO BUFFER
		draw_sprite(screen, buffer, 0, 0);//DESENHA A VARIAVEVL BUFFER NA SCREEN

		rest(5);
		clear(buffer);
	}
	//DESTRUIÇÃO DOS BITMAPS
	destroy_bitmap(fundo);
	destroy_bitmap(player_right[0]);
	destroy_bitmap(player_right[1]);
	destroy_bitmap(player_right[2]);
	destroy_bitmap(player_left[0]);
	destroy_bitmap(player_left[1]);
	destroy_bitmap(player_left[2]);
	destroy_bitmap(casa);
	destroy_bitmap(predio);
}

void noite(BITMAP *buffer, int sexo){
	int x = 0, y = 0;//COORDENADAS X E Y
	int num_frames = 3;
	int frame_atual = 0;
	int tempo_troca = 100;

	BITMAP* player_right[3];
	BITMAP* player_left[3];
	BITMAP* face;//CARREGAR PERSONAGEM DIREITA

	BITMAP* fundo = load_bitmap("../Animations_assets/noite.bmp", NULL);//CARRREGAR O FUNDO DO JOGO
	BITMAP* predio = load_bitmap("../Animations_assets/cassino.bmp", NULL);//CARREGAR PREDIO DO TRABALHO
	BITMAP* casa = load_bitmap("../Animations_assets/predio_pablo.bmp", NULL);//CARREGAR CASA

	FONT *courrier_new;
	courrier_new = load_font("../Fontes/CourrierNew.pcx", NULL, NULL);

	if(sexo == 0){
		player_right[0] = load_bitmap("../Personagens/direita1.bmp", NULL);//CARREGAR PERSONAGEM DIREITA
		player_right[1] = load_bitmap("../Personagens/direita2.bmp", NULL);//CARREGAR PERSONAGEM ESQUERDA
		player_right[2] = load_bitmap("../Personagens/direita3.bmp", NULL);//CARREGAR PERSONAGEM ESQUERDA
		
		player_left[0] = load_bitmap("../Personagens/esquerda1.bmp", NULL);//CARREGAR PERSONAGEM DIREITA
		player_left[1] = load_bitmap("../Personagens/esquerda2.bmp", NULL);//CARREGAR PERSONAGEM ESQUERDA
		player_left[2] = load_bitmap("../Personagens/esquerda3.bmp", NULL);//CARREGAR PERSONAGEM FemLeft_

		face = load_bitmap("../Personagens/direita1.bmp", NULL);
	}
	else if(sexo == 1){
		player_right[0] = load_bitmap("../Personagens/FemRight_1.bmp", NULL);//CARREGAR PERSONAGEM DIREITA
		player_right[1] = load_bitmap("../Personagens/FemRight_2.bmp", NULL);//CARREGAR PERSONAGEM ESQUERDA
		player_right[2] = load_bitmap("../Personagens/FemRight_3.bmp", NULL);//CARREGAR PERSONAGEM ESQUERDA
		
		player_left[0] = load_bitmap("../Personagens/FemLeft_1.bmp", NULL);//CARREGAR PERSONAGEM DIREITA
		player_left[1] = load_bitmap("../Personagens/FemLeft_2.bmp", NULL);//CARREGAR PERSONAGEM ESQUERDA
		player_left[2] = load_bitmap("../Personagens/FemLeft_3.bmp", NULL);//CARREGAR PERSONAGEM FemLeft_

		face = load_bitmap("../Personagens/FemRight_1.bmp", NULL);
	}

	//LOOP PRINCIPAL, EXECUTA TUDO QUE ESTA LA DENTRO, ATE QUE O <<<ALT>>> SEJA PRESSIONADO
	while (1)
	{
		if(x >= 950)
		{
			break;
		}
		while(x >= 950 || x <= 220)
		{ 
			if(x >= 950)
			{
				x -= 5;
			}
			else if(x <= 220)
			{
				x += 5;
			}
		}

		clear(buffer);

		//ATUALIZAÇÃO DE ALGUMAS VARIAVEIS
		frame_atual = (timer / tempo_troca) % num_frames;

		if(key[KEY_RIGHT])
		{
			x += 5;
			face = player_right[frame_atual];
		}
		else if(key[KEY_LEFT])
		{
			x-=5;
			face = player_left[frame_atual];
		}

		draw_sprite(buffer, fundo , 0, 0);////DESENHA A VARIAVEVL FUNDO NO BUFFER

		textprintf_ex(buffer, font, 300, 0, makecol(0, 255, 0), -1, "X: %i", x);//MOSTRA A COORDENADA X EM TEMPO REAL

		if(x == 950)
		{
			textprintf_ex(fundo, courrier_new, 100, 0, makecol(255, 0, 0), -1, "PRESSIONE 'ALT' PARA IR PARA A PROXIMA PARTE");
		}

		draw_sprite(buffer, face , 100 + x, 530 + y);//DESENHA A VARIAVEVL FACE NO BUFFER
		draw_sprite(buffer, casa , -25, 250);//DESENHA A VARIAVEVL CASA NO BUFFER
		draw_sprite(buffer, predio , 1000 , 400);//DESENHA A VARIAVEVL PREDIO NO BUFFER
		draw_sprite(screen, buffer, 0, 0);//DESENHA A VARIAVEVL BUFFER NA SCREEN

		rest(5);
		clear(buffer);
	}
	//DESTRUIÇÃO DOS BITMAPS
	destroy_bitmap(fundo);
	destroy_bitmap(player_right[0]);
	destroy_bitmap(player_right[1]);
	destroy_bitmap(player_right[2]);
	destroy_bitmap(player_left[0]);
	destroy_bitmap(player_left[1]);
	destroy_bitmap(player_left[2]);
	destroy_bitmap(casa);
	destroy_bitmap(predio);
}
