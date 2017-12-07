CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS =
LDLIBS = -lm

SRC = main.c neural.c loaderNN.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: main

main: ${OBJ}

.PHONY: clean

clean:
		${RM} ${OBJ}
		${RM} ${DEP}
		${RM} main

-include ${DEP}
