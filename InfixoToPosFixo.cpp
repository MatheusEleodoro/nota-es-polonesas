#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;

bool comparaNumero(char auxiliar);
void imprimePosfixa(char posfixa[]);

int main(){
	char infixa[99], posfixa[99], operadores[99], auxiliar;
	int contPosfixa=-1, contOperadores=-1;
	bool resposta;
	posfixa[0] = '\0';
	cout<<"expressao infixa: ";
	gets(infixa);
	
	for(int cont=0; cont<strlen(infixa); cont++){
		if(comparaNumero(infixa[cont])){ //if chamando a função "comparaNumero" para colocar os numeros/variaveis na posfixa ou fazer tratamento com os operadores
			contPosfixa++;
			posfixa[contPosfixa] = infixa[cont];
		}else{
			/*
			 *	CORAÇÃO DO ALGORÍTIMO 
			 *	o switch vai controlar as manipulações da pilha com os operadores.
			 *	LISTA DE PRIORIDADE:
			 *	'('      -> prioridade 4
			 *	'+' '-'  -> prioridade 1
			 *	'*' '/'  -> prioridade 2
			 *	'^'      -> prioridade 3
			 8	')"      -> NA
			 */ 
			switch(infixa[cont]){
				case '(':
					contOperadores++;
					operadores[contOperadores] = infixa[cont];
					break;
				case ')':
					for(; operadores[contOperadores] != '('; contOperadores--, contPosfixa++){
						posfixa[contPosfixa+1] = operadores[contOperadores];
					}
					contOperadores--;
					break;
				case '+':
				case '-':
					if(operadores[contOperadores] == '^' || operadores[contOperadores] == '*'){
						for(int x=0; x == 0; contOperadores--,contPosfixa++){
							posfixa[contPosfixa+1] = operadores[contOperadores];
							if(operadores[contOperadores] == '+' || operadores[contOperadores] == '-' || operadores[contOperadores] == '(' || contOperadores-1 == -1)
								x++;
						}	
					}
					if(contOperadores != -1 && operadores[contOperadores] != '(' /*&& operadores[contOperadores] == '^' || operadores[contOperadores] == '*'*/){
						contPosfixa++;
						posfixa[contPosfixa] = operadores[contOperadores];
						operadores[contOperadores] = infixa[cont];
					}else if(contOperadores == -1 || operadores[contOperadores] == '('){
						contOperadores++;
						operadores[contOperadores] = infixa[cont];
					}
					
					break;
				case '*':
				case '/':
					if(operadores[contOperadores] == '^'){
						for(int x=0; x == 0; contOperadores--,contPosfixa++){
							posfixa[contPosfixa+1] = operadores[contOperadores];
							if(operadores[contOperadores] == '*' || operadores[contOperadores] == '/')
								x++;
						}	
					}
					if(contOperadores != -1 && operadores[contOperadores] != '(' && (operadores[contOperadores] != '+' && operadores[contOperadores] != '-')){
						contPosfixa++;
						if(operadores[contOperadores] == '*' || operadores[contOperadores] == '/'){
							posfixa[contPosfixa] = operadores[contOperadores];
							operadores[contOperadores] = infixa[cont];
						}else{
							posfixa[contPosfixa] = infixa[cont];
						}
					}else if(contOperadores == -1 || operadores[contOperadores] == '(' || operadores[contOperadores] == '+' || operadores[contOperadores] == '-'){
						contOperadores++;
						operadores[contOperadores] = infixa[cont];
					}
					break;
				case '^':
					if(operadores[contOperadores] == '^')
						posfixa[contPosfixa] = infixa[cont];
					else{
						contOperadores++;
						operadores[contOperadores] = infixa[cont];
					}
					break;
				default: //simbolos inválidos
					system("cls");
					cout<<"*****************************************";
					cout<<"\n**Caractere invalido!! - Fim do sistema**\n";
					cout<<"*****************************************";
					exit(0);
			}
		}
		if(strlen(infixa) == cont+1){ //tirar os restos da pilha quando a infixa terminar de ser escaneada
			for(int x=-1; x<contOperadores; contOperadores--,contPosfixa++){
				posfixa[contPosfixa+1] = operadores[contOperadores];
			}
			posfixa[contPosfixa+1] = '\0';
		}
	}
	
	cout<<"expressao posfixa: ";
	imprimePosfixa(posfixa);
	
	exit(0);
}

bool comparaNumero(char auxiliar){ //função para definir se é um numero/variavel ou algum outro simbolo
	if((auxiliar >= '0' && auxiliar <= '9') || (auxiliar >= 'a' && auxiliar <= 'z') || (auxiliar >= 'A' && auxiliar <= 'Z')){
		return true;
	} else{
		return false;
	}
}



void imprimePosfixa(char posfixa[]){ //função para imprimir a expressão pós-fixa
	for(int cont=0; posfixa[cont] != '\0'; cont++){
		cout<<posfixa[cont];
	}
}	
