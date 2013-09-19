#!/bin/sh  

pdflatex Tesis.tex
bibtex Tesis.aux
pdflatex Tesis.tex
pdflatex Tesis.tex

rm *.aux *.log *.toc *.bbl *.blg *.lof
