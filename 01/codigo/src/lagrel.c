/* 
 * Trabalho de MO420 - Programacao Linear Inteira
 * 2009s1 - Prof. Cid
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#include "../include/lagrel.h"

/*
 * copy_matrix: Copia o valor da matriz src para dest.
 */
static void copy_matrix(int ***dest, int **src, int n)
{
	int i;
	int j;

	for (i = 0; i < n; i++) {
		for (j = 0; j< n; j++) {
			(*dest)[i][j] = src[i][j];
		}
	}
	
	return;

} /* copy_matrix */			

/*
 * new_cost: Calcula o custos das arestas para a solucao primal.
 */
static void new_cost(float ***c, float **a, float **b, int n)
{
	int i;
	int j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			(*c)[i][j] = a[i][j] + b[i][j];
		}
	}

	return;

} /* new_cost */

/* 
 * print_solution: imprime os vertices do caminho de s a t
 */
static void print_solution(int **sol, int n, int s, int t)
{
	int i;
	int u;
	int tmp;
	
	fprintf(stdout, "Caminho: %d ", s);
	u = s;
	i = 0;
	while ((u != t) && (i < n)) {
		if (sol[u][i] != 0) {
			fprintf(stdout, "%d ", i);
			tmp = u;
			u = i;
			i = tmp;
		}
		i++;
	}
 
	fprintf(stdout, "\n");
	return;

} /* print_solution */

/*
 * calc_solution: Calcula o valor da distancia do conjunto  
 * solucao dado.
 */
static float calc_solution(struct graph *G, int **x)
{
	int i;
	int j;

	float dist;

	dist = 0;
	for (i = 0; i < G->v; i++) {
		for (j = i; j < G->v; j++) {
			dist = dist + (G->dist[i][j] * x[i][j]);
		}
	}

	return dist;

} /* calc_solution */

/*
 * calc_cost: Calcula o custo do caminho do conjunto  
 * solucao dado.
 */
static float calc_cost(struct graph *G, int **x)
{
	int i;
	int j;

	float cost;

	cost = 0;
	for (i = 0; i < G->v; i++) {
		for (j = i; j < G->v; j++) {
			cost = cost + (G->cost[i][j] * x[i][j]);
		}
	}

	return cost;

} /* calc_cost */

/*
 * update_lag_cost_rl1: Calcula o custo lagrangeano para a 
 * relaxacao 1.
 * Entrada:
 *   - Informacoes sobre o grafo de entrada
 *   - Multiplicadores de lagrange
 * Saida:
 *   - Custo lagrangeano
 */
static void update_lag_cost_rl1(struct graph *G, float *u, 
				struct edge **E)
{
	int i;
	int j;
	int s;
	int t;

	float **lag_cost;

	s = 0;
	t = G->v -1;

	/* Calculando o custo lagrangeano */
	lag_cost = (float **) malloc(G->v * sizeof(float *));
	for (i = 0; i < G->v; i++) {
		lag_cost[i] = (float *) malloc(G->v *
					       sizeof(float));
	}

	/* Vertice j != de s e t (sum(xij) - sum(xij) = 0)  */
	for (j = 0; j < G->v; j++) {
		for (i = 0; i < G->v; i++) {
			lag_cost[j][i] = (G->dist)[j][i];
		}
	}

	/* Vertice j != de s e t (sum(xij) = 2)  */
/* 	for (j = 0; j < G->v; j++) { */
/* 		for (i = 0; i < G->v; i++) { */
/* 			lag_cost[j][i] = (G->dist)[j][i] + u[j]; */
/* 		} */
/* 	} */
	
	/* Vertice s */
	for (i = 0; i < G->v; i++) {
		if ((G->dist)[s][i] != 0) {
			lag_cost[s][i] = (G->dist)[s][i] + u[s];
			lag_cost[i][s] = (G->dist)[i][s] + u[s];
		}
		else {
			lag_cost[s][i] = 0;
			lag_cost[i][s] = 0;
		}
	}
		
