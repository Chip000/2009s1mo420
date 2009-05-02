/* 
 * Trabalho de MO420 - Programacao Linear Inteira
 * 2009s1 - Prof. Cid
 * Autor: Victor de Abreu Iizuka ra046874 
 */

#ifndef HAVE_MYTIME_H
#define HAVE_MYTIME_H

#include <sys/time.h>
#include <time.h>

/* 
 * timeval_subtract: Funcao auxiliar de contagem de tempo.
 */
int timeval_subtract (struct timeval *result, 
		      struct timeval *x, 
		      struct timeval *y);

#endif /* ! HAVE_MYTIME_H */
