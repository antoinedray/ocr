# EPITA OCR Programming S3 - 2016/2017
# Makefile
# 404 Team
 
# Compilers and options
CC=gcc
CPPFLAGS=
CFLAGS= -Wall -Wextra -std=c99
LDFLAGS=
LDLIBS=
 
SRC = math_func.c main.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
 
all: main
 
main: ${OBJ}
 
-include ${DEP}
 
clean:
	rm -f ${OBJ} ${DEP}
	rm -f main
 
# END