# Simple OCR Makefile

CC= gcc #-fsanitize=address

CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -std=c99 -O0 -g
LDFLAGS=
LDLIBS= -lm

SRC= neural.c main_pres.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: main_pres
main_pres: ${OBJ}

.PHONY: clean

clean:
	rm -f ${OBJ} ${DEP} main_pres neural.h.gch

#-include ${DEP}
# include dependency files
#-include ${DEP}
 
# END
