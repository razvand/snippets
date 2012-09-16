# folders required throughout rules
HIGHLIGHT_DIR = tex/code
STY_DIR = ../../../sty
OUT_DIR = texfiles
CODE_DIR = code
FORMAT_DIR = format

PDFLATEX = pdflatex


# BASENAME is defined in top-level Makefile including this file.
TEX = $(addsuffix .tex, $(BASENAME))

#
# PDF output files
# * standard slides with overlays (private use)
# * notes only (no data from slides) (private use)
# * handout slides with no overlays for printing and distributing
# * four slides on one A4 page (handout) with `Notes' area on the right
# * eight slides on one A4 page (handout) (two four-slide columns)
# * wide slides for dual screen use: slides + notes (private use)
#
SLIDES = $(addsuffix .pdf, $(BASENAME))
NOTES = $(addsuffix -notes.pdf, $(BASENAME))
HANDOUT = $(addsuffix -handout.pdf, $(BASENAME))
HANDOUT_4ON1 = $(addsuffix -handout-4on1-notes.pdf, $(BASENAME))
HANDOUT_8ON1 = $(addsuffix -handout-8on1.pdf, $(BASENAME))
DUALSCREEN = $(addsuffix -dualscreen.pdf, $(BASENAME))


.PHONY: main all clean
.PHONY: slides notes handout handout-4on1-notes handout-8on1 dualscreen
.PHONY: 4on1 8on1

# If run `make' with no arguments, only generate slides.
main: slides

# Handouts are public formats.
# Slides, dual screen slides and notes are private.
all: slides notes handout handout-4on1-notes handout-8on1 dualscreen
public: handout handout-4on1-notes handout-8on1

# Phony targets depend on PDF output files.
slides: $(SLIDES)
notes: $(NOTES)
handout: $(HANDOUT)
handout-4on1-notes: $(HANDOUT_4ON1)
handout-8on1: $(HANDOUT_8ON1)
dualscreen: $(DUALSCREEN)

# "aliases" for easy options to `make'
4on1: handout-4on1-notes
8on1: handout-8on1


$(NOTES) $(HANDOUT) $(HANDOUT_4ON1) $(HANDOUT_8ON1) $(DUALSCREEN): $(BASENAME)-%.pdf: $(FORMAT_DIR)/%.tex
	# Rebuild source files, if any
	-test -d $(CODE_DIR) && make -C $(CODE_DIR)
	# Create out directory
	-test -d $(OUT_DIR) || mkdir $(OUT_DIR)
	# Twice, so TOC is also updated
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) -jobname $(basename $@) $<
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) -jobname $(basename $@) $<
	ln $(OUT_DIR)/$@ .

$(SLIDES): $(TEX)
	# Rebuild source files, if any
	-test -d $(CODE_DIR) && make -C $(CODE_DIR)
	# Create out directory
	-test -d $(OUT_DIR) || mkdir $(OUT_DIR)
	# Twice, so TOC is also updated
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) -jobname $(basename $@) $<
	TEXINPUTS=$(STY_DIR)//: $(PDFLATEX) -output-directory $(OUT_DIR) -jobname $(basename $@) $<
	ln $(OUT_DIR)/$@ .


clean:
	-rm -fr $(OUT_DIR)
	-test -d $(CODE_DIR) && make -C $(CODE_DIR) clean
