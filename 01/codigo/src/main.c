/* 
 * Trabalho de MO420 - Programacao Linear Inteira
 * 2009s1 - Prof. Cid
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "../include/mytime.h"
#include "../include/parser.h"
#include "../include/lagrel.h"

#define DEBUG 1
#define TARGET "relaxlag"
#define DEFAULT_SUBGRAD_PARAM_FILE "param"
#define GNUPLOT_DIR "./gnuplot/"
#define GNUPLOT_EXT ".gnuplot"

void display_help(void)
{
	fprintf(stderr, 
		"USAGE: ./%s (num_rel) (arq_inst) <param> \n",
		TARGET);
	fprintf(stderr, "num_rem: Relaxacao a ser testada 1 ou 2\n");
	fprintf(stderr, "   1- dualiza-se as restricoes do PCMC\n");
	fprintf(stderr, "   2- dualiza-se a restricao da KNAP\n");
	fprintf(stderr, "arq_inst: instancia a resolvida\n");
	fprintf(stderr, "param: arquivo contendo os parametros do ");
	fprintf(stderr, "metodo de subgradiente (opcional)\n");
 
	return;
}

int main(int argc, char **argv) {

	struct timeval ini;
	struct timeval fin;
	struct timeval res;

	struct graph G;
	struct subgrad_param subpar;

	int relax;
	char *filename;
	char *subgrad_param_file;
	char *gnuplot_file;

	if (argc < 3) {
		fprintf(stderr, ">>>ERROR: ");
		fprintf(stderr, "Numero de parametros invalido!!\n");
		display_help();
		return 1;
	}

	relax = atoi(argv[1]);
	filename = argv[2];

	if (argv[3] == NULL) {
		subgrad_param_file = DEFAULT_SUBGRAD_PARAM_FILE;
	}
	else {
		subgrad_param_file = argv[3];
	}

	if ((relax != 1) && (relax != 2)) {
		fprintf(stderr, ">>>ERROR: ");
		fprintf(stderr, "Opcao para relaxacao invalida!!\n");
		display_help();
		return 1;
	}
	
	/* tempo de inicio */
	gettimeofday (&ini, NULL);

	/* Carregando a entrada na memoria */
	if (graph_parser(filename, &G) != 0) {
		fprintf(stderr, ">>>ERROR: ");
		fprintf(stderr, "Arquivo de entrada invalido!!\n");
		return 1;
	}

	if (DEBUG == 1) {
		print_graph(G);
	}

	/* Leitura dos parametros para o metodo do subgradiente */
	if (subgrad_parser(subgrad_param_file, &(subpar)) != 0) {
		fprintf(stderr, ">>>ERROR: ");
		fprintf(stderr, "Arquivo de parametros invalido!!\n");
		return 1;
	}

	if (DEBUG == 1) {
		print_subgrad_param(subpar);
	}

	gnuplot_file = (char *) malloc((strlen(GNUPLOT_DIR)
					+ strlen(basename(filename)) +
					+ strlen(basename(subgrad_param_file))
					+ strlen(GNUPLOT_EXT)
					+ 4) * sizeof(char));

	sprintf(gnuplot_file, "%s%s.%d.%s%s", GNUPLOT_DIR, basename(filename),
		relax, basename(subgrad_param_file), GNUPLOT_EXT);

	lag_heuristic(&subpar, &G, relax, gnuplot_file);  

	free(gnuplot_file);

	/* Liberando memoria usada pelo grafo */
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
