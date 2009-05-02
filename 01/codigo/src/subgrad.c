/* 
 * Trabalho de MO420 - Programacao Linear Inteira
 * 2009s1 - Prof. Cid
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#include "../include/subgrad.h"

/*
 * copy_matrix: Copia o valor da matriz src para dest
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
	
	/* Encontra o menor caminho usando o custo como distancia
	   fazendo com que a restricao de custo (mochila) 
	   seja satisfeita. */
	cost = shortest_path(G->cost, G->v, 0, G->v - 1, x);

	if (cost > G->max_cost) {
		fprintf(stderr, ">>>ERROR: primal_bound");
		fprintf(stderr, "restricao de custo nao satisfeita.");
		fprintf(stderr, "\n");
		fprintf(stderr, ">>> (%f > %d) \n", cost, G->max_cost);
		return -1;
	}

	/* Encontrando a distancia do caminho encontrado */
	return calc_solution(G, (*x));
	
} /* primal_bound */

/*
 * update_lag_cost_rl1: Calcula o custo lagrangeano para a 
 * relaxacao 1.
 * Entrada:
 *   - Informacoes sobre o grafo de entrada
 *   - Multiplicadores de lagrange
 * Saida:
 *   - Custo lagrangeano
 */
static void update_lag_cost_rl1(struct graph *G)
{
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
			(*c)[i][j] = (G->dist)[i][j] + u * (*c)[i][j];
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

	float cost;

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
 * subgrad_parser: Parser para o arquivo contendo os parametros do 
 * metodo de subgradiente.  
 * Retorna 0 em caso de sucesso e 1 caso contrario.
 */
int subgrad_parser(const char *filename, struct subgrad_param *subpar)
{
	FILE *f;

	if ((f = fopen(filename, "r")) == NULL) {
		return 1;
	}
	
	fscanf(f, "e = %f\n", &(subpar->e));
	fscanf(f, "max_iter = %d\n", &(subpar->max_iter));
	fscanf(f, "max_iter_no_improv = %d\n", 
	       &(subpar->max_iter_no_improv));

	return 0;

} /* subgrad_parser */

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
	float c;
	float *u;

	float **lag_cost;

	int i;
	int j;
	int k;
	int l;
	
	int **x_sol;
	int **x;

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

	/* Encontrando o limitante primal */
	gettimeofday(&iub, NULL);

	ub_tmp = primal_bound(G, &x_sol);

	ub = MIN(ub, ub_tmp);
	gettimeofday(&fub, NULL);

	gettimeofday(&ilb, NULL);

	switch(rel) {
	case 1: /* Problema da Mochila: Restricoes do PCMC 
		   dualizadas */
		break;
	case 2: /* Problema do PCMC: Restricao da Mochila
		   dualizada */
		
		u = (float *) malloc(sizeof(float));

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
					ub = lb_tmp;
				}

				/* Verificando se a solucao e otima
				   para o PCMCRC */
				if (is_optimal_rl2(G, x) != 0) {
					sol = calc_solution(G, x);
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
				break;
			}

			/* Atualizando os multiplicadores */
			if (l > subpar->max_iter_no_improv) {
				subpar->e = subpar->e / 2;
				l = 0;
			}

			c = G->max_cost;
			for (i = 0; i < G->v; i++) {
				for (j = 0; j < G->v; j++) {
					c = c - ((G->cost)[i][j] * 
						 x[i][j]);
				}
			}

			t = subpar->e * (ub - lb_tmp) / (c * c) ;
			u[0] = MAX(0, u[0] - t * c);

			k++;
			l++;
		}
		
		break;
	default:
		/* Empty */
		break;
	}

	gettimeofday(&flb, NULL);

	fclose(f_out);

	timeval_subtract(&resub, &fub, &iub);
	timeval_subtract(&reslb, &flb, &ilb);

	fprintf(stdout, "Numero de iteracoes: %d \n", k);
	fprintf(stdout, "tempo: %ld seg e %ld microseg",
		(time_t)resub.tv_sec, (suseconds_t)resub.tv_usec);
	fprintf(stdout, " - limitante superior: %f\n", ub);
	fprintf(stdout, "tempo: %ld seg e %ld microseg",
		(time_t)reslb.tv_sec, (suseconds_t)reslb.tv_usec);
	fprintf(stdout, " - limitante inferior: %f\n", lb);

	fprintf(stdout, "Custo da solucao: %f\n", sol);


	/* Liberando memoria */
 	for (i = 0; i < G->v; i++) {
		free(x[i]);
		free(x_sol[i]);
	}
	free(x);
	free(x_sol);

	return;

} /* lag_heuristic */

/* DEBUG FUNCTIONS */

/* 
 * print_subgrad_param: imprime os parametros do metodo do 
 * subgradiente
 */
void print_subgrad_param(struct subgrad_param subpar)
{
	fprintf(stdout, "\n>>>DEBUG: \n");

	fprintf(stdout, "E:%f\n", subpar.e);
	fprintf(stdout, "MAX_ITER:%d\n", subpar.max_iter);
	fprintf(stdout, "MAX_ITER_NO_IMPROV:%d\n", subpar.max_iter_no_improv);
	
	fprintf(stdout, "\n");

	return;

} /* print_subgrad_param */

/* EOF */
