#include <stdio.h>
#include <tokenizer.h>

int space_char(char c) {
  return c == '\t' || c == ' ';
}

int non_space_char(char c) {
  return c != '\0' || !space_char(c);
}

/* char *token_start(char *str){ */
/*   // TODO... */
/* } */

/* char **tokenize(char* str) { */
/* } */
