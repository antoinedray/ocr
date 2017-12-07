#!/bin/sh

set -e
# Any subsequent(*) commands which fail will cause the shell script to exit

GREEN='\033[0;32m'
NC='\033[0m' # No Color

if [ "$#" -eq 1 ]; then
    if [ $1 == "-gen" ]; then
        listFonts="Arial Georgia Verdana"
        listMaj="A B C D E F G H I J K L M N O P Q R S T U V W X Y Z"
        listMin="q w e r t y u i o p a s d f g h j k l z x c v b n m"
        listNum="0 1 2 3 4 5 6 7 8 9"
        for f in $listFonts
        do
            for c in $listMaj
            do
                convert -size 32x32     -gravity center  \
                        -font ${f}     -pointsize 32       label:${c} \
                        ${c}_maj_${f}.jpg
            done
            echo "[${GREEN}SUCCESS${NC}] Generating ${f} Uppercases"
            for c in $listMin
            do
                convert -size 32x32     -gravity center  \
                        -font ${f}     -pointsize 32       label:${c} \
                        ${c}_min_${f}.jpg
            done
            echo "[${GREEN}SUCCESS${NC}] Generating ${f} Lowercases"
            for c in $listNum
            do
                convert -size 32x32     -gravity center  \
                        -font ${f}     -pointsize 32       label:${c} \
                        ${c}_${f}.jpg
            done
            echo "[${GREEN}SUCCESS${NC}] Generating ${f} numbers"
        done
    elif [ $1 == "-clean" ]; then
        rm -f *.jpg
        echo "[${GREEN}SUCCESS${NC}] Deleting all images previously generated"
    elif [ $1 == "-h" ]; then
        echo "-gen : Generate the database"
        echo "-clean : Clean the database"
    fi
else
    echo "Invalid parameter, run './gen.sh -h'"
fi
