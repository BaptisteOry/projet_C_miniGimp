projet_C_miniGimp

-------------------------------------------------------------------------------------

OPERATION AND COMMAND LINE :

to execute : bin/minigimp
usage : bin/minigimp image_input.ppm [-h] [-histo] [<code_effect>[_<param1>]*]* [-o image_output.ppm]

[-h] = histogram : create a histogram for the input image and the output image
[-histo] = history : create or update the output image history

-------------------------------------------------------------------------------------

EFFECTS  :

Luts :
<code_effect> / description / <param>
ADDLUM / add luminosity / YES
DIMLUM / decrease luminosity / YES
ADDCON / add contrast / YES
DIMCON / decrease contrast / YES
INVERT / invert colors / NO

Changes :
<code_effect> / description / <param>
SEPIA / sepia / YES
BLACKANDWHITE / black and white / NO
BLUR / blur / NO
REINEDGES / reinforce the edges / NO
DETECTEDGES / detect the edges / NO
BUMP / bump / NO
HIGHPASS / highpass / NO
LOWPASS / lowpass / NO

-------------------------------------------------------------------------------------

EXAMPLES OF TESTED COMMAND LINES :

bin/minigimp images/squirrel.ppm -histo ADDLUM 50 INVERT -o images/squirrel_output.ppm
bin/minigimp images/squirrel.ppm -h -histo BLUR -o images/squirrel_output.ppm
bin/minigimp images/squirrel.ppm SEPIA 20