	/* Vertice t */
	for (i = 0; i < G->v; i++) {
		if ((G->dist)[i][t] != 0) {
			lag_cost[i][t] = (G->dist)[i][t] + u[t];
			lag_cost[t][i] = (G->dist)[t][i] + u[t];
		}
		else {
			lag_cost[i][t] = 0;
			lag_cost[t][i] = 0;
		}
	}

	/* Atualizando a estrutura de arestas para o
	   novo custo */
	update_edge_cost(lag_cost, G->e, E);

	/* Liberando Memoria */
	for (i = 0; i < G->v; i++) {
		free(lag_cost[i]);
	}
	free(lag_cost);

	return;

} /* update_lag_cost_rl1 */

/*
 * update_lag_cost_rl2: Calcula o custo lagrangeano para a 
 * relaxacao 2.
 * Entrada:
 *   - Informacoes sobre o grafo de entrada
 *   - Multiplicadores de lagrange
 * Saida:
 *   - Custo lagrangeano
 */
static void update_lag_cost_rl2(struct graph *G, float u, float ***c)
{
	int i;
	int j;
	
	for (i = 0; i < G->v; i++) {
		for (j = 0; j < G->v; j++) {
			(*c)[i][j] = (G->dist)[i][j] + u * (G->cost)[i][j];
		}
	}

	return;
} /* update_lag_cost_rl2 */

/*
 * is_feasible: Verifica se a solucao e viavel para o PCMCRC.
 * Entrada:
 *   - Informacoes sobre o grafo de entrada
 *   - Conjunto solucao a ser analisado
 * Saida:
 *   - Retorna 1 caso seja viavel e 0 cc
 */
static int is_feasible(struct graph *G, int **x)
{
	int i;
	int j;
	int u;
	int t;
	int tmp;

	float cost;

	/* Verifica se forma um caminho */
	u = 0;
	t = G->v - 1;
	i = 0;
	while ((u != t) && (i < G->v)) {
		if (x[u][i] != 0) {
			tmp = u;
			u = i;
			i = tmp;
		}
		i++;
	}

	if (u != t) {
		return 0;
	}

	/* calculando o custo da solucao */
	cost = 0;
	for (i = 0; i < G->v; i++) {
		for (j = i; j < G->v; j++) {
			cost = cost + ((G->cost)[i][j] * x[i][j]);
		}
	}

	/* verificando se a restricao e satisfeita */
	if (cost > G->max_cost) {
		return 0;
	}

	return 1;

} /* is_feasible */

/*
 * is_optimal_rl1: Verifica se a solucao e otima para o PCMCRC
 * na relaxacao 1.
 * Entrada:
 *   - Informacoes sobre o grafo de entrada
 *   - Conjunto solucao a ser analisado
 * Saida:
 *   - Retorna 1 caso seja otima e 0 cc
 */
static int is_optimal_rl1(struct graph *G, int **sol)
{
	int i;
	int u;
	int t;
	int tmp;

	/* Verifica se forma um caminho */
	u = 0;
	t = G->v - 1;
	i = 0;
	while ((u != t) && (i < G->v)) {
		if (sol[u][i] != 0) {
			tmp = u;
			u = i;
			i = tmp;
		}
		i++;
	}

	if (u != t) {
		return 0;
	}

	return 1;

} /* is_optimal_rl1 */

/*
 * is_optimal_rl2: Verifica se a solucao e otima para o PCMCRC
 * na relaxacao 2.
 * Entrada:
 *   - Informacoes sobre o grafo de entrada
 *   - Conjunto solucao a ser analisado
 * Saida:
 *   - Retorna 1 caso seja otima e 0 cc
 */
static int is_optimal_rl2(struct graph *G, int **x)
{
	int i;
	int j;
	
	float c;

	/* Verifica se a retricao da mochila e valida
	   na igualdade */
	c = G->max_cost;
	for (i = 0; i < G->v; i++) {
		for (j = 0; j < G->v; j++) {
			c = c - ((G->cost)[i][j] * x[i][j]);
		}
	}
	
	/* Se nao e valida na igualdade a solucao nao e otima
	   para o PCMCRC */
	if (c != 0) {
		return 0;
	}

	return 1;

} /* is_optimal_rl2 */

