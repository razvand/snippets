EPSTOPDF = epstopdf
DIA = dia

all: so.pdf

so.pdf: so.eps
	$(EPSTOPDF) $<

so.eps: so.dia
	$(DIA) -t eps-pango $<
