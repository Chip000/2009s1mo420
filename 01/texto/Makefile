GNUPLOT_DIR=./gnuplot
TARGET=ra046874

TEX=$(TARGET).tex
DVI=$(TARGET).dvi
PS=$(TARGET).ps
PDF=$(TARGET).pdf

.PHONY: all clean

$(DVI): $(TEX)
	latex $(TEX)
	bibtex $(TARGET)
	latex $(TEX)
	latex $(TEX)
	
$(PS): $(DVI)
	dvips -Pcmz -o -t letter $(TARGET).dvi

$(PDF): $(PS)
	ps2pdf $(PS)

pdf: $(PDF)

clean:
	rm -f $(EPS_DIR)/*.eps *~ $(PDF) $(PS) $(DVI) *.aux *.log *.loa *.bbl *.blg *.lof *.lot *.toc *.ps *.pdf .nfs*

