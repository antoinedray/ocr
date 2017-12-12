#!/bin/sh

set -e
# Any subsequent(*) commands which fail will cause the shell script to exit

# CONFIG
GREEN='\033[0;32m'
NC='\033[0m' # No Color
FONTS='fonts/*' # Path to font folder
SIZE='16x16' # Size of the image
FORMAT='.jpg' # Image format
DATAFILE='data.txt'

touch $DATAFILE

listMaj="A B C D E F G H I J K L M N O P Q R S T U V W X Y Z"
listMin="a b c d e f g h i j k l m n o p q r s t u v w x y z"
listNum="0 1 2 3 4 5 6 7 8 9"
listChars=", . ! ?"


for f in $FONTS
do
    # We extract from the ttf file the name of the font
    ff=${f%.*} # Remove extension
    ff=${ff##*/} # Remove path to extension

    for c in $listMaj
    do
        convert -size ${SIZE}     -gravity center  \
                -font ${f}        -pointsize 25       label:${c} \
                ${c}_maj_${ff}${FORMAT}
        echo "${c}_maj_${ff}${FORMAT}" >> $DATAFILE
    done
    echo "[${GREEN}SUCCESS${NC}] Generating ${ff} Uppercases"

    for c in $listMin
    do
        convert -size ${SIZE}     -gravity center  \
                -font ${f}        -pointsize 25       label:${c} \
                ${c}_min_${ff}${FORMAT}
        echo "${c}_min_${ff}${FORMAT}" >> $DATAFILE
    done
    echo "[${GREEN}SUCCESS${NC}] Generating ${ff} Lowercases"

    for c in $listNum
    do
        convert -size ${SIZE}     -gravity center  \
                -font ${f}        -pointsize 25       label:${c} \
                ${c}_num_${ff}${FORMAT}
        echo "${c}_num_${ff}${FORMAT}" >> $DATAFILE
    done
    echo "[${GREEN}SUCCESS${NC}] Generating ${ff} Numbers"
    i=0
    for c in $listChars
    do
        convert -size ${SIZE}     -gravity center  \
                -font ${f}        -pointsize 25       label:${c} \
                ${i}_char_${ff}${FORMAT}
        echo "${i}_char_${ff}${FORMAT}" >> $DATAFILE
        i=$(expr $i + 1)
    done
    echo "[${GREEN}SUCCESS${NC}] Generating ${ff} Special characters"
done
