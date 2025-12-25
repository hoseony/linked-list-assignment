#include <stddef.h>
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
list_t *list_alloc(void);
void list_free(list_t *list);
int list_prepend(list_t *list, int val);
int list_append(list_t *list, int val);
int list_insert(list_t *list, int val, size_t pos);
int list_rm(list_t *list, int *val, size_t pos);
int list_set(list_t *list, int val, size_t pos);
int list_get(list_t *list, int *val, size_t pos);
