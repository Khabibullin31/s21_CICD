#include "s21_cat.h"

int main(int argc, char **argv) {
  struct flags flag;
  EmptyCatStruct(&flag);
  if (argc > 0) {
    if (get_arg(argv, &flag)) {
      open_files(flag);
    }
  }
  return 0;
}

void EmptyCatStruct(struct flags *flag) {
  flag->file = 0;
  flag->b = 0;
  flag->checkB = 0;
  flag->e = 0;
  flag->n = 0;
  flag->s = 0;
  flag->checkS = 0;
  flag->t = 0;
  flag->v = 0;
  flag->checkENTER = 0;
}

int get_arg(char **argv, struct flags *flag) {
  int error = 1;
  int j = 0;

  for (int i = 1; argv[i]; i++) {
    if (argv[i][0] == '-' && argv[i][1] == '-') {
      flag_GNU(argv, flag, i);
    } else if (argv[i][0] == '-' && argv[i][1] != '-') {
      for (int t = 1; argv[i][t]; t++) {
        if (argv[i][t] == 'b') {
          flag->b = 1;
        } else if (argv[i][t] == 'e') {
          flag->e = 1;
          flag->v = 1;
        } else if (argv[i][t] == 'n') {
          flag->n = 1;
        } else if (argv[i][t] == 's') {
          flag->s = 1;
        } else if (argv[i][t] == 't') {
          flag->t = 1;
          flag->v = 1;
        } else if (argv[i][t] == 'v') {
          flag->v = 1;
        } else if (argv[i][t] == 'E') {
          flag->e = 1;
        } else if (argv[i][t] == 'T') {
          flag->t = 1;
        } else {
          printf("s21_cat: invalid option -- '%c'\n", argv[i][t]);
          error = 0;
        }
      }
    } else {
      flag->file = 1;
      fName[j] = argv[i];
      j++;
    }
  }

  if (flag->b == 1) {
    flag->n = 0;
  }

  return error;
}

void flag_GNU(char **argv, struct flags *flag, int i) {
  if (strcmp("--number-nonblank", argv[i]) == 0) {
    flag->b = 1;
  } else if (strcmp("--number", argv[i]) == 0) {
    flag->n = 1;
  } else if (strcmp("--squeeze-blank", argv[i]) == 0) {
    flag->s = 1;
  }
}

void input_r(FILE *file, struct flags *flag) {
  char ch;
  while (fscanf(file, "%c", &ch) != EOF) {
    print(ch, flag);
  }
}

void open_files(struct flags flag) {
  for (int i = 0; fName[i]; i++) {
    FILE *file;
    file = fopen(fName[i], "r");
    if (file) {
      input_r(file, &flag);
      fclose(file);
    } else {
      printf("s21_cat: %s: No such file or directory\n", fName[i]);
    }
  }
}

void print(char ch, struct flags *flag) {
  int null_str = 0;
  if (flag->s == 1 && flag->checkS == 0 && ch == '\n') {
    flag->checkS += 1;
  } else if (flag->checkS != 0 && ch == '\n') {
    flag->checkS += 1;
    null_str = 1;
  } else if (flag->checkS > 1 && ch != '\n') {
    flag->checkS = 0;
    if (flag->e == 1) {
      printf("$");
    }
    printf("\n");
    if (flag->n != 0) {
      printf("%6d\t", flag->n);
      flag->n += 1;
    }
  } else {
    flag->checkS = 0;
  }

  if (flag->n != 0 || flag->b != 0) {
    if (flag->checkENTER == 1) {
      printf("%6d\t", flag->n);
      flag->n += 1;
      flag->checkENTER = 0;
    }
    if (flag->n == 1) {
      printf("%6d\t", flag->n);
      flag->n += 1;
    }
    if (flag->b == 1) {
      printf("%6d\t", flag->b);
      flag->b += 1;
    }
    if (ch == '\n' && flag->n != 0 && null_str == 0) {
      flag->checkENTER = 1;
    }
    if (ch == '\n' && flag->b != 0) {
      flag->checkB += 1;
    }
    if (ch != '\n' && flag->checkB != 0 && flag->checkS == 0) {
      printf("%6d\t", flag->b);
      flag->checkB = 0;
      flag->b += 1;
    }
  }
  if (flag->e == 1 && ch == '\n' && null_str == 0) {
    printf("$");
  }
  if (flag->v == 1) {
    if (ch < 32 && ch != 9 && ch != 10) {
      printf("^");
      ch += 64;
    }
    if (ch == 127) {
      printf("^");
      ch = '?';
    }
  }
  if (flag->t == 1 && ch == '\t') {
    printf("^");
    ch = 'I';
  }

  if (null_str == 0) {
    printf("%c", ch);
  }
}
