CPPFLAGS = -MMD
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS =
LDLIBS = -lm

SRC = trainning.c neural.c loaderNN.c data_base.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: trainning

trainning: ${OBJ}

.PHONY: clean

clean:
		${RM} ${OBJ}
		${RM} ${DEP}
		${RM} trainning

-include ${DEP}
