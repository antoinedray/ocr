# Simple OCR Makefile

CC= gcc

CPPFLAGS= `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Werror -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl` -lSDL_image

# Place in SRC all the files we want to build separated by a space
SRC= mysdl/mysdl.c preproc/preproc.c segmentation/segmentation.c ui/ui.c main.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} # remove object files
	${RM} ${DEP} # remove dependency files
	${RM} main # remove main program

.PHONY: clean all main

# include dependency files
-include ${DEP}

# END
