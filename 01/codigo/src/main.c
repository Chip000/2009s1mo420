/* 
 * Trabalho de MO420 - Programacao Linear Inteira
 * 2009s1 - Prof. Cid
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "../include/myfunc.h"
#include "../include/mytime.h"
#include "../include/parser.h"

#define DEBUG 1
#define TARGET "relaxlag"

void display_help(void)
{
	fprintf(stderr, "USAGE: ./%s (num_rel) (arq_inst)\n\n", TARGET);
	fprintf(stderr, "num_rem: Relaxacao a ser testada 1 ou 2\n");
	fprintf(stderr, "         1- dualiza-se as restricoes do PCMC\n");
	fprintf(stderr, "         2- dualiza-se a restricao da KNAP\n");
	fprintf(stderr, "arq_inst: arquivo de instancia a ser resolvida\n");

	return;
}

int main(int argc, char **argv) {

	struct timeval ini;
	struct timeval fin;
	struct timeval res;

	struct graph G;

	int relax;
	char *filename;

	float cost;
	int *x;

	if (argc < 3) {
		fprintf(stderr, ">>>ERROR: Numero de parametros invalido!!\n");
		display_help();
		return 1;
	}

	relax = atoi(argv[1]);
	filename = argv[2];

	if ((relax != 1) && (relax != 2)) {
		fprintf(stderr, ">>>ERROR: Opcao para relaxacao invalida!!\n");
		display_help();
		return 1;
	}
	
	/* tempo de inicio */
	gettimeofday (&ini, NULL);

	/* Carregando a entrada na memoria */
	if (parser(filename, &G) != 0) {
		fprintf(stderr, ">>>ERROR: Arquivo invalido!!\n");
		return 1;
	}

	if (DEBUG == 1) {
		print_graph(G);
	}

	cost = shortest_path(G.cost, G.v, 0, G.v - 1, &x);

	fprintf(stderr, "Custo = %f\n", cost);

	if (DEBUG == 1) {
		print_shortest_path(x, G.v, cost);
	}

	free(x);

	free_graph(G);

	/* tempo de termino */
	gettimeofday(&fin, NULL);

	/* apresentando tempo total */
	timeval_subtract (&res, &fin, &ini);
	fprintf(stdout, "tempo total: %ld seg e %ld microseg\n", 
			(time_t)res.tv_sec, (suseconds_t)res.tv_usec);

	return 0;

}

/* EOF */
