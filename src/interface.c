#include <stdio.h>

int main() {
  printf("Welcome to Ashkan's tokenizer!\nEnter your sentence and press enter.\n");
  while(1) {
    printf(">");
    // don't go to next iteration until you reach a newline character.
    // char c = getchar();
    // char c;
    /* while(c = getchar()){ */
    /*   printf("%c", c); */
    /* } */

    char line[100];
    fgets(line, sizeof(line), stdin);
    printf(line);
  }
}
