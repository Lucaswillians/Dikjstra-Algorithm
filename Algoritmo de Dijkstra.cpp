#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// prototipo funcao
void grafo();
void dijkstra(int vertices, int origem, int destino, int *custos);
void resultado();

// variaveis 
int origem, destino, vertices = 0;
int custo;
int *custos = NULL;

int main ()
{
grafo();
dijkstra(vertices, origem, destino, custos);
resultado();

	return 0;
}

void grafo ()
{
	do 
	{
		printf("Digite o numero de vertices: ");
		scanf("%i", &vertices);	
	}
	while (vertices < 3);

	if (!custos)
	{
		free(custos);
	}

	custos = (int*) malloc(sizeof(int)*vertices*vertices);
	
	for (int i = 0; i <= vertices; i++)
	{
		custos[i] = -1;
	}
	
	do 
	{
		system("cls");
		printf("Digite o numero de arestas: \n");
	
		do 
		{
			printf("Origem: Vertice 1 ao Vertice %i | Digite '0' para sair", vertices);
			scanf("%i", &origem);
		}
		while (origem < 0 || origem > vertices);
		
		if (origem)
		{
			do 
			{
				printf("Destino entre 1 e %i, exceto o %i", vertices, origem);
				scanf("%i", &destino);
			}
			while (destino < 1 || destino > vertices || destino == origem);
			
			do 
			{
				printf("Custo do vertice %i para o vertice %i", origem, destino);
				scanf("%i", &custo);
			}
			while (custo < 0);
			custos[(origem-1) * vertices + destino -1] = custo;
		}
	}	
	while (origem);
}

void dijkstra (int vertices, int origem, int destino, int *custos)
{
	int *ant, *tmp, i, v, cont = 0;
	int *z;
	double dist[vertices];
	double min;
	
	ant = (int *)  calloc (vertices, sizeof(int *));
		
	tmp = (int *)  calloc (vertices, sizeof(int *));
	
	z = (int *)  calloc (vertices, sizeof(int *));
	
	for ( i = 0; i < vertices; i++)
	{
		if (custos [(origem - 1) * vertices + i] != -1)
		{
			ant[i] = origem - 1;
			dist[i] = custos [(origem - 1) * vertices + i];
		}
		else 
		{
			ant[i] = -1;
			dist[i] = HUGE_VAL;
		}
		z[i] = 0;	
	}
	
	z[origem - 1] = 1;
	dist[origem-1] = 0;
	 
	do
	{
		min = HUGE_VAL;
		for (i = 0; i < vertices; i++)
		{
			if (!z[i])
			{
				if (dist[i] >= 0 && dist[i] < min)
				{
					min = dist[i]; v=i;
				}
			}
		}
		if (min != HUGE_VAL && v != destino - 1)
		{
			z[v] = 1;
			for (i = 0; i < vertices; i++)
			{
				if (!z[i])
				{
					if (custos[v*vertices+i] != -1 && dist[v] + custos[v*vertices+i] < dist[i])
					{
						dist[i] = dist[v] + custos[v*vertices+i];
						ant[i] = v;
					}
				}
			}
		}
	}
	while (v != destino -1 && min != HUGE_VAL);
	
	printf("\t De %i para %i: \t", origem, destino);
	if (min == HUGE_VAL)
	{
		printf("Não Existe\n");
		printf("\t Custo \t \n");
	}
	else 
	{
		i = destino;
		i = ant[i-1];
		while (i != -1)
		{
			tmp[cont] = i + 1;
			cont++;
			i = ant[i];
		}
	
		for ( i = cont; i > 0; i--)
		{
			printf("%i -> ", tmp[i - 1]);
		}
		
		printf("%i", destino);
		printf("\n\t Custo: \n", dist[destino -1]);
	}
}

void resultado()
{
	int i, j;
	system("cls");
	printf("Lista dos menores caminhos do grafo: \n");
	for (i = 1; i <= vertices; i++)
	{
		for (j = 1; j <= vertices; j++)
		{
			dijkstra(vertices, i, j, custos);
		}
	}
}
