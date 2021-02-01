/*
 * Autores: Higor Alves Ferreira, Lucas Macedo da Silva, Vitor de Almeida Silva.
 * Versão: 1.2
 * 
 * Crypto - Gera um arquivo criptografado.
 * 
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
//#include <openssl/evp.h>


#define TAM_FROM 256

int main (){
	int arq, var;
	int c = 0;
		
	char from[TAM_FROM] = {0},semCript[TAM_FROM] = {0}, msg[TAM_FROM], comCript[TAM_FROM]= {0};
	char cmd[255] = {0};
				
	
	FILE *ptr_arquivo;


	arq = open ("/dev/SequencialN", O_RDWR);
	if (arq < 0){
		printf("Erro, arquivo não aberto\n");
		return 0;
	}
		
	printf ("Arquivo aberto com sucesso\n");
	system("clear");
	
	do{
		var = 0;
		printf("\nDigite uma opção: \n[1] Escrever \n[2] Ler \n[3] Criptografar \n[4] Descriptografar \n[5] Help \n[0] Sair\n");
		scanf ("%i", &c);
		
		switch (c){
			case 0:
				system("clear");
				return 0;
				break;
			
			case 1:
				
				var = write (arq, NULL, 0);
				if (var < 0){
					printf ("Erro, operação de escrita não realizada\n");
				}else{
					printf("Operação de escrita efetuada com sucesso\n");
				}
				
				printf("\nInsira uma String, Para ser criptografada:");
				scanf("%s",semCript);
				
				sprintf(cmd,"%s" "%s" "%s", "echo ", semCript, " >string.txt");
				system(cmd);
				//system("openssl enc -e -des3 -salt -in string.txt -out cripto.bin");
				//system("openssl enc -d -des3 -in cripto.bin -out string2.txt");
				
				
				
				break;
		
			case 2:
		
				/*var = read (arq, from , TAM_FROM);
				if (var < 0){
					printf ("Erro, operação de leitura não realizada\n");
				}else{
					
					printf ("Foi lido: %s \n", cmd); 
				}

				*/

				ptr_arquivo=NULL;
				ptr_arquivo = fopen("string.txt", "r");
				system("clear");
			 
				if(ptr_arquivo )
				{
					//system("hd string.txt");
					system("cat string.txt");
				}
				else
				{
					system("cat string.bin");
				}

				break;
				
				
			case 3:
				system("openssl enc -e -des3 -salt -in string.txt -out string.bin"); //Realiza a criptografia do arquivo string.txt
				system("rm -r string.txt");											 //Gerando o arquivo string.bin
				break;	
			
			case 4:
				system("openssl enc -d -des3 -in string.bin -out string.txt");
				break;
				
			case 5:
				printf ("\n\n ---Device Driver Help --- \n Autores: Higor Alves, Lucas Macedo, Vitor de Almeida.\n\nOpção [1] comunica com o Device Driver para que o mesmo gere um número aleatório com a ajuda da biblioteca random.h \nOpção [2] comunica com o Device Driver que seja lido o último número aleatório gerado\n");
				break;
				
			default:
				printf ("Erro, informe uma opção válida\n");
				printf("\nDigite uma opção: \n[1] Escrever \n[2] Ler \n[3] Criptografar \n[4] Descriptografar \n[5] Help \n[0] Sair\n");
				scanf ("%i", &c);
				break;
		}
	}while(c != 0);
	system("clear");
	
	return 0;
	
}
