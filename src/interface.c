#include <stdio.h>

#include "history.h"
#include "tokenizer.h"

int get_stdin_id(char line[100]) {
  line++;  // skip the '^' at the beginning
  // -1 means user entered ^ with no following digits.
  int id = -1;

  // check if this is a digit in ascii
  for (int i = 0; line[i] >= 48 && line[i] < 58; i++) {
    if (id == -1) {
      id = 0;
    }
    int digit = line[i] - 48;
    id = id * 10 + digit;
  }
  return id;
}

int main() {
  printf("Welcome to Ashkan's tokenizer!\n");
  printf("Enter any sentence to see it tokenized.\n");
  printf(
      "To quit, enter 'q' (anything starting with 'q' ends the program. If you "
      "have a sentence like that, add a space at the beginning.\n");
  printf(
      "To access history, use this format: '^x' where [x] represents a "
      "number\n");

  List* history = init_history();
  while (1) {
    printf("quit: 'q', history: '^[x]'\n");
    printf("> ");

    char line[100];
    fgets(line, sizeof(line), stdin);
    // printf(line);

    if (line[0] == 'q') {
      printf("Quit...\n");
      free_history(history);
      break;

    } else if (line[0] == '^') {
      int hist_id = get_stdin_id(line);
      if (hist_id == -1) {
        printf("Your '^' was not followed by digits...\n");
        continue;
      }
      char* hist_line = get_history(history, hist_id);
      printf("History item %i: %s\n", hist_id, hist_line);

    } else {
      // add to history
      printf("before add history\n");
      add_history(history, line);
      printf("after add history\n");
      // tokenize & print
      char** tokens = tokenize(line);
      print_tokens(tokens);
      // free tokens right now since we
      // won't use them again...
      free_tokens(tokens);
    }
  }
}
