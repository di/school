.PHONY : test clean run

graph : ndfa.py
	./ndfa.py graph $(inFile)

sim : ndfa.py
	./ndfa.py sim $(inFile)

clean :
	-\rm *.out
