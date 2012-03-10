#!/bin/sed -f

s/INSERT INTO[ \t]\+"\([^"]\+\)"/INSERT INTO `\1`/g
#s/CREATE TABLE[ \t]\+"\([^"]\+\)"/INSERT INTO `\1`/g
#s/CREATE INDEX[ \t]\+"\([^"]\+\)"/INSERT INTO `\1`/g
/CREATE TABLE/s/"/`/g
/CREATE INDEX/s/"/`/g
/CREATE UNIQUE INDEX/s/"/`/g
s/AUTOINCREMENT/AUTO_INCREMENT/g
s/'t'/'1'/g
s/'f'/'0'/g
