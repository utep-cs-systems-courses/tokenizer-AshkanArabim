#include "history.h"
#include <stdlib.h>
#include <stdio.h>

List* init_history() {
  List *list = malloc(sizeof(List));
  list->root = NULL;
  return list;
}

void add_history(List *list, char *str) {
  /* // special case: if list is empty, insert here */
  /* // if(!*(list->root)){ */
  /* if(list->root == NULL){ */
  /*   // list->root = malloc(sizeof(Item)); */
  /*   // *(list->root) = {.id = 0, .str = str}; */
  /*   // PROBLEM ^^ */

  /*   // for each list sub-item, allocate memory, */
  /*   // then put a value in it. */
  /*   list->root = malloc(sizeof(Item)); // allocate for root (Item) */
  /*   list->root->id = malloc(sizeof(int)); // allocate for id */
  /*   *(list->root->id) = 0; // assign id */
  /*   list->root->str = malloc(sizeof(char*)); // allocate for *str */
  /*   *(list->root->str) = str; // assign str */
  /*   list->root->next = malloc(sizeof(Item*)); // allocate for next */
  /*   *(list->root->next) = NULL; // assign next to NULL (bc it's the last one) */
  /*   return; */
  /* } */
  
  /* int id_counter = 0; */
  
  /* // skip to the last list item */
  /* while (list->next){ */
  /*   id_counter++; */
  /*   list = list->next; */
  /* } */
  /* // initialize next to a list containing str and the id */
  /* *(list->next) = {.str = str, .id = ++id_counter}; */

  // alternate improved logic
  int id_counter = 0;
  Item* histitem = list->root;

  while(histitem != NULL) {
    histitem = histitem->next;
    id_counter++;
  }
  
  list->root = malloc(sizeof(Item)); // allocate for root (Item)
  // list->root->id = malloc(sizeof(int)); // allocate for id
  list->root->id = id_counter; // assign id
  list->root->str = malloc(sizeof(char*)); // allocate for char* str
  list->root->str = str; // assign str
  list->root->next = malloc(sizeof(Item*)); // allocate for Item* next
  list->root->next = NULL; // assign next to NULL (bc it's the last one)
}

char *get_history(List* list, int id) {
  printf("%p", list); // DEBUG
  Item *item = list->root;
  printf("inside get_hist..."); // DEBUG
  char *word = item->str; // these default to the first
  printf("inside get_hist..."); // DEBUG
  // so, in the for loop below we use i<id to avoid duplicaiton.

  // loop until you reach that index
  for(int i=0; i < id; i++) {
    item = item->next;
    word = item->str;
  
    printf("inside get_hist loop %d...", i); // DEBUG

    // if we go out of bounds
    if(*word) {
      printf("%s\n", "Index out of bounds!");
      return NULL;
    }
  }

  return word;
  //  printf("word [%d]: %s\n", id, word);
}

void print_history(List *list) {
  Item *item = list->root;

  int index_counter = 0;
  while(1){
    char *word_ptr = get_history(list, index_counter);
    if(!*word_ptr){
      return;
    }

    printf("%s\n", word_ptr);
  }
}

// can't be recursive:
// it's passing a list, NOT an item!
void free_history(List *list) {
  // base case: there are no more nodes
    // return;

  // recurseive case:
    // recurse on next pointer
    // free id
    // free str(it's a pointer)
    // free self

  /* if (!*list) { */
  /*   return; */
  /* } else { */
  /*   free_history(list->next); // free child */
  /*   free(list->id); // free id */
  /*   free(list->str); // free str */
  /*   free(list); // free self */
  /* } */

  // ------ new logic ------
  // free all list items until nothing left
  Item* histitem = list->root;
  while (histitem != NULL) {
    // id doesn't need to be freed since it's a ptr
    // by freeing histitem (or a copy), id will be freed as well
    free(histitem->str);

    // copy histitem pointer to temp
    // to not lose access to the next pointer
    // after freeing this one
    Item* tempptr = histitem;
    histitem = histitem->next;
    free(tempptr);
  }

  // free list itself
  free(list);
}
