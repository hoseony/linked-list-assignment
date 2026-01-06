#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct node_s {
  void *data;
  struct node_s *prev;
  struct node_s *next;
} node_t;

typedef struct list_s {
  node_t *head;
  node_t *tail;
  size_t size;
} list_t;

list_t *list_alloc(void) {
  list_t *list;
  list = NULL;

  list = malloc(sizeof(list_t));
  if (list == NULL) {
    return NULL;
  }

  list->head = NULL;
  list->tail = NULL;
  list->size = 0;

  return list;
}







//print function for debugging
void list_print(list_t *list) {
  if (list == NULL) {
    printf("NULL list");
    return;
  }

  printf("size = %d\n", list->size);

  node_t *cur = list->head;
  size_t index = 0;

  while (cur != NULL) {
    printf("node %zu: ", index);

    if (cur->data == NULL) {
      printf("NULL data");
      return;
    } else {
      int *p = *(int *)cur->data;
      for (int i = 0; i < 9; i++) {
        printf("%d ", p[i]); //pointer arithmetic (for my note)
      }
    }

    printf("\n");
    cur= cur->next;
    index++;
  }
}

//3x3 matrix function for testing
void mk_matrix(void) {

}




int main(void) {
  
}

