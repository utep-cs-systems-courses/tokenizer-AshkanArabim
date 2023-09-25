#include "stdio.h"

// typedef avoid you having to call 'struct' every time you want
// to use BstNode
typedef struct BstNode_s {
  struct BstNode_s *children[2];
  char *str;
} BstNode;

BstNode *bstRoot;

void bstInsert(BstNode **rootp, char *str);
void bstPrint(BstNode *root);
void bstClear(BstNode **rootp);

