/*O indivíduo fará a escolha do seu sexo(masculino ou feminino) e da sua idade que interferirá na história,
ele terá inicialmente um salario base, uma reserva de capital no banco, barra de estamina e barra de felicadade
(todas essas variáveis irão interferir na gameplay do usuário), no inicio do jogo o personagem principal fará 
sua rotina normal, acordar,tomar café e ir trabalhar, na parte do trabalho ele irá receber uma proposta de um
amigo para depois do trabalho eles irem para uma casa de apostar para jogar o jogo do bicho, e você resolve aceitar.
Nos dois dias iniciais iremos viciar o jogo para que o player sempre ganhe, após esse dois dias  o algoritmo mudará
e terá uma chance de ganho de: terceiro dia: 30%, quarto dia: 25%, quinto dia: 15%, sexto dia:  95%, sétimo dia 10%,
oitavo dia 10%, nono dia 8%, décimo dia 99% e nos próximos dias irá ter uma repetição de 5 para 1 (a cada 4 dias
com 8% ele terá 1 dia com 99% de ganhar), as porcentagens são baseadas em neurociência (irei adicionar o artigo depois)
no qual se temos uma recompensa logo no início (para prender a pessoa)  e perda com reforço de ganho (a partir do momento
que se tem um reforço de ganho ele irá ficar viciado em fazer a aposta e não em simplesmente ganhar a aposta). 
O jogo termina quando o player morrer ou falir.*/
#include <stdio.h>
#include <stdlib.h>
struct player //Declaração da struct onde contém os itens obrigatorios para o cadastro do jogador
{
	char nome[40];
	int idade;
	char sexo;
};
int main()
{
	float dinheiro_base = 1200.00;//Dinheiro inicial do jogador
	int felicidade, estamina;
	struct player cad;//Chamada da struct para ser feito o cadastro do jogador
	printf("Jogador, qual o seu nome? ");
	scanf("%s", &cad.nome[40]);
	printf("Jogador, qual a sua idade? ");
	scanf("%i", &cad.idade);
	if(cad.idade < 18)//Tratativa para jogadores menores de idade
	{
		printf("Infelizmente voce nao tem idade para jogar jogos deste tipo, volte depois de ter completado 18 anos!!!");
		exit(0);//Encerramento do programa já que o jogador não possui idade suficiente para jogar
	}
	printf("Digite M se for do sexo Masculino ou F se for do sexo Feminino: ");
	scanf("%s", &cad.sexo);
	switch(cad.sexo)//O sexo interfere no personagem que será uasdo ao decorrer do jogo
	{
		case 'M': 
		{
			
			break;
		}
		case 'm': 
		{
			
			break;
		}
		case 'F': 
		{
			
			break;
		}
		case 'f': 
		{
			
			break;
		}
	}
	system("pause");
	return 0;
}