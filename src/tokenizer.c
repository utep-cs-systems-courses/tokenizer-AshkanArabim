#include "tokenizer.h"

#include <stdio.h>
#include <stdlib.h>

int space_char(char c) { return c != '\0' && (c == '\t' || c == ' '); }

int non_space_char(char c) { return c != '\0' && !space_char(c); }

char *token_start(char *str) {
  // skip characters until you reach a space
  while (non_space_char(*str++))
    ;
  return str;  // return pointer to character after space
}

char *token_terminator(char *token) {
  // assuming we're on a word, return the (space) character immediately after
  // the word.
  while (non_space_char(*token)) {
    if (*token == '\n') {
      // printf("\\n detected alert!"); // DEBUG
    }
    token++;
  };
  return token;
}

int count_tokens(char *str) {
  int count = 0;
  // while (*str++ != '\0') {
  while(*str != '\0') {
    if (non_space_char(*str)) {
      count++;
      // skip str to the space / terminator following this word.
      // note: token terminator points to anything AFTER the word
      // so if you reach a \n and increment here as well you are screwed.
      str = token_terminator(str); 
    } else {
      str++; // only increment when not using token_terminator
    }
  }
  // printf("I just read: %s\n", str); // DEBUG
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
  int numtokens = count_tokens(str);
  // printf("count_tokens returned: %d\n", numtokens);  // DEBUG
  char **tokens = malloc(sizeof(char *) * numtokens + 1);
  for (int i = 0; i < numtokens; i++) {
    int strsize = (token_terminator(str) - str);
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
