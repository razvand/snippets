#!/bin/sed -f

{
:again
# Creole Syntax: http://www.wikicreole.org/wiki/Creole1.0
# Redmine Wiki Syntax: http://www.redmine.org/projects/redmine/wiki/RedmineTextFormatting

# HTTP URLs
s/\[\[[ \t]*\(https\?:\/\/[^\| \t]\+\)[ \t]*|[ \t]*\([^]]\+\)[ \t]*\]\]/"\2":\1/g
s/\[\[[ \t]*\([^\| \t]\+\)[ \t]*|[ \t]*\([^]]\+\)[ \t]*\]\]/[[\1|\2]]/g
# bold
s/\*\*\([^*\t ]\+\)\*\*/*\1*/g
# italic
s/\/\/\([^\/]\+\)\/\//_\1_/g
s/{{{\(.*\)}}}/@\1@/g
# headings
s/[ \t]*=====[ \t]*\([^=]\+\)=\+[ \t]*$/h5. \1/g
s/[ \t]*====[ \t]*\([^=]\+\)=\+[ \t]*$/h4. \1/g
s/[ \t]*===[ \t]*\([^=]\+\)=\+[ \t]*$/h3. \1/g
s/[ \t]*==[ \t]*\([^=]\+\)=\+[ \t]*$/h2. \1/g
s/[ \t]*=[ \t]*\([^=]\+\)=\+[ \t]*$/h1. \1/g

/^[ \t]*{{{[ \t]*$/,/^[ \t]*}}}/ {
/^[ \t]*{{{[ \t]*$/d
/^[ \t]*}}}/ {
	s/^[ \t]*}}}\(.*$\)/\1/
	/^[ \t]*$/d
	b again
}
s/\(^.*$\)/> \1/
}
}
