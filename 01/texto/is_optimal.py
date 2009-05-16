#!/usr/bin/python
# -*- coding: iso-8859-1 -*-

# argv 1 - out file; 2 - in dir; 
import re
import os
import sys

r0 = re.compile(".*:(.*)-.*:(.*)")
r1 = re.compile(".*:(.*)")

dir = os.listdir(sys.argv[1])
dir.sort()

for arq in dir:

	l = []

	if ".out" in arq:
		f = open(sys.argv[1]+arq, "r")

		for i in f:
			if ("Solucao otima" in i):
				print arq
		f.close() 
