/* 
 * Trabalho de MO420 - Programacao Linear Inteira
 * 2009s1 - Prof. Cid
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#include "../include/parser.h"

/*
 * parser: Guarda as informacoes do arquivo de entrada na
 * estrutura graph. 
 * Retorna 0 em caso de sucesso e 1 caso contrario.
 */
int parser(const char *filename, struct graph *G)
{

	int i = 0;
	int u = 0;
        int v = 0;
	float c = 0;
	float d = 0;

	char buff[MAX_BUFFER_SIZE];

	FILE *file;
	if ((file = fopen(filename, "r")) == NULL) {
		return 1;
	}

	/* Pulando as duas primeiras linhas do arquivo */
	fgets(buff, MAX_BUFFER_SIZE, file);
	fgets(buff, MAX_BUFFER_SIZE, file);
 
	/* Pegando a quantidade de vertices */
	fscanf(file, "N.Vert:%d\n", &(G->v));
		
	/* Pegando a quantidade de arestas */
	fscanf(file, "N.Arest:%d\n", &(G->e));
		
	/* Valor da restricao de custo maximo do caminho  */
	fscanf(file, "Custo Max:%d\n", &(G->max_cost));
	
	/* Alocando espaco para a matriz de custo e de distancia das arestas */
	G->cost = (float **) malloc(G->v * sizeof(float *));
	for (i = 0; i < G->v; i++) {
		G->cost[i] = (float *) malloc(G->v * sizeof(float));
	}

	G->dist = (float **) malloc(G->v * sizeof(float *));
	for (i = 0; i < G->v; i++) {
		G->dist[i] = (float *) malloc(G->v * sizeof(float));
	}

	/* Pulando as 2 proximas linhas do arquivo (Arestas+cabecalho) */
	fgets(buff, MAX_BUFFER_SIZE, file);
	fgets(buff, MAX_BUFFER_SIZE, file);

	/* Armazenando os valores de custos e distancias das arestas
	 * OBS: o grafo	e' nao-orientado */
	while ((fscanf(file, "%d\t%d\t%f\t%f\n", &u, &v, &d, &c)) > 0) {
		G->cost[u][v] = c;
		G->cost[v][u] = c;
		G->dist[u][v] = d;
		G->dist[v][u] = d;
	}
	
	fclose(file);

	return 0;

} /* parser */


/*
 * free_graph: Libera a memoria usada pela estrutura graph.
 */
void free_graph(struct graph G)
{
	
	int i;

	for (i = 0; i < G.v; i++) {
		free(G.cost[i]);
		free(G.dist[i]);
	}
	
	free(G.cost);
	free(G.dist);

	return;

} /* free_graph */

/* DEBUG FUNCTIONS */

/* 
 * print_graph: imprime as informacoes contidas na estrutura
 * graph lida.
 */
void print_graph(struct graph G)
{
	int i, j;
	
	fprintf(stdout, "\n>>>DEBUG: \n");

	fprintf(stdout, "N. Vert:%d\n", G.v);
	fprintf(stdout, "N. Arest:%d\n", G.e);
	fprintf(stdout, "Custo Max:%d\n", G.max_cost);
	
	fprintf(stdout, "\nCost: \n");
	for (i = 0; i < G.v; i++) {
		for (j = 0; j < G.v; j ++) {
			fprintf(stdout, "%.2f ", G.cost[i][j]);
		}
		fprintf(stdout, "\n");
	} 

	fprintf(stdout, "\nDist: \n");
	for (i = 0; i < G.v; i++) {
		for (j = 0; j < G.v; j ++) {
			fprintf(stdout, "%.2f ", G.dist[i][j]);
		}
		fprintf(stdout, "\n");
	} 

	return;

} /* print_graph */

/* EOF */
