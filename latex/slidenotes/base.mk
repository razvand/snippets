HIGHLIGHT = tex/code
PDFLATEX = pdflatex
STY_DIR = ../../../sty
OUT_DIR = texfiles
CODE_DIR = code

TEX = $(addsuffix .tex, $(BASENAME))
SLIDES = $(addsuffix .pdf, $(BASENAME))
NOTES = $(addsuffix -notes.pdf, $(BASENAME))
HANDOUT = $(addsuffix -handout.pdf, $(BASENAME))
HANDOUT_4ON1 = $(addsuffix -handout-4on1-notes.pdf, $(BASENAME))
HANDOUT_8ON1 = $(addsuffix -handout-8on1.pdf, $(BASENAME))
DUALSCREEN = $(addsuffix -dualscreen.pdf, $(BASENAME))

NOTES_OPTIONS = "\PassOptionsToClass{notes=only}{beamer} \input{$(BASENAME)}"
HANDOUT_OPTIONS = "\PassOptionsToClass{handout}{beamer} \input{$(BASENAME)}"
HANDOUT_4ON1_OPTIONS = "\def\fouronone{1} \PassOptionsToClass{handout}{beamer} \input{$(BASENAME)}"
HANDOUT_8ON1_OPTIONS = "\def\eightonone{1} \PassOptionsToClass{handout}{beamer} \input{$(BASENAME)}"
DUALSCREEN_OPTIONS = "\def\dualscreen{1} \input{$(BASENAME)}"

.PHONY: clean all

main: $(SLIDES)

all: $(SLIDES) $(NOTES) $(HANDOUT) \
       $(HANDOUT_4ON1) $(HANDOUT_8ON1)$(DUALSCREEN)

slides: $(SLIDES)
notes: $(NOTES)
handout: $(HANDOUT)
4on1: $(HANDOUT_4ON1)
8on1: $(HANDOUT_8ON1)
dualscreen: $(DUALSCREEN)

$(SLIDES): $(TEX)
	# Rebuild source files, if any
	-test -d $(CODE_DIR) && make -C $(CODE_DIR)
	# Create out directory
	-test -d $(OUT_DIR) || mkdir $(OUT_DIR)
	# Twice, so TOC is also updated
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) $<
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) $<
	cp $(OUT_DIR)/$@ .

$(NOTES): $(TEX)
	# Rebuild source files, if any
	-test -d $(CODE_DIR) && make -C $(CODE_DIR)
	# Create out directory
	-test -d $(OUT_DIR) || mkdir $(OUT_DIR)
	# Twice, so TOC is also updated
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) -jobname $@ $(NOTES_OPTIONS)
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) -jobname $@ $(NOTES_OPTIONS)
	cp $(OUT_DIR)/$@ .

$(HANDOUT): $(TEX)
	# Rebuild source files, if any
	-test -d $(CODE_DIR) && make -C $(CODE_DIR)
	# Create out directory
	-test -d $(OUT_DIR) || mkdir $(OUT_DIR)
	# Twice, so TOC is also updated
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) -jobname $@ $(HANDOUT_OPTIONS)
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) -jobname $@ $(HANDOUT_OPTIONS)
	cp $(OUT_DIR)/$@ .

$(HANDOUT_4ON1): $(TEX)
	# Rebuild source files, if any
	-test -d $(CODE_DIR) && make -C $(CODE_DIR)
	# Create out directory
	-test -d $(OUT_DIR) || mkdir $(OUT_DIR)
	# Twice, so TOC is also updated
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) -jobname $@ $(HANDOUT_4ON1_OPTIONS)
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) -jobname $@ $(HANDOUT_4ON1_OPTIONS)
	cp $(OUT_DIR)/$@ .

$(HANDOUT_8ON1): $(TEX)
	# Rebuild source files, if any
	-test -d $(CODE_DIR) && make -C $(CODE_DIR)
	# Create out directory
	-test -d $(OUT_DIR) || mkdir $(OUT_DIR)
	# Twice, so TOC is also updated
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) -jobname $@ $(HANDOUT_8ON1_OPTIONS)
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) -jobname $@ $(HANDOUT_8ON1_OPTIONS)
	cp $(OUT_DIR)/$@ .

$(DUALSCREEN): $(TEX)
	# Rebuild source files, if any
	-test -d $(CODE_DIR) && make -C $(CODE_DIR)
	# Create out directory
	-test -d $(OUT_DIR) || mkdir $(OUT_DIR)
	# Twice, so TOC is also updated
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) -jobname $@ $(DUALSCREEN_OPTIONS)
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) -jobname $@ $(DUALSCREEN_OPTIONS)
	cp $(OUT_DIR)/$@ .

clean:
	-rm -fr $(OUT_DIR)
	-test -d $(CODE_DIR) && make -C $(CODE_DIR) clean
