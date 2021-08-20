#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#define MAX 100


struct ExpNo{
	 char caractere;
	 struct ExpNo *prox;
};
typedef struct ExpNo exp_no;
struct LetNo{
	 char caractere;
	 struct LetNo *prox;
};
typedef struct LetNo let_no;
struct CaracNo{
	 char caractere;
	 struct Carac *prox;
};
typedef struct CaracNo carac_no;

int tam;

int menu(exp_no *pilhaexp);
int vazia(exp_no *pilha);
void InitPilha(exp_no *pilha);
void opcao(exp_no *pilhaExpressao, int op);
//void exibe(exp_no *pilha);
void FreePilha(exp_no *pilha);
void push(exp_no *pilha, char elemento);
exp_no *aloca(char elemento);
char *infixaParaPosfixa(exp_no *pilhaExpressao);
void inserirExpressao(exp_no *pilhaExpressao);
void ValidarExp(char *exp);
void VerExp();
void LimpaExp(char *exp);
char elemento;
char exp[MAX];
int main(int argc, char *argv[])
{
	int opt;
	char *exp;
	char chr;
	printf("\t\t\t\t\t CONVERSOR DE NOTAÇÕES POLONESAS \n ",setlocale(LC_ALL,""));
	printf("\t\t\t\t\tTamanho maximo da expressão (100) ",setlocale(LC_ALL,""));

	exp_no *pilhaExpressao = (exp_no *) malloc(sizeof(exp_no)); // Pilha das Expressões
	//exp_no *pilhaExpressao = (exp_no *) malloc(sizeof(exp_no)); // Pilha das letras
	if(!pilhaExpressao){
	  printf("Erro ao alocar memoria.\n");
	  exit(1);
	}else{
		InitPilha(pilhaExpressao);

     if(argc != 2)  // N?o foi utilizado linha de comando
			inserirExpressao(pilhaExpressao);
	 else{ // Valida express?o e insere na pilha
	 		exp = argv[1];

			ValidarExp(exp);

	 		while(chr = *exp++)
	 			push(pilhaExpressao, chr);
	 	 }

	 do{
		  opt = menu(pilhaExpressao);
		  opcao(pilhaExpressao,opt);
	 }while(opt);

	 free(pilhaExpressao);

	 return 0;
	 }
}

/*
	Insere uma nova express?o na pilha
*/
void inserirExpressao(exp_no *pilhaExpressao){

	char chr;
	int i;
	size_t strSize = 0;
	memset(exp, 0, MAX);

	if(!vazia(pilhaExpressao)){
		FreePilha(pilhaExpressao);
		InitPilha(pilhaExpressao);
	}

	do{
		fflush(stdin);
		printf("\n\nDigite a expressão:",setlocale(LC_ALL,""));
		fgets(exp, MAX, stdin);
	}while(strlen(exp) < 3);


	ValidarExp(exp);

	printf("\n\nExpressão Digitada: ",setlocale(LC_ALL,""));
	printf("[ %s ]\n",exp);
	system("pause");

	//for(i = 0; i < strSize; i++)
	//	push(pilhaExpressao, exp[i]);

}

/*
	Retira espa?os e parenteses de express?es
*/
void ValidarExp(char *exp){
	char *p2 = exp;

    while(*exp != '\0') {
        if(*exp != '\t' && *exp != '\n' & *exp != ' ') {
            *p2++ = *exp++;
        } else {
            ++exp;
        }
    }
    *p2 = '\0';
}

void InitPilha(exp_no *PILHA) // Inicia a pilha e o contador
{
	 PILHA->prox = NULL;
	 tam=0;
}

int menu(exp_no *pilhaExpressao)
{
	 int opt;

	 system("cls");
	 printf("\n\nExpressão Digitada: ",setlocale(LC_ALL,""));
	 puts(exp);

	 printf("Escolha a opcao\n");
	 printf("1 - Iniciar Conversão\n");
	 printf("3 - Nova Expressão\n");
	 printf("0 - Exit\n");

	 scanf("%d", &opt);

	 return opt;
}



void opcao(exp_no *pilhaExpressao, int op)
{
	 exp_no *tmp;

	 switch(op){
		  case 0:
		   		FreePilha(pilhaExpressao);
		   break;

		  case 1:
			VerExp();
		  	system("pause");
		   break;

		  case 2:
		  	FreePilha(pilhaExpressao);
			InitPilha(pilhaExpressao);
		   break;
	      case 3:
	      		inserirExpressao(pilhaExpressao);
	       break;
		  default:
		   		printf("Invalido");
	 }
}
/*
	A fun??o a seguir realiza a convers?o de uma express?o em pilha para posfixa
	e retorna o ponteiro da string

	Argumentos:
		- pilha contendo a express?o
*/
char *infixaParaPosfixa(exp_no *pilhaExpressao){

	return 0;
}

