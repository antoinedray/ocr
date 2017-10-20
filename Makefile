# Simple OCR Makefile

CC= gcc

CPPFLAGS= `pkg-config --cflags gtk+-3.0` `pkg-config --cflags sdl` -MMD
# Add -Werror to treat warnings as errors 
CFLAGS= -Wall -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl` -lSDL_image

# Place in SRC all the files we whant to build separated by a space
SRC= pixel_operations.c ui.c main.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main
 
main: ${OBJ}

.PHONY: clean

clean:
	${RM} ${OBJ} # remove object files
	${RM} ${DEP} # remove dependency files
	${RM} main # remove main program

# include dependency files
-include ${DEP}
 
# END
