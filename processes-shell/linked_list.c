#include <string.h>
#include <stdlib.h>
#include "linked_list.h"

node* prepend (node* nodes, char* data) {
  node* new_node = malloc (sizeof (node));
  new_node->data = strdup (data);
  new_node->link = nodes;
  return new_node;
}

void free_nodes (node* nodes) {
  while (nodes) {
    node* tmp = nodes->link;
    free (nodes->data);
    free (nodes);
    nodes = tmp;
  }
}
