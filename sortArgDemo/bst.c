#include "stdlib.h"
#include "bst.h"

BstNode *root = 0;

// understood :)
int bstStrcmp(char *a, char *b) /* return pos if string a > string b, 0 if equal, neg otherwise */
{
  while (*a && *b) {		/* until end of string */
    int diff = *a++ - *b++;
    if (diff) return diff;	/* differed within string */
  }
  if (!*a && !*b) return 0;	/* strings are same length & content */
  return (*a) ? 1 : -1;		/* a > b if a is longer */
}

// understood :)
int bstStrlen(char *s)
{
  char *sc = s;
  while (*sc++) // how does this stop?
    ;
  return sc - s;
}

// QUESTIONS WHY DOES *(p+1) WORK FOR char **argv ??

// take a node pointer and a string,
// put the string into the node.
// understood :)
void
bstInsert(BstNode **rootp, char *str) // QUESTION: WHY IS THIS **?
{
  if (*rootp == 0) {		/* insert here if NULL pointer */
    BstNode *newNode = malloc(sizeof(BstNode));
    // BstNode *newNode = malloc(sizeof(BstNode));
    // newNode->children=NULL;
    // newNode->str="testing";
    // free(newNode) 
    // BstNode newNode = {.children=NULL, .str="my node"};
    for (int i = 0; i < 2; i++) newNode->children[i] = 0; // set children to null
    /* copy first zero-terminated  string from inbuf */
    int len = bstStrlen(str), sindex = 0; // take the length of the word
    char *scopy = malloc((len + 1) * sizeof(char)), c;
    // QUESTION: why are we using scopy and c for??
    
    do {
      c = *(scopy+sindex) = *(str+sindex); /* c = scopy[sindex] = str[sindex] */
      sindex++;
      // ^^ here, scopy is storing a copy of str
      // while c is only used to check for the null pointer
      // QUESTION: vv
      // I guess it's nicer to use c instead of *(scopy + sindex) ????
    } while (c);
    newNode->str = scopy;
    *rootp = newNode;
  } else {
    int diff = bstStrcmp(str, (*rootp)->str);
    bstInsert(&((*rootp)->children[(diff > 0) ? 1 : 0]), str);
  }
}

// understood :)
void
bstPrint(BstNode *root)		/* in order */
{
  if (root == 0) return;
  bstPrint(root->children[0]);
  puts(root->str);
  bstPrint(root->children[1]);
}

// clears the memory
void
bstClear(BstNode **rootp)
{
  if (*rootp == 0) return;
  for (int i = 0; i < 2; i++)
    bstClear(&(*rootp)->children[i]);
  free((*rootp)->str);
  free(*rootp);
  *rootp = 0;
}
