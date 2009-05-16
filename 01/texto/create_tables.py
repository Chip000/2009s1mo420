#!/usr/bin/python
# -*- coding: iso-8859-1 -*-

# argv 1 - out file; 2 - in dir; 
import re
import os
import sys

r0 = re.compile(".*:(.*)-.*:(.*)")
r1 = re.compile(".*:(.*)")
saida = open(sys.argv[1], "w")

saida.write(r"\begin{table}[htb]")
saida.write("\n")
saida.write(r"\centering")
saida.write("\n")
saida.write(r"\sffamily")
saida.write("\n")
saida.write(r"  \begin{tabular}{c|c|c|c|c}")
saida.write("\n")
saida.write(r"  \thead{Instância} & \thead{lim. superior} & \thead{tempo lim.sup.} & \thead{lim.inferior} & \thead{tempo lim.inf.} \\")
saida.write("\n")
saida.write(r"  \hline{}")
saida.write("\n")

dir = os.listdir(sys.argv[2])
dir.sort()

for arq in dir:

	l = []

	if ".out" in arq:
		f = open(sys.argv[2]+arq, "r")
		goodlines = False

		for i in f:
			if ("Numero de iteracoes" in i):
				goodlines = True
			else:
				if (goodlines == True):
					goodlines = True
				else:
					continue
				
			if r0.match(i):
				l0 = r0.findall(i)
				l.append(l0[0])
			else:
				if r1.match(i):
					l1 = r1.findall(i)
					l.append(l1[0])
		
		print "O"
		print l
		print arq.split(".")

		saida.write("\t%s & $%s$ & %s & $%s$ & %s\\\\\n" % (arq.split('.')[0], l[1][1], l[1][0], l[2][1], l[2][0]))
		f.close()
	else:
		print "n"

saida.write(r"  \end{tabular}")
saida.write("\n")
saida.write(r"  \caption{Valores dos limitantes superior e inferior usando o arquivo ###AQUI###}")
saida.write("\n")
saida.write(r"  \label{tab:dados_lim_###AQUI2###}")
saida.write("\n")
saida.write(r"  \normalfont")
saida.write("\n")
saida.write(r"\end{table}")
saida.write("\n")

saida.write(r"\begin{table}[htb]")
saida.write("\n")
saida.write(r"\centering")
saida.write("\n")
saida.write(r"\sffamily")
saida.write("\n")
saida.write(r"  \begin{tabular}{c|c|c|c|c}")
saida.write("\n")
saida.write(r"  \thead{Instância} & \thead{distância} & \thead{custo} & \thead{tempo total} & \thead{Num. iterações} \\")
saida.write("\n")
saida.write(r"  \hline{}")
saida.write("\n")

for arq in dir:

	l = []

	if ".out" in arq:
		f = open(sys.argv[2]+arq, "r")
		goodlines = False

		for i in f:
			if ("Numero de iteracoes" in i):
				goodlines = True
			else:
				if (goodlines == True):
					goodlines = True
				else:
					continue
				
			if r0.match(i):
				l0 = r0.findall(i)
				l.append(l0[0])
			else:
				if r1.match(i):
					l1 = r1.findall(i)
					l.append(l1[0])
		
		print "O"
		print l
		print arq.split(".")

		saida.write("\t%s & $%s$ & $%s$ & %s & $%s$\\\\\n" % (arq.split('.')[0], l[3], l[4], l[6], l[0]))
		f.close()
	else:
		print "n"

saida.write(r"  \end{tabular}")
saida.write("\n")
saida.write(r"  \caption{Melhor solução encontrada usando o arquivo ###AQUI###}")
saida.write("\n")
saida.write(r"  \label{tab:dados_sol_###AQUI2###}")
saida.write("\n")
saida.write(r"  \normalfont")
saida.write("\n")
saida.write(r"\end{table}")
saida.write("\n")

saida.close()
