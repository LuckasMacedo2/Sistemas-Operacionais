/*
 * Autores: Higor Alves Ferreira, Lucas Macedo da Silva, Vitor de Almeida Silva.
 * Versão: 1.1
 * 
 * RND - Gera números Aleátorios.
 * 
 */ 


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <string.h>


#define TAM_FROM 256

int main (){
	int arq, var;
	int c = 0;
		
	char from[TAM_FROM] = {0}, msg[TAM_FROM];
				
	arq = open ("/dev/RND", O_RDWR);
	if (arq < 0){
		printf("Erro, arquivo não aberto\n");
		return 0;
	}
		
	printf ("Arquivo aberto com sucesso\n");
	system("clear");
	
	do{
		var = 0;
		printf("\nDigite uma opção: \n[1] Gerar número aleátorio \n[2] Ver número gerado \n[3] Help \n[0] Sair\n");
		scanf ("%i", &c);
		
		switch (c){
			case 0:
				system("clear");
				return 0;
				break;
			
			case 1:
				
				var = write (arq, "", 0);
				printf("Número aleatorio gerado com sucesso\n");
				break;
		
			case 2:
				var = read (arq, from, TAM_FROM);
				printf ("Foi gerado o n: %s \n", from); 

				break;
				
			case 3:
				printf ("\n\n ---Device Driver Help --- \n Autores: Higor Alves, Lucas Macedo, Vitor de Almeida.\n\nOpção [1] comunica com o Device Driver para que o mesmo gere um número aleatório com a ajuda da biblioteca random.h \nOpção [2] comunica com o Device Driver que seja lido o último número aleatório gerado\n");
				break;
				
				
			default:
				printf ("Erro, informe uma opção válida\n");
				printf("\nDigite uma opção: \n[1] Escrever \n[2] Ler \n[3] help \n[0] Sair\n");
				scanf ("%i", &c);
				break;
		}
	}while(c != 0);
	system("clear");
	
	return 0;
	
}
