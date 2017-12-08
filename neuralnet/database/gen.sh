#!/bin/sh

set -e
# Any subsequent(*) commands which fail will cause the shell script to exit

# CONFIG
GREEN='\033[0;32m'
NC='\033[0m' # No Color
FONTS='fonts/*' # Path to font folder
SIZE='32x32' # Size of the image
FORMAT='.jpg' # Image format

if [ "$#" -eq 1 ]; then

    if [ $1 == "-gen" ]; then

        listFonts="Arial Georgia Verdana"
        listMaj="A B C D E F G H I J K L M N O P Q R S T U V W X Y Z"
        listMin="q w e r t y u i o p a s d f g h j k l z x c v b n m"
        listNum="0 1 2 3 4 5 6 7 8 9"

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
            done
            echo "[${GREEN}SUCCESS${NC}] Generating ${ff} Uppercases"

            for c in $listMin
            do
                convert -size ${SIZE}     -gravity center  \
                        -font ${f}        -pointsize 25       label:${c} \
                        ${c}_min_${ff}${FORMAT}
            done
            echo "[${GREEN}SUCCESS${NC}] Generating ${ff} Lowercases"

            for c in $listNum
            do
                convert -size ${SIZE}     -gravity center  \
                        -font ${f}        -pointsize 25       label:${c} \
                        ${c}_num_${ff}${FORMAT}
            done
            echo "[${GREEN}SUCCESS${NC}] Generating ${ff} numbers"
        done

    elif [ $1 == "-clean" ]; then
        rm -f *${FORMAT}
        echo "[${GREEN}SUCCESS${NC}] Deleting all images previously generated"

    elif [ $1 == "-h" ]; then
        echo "\n=== HELP ==="
        echo "-gen : Generate the database"
        echo "-clean : Clean the database\n"
    fi

else
    echo "Invalid parameter, run './gen.sh -h'"
fi
