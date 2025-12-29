#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
	int data;
	struct node_s *next;
} node_t;

typedef struct list_s {
	node_t *head;
	node_t *tail;
	size_t size;
} list_t;


// functions to implement

list_t *list_alloc(void) {
	list_t *list;
  list = NULL;

  list = malloc(sizeof(list_t)); // dynamically allocate
  
  if (list == NULL) { //check if allocation fails
    return NULL;
  };

  return list;
}

int main(void) {
  list_t *list = list_alloc();

  if (!list) {
    printf("list_alloc failed");
    return 1;
  }

  printf("pointer %p\n", (void *)list);
  printf("list->head %p\n", (void *)list->head);
  printf("list->tail %p\n", (void *)list->tail);
  printf("list->size %zu\n", list->size);

  return 0;
}
