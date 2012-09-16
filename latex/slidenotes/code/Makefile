TEXFILES = cli-example.tex

ifeq (3, $(shell highlight --version | head -2 | tail -1 | rev | cut -d ' ' -f 1 | rev | cut -d '.' -f 1))
	HIGHLIGHT_OPTS = -O latex -l -f -t 8 -K tiny -S bash -c highlight.sty
else
	HIGHLIGHT_OPTS = -L -l -f -t 8 -K tiny -S bash -c highlight.sty
endif

all: $(TEXFILES)

cli-example.tex: cli-example.bash
	highlight $(HIGHLIGHT_OPTS) -i $< -o $@

.PHONY: clean
clean:
	rm -f $(TEXFILES) highlight.sty highlight.css *~
