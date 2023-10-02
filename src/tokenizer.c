#include "tokenizer.h"

#include <stdio.h>
#include <stdlib.h>

int space_char(char c) { return c != '\0' && (c == '\t' || c == ' '); }

int non_space_char(char c) { return c != '\0' && !space_char(c); }

char *token_start(char *str) {
  // skip characters until you reach a space
  char *sc = str;
  while (non_space_char(*sc))
    ;
  return sc;  // return pointer to character after space
}

char *token_terminator(char *token) {
  // assuming we're on a word, return the (space) character immediately after
  // the word.
  while (non_space_char(*token++)) {
    printf("checked %c\n", *token);  // DEBUG: STOPS HERE!!
  };
  printf("token terminator ends...\n");  // DEBUG
  return token;
}

// int count_tokens(char *str) {
//   int count = 0;
//   // iterate over string
//   while (*str++ != '\0') {
//     if (non_space_char(*str)) {  // if non space (word) detected
//       count++;
//       while (non_space_char(*str++))
//         ;  // skip all chars in this word
//     }
//   }
//   return count;
// }

// V2
int count_tokens(char *str) {
  int count = 0;
  while (*str++ != '\0') {
    printf("counter iteration...");  // DEBUG
    if (non_space_char(*str)) {
      count++;
      // skip str to the space / terminator following this word.
      str = token_terminator(str);
    }
    printf("NEW this runs inside the loop\n");
  }
  printf("NEW this runs\n");
  return count;
}

char *copy_str(char *inStr, short len) {
  // allocate heap memory (one more than len for \0)
  char *newstr = malloc(sizeof(char) * (len + 1));
  char *newstrslider = newstr;

  // new and improved copy loop
  while (non_space_char(*inStr)) {
    *newstrslider = *inStr;
    inStr++;
    newstrslider++;
  }

  // terminate with zero
  *newstrslider = '\0';

  // return poniter
  return newstr;
}

char *skip_spaces(char *str) {
  while (space_char(*str))
    ;  // skip any space characters

  if (*str == '\0') {
    return NULL;
  } else {
    return str;
  }
}

char **tokenize(char *str) {
  printf("NEW this runs\n");  // DEBUG
  int numtokens = count_tokens(str);
  printf("count_tokens returned: %d\n", numtokens);  // DEBUG
  char **tokens = malloc(sizeof(char *) * numtokens + 1);
  printf("tokenizing each word...\n");  // DEBUG
  for (int i = 0; i < numtokens; i++) {
    int strsize = (token_terminator(str) - str);
    printf("strsize: %d\n", strsize);
    tokens[i] = copy_str(str, strsize);
    str = token_start(str);
  }
  tokens[numtokens] = NULL;

  return tokens;
}

void print_tokens(char **tokens) {
  for (int i = 0;; i++) {
    if (tokens[i] == NULL) {
      return;
    }
    printf("%s\n", tokens[i]);
  }
}

void free_tokens(char **tokens) {
  for (int i = 0;; i++) {
    if (tokens[i] == NULL) {  // break at the end of array
      return;
    }
    free(tokens[i]);
    tokens[i] = NULL;  // nullify pointer after freeing
  }

  free(tokens);
  tokens = NULL;  // nullify tokens itself
}
