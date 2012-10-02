DOCS=\
	overview\
	plan\
	requirements\
	acceptance\
	peer-review\
	presentation\
	final_presentation\
	design\
	integration\

.PHONY: all clean distclean website

all: $(addsuffix .pdf, $(DOCS))

clean: $(addsuffix .clean, $(DOCS))

distclean: $(addsuffix .distclean, $(DOCS))

%.pdf:
	$(MAKE) -C $*

%.html:
	$(MAKE) -C $* html

%.clean:
	$(MAKE) -C $* clean

%.distclean:
	$(MAKE) -C $* distclean
