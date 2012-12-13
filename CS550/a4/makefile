all :
	    # do nothing

# display (using the more utility) all source code for part 1
view-part1 : 
	more part1/interpreterext.py
	more part1/programext.py

# target to build your parser
build :
	    # lol

# run your parser from part 1
run-part1 : 
	python part1/interpreterext.py

# display (using the more utility) your iterative length function in the mini
# language
view-func1 : 
	more part1/func1.mini

# display (using the more utility) your recursive length function in the mini
# language
view-func2 : 
	more part1/func2.mini

# display (using the more utility) all source code for part 2
view-part2 : 
	more part2/interpreterext.py
	more part2/programext.py
	more part2/memory.py
	more part2/environment.py

# run your parser from part 2
run-part2 : part2/interpreterext.py
	python part2/interpreterext.py

# cleans up all intermediate and resulting files
clean :
	rm -f *.pyc
	rm -f parser.out
	rm -f parsetab.py
	rm -f part1/*.pyc
	rm -f part1/parser.out
	rm -f part1/parsetab.py
	rm -f part2/*.pyc
	rm -f part2/parser.out
	rm -f part2/parsetab.py
