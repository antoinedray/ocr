set -e

START=10
END=20

while (( "$START" <= "$END" ))
do
  PREV=$(expr $START - 1)
  touch "database_NN/OCR_NN_${START}"
  perl -p -i -e "s/database_NN\/OCR_NN_${PREV}/database_NN\/OCR_NN_${START}/g" trainning.c
  make && ./trainning
  START=$(expr $START + 1)
done
