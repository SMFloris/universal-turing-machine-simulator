UTMS - Universal Turing Machine Simulator

Written in C/C++ with Qt4 for the Calculability and Complexity course.

Takes an encoded UTM and runs it, it can have multiple input/output bands.

It has the following encoding:

-----------------------------

For alphabet:

O = 1

1 = 11

-----------------------------

For states:

q0 = 1

q1 = 11

...(and so on)

-----------------------------

For band direction:
L = 1
R = 11

S(top) = 111

-----------------------------
It ties together as following:

Between 000 ... 000 lies the UTM.

Transformations between states are separated by 00

Transformations are encoded as such(remove blanks):

STATE1 0 LETTER1 0 BAND_DIRECTION 0 LETTER2 0 STATE2

it behaves like this: if the current state = STATE1 and the current letter on the band is LETTER1 then REPLACE LETTER1 with LETTER2 advance band in BAND_DIRECTION and GO TO STATE2.


Notes:

UTMs are described by files with the ".utm" file format. They are just comprised of 0s and 1s CHARACTERS for readability purposes.

Input bands are just text files (\*.txt) comprised of the {0,1}\* language, that start with a blank (space).

Both *.utm and *.txt files should be in the same directory as the executable.
