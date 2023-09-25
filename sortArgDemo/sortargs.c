#include "bst.h"  
  
int main(int argc, char **argv)	/* prints arguments in order */
{
  printf("the program name is <%s>\n", *(argv+0)); // I don't get this.
  for (char **p = &argv[1]; *p; p++) // why is p a double pointer?
    bstInsert(&bstRoot, *p);
  // ^^ inserts a new word into the tree
  bstPrint(bstRoot);
  // ^^ just prints it in order
  bstClear(&bstRoot);
  // IF YOU DON'T FREE THE MEMORY
  // YOU'RE SCREWED
}
