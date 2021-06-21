#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

struct node
{
	int value;
	struct node* next;
};

typedef struct node node;

struct dados
{
	int item;
	struct dados *next;
	//int anterior;
};

typedef struct dados dados;

struct graph
{
	dados *table[10000];
	int visitado[10000];
	int anterior[10000];
};

typedef struct graph graph;

struct fila
{
	struct dados* head;
};

typedef struct fila fila;

void ordenar(dados *head)
{
	int aux;
	dados* hi;
	dados* hj;
	dados* hfim = NULL;

	if(head == NULL)
	{
		return;
	}

	for(hi = head; hi -> next != NULL; hi = hi -> next)
	{
		for(hj = head; hj -> next != hfim; hj = hj -> next)
		{
			if(hj -> item > hj -> next -> item)
			{
				aux = hj -> item;
				hj -> item = hj -> next -> item;
				hj -> next -> item = aux;
			}
		}

		hfim = hj;
	}
}

fila* criar_fila()
{
	fila *new_fila = (fila*) malloc(sizeof(fila));
	new_fila -> head = NULL;
	return new_fila;
}

void enqueue(fila* queue, int item)
{
	dados *new_dado = (dados*) malloc(sizeof(dados));
	new_dado -> item = item;

	if(queue -> head == NULL)
	{
		new_dado -> next = queue -> head;
		queue -> head = new_dado;
	}
	else
	{
		dados* aux = queue -> head;
		while(aux -> next != NULL)
		{
			aux = aux -> next;
		}
		aux -> next = new_dado;
		new_dado -> next = NULL;
	}
}

int dequeue(fila* queue)
{
	int first = queue -> head -> item;
	queue -> head = queue -> head -> next;
	return first;
}

bool esta_vazia(fila* queue)
{
	if(queue -> head == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int contar(graph* grafo, int inicio, int destino)
{
	int count = 0;

	if(inicio == destino)
	{
		return 0;
	}

	if(grafo -> anterior[destino] == -1)
	{
		return -666;
	}

	while(grafo -> anterior[destino] != inicio)
	{
		if(grafo -> anterior[destino] == -1)
		{
			return -666;
		}
		count++;
		destino = grafo -> anterior[destino];
	}
	count++;
	return count;
}

void percorrer_em_largura(graph* grafo, int inicio, int destino)
{
	printf("Iniciando busca em largura a partir de %d\n", inicio);
	fila *queue = criar_fila();
	int dequeued;
	dados *adj = grafo -> table[inicio];
	grafo -> visitado[inicio] = 1;
	enqueue(queue, inicio);

	while(esta_vazia(queue) == false)
	{
		dequeued = dequeue(queue);
		adj = grafo -> table[dequeued];
		while(adj != NULL)
		{
			if(grafo -> visitado[adj -> item] == 0)
			{
				printf("Iniciando busca em largura a partir de %d\n", adj -> item);
				grafo -> visitado[adj -> item] = 1;
				enqueue(queue, adj -> item);
				grafo -> anterior[adj -> item] = dequeued;
			}

			adj = adj -> next;
		}
	}

	printf("\n");

	free(queue);
}

node* add(node* head, int value)
{
	node *new_node = (node*) malloc(sizeof(node));
	new_node -> value = value;
	new_node -> next = head;
	return new_node;
}

void imprimir_tabela(graph* grafo, int inicio, int tamanho, int quantidade, int destino)
{
	int dist;

	for(int j = 0; j < tamanho; j++)
	{
		grafo -> visitado[j] = 0;
	}

	for(int i = 0; i < tamanho; i++)
	{
		dist = contar(grafo, inicio, i);

		if(dist == -666)
		{
			printf("%d | - | -\n", i);
		}
		else
		{
			printf("%d | %d | ", i, dist);

			if(grafo -> anterior[i] == -1)
			{
				printf("-\n");
			}
			else
			{
				printf("%d\n", grafo -> anterior[i]);
			}
		}
		
		for(int j = 0; j < tamanho; j++)
		{
			grafo -> visitado[j] = 0;
		}
	}

	printf("\n");

	node* head = NULL;

	if(inicio == destino)
	{
		printf("Caminho entre %d e %d: %d\n\n", inicio, destino, inicio);
		return;
	}

	if(grafo -> anterior[destino] == -1)
	{
		printf("Sem caminho entre %d e %d\n\n", inicio, destino);
		return;
	}



	head = add(head, destino);
	int aux_destino = destino;
	while(grafo -> anterior[destino] != inicio)
	{
		if(grafo -> anterior[destino] == -1)
		{
			printf("Sem caminho entre %d e %d\n\n", inicio, destino);
			return;
		}
		
		head = add(head, grafo -> anterior[destino]);

		destino = grafo -> anterior[destino];
	}
	
	head = add(head, grafo -> anterior[destino]);

	destino = aux_destino;

	printf("Caminho entre %d e %d: %d", inicio, destino, inicio);
	head = head -> next;
	while(head != NULL)
	{
		printf(" => %d", head -> value);
		head = head -> next;
	}

	printf("\n\n");
}

graph* creat_graph(int tamanho)
{
	graph* new_graph = (graph*) malloc(sizeof(graph));
	for(int i = 0; i < tamanho; i++)
	{
		new_graph -> table[i] = NULL;
		new_graph -> visitado[i] = 0;
		new_graph -> anterior[i] = -1;
	}
	//new_graph -> dist = -1;
	return new_graph;
}

dados *criar_dado(int value)
{
	dados* new_dado = (dados*) malloc(sizeof(dados));
	new_dado -> item = value;
	new_dado -> next = NULL;
	return new_dado;
}

void add_ligacao(graph *grafo, int x, int y)
{
	dados *vertice = criar_dado(y);
	vertice -> next = grafo -> table[x];
	grafo -> table[x] = vertice;
}

int main()
{
	int tamanho, quantidade_de_ligacoes, casos, i = 0, x, y;

	scanf("%d %d %d\n", &tamanho, &quantidade_de_ligacoes, &casos);

	graph* grafo = creat_graph(tamanho);

	for(i = 0; i < quantidade_de_ligacoes; i++)
	{
		scanf("%d %d", &x, &y);
		add_ligacao(grafo, x, y);
	}

	for(i = 0; i < tamanho; i++)
	{
		ordenar(grafo -> table[i]);
	}

	int inicio, destino;

	for(i = 0; i < casos; i++)
	{
		printf("--------\n\n");

		int quantidade = 0;

		scanf("%d %d", &inicio, &destino);

		dados* aux = grafo -> table[inicio];
		while(grafo -> table[inicio] != NULL)
		{
			quantidade++;
			grafo -> table[inicio] = grafo -> table[inicio] -> next;
		}
		grafo -> table[inicio] = aux;

		printf("Caso de Teste #%d - BFS(%d)\n\n", i+1, inicio);

		percorrer_em_largura(grafo, inicio, destino);
		imprimir_tabela(grafo, inicio, tamanho, quantidade, destino);

		for(int j = 0; j < tamanho; j++)
		{
			grafo -> visitado[j] = 0;
			grafo -> anterior[j] = -1;
		}
	}

	free(grafo);

	printf("--------\n");

	return 0;
}