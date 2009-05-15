GNUPLOT_DIR=./gnuplot
TARGET=ra046874

TEX=$(TARGET).tex
DVI=$(TARGET).dvi
PS=$(TARGET).ps
PDF=$(TARGET).pdf

.PHONY: pdf clean

$(DVI): $(TEX)
	latex $(TEX)
#	bibtex $(TARGET)
	latex $(TEX)
	latex $(TEX)

$(PS): $(DVI)
	dvips -Pcmz -o -t letter $(TARGET).dvi

$(PDF): $(PS)
	ps2pdf $(PS)

pdf: clean $(PDF)

clean:
	rm -f *~ $(PDF) $(PS) $(DVI) 
	rm -f *.aux *.log *.loa *.bbl *.blg *.lof *.lot 
	rm -f *.toc *.ps .nfs* *.out

