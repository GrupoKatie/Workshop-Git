#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

struct dados
{
	long int value;
	struct dados *next;
};

typedef struct dados dados;

struct hash_table
{
	dados *table[100000];
};

typedef struct hash_table hash_table;

hash_table* create_hash_table(int tamanho)
{
	hash_table *new_ht = (hash_table*) malloc(sizeof(hash_table));

	for(int i = 0; i < tamanho; i++)
	{
		new_ht -> table[i] = NULL;
	}

	return new_ht;
}

void put_rehashing(hash_table *ht, long int value, int tamanho)
{
	long int h = value % tamanho;

	if(ht -> table[h] != NULL)
	{
		dados* new_dados = (dados*) malloc(sizeof(dados));
		new_dados -> value = value;
		new_dados -> next = ht -> table[h];

		ht -> table[h] = new_dados;
	}
	else
	{
		dados* new_dados = (dados*) malloc(sizeof(dados));
		new_dados -> value = value;
		new_dados -> next = NULL;
		ht -> table[h] = new_dados;
	}

	return ht;
}

hash_table *rehashing(hash_table *ht, int tamanho_antigo, int tamanho_novo)
{
    hash_table *aux = create_hash_table(tamanho_novo);
	for(int i = 0; i < tamanho_antigo; i++)
	{
		while(ht -> table[i] != NULL)
		{
			put_rehashing(aux, ht -> table[i] -> value, tamanho_novo);
			ht -> table[i] = ht -> table[i] -> next;
		}
	}

	free(ht);
	return aux;
}

int comparacoes(hash_table *ht, long int key, long int value, int tamanho)
{
	long int h = key % tamanho, numero_de_comparacoes = 0;

	if(ht -> table[h] != NULL)
	{
		hash_table *aux = create_hash_table(tamanho);
		aux -> table[h] = ht -> table[h];

		while(ht -> table[h] != NULL)
		{
		    numero_de_comparacoes += 1;   
		    
		    if(ht -> table[h] -> value == value)
		    {
		        return numero_de_comparacoes;
		    }

			if(ht -> table[h] -> next == NULL)
			{
				break;
			}

			ht -> table[h] = ht -> table[h] -> next;
		}

		ht -> table[h] = aux -> table[h];

		free(aux);

		return numero_de_comparacoes;
	}
	
	return numero_de_comparacoes;
}

int put(hash_table *ht, long int key, long int value, int tamanho)
{
	long int h = key % tamanho;

	if(ht -> table[h] != NULL)
	{
		hash_table *aux = create_hash_table(tamanho);
		aux -> table[h] = ht -> table[h];

		while(ht -> table[h] != NULL)
		{
			if(ht -> table[h] -> value == value)
			{
				ht -> table[h] = aux -> table[h];
				free(aux);
				return 0; //false, já existia no conjunto
			}

			if(ht -> table[h] -> next == NULL)
			{
				break;
			}

			ht -> table[h] = ht -> table[h] -> next;
		}
		
		ht -> table[h] = aux -> table[h];
		
		dados* new_dados = (dados*) malloc(sizeof(dados));
		new_dados -> value = value;
		new_dados -> next = ht -> table[h];

		ht -> table[h] = new_dados;

		free(aux);

		return 1;//true, adicionado corretamente

		/*while(ht -> table[h] -> next != NULL)
		{
			ht -> table[h] = ht -> table[h] -> next;
		}

		ht -> table[h] -> next = new_dados;
		ht -> table[h] = aux -> table[h];*/
	}
	else
	{
	    dados* new_dados = (dados*) malloc(sizeof(dados));
		new_dados -> value = value;
		new_dados -> next = NULL;
		ht -> table[h] = new_dados;   

		return 1;//true, adicionado corretamente
	}
}

int del(hash_table *ht, long int key, long int value, int tamanho)
{
	long int h = key % tamanho;

	if(ht -> table[h] != NULL)
	{
	    if(ht -> table[h] -> value == value)
		{
			ht -> table[h] = ht -> table[h] -> next;
			return 1; //true, elemento removido com sucesso
		}
		
		hash_table *aux = create_hash_table(tamanho);
		aux -> table[h] = ht -> table[h];
		
		hash_table *aux2 = create_hash_table(tamanho);
		aux2 -> table[h] = ht -> table[h];

		while(ht -> table[h] != NULL)
		{
			if(ht -> table[h] -> value == value)
			{
			    aux -> table[h] -> next = ht -> table[h] -> next;
			    ht -> table[h] = aux2 -> table[h];
				//ht -> table[h] = ht -> table[h] -> next = ;
				//ht -> table[h] = aux -> table[h];
				free(aux);
				free(aux2);
				return 1; //true, elemento removido com sucesso
			}

			if(ht -> table[h] -> next == NULL)
			{
				break;
			}
            
            aux -> table[h] = ht -> table[h];
			ht -> table[h] = ht -> table[h] -> next;
		}

		ht -> table[h] = aux2 -> table[h];

		free(aux);
		free(aux2);

		return 0; //false, o elemento não existe
	}
	
	return 0;//false, o elemento não existe
}