/*
 * primal_bound: Encontra o limitante primal para o PCMCRC
 * Entrada:
 *   - Informacoes sobre o grafo de entrada
 * Saida:
 *   - Conjunto solucao
 *   - Limitante primal
 */
static float primal_bound(struct graph *G, int ***x)
{
	float cost;
	
	float **C;

	int i;
	
	/* Calculando os custos das arestas */
	C = (float **) malloc(G->v * sizeof(float *));
	for (i = 0; i < G->v; i++) {
		C[i] = (float *) malloc(G->v * sizeof(float));
	}
	
	new_cost(&C, G->cost, G->dist, G->v);

	/* Encontra o menor caminho usando o custo + distancia
	   como distancia fazendo com que a restricao de custo 
	   (mochila) seja satisfeita. */
	cost = shortest_path(C, G->v, 0, G->v - 1, x);
	
	/* Calculando o custo da solucao encontrada */
	cost = calc_cost(G, (*x));

	if (cost > G->max_cost) {
		fprintf(stderr, ">>>ERROR: primal_bound");
		fprintf(stderr, "restricao de custo nao satisfeita.");
		fprintf(stderr, "\n");
		fprintf(stderr, ">>> (%f > %d) \n", cost, G->max_cost);
		return -1;
	}

	/* Liberando memoria */
	for (i = 0; i < G->v; i++) {
		free(C[i]);
	}
	free(C);

	/* Encontrando a distancia do caminho encontrado */
	return calc_solution(G, (*x));
	
} /* primal_bound */

/*
 * lag_heuristic: Heuristica lagrangeana que calcula os valores dos 
 * limitantes usando o metodo do subgradiente, encontrando a solucao
 * do problema.
 * Entrada:
 *   - Parametros para o metodo do subgradiente
 *   - Informacoes sobre o grafo de entrada
 *   - Relaxacao a ser feita
 *   - Nome do arquivo de saida que tera os valores dos limitantes
 *     a cada iteracao
 */
