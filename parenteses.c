#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 255

struct pilha
{
	int tamanho;
	char valores[MAX_STACK_SIZE];
};

typedef struct pilha pilha;

void push(pilha *topo, char item)
{
	if(topo -> tamanho == MAX_STACK_SIZE)
	{
		printf("Stack overflow\n");
	}
	else
	{
		topo -> valores[topo -> tamanho++] = item;
	}
}

char pop(pilha *topo)
{
	if(topo -> tamanho == 0)
	{
		printf("Stack underflow\n");
		return '1';
	}
	else
	{
		return topo -> valores[--topo -> tamanho];
	}
}

/*int peek(pilha *topo)
{
	if(topo -> tamanho == 0)
	{
		printf("Stack underflow\n");
		return -1;
	}
	else
	{
		return topo -> valores[topo -> tamanho - 1];
	}
}*/

void verifica(pilha *topo)
{
	int direita_parenteses = 0, esquerda_parenteses = 0, direita_cochetes = 0, esquerda_cochetes = 0;
	while(topo -> tamanho > 0)
	{
		char aux = pop(topo);
		if(aux == ')')
		{
			esquerda_parenteses += 1;
		}
		else if(aux == '(')
		{
			direita_parenteses += 1;
			if(direita_parenteses > esquerda_parenteses)
			{
				printf("No\n");
				return;
			}
		}
		else if(aux == ']')
		{
			esquerda_cochetes += 1;
		}
		else if(aux == '[')
		{
			direita_cochetes += 1;
			if (direita_cochetes > esquerda_cochetes)
			{
				printf("No\n");
				return;
			}
		}
	}

	if(direita_parenteses == esquerda_parenteses && direita_cochetes == esquerda_cochetes)
	{
		printf("Yes\n");
	}
	else
	{
		printf("No\n");
	}
	return;
}

pilha* criar_pilha()
{
	pilha *new_topo = (pilha*) malloc(sizeof(pilha));
	new_topo -> tamanho = 0;
	return new_topo;
}

int main()
{
	int quantidade, i = 0, tam;
	char string[255];

	scanf("%d\n", &quantidade);

	while(i < quantidade)
	{
		pilha *topo = criar_pilha();

		scanf("%[^\n]", string);
		getchar();

		tam = strlen(string);

		for(int j = 0; j < tam; j++)
		{
			push(topo, string[j]);
		}

		printf("%d\n", topo -> tamanho);

		verifica(topo);

		i++;
	}
	return 0;
}

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct node
{
	char valor;
	struct node *next;
};

typedef struct node node;

struct pilha
{
	int tamanho;
	struct node *top;
};

typedef struct pilha pilha;

int vazia(pilha *stack)
{
    if(stack == NULL)
    {
        return 1;
    }
    return 0;
}

void verifica(char string[], int tam, pilha *stack)
{
	if(vazia(stack) == 1)
	{
		printf("Yes\n");
		return;
	}
	else
	{
		int direita_parenteses = 0, esquerda_parenteses = 0, direita_cochetes = 0, esquerda_cochetes = 0;
		
		for(int i = 0; i < tam; i++)
		{	
			if(string[i] == '(')
			{
				direita_parenteses += 1;
			}
			else if(string[i] == ')')
			{
				esquerda_parenteses += 1;
				if(esquerda_parenteses > direita_parenteses)
				{
					printf("No\n");
					return;
				}
			}
			else if(string[i] == '[')
			{
				direita_cochetes += 1;
			}
			else if(string[i] == ']')
			{
				esquerda_cochetes += 1;
				if (esquerda_cochetes > direita_cochetes)
				{
					printf("No\n");
					return;
				}
			}
		}

		if(direita_parenteses == esquerda_parenteses && direita_cochetes == esquerda_cochetes)
		{
			printf("Yes\n");
		}
		else
		{
			printf("No\n");
		}
		
		return;
	}
}

node* add(char item)
{
	node *new_node = (node*) malloc(sizeof(node));
	new_node -> valor = item;
	new_node -> next = NULL;
	return new_node;
}

pilha* criar_pilha()
{
	pilha *new_pilha = (pilha*) malloc(sizeof(pilha));
	new_pilha -> top = NULL;
	new_pilha -> tamanho = 0;
	return new_pilha;
}

void push(pilha *stack, char item)
{
	node *new_node = add(item);
	new_node -> next = stack -> top;
	stack -> top = new_node;
	stack -> tamanho++;
}

/*void pop(pilha *stack)
{
	if(stack -> tamanho > 0)
	{
		
	}
	else
	{
		return topo -> valores[--topo -> tamanho];
	}
}*/

node* criar_lista()
{
	return NULL;
}

int main()
{
	pilha* stack = criar_pilha();
	node* lista = criar_lista();

	int quantidade, i = 0, tam;
	char string[256];

	scanf("%d\n", &quantidade);

	while(i < quantidade)
	{
		gets(string);

		tam = strlen(string);

		verifica(string, tam, stack);

		i++;

		stack -> top = NULL;
	}
	return 0;
}