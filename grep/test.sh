#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
echo "" > log.txt

for var in -v -c -l -n -h -o
do
  for var2 in -v -c -l -n -h -o
  do
      for var3 in -v -c -l -n -h -o
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          TEST1="for s21_grep.c s21_grep.h Makefile $var"
          echo "$TEST1"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
              echo "SUCCESS: $COUNTER_SUCCESS"
              echo "FAIL: $COUNTER_FAIL"
              exit 1
          fi
          rm s21_grep.txt grep.txt

          TEST2="for s21_grep.c $var"
          echo "$TEST2"
          ./s21_grep $TEST2 > s21_grep.txt
          grep $TEST2 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST2" >> log.txt
              (( COUNTER_FAIL++ ))
              echo "SUCCESS: $COUNTER_SUCCESS"
              echo "FAIL: $COUNTER_FAIL"
              exit 2
          fi
          rm s21_grep.txt grep.txt

          TEST3="-e for -e ^int s21_grep.c s21_grep.h Makefile $var"
          echo "$TEST3"
          ./s21_grep $TEST3 > s21_grep.txt
          grep $TEST3 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST3" >> log.txt
              (( COUNTER_FAIL++ ))
              echo "SUCCESS: $COUNTER_SUCCESS"
              echo "FAIL: $COUNTER_FAIL"
              exit 3
          fi
          rm s21_grep.txt grep.txt

          TEST4="-e for -e ^int s21_grep.c $var"
          echo "$TEST4"
          ./s21_grep $TEST4 > s21_grep.txt
          grep $TEST4 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              (( COUNTER_SUCCESS++ ))
            else
              echo "$TEST4" >> log.txt
              (( COUNTER_FAIL++ ))
              echo "SUCCESS: $COUNTER_SUCCESS"
              echo "FAIL: $COUNTER_FAIL"
              exit 4
          fi
          rm s21_grep.txt grep.txt

      #   TEST5="-e regex -e ^print s21_grep.c $var $var2 $var3 -f pattern.txt"
      #   echo "$TEST5"
      #   ./s21_grep $TEST5 > s21_grep.txt
      #   grep $TEST5 > grep.txt
      #  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
      #  if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
      #    then
      #      (( COUNTER_SUCCESS++ ))
      #    else {
      #      echo "$TEST5" >> log.txt
      #      (( COUNTER_FAIL++ ))
      #      echo "SUCCESS: $COUNTER_SUCCESS"
      #      echo "FAIL: $COUNTER_FAIL"
      #      exit 5
      #   }
      # fi
      # rm s21_grep.txt grep.txt

        fi
      done
  done
done
echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"