#!/bin/sed -f

{
s/\[\(http[^]]\+\)]/[[\1]]/g
s/<pre>/<code>/g
s/<\/pre>/<\/code>/g
s/<tt>/{{{/g
s/<\/tt>/}}}/g
s/<b>/**/g
s/<\/b>/**/g
s/<ul>//g
s/<\/ul>//g
s/[ \t]*<li>\(.*\)<\/li>/* \1/g
s/'''/**/g
s/''/\/\//g
s/{{{\[\[/[[/g
s/\]\]}}}/]]/g
s/\(\[\[http:[^ ]\+\) /\1|/g
# diacritics
# ș
s/\xc5\x9f/\xc8\x99/g
# ț
s/\xc5\xa3/\xc8\x9b/g
# Ș
s/\xc5\x9e/\xc8\x98/g
# Ț
s/\xc5\xa2/\xc8\x9a/g
# weird quotes
s/\xe2\x80\x9c/"/g
s/\xe2\x80\x9d/"/g
}
