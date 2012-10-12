pdflatex remo.tex
bibtex remo.aux 
pdflatex remo.tex
pdflatex remo.tex

rm *.aux *.bbl *.blg *.log *.lpr *~ 
