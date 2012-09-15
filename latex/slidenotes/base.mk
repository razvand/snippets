HIGHLIGHT = tex/code
PDF = $(addsuffix .pdf, $(BASENAME))
TEX = $(addsuffix .tex, $(BASENAME))
PDFLATEX = pdflatex
STY_DIR = ../../../sty
OUT_DIR = texfiles
CODE_DIR = code

.PHONY: clean all $(PDF)

all: $(PDF)

$(PDF): $(TEX)
	# Rebuild source files, if any
	-test -d $(CODE_DIR) && make -C $(CODE_DIR)
	# Create out directory
	-test -d $(OUT_DIR) || mkdir $(OUT_DIR)
	# Twice, so TOC is also updated
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) $<
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) $<
	cp $(OUT_DIR)/$(PDF) .

clean:
	-rm -fr $(OUT_DIR)
	-test -d $(CODE_DIR) && make -C $(CODE_DIR) clean
