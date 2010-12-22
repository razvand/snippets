#!/bin/sed -f

{
s/\[\(https\?[^]]\+\)]/[[\1]]/g
s/^ \*/*/g
s/^  \*/*/g
s/^   \*/**/g
s/^    \*/**/g
s/^     \*/***/g
s/^      \*/***/g
s/||/|/g
s/<pre>/<code>/g
s/<\/pre>/<\/code>/g
s/<source[ \t]\+lang="\([a-z]\+\)">/<code \1>/g
s/<\/source>/<\/code>/g
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
s/\(\[\[https\?:[^ ]\+\) /\1|/g
}
