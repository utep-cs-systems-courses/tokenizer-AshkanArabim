#include "tokenizer.h"
#include "history.h"
#include <stdlib.h>
#include <stdio.h>

List* init_history() {
  List *list = malloc(sizeof(List));
  list->root = NULL;
  return list;
}

char *copy_line(char *str) {
  // make a stack variable
  // copy str to new var
  // get size of var
  // allocate heap memory for var
  // return pointer

  // -- alternate logic --
  // allocate heap memory for 100 chars
  // NOTE: line size is hard-coded; I'm a lazy idiot.
  char *newstr = malloc(sizeof(char) * 100);
  // copy string --> \0 is already included
  for (int i = 0; i < 100; i++) {
    newstr[i] = str[i]; 
    // newstr[i] = '\0'; // doesn't work with all \0 either :/
  }
  // return pointer
  return newstr;
}

void add_history(List *list, char *str) {
  printf("add_history works\n"); // DEBUG

  // alternate improved logic
  int id_counter = 0;
  if (list->root == NULL) {
    list->root = malloc(sizeof(Item)); // allocate for list->root (Item)
    list->root->id = id_counter; // assign id
    list->root->str = copy_line(str); // copy str to list->root
    list->root->next = NULL; // assign next to NULL (bc it's the last one)
    return;
  }

  Item* histitem = list->root;
  printf("add_history 2 works\n"); // DEBUG

  // skip until last element
  while(histitem->next != NULL) {
    printf("element %i is full.\n", id_counter); // DEBUG
    histitem = histitem->next;
    id_counter++;
  }
  
  printf("add_history 3 works\n"); // DEBUG

  // create new pointer
  Item *new_histitem = malloc(sizeof(Item)); // allocate for root (Item)
  new_histitem->id = id_counter + 1; // assign id
  new_histitem->str = copy_line(str); // copy str to new_histitem
  new_histitem->next = NULL; // assign next to NULL (bc it's the last one)

  // link last element to new element
  histitem->next = new_histitem;
  
  // printf("%s\n", new_histitem->str); // DEBUG: works

  // doesn't even start.
  // printf("list->root: %p\n", list->root); // DEBUG

  // printf("right after the fault\n"); // DEBUG: doesn't run
}

char *get_history(List* list, int id) {
  printf("we are in get history...");
  printf("%p", list); // DEBUG
  Item *item = list->root;
  printf("inside get_hist...\n"); // DEBUG
  char *line = item->str; // these default to the first
  printf("inside get_hist...\n"); // DEBUG
  // so, in the for loop below we use i<id to avoid duplicaiton.

  // loop until you reach that index
  for(int i=0; i < id; i++) {
    item = item->next;
    line = item->str;
  
    printf("inside get_hist loop %d...", i); // DEBUG

    // if we go out of bounds
    if(item == NULL) {
      printf("%s\n", "Index out of bounds!");
      return NULL;
    }
  }

  return line;
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
