#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <locale.h>

struct node 
{
	char nome[1000];
	struct node *next;
	struct node *previous;
};

typedef struct node node;

struct queue
{
	int tamanho_da_fila;
  	node *head;
};

typedef struct queue queue;

queue* criar_fila()
{
	queue *new_queue = (queue*) malloc(sizeof(queue));
	new_queue -> head = NULL;
	new_queue -> tamanho_da_fila = 0;
	return new_queue;
}

void enqueue(queue *queue, char *nome)
{
	node *new_node = (node*) malloc(sizeof(node));
	strcpy(new_node -> nome, nome);

	if(queue -> head == NULL)
	{
		new_node -> next = queue -> head;
		new_node -> previous = queue -> head;
		queue -> head = new_node;
	}
	else
	{
		node* aux = queue -> head;
		while(aux -> next != NULL)
		{
			aux = aux -> next;
		}
		aux -> next = new_node;
		new_node -> next = NULL;
		new_node -> previous = aux;
	}
}

void dequeue_ru(queue *queue, char *nome)
{
	queue -> head = queue -> head -> next;
	printf("%s almocou no RU e esta voltando pra aula\n", nome);
}

void dequeue_area2(queue *queue, char *nome)
{
	queue -> head = queue -> head -> next;
	printf("%s almocou na Area 2 e esta voltando pra aula\n", nome);
}

int main()
{
	setlocale(LC_ALL, "Portuguese");

	queue *fila_ru = criar_fila();
	queue *fila_area2 = criar_fila();

	char string_ru[1000];
	char string_area2[1000];
	char especial_ru[1000];
	char especial_area2[1000];

	scanf("%[^\n]", string_ru);
	getchar();
	scanf("%[^\n]", string_area2);
	getchar();

	int tamanho_string_ru = strlen(string_ru);
	int tamanho_string_area2 = strlen(string_area2);

	for(int i = 3, j = 0; i < tamanho_string_ru; i++, j++)
	{
		especial_ru[j] = string_ru[i];
	}

	for(int i = 7, j = 0; i < tamanho_string_area2; i++, j++)
	{
		especial_area2[j] = string_area2[i];
	}

	char *comando;
	comando = malloc(2000 * sizeof(char));

	while(scanf("%[^\n]", comando) != EOF)
	{
		getchar();

		if(strcmp(comando, "SAIU:RU") == 0)
		{
			if(fila_ru -> head == NULL)
			{
				printf("Nao ha mais ninguem para comer aqui\n");
			}
			else
			{
				dequeue_ru(fila_ru, fila_ru -> head -> nome);
			}
		}
		else if(strcmp(comando, "SAIU:AREA2") == 0)
		{
			if(fila_area2 -> head == NULL)
			{
				printf("Nao ha mais ninguem para comer aqui\n");
			}
			else
			{
				dequeue_area2(fila_area2, fila_area2 -> head -> nome);
			}
		}
		else
		{
			bool tem_preferencia = false;
			int tamanho_comando = strlen(comando), tamanho_preferencia, tamanho_nome, aux = 0;

			for(int i = 0; i < tamanho_comando; i++)
			{
				if(comando[i] == ':')
				{
					tem_preferencia = true;
					break;
				}
			}

			if(tem_preferencia)
			{
				char *preferencia, *nome;

				nome = strtok(comando, ":");
				preferencia = strtok(NULL, "\0");

				if(strcmp(preferencia, especial_ru) == 0)
				{
					enqueue(fila_ru, nome);
					fila_ru -> tamanho_da_fila += 1;
					printf("%s foi para a fila do RU\n", nome);
				}
				else if(strcmp(preferencia, especial_area2) == 0)
				{
					enqueue(fila_area2, nome);
					fila_area2 -> tamanho_da_fila += 1;
					printf("%s foi para a fila da Area 2\n", nome);
				}
				else
				{
					if(fila_area2 -> tamanho_da_fila >= fila_ru -> tamanho_da_fila)
					{
						enqueue(fila_area2, nome);
						fila_area2 -> tamanho_da_fila += 1;
						printf("%s foi para a fila da Area 2\n", nome);
					}
					else
					{
						enqueue(fila_ru, nome);
						fila_ru -> tamanho_da_fila += 1;
						printf("%s foi para a fila do RU\n", nome);
					}
				}
			}
			else
			{
				char *nome;

				nome = strtok(comando, "\0");

				if(fila_area2 -> tamanho_da_fila >= fila_ru -> tamanho_da_fila)
				{
					enqueue(fila_area2, nome);
					printf("%s foi para a fila da Area 2\n", nome);
				}
				else
				{
					enqueue(fila_ru, nome);
					printf("%s foi para a fila do RU\n", nome);
				}
			}
		}

		free(comando);

		char *comando;
		comando = malloc(2000 * sizeof(char));
	}


	return 0;
}