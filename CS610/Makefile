DOC=ppa

default:
	pdflatex $(DOC)
	bibtex $(DOC)
	bibtex $(DOC)
	pdflatex $(DOC)
	pdflatex $(DOC)
clean:
	rm *.aux *.bb. *.log *.blg $(DOC).pdf
