all :
	    # do nothing

# display (using the more utility) all of your source code (excluding the
# modified RAM)
view : 
	more *.py

# Does whatever you need to do to produce:
#   1. symbolic RAL code
#   2. linked RAL code
#   3. (optional) – You optimised RAL code
compile :
	python interpreterext.py -O

# Use cat to display your symbolic RAL program (produced in translate) to
# stdout.
view-trans : 
	cat trans.txt

# Use cat to display your compiled (not optimised) RAL program (produced in
# translate to stdout.
view-link : 
	cat ral.txt

# Use cat to display your compiled, optimised RAL program (produced in translate
# to stdout.
view-op :
	cat ral-op.txt

# invoke ~jjohnson/bin/ram to run your program. Let output go to stdout.
run :
	~jjohnson/bin/ram ral.txt mem.txt

# invoke ~jjohnson/bin/ram to run your optimised program.
run-op :
	~jjohnson/bin/ram ral-op.txt mem.txt

# remove all binaries and intermediate files
clean :
	rm -f *.pyc
	rm -f *.txt
	rm -f parser.out
	rm -f parsetab.py
