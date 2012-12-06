JAVAC=javac
JAR=jar
JDEBUGFLAGS=-O

############################################################

# Automatically "scrape" the version from the VERSION member variable in Othello.java:
DISTVERSION=$(shell cat src/edu/drexel/cs/ai/othello/Othello.java | grep "VERSION.*=" | sed -e 's/.*"\(.*\)".*/\1/')
DISTNAME=CS380othello-$(DISTVERSION)
RAWDIRS=edu/drexel/cs/ai/othello
DIRS=$(foreach dir,$(RAWDIRS),$(dir))
STUDENTS=$(subst CVS,,$(subst src/students/,,$(wildcard src/students/*)))
STUDENT_FILES=$(foreach student,$(STUDENTS),$(wildcard src/students/$(student)/*.java))
JAVA_FILES=$(foreach dir,$(DIRS),$(wildcard src/$(dir)/*.java))
PACKAGES=$(subst /,.,$(DIRS)) $(subst /,.,$(foreach student,$(STUDENTS),students/$(student)))
JARS=lib/othello.jar $(foreach student,$(STUDENTS),lib/$(student).jar)

.PHONY : all
all : othello javadoc $(JARS)

othello : $(JARS)
	@echo 'for i in lib/*.jar' > $@
	@echo 'do' >> $@
	@echo '  CP="$${i}:$${CP}"' >> $@
	@echo 'done' >> $@
	@echo 'CLASSPATH=$${CP} java edu.drexel.cs.ai.othello.Othello $$@' >> $@
	@chmod 755 $@

.PHONY : build-othello
build-othello : $(JAVA_FILES) classes
	$(JAVAC) $(JDEBUGFLAGS) -d classes/ $(JAVA_FILES)

classes/%.class : src/%.java classes
	$(JAVAC) $(JDEBUGFLAGS) -d classes -classpath classes $<

classes :
	mkdir -p $@

lib : 
	mkdir -p $@

lib/othello.jar : lib build-othello
	@echo "Manifest-Version: 1.0" > .manifest.tmp
	@echo "Main-Class: edu.drexel.cs.ai.othello.Othello" >> .manifest.tmp
	$(JAR) cmf .manifest.tmp lib/othello.jar -C classes edu
	@rm -rf .manifest.tmp

lib/%.jar : lib $(wildcard src/students/%/*.java)
	$(JAVAC) $(JDEBUGFLAGS) -classpath lib/othello.jar -d classes/ $(wildcard src/students/$*/*.java)
	@echo "Manifest-Version: 1.0" > .manifest.tmp
	@echo "Main-Class: edu.drexel.cs.ai.othello.Othello" >> .manifest.tmp
	$(JAR) cmf .manifest.tmp $@ -C classes students/$*
	@rm -rf .manifest.tmp

.PHONY : clean
clean :
	rm -rf othello
	rm -rf lib
	rm -rf classes

doc :
	mkdir -p $@

# JAVADOC:

WINDOWTITLE = 'Othello $(DISTVERSION) API Specification'
DOCTITLE = $(WINDOWTITLE)
HEADER = '<b>Othello $(DISTVERSION)</b>'
BOTTOM = 'Copyright 2006&ndash;2007 <a href="http://www.sultanik.com/">Evan A. Sultanik</a></font>'
SRCDIR = 'src/'

.PHONY : javadoc
javadoc : doc
	javadoc -d ./doc/ -use -splitIndex -author -windowtitle $(WINDOWTITLE) -doctitle $(DOCTITLE) -header $(HEADER) -bottom $(BOTTOM) -sourcepath $(SRCDIR) -protected -breakiterator $(PACKAGES)

.PHONY: dist
dist : $(DISTNAME).tar.gz

$(DISTNAME).tar : all
	@rm -rf $(DISTNAME)
	@mkdir $(DISTNAME)
	@find src/ -name "*.java" -exec cp --parents \{\} $(DISTNAME)/ \;
	@find src/ -name "Makefile" -exec cp --parents \{\} $(DISTNAME)/ \;
	@cp -r doc $(DISTNAME)/
	@cp othello $(DISTNAME)/
	@cp AUTHORS COPYING INSTALL NEWS README ChangeLog Makefile $(DISTNAME)/
	@cp -r lib $(DISTNAME)/
	tar cvf $(DISTNAME).tar $(DISTNAME)
	@rm -rf $(DISTNAME)

$(DISTNAME).tar.gz : $(DISTNAME).tar
	gzip -f $(DISTNAME).tar
