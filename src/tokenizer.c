#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

int space_char(char c) {
  return c != '\0' && (c == '\t' || c == ' ');
}

int non_space_char(char c) {
  return c != '\0' && !space_char(c);
}

char *token_start(char *str){
  // skip characters until you reach a space
  char *sc = str;
  while (non_space_char(*sc++));
  return sc; // return pointer to character after space pointer
}

char *token_terminator(char *token) {
  // QUESTION: I don't get the description in the header...
  char *sc = token;
  // assuming we're on a word, return the (space) character immediately after the word.
  while (non_space_char(*sc++));
  return sc;
}

int count_tokens(char *str) {
  int count = 0;
  // iterate over string
  while(*str++ != '\0') {
    if (non_space_char(*str)) { // if non space (word) detected
      count++;
      while(non_space_char(*str++)); // skip all chars in this word
    }
  }
  return count;
}

char *copy_str(char *inStr, short len) {
  // allocate heap memory (one more than len for \0)
  char* newstr = malloc(sizeof(char) * (len + 1));
  char* newstrslider = newstr;

  //// iterate and copy
  //do{
    //*newstrslider = *inStr;
    //newstrslider++;
  //} while (++inStr);


  // new and improved copy loop
  while(non_space_char(*inStr)){
    *newstrslider = *inStr;
    inStr++;
    newstrslider++;
  }
  
  // terminate with zero
  *newstrslider = '\0';

  // return poniter
  return newstr;
}

/* char* skip_letters(char* str) { */
/*   while(non_space_char(str++)); // skip any non-space character */

/*   // probably not necessary, */
/*   // but, this will return a null pointer if we reach the end of the string */
/*   if (*str == '\0') { */
/*     return NULL; */
/*   } else { */
/*     return str; */
/*   } */
/* } */

char* skip_spaces(char* str) {
  while(space_char(*str)); // skip any space characters

  if (*str == '\0') {
    return NULL;
  } else {
    return str;
  }
}

char** tokenize(char* str){
  // V2 vv
  int numtokens = count_tokens(str);
  char** tokens = malloc(sizeof(char*) * numtokens + 1);
  for (int i = 0; i < numtokens; i++) {
    int strsize = (token_terminator(str) - str);
    tokens[i] = copy_str(str, strsize);
    str = token_start(str);
  }
  tokens[numtokens] = NULL;

  return tokens;
  // V2 ^^
  
  // int tindex = 0;

  // sc = str // copy of pointer at beginning

    // if is_space(sc):
    // sc = skip_spaces(sc) --> func?

  //// add the pointers to the start of each token to "tokens"
  //// option 1: vv don't touch original text, just add tokens --> BAD
  // while is_not_space(sc):
    // char* token = sc
    // tokens[counter] = token;
    // sc = skip_letters(sc) --> func?
    // counter++

  //// option 2: vv copy each token to heap, add THAT to "tokens"
  // while (sc != \0):
    // if space --> skip
    // ..
}

void print_tokens(char **tokens) {
  for(int i = 0; ; i++) {
    if (tokens[i] == NULL) {
      return;
    }
    printf("%s\n", tokens[i]);
  }
}

void free_tokens(char **tokens) {
  for(int i = 0; ; i++) {
    if (tokens[i] == NULL) { // break at the end of array
      return;
    }
    free(tokens[i]);
    tokens[i] = NULL; // nullify pointer after freeing
  }

  free(tokens);
  tokens = NULL; // nullify tokens itself
}
