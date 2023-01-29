#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_BUFFER 100000
#define MY_REG 10000
#define MAX_ERR_LENGTH 500

struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int empty_line;
};

void grep_flags(int argc, char *argv[], struct flags *flag, char *ef_arg);
void add_e_arg(char *optarg, int *e_count, char *ef_arg, struct flags *);
void add_f_arg(char *optarg, int *e_count, char *ef_arg, struct flags *);

void open_files(int argc, char *argv[], char *ef_arg, struct flags flag);
void reg_compile(char *argv[], char *my_reg, FILE *fp, struct flags flag,
                 int files_count);

#endif  // SRC_GREP_S21_GREP_H_
