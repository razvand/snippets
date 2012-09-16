EPSTOPDF = epstopdf
DIA = dia

.PHONY: all clean

all: so.pdf

so.pdf: so.eps
	$(EPSTOPDF) $<

so.eps: so.dia
	$(DIA) -t eps-pango $<

clean:
	-rm -f so.eps so.pdf
