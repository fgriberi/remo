#!/bin/bash

pdflatex thesisPresentation.tex
pdflatex thesisPresentation.tex

rm *.aux
rm *.log
rm *.nav
rm *.out
rm *.snm	
rm *.toc
rm *.vrb
rm *~ -r