int has(hash_table *ht, long int key, long int value, int tamanho)
{
	long int h = key % tamanho, numero_de_comparacoes = 0;

	if(ht -> table[h] != NULL)
	{
		hash_table *aux = create_hash_table(tamanho);
		aux -> table[h] = ht -> table[h];

		while(ht -> table[h] != NULL)
		{
			if(ht -> table[h] -> value == value)
			{
				ht -> table[h] = aux -> table[h];
				free(aux);
				return 1; //o elemento existe
			}

			if(ht -> table[h] -> next == NULL)
			{
				break;
			}

			ht -> table[h] = ht -> table[h] -> next;
		}

		ht -> table[h] = aux -> table[h];

		free(aux);

		return 0; //o elemento n existe
	}
	
	return 0; //o elemento n existe
}

long int prt(hash_table *ht, int tamanho)
{
	long int maior = 0, quantidade;
	hash_table *aux = create_hash_table(tamanho);
	for(int i = 0; i < tamanho; i++)
	{
	    aux -> table[i] = ht -> table[i];
		quantidade = 0;

		while(ht -> table[i] != NULL)
		{
			quantidade += 1;
			ht -> table[i] = ht -> table[i] -> next;
		}

		if(quantidade > maior)
		{
			maior = quantidade;
		}
		
		ht -> table[i] = aux -> table[i];
	}
	
	free(aux);

	return maior;
}
void print_hash_table(hash_table *ht, int tamanho)
{
	for(int i = 0; i < tamanho; i++)
	{
		printf("%d ->", i);

		while(ht -> table[i] != NULL)
		{
			printf(" %ld ->", ht -> table[i] -> value);
			ht -> table[i] = ht -> table[i] -> next;
		}
		
		printf(" \\\n");
	}
}

int main()
{
	int operacao = 0, tamanho = 7, confere_existencia, numero_de_comparacoes;
	double carga = 0.0, cardinalidade = 0.0;
	char string[20];
	hash_table* ht = create_hash_table(tamanho);

	while(scanf("%[^\n]", string) != EOF)
	{
		getchar();

		printf("%d ", operacao);

		int tam = strlen(string);

		if(tam > 3)
		{
		    char string_int[tam-3];
			for(int i = 4, j = 0; i < tam; i++, j++)
			{
				string_int[j] = string[i];
			}

			long int valor = atoi(string_int);

			if(string[0] == 'A')
			{
				numero_de_comparacoes = comparacoes(ht, valor, valor, tamanho);
				confere_existencia = put(ht, valor, valor, tamanho);
				
				if(confere_existencia == 1)
				{
					cardinalidade += 1;
					carga = (cardinalidade)/tamanho;
				}

				printf("%d %d\n", confere_existencia, numero_de_comparacoes);

				if(carga >= 0.75)
				{
					int t = tamanho;
					tamanho = 2*tamanho-1;
					ht = rehashing(ht, t, tamanho);
					carga = 0.0;
				}
			}
			else if(string[0] == 'D')
			{
				numero_de_comparacoes = comparacoes(ht, valor, valor, tamanho);
				confere_existencia = del(ht, valor, valor, tamanho);

				if(confere_existencia == 1)
				{
					cardinalidade -= 1;
					carga = (cardinalidade)/tamanho;
				}

				printf("%d %d\n", confere_existencia, numero_de_comparacoes);
			}
			else if(string[0] == 'H')
			{
				numero_de_comparacoes = comparacoes(ht, valor, valor, tamanho);
				confere_existencia = has(ht, valor, valor, tamanho);

				printf("%d %d\n", confere_existencia, numero_de_comparacoes);
			}
		}
		else
		{
		    //hash_table* aux = create_hash_table(tamanho);
		    //aux = ht;
		    //printf("\n");
		    //ht = aux;
		    if(operacao == 43)
		    {
		        print_hash_table(ht, tamanho);
		    }
			printf("%d %.0lf %ld\n", tamanho, cardinalidade, prt(ht, tamanho));
		}
        
		operacao++;
	}

	return 0;
}