void lag_heuristic(struct subgrad_param *subpar, 
		   struct graph *G, 
		   int rel,
		   const char *filename)
{
	float ub;
	float lb;
	float ub_tmp;
	float lb_tmp;
	float t;
	float sol;
	float cost;
	float cost_aux;
	float *c;
	float *u;

	float **lag_cost;

	int i;
	int j;
	int k;
	int l;
	
	int **x_sol;
	int **x;

	struct edge *E;

	struct timeval iub;
	struct timeval fub;
	struct timeval ilb;
	struct timeval flb;
	struct timeval resub;
	struct timeval reslb;

	FILE *f_out;

	/* Inicializacao */
	if ((f_out = fopen(filename, "wb")) == NULL) {
		fprintf(stderr, ">>>ERROR: ");
		fprintf(stderr, "Arquivo de saida invalido!!\n");
		return;
	} 
	
	x_sol = (int **) malloc(G->v * sizeof(int *));
	for (i = 0; i < G->v; i++) {
		x_sol[i] = (int *) malloc(G->v * sizeof(int)); 
	}

	x = (int **) malloc(G->v * sizeof(int *));
 	for (i = 0; i < G->v; i++) {
		x[i] = (int *) malloc(G->v * sizeof(int)); 
	}
       
	for (i = 0; i < G->v; i++) {
		for (j = 0; j < G->v; j++) {
			x_sol[i][j] = 0;
			x[i][j] = 0;
		}
	}
	
	lb = 0;
	ub = INF;

	k = 0;
	l = 0;
	sol = INF;
	cost = INF;
	cost_aux = 0;

	/* Encontrando o limitante primal */
	gettimeofday(&iub, NULL);

	ub_tmp = primal_bound(G, &x_sol);

	ub = MIN(ub, ub_tmp);
	gettimeofday(&fub, NULL);

	gettimeofday(&ilb, NULL);

	switch(rel) {
	case 1: /* Problema da Mochila: Restricoes do PCMC 
		   dualizadas */

		/* Pegando o conjunto de arestas do grafo
		   para facilitar a implementacao do algoritmo
		   da mochila */
		E = create_edge_array(G);

		u = (float *) malloc(G->v * sizeof(float));
		c = (float *) malloc(G->v * sizeof(float));

		/* Multiplicadores de lagrange = 0 */
		for (i = 0; i < G->v; i++) {
			u[i] = 0;
			c[i] = 0;
		}

		while ((k <= subpar->max_iter) && (ub - lb >= 1)) {
			/* Atualizando os custos lagrangeanos */
			update_lag_cost_rl1(G, u, &E);

			/* Problema da mochila e de maximizacao */
			lb_tmp = knapsack(E, G->e, G->v, G->max_cost, &x);

			/* custo - u[s] - u[t] */
			lb_tmp = lb_tmp - u[0] - u[G->v - 1];

			/* sum(xij) = 2 */
/* 			cost_aux = 0; */
/* 			for (i = 1; i < G->v - 1; i++) { */
/* 				cost_aux = cost_aux + 2 * u[i]; */
/* 			} */
/* 			lb_tmp = lb_tmp - cost_aux; */

			fprintf(stderr, "%d lb_tmp: %f\n", k, lb_tmp);

			for (i = 0; i < G->v; i++) {
				for (j = 0; j < G->v; j++) {
					fprintf(stderr, "%d ", x[i][j]);
				}
				fprintf(stderr,"\n");
			}

			/* Verifica se a solucao encontrada e viavel 
			   para o PCMCRC */
			if (is_feasible(G, x) != 0) {
				if (lb_tmp > ub) {
					copy_matrix(&x_sol, x, G->v);
					ub = calc_solution(G, x_sol);
				}

				/* Verificando se a solucao e otima
				   para o PCMCRC */
				if (is_optimal_rl1(G, x) != 0) {
					sol = calc_solution(G, x);
					cost = calc_cost(G, x);
					break;
				}
			}

			if (lb_tmp > lb) {
				lb = lb_tmp;
				l = 0;
			}
						
			fprintf(f_out, "\t%d\t%f\t%f\n", k, lb, ub);

			/* Criterio de parada */
			if (ub - lb < 1) {
				/* solucao encontrada e otima */
				sol = calc_solution(G, x_sol);
				cost = calc_cost(G, x_sol);
				break;
			}

			/* Atualizando os multiplicadores */
			if (l > subpar->max_iter_no_improv) {
				subpar->e = subpar->e / 2;
				l = 0;
			}

			cost_aux = 0;
			/* Vertices j != s e t */
/* 			for (j = 1; j < G->v - 1; j++) { */
/* 				c[j] = 2; */
/* 				for (i = 0; i < G->v; i++) { */
/* 					c[j] = c[j] - x[j][i]; */
/* 				} */
/* 				cost_aux = cost_aux + (c[j] * c[j]); */
/* 			} */
			
			/* Vertice s */
			c[0] = 1;
			for (i = 0; i < G->v; i++) {
				c[0] = c[0] - x[0][i];
			}
			cost_aux = cost_aux + (c[0] * c[0]); 
			
			/* Vertice t */
			c[G->v - 1] = 1;
			for (i = 0; i < G->v; i++) {
				c[G->v-1] = c[G->v-1] - x[i][G->v-1];
			}
			cost_aux = cost_aux + (c[G->v-1] * c[G->v-1]); 

			/******VERIFICAR AQUI A ATUALIZACAO DOS MULTIPLICADORES**********/

			t = subpar->e * (lb_tmp - ub) / cost_aux;
			for (j = 0; j < G->v; j++) {
				u[j] = u[j] - t * c[j];
			}

			k++;
			l++;
		}
		
		/* caso ultrapasse o numero maximo de iteracoes */
		if (k > subpar->max_iter) {
			sol = calc_solution(G, x_sol);
			cost = calc_cost(G, x_sol);
			k--; /* ajuste no numero de iteracoes */
		}
		
		/* Liberando memoria */
		free(u);
		free(c);

		free_edge_array(E);

		break;
	case 2: /* Problema do PCMC: Restricao da Mochila
		   dualizada */
		
		u = (float *) malloc(sizeof(float));
		c = (float *) malloc(sizeof(float));

		/* Multiplicadores de lagrange = 0 */
		u[0] = 0;

		/* Criando matriz de custos lagrangeanos */
		lag_cost = (float **) malloc(G->v * sizeof(float *));
		for (i = 0; i < G->v; i++) {
			lag_cost[i] = (float *) malloc(G->v * 
						       sizeof(float));
		}
	
		for (i = 0; i < G->v; i++) {
			for (j = 0; j < G->v; j++) {
				lag_cost[i][j] = 0;
			}
		}

		while ((k <= subpar->max_iter) && (ub - lb >= 1)) {
			/* Atualizando os custos lagrangeanos */
			update_lag_cost_rl2(G, u[0], &lag_cost);

			lb_tmp = shortest_path(lag_cost, 
					       G->v, 0, 
					       G->v - 1, &x);

			/* custo - u*C */
			lb_tmp = lb_tmp - u[0] * G->max_cost;

			/* Verifica se a solucao encontrada e viavel 
			   para o PCMCRC */
			if (is_feasible(G, x) != 0) {
				if (lb_tmp > ub) {
					copy_matrix(&x_sol, x, G->v);
					ub = calc_solution(G, x_sol);
				}

				/* Verificando se a solucao e otima
				   para o PCMCRC */
				if (is_optimal_rl2(G, x) != 0) {
					copy_matrix(&x_sol, x, G->v);
					sol = calc_solution(G, x_sol);
					cost = calc_cost(G, x_sol);
					break;
				}
			}

			if (lb_tmp > lb) {
				lb = lb_tmp;
				l = 0;
			}
						
			fprintf(f_out, "\t%d\t%f\t%f\n", k, lb, ub);

			/* Criterio de parada */
			if (ub - lb < 1) {
				/* solucao encontrada e otima */
				sol = calc_solution(G, x_sol);
				cost = calc_cost(G, x_sol);
				break;
			}

			/* Atualizando os multiplicadores */
			if (l > subpar->max_iter_no_improv) {
				subpar->e = subpar->e / 2;
				l = 0;
			}

			c[0] = G->max_cost;
			for (i = 0; i < G->v; i++) {
				for (j = 0; j < G->v; j++) {
					c[0] = c[0] - ((G->cost)[i][j] * 
						 x[i][j]);
				}
			}

			t = subpar->e * (lb_tmp - ub) / (c[0] * c[0]) ;
			u[0] = MAX(0, u[0] + t * c[0]);

			k++;
			l++;
		}
		
		/* caso ultrapasse o numero maximo de iteracoes */
		if (k > subpar->max_iter) {
			sol = calc_solution(G, x_sol);
			cost = calc_cost(G, x_sol);
			k--; /* ajuste no numero de iteracoes */
		}
		
		/* Liberando memoria */
		free(u);
		free(c);

		for (i = 0; i < G->v; i++) {
			free(lag_cost[i]);
		}
		free(lag_cost);

		break;

	default:
		fprintf(stderr, ">>>ERROR: relaxacao nao existente\n");
		break;
	}

	gettimeofday(&flb, NULL);

	fclose(f_out);

	timeval_subtract(&resub, &fub, &iub);
	timeval_subtract(&reslb, &flb, &ilb);

	fprintf(stdout, "Numero de iteracoes: %d \n", k + 1);
	fprintf(stdout, "tempo: %ld seg e %ld microseg",
		(time_t)resub.tv_sec, (suseconds_t)resub.tv_usec);
	fprintf(stdout, " - limitante superior: %f\n", ub);
	fprintf(stdout, "tempo: %ld seg e %ld microseg",
		(time_t)reslb.tv_sec, (suseconds_t)reslb.tv_usec);
	fprintf(stdout, " - limitante inferior: %f\n", lb);

	fprintf(stdout, "Distancia do Caminho: %f\n", sol);
	fprintf(stdout, "Custo do Caminho: %f\n", cost);
	print_solution(x_sol, G->v, 0, G->v -1);

	/* Liberando memoria */
 	for (i = 0; i < G->v; i++) {
		free(x[i]);
		free(x_sol[i]);
	}
	free(x);
	free(x_sol);

	return;

} /* lag_heuristic */

/* EOF */