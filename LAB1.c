// CEUB - Engenharia de Computaçãoo - 6º semestre - Compiladores - Prof. Leonardo Pol Suarez
// Laboratório 1 - Segundo Bimestre - 20/10/2020
// Pablo Felipe Santos Carneiro - 21804056

#include <stdio.h>
#include <string.h>
#include <locale.h>

int identificar(char nome[64], char lista[64][64]) {
	int i;
	for(i = 1; i < 64; i++) {
		if(strcmp(nome, lista[i]) == 0) {
			return(i);
		}
	}
	
	for(i = 1; i < 64; i++) {
		if(lista[i][0] == '\0') {
			for(int j = 0; j < 64; j++) {
				lista[i][j] = nome[j];
			}
			
			return(i);
		}
	}
	
	return(-1);
}

int main() {
	setlocale(LC_ALL, "portuguese");
	char entrada[1024];
	
	for(int i = 0; i < 1024; i++) {
		entrada[i] = '\0';
	}
	
	do {
		printf("Entrada: ");
		fgets(entrada, 1024, stdin);
	} while(entrada[0] == '\n');
	
	int qid = 1;
	char listaid[64][64];
	
	int qerr = 0;
	int listaerros[64];
	
	for(int i = 0; i < 64; i++) {
		listaerros[i] = 0;
		for(int j = 0; j < 64; j++) {
			listaid[i][j] = '\0';
		}
	}
	
	int ultlex = 0; // 0 = delimitador; 1 = numero; 2 = identificador; 3 = operador; -1 = inválido;
	int atr = 0; // atribuição?
	
	printf("\n   LEXEMA   |   TOKEN (TIPO)   \n            |\n");
	
	for(int i = 0; (i < 1024) && (entrada[i] != '\n'); i++) {
		if(entrada[i] == ' ') {
			continue;
		}
		else if(entrada[i] >= '0' && entrada[i] <= '9') {
			char num[64];
			for(int a = 0; a < 64; a++) {
				num[a] = '\0';
			}
			
			int aux = 0, j = 0;
			for(j = i; (j < 1024) && (entrada[j] >= '0' && entrada[j] <= '9'); j++) {
				num[aux] = entrada[j];
				aux++;
			}
			
			i = j - 1;
			
			printf(" %10s | numero", num);
			
			if(ultlex == 1 || ultlex == 2) {
				printf(" -> INVÁLIDO: nenhuma operação com o lexema anterior");
				listaerros[qerr] = 1;
				qerr++;
			}
			
			printf("\n");
			
			ultlex = 1;
			continue;
		}
		else if((entrada[i] >= 'a' && entrada[i] <= 'z') || (entrada[i] >= 'A' && entrada[i] <= 'Z')) {
			char var[64];
			for(int a = 0; a < 64; a++) {
				var[a] = '\0';
			}
			
			int aux = 0, j = 0;
			for(j = i; (j < 1024) && ((entrada[j] >= 'a' && entrada[j] <= 'z') || (entrada[j] >= 'A' && entrada[j] <= 'Z')); j++) {
				var[aux] = entrada[j];
				aux++;
			}
			
			i = j - 1;
			
			printf(" %10s | identificador #%i", var, identificar(var, listaid));
			
			if(ultlex == 2 || ultlex == 1) {
				printf(" -> INVÁLIDO: nenhuma operação com o lexema anterior");
				listaerros[qerr] = 1;
				qerr++;
			}
			
			printf("\n");
			
			ultlex = 2;
			continue;
		}
		else {
			printf("          %c | ", entrada[i]);
		
			switch(entrada[i]) {
				case '=':
					printf("operador de atribuição");
					break;
					
				case '+':
					printf("operador aritmético ADD");
					break;
					
				case '-':
					printf("operador aritmético SUB");
					break;
				
				case '*':
					printf("operador aritmético MUL");
					break;
					
				case '/':
					printf("operador aritmético DIV");
					break;
					
				case ';':
					printf("delimitador");
					atr = 0;
					break;
					
				default:
					printf("CARACTERE SEM SIGNIFICADO\n");
					ultlex = -1;
					listaerros[qerr] = 4;
					qerr++;
					continue;
			}
			
			if(atr == 1) {
				printf(" -> INVÁLIDO: atribuições não podem conter operandos");
				listaerros[qerr] = 5;
				qerr++;
			}
			if(ultlex == 3 && (i > 0 && entrada[i - 1] == ' ')) {
				printf(" -> INVÁLIDO: conflita com o operador anterior");
				listaerros[qerr] = 3;
				qerr++;
			}
			
			switch(entrada[i]) {
				case '=':
					atr = 1;
					break;				
			}
			
			ultlex = 3;
			
			printf("\n");
		}
	}
	
	printf("\n");
	if(qerr > 0) {
		for(int i = 0; i < 64 && listaerros[i] != 0; i++) {
			switch(listaerros[i]) {
				case 1:
					printf("Foram encontradas duas variáveis ou números seguidos separados por espaços em branco.\n");
					break;
					
				case 3:
					printf("Foram encontrados dois operadores seguidos separados por espaços em branco.\n");
					break;
					
				case 4:
					printf("Um caractere inválido foi encontrado.\n");
					break;
					
				case 5:
					printf("Foram encontrados mais de um operando após o enunciado de atribuição.\n");
					break; 
			}
		}
	
		printf("\n");
	}
	
	main();
}
