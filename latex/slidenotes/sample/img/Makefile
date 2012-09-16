#
# Access the wiki page below for information on processing Dia and Inkscape
# image files.
#
# https://systems.cs.pub.ro/projects/projects/templates/wiki/Images
#

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
