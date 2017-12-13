set -e

START=7
END=10
PREV=6

while [ $START <= $END ]
  $PREV=$(expr $START - 1)
  touch "database_NN/OCR_NN_${START}"
  perl -p -i -e "s/database_NN/OCR_NN_${PREV}/database_NN_${START}/g" trainning.c
  make && ./training
end
