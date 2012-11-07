pdflatex ArquitectureResponsibilities.tex
bibtex ArquitectureResponsibilities.aux 
pdflatex ArquitectureResponsibilities.tex
pdflatex ArquitectureResponsibilities.tex

pdflatex docArquitecture.tex
bibtex docArquitecture.aux 
pdflatex docArquitecture.tex
pdflatex docArquitecture.tex

pdflatex diagrams.tex
bibtex diagrams.aux 
pdflatex diagrams.tex
pdflatex diagrams.tex

rm *.aux *.bbl *.blg *.log
