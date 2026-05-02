#include <stdio.h>
#include "singleLinked.h"

list_t *list_alloc(void);
void list_free(list_t *list);
int list_prepend(list_t *list, int val);
int list_append(list_t *list, int val);
int list_insert(list_t *list, int val, size_t pos);
int list_rm(list_t *list, int *val, size_t pos);
int list_set(list_t *list, int val, size_t pos);
int list_get(list_t *list, int *val, size_t pos);
int list_print(list_t *list);

int main(void) {
  list_t *list = list_alloc();

  list_prepend(list, 1);
  list_prepend(list, 2);
  list_prepend(list, 3);
  list_append(list, 0);
  list_print(list);
  
  int x;
  if (list_get(list, &x, 3) == 0) {
    printf("\n oh look at this %d\n", x);
  } else {
    printf("oh no \n");
  }

  list_insert(list, 30, 4);
  list_print(list);

  list_set(list, 100, 4);
  list_print(list);

  list_rm(list, NULL, 4);
  list_print(list);

  list_free(list);
}
