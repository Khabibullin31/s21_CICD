#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 2048
char *fName[SIZE];
struct flags {
  int file;
  int b;
  int checkB;
  int e;
  int n;
  int s;
  int checkS;
  int t;
  int v;
  int checkENTER;
};

void open_files(struct flags flag);
void EmptyCatStruct(struct flags *flag);
int get_arg(char **input, struct flags *flag);
void input_r(FILE *file, struct flags *flag);
void flag_GNU(char **input, struct flags *flag, int i);
void print(char ch, struct flags *flag);

#endif  // SRC_CAT_S21_CAT_H_