int vazia(exp_no *PILHA)
{
	 if(PILHA->prox == NULL) // Se o pr?ximo n? da pilha estiver NULL, a pilha est? vazia
	  return 1;
	 else
	  return 0;
}

void exibe(exp_no *PILHA) // Exibe o conte?do da pilha
{
	 if(vazia(PILHA)){
	  	printf("PILHA vazia!");
	  return ;
	 }

	 exp_no *tmp; // Ponteiro tempor?rio
	 tmp = PILHA->prox; // Recebe o primeiro n?

	 while( tmp != NULL){   // Enquanto o pr?ximo n? n?o for NULL, ainda existem elementos
	  printf("%1c ", tmp->caractere);
	  tmp = tmp->prox;     // tmp aponta para prox da pilha, onde o prox possui o prox para o outro n? at? encontrar NULL
	  					// tmp->prox = prox->prox = prox->prox = NULL; (tr?s n?s)
	 }

}

void FreePilha(exp_no *PILHA)
{
	 if(!vazia(PILHA)){
		  exp_no *proxExpNo, *atual;
		  atual = PILHA->prox;
	  while(atual != NULL){ // Dando free nos n?s at? encontrar NULL
     	   proxExpNo = atual->prox;
		   free(atual);
	 	   atual = proxExpNo;
	  }
	 }
}


exp_no *aloca(char elemento) // Alocar novo n? na pilha
{
	 exp_no *novo=(exp_no *) malloc(sizeof(exp_no));

	 if(!novo){
		  printf("Erro na alocação de memoria\n",setlocale(LC_ALL,""));
		  exit(1);
	 }else{
		  novo->caractere = elemento;
	  	  return novo;
	 }
}

void push(exp_no *PILHA, char elemento)
{
	 exp_no *novo = aloca(elemento); // aloca novo n?, pergunta qual elemento adicionar
	 novo->prox = NULL; // Inicia o proximo como NULL

	 if(vazia(PILHA))
	  	PILHA->prox = novo; // Se a pilha estiver vazia, o ponteiro proximo continuar? NULL
	 else{
	  	exp_no *tmp = PILHA->prox;  // Aponta para o pr?ximo elemento, PILHA->prox possui o endere?o do topo da pilha

	  while(tmp->prox != NULL) // Enquanto o pr?ximo elemento n?o for NULL
	   	tmp = tmp->prox; // o ponteiro temporario ir? recebendo o pr?ximo n?

	  	tmp->prox = novo; // Quando alcancar o ponteiro com o valor NULL, o endere?o do novo n? ser? colocado no prox
	 }
	 tam++;
}
void VerExp(){

	char exp_aux[MAX];
	strcpy(exp_aux,exp);
	LimpaExp(exp_aux);
    int t = strlen(exp_aux);
	puts(exp_aux);


		for (int i=0;i<t-1;i++){

		if(exp_aux[0]=='+'||exp_aux[0]=='-'||exp_aux[0]=='*'||exp_aux[0]=='/'){
			printf("\t\t\t\t\t CONVERSOR DE NOTAÇÕES POLONESAS \n\n\n ",setlocale(LC_ALL,""));
			printf("\t\t\t\t\t VOCÊ DIGITOU UMA NOTAÇÃO PRE-FIXA\n\n\n",setlocale(LC_ALL,""));

			break;
		}
		if(exp_aux[t-1]=='+'||exp_aux[t-1]=='-'||exp_aux[t-1]=='*'||exp_aux[t-1]=='/'){
            printf("\t\t\t\t\t CONVERSOR DE NOTAÇÕES POLONESAS \n\n\n ",setlocale(LC_ALL,""));
			printf("\t\t\t\t\t VOCÊ DIGITOU UMA NOTAÇÃO PÓS-FIXA\n\n\n",setlocale(LC_ALL,""));
            break;
		}
		else{
            printf("\t\t\t\t\t CONVERSOR DE NOTAÇÕES POLONESAS \n\n\n ",setlocale(LC_ALL,""));
			printf("\t\t\t\t\t VOCÊ DIGITOU UMA NOTAÇÃO INFIXA\n\n\n",setlocale(LC_ALL,""));
            break;
		}

	}


}
void LimpaExp(char *expressao){
	char *p2 = expressao;

	// Remover \n, \t, (, ) e espa?os
    while(*expressao != '\0') {
        if(*expressao != '\t' && *expressao != '\n' & *expressao != '(' & *expressao != ')' & *expressao != ' ') {
            *p2++ = *expressao++;
        } else {
            ++expressao;
        }
    }
    *p2 = '\0';
}


